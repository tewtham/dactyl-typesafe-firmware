#ifndef Keys_h
#define Keys_h

#include "./constants.h"

#define STANDARD_KEY 0x01 // standard key
#define MOUSE_BUTTON 0x02 // mouse button
#define MOUSE_MOD 0x03 // mouse modifier
#define KEY_MOD 0x04 // modifier
#define TO_LAYER 0x05 // to layer. when pressed, switch to layer 2. when released, switch to layer 0.
#define UNUSED 0x06
#define BATTERY_PRINT 0x07
#define CLEAR_BONDS 0x08
#define MEDIA_KEY 0x09

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4
#define MOUSE_ALL (MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE)

#define KEY_LEFT_CTRL   0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT    0x82
#define KEY_LEFT_GUI    0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT   0x86
#define KEY_RIGHT_GUI   0x87

#define KEY_UP_ARROW    0xDA
#define KEY_DOWN_ARROW    0xD9
#define KEY_LEFT_ARROW    0xD8
#define KEY_RIGHT_ARROW   0xD7
#define KEY_BACKSPACE   0xB2
#define KEY_TAB       0xB3
#define KEY_RETURN      0xB0
#define KEY_ESC       0xB1
#define KEY_INSERT      0xD1
#define KEY_DELETE      0xD4
#define KEY_PAGE_UP     0xD3
#define KEY_PAGE_DOWN   0xD6
#define KEY_HOME      0xD2
#define KEY_END       0xD5
#define KEY_CAPS_LOCK   0xC1
#define KEY_F1        0xC2
#define KEY_F2        0xC3
#define KEY_F3        0xC4
#define KEY_F4        0xC5
#define KEY_F5        0xC6
#define KEY_F6        0xC7
#define KEY_F7        0xC8
#define KEY_F8        0xC9
#define KEY_F9        0xCA
#define KEY_F10       0xCB
#define KEY_F11       0xCC
#define KEY_F12       0xCD
#define KEY_F13       0xF0
#define KEY_F14       0xF1
#define KEY_F15       0xF2
#define KEY_F16       0xF3
#define KEY_F17       0xF4
#define KEY_F18       0xF5
#define KEY_F19       0xF6
#define KEY_F20       0xF7
#define KEY_F21       0xF8
#define KEY_F22       0xF9
#define KEY_F23       0xFA
#define KEY_F24       0xFB

class Key {
  public:
    Key(uint8_t t) {
        code = 0;
        type = t;
    }
    Key(uint8_t t, char c) {
      code = c;
      type = t;
    }
    static Key standard(char code) {
      return Key(STANDARD_KEY, code);
    }
    uint8_t type;
    char code; // TODO: uint16_t so we can supoprt all the consumer control codes
};

// when pressed, switch to layer 2. when released, switch to layer 0.
// layer 1 is reached by moving the mouse
Key layer = Key(TO_LAYER);
Key unused = Key(UNUSED);
Key battpr = Key(BATTERY_PRINT);
Key clrbnd = Key(CLEAR_BONDS);

Key mouseL = Key(MOUSE_BUTTON, MOUSE_LEFT);
Key mouseM = Key(MOUSE_BUTTON, MOUSE_MIDDLE);
Key mouseR = Key(MOUSE_BUTTON, MOUSE_RIGHT);

Key scrollX = Key(MOUSE_MOD, MOUSEMOD_SCROLLX);
Key scrollY = Key(MOUSE_MOD, MOUSEMOD_SCROLLY);

Key alt     = Key(KEY_MOD, KEY_LEFT_ALT);
Key ctrl    = Key(KEY_MOD, KEY_LEFT_CTRL);
Key gui     = Key(KEY_MOD, KEY_LEFT_GUI);
Key shift   = Key(KEY_MOD, KEY_LEFT_SHIFT);

Key backsl  = Key::standard('\\');
Key backsp  = Key::standard(KEY_BACKSPACE);
Key comma   = Key::standard(',');
Key del     = Key::standard(KEY_DELETE);
Key down    = Key::standard(KEY_DOWN_ARROW);

