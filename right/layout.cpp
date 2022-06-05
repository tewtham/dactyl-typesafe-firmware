#include <bluefruit.h>
#include "./layout.h"
#include "./keys.h"
#include "./keyboard_dev.h"
#include "./ble.h"
#include "./adns.h"

// these macros (LAYER_KEYS and KEY_MAP) are from either "4x6.h" or "5x6.h" depending on what's in "keyboard.h"
const Key layerKeys [3][NUM_KEYS] = LAYER_KEYS;
const int8_t keyMap [NUM_ROWS][NUM_COLUMNS] = KEY_MAP;

Layout_::Layout_() {
  mouseModifiers = 0x00;
  currentLayer = 1;
  mouseButtons = 0x0;
}

void Layout_::init(void) {
  SplitKeyboard.begin();

  while(!SplitKeyboard.isConnected() ) delay(100);
  
  for (int i = 0; i < NUM_KEYS; i++) {
    pressedLayer[i] = -1;
  }
}

void Layout_::btnPress(uint8_t row, uint8_t col) {
  int index = keyMap[row][col];
  pressedLayer[index] = currentLayer;
  Key key = layerKeys[currentLayer][index];

  switch(key.type) {
    case STANDARD_KEY:
    case KEY_MOD:
      SplitKeyboard.press(key.code);
      break;
    case MOUSE_MOD:
      mouseModifiers |= key.code;
      Adns.setModifiers(mouseModifiers);
      break;
    case MOUSE_BUTTON:
      mouseButtons |= key.code;
      setMouseButtons();
      break;
    case BATTERY_PRINT:
      char buffer[15];
      sprintf(buffer, "%u%%:%u%% ", readLeftBattery(), readBattery());
      SplitKeyboard.print(buffer);
      break;
    case CLEAR_BONDS:
      Bluefruit.clearBonds();
      break;
    case TO_LAYER:
      setLayer(2);
      break;
    case MEDIA_KEY:
      SplitKeyboard.mediaPress(key.code);
      break;
  }
}

uint8_t Layout_::getLayer() {
  return currentLayer;
}


void Layout_::setLayer(uint8_t layer) {
  SplitKeyboard.releaseAll();
  currentLayer = layer;
}

void Layout_::btnRelease(uint8_t row, uint8_t col) {
  int index = keyMap[row][col];
  if (pressedLayer[index] == -1) pressedLayer[index] = currentLayer;
  Key key = layerKeys[currentLayer][index];

  switch(key.type) {
    case STANDARD_KEY:
    case KEY_MOD:
      SplitKeyboard.release(key.code);
      break;
    case MOUSE_MOD:
      mouseModifiers &= ~key.code;
      Adns.setModifiers(mouseModifiers);
      break;
    case MOUSE_BUTTON:
      mouseButtons &= ~key.code;
      setMouseButtons();
      break;
    case TO_LAYER:
      setLayer(0);
      break;
    case MEDIA_KEY:
      SplitKeyboard.mediaRelease();
      break;
  }
  pressedLayer[index] = -1;
}

void Layout_::setMouseButtons(void) {
  SplitMouse.setButtons(mouseButtons);
}

Layout_ Layout;
