

/*
    This is a periodicaly can bus message sender script with Interrupt Reading
*/

#include <Arduino.h>
#include <stdint.h>
#include <SPI.h>
#include <mcp2515_can.h>
#include <TaskScheduler.h>
#include <PID_v2.h>
#include "arduino_dbc_driver-binutil.h"
//#include <OBD2.h>  DO NOT INCLUDE BEFORE REDEFINE MPC2515 CAN header files!

//includ debugging:
#define DEBUG
    
#ifdef DEBUG
    #include "avr8-stub.h"
    #include "app_api.h"
#endif



 
#define TPS_POTI_READ_PIN A0
#define DCDC_RELAY_PIN 6

//User defined Macro to send a CAN frame
#define SEND_CAN_MESSAGE(msg) \
    CAN.sendMsgBuf(msg.MsgId, msg.IDE, msg.DLC, msg.charData);



// Specify the links and initial tuning parameters of voltage controller
double Kp1 = 1.5, Ki1 = 2, Kd1 = 1, Ts1 = 100;
//Battery terminal PID voltage controller
PID_v2 U_Bat_PID(Kp1, Ki1, Kd1, PID::Direct);

// Specify the links and initial tuning parameters of current controller
double Kp2 = 7, Ki2 = 5, Kd2 = 0, Ts2 = 100;
//Battery charching PID current controller
PID_v2 I_Bat_PID(Kp2, Ki2, Kd2, PID::Direct);


//Global variabels (from i/o pins and other storage)
int n_requested;
float i_requested;
long time_notice;       //time used to unlock batery air's on command
float tps_act;
int threshold_tps = 0.8;
float u_max_tps = 4.8;
float u_min_tps = 0.2;


// Callback methods (time based Events)
void t_Startup_Event();
void t_100Hz_Event();
void t_20Hz_Event();
void t_5Hz_Event();


//Tasks
Task t_Startup(1, TASK_ONCE, &t_Startup_Event);
Task t_100Hz(1000/100, TASK_FOREVER, &t_100Hz_Event);
Task t_20Hz(1000/20, TASK_FOREVER, &t_20Hz_Event);
Task t_5Hz(1000/5, TASK_FOREVER, &t_5Hz_Event);

Scheduler scheduler;


// Set SPI CS Pin according to used hardware
// For Arduino MCP2515 Shield:
// SPI_CS Pin: D9

const int SPI_CS_PIN = 9;

mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

CanFrame rxframe;
CanFrame txframe;


///-------------GENERAL FUNCTIONS---------------///

/**************************************************************************/
/*!
    @brief    Read incoming CAN Messages while main loop is interpted
    @param    none
    @returns  none
*/
/**************************************************************************/
void CanRxInterrupt(void) {

    CAN.readMsgBuf(&rxframe.DLC, rxframe.charData);
    rxframe.IDE = CAN.getCanId();
    rxframe.time = millis();

    arduino_dbc_driver_Receive(&arduino_dbc_driver_rx, rxframe.Data, rxframe.IDE , rxframe.DLC);

    //Serial.println(canId, HEX);
    //Serial.println(canId);
    
}   


/**************************************************************************/
/*!
    @brief    Precharge the 48V System and boot the 48V Battery.
              Voltage must be in -+ 2V Range of batery for 500ms to close Circuit Breaker.
    @param    none
    @returns  none
*/
/**************************************************************************/
void Boot_48V_Bat(void){

    double U_Stack = DBC_DRIVER_veh_bms_db_stack_U_ro_fromS(double(arduino_dbc_driver_rx.VEH_BMS_PACK_DATA_1.veh_bms_db_stack_U_ro));
    double U_Terminal = DBC_DRIVER_veh_bms_db_term_U_ro_fromS(double(arduino_dbc_driver_rx.VEH_BMS_PACK_DATA_1.veh_bms_db_term_U_ro));

    U_Bat_PID.Setpoint(U_Stack);                 //Calculate new PWM by PID Controller
    const double input = U_Terminal;
    const double output = U_Bat_PID.Run(input);
    analogWrite(DCDC_RELAY_PIN, output);

    if (time_notice >= 500)                             //Check if condition was met the last 500ms
    {
        
        arduino_dbc_driver_tx.VEH_MSG_TO_BMS.veh_cb_cmd_e = 1;
        analogWrite(DCDC_RELAY_PIN, 0);
    }


    if ((U_Terminal < (U_Stack + 2)) & (U_Terminal > (U_Stack - 2)) & (U_Terminal > 1))
    {
        time_notice += 50;                              //Increment the timer by 50ms while condition met (20Hz Event)
    }

    else
    {
        time_notice = 0;                                //When out of +- 2V Range set timer to 0 and set open CB command
        arduino_dbc_driver_tx.VEH_MSG_TO_BMS.veh_cb_cmd_e = 0;
    }
}

