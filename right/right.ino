#include "./ble.h"
#include "./layout.h"
#include "./reader.h"
#include "./adns.h"

void setup() {
  Serial.begin(115200);
  Serial.println("init start");
  ble_init();
  Layout.init();
  Reader.init();
  Adns.init();
  Serial.println("init complete");
}

uint8_t _ucounter = 0;
uint32_t battimer = 0;

void loop() {
  Reader.updateState();
  Adns.updateState();
  #if BLE_CENTRAL
  delay(20);
  #endif
}
