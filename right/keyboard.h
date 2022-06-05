#ifndef FiveXSix_h
#define FiveXSix_h

#define NUM_KEYS 54

#define NUM_ROWS 6
#define NUM_COLUMNS 12

// ======================= LAYER 0 ==============================
#define LAYER_0_LEFT \
esc    , keyQ   , keyW   , keyE   , keyR   , keyT   , \
minus  , keyA   , keyS   , keyD   , keyF   , keyG   , \
tab    , keyZ   , keyX   , keyC   , keyV   , keyB   , \
gui    , tilde  , equal  , alt    ,                   \
                           backsp , space  , del    , \
alt, ctrl, shift, gui

#define LAYER_0_RIGHT \
keyY   , keyU   , keyI   , keyO   , keyP   , backsl , \
keyH   , keyJ   , keyK   , keyL   , semicl , quote  , \
keyN   , keyM   , comma  , period , slash  , shift  , \
lftBrc , rgtBrc , ctrl   , shift  ,                   \
layer  , enter  , endl

// ======================= LAYER 1 ==============================
#define LAYER_1_LEFT \
esc    , scrollX, unused , up     , unused , unused, \
minus  , scrollY, left   , down   , right  , unused, \
tab    , unused , keyX   , keyC   , keyV   , unused, \
gui    , unused , unused , alt    ,                   \
                           backsp , space  , del   , \
alt, ctrl, shift, gui

#define LAYER_1_RIGHT \
scrollX, unused , unused , unused , clrbnd , battpr, \
scrollY, mouseL , mouseM , mouseR , unused , unused, \
unused , unused , unused , unused , unused , unused, \
unused , unused , ctrl   , shift  ,                  \
layer  , enter  , endl

// ======================= LAYER 2 ==============================
#define LAYER_2_LEFT \
minus  , bang   , at     , hash   , dola   , perc   , \
esc    , key1   , key2   , key3   , key4   , key5   , \
shift  , unused , unused , unused , unused , unused , \
gui    , unused , unused , alt    ,                   \
                           backsp , space  , del    , \
vup, nex, vdwn, prev

#define LAYER_2_RIGHT \
cart   , amp    , ast    , lpar   , rpar   , unde   , \
key6   , key7   , key8   , key9   , key0   , minus  , \
unused , unused , unused , period , unused , unused , \
nex    , vdwn   , vup    , ply    ,                   \
layer  , unused , unused

#define LAYER_KEYS {{LAYER_0_LEFT,LAYER_0_RIGHT},{LAYER_1_LEFT,LAYER_1_RIGHT},{LAYER_2_LEFT,LAYER_2_RIGHT}}

// Map state col/row to an index in the layout
#define KEY_MAP { \
  {18,19,20,21,-1,-1,     50,49,48,47,-1,-1}, \
  {12,13,14,15,16,17,     46,45,44,43,42,41}, \
  { 6, 7, 8, 9,10,11,     40,39,38,37,36,35}, \
  { 0, 1, 2, 3, 4, 5,     34,33,32,31,30,29}, \
  {-1,-1,22,24,-1,23,     -1,-1,52,51,-1,53}, \
  {-1,-1,25,27,26,28,     -1,-1,-1,-1,-1,-1}  \
}

#endif
