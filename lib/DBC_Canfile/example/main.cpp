#include <Arduino.h>
#include "arduino_dbc_driver-binutil.h"  //load the DBC Can Database

CanFrame txframe;


void setup() {
  Serial.begin(115200);

}

void loop() {

	CanFrame rxtestframe;
  
	rxtestframe.MsgId = EBOOSTER_DATA_AND_FAULT_CANID;
	rxtestframe.DLC = EBOOSTER_DATA_AND_FAULT_DLC;

	rxtestframe.Data[0] = 0x5B;
	rxtestframe.Data[1] = 0x5B;
  	rxtestframe.Data[2] = 0x5B;
	rxtestframe.Data[3] = 0xBC;
	rxtestframe.Data[4] = 0x02;
	rxtestframe.Data[5] = 0x5B;
	rxtestframe.Data[6] = 0x5B;
	rxtestframe.Data[7] = 0x5B;    

	// Frame from CAN bus is passing through CAN parser via *_Receive function
	// Proper ID or 0 will be returned
  
  auto id = arduino_dbc_driver_Receive(&arduino_dbc_driver_rx, rxtestframe.Data, rxtestframe.MsgId, rxtestframe.DLC);

	if (id == EBOOSTER_DATA_AND_FAULT_CANID)
	{	

		Serial.println("eBooster data and fault frame received : ");
		// to get meaningful value fromS macro must be applied

		Serial.println(DBC_DRIVER_actual_speed_ebooster_ro_fromS((double)arduino_dbc_driver_rx.EBOOSTER_DATA_AND_FAULT.actual_speed_ebooster_ro));

	}

	// Make packing back

	arduino_dbc_driver_tx.VEH_TO_EBOOSTER_CONTROL.target_speed_ebooster_ro = DBC_DRIVER_target_speed_ebooster_ro_toS(30000);


	// Pack signal to CAN struct
	Pack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(&arduino_dbc_driver_tx.VEH_TO_EBOOSTER_CONTROL, &txframe);
	// tx frame now ready to be sent
	// CANNodeSendFrame(&txframe);

	Serial.println("MsgId: " + String(int(txframe.MsgId)));

	Serial.println("DLC: " +  String((txframe.DLC)));

	for (int32_t i = 0; i < txframe.DLC && i < 8; i++)
	{
		Serial.println("Data [" + String((i)) + "] = " + String((txframe.Data[i]))); 
	}
  delay(2000);
}



