#ifndef USB_KEYBOARD_h
#define USB_KEYBOARD_h

#include <Arduino.h>

class SplitMouse_ {
  private:
    uint8_t _b;
    void report(int8_t x, int8_t y, int8_t scroll, int8_t pan);
  public:
    SplitMouse_(void);
    void begin(void);
    void mouseMove(int8_t x, int8_t y) {
      report(x,y,0,0);
    }
    void mouseScroll(int8_t scroll) {
      report(0,0,scroll,0);
    }
    void mousePan(int8_t pan) {
      report(0,0,0,pan);
    }
    void setButtons(uint8_t b) {
      _b = b;
      report(0,0,0,0);
    }
};
extern SplitMouse_ SplitMouse;

typedef struct {
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class SplitKeyboard_ : public Print {
  private:
    KeyReport _keyReport;
    void sendReport(KeyReport* keys);
  public:
    SplitKeyboard_(void);
    bool isConnected(void);
    void mediaPress(uint8_t key);
    void mediaRelease(void);
    void begin(void);
    void end(void);
    size_t write(uint8_t k);
    size_t write(const uint8_t *buffer, size_t size);
    size_t press(uint8_t k);
    size_t release(uint8_t k);
    void releaseAll(void);
    void updateState(void);
};
extern SplitKeyboard_ SplitKeyboard;

#endif
