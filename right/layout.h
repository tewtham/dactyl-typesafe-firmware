#ifndef Layout_h
#define Layout_h

#include <stdint.h>
#include "./reader.h"
#include "./constants.h"
#include "./keyboard.h"

class Layout_ {
  private:
    uint8_t currentLayer;
    uint8_t mouseButtons;
    void setMouseButtons(void);
    uint8_t mouseModifiers;
    int pressedLayer[NUM_KEYS];
  public:
    Layout_();
    bool state[NUM_ROWS][NUM_COLUMNS];
    void init(void);
    void updateState();
    uint8_t getLayer();
    void setLayer(uint8_t);
    void btnPress(uint8_t, uint8_t);
    void btnRelease(uint8_t, uint8_t);
};

extern Layout_ Layout;

#endif
