// Generator version : v3.1
// DBC filename      : Pony_V2.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// DBC file version
#define VER_DBC_DRIVER_MAJ (0U)
#define VER_DBC_DRIVER_MIN (0U)

// include current dbc-driver compilation config
#include "dbc_driver-config.h"

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
// This file must define:
// base monitor struct
#include "canmonitorutil.h"

#endif // DBC_DRIVER_USE_DIAG_MONITORS


// DLC maximum value which is used as the limit for frame's data buffer size.
// Client can set its own value (not sure why) in driver-config
// or can test it on some limit specified by application
// e.g.: static_assert(TESTDB_MAX_DLC_VALUE <= APPLICATION_FRAME_DATA_SIZE, "Max DLC value in the driver is too big")
#ifndef DBC_DRIVER_MAX_DLC_VALUE
// The value which was found out by generator (real max value)
#define DBC_DRIVER_MAX_DLC_VALUE 8U
#endif

// The limit is used for setting frame's data bytes
#define DBC_DRIVER_VALIDATE_DLC(msgDlc) (((msgDlc) <= (DBC_DRIVER_MAX_DLC_VALUE)) ? (msgDlc) : (DBC_DRIVER_MAX_DLC_VALUE))

// Initial byte value to be filles in data bytes of the frame before pack signals
// User can define its own custom value in driver-config file
#ifndef DBC_DRIVER_INITIAL_BYTE_VALUE
#define DBC_DRIVER_INITIAL_BYTE_VALUE 0U
#endif


// Broadcast der sobald 12V anliegen vom eBooster mit 100 Hz gesendet wird
// def @EBOOSTER_DATA_AND_FAULT CAN Message (107  0x6b)
#define EBOOSTER_DATA_AND_FAULT_IDE (0U)
#define EBOOSTER_DATA_AND_FAULT_DLC (8U)
#define EBOOSTER_DATA_AND_FAULT_CANID (0x6bU)
#define EBOOSTER_DATA_AND_FAULT_CYC (10U)
// signal: @actual_speed_ebooster_ro
#define DBC_DRIVER_actual_speed_ebooster_ro_CovFactor (100)
#define DBC_DRIVER_actual_speed_ebooster_ro_toS(x) ( (uint16_t) ((x) / (100)) )
#define DBC_DRIVER_actual_speed_ebooster_ro_fromS(x) ( ((x) * (100)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Wenn U>54 V =1 Wenn wieder unter 52 V = 0
  uint8_t overvoltage_48V : 1;               //      Bits= 1

  // Wenn U < 35 V = 1 Wenn wieder ueber 38 = 0
  uint8_t undervoltage_48V : 1;              //      Bits= 1

  // Vermutung, denn ist aktiv wenn hand auf turbo und str mung abreisst und drehzahl  ber 73'000 steigt
  uint8_t overspeed : 1;                     //      Bits= 1

  // 1 wenn eBooster nach warnung nicht gestoppt wurde und nun automatisch abschaltet (bleibt ca 11sek aktiv)
  uint8_t timeout_cause_off : 1;             //      Bits= 1

  uint8_t mecanical_blocked_ebooster : 1;    //      Bits= 1

  // Wenn id 0x06D empfangen wird: 0 sonst 1
  uint8_t status_control_signal : 1;         //      Bits= 1

  // Meldung das ansteuerung stoppen muss, ansonsten notaus (bleibt ca 11sek aktiv)
  uint8_t timout_max_use : 1;                //      Bits= 1

  // 1 wenn eBooster am Maximalstrom (konfigurierbar)
  uint8_t currentlimit_activ : 1;            //      Bits= 1

  // Beim Boot an bis Ansteuerung empfangen wird und < 0x16 ist 
  uint8_t Unbekannt_3 : 1;                   //      Bits= 1

  // eBooster wegen st rung deaktiviert, Reset mit Absenkung solldrehzahl 0 
  uint8_t error_auto_off : 1;                //      Bits= 1

  // UINT-16 Istwert Drehzahl
  uint16_t actual_speed_ebooster_ro;         //      Bits=10 Factor= 100             Unit:'min-1'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  uint32_t actual_speed_ebooster_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Stromaufnahme 48V
  uint8_t actual_current_ebooster;           //      Bits= 8 Unit:'A'

  // steigt bei ansteuerung an, mit heissluftf hn aber nicht, Wird mit modell berechnet (mtz Artikel)
  uint8_t thermal_dutty_ebooter;             //      Bits= 8

#else

  // Wenn U>54 V =1 Wenn wieder unter 52 V = 0
  uint8_t overvoltage_48V;                   //      Bits= 1

  // Wenn U < 35 V = 1 Wenn wieder ueber 38 = 0
  uint8_t undervoltage_48V;                  //      Bits= 1

  // Vermutung, denn ist aktiv wenn hand auf turbo und str mung abreisst und drehzahl  ber 73'000 steigt
  uint8_t overspeed;                         //      Bits= 1

  // 1 wenn eBooster nach warnung nicht gestoppt wurde und nun automatisch abschaltet (bleibt ca 11sek aktiv)
  uint8_t timeout_cause_off;                 //      Bits= 1

  uint8_t mecanical_blocked_ebooster;        //      Bits= 1

  // Wenn id 0x06D empfangen wird: 0 sonst 1
  uint8_t status_control_signal;             //      Bits= 1

  // Meldung das ansteuerung stoppen muss, ansonsten notaus (bleibt ca 11sek aktiv)
  uint8_t timout_max_use;                    //      Bits= 1

  // 1 wenn eBooster am Maximalstrom (konfigurierbar)
  uint8_t currentlimit_activ;                //      Bits= 1

  // Beim Boot an bis Ansteuerung empfangen wird und < 0x16 ist 
  uint8_t Unbekannt_3;                       //      Bits= 1

  // eBooster wegen st rung deaktiviert, Reset mit Absenkung solldrehzahl 0 
  uint8_t error_auto_off;                    //      Bits= 1

  // UINT-16 Istwert Drehzahl
  uint16_t actual_speed_ebooster_ro;         //      Bits=10 Factor= 100             Unit:'min-1'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  uint32_t actual_speed_ebooster_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Stromaufnahme 48V
  uint8_t actual_current_ebooster;           //      Bits= 8 Unit:'A'

  // steigt bei ansteuerung an, mit heissluftf hn aber nicht, Wird mit modell berechnet (mtz Artikel)
  uint8_t thermal_dutty_ebooter;             //      Bits= 8

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} EBOOSTER_DATA_AND_FAULT_t;

