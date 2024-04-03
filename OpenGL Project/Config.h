#pragma once

#define ENGINE_SETTING_DISPLAY_MODEL

//#define ENGINE_SETTING_MAIN

//defaults to display model.
#ifdef ENGINE_SETTING_DISPLAY_MODEL
#undef ENGINE_SETTING_MAIN
#endif