/**************************************************************************/
/*!
    @brief    Set the charching current, integrated PID Current control
    @param    current: Final charching current
    @returns  none
*/
/**************************************************************************/
void Set_48V_charching_current(const float current){

    //Calculate new PWM by PID Controller
    if (arduino_dbc_driver_rx.VEH_BMS_PACK_DATA_2.veh_bms_db_cb_status_e == 1)
    {   
        //const float current_requested min(current, Bat48V.I_chrg_avail);
        const float current_requested = current;
        const double current_acctual = DBC_DRIVER_veh_bms_db_inst_I_ro_fromS(double(arduino_dbc_driver_rx.VEH_BMS_PACK_DATA_1.veh_bms_db_inst_I_ro));

        I_Bat_PID.Setpoint(current_requested);
        const double input = current_acctual;
        const double output = I_Bat_PID.Run(input);

        if(current <= 0.5){
            analogWrite(DCDC_RELAY_PIN, 0);
            
            }
        else{analogWrite(DCDC_RELAY_PIN, output);}


        Serial.println(output);
    }
}



/**************************************************************************/
/*!
    @brief    Stops the ebooster turning(if not allready happen) and resets error states
              (necessary on every startup to start idle or any other shaft speed)
    @param    none
    @returns  none
*/
/**************************************************************************/
void ebooster_reset_fault(void){
    unsigned char DATA0x06d[8] = {0, 0, 0x03, 0x00, 0, 0, 0, 0}; 

    CAN.sendMsgBuf(0x06d, 0, 8, DATA0x06d);
    CAN.sendMsgBuf(0x06d, 0, 8, DATA0x06d);
    CAN.sendMsgBuf(0x06d, 0, 8, DATA0x06d);
}


/**************************************************************************/
/*!
    @brief    n_set of the eBooster will be set to idle speed (normal operation in standby)
    @param    none
    @returns  none
*/
/**************************************************************************/
void ebooster_idle_speed(void){

    arduino_dbc_driver_tx.VEH_TO_EBOOSTER_CONTROL.target_speed_ebooster_ro = 40;
    
}


/**************************************************************************/
/*!
    @brief    Sets the requested speed of the eBooster(n_set in RPM (6'000-80'000)) 
    @param    none
    @returns  none
*/
/**************************************************************************/
void ebooster_set_speed(int16_t rpm_speed){
    
    arduino_dbc_driver_tx.VEH_TO_EBOOSTER_CONTROL.target_speed_ebooster_ro = DBC_DRIVER_target_speed_ebooster_ro_toS(rpm_speed);
    
    }


/**************************************************************************/
/*!
    @brief    Sets the maximal current the ebooster can use in ampere
    @param    none
    @returns  none
*/
/**************************************************************************/
void ebooster_set_max_current(int8_t I_max){

    arduino_dbc_driver_tx.VEH_TO_EBOOSTER_CONTROL.max_current_48V = I_max;
    
    }



///-------------TIMED EVENTS---------------///

/**************************************************************************/
/*!
    @brief    Callback method Startup task - Will be executed once at startup
    @param    none
    @returns  none
*/
/**************************************************************************/
void t_Startup_Event() {

    Serial.print("t_Startup: ");
    Serial.println(millis());
  
}



