#pragma once
#include "precisionui.h"

typedef struct {
  SDL_Color textColor;
  SDL_Color backgroundColor;
  SDL_Color accentColor;
  SDL_Color sidebarColor;
  SDL_Color sidebarDivColor;
  SDL_Color dividerColor;
  SDL_Color offTextColor;
  SDL_Color touchOutlineColor;
} PUI_Theme;

typedef enum {
  PUI_THEME_DARK,
  PUI_THEME_LIGHT
} PUI_Theme_Preset;

void PUI_Theme_Init(PUI_Theme_Preset preset);

PUI_Theme THEME;