// Generator version : v3.1
#pragma once

#include <stdint.h>

// when USE_SIGFLOAT enabed the sigfloat_t must be defined
// typedef double sigfloat_t;

// when USE_CANSTRUCT enabled __CoderDbcCanFrame_t__ must be defined
// #include "{header_with_can_struct}"
// typedef {can_struct} __CoderDbcCanFrame_t__;

/*typedef union {
 uint64_t int64;
 uint32_t int32[2];
 uint16_t int16[4];
 uint8_t int8[8];
 unsigned char character[8];
} BytesUnion;*/


typedef struct {
	uint32_t MsgId;		// 29 bit if ide set, 11 bit otherwise
	uint32_t fid;				// family ID - used internally to library
	uint8_t IDE;			// Extended ID flag
	uint8_t rtr; 				// Remote Transmission Request (1 = RTR, 0 = data frame)
	uint8_t priority;			// Priority but only for TX frames and optional (0-31)
	uint32_t time; 				// CAN timer value when mailbox message was received
	uint8_t DLC;				// Number of data bytes
	union {
        uint8_t Data[8];    	// Ermöglicht direkten Zugriff über `frame.Data[3]`
        unsigned char charData[8]; // Alternativer Zugriff für spezialisierte Darstellung
    };
} CanFrame;

typedef CanFrame __CoderDbcCanFrame_t__;


// if you need to allocate rx and tx messages structs put the allocation macro here
// #define __DEF_{your_driver_name}__
#define __DEF_ARDUINO_DBC_DRIVER__


// defualt @__ext_sig__ help types definition

typedef uint32_t ubitext_t;
typedef int32_t bitext_t;

// To provide a way to make missing control correctly you
// have to define macro @GetSystemTick() which has to
// return kind of tick counter (e.g. 1 ms ticker)

// #define GetSystemTick() __get__tick__()

// To provide a way to calculate hash (crc) for CAN
// frame's data field you have to define macro @GetFrameHash

// #define GetFrameHash(a,b,c,d,e) __get_hash__(a,b,c,d,e)

