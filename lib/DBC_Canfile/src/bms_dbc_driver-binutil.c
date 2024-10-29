// Generator version : v3.1
// DBC filename      : Pony_V2.dbc
#include "bms_dbc_driver-binutil.h"

// DBC file version
#if (VER_DBC_DRIVER_MAJ != (0U)) || (VER_DBC_DRIVER_MIN != (0U))
#error The BMS_DBC_DRIVER binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_BMS_DBC_DRIVER__

bms_dbc_driver_rx_t bms_dbc_driver_rx;

bms_dbc_driver_tx_t bms_dbc_driver_tx;

#endif // __DEF_BMS_DBC_DRIVER__

uint32_t bms_dbc_driver_Receive(bms_dbc_driver_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if (_id == 0x500U) {
  recid = Unpack_VEH_MSG_TO_BMS_dbc_driver(&(_m->VEH_MSG_TO_BMS), _d, dlc_);
 } else if (_id == 0x501U) {
  recid = Unpack_VEH_CRASH_dbc_driver(&(_m->VEH_CRASH), _d, dlc_);
 }

 return recid;
}