// muss min. mit 100 Hz gesendet weden
// 
// 
// def @VEH_TO_EBOOSTER_CONTROL CAN Message (109  0x6d)
#define VEH_TO_EBOOSTER_CONTROL_IDE (0U)
#define VEH_TO_EBOOSTER_CONTROL_DLC (8U)
#define VEH_TO_EBOOSTER_CONTROL_CANID (0x6dU)
#define VEH_TO_EBOOSTER_CONTROL_CYC (10U)
// signal: @target_speed_ebooster_ro
#define DBC_DRIVER_target_speed_ebooster_ro_CovFactor (100)
#define DBC_DRIVER_target_speed_ebooster_ro_toS(x) ( (uint16_t) ((x) / (100)) )
#define DBC_DRIVER_target_speed_ebooster_ro_fromS(x) ( ((x) * (100)) )
// signal: @collant_flow_ebooster_ro
#define DBC_DRIVER_collant_flow_ebooster_ro_CovFactor (0.1)
#define DBC_DRIVER_collant_flow_ebooster_ro_toS(x) ( (uint8_t) (((x) - (0.0)) / (0.1)) )
#define DBC_DRIVER_collant_flow_ebooster_ro_fromS(x) ( (((x) * (0.1)) + (0.0)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Hex Werte
  // 00 00 - 13 00 : Off (01 00, 02 00 : Arretiert) (03 00, 04 00 : Reset Error)
  // 14 00 - 3B 00 : Idle (3'000min-1)
  // 3B 00 - 20 03 : RPM (6'000 - 80'000min-1)
  // Muss zu beginn immer erst unter 14 00 sein f r freigabe
  uint16_t target_speed_ebooster_ro;         //      Bits=10 Factor= 100             Unit:'min-1'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  uint32_t target_speed_ebooster_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // sehr traeges Verhalten
  uint8_t Unbekannt_1;                       //      Bits= 8

  // Sinkt bei motordrehzahl
  uint8_t Unbekannt_2;                       //      Bits= 8

  uint8_t collant_flow_ebooster_ro;          //      Bits= 8 Factor= 0.1             Unit:'L/min'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t collant_flow_ebooster_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Dezimalwerte
  // < 20A = 0 min-1
  // 20A = 40'000
  // 30A = 45'500
  // 40A = 50'500
  // 50A = 54'500 min-1
  // 60A = 58'000 min-1
  // 70A = 61'000 min-1
  // 85A = 64'000 min-1
  // 100A = 68'500 min-1
  // 110A = 69'000 min-1
  // 120A = 69'300 min-1
  // 130A = 69'300 min-1
  uint8_t max_current_48V;                   //      Bits= 8 Unit:'A'

#else

  // Hex Werte
  // 00 00 - 13 00 : Off (01 00, 02 00 : Arretiert) (03 00, 04 00 : Reset Error)
  // 14 00 - 3B 00 : Idle (3'000min-1)
  // 3B 00 - 20 03 : RPM (6'000 - 80'000min-1)
  // Muss zu beginn immer erst unter 14 00 sein f r freigabe
  uint16_t target_speed_ebooster_ro;         //      Bits=10 Factor= 100             Unit:'min-1'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  uint32_t target_speed_ebooster_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // sehr traeges Verhalten
  uint8_t Unbekannt_1;                       //      Bits= 8

  // Sinkt bei motordrehzahl
  uint8_t Unbekannt_2;                       //      Bits= 8

  uint8_t collant_flow_ebooster_ro;          //      Bits= 8 Factor= 0.1             Unit:'L/min'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t collant_flow_ebooster_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Dezimalwerte
  // < 20A = 0 min-1
  // 20A = 40'000
  // 30A = 45'500
  // 40A = 50'500
  // 50A = 54'500 min-1
  // 60A = 58'000 min-1
  // 70A = 61'000 min-1
  // 85A = 64'000 min-1
  // 100A = 68'500 min-1
  // 110A = 69'000 min-1
  // 120A = 69'300 min-1
  // 130A = 69'300 min-1
  uint8_t max_current_48V;                   //      Bits= 8 Unit:'A'

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_TO_EBOOSTER_CONTROL_t;

// Broadcast der sobald 12V anliegen vom eBooster mit 10 Hz gesendet wird
// def @EBOOSTER_GENERAL_DATA CAN Message (379  0x17b)
#define EBOOSTER_GENERAL_DATA_IDE (0U)
#define EBOOSTER_GENERAL_DATA_DLC (8U)
#define EBOOSTER_GENERAL_DATA_CANID (0x17bU)
#define EBOOSTER_GENERAL_DATA_CYC (100U)
// signal: @actual_temperature_ebooster_ro
#define DBC_DRIVER_actual_temperature_ebooster_ro_CovFactor (0.555)
#define DBC_DRIVER_actual_temperature_ebooster_ro_toS(x) ( (uint8_t) (((x) - (-17.777777778)) / (0.555)) )
#define DBC_DRIVER_actual_temperature_ebooster_ro_fromS(x) ( (((x) * (0.555)) + (-17.777777778)) )
// signal: @actual_supply_voltage_48V_ro
#define DBC_DRIVER_actual_supply_voltage_48V_ro_CovFactor (0.251256281)
#define DBC_DRIVER_actual_supply_voltage_48V_ro_toS(x) ( (uint8_t) (((x) - (0.0)) / (0.251256281)) )
#define DBC_DRIVER_actual_supply_voltage_48V_ro_fromS(x) ( (((x) * (0.251256281)) + (0.0)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // zaehlt rauf bis 1F FF und startet wieder bei 00 00
  uint16_t ebooster_tx_counter;                 //      Bits=16

  // Muss noch kalibriert werden (Sieht nach Fahrenheit aus)
  uint8_t actual_temperature_ebooster_ro;       //      Bits= 8 Offset= -17.777777778      Factor= 0.555           Unit:' C'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t actual_temperature_ebooster_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Mit Netzteil kalibiert
  uint8_t actual_supply_voltage_48V_ro;         //      Bits= 8 Factor= 0.251256281     Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t actual_supply_voltage_48V_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#else

  // zaehlt rauf bis 1F FF und startet wieder bei 00 00
  uint16_t ebooster_tx_counter;                 //      Bits=16

  // Muss noch kalibriert werden (Sieht nach Fahrenheit aus)
  uint8_t actual_temperature_ebooster_ro;       //      Bits= 8 Offset= -17.777777778      Factor= 0.555           Unit:' C'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t actual_temperature_ebooster_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Mit Netzteil kalibiert
  uint8_t actual_supply_voltage_48V_ro;         //      Bits= 8 Factor= 0.251256281     Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t actual_supply_voltage_48V_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} EBOOSTER_GENERAL_DATA_t;

// def @VEH_MSG_TO_BMS CAN Message (1280 0x500)
#define VEH_MSG_TO_BMS_IDE (0U)
#define VEH_MSG_TO_BMS_DLC (2U)
#define VEH_MSG_TO_BMS_CANID (0x500U)
#define VEH_MSG_TO_BMS_CYC (50U)

// Value tables for @veh_cb_cmd_e signal

#ifndef veh_cb_cmd_e_VEH_MSG_TO_BMS_VEH_CB_CMD__CLOSE
#define veh_cb_cmd_e_VEH_MSG_TO_BMS_VEH_CB_CMD__CLOSE (1)
#endif

#ifndef veh_cb_cmd_e_VEH_MSG_TO_BMS_VEH_CB_CMD__OPEN
#define veh_cb_cmd_e_VEH_MSG_TO_BMS_VEH_CB_CMD__OPEN (0)
#endif


typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Circuit Breaker command from the Vehicle/Tester.
  //  1 : "VEH_CB_CMD__CLOSE"
  //  0 : "VEH_CB_CMD__OPEN"
  uint8_t veh_cb_cmd_e : 1;                  //      Bits= 1

  uint8_t veh_fan_dutycycle_cmd;             //      Bits= 8

