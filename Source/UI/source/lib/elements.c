#include "elements.h"

/*
 * Item Start Coords = (100, 140)
 * Accent Bar = (88, 129) (91, 180) w,h(91-88, 180-129) = (3, 51)
 * Next = (101, 246)
 * Spacing = 70px
 */
void calcSidebarAccentBar(int x, int y, int *resX, int *resY) {
  // *resX = x - (100 - 88);
  // *resY = y - (140 - 129);
  *resX = x - 12;
  *resY = y - 11; 
}
int calcSidebarDivY(int y) {
  int accBarY = y - 11;
  return accBarY + 25;
}
char* PUI_Element_Sidebar_GetItem(int idx) {
  return SIDEBAR_LIST[idx];
}
void PUI_Element_Sidebar(int sz, ...) { // Will always draw on the left side of the screen
  PUI_DrawRectangle(0, 88, 409, 646 - 88, THEME.sidebarColor); // draw the sidebar background
  int i;
  int lastY = (140 - 70);
  va_list valist;
  va_start(valist, sz);
  SIDEBAR_LENGTH = sz - 1;
  for (i = 0; i < sz; i++)   { // loop through variable arguments
    char *str = va_arg(valist, char*);
    int newY = lastY + 70;
    SIDEBAR_LIST[i] = str;
    if (strcmp(str, "~~~DIVIDER~~~") == 0) {
      if (SIDEBAR_INDEX == i) {
        if (LAST_KEY == KEY_UP) SIDEBAR_INDEX--;
        if (LAST_KEY == KEY_DOWN) SIDEBAR_INDEX++;
        if (SIDEBAR_INDEX > SIDEBAR_LENGTH) SIDEBAR_INDEX = 0;
      }
      int divY = calcSidebarDivY(lastY + 50);
      PUI_DrawLine(80, divY, 380, divY, THEME.sidebarDivColor);
      lastY = lastY + 40; 
    } else {
      int accBarX;
      int accBarY;
      calcSidebarAccentBar(100, newY, &accBarX, &accBarY);
      SDL_Color textColor = THEME.textColor;
      if (i == SIDEBAR_INDEX) {
        textColor = THEME.accentColor;
        SIDEBAR_SEL = str;        
        PUI_DrawRectangle(accBarX, accBarY, 3, 51, THEME.accentColor);
      }
      SIDEBAR_X1[i] = accBarX;
      SIDEBAR_Y1[i] = accBarY;
      SIDEBAR_X2[i] = accBarX + 222;
      SIDEBAR_Y2[i] = accBarY + 51;
      PUI_DrawString(InterUI_Regular, 100, newY, textColor, str);
      lastY = newY;
    }
  }
  va_end(valist);
  SIDEBAR_DRAWN = true;
  CONTENT_X = 469;
  CONTENT_Y = 130;  
}

int PUI_Element_Divider(void) { // create a divider on the list
  int idx = ELEMENT_INDEX + 1;
  int x = 0;
  int y = 0;
  PUI_Element lastEl = ELEMENTS[idx - 1];
  if (idx == 0) {
    x = CONTENT_X;
    y = CONTENT_Y;
  } else if (lastEl.id == 1) {
    x = CONTENT_X;
    y = lastEl.y + 71;
  } else /*if (lastEl.id == 2 || lastEl.id == 3 || lastEl.id == 4 || lastEl.id == 5) */ {
    if ((idx - 2) < 0) {
      x = CONTENT_X;
      y = CONTENT_Y;
    } else {
      PUI_Element last2El = ELEMENTS[idx - 2];
      x = CONTENT_X;
      y = last2El.y2 + 71;
    }
  }
  ELEMENTS[idx] = (PUI_Element) {
    .id = 1,
    .x = x,
    .y = y,
    .x1 = x,
    .y1 = y,
    .x2 = x,
    .y2 = y,
    .canTap = false
  };
  if (!lastEl.tapped && !lastEl.focused) PUI_DrawLine(x, y, x + 720, y, THEME.sidebarDivColor);
  ELEMENT_INDEX = idx;
  return idx;
}

int PUI_Element_Label(TTF_Font *font, char* text, bool centered) {
  int idx = ELEMENT_INDEX + 1;
  int x = 0;
  int y = 0;
  PUI_Element lastEl = ELEMENTS[idx - 1];

  if (idx == 0) {
    x = CONTENT_X;
    y = CONTENT_Y;
  } else if (lastEl.id == 1) {
    x = lastEl.x;
    y = lastEl.y;
  } else {
    x = lastEl.x;
    y = lastEl.y + 71;
  }
  if (centered) {
    y = y + 20;
    x = x + 15;
  }
  ELEMENTS[idx] = (PUI_Element) {
    .id = 3,
    .x = x,
    .y = y,
    .x1 = x,
    .y1 = y,
    .x2 = x,
    .y2 = y,
    .canTap = false
  };
  PUI_DrawString(font, x, y, THEME.offTextColor, text);
  ELEMENT_INDEX = idx;
  return idx;
}

int PUI_Element_Button(TTF_Font *font, char* text, bool centered) {
  int idx = ELEMENT_INDEX + 1;
  int x = 0;
  int y = 0;
  int x2 = 0;
  int y2 = 0;
  PUI_Element lastEl = ELEMENTS[idx - 1];

  if (idx == 0) {
    x = CONTENT_X;
    y = CONTENT_Y;
  } else if (lastEl.id == 1) {
    x = lastEl.x;
    y = lastEl.y;
  } else {
    x = lastEl.x;
    y = lastEl.y + 71;
  }
  x2 = x + 720;
  y2 = y + 71;
  if (centered) y = y + 20;
  x = x + 15;
  bool focused = false;
  if (ELEMENT_FOCUS == idx && !SIDEBAR_FOCUS) {
    focused = true;
    int w = x2 - (x - 15);
    int h = y2 - (y - 20);
    PUI_DrawRectangleOutlineRepeat(x - 15, y - 20, w, h, 5, THEME.touchOutlineColor);
  }

  ELEMENTS[idx] = (PUI_Element) {
    .id = 5,
    .x = x,
    .y = y,
    .x1 = x,
    .y1 = y,
    .x2 = x2,
    .y2 = y2,
    .canTap = true,
    .canFocus = true,
    .tapped = false,
    .focused = focused,
    .boolMeta = centered
  };
  PUI_DrawString(font, x, y, THEME.textColor, text);
  ELEMENT_INDEX = idx;
  return idx;
}