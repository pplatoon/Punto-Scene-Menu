#include "touch.h"

bool PUI_Touch_Touching(u32 touch_count, int x1, int y1, int x2, int y2) {
  touchPosition touch;
  int i;
  for (i = 0; i < touch_count; i++) {
    hidTouchRead(&touch, i);
    u32 x = touch.px;
    u32 y = touch.py;
    if (x1 <= x && x <= x2 && y1 <= y && y <= y2) return true;
  }
  return false;
}

int PUI_Touch_Sidebar_Touching(u32 touch_count) {
  int i;
  int x1;
  int y1;
  int x2;
  int y2;
  for (i = 0; i < SIDEBAR_LENGTH + 1; i++) {
    x1 = SIDEBAR_X1[i];
    y1 = SIDEBAR_Y1[i];
    x2 = SIDEBAR_X2[i];
    y2 = SIDEBAR_Y2[i];
    if (PUI_Touch_Touching(touch_count, x1, y1, x2, y2)) return i;
  }
  return -1;
}

int PUI_Touch_Element_Touching(u32 touch_count) {
  int i;
  int x1;
  int y1;
  int x2;
  int y2;
  for (i = 0; i < (ELEMENT_INDEX + 1); i++) {
    PUI_Element elem = ELEMENTS[i];
    if (!elem.canTap) continue;
    x1 = elem.x1;
    y1 = elem.y1;
    x2 = elem.x2;
    y2 = elem.y2;
    if (PUI_Touch_Touching(touch_count, x1, y1, x2, y2)) {
      elem.tapped = true;
      ELEMENTS[i] = elem;
      if (elem.id == 5) {
        x1 = x1 - 15;
        if (elem.boolMeta) y1 = y1 - 20;
        int w = x2 - x1;
        int h = y2 - y1;
        PUI_DrawRectangleOutlineRepeat(x1, y1, w, h, 5, THEME.touchOutlineColor);
      }
      return i;
    }
  }
  return -1;
}