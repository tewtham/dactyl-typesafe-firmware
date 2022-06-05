#ifndef Reader_h
#define Reader_h

#include "./constants.h"

class Reader_ {
  public:
    Reader_();
    void init(void);
    bool state[6][6];
    void updateState(void);
};

extern Reader_ Reader;

#endif
