// Generator version : v3.1
// DBC filename      : Pony_V2.dbc
#include "ebooster_dbc_driver-binutil.h"

// DBC file version
#if (VER_DBC_DRIVER_MAJ != (0U)) || (VER_DBC_DRIVER_MIN != (0U))
#error The EBOOSTER_DBC_DRIVER binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_EBOOSTER_DBC_DRIVER__

ebooster_dbc_driver_rx_t ebooster_dbc_driver_rx;

ebooster_dbc_driver_tx_t ebooster_dbc_driver_tx;

#endif // __DEF_EBOOSTER_DBC_DRIVER__

uint32_t ebooster_dbc_driver_Receive(ebooster_dbc_driver_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if (_id == 0x6DU) {
  recid = Unpack_VEH_TO_EBOOSTER_CONTROL_dbc_driver(&(_m->VEH_TO_EBOOSTER_CONTROL), _d, dlc_);
 }

 return recid;
}

