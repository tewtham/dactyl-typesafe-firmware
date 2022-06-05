#ifndef Reader_h
#define Reader_h

#include "./constants.h"
#include "./keyboard.h"

class Reader_ {
  public:
    Reader_();
    void init(void);
    bool state[NUM_ROWS][NUM_COLUMNS];
    void updateState(void);
};

extern Reader_ Reader;

#endif