#else

  // Circuit Breaker command from the Vehicle/Tester.
  //  1 : "VEH_CB_CMD__CLOSE"
  //  0 : "VEH_CB_CMD__OPEN"
  uint8_t veh_cb_cmd_e;                      //      Bits= 1

  uint8_t veh_fan_dutycycle_cmd;             //      Bits= 8

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_MSG_TO_BMS_t;

// Crash signal.
// def @VEH_CRASH CAN Message (1281 0x501)
#define VEH_CRASH_IDE (0U)
#define VEH_CRASH_DLC (1U)
#define VEH_CRASH_CANID (0x501U)
#define VEH_CRASH_CYC (50U)

// Value tables for @veh_crash_cmd_b signal

#ifndef veh_crash_cmd_b_VEH_CRASH_BOOL__TRUE
#define veh_crash_cmd_b_VEH_CRASH_BOOL__TRUE (1)
#endif

#ifndef veh_crash_cmd_b_VEH_CRASH_BOOL__FALSE
#define veh_crash_cmd_b_VEH_CRASH_BOOL__FALSE (0)
#endif


typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Crash sigjnal command from the vehicle/tester.
  //  1 : "BOOL__TRUE"
  //  0 : "BOOL__FALSE"
  uint8_t veh_crash_cmd_b : 1;               //      Bits= 1

#else

  // Crash sigjnal command from the vehicle/tester.
  //  1 : "BOOL__TRUE"
  //  0 : "BOOL__FALSE"
  uint8_t veh_crash_cmd_b;                   //      Bits= 1

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_CRASH_t;

// def @VEH_BMS_PACK_STATUS_1 CAN Message (1536 0x600)
#define VEH_BMS_PACK_STATUS_1_IDE (0U)
#define VEH_BMS_PACK_STATUS_1_DLC (7U)
#define VEH_BMS_PACK_STATUS_1_CANID (0x600U)
#define VEH_BMS_PACK_STATUS_1_CYC (50U)

// Value tables for @veh_bms_db_cb_state_e signal

#ifndef veh_bms_db_cb_state_e_VEH_BMS_PACK_STATUS_1_CBACT_STATE__FAULT
#define veh_bms_db_cb_state_e_VEH_BMS_PACK_STATUS_1_CBACT_STATE__FAULT (2)
#endif

#ifndef veh_bms_db_cb_state_e_VEH_BMS_PACK_STATUS_1_CBACT_STATE__CLOSED
#define veh_bms_db_cb_state_e_VEH_BMS_PACK_STATUS_1_CBACT_STATE__CLOSED (1)
#endif

#ifndef veh_bms_db_cb_state_e_VEH_BMS_PACK_STATUS_1_CBACT_STATE__OPEN
#define veh_bms_db_cb_state_e_VEH_BMS_PACK_STATUS_1_CBACT_STATE__OPEN (0)
#endif


typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Indicates the current state of the Circuit Breaker
  //  2 : "CBACT_STATE__FAULT"
  //  1 : "CBACT_STATE__CLOSED"
  //  0 : "CBACT_STATE__OPEN"
  uint8_t veh_bms_db_cb_state_e : 3;              //      Bits= 3

  // Message integrity counter.
  uint8_t veh_bms_db_rolling_counter : 4;         //      Bits= 4

  uint8_t fan_status : 2;                         //      Bits= 2

  // Soft EPO status (Opens the relay after 5 sec)
  uint8_t soft_epo_status : 1;                    //      Bits= 1

  // Hard EPO status (Opens the relay immediately)
  uint8_t hard_epo_status : 1;                    //      Bits= 1

  // Indicates if the conditions for cell balancing are active.
  uint8_t veh_bms_db_cbal_en_b : 1;               //      Bits= 1

  int8_t veh_bms_db_arb_cmd_e : 1;                //  [-] Bits= 1

  // Indicates that the Circuit Breaker has failed and is stuck open.
  uint8_t veh_bms_db_cb_err_stuck_open_b : 1;     //      Bits= 1

  // Indicates that the Circuit Breaker has failed and is stuck closed.
  uint8_t veh_bms_db_cb_err_stuck_closed_b : 1;   //      Bits= 1

  uint8_t derating_status : 1;                    //      Bits= 1

  uint8_t hvbatt_total_capacity : 3;              //      Bits= 3

  // Indication that a charging over-current condition exists.
  uint8_t veh_bms_db_ocp_maturing_actv_b : 1;     //      Bits= 1

  // Indicates if over-current protection is active.
  uint8_t veh_bms_db_ocp_actv_b : 1;              //      Bits= 1

  // Indication that a pack over-temperature condition exists.
  uint8_t veh_bms_db_otp_maturing_actv_b : 1;     //      Bits= 1

  // Indicates if pack over-temperature protection is active.
  uint8_t veh_bms_db_otp_actv_b : 1;              //      Bits= 1

  // Indication that a cell over-voltage condition exists.
  uint8_t veh_bms_db_ovp_maturing_actv_b : 1;     //      Bits= 1

  // Indicates if cell-level over-voltage protection is active.
  uint8_t veh_bms_db_ovp_actv_b : 1;              //      Bits= 1

  // Indication that a cell under-voltage condition exists.
  uint8_t veh_bms_db_uvp_maturing_actv_b : 1;     //      Bits= 1

  // Indicates if cell-level under-voltage protection is active.
  uint8_t veh_bms_db_uvp_actv_b : 1;              //      Bits= 1

  uint8_t veh_bms_db_soh;                         //      Bits= 8

  uint8_t veh_bms_db_dtc_otp_actv_b : 1;          //      Bits= 1

  uint8_t veh_bms_db_dtc_cb_weld_actv_b : 1;      //      Bits= 1

  uint8_t veh_bms_dtc_equalize_fail_actv_b : 1;   //      Bits= 1

  uint8_t veh_bms_db_dtc_ovp_actv_b : 1;          //      Bits= 1

  uint8_t veh_bms_db_dtc_uvp_actv_b : 1;          //      Bits= 1

  uint8_t veh_bms_dtc_cb_stuck_open_actv_b : 1;   //      Bits= 1

  uint8_t veh_bms_db_dtc_cb_uncmnd_open_b : 1;    //      Bits= 1

  uint8_t veh_bms_db_dtc_cb_failed_open_b : 1;    //      Bits= 1