// TODO: fixme
Key endl     = Key::standard(KEY_END);
Key enter   = Key::standard(KEY_RETURN);
Key equal   = Key::standard('=');
Key esc     = Key::standard(KEY_ESC);
Key home    = Key::standard(KEY_HOME);
Key left    = Key::standard(KEY_LEFT_ARROW);
Key lftBrc  = Key::standard('[');
Key minus   = Key::standard('-');
Key period  = Key::standard('.');
Key quote   = Key::standard('\'');
Key rgtBrc  = Key::standard(']');
Key right   = Key::standard(KEY_RIGHT_ARROW);
Key semicl  = Key::standard(';');
Key slash   = Key::standard('/');
Key space   = Key::standard(' ');
Key tab     = Key::standard(KEY_TAB);
Key tilde   = Key::standard('`');
Key up      = Key::standard(KEY_UP_ARROW);

Key f1  = Key::standard(KEY_F1);
Key f2  = Key::standard(KEY_F2);
Key f3  = Key::standard(KEY_F3);
Key f4  = Key::standard(KEY_F4);
Key f5  = Key::standard(KEY_F5);
Key f6  = Key::standard(KEY_F6);
Key f7  = Key::standard(KEY_F7);
Key f8  = Key::standard(KEY_F8);
Key f9  = Key::standard(KEY_F9);
Key f10 = Key::standard(KEY_F10);

Key key0 = Key::standard('0');
Key key1 = Key::standard('1');
Key key2 = Key::standard('2');
Key key3 = Key::standard('3');
Key key4 = Key::standard('4');
Key key5 = Key::standard('5');
Key key6 = Key::standard('6');
Key key7 = Key::standard('7');
Key key8 = Key::standard('8');
Key key9 = Key::standard('9');
Key keyA = Key::standard('a');
Key keyB = Key::standard('b');
Key keyC = Key::standard('c');
Key keyD = Key::standard('d');
Key keyE = Key::standard('e');
Key keyF = Key::standard('f');
Key keyG = Key::standard('g');
Key keyH = Key::standard('h');
Key keyI = Key::standard('i');
Key keyJ = Key::standard('j');
Key keyK = Key::standard('k');
Key keyL = Key::standard('l');
Key keyM = Key::standard('m');
Key keyN = Key::standard('n');
Key keyO = Key::standard('o');
Key keyP = Key::standard('p');
Key keyQ = Key::standard('q');
Key keyR = Key::standard('r');
Key keyS = Key::standard('s');
Key keyT = Key::standard('t');
Key keyU = Key::standard('u');
Key keyV = Key::standard('v');
Key keyW = Key::standard('w');
Key keyX = Key::standard('x');
Key keyY = Key::standard('y');
Key keyZ = Key::standard('z');

Key bang = Key::standard(0x21);
Key at = Key::standard(0x40);
Key hash = Key::standard(0x23);
Key dola = Key::standard(0x24);
Key perc = Key::standard(0x25);
Key cart = Key::standard(0x5E);
Key amp = Key::standard(0x26);
Key ast = Key::standard(0x2A);
Key lpar = Key::standard(0x28);
Key rpar = Key::standard(0x29);
Key unde = Key::standard(0x5F);

// https://github.com/adafruit/Adafruit_TinyUSB_Arduino/blob/a3e9ccbe889af3de4813d918d6df0fb75c4b7477/src/class/hid/hid.h#L811
Key ply = Key(MEDIA_KEY, HID_USAGE_CONSUMER_PLAY_PAUSE);
Key vup = Key(MEDIA_KEY, HID_USAGE_CONSUMER_VOLUME_INCREMENT);
Key vdwn = Key(MEDIA_KEY, HID_USAGE_CONSUMER_VOLUME_DECREMENT);
Key nex = Key(MEDIA_KEY, HID_USAGE_CONSUMER_SCAN_NEXT);
Key prev = Key(MEDIA_KEY, HID_USAGE_CONSUMER_SCAN_PREVIOUS);

#endif
