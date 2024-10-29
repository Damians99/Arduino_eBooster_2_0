// Generator version : v3.1
// DBC filename      : Pony_V2.dbc
#include "dbc_driver.h"


// DBC file version
#if (VER_DBC_DRIVER_MAJ != (0U)) || (VER_DBC_DRIVER_MIN != (0U))
#error The DBC_DRIVER dbc source files have different versions
#endif

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "dbc_driver-fmon.h"

#endif // DBC_DRIVER_USE_DIAG_MONITORS

// This macro guard for the case when you need to enable
// using diag monitors but there is no necessity in proper
// SysTick provider. For providing one you need define macro
// before this line - in dbccodeconf.h

#ifndef GetSystemTick
#define GetSystemTick() (0u)
#endif

// This macro guard is for the case when you want to build
// app with enabled optoin auto CSM, but don't yet have
// proper getframehash implementation

#ifndef GetFrameHash
#define GetFrameHash(a,b,c,d,e) (0u)
#endif

// This function performs extension of sign for the signals
// whose bit width value is not aligned to one of power of 2 or less than 8.
// The types 'bitext_t' and 'ubitext_t' define the biggest bit width which
// can be correctly handled. You need to select type which can contain
// n+1 bits where n is the largest signed signal width. For example if
// the most wide signed signal has a width of 31 bits you need to set
// bitext_t as int32_t and ubitext_t as uint32_t
// Defined these typedefs in @dbccodeconf.h or locally in 'dbcdrvname'-config.h
static bitext_t __ext_sig__(ubitext_t val, uint8_t bits)
{
  ubitext_t const m = (ubitext_t) (1u << (bits - 1u));
  return ((val ^ m) - m);
}