#else

  // Indicates the current state of the Circuit Breaker
  //  2 : "CBACT_STATE__FAULT"
  //  1 : "CBACT_STATE__CLOSED"
  //  0 : "CBACT_STATE__OPEN"
  uint8_t veh_bms_db_cb_state_e;                  //      Bits= 3

  // Message integrity counter.
  uint8_t veh_bms_db_rolling_counter;             //      Bits= 4

  uint8_t fan_status;                             //      Bits= 2

  // Soft EPO status (Opens the relay after 5 sec)
  uint8_t soft_epo_status;                        //      Bits= 1

  // Hard EPO status (Opens the relay immediately)
  uint8_t hard_epo_status;                        //      Bits= 1

  // Indicates if the conditions for cell balancing are active.
  uint8_t veh_bms_db_cbal_en_b;                   //      Bits= 1

  int8_t veh_bms_db_arb_cmd_e;                    //  [-] Bits= 1

  // Indicates that the Circuit Breaker has failed and is stuck open.
  uint8_t veh_bms_db_cb_err_stuck_open_b;         //      Bits= 1

  // Indicates that the Circuit Breaker has failed and is stuck closed.
  uint8_t veh_bms_db_cb_err_stuck_closed_b;       //      Bits= 1

  uint8_t derating_status;                        //      Bits= 1

  uint8_t hvbatt_total_capacity;                  //      Bits= 3

  // Indication that a charging over-current condition exists.
  uint8_t veh_bms_db_ocp_maturing_actv_b;         //      Bits= 1

  // Indicates if over-current protection is active.
  uint8_t veh_bms_db_ocp_actv_b;                  //      Bits= 1

  // Indication that a pack over-temperature condition exists.
  uint8_t veh_bms_db_otp_maturing_actv_b;         //      Bits= 1

  // Indicates if pack over-temperature protection is active.
  uint8_t veh_bms_db_otp_actv_b;                  //      Bits= 1

  // Indication that a cell over-voltage condition exists.
  uint8_t veh_bms_db_ovp_maturing_actv_b;         //      Bits= 1

  // Indicates if cell-level over-voltage protection is active.
  uint8_t veh_bms_db_ovp_actv_b;                  //      Bits= 1

  // Indication that a cell under-voltage condition exists.
  uint8_t veh_bms_db_uvp_maturing_actv_b;         //      Bits= 1

  // Indicates if cell-level under-voltage protection is active.
  uint8_t veh_bms_db_uvp_actv_b;                  //      Bits= 1

  uint8_t veh_bms_db_soh;                         //      Bits= 8

  uint8_t veh_bms_db_dtc_otp_actv_b;              //      Bits= 1

  uint8_t veh_bms_db_dtc_cb_weld_actv_b;          //      Bits= 1

  uint8_t veh_bms_dtc_equalize_fail_actv_b;       //      Bits= 1

  uint8_t veh_bms_db_dtc_ovp_actv_b;              //      Bits= 1

  uint8_t veh_bms_db_dtc_uvp_actv_b;              //      Bits= 1

  uint8_t veh_bms_dtc_cb_stuck_open_actv_b;       //      Bits= 1

  uint8_t veh_bms_db_dtc_cb_uncmnd_open_b;        //      Bits= 1

  uint8_t veh_bms_db_dtc_cb_failed_open_b;        //      Bits= 1

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_PACK_STATUS_1_t;

// def @VEH_BMS_PACK_STATUS_2 CAN Message (1537 0x601)
#define VEH_BMS_PACK_STATUS_2_IDE (0U)
#define VEH_BMS_PACK_STATUS_2_DLC (7U)
#define VEH_BMS_PACK_STATUS_2_CANID (0x601U)
#define VEH_BMS_PACK_STATUS_2_CYC (1000U)

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Number of Circuit Breaker operations under load.
  uint32_t veh_bms_cb_loaded_switched_Cnt;      //      Bits=18

  // Remaining lifetime of the Circuit Breaker
  uint8_t veh_bms_cb_lifetime_remain_Pct;       //      Bits= 8

  // Software version, build identifier.
  uint8_t veh_bms_db_sw_version_build;          //      Bits= 8

  // Software version, minor identifier.
  uint8_t veh_bms_db_sw_version_minor;          //      Bits= 8

  // Software version, major identifier.
  uint8_t veh_bms_db_sw_version_major;          //      Bits= 8

#else

  // Number of Circuit Breaker operations under load.
  uint32_t veh_bms_cb_loaded_switched_Cnt;      //      Bits=18

  // Remaining lifetime of the Circuit Breaker
  uint8_t veh_bms_cb_lifetime_remain_Pct;       //      Bits= 8

  // Software version, build identifier.
  uint8_t veh_bms_db_sw_version_build;          //      Bits= 8

  // Software version, minor identifier.
  uint8_t veh_bms_db_sw_version_minor;          //      Bits= 8

  // Software version, major identifier.
  uint8_t veh_bms_db_sw_version_major;          //      Bits= 8

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_PACK_STATUS_2_t;

// def @VEH_BMS_CELL_DATA_1 CAN Message (1552 0x610)
#define VEH_BMS_CELL_DATA_1_IDE (0U)
#define VEH_BMS_CELL_DATA_1_DLC (8U)
#define VEH_BMS_CELL_DATA_1_CANID (0x610U)
#define VEH_BMS_CELL_DATA_1_CYC (50U)
// signal: @veh_bms_db_cell_01_U_ro
#define DBC_DRIVER_veh_bms_db_cell_01_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_01_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_01_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_02_U_ro
#define DBC_DRIVER_veh_bms_db_cell_02_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_02_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_02_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_03_U_ro
#define DBC_DRIVER_veh_bms_db_cell_03_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_03_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_03_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_04_U_ro
#define DBC_DRIVER_veh_bms_db_cell_04_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_04_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_04_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Cell 1 voltage
  uint16_t veh_bms_db_cell_01_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_01_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 1 balance command.
  uint8_t veh_bms_db_cell_01_bal_actv_b : 1;   //      Bits= 1

  // Cell 2 voltage
  uint16_t veh_bms_db_cell_02_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_02_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 2 balance command.
  uint8_t veh_bms_db_cell_02_bal_actv_b : 1;   //      Bits= 1

  // Cell 3 voltage
  uint16_t veh_bms_db_cell_03_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_03_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 3 balance command.
  uint8_t veh_bms_db_cell_03_bal_actv_b : 1;   //      Bits= 1

  // Cell 4 voltage
  uint16_t veh_bms_db_cell_04_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_04_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 4 balance command.
  uint8_t veh_bms_db_cell_04_bal_actv_b : 1;   //      Bits= 1

#else

  // Cell 1 voltage
  uint16_t veh_bms_db_cell_01_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_01_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 1 balance command.
  uint8_t veh_bms_db_cell_01_bal_actv_b;       //      Bits= 1

  // Cell 2 voltage
  uint16_t veh_bms_db_cell_02_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_02_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 2 balance command.
  uint8_t veh_bms_db_cell_02_bal_actv_b;       //      Bits= 1

  // Cell 3 voltage
  uint16_t veh_bms_db_cell_03_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_03_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 3 balance command.
  uint8_t veh_bms_db_cell_03_bal_actv_b;       //      Bits= 1

  // Cell 4 voltage
  uint16_t veh_bms_db_cell_04_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_04_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 4 balance command.
  uint8_t veh_bms_db_cell_04_bal_actv_b;       //      Bits= 1

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_CELL_DATA_1_t;

// def @VEH_BMS_CELL_DATA_2 CAN Message (1553 0x611)
#define VEH_BMS_CELL_DATA_2_IDE (0U)
#define VEH_BMS_CELL_DATA_2_DLC (8U)
#define VEH_BMS_CELL_DATA_2_CANID (0x611U)
#define VEH_BMS_CELL_DATA_2_CYC (50U)
// signal: @veh_bms_db_cell_05_U_ro
#define DBC_DRIVER_veh_bms_db_cell_05_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_05_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_05_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_06_U_ro
#define DBC_DRIVER_veh_bms_db_cell_06_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_06_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_06_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_07_U_ro
#define DBC_DRIVER_veh_bms_db_cell_07_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_07_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_07_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_08_U_ro
#define DBC_DRIVER_veh_bms_db_cell_08_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_08_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_08_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Cell 5 voltage
  uint16_t veh_bms_db_cell_05_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_05_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 5 balance command.
  uint8_t veh_bms_db_cell_05_bal_actv_b : 1;   //      Bits= 1

  // Cell 6 voltage
  uint16_t veh_bms_db_cell_06_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_06_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 6 balance command.
  uint8_t veh_bms_db_cell_06_bal_actv_b : 1;   //      Bits= 1

  // Cell 7 voltage
  uint16_t veh_bms_db_cell_07_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_07_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 7 balance command.
  uint8_t veh_bms_db_cell_07_bal_actv_b : 1;   //      Bits= 1

  // Cell 8 voltage
  uint16_t veh_bms_db_cell_08_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_08_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 8 balance command.
  uint8_t veh_bms_db_cell_08_bal_actv_b : 1;   //      Bits= 1

