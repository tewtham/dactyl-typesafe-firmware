#include <bluefruit.h>
#include "ble.h"
#include "./constants.h"
#include "./layout.h"

BLEClientService bleclient_client(SERVICE_ID);
BLEClientCharacteristic bleclient_keyupdate(UPDATE_ID);
BLEClientCharacteristic batterypercent(BATTERY_ID);

BLEBas blebas;
BLEHidAdafruit blehid;
BLEDis bledis;

void start_advertising(void) {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_MOUSE);
  #if BLE_CENTRAL
  Bluefruit.Advertising.addService(blehid);
  #endif
  Bluefruit.Advertising.addService(blebas);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

void scan_callback(ble_gap_evt_adv_report_t* report) {
  Bluefruit.Central.connect(report);
}

void connect_callback(uint16_t conn_handle) {
  Serial.println("connected");

  if (!bleclient_client.discover(conn_handle)) {
    Serial.println("service not found");
    Bluefruit.disconnect(conn_handle);
    return;
  }

  if (!bleclient_keyupdate.discover() || !batterypercent.discover()) {
    Serial.println("chars not found");
    Bluefruit.disconnect(conn_handle);
    return;
  }

  bleclient_keyupdate.enableNotify();
  batterypercent.enableNotify();
  #if BLE_CENTRAL
  start_advertising();
  #endif
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason) {
  (void) conn_handle;
  (void) reason;

  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}

uint8_t _leftbattery = 0;

void batterypercent_notify_callback(BLEClientCharacteristic* chr, uint8_t* data, uint16_t len) {
  Serial.print("battery update ");
  Serial.println(data[0], DEC);
  _leftbattery = data[0];
}

void keyupdate_notify_callback(BLEClientCharacteristic* chr, uint8_t* data, uint16_t len) {
  Serial.print("key update ");
  Serial.print(data[0], DEC);
  Serial.print(" ");
  Serial.print(data[1], DEC);
  Serial.print(" ");
  Serial.println(data[2], DEC);

  if (data[2] == 1) {
    Layout.btnPress(data[0], data[1]);
  } else {
    Layout.btnRelease(data[0], data[1]);
  }
}

uint8_t readLeftBattery(void) {
  return _leftbattery;
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

  Serial.print("value: ");
  Serial.println(value, DEC);

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

  Serial.print(mvolts, DEC);
  Serial.print(" volts");

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

void ble_init() {
  #if BLE_CENTRAL
  Bluefruit.begin(1, 1);
  Bluefruit.Periph.setConnInterval(9, 16);
  Bluefruit.setTxPower(4);
  Bluefruit.setName("dactyl typesafe");
  
  // device information service
  bledis.setManufacturer("dactyl typesafe");
  bledis.setModel("dactyl typesafe");
  bledis.begin();
  
  // battery service
  blebas.begin();
  blebas.write(100);
  
  // hid service
  blehid.begin();
  #else
  Bluefruit.begin(0, 1);
  Bluefruit.Periph.setConnInterval(9, 16);
  Bluefruit.setTxPower(4);
  #endif

  bleclient_client.begin();
  bleclient_keyupdate.setNotifyCallback(keyupdate_notify_callback);
  bleclient_keyupdate.begin();
  batterypercent.setNotifyCallback(batterypercent_notify_callback);
  batterypercent.begin();
  
  Bluefruit.setConnLedInterval(250);
  Bluefruit.Central.setConnectCallback(connect_callback);
  Bluefruit.Central.setDisconnectCallback(disconnect_callback);

  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.filterUuid(bleclient_client.uuid);
  Bluefruit.Scanner.useActiveScan(false);
  Bluefruit.Scanner.start(0);
}
