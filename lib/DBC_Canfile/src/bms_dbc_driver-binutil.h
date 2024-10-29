// Generator version : v3.1
// DBC filename      : Pony_V2.dbc
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "dbc_driver.h"

typedef struct
{
  VEH_MSG_TO_BMS_t VEH_MSG_TO_BMS;
  VEH_CRASH_t VEH_CRASH;
} bms_dbc_driver_rx_t;

typedef struct
{
  VEH_BMS_PACK_STATUS_1_t VEH_BMS_PACK_STATUS_1;
  VEH_BMS_PACK_STATUS_2_t VEH_BMS_PACK_STATUS_2;
  VEH_BMS_CELL_DATA_1_t VEH_BMS_CELL_DATA_1;
  VEH_BMS_CELL_DATA_2_t VEH_BMS_CELL_DATA_2;
  VEH_BMS_CELL_DATA_3_t VEH_BMS_CELL_DATA_3;
  VEH_BMS_CELL_DATA_4_t VEH_BMS_CELL_DATA_4;
  VEH_BMS_PACK_LIMITS_1_t VEH_BMS_PACK_LIMITS_1;
  VEH_BMS_PACK_LIMITS_2_t VEH_BMS_PACK_LIMITS_2;
  VEH_BMS_PACK_LIMITS_3_t VEH_BMS_PACK_LIMITS_3;
  VEH_BMS_PACK_DATA_1_t VEH_BMS_PACK_DATA_1;
  VEH_BMS_PACK_DATA_2_t VEH_BMS_PACK_DATA_2;
} bms_dbc_driver_tx_t;

uint32_t bms_dbc_driver_Receive(bms_dbc_driver_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_BMS_DBC_DRIVER__

extern bms_dbc_driver_rx_t bms_dbc_driver_rx;

extern bms_dbc_driver_tx_t bms_dbc_driver_tx;

#endif // __DEF_BMS_DBC_DRIVER__

#ifdef __cplusplus
}
#endif
