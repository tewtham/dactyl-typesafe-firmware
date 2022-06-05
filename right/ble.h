#ifndef BLE_h
#define BLE_h
#include <bluefruit.h>

#define BLE_CENTRAL false

extern BLEHidAdafruit blehid;

extern BLEDis bledis;
extern BLEBas blebas;
void ble_init(void);

uint8_t readBattery(void);
uint8_t readLeftBattery(void);
#endif