#else

  // Cell 5 voltage
  uint16_t veh_bms_db_cell_05_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_05_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 5 balance command.
  uint8_t veh_bms_db_cell_05_bal_actv_b;       //      Bits= 1

  // Cell 6 voltage
  uint16_t veh_bms_db_cell_06_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_06_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 6 balance command.
  uint8_t veh_bms_db_cell_06_bal_actv_b;       //      Bits= 1

  // Cell 7 voltage
  uint16_t veh_bms_db_cell_07_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_07_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 7 balance command.
  uint8_t veh_bms_db_cell_07_bal_actv_b;       //      Bits= 1

  // Cell 8 voltage
  uint16_t veh_bms_db_cell_08_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_08_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 8 balance command.
  uint8_t veh_bms_db_cell_08_bal_actv_b;       //      Bits= 1

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_CELL_DATA_2_t;

// def @VEH_BMS_CELL_DATA_3 CAN Message (1554 0x612)
#define VEH_BMS_CELL_DATA_3_IDE (0U)
#define VEH_BMS_CELL_DATA_3_DLC (8U)
#define VEH_BMS_CELL_DATA_3_CANID (0x612U)
#define VEH_BMS_CELL_DATA_3_CYC (50U)
// signal: @veh_bms_db_cell_09_U_ro
#define DBC_DRIVER_veh_bms_db_cell_09_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_09_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_09_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_10_U_ro
#define DBC_DRIVER_veh_bms_db_cell_10_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_10_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_10_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_11_U_ro
#define DBC_DRIVER_veh_bms_db_cell_11_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_11_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_11_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_12_U_ro
#define DBC_DRIVER_veh_bms_db_cell_12_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_12_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_12_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Cell 9 voltage
  uint16_t veh_bms_db_cell_09_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_09_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 9 balance command.
  uint8_t veh_bms_db_cell_09_bal_actv_b : 1;   //      Bits= 1

  // Cell 10 voltage
  uint16_t veh_bms_db_cell_10_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_10_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 10 balance command.
  uint8_t veh_bms_db_cell_10_bal_actv_b : 1;   //      Bits= 1

  // Cell 11 voltage
  uint16_t veh_bms_db_cell_11_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_11_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 11 balance command.
  uint8_t veh_bms_db_cell_11_bal_actv_b : 1;   //      Bits= 1

  // Cell 12 voltage
  uint16_t veh_bms_db_cell_12_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_12_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 12 balance command.
  uint8_t veh_bms_db_cell_12_bal_actv_b : 1;   //      Bits= 1

#else

  // Cell 9 voltage
  uint16_t veh_bms_db_cell_09_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_09_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 9 balance command.
  uint8_t veh_bms_db_cell_09_bal_actv_b;       //      Bits= 1

  // Cell 10 voltage
  uint16_t veh_bms_db_cell_10_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_10_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 10 balance command.
  uint8_t veh_bms_db_cell_10_bal_actv_b;       //      Bits= 1

  // Cell 11 voltage
  uint16_t veh_bms_db_cell_11_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_11_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 11 balance command.
  uint8_t veh_bms_db_cell_11_bal_actv_b;       //      Bits= 1

  // Cell 12 voltage
  uint16_t veh_bms_db_cell_12_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_12_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 12 balance command.
  uint8_t veh_bms_db_cell_12_bal_actv_b;       //      Bits= 1

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_CELL_DATA_3_t;

// def @VEH_BMS_CELL_DATA_4 CAN Message (1555 0x613)
#define VEH_BMS_CELL_DATA_4_IDE (0U)
#define VEH_BMS_CELL_DATA_4_DLC (8U)
#define VEH_BMS_CELL_DATA_4_CANID (0x613U)
#define VEH_BMS_CELL_DATA_4_CYC (50U)
// signal: @veh_bms_db_cell_13_U_ro
#define DBC_DRIVER_veh_bms_db_cell_13_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_13_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_13_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_cell_14_U_ro
#define DBC_DRIVER_veh_bms_db_cell_14_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_cell_14_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_cell_14_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_max_cell_U_ro
#define DBC_DRIVER_veh_bms_db_max_cell_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_max_cell_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_max_cell_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_min_cell_U_ro
#define DBC_DRIVER_veh_bms_db_min_cell_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_min_cell_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_min_cell_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Cell 13 voltage
  uint16_t veh_bms_db_cell_13_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_13_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 13 balance command.
  uint8_t veh_bms_db_cell_13_bal_actv_b : 1;   //      Bits= 1

  // Cell 14 voltage
  uint16_t veh_bms_db_cell_14_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_14_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 14 balance command.
  uint8_t veh_bms_db_cell_14_bal_actv_b : 1;   //      Bits= 1

  // Max cell voltage.
  uint16_t veh_bms_db_max_cell_U_ro;           //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_max_cell_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Min cell voltage.
  uint16_t veh_bms_db_min_cell_U_ro;           //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_min_cell_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#else

  // Cell 13 voltage
  uint16_t veh_bms_db_cell_13_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_13_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 13 balance command.
  uint8_t veh_bms_db_cell_13_bal_actv_b;       //      Bits= 1

  // Cell 14 voltage
  uint16_t veh_bms_db_cell_14_U_ro;            //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_cell_14_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Cell 14 balance command.
  uint8_t veh_bms_db_cell_14_bal_actv_b;       //      Bits= 1

  // Max cell voltage.
  uint16_t veh_bms_db_max_cell_U_ro;           //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_max_cell_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Min cell voltage.
  uint16_t veh_bms_db_min_cell_U_ro;           //      Bits=13 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_min_cell_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_CELL_DATA_4_t;

