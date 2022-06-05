#include "./ble_server.h"
#include "./reader.h"

void setup() {
  Serial.begin(115200);
  Serial.println("init start");
  
  BLEServer.init();
  Reader.init();
  Serial.println("init complete");
}

uint32_t battimer = 0;
void loop() {
  Reader.updateState();
  if (battimer++ > 24000) {
    // Serial.println("writing battery");
    BLEServer.writeBattery();
    battimer = 0;
  }
}
