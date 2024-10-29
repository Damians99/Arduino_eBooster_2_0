// Generator version : v3.1
// DBC filename      : Pony_V2.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// DBC file version
#define VER_DBC_DRIVER_MAJ_FMON (0U)
#define VER_DBC_DRIVER_MIN_FMON (0U)

#include "dbc_driver-config.h"

#ifdef DBC_DRIVER_USE_DIAG_MONITORS

#include "canmonitorutil.h"
/*
This file contains the prototypes of all the functions that will be called
from each Unpack_*name* function to detect DBC related errors
It is the user responsibility to defined these functions in the
separated .c file. If it won't be done the linkage error will happen
*/

#ifdef DBC_DRIVER_USE_MONO_FMON

void _FMon_MONO_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);

#define FMon_EBOOSTER_DATA_AND_FAULT_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_TO_EBOOSTER_CONTROL_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_EBOOSTER_GENERAL_DATA_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_MSG_TO_BMS_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_CRASH_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_STATUS_1_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_STATUS_2_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_CELL_DATA_1_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_CELL_DATA_2_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_CELL_DATA_3_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_CELL_DATA_4_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_LIMITS_1_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_LIMITS_2_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_LIMITS_3_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_DATA_1_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_DATA_2_dbc_driver(x, y) _FMon_MONO_dbc_driver((x), (y))

#else

void _FMon_EBOOSTER_DATA_AND_FAULT_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_TO_EBOOSTER_CONTROL_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_EBOOSTER_GENERAL_DATA_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_MSG_TO_BMS_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_CRASH_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_PACK_STATUS_1_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_PACK_STATUS_2_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_CELL_DATA_1_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_CELL_DATA_2_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_CELL_DATA_3_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_CELL_DATA_4_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_PACK_LIMITS_1_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_PACK_LIMITS_2_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_PACK_LIMITS_3_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_PACK_DATA_1_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);
void _FMon_VEH_BMS_PACK_DATA_2_dbc_driver(FrameMonitor_t* _mon, uint32_t msgid);

#define FMon_EBOOSTER_DATA_AND_FAULT_dbc_driver(x, y) _FMon_EBOOSTER_DATA_AND_FAULT_dbc_driver((x), (y))
#define FMon_VEH_TO_EBOOSTER_CONTROL_dbc_driver(x, y) _FMon_VEH_TO_EBOOSTER_CONTROL_dbc_driver((x), (y))
#define FMon_EBOOSTER_GENERAL_DATA_dbc_driver(x, y) _FMon_EBOOSTER_GENERAL_DATA_dbc_driver((x), (y))
#define FMon_VEH_MSG_TO_BMS_dbc_driver(x, y) _FMon_VEH_MSG_TO_BMS_dbc_driver((x), (y))
#define FMon_VEH_CRASH_dbc_driver(x, y) _FMon_VEH_CRASH_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_STATUS_1_dbc_driver(x, y) _FMon_VEH_BMS_PACK_STATUS_1_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_STATUS_2_dbc_driver(x, y) _FMon_VEH_BMS_PACK_STATUS_2_dbc_driver((x), (y))
#define FMon_VEH_BMS_CELL_DATA_1_dbc_driver(x, y) _FMon_VEH_BMS_CELL_DATA_1_dbc_driver((x), (y))
#define FMon_VEH_BMS_CELL_DATA_2_dbc_driver(x, y) _FMon_VEH_BMS_CELL_DATA_2_dbc_driver((x), (y))
#define FMon_VEH_BMS_CELL_DATA_3_dbc_driver(x, y) _FMon_VEH_BMS_CELL_DATA_3_dbc_driver((x), (y))
#define FMon_VEH_BMS_CELL_DATA_4_dbc_driver(x, y) _FMon_VEH_BMS_CELL_DATA_4_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_LIMITS_1_dbc_driver(x, y) _FMon_VEH_BMS_PACK_LIMITS_1_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_LIMITS_2_dbc_driver(x, y) _FMon_VEH_BMS_PACK_LIMITS_2_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_LIMITS_3_dbc_driver(x, y) _FMon_VEH_BMS_PACK_LIMITS_3_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_DATA_1_dbc_driver(x, y) _FMon_VEH_BMS_PACK_DATA_1_dbc_driver((x), (y))
#define FMon_VEH_BMS_PACK_DATA_2_dbc_driver(x, y) _FMon_VEH_BMS_PACK_DATA_2_dbc_driver((x), (y))

#endif

#endif // DBC_DRIVER_USE_DIAG_MONITORS

#ifdef __cplusplus
}
#endif