/**************************************************************************/
/*!
    @brief    Callback method of task 100_Hz_Event - Can id's that will be 
              sent with a Frequence of 100Hz
    @param    none
    @returns  none
*/
/**************************************************************************/
void t_100Hz_Event() {

    Pack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(&arduino_dbc_driver_tx.VEH_TO_EBOOSTER_CONTROL, &txframe);
    SEND_CAN_MESSAGE(txframe);
    //Serial.println("CAN BUS sendMsgBuf ok!");
    //Serial.print("t_100Hz: ");
    //Serial.println(millis());

     
}



/**************************************************************************/
/*!
    @brief    Callback method of task t_20Hz_Event - Can id's that will be 
              sent with a Frequence of 20Hz
    @param    none
    @returns  none
*/
/**************************************************************************/
void t_20Hz_Event() {

    if ((arduino_dbc_driver_rx.VEH_BMS_PACK_DATA_2.veh_bms_db_cb_status_e != 1) & (millis() > 1000)) //Try to startup 48V within 1000ms after Startup of system
    {
        Boot_48V_Bat();
    }

    Set_48V_charching_current(i_requested);

    //Only use to tune controller parameters (Simulate step response)
    //int Jump = digitalRead(A5);
    //if(Jump > 0){Bat48V.U_cells = 20;}
    //else{Bat48V.U_cells = 40;}
    //U_Bat_PID.Setpoint(Bat48V.U_cells);
    //const double input = Bat48V.U_terminal;
    //const double output = U_Bat_PID.Run(input);
    //analogWrite(DCDC_RELAY_PIN, output);

    Pack_VEH_CRASH_dbc_driver(&arduino_dbc_driver_tx.VEH_CRASH, &txframe);
    SEND_CAN_MESSAGE(txframe);

    Pack_VEH_MSG_TO_BMS_dbc_driver(&arduino_dbc_driver_tx.VEH_MSG_TO_BMS, &txframe);
    SEND_CAN_MESSAGE(txframe);
    
    //Serial.println("CAN BUS sendMsgBuf ok!");
    //Serial.print("t_20Hz: ");
    //Serial.println(millis());
}



/**************************************************************************/
/*!
    @brief    5Hz Task, used to read analog pins and User inputs
    @param    none
    @returns  none
*/
/**************************************************************************/
void t_5Hz_Event() {
    
    /*
    const int ANALOG_Max_Value = 1023;
    const int RPM_Max_Value = 72000;
    const int RPM_Conv_Factor = 100;

    int n_requested_raw = analogRead(A0);
    n_requested = round((float)n_requested_raw / ANALOG_Max_Value * RPM_Max_Value / RPM_Conv_Factor); 
    */
    
    int n_requested_raw = analogRead(TPS_POTI_READ_PIN);
    n_requested = round((float)n_requested_raw / 1023 * 72000);       //Read poti value and convert it to requested eBooster RPM
    i_requested = exp((float)n_requested_raw / 1023 * 5)-1; 

    arduino_dbc_driver_tx.VEH_TO_EBOOSTER_CONTROL.target_speed_ebooster_ro = DBC_DRIVER_target_speed_ebooster_ro_toS(n_requested); 

    //Serial.println(i_requested);

    
    //Only use to tune controller parameters
    //const float Inte_val = exp((float)n_requested_raw / 1023 * 10)-1;
    //U_Bat_PID.SetTunings(Kp1, Inte_val, Kd1);
    //Serial.println(U_Bat_PID.GetKi1());
    //Serial.println();

    
    //digitalWrite(DCDC_RELAY_PIN, Bat48V.CB_State);
    //Serial.println(Bat48V.CB_State);

}



///-------------ARDUINO SETUP---------------///

