#ifndef BLEServer_h
#define BLEServer_h

#include <bluefruit.h>

class BLEServer_ {
  private:
    BLEService service;
    BLECharacteristic keyupdate;
    BLECharacteristic battery;
  public:
    BLEServer_();
    void init(void);
    void btnPress(uint8_t row, uint8_t col);
    void btnRelease(uint8_t row, uint8_t col);
    void writeBattery(void);
};

void writeBattery(void);

extern BLEServer_ BLEServer;
#endif
