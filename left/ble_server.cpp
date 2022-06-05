#include "./ble_server.h"
#include "./constants.h"

BLEDis bledis;

BLEServer_::BLEServer_() {
  service = BLEService(SERVICE_ID);
  keyupdate = BLECharacteristic(UPDATE_ID);
  battery = BLECharacteristic(BATTERY_ID);
}

void BLEServer_::init(void) {
  Bluefruit.begin();
  Bluefruit.setName("dactyl left");

  // device information service
  bledis.setManufacturer("dactyl left");
  bledis.setModel("dactyl left");
  bledis.begin();

  service.begin();

  keyupdate.setProperties(CHR_PROPS_NOTIFY);
  keyupdate.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  keyupdate.setFixedLen(3);
  keyupdate.begin();

  battery.setProperties(CHR_PROPS_NOTIFY);
  battery.setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  battery.setFixedLen(1);
  battery.begin();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(service);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void BLEServer_::btnPress(uint8_t row, uint8_t col) {
  uint8_t d[3] = { row, col, 1 };
  keyupdate.notify(d, sizeof(d));
}

void BLEServer_::btnRelease(uint8_t row, uint8_t col) {
  uint8_t d[3] = { row, col, 0 };
  keyupdate.notify(d, sizeof(d));
}

uint32_t readVDDH() {
  int16_t value = 0;
  NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_10bit;

  NRF_SAADC->ENABLE = (SAADC_ENABLE_ENABLE_Enabled << SAADC_ENABLE_ENABLE_Pos);
  for (int i = 0; i < 8; i++) 
  {
      NRF_SAADC->CH[i].PSELN = SAADC_CH_PSELP_PSELP_NC;
      NRF_SAADC->CH[i].PSELP = SAADC_CH_PSELP_PSELP_NC;
  }
  NRF_SAADC->CH[0].CONFIG =   ((SAADC_CH_CONFIG_RESP_Bypass     << SAADC_CH_CONFIG_RESP_Pos)   & SAADC_CH_CONFIG_RESP_Msk)
                              | ((SAADC_CH_CONFIG_RESP_Bypass     << SAADC_CH_CONFIG_RESN_Pos)   & SAADC_CH_CONFIG_RESN_Msk)
                              | ((SAADC_CH_CONFIG_GAIN_Gain1_2    << SAADC_CH_CONFIG_GAIN_Pos)   & SAADC_CH_CONFIG_GAIN_Msk)
                              | ((SAADC_CH_CONFIG_REFSEL_Internal << SAADC_CH_CONFIG_REFSEL_Pos) & SAADC_CH_CONFIG_REFSEL_Msk)
                              | ((SAADC_CH_CONFIG_TACQ_3us        << SAADC_CH_CONFIG_TACQ_Pos)   & SAADC_CH_CONFIG_TACQ_Msk)
                              | ((SAADC_CH_CONFIG_MODE_SE         << SAADC_CH_CONFIG_MODE_Pos)   & SAADC_CH_CONFIG_MODE_Msk);
  NRF_SAADC->CH[0].PSELN = SAADC_CH_PSELP_PSELP_VDDHDIV5;
  NRF_SAADC->CH[0].PSELP = SAADC_CH_PSELP_PSELP_VDDHDIV5;


  NRF_SAADC->RESULT.PTR = (uint32_t)&value;
  NRF_SAADC->RESULT.MAXCNT = 1; // One sample

  NRF_SAADC->TASKS_START = 0x01UL;

  while (!NRF_SAADC->EVENTS_STARTED);
  NRF_SAADC->EVENTS_STARTED = 0x00UL;

  NRF_SAADC->TASKS_SAMPLE = 0x01UL;

  while (!NRF_SAADC->EVENTS_END);
  NRF_SAADC->EVENTS_END = 0x00UL;
  NRF_SAADC->TASKS_STOP = 0x01UL;

  while (!NRF_SAADC->EVENTS_STOPPED);
  NRF_SAADC->EVENTS_STOPPED = 0x00UL;

  // Serial.print("value: ");
  // Serial.println(value, DEC);

  if (value < 0) 
  {
      value = 0;
  }

  NRF_SAADC->ENABLE = (SAADC_ENABLE_ENABLE_Disabled << SAADC_ENABLE_ENABLE_Pos);
  return value;
}

uint8_t readBattery(void) {
  analogReference(AR_INTERNAL_3_0);
  analogReadResolution(12);
  delay(1);
  uint32_t mvolts = readVDDH() * 5;
  analogReference(AR_DEFAULT);
  analogReadResolution(10);

  // Serial.print(mvolts, DEC);
  // Serial.print(" volts");

  if(mvolts < 3300) return 0;

  uint8_t percent;
  if(mvolts < 3600) {
    mvolts -= 3300;
    percent = mvolts/30;
  }
  
  mvolts -= 3600;
  percent = (uint8_t) 10 + (uint8_t)((mvolts * 15)/100);
  if (percent > 100){
    percent = 100;
  }

  return percent;
};

void BLEServer_::writeBattery(void) {
  uint8_t percentage = readBattery();
  // Serial.print(percentage, DEC);
  // Serial.println("%");
  uint8_t d[1] = { percentage };
  battery.notify(d, sizeof(d));
}

BLEServer_ BLEServer;