void setup() {

    
    Serial.begin(115200);

        
    #ifdef DEBUG
        //Serial.print("Debugging active");
        //Serial.end();
        debug_init();
    #endif

    /*Init start values
    eBooster.Fault = false;     //Set all faults to false
    Bat48V.Fault = false;
    
    
    //define initial values of can frame 
    eBooster_VEH_MSG_0x06d.id = 0x06d;
    eBooster_VEH_MSG_0x06d.extended = 0;
    eBooster_VEH_MSG_0x06d.length = 8;

    Bat48V_VEH_MSG_0x500.id = 0x500;
    Bat48V_VEH_MSG_0x500.extended = 0;
    Bat48V_VEH_MSG_0x500.length = 2;

    Bat48V_VEH_CRASH_0x501.id = 0x501;
    Bat48V_VEH_CRASH_0x501.extended = 0;
    Bat48V_VEH_CRASH_0x501.length = 1;
    Bat48V_VEH_CRASH_0x501.data.int8[0] = 0x80;

    Custom_Diag_Data_0x666.id = 0x666;
    Custom_Diag_Data_0x666.extended = 0;
    Custom_Diag_Data_0x666.length = 8;
    */


    //Initialise TaskScheduler
    Serial.println("Scheduler TEST");
    
    scheduler.init();
    Serial.println("Initialized scheduler");
    
    scheduler.addTask(t_100Hz);
    Serial.println("added t_100Hz");
    
    scheduler.addTask(t_20Hz);
    Serial.println("added t_20Hz");

    scheduler.addTask(t_5Hz);
    Serial.println("added t_5Hz");
    
    scheduler.addTask(t_Startup);
    Serial.println("added t_Startup");

    delay(500);
    
    t_100Hz.enable();
    t_20Hz.enable();
    t_5Hz.enable();   
    t_Startup.enable();
    Serial.println("All Tasks enabled");

    // Setup Arduino I/O Pins definitions
    pinMode(DCDC_RELAY_PIN, OUTPUT);
    pinMode(TPS_POTI_READ_PIN, INPUT);
    pinMode(A5, INPUT_PULLUP);
    Serial.println("I/O Pins initialized sucessfully");

    // Setup controllers
    double U_init = DBC_DRIVER_veh_bms_db_term_U_ro_fromS((double)arduino_dbc_driver_rx.VEH_BMS_PACK_DATA_1.veh_bms_db_term_U_ro);
    double I_init = DBC_DRIVER_veh_bms_db_inst_I_ro_fromS((double)arduino_dbc_driver_rx.VEH_BMS_PACK_DATA_1.veh_bms_db_inst_I_ro);

    U_Bat_PID.Start(U_init,                         // input
              40,                                   // current output
              42);                                  // setpoint (Voltage at terminal)

    U_Bat_PID.SetOutputLimits(0, 100);
    U_Bat_PID.SetSampleTime(Ts1);


    I_Bat_PID.Start(I_init,                         // input    
                0,                                  // current output
                0);                                 // setpoint (charching current)

    I_Bat_PID.SetOutputLimits(0, 255);
    I_Bat_PID.SetSampleTime(Ts2);


    // Initialise and setup CAN-Bus shield
    Serial.begin(115200);
    while(!Serial); // wait for Serial

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(500);
    }

  
    //set mask for incomming data, set both the mask to 0x3ff
    CAN.init_Mask(0, 0, 0x3ff);                                 // there are 2 mask in mcp2515, we need to set both of them to recive all
    CAN.init_Mask(1, 0, 0x3ff);


    //set filter for all id's we will recive there are 6 filter in mcp2515
/*
    CAN.init_Filt(0, 0, eBooster_h);                            // eBooster act. Values (RPM, Current....)
    CAN.init_Filt(1, 0, Batt_Data2);                            // Battery Data 2 CB State, Temp....

    CAN.init_Filt(2, 0, Batt_PWR10);                            // Battery 10s available charge/discaharge power 
    CAN.init_Filt(3, 0, Batt_Data1);                            // Battery Data 1 Current, Voltage
    CAN.init_Filt(4, 0, eBooster_l);                            // eBooster Temp and Voltage
*/
    Serial.println("CAN init ok!");

 }



///-------------MAIN LOOP---------------///

void loop() {

    while (CAN_MSGAVAIL == CAN.checkReceive())
    {
        CanRxInterrupt();
        //Serial.println("MSG detectet on RX");
    }
    
    scheduler.execute();

}

// END FILE