uint32_t Unpack_EBOOSTER_DATA_AND_FAULT_dbc_driver(EBOOSTER_DATA_AND_FAULT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->overvoltage_48V = (uint8_t) ( (_d[0] & (0x01U)) );
  _m->undervoltage_48V = (uint8_t) ( ((_d[0] >> 1U) & (0x01U)) );
  _m->overspeed = (uint8_t) ( ((_d[0] >> 2U) & (0x01U)) );
  _m->timeout_cause_off = (uint8_t) ( ((_d[0] >> 3U) & (0x01U)) );
  _m->mecanical_blocked_ebooster = (uint8_t) ( ((_d[0] >> 4U) & (0x01U)) );
  _m->status_control_signal = (uint8_t) ( ((_d[0] >> 6U) & (0x01U)) );
  _m->timout_max_use = (uint8_t) ( ((_d[0] >> 7U) & (0x01U)) );
  _m->currentlimit_activ = (uint8_t) ( ((_d[1] >> 1U) & (0x01U)) );
  _m->Unbekannt_3 = (uint8_t) ( ((_d[1] >> 6U) & (0x01U)) );
  _m->error_auto_off = (uint8_t) ( ((_d[1] >> 7U) & (0x01U)) );
  _m->actual_speed_ebooster_ro = (uint16_t) ( ((_d[4] & (0x03U)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->actual_speed_ebooster_phys = (uint32_t) DBC_DRIVER_actual_speed_ebooster_ro_fromS(_m->actual_speed_ebooster_ro);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->actual_current_ebooster = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->thermal_dutty_ebooter = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EBOOSTER_DATA_AND_FAULT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EBOOSTER_DATA_AND_FAULT_dbc_driver(&_m->mon1, EBOOSTER_DATA_AND_FAULT_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return EBOOSTER_DATA_AND_FAULT_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_EBOOSTER_DATA_AND_FAULT_dbc_driver(EBOOSTER_DATA_AND_FAULT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(EBOOSTER_DATA_AND_FAULT_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->actual_speed_ebooster_ro = (uint16_t) DBC_DRIVER_actual_speed_ebooster_ro_toS(_m->actual_speed_ebooster_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->overvoltage_48V & (0x01U)) | ((_m->undervoltage_48V & (0x01U)) << 1U) | ((_m->overspeed & (0x01U)) << 2U) | ((_m->timeout_cause_off & (0x01U)) << 3U) | ((_m->mecanical_blocked_ebooster & (0x01U)) << 4U) | ((_m->status_control_signal & (0x01U)) << 6U) | ((_m->timout_max_use & (0x01U)) << 7U) );
  cframe->Data[1] |= (uint8_t) ( ((_m->currentlimit_activ & (0x01U)) << 1U) | ((_m->Unbekannt_3 & (0x01U)) << 6U) | ((_m->error_auto_off & (0x01U)) << 7U) );
  cframe->Data[3] |= (uint8_t) ( (_m->actual_speed_ebooster_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->actual_speed_ebooster_ro >> 8U) & (0x03U)) );
  cframe->Data[5] |= (uint8_t) ( (_m->actual_current_ebooster & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->thermal_dutty_ebooter & (0xFFU)) );

  cframe->MsgId = (uint32_t) EBOOSTER_DATA_AND_FAULT_CANID;
  cframe->DLC = (uint8_t) EBOOSTER_DATA_AND_FAULT_DLC;
  cframe->IDE = (uint8_t) EBOOSTER_DATA_AND_FAULT_IDE;
  return EBOOSTER_DATA_AND_FAULT_CANID;
}

#else

uint32_t Pack_EBOOSTER_DATA_AND_FAULT_dbc_driver(EBOOSTER_DATA_AND_FAULT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(EBOOSTER_DATA_AND_FAULT_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->actual_speed_ebooster_ro = (uint16_t) DBC_DRIVER_actual_speed_ebooster_ro_toS(_m->actual_speed_ebooster_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->overvoltage_48V & (0x01U)) | ((_m->undervoltage_48V & (0x01U)) << 1U) | ((_m->overspeed & (0x01U)) << 2U) | ((_m->timeout_cause_off & (0x01U)) << 3U) | ((_m->mecanical_blocked_ebooster & (0x01U)) << 4U) | ((_m->status_control_signal & (0x01U)) << 6U) | ((_m->timout_max_use & (0x01U)) << 7U) );
  _d[1] |= (uint8_t) ( ((_m->currentlimit_activ & (0x01U)) << 1U) | ((_m->Unbekannt_3 & (0x01U)) << 6U) | ((_m->error_auto_off & (0x01U)) << 7U) );
  _d[3] |= (uint8_t) ( (_m->actual_speed_ebooster_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->actual_speed_ebooster_ro >> 8U) & (0x03U)) );
  _d[5] |= (uint8_t) ( (_m->actual_current_ebooster & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->thermal_dutty_ebooter & (0xFFU)) );

  *_len = (uint8_t) EBOOSTER_DATA_AND_FAULT_DLC;
  *_ide = (uint8_t) EBOOSTER_DATA_AND_FAULT_IDE;
  return EBOOSTER_DATA_AND_FAULT_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(VEH_TO_EBOOSTER_CONTROL_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->target_speed_ebooster_ro = (uint16_t) ( ((_d[3] & (0x03U)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->target_speed_ebooster_phys = (uint32_t) DBC_DRIVER_target_speed_ebooster_ro_fromS(_m->target_speed_ebooster_ro);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->Unbekannt_1 = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->Unbekannt_2 = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->collant_flow_ebooster_ro = (uint8_t) ( (_d[6] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->collant_flow_ebooster_phys = (sigfloat_t)(DBC_DRIVER_collant_flow_ebooster_ro_fromS(_m->collant_flow_ebooster_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->max_current_48V = (uint8_t) ( (_d[7] & (0xFFU)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_TO_EBOOSTER_CONTROL_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_TO_EBOOSTER_CONTROL_dbc_driver(&_m->mon1, VEH_TO_EBOOSTER_CONTROL_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_TO_EBOOSTER_CONTROL_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(VEH_TO_EBOOSTER_CONTROL_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_TO_EBOOSTER_CONTROL_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->target_speed_ebooster_ro = (uint16_t) DBC_DRIVER_target_speed_ebooster_ro_toS(_m->target_speed_ebooster_phys);
  _m->collant_flow_ebooster_ro = (uint8_t) DBC_DRIVER_collant_flow_ebooster_ro_toS(_m->collant_flow_ebooster_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[2] |= (uint8_t) ( (_m->target_speed_ebooster_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->target_speed_ebooster_ro >> 8U) & (0x03U)) );
  cframe->Data[4] |= (uint8_t) ( (_m->Unbekannt_1 & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->Unbekannt_2 & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->collant_flow_ebooster_ro & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->max_current_48V & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_TO_EBOOSTER_CONTROL_CANID;
  cframe->DLC = (uint8_t) VEH_TO_EBOOSTER_CONTROL_DLC;
  cframe->IDE = (uint8_t) VEH_TO_EBOOSTER_CONTROL_IDE;
  return VEH_TO_EBOOSTER_CONTROL_CANID;
}

#else

uint32_t Pack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(VEH_TO_EBOOSTER_CONTROL_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_TO_EBOOSTER_CONTROL_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->target_speed_ebooster_ro = (uint16_t) DBC_DRIVER_target_speed_ebooster_ro_toS(_m->target_speed_ebooster_phys);
  _m->collant_flow_ebooster_ro = (uint8_t) DBC_DRIVER_collant_flow_ebooster_ro_toS(_m->collant_flow_ebooster_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[2] |= (uint8_t) ( (_m->target_speed_ebooster_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->target_speed_ebooster_ro >> 8U) & (0x03U)) );
  _d[4] |= (uint8_t) ( (_m->Unbekannt_1 & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->Unbekannt_2 & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->collant_flow_ebooster_ro & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->max_current_48V & (0xFFU)) );

  *_len = (uint8_t) VEH_TO_EBOOSTER_CONTROL_DLC;
  *_ide = (uint8_t) VEH_TO_EBOOSTER_CONTROL_IDE;
  return VEH_TO_EBOOSTER_CONTROL_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_EBOOSTER_GENERAL_DATA_dbc_driver(EBOOSTER_GENERAL_DATA_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ebooster_tx_counter = (uint16_t) ( ((_d[1] & (0xFFU)) << 8U) | (_d[0] & (0xFFU)) );
  _m->actual_temperature_ebooster_ro = (uint8_t) ( (_d[2] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->actual_temperature_ebooster_phys = (sigfloat_t)(DBC_DRIVER_actual_temperature_ebooster_ro_fromS(_m->actual_temperature_ebooster_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->actual_supply_voltage_48V_ro = (uint8_t) ( (_d[3] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->actual_supply_voltage_48V_phys = (sigfloat_t)(DBC_DRIVER_actual_supply_voltage_48V_ro_fromS(_m->actual_supply_voltage_48V_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EBOOSTER_GENERAL_DATA_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EBOOSTER_GENERAL_DATA_dbc_driver(&_m->mon1, EBOOSTER_GENERAL_DATA_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return EBOOSTER_GENERAL_DATA_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_EBOOSTER_GENERAL_DATA_dbc_driver(EBOOSTER_GENERAL_DATA_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(EBOOSTER_GENERAL_DATA_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->actual_temperature_ebooster_ro = (uint8_t) DBC_DRIVER_actual_temperature_ebooster_ro_toS(_m->actual_temperature_ebooster_phys);
  _m->actual_supply_voltage_48V_ro = (uint8_t) DBC_DRIVER_actual_supply_voltage_48V_ro_toS(_m->actual_supply_voltage_48V_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( (_m->ebooster_tx_counter & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->ebooster_tx_counter >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->actual_temperature_ebooster_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->actual_supply_voltage_48V_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) EBOOSTER_GENERAL_DATA_CANID;
  cframe->DLC = (uint8_t) EBOOSTER_GENERAL_DATA_DLC;
  cframe->IDE = (uint8_t) EBOOSTER_GENERAL_DATA_IDE;
  return EBOOSTER_GENERAL_DATA_CANID;
}

#else

uint32_t Pack_EBOOSTER_GENERAL_DATA_dbc_driver(EBOOSTER_GENERAL_DATA_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(EBOOSTER_GENERAL_DATA_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->actual_temperature_ebooster_ro = (uint8_t) DBC_DRIVER_actual_temperature_ebooster_ro_toS(_m->actual_temperature_ebooster_phys);
  _m->actual_supply_voltage_48V_ro = (uint8_t) DBC_DRIVER_actual_supply_voltage_48V_ro_toS(_m->actual_supply_voltage_48V_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( (_m->ebooster_tx_counter & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->ebooster_tx_counter >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->actual_temperature_ebooster_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->actual_supply_voltage_48V_ro & (0xFFU)) );

  *_len = (uint8_t) EBOOSTER_GENERAL_DATA_DLC;
  *_ide = (uint8_t) EBOOSTER_GENERAL_DATA_IDE;
  return EBOOSTER_GENERAL_DATA_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_MSG_TO_BMS_dbc_driver(VEH_MSG_TO_BMS_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_cb_cmd_e = (uint8_t) ( (_d[0] & (0x01U)) );
  _m->veh_fan_dutycycle_cmd = (uint8_t) ( (_d[1] & (0xFFU)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_MSG_TO_BMS_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_MSG_TO_BMS_dbc_driver(&_m->mon1, VEH_MSG_TO_BMS_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_MSG_TO_BMS_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_MSG_TO_BMS_dbc_driver(VEH_MSG_TO_BMS_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_MSG_TO_BMS_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->veh_cb_cmd_e & (0x01U)) );
  cframe->Data[1] |= (uint8_t) ( (_m->veh_fan_dutycycle_cmd & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_MSG_TO_BMS_CANID;
  cframe->DLC = (uint8_t) VEH_MSG_TO_BMS_DLC;
  cframe->IDE = (uint8_t) VEH_MSG_TO_BMS_IDE;
  return VEH_MSG_TO_BMS_CANID;
}

#else

uint32_t Pack_VEH_MSG_TO_BMS_dbc_driver(VEH_MSG_TO_BMS_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_MSG_TO_BMS_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->veh_cb_cmd_e & (0x01U)) );
  _d[1] |= (uint8_t) ( (_m->veh_fan_dutycycle_cmd & (0xFFU)) );

  *_len = (uint8_t) VEH_MSG_TO_BMS_DLC;
  *_ide = (uint8_t) VEH_MSG_TO_BMS_IDE;
  return VEH_MSG_TO_BMS_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_CRASH_dbc_driver(VEH_CRASH_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_crash_cmd_b = (uint8_t) ( (_d[0] & (0x01U)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_CRASH_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_CRASH_dbc_driver(&_m->mon1, VEH_CRASH_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_CRASH_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_CRASH_dbc_driver(VEH_CRASH_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_CRASH_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( (_m->veh_crash_cmd_b & (0x01U)) );

  cframe->MsgId = (uint32_t) VEH_CRASH_CANID;
  cframe->DLC = (uint8_t) VEH_CRASH_DLC;
  cframe->IDE = (uint8_t) VEH_CRASH_IDE;
  return VEH_CRASH_CANID;
}

#else

uint32_t Pack_VEH_CRASH_dbc_driver(VEH_CRASH_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_CRASH_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( (_m->veh_crash_cmd_b & (0x01U)) );

  *_len = (uint8_t) VEH_CRASH_DLC;
  *_ide = (uint8_t) VEH_CRASH_IDE;
  return VEH_CRASH_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_STATUS_1_dbc_driver(VEH_BMS_PACK_STATUS_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_cb_state_e = (uint8_t) ( ((_d[1] >> 5U) & (0x07U)) );
  _m->veh_bms_db_rolling_counter = (uint8_t) ( (_d[2] & (0x0FU)) );
  _m->fan_status = (uint8_t) ( ((_d[2] >> 4U) & (0x03U)) );
  _m->soft_epo_status = (uint8_t) ( ((_d[2] >> 6U) & (0x01U)) );
  _m->hard_epo_status = (uint8_t) ( ((_d[2] >> 7U) & (0x01U)) );
  _m->veh_bms_db_cbal_en_b = (uint8_t) ( (_d[3] & (0x01U)) );
  _m->veh_bms_db_arb_cmd_e = (int8_t) __ext_sig__(( ((_d[3] >> 1U) & (0x01U)) ), 1);
  _m->veh_bms_db_cb_err_stuck_open_b = (uint8_t) ( ((_d[3] >> 2U) & (0x01U)) );
  _m->veh_bms_db_cb_err_stuck_closed_b = (uint8_t) ( ((_d[3] >> 3U) & (0x01U)) );
  _m->derating_status = (uint8_t) ( ((_d[3] >> 4U) & (0x01U)) );
  _m->hvbatt_total_capacity = (uint8_t) ( ((_d[3] >> 5U) & (0x07U)) );
  _m->veh_bms_db_ocp_maturing_actv_b = (uint8_t) ( (_d[4] & (0x01U)) );
  _m->veh_bms_db_ocp_actv_b = (uint8_t) ( ((_d[4] >> 1U) & (0x01U)) );
  _m->veh_bms_db_otp_maturing_actv_b = (uint8_t) ( ((_d[4] >> 2U) & (0x01U)) );
  _m->veh_bms_db_otp_actv_b = (uint8_t) ( ((_d[4] >> 3U) & (0x01U)) );
  _m->veh_bms_db_ovp_maturing_actv_b = (uint8_t) ( ((_d[4] >> 4U) & (0x01U)) );
  _m->veh_bms_db_ovp_actv_b = (uint8_t) ( ((_d[4] >> 5U) & (0x01U)) );
  _m->veh_bms_db_uvp_maturing_actv_b = (uint8_t) ( ((_d[4] >> 6U) & (0x01U)) );
  _m->veh_bms_db_uvp_actv_b = (uint8_t) ( ((_d[4] >> 7U) & (0x01U)) );
  _m->veh_bms_db_soh = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->veh_bms_db_dtc_otp_actv_b = (uint8_t) ( (_d[6] & (0x01U)) );
  _m->veh_bms_db_dtc_cb_weld_actv_b = (uint8_t) ( ((_d[6] >> 1U) & (0x01U)) );
  _m->veh_bms_dtc_equalize_fail_actv_b = (uint8_t) ( ((_d[6] >> 2U) & (0x01U)) );
  _m->veh_bms_db_dtc_ovp_actv_b = (uint8_t) ( ((_d[6] >> 3U) & (0x01U)) );
  _m->veh_bms_db_dtc_uvp_actv_b = (uint8_t) ( ((_d[6] >> 4U) & (0x01U)) );
  _m->veh_bms_dtc_cb_stuck_open_actv_b = (uint8_t) ( ((_d[6] >> 5U) & (0x01U)) );
  _m->veh_bms_db_dtc_cb_uncmnd_open_b = (uint8_t) ( ((_d[6] >> 6U) & (0x01U)) );
  _m->veh_bms_db_dtc_cb_failed_open_b = (uint8_t) ( ((_d[6] >> 7U) & (0x01U)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_PACK_STATUS_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_PACK_STATUS_1_dbc_driver(&_m->mon1, VEH_BMS_PACK_STATUS_1_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_PACK_STATUS_1_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_PACK_STATUS_1_dbc_driver(VEH_BMS_PACK_STATUS_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_STATUS_1_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

  cframe->Data[1] |= (uint8_t) ( ((_m->veh_bms_db_cb_state_e & (0x07U)) << 5U) );
  cframe->Data[2] |= (uint8_t) ( (_m->veh_bms_db_rolling_counter & (0x0FU)) | ((_m->fan_status & (0x03U)) << 4U) | ((_m->soft_epo_status & (0x01U)) << 6U) | ((_m->hard_epo_status & (0x01U)) << 7U) );
  cframe->Data[3] |= (uint8_t) ( (_m->veh_bms_db_cbal_en_b & (0x01U)) | ((_m->veh_bms_db_arb_cmd_e & (0x01U)) << 1U) | ((_m->veh_bms_db_cb_err_stuck_open_b & (0x01U)) << 2U) | ((_m->veh_bms_db_cb_err_stuck_closed_b & (0x01U)) << 3U) | ((_m->derating_status & (0x01U)) << 4U) | ((_m->hvbatt_total_capacity & (0x07U)) << 5U) );
  cframe->Data[4] |= (uint8_t) ( (_m->veh_bms_db_ocp_maturing_actv_b & (0x01U)) | ((_m->veh_bms_db_ocp_actv_b & (0x01U)) << 1U) | ((_m->veh_bms_db_otp_maturing_actv_b & (0x01U)) << 2U) | ((_m->veh_bms_db_otp_actv_b & (0x01U)) << 3U) | ((_m->veh_bms_db_ovp_maturing_actv_b & (0x01U)) << 4U) | ((_m->veh_bms_db_ovp_actv_b & (0x01U)) << 5U) | ((_m->veh_bms_db_uvp_maturing_actv_b & (0x01U)) << 6U) | ((_m->veh_bms_db_uvp_actv_b & (0x01U)) << 7U) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_soh & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->veh_bms_db_dtc_otp_actv_b & (0x01U)) | ((_m->veh_bms_db_dtc_cb_weld_actv_b & (0x01U)) << 1U) | ((_m->veh_bms_dtc_equalize_fail_actv_b & (0x01U)) << 2U) | ((_m->veh_bms_db_dtc_ovp_actv_b & (0x01U)) << 3U) | ((_m->veh_bms_db_dtc_uvp_actv_b & (0x01U)) << 4U) | ((_m->veh_bms_dtc_cb_stuck_open_actv_b & (0x01U)) << 5U) | ((_m->veh_bms_db_dtc_cb_uncmnd_open_b & (0x01U)) << 6U) | ((_m->veh_bms_db_dtc_cb_failed_open_b & (0x01U)) << 7U) );

  cframe->MsgId = (uint32_t) VEH_BMS_PACK_STATUS_1_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_PACK_STATUS_1_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_PACK_STATUS_1_IDE;
  return VEH_BMS_PACK_STATUS_1_CANID;
}

#else

uint32_t Pack_VEH_BMS_PACK_STATUS_1_dbc_driver(VEH_BMS_PACK_STATUS_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_STATUS_1_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

  _d[1] |= (uint8_t) ( ((_m->veh_bms_db_cb_state_e & (0x07U)) << 5U) );
  _d[2] |= (uint8_t) ( (_m->veh_bms_db_rolling_counter & (0x0FU)) | ((_m->fan_status & (0x03U)) << 4U) | ((_m->soft_epo_status & (0x01U)) << 6U) | ((_m->hard_epo_status & (0x01U)) << 7U) );
  _d[3] |= (uint8_t) ( (_m->veh_bms_db_cbal_en_b & (0x01U)) | ((_m->veh_bms_db_arb_cmd_e & (0x01U)) << 1U) | ((_m->veh_bms_db_cb_err_stuck_open_b & (0x01U)) << 2U) | ((_m->veh_bms_db_cb_err_stuck_closed_b & (0x01U)) << 3U) | ((_m->derating_status & (0x01U)) << 4U) | ((_m->hvbatt_total_capacity & (0x07U)) << 5U) );
  _d[4] |= (uint8_t) ( (_m->veh_bms_db_ocp_maturing_actv_b & (0x01U)) | ((_m->veh_bms_db_ocp_actv_b & (0x01U)) << 1U) | ((_m->veh_bms_db_otp_maturing_actv_b & (0x01U)) << 2U) | ((_m->veh_bms_db_otp_actv_b & (0x01U)) << 3U) | ((_m->veh_bms_db_ovp_maturing_actv_b & (0x01U)) << 4U) | ((_m->veh_bms_db_ovp_actv_b & (0x01U)) << 5U) | ((_m->veh_bms_db_uvp_maturing_actv_b & (0x01U)) << 6U) | ((_m->veh_bms_db_uvp_actv_b & (0x01U)) << 7U) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_soh & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->veh_bms_db_dtc_otp_actv_b & (0x01U)) | ((_m->veh_bms_db_dtc_cb_weld_actv_b & (0x01U)) << 1U) | ((_m->veh_bms_dtc_equalize_fail_actv_b & (0x01U)) << 2U) | ((_m->veh_bms_db_dtc_ovp_actv_b & (0x01U)) << 3U) | ((_m->veh_bms_db_dtc_uvp_actv_b & (0x01U)) << 4U) | ((_m->veh_bms_dtc_cb_stuck_open_actv_b & (0x01U)) << 5U) | ((_m->veh_bms_db_dtc_cb_uncmnd_open_b & (0x01U)) << 6U) | ((_m->veh_bms_db_dtc_cb_failed_open_b & (0x01U)) << 7U) );

  *_len = (uint8_t) VEH_BMS_PACK_STATUS_1_DLC;
  *_ide = (uint8_t) VEH_BMS_PACK_STATUS_1_IDE;
  return VEH_BMS_PACK_STATUS_1_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_STATUS_2_dbc_driver(VEH_BMS_PACK_STATUS_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_cb_loaded_switched_Cnt = (uint32_t) ( ((_d[0] & (0x03U)) << 16U) | ((_d[1] & (0xFFU)) << 8U) | (_d[2] & (0xFFU)) );
  _m->veh_bms_cb_lifetime_remain_Pct = (uint8_t) ( (_d[3] & (0xFFU)) );
  _m->veh_bms_db_sw_version_build = (uint8_t) ( (_d[4] & (0xFFU)) );
  _m->veh_bms_db_sw_version_minor = (uint8_t) ( (_d[5] & (0xFFU)) );
  _m->veh_bms_db_sw_version_major = (uint8_t) ( (_d[6] & (0xFFU)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_PACK_STATUS_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_PACK_STATUS_2_dbc_driver(&_m->mon1, VEH_BMS_PACK_STATUS_2_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_PACK_STATUS_2_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_PACK_STATUS_2_dbc_driver(VEH_BMS_PACK_STATUS_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_STATUS_2_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_cb_loaded_switched_Cnt >> 16U) & (0x03U)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->veh_bms_cb_loaded_switched_Cnt >> 8U) & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->veh_bms_cb_loaded_switched_Cnt & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->veh_bms_cb_lifetime_remain_Pct & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( (_m->veh_bms_db_sw_version_build & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_sw_version_minor & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->veh_bms_db_sw_version_major & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_PACK_STATUS_2_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_PACK_STATUS_2_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_PACK_STATUS_2_IDE;
  return VEH_BMS_PACK_STATUS_2_CANID;
}

#else

uint32_t Pack_VEH_BMS_PACK_STATUS_2_dbc_driver(VEH_BMS_PACK_STATUS_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_STATUS_2_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

  _d[0] |= (uint8_t) ( ((_m->veh_bms_cb_loaded_switched_Cnt >> 16U) & (0x03U)) );
  _d[1] |= (uint8_t) ( ((_m->veh_bms_cb_loaded_switched_Cnt >> 8U) & (0xFFU)) );
  _d[2] |= (uint8_t) ( (_m->veh_bms_cb_loaded_switched_Cnt & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->veh_bms_cb_lifetime_remain_Pct & (0xFFU)) );
  _d[4] |= (uint8_t) ( (_m->veh_bms_db_sw_version_build & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_sw_version_minor & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->veh_bms_db_sw_version_major & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_PACK_STATUS_2_DLC;
  *_ide = (uint8_t) VEH_BMS_PACK_STATUS_2_IDE;
  return VEH_BMS_PACK_STATUS_2_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_CELL_DATA_1_dbc_driver(VEH_BMS_CELL_DATA_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_cell_01_U_ro = (uint16_t) ( ((_d[0] & (0x1FU)) << 8U) | (_d[1] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_01_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_01_U_ro_fromS(_m->veh_bms_db_cell_01_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_01_bal_actv_b = (uint8_t) ( ((_d[0] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_02_U_ro = (uint16_t) ( ((_d[2] & (0x1FU)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_02_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_02_U_ro_fromS(_m->veh_bms_db_cell_02_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_02_bal_actv_b = (uint8_t) ( ((_d[2] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_03_U_ro = (uint16_t) ( ((_d[4] & (0x1FU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_03_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_03_U_ro_fromS(_m->veh_bms_db_cell_03_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_03_bal_actv_b = (uint8_t) ( ((_d[4] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_04_U_ro = (uint16_t) ( ((_d[6] & (0x1FU)) << 8U) | (_d[7] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_04_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_04_U_ro_fromS(_m->veh_bms_db_cell_04_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_04_bal_actv_b = (uint8_t) ( ((_d[6] >> 5U) & (0x01U)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_CELL_DATA_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_CELL_DATA_1_dbc_driver(&_m->mon1, VEH_BMS_CELL_DATA_1_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_CELL_DATA_1_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_CELL_DATA_1_dbc_driver(VEH_BMS_CELL_DATA_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_CELL_DATA_1_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_01_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_01_U_ro_toS(_m->veh_bms_db_cell_01_U_phys);
  _m->veh_bms_db_cell_02_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_02_U_ro_toS(_m->veh_bms_db_cell_02_U_phys);
  _m->veh_bms_db_cell_03_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_03_U_ro_toS(_m->veh_bms_db_cell_03_U_phys);
  _m->veh_bms_db_cell_04_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_04_U_ro_toS(_m->veh_bms_db_cell_04_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_cell_01_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_01_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[1] |= (uint8_t) ( (_m->veh_bms_db_cell_01_U_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->veh_bms_db_cell_02_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_02_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[3] |= (uint8_t) ( (_m->veh_bms_db_cell_02_U_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_cell_03_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_03_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_cell_03_U_ro & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->veh_bms_db_cell_04_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_04_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[7] |= (uint8_t) ( (_m->veh_bms_db_cell_04_U_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_CELL_DATA_1_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_CELL_DATA_1_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_CELL_DATA_1_IDE;
  return VEH_BMS_CELL_DATA_1_CANID;
}

#else

uint32_t Pack_VEH_BMS_CELL_DATA_1_dbc_driver(VEH_BMS_CELL_DATA_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_CELL_DATA_1_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_01_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_01_U_ro_toS(_m->veh_bms_db_cell_01_U_phys);
  _m->veh_bms_db_cell_02_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_02_U_ro_toS(_m->veh_bms_db_cell_02_U_phys);
  _m->veh_bms_db_cell_03_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_03_U_ro_toS(_m->veh_bms_db_cell_03_U_phys);
  _m->veh_bms_db_cell_04_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_04_U_ro_toS(_m->veh_bms_db_cell_04_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_cell_01_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_01_bal_actv_b & (0x01U)) << 5U) );
  _d[1] |= (uint8_t) ( (_m->veh_bms_db_cell_01_U_ro & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->veh_bms_db_cell_02_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_02_bal_actv_b & (0x01U)) << 5U) );
  _d[3] |= (uint8_t) ( (_m->veh_bms_db_cell_02_U_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_cell_03_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_03_bal_actv_b & (0x01U)) << 5U) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_cell_03_U_ro & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->veh_bms_db_cell_04_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_04_bal_actv_b & (0x01U)) << 5U) );
  _d[7] |= (uint8_t) ( (_m->veh_bms_db_cell_04_U_ro & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_CELL_DATA_1_DLC;
  *_ide = (uint8_t) VEH_BMS_CELL_DATA_1_IDE;
  return VEH_BMS_CELL_DATA_1_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_CELL_DATA_2_dbc_driver(VEH_BMS_CELL_DATA_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_cell_05_U_ro = (uint16_t) ( ((_d[0] & (0x1FU)) << 8U) | (_d[1] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_05_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_05_U_ro_fromS(_m->veh_bms_db_cell_05_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_05_bal_actv_b = (uint8_t) ( ((_d[0] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_06_U_ro = (uint16_t) ( ((_d[2] & (0x1FU)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_06_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_06_U_ro_fromS(_m->veh_bms_db_cell_06_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_06_bal_actv_b = (uint8_t) ( ((_d[2] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_07_U_ro = (uint16_t) ( ((_d[4] & (0x1FU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_07_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_07_U_ro_fromS(_m->veh_bms_db_cell_07_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_07_bal_actv_b = (uint8_t) ( ((_d[4] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_08_U_ro = (uint16_t) ( ((_d[6] & (0x1FU)) << 8U) | (_d[7] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_08_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_08_U_ro_fromS(_m->veh_bms_db_cell_08_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_08_bal_actv_b = (uint8_t) ( ((_d[6] >> 5U) & (0x01U)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_CELL_DATA_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_CELL_DATA_2_dbc_driver(&_m->mon1, VEH_BMS_CELL_DATA_2_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_CELL_DATA_2_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_CELL_DATA_2_dbc_driver(VEH_BMS_CELL_DATA_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_CELL_DATA_2_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_05_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_05_U_ro_toS(_m->veh_bms_db_cell_05_U_phys);
  _m->veh_bms_db_cell_06_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_06_U_ro_toS(_m->veh_bms_db_cell_06_U_phys);
  _m->veh_bms_db_cell_07_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_07_U_ro_toS(_m->veh_bms_db_cell_07_U_phys);
  _m->veh_bms_db_cell_08_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_08_U_ro_toS(_m->veh_bms_db_cell_08_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_cell_05_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_05_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[1] |= (uint8_t) ( (_m->veh_bms_db_cell_05_U_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->veh_bms_db_cell_06_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_06_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[3] |= (uint8_t) ( (_m->veh_bms_db_cell_06_U_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_cell_07_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_07_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_cell_07_U_ro & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->veh_bms_db_cell_08_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_08_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[7] |= (uint8_t) ( (_m->veh_bms_db_cell_08_U_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_CELL_DATA_2_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_CELL_DATA_2_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_CELL_DATA_2_IDE;
  return VEH_BMS_CELL_DATA_2_CANID;
}

#else

uint32_t Pack_VEH_BMS_CELL_DATA_2_dbc_driver(VEH_BMS_CELL_DATA_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_CELL_DATA_2_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_05_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_05_U_ro_toS(_m->veh_bms_db_cell_05_U_phys);
  _m->veh_bms_db_cell_06_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_06_U_ro_toS(_m->veh_bms_db_cell_06_U_phys);
  _m->veh_bms_db_cell_07_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_07_U_ro_toS(_m->veh_bms_db_cell_07_U_phys);
  _m->veh_bms_db_cell_08_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_08_U_ro_toS(_m->veh_bms_db_cell_08_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_cell_05_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_05_bal_actv_b & (0x01U)) << 5U) );
  _d[1] |= (uint8_t) ( (_m->veh_bms_db_cell_05_U_ro & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->veh_bms_db_cell_06_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_06_bal_actv_b & (0x01U)) << 5U) );
  _d[3] |= (uint8_t) ( (_m->veh_bms_db_cell_06_U_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_cell_07_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_07_bal_actv_b & (0x01U)) << 5U) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_cell_07_U_ro & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->veh_bms_db_cell_08_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_08_bal_actv_b & (0x01U)) << 5U) );
  _d[7] |= (uint8_t) ( (_m->veh_bms_db_cell_08_U_ro & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_CELL_DATA_2_DLC;
  *_ide = (uint8_t) VEH_BMS_CELL_DATA_2_IDE;
  return VEH_BMS_CELL_DATA_2_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_CELL_DATA_3_dbc_driver(VEH_BMS_CELL_DATA_3_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_cell_09_U_ro = (uint16_t) ( ((_d[0] & (0x1FU)) << 8U) | (_d[1] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_09_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_09_U_ro_fromS(_m->veh_bms_db_cell_09_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_09_bal_actv_b = (uint8_t) ( ((_d[0] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_10_U_ro = (uint16_t) ( ((_d[2] & (0x1FU)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_10_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_10_U_ro_fromS(_m->veh_bms_db_cell_10_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_10_bal_actv_b = (uint8_t) ( ((_d[2] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_11_U_ro = (uint16_t) ( ((_d[4] & (0x1FU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_11_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_11_U_ro_fromS(_m->veh_bms_db_cell_11_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_11_bal_actv_b = (uint8_t) ( ((_d[4] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_12_U_ro = (uint16_t) ( ((_d[6] & (0x1FU)) << 8U) | (_d[7] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_12_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_12_U_ro_fromS(_m->veh_bms_db_cell_12_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_12_bal_actv_b = (uint8_t) ( ((_d[6] >> 5U) & (0x01U)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_CELL_DATA_3_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_CELL_DATA_3_dbc_driver(&_m->mon1, VEH_BMS_CELL_DATA_3_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_CELL_DATA_3_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_CELL_DATA_3_dbc_driver(VEH_BMS_CELL_DATA_3_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_CELL_DATA_3_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_09_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_09_U_ro_toS(_m->veh_bms_db_cell_09_U_phys);
  _m->veh_bms_db_cell_10_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_10_U_ro_toS(_m->veh_bms_db_cell_10_U_phys);
  _m->veh_bms_db_cell_11_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_11_U_ro_toS(_m->veh_bms_db_cell_11_U_phys);
  _m->veh_bms_db_cell_12_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_12_U_ro_toS(_m->veh_bms_db_cell_12_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_cell_09_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_09_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[1] |= (uint8_t) ( (_m->veh_bms_db_cell_09_U_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->veh_bms_db_cell_10_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_10_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[3] |= (uint8_t) ( (_m->veh_bms_db_cell_10_U_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_cell_11_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_11_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_cell_11_U_ro & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->veh_bms_db_cell_12_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_12_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[7] |= (uint8_t) ( (_m->veh_bms_db_cell_12_U_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_CELL_DATA_3_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_CELL_DATA_3_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_CELL_DATA_3_IDE;
  return VEH_BMS_CELL_DATA_3_CANID;
}

#else

uint32_t Pack_VEH_BMS_CELL_DATA_3_dbc_driver(VEH_BMS_CELL_DATA_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_CELL_DATA_3_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_09_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_09_U_ro_toS(_m->veh_bms_db_cell_09_U_phys);
  _m->veh_bms_db_cell_10_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_10_U_ro_toS(_m->veh_bms_db_cell_10_U_phys);
  _m->veh_bms_db_cell_11_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_11_U_ro_toS(_m->veh_bms_db_cell_11_U_phys);
  _m->veh_bms_db_cell_12_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_12_U_ro_toS(_m->veh_bms_db_cell_12_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_cell_09_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_09_bal_actv_b & (0x01U)) << 5U) );
  _d[1] |= (uint8_t) ( (_m->veh_bms_db_cell_09_U_ro & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->veh_bms_db_cell_10_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_10_bal_actv_b & (0x01U)) << 5U) );
  _d[3] |= (uint8_t) ( (_m->veh_bms_db_cell_10_U_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_cell_11_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_11_bal_actv_b & (0x01U)) << 5U) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_cell_11_U_ro & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->veh_bms_db_cell_12_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_12_bal_actv_b & (0x01U)) << 5U) );
  _d[7] |= (uint8_t) ( (_m->veh_bms_db_cell_12_U_ro & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_CELL_DATA_3_DLC;
  *_ide = (uint8_t) VEH_BMS_CELL_DATA_3_IDE;
  return VEH_BMS_CELL_DATA_3_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_CELL_DATA_4_dbc_driver(VEH_BMS_CELL_DATA_4_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_cell_13_U_ro = (uint16_t) ( ((_d[0] & (0x1FU)) << 8U) | (_d[1] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_13_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_13_U_ro_fromS(_m->veh_bms_db_cell_13_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_13_bal_actv_b = (uint8_t) ( ((_d[0] >> 5U) & (0x01U)) );
  _m->veh_bms_db_cell_14_U_ro = (uint16_t) ( ((_d[2] & (0x1FU)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_14_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_cell_14_U_ro_fromS(_m->veh_bms_db_cell_14_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_cell_14_bal_actv_b = (uint8_t) ( ((_d[2] >> 5U) & (0x01U)) );
  _m->veh_bms_db_max_cell_U_ro = (uint16_t) ( ((_d[4] & (0x1FU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_max_cell_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_max_cell_U_ro_fromS(_m->veh_bms_db_max_cell_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_min_cell_U_ro = (uint16_t) ( ((_d[6] & (0x1FU)) << 8U) | (_d[7] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_min_cell_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_min_cell_U_ro_fromS(_m->veh_bms_db_min_cell_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_CELL_DATA_4_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_CELL_DATA_4_dbc_driver(&_m->mon1, VEH_BMS_CELL_DATA_4_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_CELL_DATA_4_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_CELL_DATA_4_dbc_driver(VEH_BMS_CELL_DATA_4_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_CELL_DATA_4_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_13_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_13_U_ro_toS(_m->veh_bms_db_cell_13_U_phys);
  _m->veh_bms_db_cell_14_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_14_U_ro_toS(_m->veh_bms_db_cell_14_U_phys);
  _m->veh_bms_db_max_cell_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_max_cell_U_ro_toS(_m->veh_bms_db_max_cell_U_phys);
  _m->veh_bms_db_min_cell_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_min_cell_U_ro_toS(_m->veh_bms_db_min_cell_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_cell_13_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_13_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[1] |= (uint8_t) ( (_m->veh_bms_db_cell_13_U_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->veh_bms_db_cell_14_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_14_bal_actv_b & (0x01U)) << 5U) );
  cframe->Data[3] |= (uint8_t) ( (_m->veh_bms_db_cell_14_U_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_max_cell_U_ro >> 8U) & (0x1FU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_max_cell_U_ro & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->veh_bms_db_min_cell_U_ro >> 8U) & (0x1FU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->veh_bms_db_min_cell_U_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_CELL_DATA_4_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_CELL_DATA_4_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_CELL_DATA_4_IDE;
  return VEH_BMS_CELL_DATA_4_CANID;
}

#else

uint32_t Pack_VEH_BMS_CELL_DATA_4_dbc_driver(VEH_BMS_CELL_DATA_4_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_CELL_DATA_4_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_cell_13_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_13_U_ro_toS(_m->veh_bms_db_cell_13_U_phys);
  _m->veh_bms_db_cell_14_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_cell_14_U_ro_toS(_m->veh_bms_db_cell_14_U_phys);
  _m->veh_bms_db_max_cell_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_max_cell_U_ro_toS(_m->veh_bms_db_max_cell_U_phys);
  _m->veh_bms_db_min_cell_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_min_cell_U_ro_toS(_m->veh_bms_db_min_cell_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_cell_13_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_13_bal_actv_b & (0x01U)) << 5U) );
  _d[1] |= (uint8_t) ( (_m->veh_bms_db_cell_13_U_ro & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->veh_bms_db_cell_14_U_ro >> 8U) & (0x1FU)) | ((_m->veh_bms_db_cell_14_bal_actv_b & (0x01U)) << 5U) );
  _d[3] |= (uint8_t) ( (_m->veh_bms_db_cell_14_U_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_max_cell_U_ro >> 8U) & (0x1FU)) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_max_cell_U_ro & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->veh_bms_db_min_cell_U_ro >> 8U) & (0x1FU)) );
  _d[7] |= (uint8_t) ( (_m->veh_bms_db_min_cell_U_ro & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_CELL_DATA_4_DLC;
  *_ide = (uint8_t) VEH_BMS_CELL_DATA_4_IDE;
  return VEH_BMS_CELL_DATA_4_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_LIMITS_1_dbc_driver(VEH_BMS_PACK_LIMITS_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_avail_chrg_1s_IA = (uint16_t) ( ((_d[0] & (0xFFU)) << 2U) | ((_d[1] >> 6U) & (0x03U)) );
  _m->veh_bms_db_avail_chrg_1s_PKW_ro = (uint16_t) ( ((_d[1] & (0x0FU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_1s_PKW_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_avail_chrg_1s_PKW_ro_fromS(_m->veh_bms_db_avail_chrg_1s_PKW_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_avail_dschrg_1s_IA_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 2U) | ((_d[4] >> 6U) & (0x03U)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_dschrg_1s_IA_phys = (int16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_1s_IA_ro_fromS(_m->veh_bms_db_avail_dschrg_1s_IA_ro);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_avail_dschrg_1s_PKW_ro = (uint16_t) ( ((_d[4] & (0x0FU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_dschrg_1s_PKW_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_avail_dschrg_1s_PKW_ro_fromS(_m->veh_bms_db_avail_dschrg_1s_PKW_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_PACK_LIMITS_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_PACK_LIMITS_1_dbc_driver(&_m->mon1, VEH_BMS_PACK_LIMITS_1_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_PACK_LIMITS_1_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_PACK_LIMITS_1_dbc_driver(VEH_BMS_PACK_LIMITS_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_LIMITS_1_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_1s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_chrg_1s_PKW_ro_toS(_m->veh_bms_db_avail_chrg_1s_PKW_phys);
  _m->veh_bms_db_avail_dschrg_1s_IA_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_1s_IA_ro_toS(_m->veh_bms_db_avail_dschrg_1s_IA_phys);
  _m->veh_bms_db_avail_dschrg_1s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_1s_PKW_ro_toS(_m->veh_bms_db_avail_dschrg_1s_PKW_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_1s_IA >> 2U) & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_1s_IA & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_chrg_1s_PKW_ro >> 8U) & (0x0FU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->veh_bms_db_avail_chrg_1s_PKW_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_1s_IA_ro >> 2U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_1s_IA_ro & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_dschrg_1s_PKW_ro >> 8U) & (0x0FU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_avail_dschrg_1s_PKW_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_PACK_LIMITS_1_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_PACK_LIMITS_1_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_PACK_LIMITS_1_IDE;
  return VEH_BMS_PACK_LIMITS_1_CANID;
}

#else

uint32_t Pack_VEH_BMS_PACK_LIMITS_1_dbc_driver(VEH_BMS_PACK_LIMITS_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_LIMITS_1_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_1s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_chrg_1s_PKW_ro_toS(_m->veh_bms_db_avail_chrg_1s_PKW_phys);
  _m->veh_bms_db_avail_dschrg_1s_IA_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_1s_IA_ro_toS(_m->veh_bms_db_avail_dschrg_1s_IA_phys);
  _m->veh_bms_db_avail_dschrg_1s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_1s_PKW_ro_toS(_m->veh_bms_db_avail_dschrg_1s_PKW_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_1s_IA >> 2U) & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_1s_IA & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_chrg_1s_PKW_ro >> 8U) & (0x0FU)) );
  _d[2] |= (uint8_t) ( (_m->veh_bms_db_avail_chrg_1s_PKW_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_1s_IA_ro >> 2U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_1s_IA_ro & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_dschrg_1s_PKW_ro >> 8U) & (0x0FU)) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_avail_dschrg_1s_PKW_ro & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_PACK_LIMITS_1_DLC;
  *_ide = (uint8_t) VEH_BMS_PACK_LIMITS_1_IDE;
  return VEH_BMS_PACK_LIMITS_1_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_LIMITS_2_dbc_driver(VEH_BMS_PACK_LIMITS_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_avail_chrg_10s_IA = (uint16_t) ( ((_d[0] & (0xFFU)) << 2U) | ((_d[1] >> 6U) & (0x03U)) );
  _m->veh_bms_db_avail_chrg_10s_PKW_ro = (uint16_t) ( ((_d[1] & (0x0FU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_10s_PKW_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_avail_chrg_10s_PKW_ro_fromS(_m->veh_bms_db_avail_chrg_10s_PKW_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_avail_dschrg_10s_IA_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 2U) | ((_d[4] >> 6U) & (0x03U)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_dschrg_10s_IA_phys = (int16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_10s_IA_ro_fromS(_m->veh_bms_db_avail_dschrg_10s_IA_ro);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_avail_dschrg_10s_PKW_ro = (uint16_t) ( ((_d[4] & (0x0FU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_dschrg_10s_PKW_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_avail_dschrg_10s_PKW_ro_fromS(_m->veh_bms_db_avail_dschrg_10s_PKW_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_PACK_LIMITS_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_PACK_LIMITS_2_dbc_driver(&_m->mon1, VEH_BMS_PACK_LIMITS_2_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_PACK_LIMITS_2_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_PACK_LIMITS_2_dbc_driver(VEH_BMS_PACK_LIMITS_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_LIMITS_2_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_10s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_chrg_10s_PKW_ro_toS(_m->veh_bms_db_avail_chrg_10s_PKW_phys);
  _m->veh_bms_db_avail_dschrg_10s_IA_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_10s_IA_ro_toS(_m->veh_bms_db_avail_dschrg_10s_IA_phys);
  _m->veh_bms_db_avail_dschrg_10s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_10s_PKW_ro_toS(_m->veh_bms_db_avail_dschrg_10s_PKW_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_10s_IA >> 2U) & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_10s_IA & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_chrg_10s_PKW_ro >> 8U) & (0x0FU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->veh_bms_db_avail_chrg_10s_PKW_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_10s_IA_ro >> 2U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_10s_IA_ro & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_dschrg_10s_PKW_ro >> 8U) & (0x0FU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_avail_dschrg_10s_PKW_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_PACK_LIMITS_2_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_PACK_LIMITS_2_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_PACK_LIMITS_2_IDE;
  return VEH_BMS_PACK_LIMITS_2_CANID;
}

#else

uint32_t Pack_VEH_BMS_PACK_LIMITS_2_dbc_driver(VEH_BMS_PACK_LIMITS_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_LIMITS_2_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_10s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_chrg_10s_PKW_ro_toS(_m->veh_bms_db_avail_chrg_10s_PKW_phys);
  _m->veh_bms_db_avail_dschrg_10s_IA_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_10s_IA_ro_toS(_m->veh_bms_db_avail_dschrg_10s_IA_phys);
  _m->veh_bms_db_avail_dschrg_10s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_10s_PKW_ro_toS(_m->veh_bms_db_avail_dschrg_10s_PKW_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_10s_IA >> 2U) & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_10s_IA & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_chrg_10s_PKW_ro >> 8U) & (0x0FU)) );
  _d[2] |= (uint8_t) ( (_m->veh_bms_db_avail_chrg_10s_PKW_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_10s_IA_ro >> 2U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_10s_IA_ro & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_dschrg_10s_PKW_ro >> 8U) & (0x0FU)) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_avail_dschrg_10s_PKW_ro & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_PACK_LIMITS_2_DLC;
  *_ide = (uint8_t) VEH_BMS_PACK_LIMITS_2_IDE;
  return VEH_BMS_PACK_LIMITS_2_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_LIMITS_3_dbc_driver(VEH_BMS_PACK_LIMITS_3_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_avail_chrg_60s_IA = (uint16_t) ( ((_d[0] & (0xFFU)) << 2U) | ((_d[1] >> 6U) & (0x03U)) );
  _m->veh_bms_db_avail_chrg_60s_PKW_ro = (uint16_t) ( ((_d[1] & (0x0FU)) << 8U) | (_d[2] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_60s_PKW_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_avail_chrg_60s_PKW_ro_fromS(_m->veh_bms_db_avail_chrg_60s_PKW_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_avail_dschrg_60s_IA_ro = (uint16_t) ( ((_d[3] & (0xFFU)) << 2U) | ((_d[4] >> 6U) & (0x03U)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_dschrg_60s_IA_phys = (int16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_60s_IA_ro_fromS(_m->veh_bms_db_avail_dschrg_60s_IA_ro);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_avail_dschrg_60s_PKW_ro = (uint16_t) ( ((_d[4] & (0x0FU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_dschrg_60s_PKW_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_avail_dschrg_60s_PKW_ro_fromS(_m->veh_bms_db_avail_dschrg_60s_PKW_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_PACK_LIMITS_3_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_PACK_LIMITS_3_dbc_driver(&_m->mon1, VEH_BMS_PACK_LIMITS_3_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_PACK_LIMITS_3_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_PACK_LIMITS_3_dbc_driver(VEH_BMS_PACK_LIMITS_3_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_LIMITS_3_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_60s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_chrg_60s_PKW_ro_toS(_m->veh_bms_db_avail_chrg_60s_PKW_phys);
  _m->veh_bms_db_avail_dschrg_60s_IA_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_60s_IA_ro_toS(_m->veh_bms_db_avail_dschrg_60s_IA_phys);
  _m->veh_bms_db_avail_dschrg_60s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_60s_PKW_ro_toS(_m->veh_bms_db_avail_dschrg_60s_PKW_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_60s_IA >> 2U) & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_60s_IA & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_chrg_60s_PKW_ro >> 8U) & (0x0FU)) );
  cframe->Data[2] |= (uint8_t) ( (_m->veh_bms_db_avail_chrg_60s_PKW_ro & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_60s_IA_ro >> 2U) & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_60s_IA_ro & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_dschrg_60s_PKW_ro >> 8U) & (0x0FU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_avail_dschrg_60s_PKW_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_PACK_LIMITS_3_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_PACK_LIMITS_3_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_PACK_LIMITS_3_IDE;
  return VEH_BMS_PACK_LIMITS_3_CANID;
}

#else

uint32_t Pack_VEH_BMS_PACK_LIMITS_3_dbc_driver(VEH_BMS_PACK_LIMITS_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_LIMITS_3_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_avail_chrg_60s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_chrg_60s_PKW_ro_toS(_m->veh_bms_db_avail_chrg_60s_PKW_phys);
  _m->veh_bms_db_avail_dschrg_60s_IA_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_60s_IA_ro_toS(_m->veh_bms_db_avail_dschrg_60s_IA_phys);
  _m->veh_bms_db_avail_dschrg_60s_PKW_ro = (uint16_t) DBC_DRIVER_veh_bms_db_avail_dschrg_60s_PKW_ro_toS(_m->veh_bms_db_avail_dschrg_60s_PKW_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_60s_IA >> 2U) & (0xFFU)) );
  _d[1] |= (uint8_t) ( ((_m->veh_bms_db_avail_chrg_60s_IA & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_chrg_60s_PKW_ro >> 8U) & (0x0FU)) );
  _d[2] |= (uint8_t) ( (_m->veh_bms_db_avail_chrg_60s_PKW_ro & (0xFFU)) );
  _d[3] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_60s_IA_ro >> 2U) & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_avail_dschrg_60s_IA_ro & (0x03U)) << 6U) | ((_m->veh_bms_db_avail_dschrg_60s_PKW_ro >> 8U) & (0x0FU)) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_avail_dschrg_60s_PKW_ro & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_PACK_LIMITS_3_DLC;
  *_ide = (uint8_t) VEH_BMS_PACK_LIMITS_3_IDE;
  return VEH_BMS_PACK_LIMITS_3_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_DATA_1_dbc_driver(VEH_BMS_PACK_DATA_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_stack_U_ro = (uint16_t) ( ((_d[0] & (0xFFU)) << 8U) | (_d[1] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_stack_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_stack_U_ro_fromS(_m->veh_bms_db_stack_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_term_U_ro = (uint16_t) ( ((_d[2] & (0xFFU)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_term_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_term_U_ro_fromS(_m->veh_bms_db_term_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_inst_I_ro = (int32_t) __ext_sig__(( ((_d[4] & (0xFFU)) << 24U) | ((_d[5] & (0xFFU)) << 16U) | ((_d[6] & (0xFFU)) << 8U) | (_d[7] & (0xFFU)) ), 32);
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_inst_I_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_inst_I_ro_fromS(_m->veh_bms_db_inst_I_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_PACK_DATA_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_PACK_DATA_1_dbc_driver(&_m->mon1, VEH_BMS_PACK_DATA_1_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_PACK_DATA_1_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_PACK_DATA_1_dbc_driver(VEH_BMS_PACK_DATA_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_DATA_1_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_stack_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_stack_U_ro_toS(_m->veh_bms_db_stack_U_phys);
  _m->veh_bms_db_term_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_term_U_ro_toS(_m->veh_bms_db_term_U_phys);
  _m->veh_bms_db_inst_I_ro = (int32_t) DBC_DRIVER_veh_bms_db_inst_I_ro_toS(_m->veh_bms_db_inst_I_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_stack_U_ro >> 8U) & (0xFFU)) );
  cframe->Data[1] |= (uint8_t) ( (_m->veh_bms_db_stack_U_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->veh_bms_db_term_U_ro >> 8U) & (0xFFU)) );
  cframe->Data[3] |= (uint8_t) ( (_m->veh_bms_db_term_U_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_inst_I_ro >> 24U) & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( ((_m->veh_bms_db_inst_I_ro >> 16U) & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( ((_m->veh_bms_db_inst_I_ro >> 8U) & (0xFFU)) );
  cframe->Data[7] |= (uint8_t) ( (_m->veh_bms_db_inst_I_ro & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_PACK_DATA_1_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_PACK_DATA_1_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_PACK_DATA_1_IDE;
  return VEH_BMS_PACK_DATA_1_CANID;
}

#else

uint32_t Pack_VEH_BMS_PACK_DATA_1_dbc_driver(VEH_BMS_PACK_DATA_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_DATA_1_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_stack_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_stack_U_ro_toS(_m->veh_bms_db_stack_U_phys);
  _m->veh_bms_db_term_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_term_U_ro_toS(_m->veh_bms_db_term_U_phys);
  _m->veh_bms_db_inst_I_ro = (int32_t) DBC_DRIVER_veh_bms_db_inst_I_ro_toS(_m->veh_bms_db_inst_I_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_stack_U_ro >> 8U) & (0xFFU)) );
  _d[1] |= (uint8_t) ( (_m->veh_bms_db_stack_U_ro & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->veh_bms_db_term_U_ro >> 8U) & (0xFFU)) );
  _d[3] |= (uint8_t) ( (_m->veh_bms_db_term_U_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_inst_I_ro >> 24U) & (0xFFU)) );
  _d[5] |= (uint8_t) ( ((_m->veh_bms_db_inst_I_ro >> 16U) & (0xFFU)) );
  _d[6] |= (uint8_t) ( ((_m->veh_bms_db_inst_I_ro >> 8U) & (0xFFU)) );
  _d[7] |= (uint8_t) ( (_m->veh_bms_db_inst_I_ro & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_PACK_DATA_1_DLC;
  *_ide = (uint8_t) VEH_BMS_PACK_DATA_1_IDE;
  return VEH_BMS_PACK_DATA_1_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

uint32_t Unpack_VEH_BMS_PACK_DATA_2_dbc_driver(VEH_BMS_PACK_DATA_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->veh_bms_db_pack_1_T_ro = (uint16_t) ( ((_d[0] & (0x07U)) << 8U) | (_d[1] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_pack_1_T_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_pack_1_T_ro_fromS(_m->veh_bms_db_pack_1_T_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_ign_b = (uint8_t) ( ((_d[0] >> 3U) & (0x01U)) );
  _m->veh_bms_db_hw_ovp_actv_b = (uint8_t) ( ((_d[0] >> 4U) & (0x01U)) );
  _m->veh_bms_db_cb_status_e = (uint8_t) ( ((_d[0] >> 6U) & (0x03U)) );
  _m->veh_bms_db_pack_2_T_ro = (uint16_t) ( ((_d[2] & (0x07U)) << 8U) | (_d[3] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_pack_2_T_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_pack_2_T_ro_fromS(_m->veh_bms_db_pack_2_T_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_pwrmon_b = (uint8_t) ( ((_d[2] >> 4U) & (0x01U)) );
  _m->veh_bms_db_lv_pwr_U_ro = (uint16_t) ( ((_d[4] & (0xFFU)) << 8U) | (_d[5] & (0xFFU)) );
#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_lv_pwr_U_phys = (sigfloat_t)(DBC_DRIVER_veh_bms_db_lv_pwr_U_ro_fromS(_m->veh_bms_db_lv_pwr_U_ro));
#endif // DBC_DRIVER_USE_SIGFLOAT

  _m->veh_bms_db_pack_soc_abs_Pct = (uint8_t) ( (_d[6] & (0xFFU)) );

#ifdef DBC_DRIVER_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_BMS_PACK_DATA_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_BMS_PACK_DATA_2_dbc_driver(&_m->mon1, VEH_BMS_PACK_DATA_2_CANID);
#endif // DBC_DRIVER_USE_DIAG_MONITORS

  return VEH_BMS_PACK_DATA_2_CANID;
}

#ifdef DBC_DRIVER_USE_CANSTRUCT

uint32_t Pack_VEH_BMS_PACK_DATA_2_dbc_driver(VEH_BMS_PACK_DATA_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_DATA_2_DLC); cframe->Data[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_pack_1_T_ro = (uint16_t) DBC_DRIVER_veh_bms_db_pack_1_T_ro_toS(_m->veh_bms_db_pack_1_T_phys);
  _m->veh_bms_db_pack_2_T_ro = (uint16_t) DBC_DRIVER_veh_bms_db_pack_2_T_ro_toS(_m->veh_bms_db_pack_2_T_phys);
  _m->veh_bms_db_lv_pwr_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_lv_pwr_U_ro_toS(_m->veh_bms_db_lv_pwr_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  cframe->Data[0] |= (uint8_t) ( ((_m->veh_bms_db_pack_1_T_ro >> 8U) & (0x07U)) | ((_m->veh_bms_db_ign_b & (0x01U)) << 3U) | ((_m->veh_bms_db_hw_ovp_actv_b & (0x01U)) << 4U) | ((_m->veh_bms_db_cb_status_e & (0x03U)) << 6U) );
  cframe->Data[1] |= (uint8_t) ( (_m->veh_bms_db_pack_1_T_ro & (0xFFU)) );
  cframe->Data[2] |= (uint8_t) ( ((_m->veh_bms_db_pack_2_T_ro >> 8U) & (0x07U)) | ((_m->veh_bms_db_pwrmon_b & (0x01U)) << 4U) );
  cframe->Data[3] |= (uint8_t) ( (_m->veh_bms_db_pack_2_T_ro & (0xFFU)) );
  cframe->Data[4] |= (uint8_t) ( ((_m->veh_bms_db_lv_pwr_U_ro >> 8U) & (0xFFU)) );
  cframe->Data[5] |= (uint8_t) ( (_m->veh_bms_db_lv_pwr_U_ro & (0xFFU)) );
  cframe->Data[6] |= (uint8_t) ( (_m->veh_bms_db_pack_soc_abs_Pct & (0xFFU)) );

  cframe->MsgId = (uint32_t) VEH_BMS_PACK_DATA_2_CANID;
  cframe->DLC = (uint8_t) VEH_BMS_PACK_DATA_2_DLC;
  cframe->IDE = (uint8_t) VEH_BMS_PACK_DATA_2_IDE;
  return VEH_BMS_PACK_DATA_2_CANID;
}

#else

uint32_t Pack_VEH_BMS_PACK_DATA_2_dbc_driver(VEH_BMS_PACK_DATA_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0u; i < DBC_DRIVER_VALIDATE_DLC(VEH_BMS_PACK_DATA_2_DLC); _d[i++] = DBC_DRIVER_INITIAL_BYTE_VALUE);

#ifdef DBC_DRIVER_USE_SIGFLOAT
  _m->veh_bms_db_pack_1_T_ro = (uint16_t) DBC_DRIVER_veh_bms_db_pack_1_T_ro_toS(_m->veh_bms_db_pack_1_T_phys);
  _m->veh_bms_db_pack_2_T_ro = (uint16_t) DBC_DRIVER_veh_bms_db_pack_2_T_ro_toS(_m->veh_bms_db_pack_2_T_phys);
  _m->veh_bms_db_lv_pwr_U_ro = (uint16_t) DBC_DRIVER_veh_bms_db_lv_pwr_U_ro_toS(_m->veh_bms_db_lv_pwr_U_phys);
#endif // DBC_DRIVER_USE_SIGFLOAT

  _d[0] |= (uint8_t) ( ((_m->veh_bms_db_pack_1_T_ro >> 8U) & (0x07U)) | ((_m->veh_bms_db_ign_b & (0x01U)) << 3U) | ((_m->veh_bms_db_hw_ovp_actv_b & (0x01U)) << 4U) | ((_m->veh_bms_db_cb_status_e & (0x03U)) << 6U) );
  _d[1] |= (uint8_t) ( (_m->veh_bms_db_pack_1_T_ro & (0xFFU)) );
  _d[2] |= (uint8_t) ( ((_m->veh_bms_db_pack_2_T_ro >> 8U) & (0x07U)) | ((_m->veh_bms_db_pwrmon_b & (0x01U)) << 4U) );
  _d[3] |= (uint8_t) ( (_m->veh_bms_db_pack_2_T_ro & (0xFFU)) );
  _d[4] |= (uint8_t) ( ((_m->veh_bms_db_lv_pwr_U_ro >> 8U) & (0xFFU)) );
  _d[5] |= (uint8_t) ( (_m->veh_bms_db_lv_pwr_U_ro & (0xFFU)) );
  _d[6] |= (uint8_t) ( (_m->veh_bms_db_pack_soc_abs_Pct & (0xFFU)) );

  *_len = (uint8_t) VEH_BMS_PACK_DATA_2_DLC;
  *_ide = (uint8_t) VEH_BMS_PACK_DATA_2_IDE;
  return VEH_BMS_PACK_DATA_2_CANID;
}

#endif // DBC_DRIVER_USE_CANSTRUCT

