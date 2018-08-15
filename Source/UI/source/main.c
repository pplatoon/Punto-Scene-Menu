#include <switch.h>
#include <sys/socket.h>
#include "../lib/precisionui.h"

int main(int argc, char **argv) {
  PUI_Init();
  PUI_DrawDividers(true);
  PUI_DrawTitle(true);
  PUI_SetTitle("Punto Scene Menu");
  while(appletMainLoop()) {
    PUI_Update();
    PUI_Element_Sidebar(6, "Test", "Test2", "Test 3", "~~~DIVIDER~~~", "test 4", "Test 5");
    char* str = "Index";
    if (SIDEBAR_INDEX == 1) {
      str = "Segundo";
    } else if (SIDEBAR_INDEX == 2) {
      str = "Tercero";
    } else if (SIDEBAR_INDEX == 4) {
      str = "Now you're on the fourth, and you jumped over the divider!";
    } else if (SIDEBAR_INDEX == 5) {
      str = "Quinto";
    }
    char* str2 = "Not tapped";
    u32 touch_count = hidTouchCount();
    PUI_Element_Divider();
    PUI_Element_Label(InterUI_Regular, str, true);
    PUI_Element_Divider();
    int testBtn = PUI_Element_Button(InterUI_Regular, "test", true);
    PUI_Touch_Element_Touching(touch_count);
    PUI_Element testBtnEl = ELEMENTS[testBtn];
    if (testBtnEl.tapped) str2 = "Tapped!";
    PUI_Element_Divider();
    PUI_Element_Label(InterUI_Regular, str2, true);
    PUI_Element_Divider();
    bool exitFlag = PUI_KeyScan(KEY_PLUS);
    PUI_Present();
    // NOTE: Properly check for an element's tapped variable after running both PUI_Touch_Element_Touching and PUI_KeyScan
    //       above it will only display tapped when it is physically tapped on the touch screen
    if (exitFlag) break;
  }
  PUI_Close();
  return 0;
}