#pragma once

#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "theme.h"
#include "fonts.h"
#include "touch.h"
#include "utils.h"
#include "elements.h"

SDL_Window *WINDOW;
SDL_Surface *WINDOW_SURFACE;
SDL_Renderer *RENDERER;

char *TITLE;
bool DRAW_DIVIDERS;
bool DRAW_TITLE;

int LAST_KEY;

int CONTENT_X;
int CONTENT_Y;
int ELEMENT_FOCUS;
bool SIDEBAR_FOCUS;

u32 kDown;

int PUI_Init(void);
void PUI_SetTitle(char* title);
void PUI_DrawDividers(bool draw);
void PUI_DrawTitle(bool draw);
void PUI_Update(void);
bool PUI_KeyScan(int breakKey);
void PUI_Present(void);
void PUI_Close(void);