// def @VEH_BMS_PACK_LIMITS_1 CAN Message (1568 0x620)
#define VEH_BMS_PACK_LIMITS_1_IDE (0U)
#define VEH_BMS_PACK_LIMITS_1_DLC (6U)
#define VEH_BMS_PACK_LIMITS_1_CANID (0x620U)
// signal: @veh_bms_db_avail_chrg_1s_PKW_ro
#define DBC_DRIVER_veh_bms_db_avail_chrg_1s_PKW_ro_CovFactor (0.01)
#define DBC_DRIVER_veh_bms_db_avail_chrg_1s_PKW_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define DBC_DRIVER_veh_bms_db_avail_chrg_1s_PKW_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @veh_bms_db_avail_dschrg_1s_IA_ro
#define DBC_DRIVER_veh_bms_db_avail_dschrg_1s_IA_ro_CovFactor (1)
#define DBC_DRIVER_veh_bms_db_avail_dschrg_1s_IA_ro_toS(x) ( (uint16_t) ((x) - (-1023)) )
#define DBC_DRIVER_veh_bms_db_avail_dschrg_1s_IA_ro_fromS(x) ( ((x) + (-1023)) )
// signal: @veh_bms_db_avail_dschrg_1s_PKW_ro
#define DBC_DRIVER_veh_bms_db_avail_dschrg_1s_PKW_ro_CovFactor (0.01)
#define DBC_DRIVER_veh_bms_db_avail_dschrg_1s_PKW_ro_toS(x) ( (uint16_t) (((x) - (-40.95)) / (0.01)) )
#define DBC_DRIVER_veh_bms_db_avail_dschrg_1s_PKW_ro_fromS(x) ( (((x) * (0.01)) + (-40.95)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Maximum charge current available for the next 1 second.
  uint16_t veh_bms_db_avail_chrg_1s_IA;            //      Bits=10 Unit:'A'

  // Maximum charge power available for the next 1 second.
  uint16_t veh_bms_db_avail_chrg_1s_PKW_ro;        //      Bits=12 Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_chrg_1s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge current available for the next 1 second.
  uint16_t veh_bms_db_avail_dschrg_1s_IA_ro;       //      Bits=10 Offset= -1023              Unit:'A'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  int16_t veh_bms_db_avail_dschrg_1s_IA_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge power available for the next 1 second.
  uint16_t veh_bms_db_avail_dschrg_1s_PKW_ro;      //      Bits=12 Offset= -40.95             Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_dschrg_1s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#else

  // Maximum charge current available for the next 1 second.
  uint16_t veh_bms_db_avail_chrg_1s_IA;            //      Bits=10 Unit:'A'

  // Maximum charge power available for the next 1 second.
  uint16_t veh_bms_db_avail_chrg_1s_PKW_ro;        //      Bits=12 Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_chrg_1s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge current available for the next 1 second.
  uint16_t veh_bms_db_avail_dschrg_1s_IA_ro;       //      Bits=10 Offset= -1023              Unit:'A'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  int16_t veh_bms_db_avail_dschrg_1s_IA_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge power available for the next 1 second.
  uint16_t veh_bms_db_avail_dschrg_1s_PKW_ro;      //      Bits=12 Offset= -40.95             Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_dschrg_1s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_PACK_LIMITS_1_t;

// def @VEH_BMS_PACK_LIMITS_2 CAN Message (1569 0x621)
#define VEH_BMS_PACK_LIMITS_2_IDE (0U)
#define VEH_BMS_PACK_LIMITS_2_DLC (6U)
#define VEH_BMS_PACK_LIMITS_2_CANID (0x621U)
#define VEH_BMS_PACK_LIMITS_2_CYC (1000U)
// signal: @veh_bms_db_avail_chrg_10s_PKW_ro
#define DBC_DRIVER_veh_bms_db_avail_chrg_10s_PKW_ro_CovFactor (0.01)
#define DBC_DRIVER_veh_bms_db_avail_chrg_10s_PKW_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define DBC_DRIVER_veh_bms_db_avail_chrg_10s_PKW_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @veh_bms_db_avail_dschrg_10s_IA_ro
#define DBC_DRIVER_veh_bms_db_avail_dschrg_10s_IA_ro_CovFactor (1)
#define DBC_DRIVER_veh_bms_db_avail_dschrg_10s_IA_ro_toS(x) ( (uint16_t) ((x) - (-1023)) )
#define DBC_DRIVER_veh_bms_db_avail_dschrg_10s_IA_ro_fromS(x) ( ((x) + (-1023)) )
// signal: @veh_bms_db_avail_dschrg_10s_PKW_ro
#define DBC_DRIVER_veh_bms_db_avail_dschrg_10s_PKW_ro_CovFactor (0.01)
#define DBC_DRIVER_veh_bms_db_avail_dschrg_10s_PKW_ro_toS(x) ( (uint16_t) (((x) - (-40.95)) / (0.01)) )
#define DBC_DRIVER_veh_bms_db_avail_dschrg_10s_PKW_ro_fromS(x) ( (((x) * (0.01)) + (-40.95)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Maximum charge current available for the next 10 seconds.
  uint16_t veh_bms_db_avail_chrg_10s_IA;            //      Bits=10 Unit:'A'

  // Maximum charge power available for the next 10 seconds
  uint16_t veh_bms_db_avail_chrg_10s_PKW_ro;        //      Bits=12 Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_chrg_10s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge current available for the next 10 seconds.
  uint16_t veh_bms_db_avail_dschrg_10s_IA_ro;       //      Bits=10 Offset= -1023              Unit:'A'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  int16_t veh_bms_db_avail_dschrg_10s_IA_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge power available for the next 10 seconds.
  uint16_t veh_bms_db_avail_dschrg_10s_PKW_ro;      //      Bits=12 Offset= -40.95             Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_dschrg_10s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#else

  // Maximum charge current available for the next 10 seconds.
  uint16_t veh_bms_db_avail_chrg_10s_IA;            //      Bits=10 Unit:'A'

  // Maximum charge power available for the next 10 seconds
  uint16_t veh_bms_db_avail_chrg_10s_PKW_ro;        //      Bits=12 Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_chrg_10s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge current available for the next 10 seconds.
  uint16_t veh_bms_db_avail_dschrg_10s_IA_ro;       //      Bits=10 Offset= -1023              Unit:'A'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  int16_t veh_bms_db_avail_dschrg_10s_IA_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge power available for the next 10 seconds.
  uint16_t veh_bms_db_avail_dschrg_10s_PKW_ro;      //      Bits=12 Offset= -40.95             Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_dschrg_10s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_PACK_LIMITS_2_t;

