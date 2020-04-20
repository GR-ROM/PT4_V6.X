/***************************************************
 * GraphicsConfig.h
 ***************************************************/
#ifndef _GRAPHICSCONFIG_H
#define _GRAPHICSCONFIG_H

//////////////////// COMPILE OPTIONS AND DEFAULTS ////////////////////

////////////  HARDWARE PROFILE /////////////
#include "HardwareProfile.h"
/////////////// FONT OPTIONS ////////////////
// Support for fonts located in internal flash
#define USE_FONT_FLASH
// Support for fonts located in external memory
//#define USE_FONT_EXTERNAL

////////////// BITMAP OPTIONS ///////////////
// Support for bitmaps located in internal flash
#define USE_BITMAP_FLASH
// Support for bitmaps located in external memory
//#define USE_BITMAP_EXTERNAL

///////////////// DRIVER ////////////////////

#include "Graphics\SCREEN_DRV.h"

#endif // _GRAPHICSCONFIG_H
 