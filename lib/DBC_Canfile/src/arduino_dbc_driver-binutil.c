// Generator version : v3.1
// DBC filename      : Pony_V2.dbc
#include "arduino_dbc_driver-binutil.h"

// DBC file version
#if (VER_DBC_DRIVER_MAJ != (0U)) || (VER_DBC_DRIVER_MIN != (0U))
#error The ARDUINO_DBC_DRIVER binutil source file has inconsistency with core dbc lib!
#endif

#ifdef __DEF_ARDUINO_DBC_DRIVER__

arduino_dbc_driver_rx_t arduino_dbc_driver_rx;

arduino_dbc_driver_tx_t arduino_dbc_driver_tx;

#endif // __DEF_ARDUINO_DBC_DRIVER__

uint32_t arduino_dbc_driver_Receive(arduino_dbc_driver_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0x6BU) && (_id < 0x612U)) {
  if ((_id >= 0x6BU) && (_id < 0x601U)) {
   if (_id == 0x6BU) {
    recid = Unpack_EBOOSTER_DATA_AND_FAULT_dbc_driver(&(_m->EBOOSTER_DATA_AND_FAULT), _d, dlc_);
   } else {
    if (_id == 0x17BU) {
     recid = Unpack_EBOOSTER_GENERAL_DATA_dbc_driver(&(_m->EBOOSTER_GENERAL_DATA), _d, dlc_);
    } else if (_id == 0x600U) {
     recid = Unpack_VEH_BMS_PACK_STATUS_1_dbc_driver(&(_m->VEH_BMS_PACK_STATUS_1), _d, dlc_);
    }
   }
  } else {
   if (_id == 0x601U) {
    recid = Unpack_VEH_BMS_PACK_STATUS_2_dbc_driver(&(_m->VEH_BMS_PACK_STATUS_2), _d, dlc_);
   } else {
    if (_id == 0x610U) {
     recid = Unpack_VEH_BMS_CELL_DATA_1_dbc_driver(&(_m->VEH_BMS_CELL_DATA_1), _d, dlc_);
    } else if (_id == 0x611U) {
     recid = Unpack_VEH_BMS_CELL_DATA_2_dbc_driver(&(_m->VEH_BMS_CELL_DATA_2), _d, dlc_);
    }
   }
  }
 } else {
  if ((_id >= 0x612U) && (_id < 0x621U)) {
   if (_id == 0x612U) {
    recid = Unpack_VEH_BMS_CELL_DATA_3_dbc_driver(&(_m->VEH_BMS_CELL_DATA_3), _d, dlc_);
   } else {
    if (_id == 0x613U) {
     recid = Unpack_VEH_BMS_CELL_DATA_4_dbc_driver(&(_m->VEH_BMS_CELL_DATA_4), _d, dlc_);
    } else if (_id == 0x620U) {
     recid = Unpack_VEH_BMS_PACK_LIMITS_1_dbc_driver(&(_m->VEH_BMS_PACK_LIMITS_1), _d, dlc_);
    }
   }
  } else {
   if ((_id >= 0x621U) && (_id < 0x630U)) {
    if (_id == 0x621U) {
     recid = Unpack_VEH_BMS_PACK_LIMITS_2_dbc_driver(&(_m->VEH_BMS_PACK_LIMITS_2), _d, dlc_);
    } else if (_id == 0x622U) {
     recid = Unpack_VEH_BMS_PACK_LIMITS_3_dbc_driver(&(_m->VEH_BMS_PACK_LIMITS_3), _d, dlc_);
    }
   } else {
    if (_id == 0x630U) {
     recid = Unpack_VEH_BMS_PACK_DATA_1_dbc_driver(&(_m->VEH_BMS_PACK_DATA_1), _d, dlc_);
    } else if (_id == 0x631U) {
     recid = Unpack_VEH_BMS_PACK_DATA_2_dbc_driver(&(_m->VEH_BMS_PACK_DATA_2), _d, dlc_);
    }
   }
  }
 }

 return recid;
}

