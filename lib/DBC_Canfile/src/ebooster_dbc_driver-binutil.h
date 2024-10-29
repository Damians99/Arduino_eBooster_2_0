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
  VEH_TO_EBOOSTER_CONTROL_t VEH_TO_EBOOSTER_CONTROL;
} ebooster_dbc_driver_rx_t;

typedef struct
{
  EBOOSTER_DATA_AND_FAULT_t EBOOSTER_DATA_AND_FAULT;
  EBOOSTER_GENERAL_DATA_t EBOOSTER_GENERAL_DATA;
} ebooster_dbc_driver_tx_t;

uint32_t ebooster_dbc_driver_Receive(ebooster_dbc_driver_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_EBOOSTER_DBC_DRIVER__

extern ebooster_dbc_driver_rx_t ebooster_dbc_driver_rx;

extern ebooster_dbc_driver_tx_t ebooster_dbc_driver_tx;

#endif // __DEF_EBOOSTER_DBC_DRIVER__

#ifdef __cplusplus
}
#endif