// def @VEH_BMS_PACK_LIMITS_3 CAN Message (1570 0x622)
#define VEH_BMS_PACK_LIMITS_3_IDE (0U)
#define VEH_BMS_PACK_LIMITS_3_DLC (6U)
#define VEH_BMS_PACK_LIMITS_3_CANID (0x622U)
#define VEH_BMS_PACK_LIMITS_3_CYC (1000U)
// signal: @veh_bms_db_avail_chrg_60s_PKW_ro
#define DBC_DRIVER_veh_bms_db_avail_chrg_60s_PKW_ro_CovFactor (0.01)
#define DBC_DRIVER_veh_bms_db_avail_chrg_60s_PKW_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.01)) )
#define DBC_DRIVER_veh_bms_db_avail_chrg_60s_PKW_ro_fromS(x) ( (((x) * (0.01)) + (0.0)) )
// signal: @veh_bms_db_avail_dschrg_60s_IA_ro
#define DBC_DRIVER_veh_bms_db_avail_dschrg_60s_IA_ro_CovFactor (1)
#define DBC_DRIVER_veh_bms_db_avail_dschrg_60s_IA_ro_toS(x) ( (uint16_t) ((x) - (-1023)) )
#define DBC_DRIVER_veh_bms_db_avail_dschrg_60s_IA_ro_fromS(x) ( ((x) + (-1023)) )
// signal: @veh_bms_db_avail_dschrg_60s_PKW_ro
#define DBC_DRIVER_veh_bms_db_avail_dschrg_60s_PKW_ro_CovFactor (0.01)
#define DBC_DRIVER_veh_bms_db_avail_dschrg_60s_PKW_ro_toS(x) ( (uint16_t) (((x) - (-40.95)) / (0.01)) )
#define DBC_DRIVER_veh_bms_db_avail_dschrg_60s_PKW_ro_fromS(x) ( (((x) * (0.01)) + (-40.95)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Maximum charge current available for the next 60 seconds.
  uint16_t veh_bms_db_avail_chrg_60s_IA;            //      Bits=10 Unit:'A'

  // Maximum charge power available for the next 60 second.
  uint16_t veh_bms_db_avail_chrg_60s_PKW_ro;        //      Bits=12 Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_chrg_60s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge current available for the next 60 seconds.
  uint16_t veh_bms_db_avail_dschrg_60s_IA_ro;       //      Bits=10 Offset= -1023              Unit:'A'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  int16_t veh_bms_db_avail_dschrg_60s_IA_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge power available for the next 60 seconds.
  uint16_t veh_bms_db_avail_dschrg_60s_PKW_ro;      //      Bits=12 Offset= -40.95             Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_dschrg_60s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#else

  // Maximum charge current available for the next 60 seconds.
  uint16_t veh_bms_db_avail_chrg_60s_IA;            //      Bits=10 Unit:'A'

  // Maximum charge power available for the next 60 second.
  uint16_t veh_bms_db_avail_chrg_60s_PKW_ro;        //      Bits=12 Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_chrg_60s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge current available for the next 60 seconds.
  uint16_t veh_bms_db_avail_dschrg_60s_IA_ro;       //      Bits=10 Offset= -1023              Unit:'A'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  int16_t veh_bms_db_avail_dschrg_60s_IA_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Maximum discharge power available for the next 60 seconds.
  uint16_t veh_bms_db_avail_dschrg_60s_PKW_ro;      //      Bits=12 Offset= -40.95             Factor= 0.01            Unit:'KW'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_avail_dschrg_60s_PKW_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_PACK_LIMITS_3_t;

// def @VEH_BMS_PACK_DATA_1 CAN Message (1584 0x630)
#define VEH_BMS_PACK_DATA_1_IDE (0U)
#define VEH_BMS_PACK_DATA_1_DLC (8U)
#define VEH_BMS_PACK_DATA_1_CANID (0x630U)
#define VEH_BMS_PACK_DATA_1_CYC (50U)
// signal: @veh_bms_db_stack_U_ro
#define DBC_DRIVER_veh_bms_db_stack_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_stack_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_stack_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_term_U_ro
#define DBC_DRIVER_veh_bms_db_term_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_term_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_term_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )
// signal: @veh_bms_db_inst_I_ro
#define DBC_DRIVER_veh_bms_db_inst_I_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_inst_I_ro_toS(x) ( (int32_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_inst_I_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Potential between cell 14 positive and cell 1 negative.
  uint16_t veh_bms_db_stack_U_ro;            //      Bits=16 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_stack_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Potential between B_POS and B_NEG.
  uint16_t veh_bms_db_term_U_ro;             //      Bits=16 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_term_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Instantaneous current
  int32_t veh_bms_db_inst_I_ro;              //  [-] Bits=32 Factor= 0.001           Unit:'A'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_inst_I_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#else

  // Potential between cell 14 positive and cell 1 negative.
  uint16_t veh_bms_db_stack_U_ro;            //      Bits=16 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_stack_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Potential between B_POS and B_NEG.
  uint16_t veh_bms_db_term_U_ro;             //      Bits=16 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_term_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Instantaneous current
  int32_t veh_bms_db_inst_I_ro;              //  [-] Bits=32 Factor= 0.001           Unit:'A'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_inst_I_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_PACK_DATA_1_t;

// def @VEH_BMS_PACK_DATA_2 CAN Message (1585 0x631)
#define VEH_BMS_PACK_DATA_2_IDE (0U)
#define VEH_BMS_PACK_DATA_2_DLC (7U)
#define VEH_BMS_PACK_DATA_2_CANID (0x631U)
#define VEH_BMS_PACK_DATA_2_CYC (50U)
// signal: @veh_bms_db_pack_1_T_ro
#define DBC_DRIVER_veh_bms_db_pack_1_T_ro_CovFactor (0.1)
#define DBC_DRIVER_veh_bms_db_pack_1_T_ro_toS(x) ( (uint16_t) (((x) - (-40.0)) / (0.1)) )
#define DBC_DRIVER_veh_bms_db_pack_1_T_ro_fromS(x) ( (((x) * (0.1)) + (-40.0)) )

// Value tables for @veh_bms_db_cb_status_e signal

#ifndef veh_bms_db_cb_status_e_VEH_BMS_PACK_DATA_2_CBSTAT_STATE__CLOSING
#define veh_bms_db_cb_status_e_VEH_BMS_PACK_DATA_2_CBSTAT_STATE__CLOSING (3)
#endif

#ifndef veh_bms_db_cb_status_e_VEH_BMS_PACK_DATA_2_CBSTAT_STATE__FAULT
#define veh_bms_db_cb_status_e_VEH_BMS_PACK_DATA_2_CBSTAT_STATE__FAULT (2)
#endif

#ifndef veh_bms_db_cb_status_e_VEH_BMS_PACK_DATA_2_CB_STATUS__CLOSED
#define veh_bms_db_cb_status_e_VEH_BMS_PACK_DATA_2_CB_STATUS__CLOSED (1)
#endif

#ifndef veh_bms_db_cb_status_e_VEH_BMS_PACK_DATA_2_CB_STATUS__OPEN
#define veh_bms_db_cb_status_e_VEH_BMS_PACK_DATA_2_CB_STATUS__OPEN (0)
#endif

// signal: @veh_bms_db_pack_2_T_ro
#define DBC_DRIVER_veh_bms_db_pack_2_T_ro_CovFactor (0.1)
#define DBC_DRIVER_veh_bms_db_pack_2_T_ro_toS(x) ( (uint16_t) (((x) - (-40.0)) / (0.1)) )
#define DBC_DRIVER_veh_bms_db_pack_2_T_ro_fromS(x) ( (((x) * (0.1)) + (-40.0)) )
// signal: @veh_bms_db_lv_pwr_U_ro
#define DBC_DRIVER_veh_bms_db_lv_pwr_U_ro_CovFactor (0.001)
#define DBC_DRIVER_veh_bms_db_lv_pwr_U_ro_toS(x) ( (uint16_t) (((x) - (0.0)) / (0.001)) )
#define DBC_DRIVER_veh_bms_db_lv_pwr_U_ro_fromS(x) ( (((x) * (0.001)) + (0.0)) )

