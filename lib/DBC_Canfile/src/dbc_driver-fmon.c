// Generator version : v3.1
// DBC filename      : Pony_V2.dbc
#include "dbc_driver-fmon.h"

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

/*
Put the monitor function content here, keep in mind -
next generation will completely clear all manually added code (!)
*/

#ifdef DBC_DRIVER_USE_MONO_FMON

void _FMon_MONO_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

#else

void _FMon_EBOOSTER_DATA_AND_FAULT_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_TO_EBOOSTER_CONTROL_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_EBOOSTER_GENERAL_DATA_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_MSG_TO_BMS_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_CRASH_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_PACK_STATUS_1_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_PACK_STATUS_2_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_CELL_DATA_1_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_CELL_DATA_2_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_CELL_DATA_3_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_CELL_DATA_4_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_PACK_LIMITS_1_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_PACK_LIMITS_2_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_PACK_LIMITS_3_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_PACK_DATA_1_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

void _FMon_VEH_BMS_PACK_DATA_2_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid)
{
  (void)_mon;
  (void)msgid;
}

#endif // DBC_DRIVER_USE_MONO_FMON

#endif // DBC_DRIVER_USE_DIAG_MONITORS
