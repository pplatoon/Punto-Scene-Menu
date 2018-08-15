#pragma once
#include "precisionui.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void PUI_ClearScreen(void);
void writeToFile(char *text);
SDL_Color PUI_MakeColor(Uint8 r, Uint8 g, Uint8 b);
SDL_Color PUI_MakeColorRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void PUI_DrawString(TTF_Font *font, int x, int y, SDL_Color color, char *string);
void PUI_DrawRectangle(int x, int y, int w, int h, SDL_Color color);
void PUI_DrawRectangleOutline(int x, int y, int w, int h, SDL_Color color);
void PUI_DrawRectangleOutlineRepeat(int x, int y, int w, int h, int repeat, SDL_Color color);
void PUI_DrawLine(int x1, int y1, int x2, int y2, SDL_Color color);