typedef struct
{
#ifdef DBC_DRIVER_USE_BITS_SIGNAL

  // Pack temperature 1.
  uint16_t veh_bms_db_pack_1_T_ro;           //      Bits=11 Offset= -40.0              Factor= 0.1             Unit:'degC'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_pack_1_T_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Indicates the value of the IGNITION discrete input.
  uint8_t veh_bms_db_ign_b : 1;              //      Bits= 1

  // Indicates the value of the HWOVP discrete input.
  uint8_t veh_bms_db_hw_ovp_actv_b : 1;      //      Bits= 1

  // Indicates the observed state of the relay based on voltage and current.
  //  3 : "CBSTAT_STATE__CLOSING"
  //  2 : "CBSTAT_STATE__FAULT"
  //  1 : "CB_STATUS__CLOSED"
  //  0 : "CB_STATUS__OPEN"
  uint8_t veh_bms_db_cb_status_e : 2;        //      Bits= 2

  // Pack temperature 2.
  uint16_t veh_bms_db_pack_2_T_ro;           //      Bits=11 Offset= -40.0              Factor= 0.1             Unit:'degC'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_pack_2_T_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Indicates if the 12V supply  is too low to drive the Circuit Breaker.
  uint8_t veh_bms_db_pwrmon_b : 1;           //      Bits= 1

  // Low voltage (12V) power voltage.
  uint16_t veh_bms_db_lv_pwr_U_ro;           //      Bits=16 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_lv_pwr_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Absolute pack State of Charge.
  uint8_t veh_bms_db_pack_soc_abs_Pct;       //      Bits= 8

#else

  // Pack temperature 1.
  uint16_t veh_bms_db_pack_1_T_ro;           //      Bits=11 Offset= -40.0              Factor= 0.1             Unit:'degC'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_pack_1_T_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Indicates the value of the IGNITION discrete input.
  uint8_t veh_bms_db_ign_b;                  //      Bits= 1

  // Indicates the value of the HWOVP discrete input.
  uint8_t veh_bms_db_hw_ovp_actv_b;          //      Bits= 1

  // Indicates the observed state of the relay based on voltage and current.
  //  3 : "CBSTAT_STATE__CLOSING"
  //  2 : "CBSTAT_STATE__FAULT"
  //  1 : "CB_STATUS__CLOSED"
  //  0 : "CB_STATUS__OPEN"
  uint8_t veh_bms_db_cb_status_e;            //      Bits= 2

  // Pack temperature 2.
  uint16_t veh_bms_db_pack_2_T_ro;           //      Bits=11 Offset= -40.0              Factor= 0.1             Unit:'degC'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_pack_2_T_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Indicates if the 12V supply  is too low to drive the Circuit Breaker.
  uint8_t veh_bms_db_pwrmon_b;               //      Bits= 1

  // Low voltage (12V) power voltage.
  uint16_t veh_bms_db_lv_pwr_U_ro;           //      Bits=16 Factor= 0.001           Unit:'V'

#ifdef DBC_DRIVER_USE_SIGFLOAT
  sigfloat_t veh_bms_db_lv_pwr_U_phys;
#endif // DBC_DRIVER_USE_SIGFLOAT

  // Absolute pack State of Charge.
  uint8_t veh_bms_db_pack_soc_abs_Pct;       //      Bits= 8

#endif // DBC_DRIVER_USE_BITS_SIGNAL

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // DBC_DRIVER_USE_DIAG_MONITORS

} VEH_BMS_PACK_DATA_2_t;

// Function signatures

uint32_t Unpack_EBOOSTER_DATA_AND_FAULT_dbc_driver(EBOOSTER_DATA_AND_FAULT_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_EBOOSTER_DATA_AND_FAULT_dbc_driver(EBOOSTER_DATA_AND_FAULT_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EBOOSTER_DATA_AND_FAULT_dbc_driver(EBOOSTER_DATA_AND_FAULT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(VEH_TO_EBOOSTER_CONTROL_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(VEH_TO_EBOOSTER_CONTROL_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(VEH_TO_EBOOSTER_CONTROL_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_EBOOSTER_GENERAL_DATA_dbc_driver(EBOOSTER_GENERAL_DATA_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_EBOOSTER_GENERAL_DATA_dbc_driver(EBOOSTER_GENERAL_DATA_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_EBOOSTER_GENERAL_DATA_dbc_driver(EBOOSTER_GENERAL_DATA_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_MSG_TO_BMS_dbc_driver(VEH_MSG_TO_BMS_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_MSG_TO_BMS_dbc_driver(VEH_MSG_TO_BMS_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_MSG_TO_BMS_dbc_driver(VEH_MSG_TO_BMS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_CRASH_dbc_driver(VEH_CRASH_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_CRASH_dbc_driver(VEH_CRASH_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_CRASH_dbc_driver(VEH_CRASH_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_STATUS_1_dbc_driver(VEH_BMS_PACK_STATUS_1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_PACK_STATUS_1_dbc_driver(VEH_BMS_PACK_STATUS_1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_PACK_STATUS_1_dbc_driver(VEH_BMS_PACK_STATUS_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_STATUS_2_dbc_driver(VEH_BMS_PACK_STATUS_2_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_PACK_STATUS_2_dbc_driver(VEH_BMS_PACK_STATUS_2_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_PACK_STATUS_2_dbc_driver(VEH_BMS_PACK_STATUS_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_CELL_DATA_1_dbc_driver(VEH_BMS_CELL_DATA_1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_CELL_DATA_1_dbc_driver(VEH_BMS_CELL_DATA_1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_CELL_DATA_1_dbc_driver(VEH_BMS_CELL_DATA_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_CELL_DATA_2_dbc_driver(VEH_BMS_CELL_DATA_2_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_CELL_DATA_2_dbc_driver(VEH_BMS_CELL_DATA_2_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_CELL_DATA_2_dbc_driver(VEH_BMS_CELL_DATA_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_CELL_DATA_3_dbc_driver(VEH_BMS_CELL_DATA_3_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_CELL_DATA_3_dbc_driver(VEH_BMS_CELL_DATA_3_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_CELL_DATA_3_dbc_driver(VEH_BMS_CELL_DATA_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_CELL_DATA_4_dbc_driver(VEH_BMS_CELL_DATA_4_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_CELL_DATA_4_dbc_driver(VEH_BMS_CELL_DATA_4_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_CELL_DATA_4_dbc_driver(VEH_BMS_CELL_DATA_4_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_LIMITS_1_dbc_driver(VEH_BMS_PACK_LIMITS_1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_PACK_LIMITS_1_dbc_driver(VEH_BMS_PACK_LIMITS_1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_PACK_LIMITS_1_dbc_driver(VEH_BMS_PACK_LIMITS_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_LIMITS_2_dbc_driver(VEH_BMS_PACK_LIMITS_2_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_PACK_LIMITS_2_dbc_driver(VEH_BMS_PACK_LIMITS_2_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_PACK_LIMITS_2_dbc_driver(VEH_BMS_PACK_LIMITS_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_LIMITS_3_dbc_driver(VEH_BMS_PACK_LIMITS_3_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_PACK_LIMITS_3_dbc_driver(VEH_BMS_PACK_LIMITS_3_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_PACK_LIMITS_3_dbc_driver(VEH_BMS_PACK_LIMITS_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_DATA_1_dbc_driver(VEH_BMS_PACK_DATA_1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_PACK_DATA_1_dbc_driver(VEH_BMS_PACK_DATA_1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_PACK_DATA_1_dbc_driver(VEH_BMS_PACK_DATA_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_DATA_2_dbc_driver(VEH_BMS_PACK_DATA_2_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef DBC_DRIVER_USE_CANSTRUCT
uint32_t Pack_VEH_BMS_PACK_DATA_2_dbc_driver(VEH_BMS_PACK_DATA_2_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_VEH_BMS_PACK_DATA_2_dbc_driver(VEH_BMS_PACK_DATA_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // DBC_DRIVER_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
