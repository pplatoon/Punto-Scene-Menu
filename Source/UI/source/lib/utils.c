#include "utils.h"

void PUI_ClearScreen(void) {
  SDL_SetRenderDrawColor(RENDERER, THEME.backgroundColor.r, THEME.backgroundColor.g, THEME.backgroundColor.b, 255);
  SDL_RenderClear(RENDERER);
}
void writeToFile(char* text) {
  FILE *f = fopen("sdmc:/test.txt", "a+");
  fprintf(f, text, "\n");
  fclose(f);
}
SDL_Color PUI_MakeColor(Uint8 r, Uint8 g, Uint8 b) {
  SDL_Color color = {r, g, b, 255};
  return color;
}
SDL_Color PUI_MakeColorRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_Color color = {r, g, b, a};
  return color;
}

void PUI_DrawString(TTF_Font *font, int x, int y, SDL_Color color, char *string) {
  SDL_SetRenderDrawColor(RENDERER, color.r, color.g, color.b, 255);
  SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, string, color, 1280);
  SDL_SetSurfaceAlphaMod(surface, 255);
  SDL_Rect pos = {x, y, surface->w, surface->h};
  SDL_BlitSurface(surface, NULL, WINDOW_SURFACE, &pos);
  SDL_FreeSurface(surface);
}

void PUI_DrawRectangle(int x, int y, int w, int h, SDL_Color color) {
	SDL_Rect rect = {x, y, w, h};
	SDL_SetRenderDrawColor(RENDERER, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(RENDERER, &rect);
}
void PUI_DrawRectangleOutline(int x, int y, int w, int h, SDL_Color color) {
  SDL_Rect rect = {x, y, w, h};
  SDL_SetRenderDrawColor(RENDERER, color.r, color.g, color.b, 255);
  SDL_RenderDrawRect(RENDERER, &rect);
}
void PUI_DrawRectangleOutlineRepeat(int x, int y, int w, int h, int repeat, SDL_Color color) {
  PUI_DrawRectangle(x, y, repeat, h, color); // --> |_| left side of rect
  PUI_DrawRectangle(x, y, w, repeat, color); // top side of rect
  PUI_DrawRectangle(x + w, y, repeat, h, color); // |_| <-- right side of rect
  PUI_DrawRectangle(x, y + h, w + repeat, repeat, color); // bottom side of rect
}
void PUI_DrawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
  SDL_SetRenderDrawColor(RENDERER, color.r, color.g, color.b, 255);
  SDL_RenderDrawLine(RENDERER, x1, y1, x2, y2);
}