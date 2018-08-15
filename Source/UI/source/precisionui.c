#include "precisionui.h"

int PUI_Init(void) {
  romfsInit();
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_CreateWindowAndRenderer(1280, 720, 0, &WINDOW, &RENDERER);
  SDL_SetRenderDrawBlendMode(RENDERER, SDL_BLENDMODE_BLEND);
  WINDOW_SURFACE = SDL_GetWindowSurface(WINDOW);
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
  PUI_Font_Init();

  ColorSetId theme;
  setsysInitialize();
  setsysGetColorSetId(&theme);

  PUI_Theme_Init(theme == ColorSetId_Dark ? PUI_THEME_DARK : PUI_THEME_LIGHT);

  TITLE = "Example";
  DRAW_DIVIDERS = true;
  DRAW_TITLE = true;
  CONTENT_X = 35;
  CONTENT_Y = 107;
  SIDEBAR_DRAWN = false;
  SIDEBAR_INDEX = 0;
  ELEMENT_INDEX = -1;
  SIDEBAR_FOCUS = true;
  ELEMENT_FOCUS = 0;
  return 0;
}

void PUI_SetTitle(char* title) {
  TITLE = title;
}

void PUI_DrawDividers(bool draw) {
  DRAW_DIVIDERS = draw;
}

void PUI_DrawTitle(bool draw) {
  DRAW_TITLE = draw;
}

/*
 * Element Indexes 
 * 0: sidebar
 */
void PUI_Update(void) {
  PUI_ClearScreen();
  SDL_RenderClear(RENDERER);
  int i;
  memset(ELEMENTS, 0, sizeof(ELEMENTS));
  ELEMENT_INDEX = -1;
  CONTENT_X = 35;
  CONTENT_Y = 107;
  SIDEBAR_DRAWN = false;
  if (DRAW_DIVIDERS) {
    PUI_DrawLine(30, 87, 1249, 87, THEME.dividerColor);
    PUI_DrawLine(30, 647, 1249, 647, THEME.dividerColor);
  }
  if (DRAW_TITLE) {
    PUI_DrawString(Title_Font, 72, 30, THEME.textColor, TITLE);
  }
  
  u32 touch_count = hidTouchCount();
  int sidebar_touched = PUI_Touch_Sidebar_Touching(touch_count);
  if (sidebar_touched > -1) SIDEBAR_INDEX = sidebar_touched;
}

bool PUI_KeyScan(int breakKey) {
  hidScanInput();
  kDown = hidKeysDown(CONTROLLER_P1_AUTO);
  if (kDown & breakKey) return true;
  if (SIDEBAR_FOCUS) {
    if (kDown & KEY_UP) {
      LAST_KEY = KEY_UP;
      SIDEBAR_INDEX--;
      if (SIDEBAR_INDEX < 0) SIDEBAR_INDEX = 0;
    } else if (kDown & KEY_DOWN) {
      LAST_KEY = KEY_DOWN;
      SIDEBAR_INDEX++;
      if (SIDEBAR_INDEX > SIDEBAR_LENGTH) SIDEBAR_INDEX = SIDEBAR_LENGTH;
    } else if (kDown & KEY_RIGHT) {
      SIDEBAR_FOCUS = false;
    }
  } else {
    PUI_Element curElem = ELEMENTS[ELEMENT_FOCUS];
    bool cycled;
    while (!curElem.canFocus) {
      ELEMENT_FOCUS++;
      curElem = ELEMENTS[ELEMENT_FOCUS];
      if (ELEMENT_FOCUS > ELEMENT_INDEX) {
        ELEMENT_FOCUS = 0;
        cycled = true;
      }
      //if (cycled) break;
    }
    if (kDown & KEY_LEFT) {
      SIDEBAR_FOCUS = true;
    } if (kDown & KEY_UP) {
      ELEMENT_FOCUS--;
      if (ELEMENT_FOCUS < 0) ELEMENT_FOCUS = 0;
      curElem = ELEMENTS[ELEMENT_FOCUS];
      while (!curElem.canFocus) {
        ELEMENT_FOCUS--;
        if (ELEMENT_FOCUS < 0) {
          ELEMENT_FOCUS = 0;
          cycled = true;
        }
        curElem = ELEMENTS[ELEMENT_FOCUS];
        if (cycled) break;
      }
    } else if (kDown & KEY_DOWN) {
      ELEMENT_FOCUS++;
      if (ELEMENT_FOCUS > ELEMENT_INDEX) ELEMENT_FOCUS = 0;
      curElem = ELEMENTS[ELEMENT_FOCUS];
      while (!curElem.canFocus) {
        ELEMENT_FOCUS++;
        if (ELEMENT_FOCUS > ELEMENT_INDEX) {
          ELEMENT_FOCUS = 0;
          cycled = true;
        }
        curElem = ELEMENTS[ELEMENT_FOCUS];
        if (cycled) break;
      }
    } else if (kDown & KEY_A) {
      if (curElem.canTap) {
        curElem.tapped = true;
        ELEMENTS[ELEMENT_FOCUS] = curElem;
      }
    }
  }
  return false;
}

void PUI_Present(void) {
  SDL_RenderPresent(RENDERER);
}

void PUI_Close(void) {
  PUI_Font_Close();
  SDL_DestroyRenderer(RENDERER);
  SDL_FreeSurface(WINDOW_SURFACE);
  SDL_DestroyWindow(WINDOW);
  SDL_Quit();
  romfsExit();
}