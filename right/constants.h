#ifndef Constants_h
#define Constants_h

#include "./pins.h"

#define DEBOUNCE_MS 12
#define SERVICE_ID 0xaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
#define UPDATE_ID 0xbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb
#define BATTERY_ID 0xcccccccccccccccccccccccccccccccc

#define MOUSEMOD_SCROLLX 0x01
#define MOUSEMOD_SCROLLY 0x02

// pin assignments

// ADNS-9800
#define MOT_PIN P1_06
#define CS_PIN P0_22

// nice nano
#define VBAT_PIN P0_04

#define NICE_ROW_0 P0_31
#define NICE_ROW_1 P0_29
#define NICE_ROW_2 P0_02
#define NICE_ROW_3 P1_15
#define NICE_ROW_4 P0_09
#define NICE_ROW_5 P0_06

#define NICE_COL_0 P0_17
#define NICE_COL_1 P0_20
#define NICE_COL_2 P0_24
#define NICE_COL_3 P1_00
#define NICE_COL_4 P0_11
#define NICE_COL_5 P1_04

#endif
