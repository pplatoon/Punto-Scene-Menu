#include "theme.h"

void PUI_Theme_Init(PUI_Theme_Preset preset) {
  if (preset == PUI_THEME_DARK) {
    THEME = (PUI_Theme) {
      .textColor = PUI_MakeColor(255, 255, 255), // Unclear, somewhere around this range (Went with highest values)
      .backgroundColor = PUI_MakeColor(45, 45, 45),
      .accentColor = PUI_MakeColor(0, 255, 197),
      .sidebarColor = PUI_MakeColor(50, 50, 50),
      .sidebarDivColor = PUI_MakeColor(81, 81, 79),
      .dividerColor = PUI_MakeColor(255, 255, 255),
      .offTextColor = PUI_MakeColor(158, 158, 158),
      .touchOutlineColor = PUI_MakeColor(43, 147, 200)
    };
  } else {
    THEME = (PUI_Theme) {
      .textColor = PUI_MakeColor(45, 45, 45),
      .backgroundColor = PUI_MakeColor(235, 235, 235),
      .accentColor = PUI_MakeColor(50, 80, 236),
      .sidebarColor = PUI_MakeColor(240, 240, 240),
      .sidebarDivColor = PUI_MakeColor(208, 208, 208),
      .dividerColor = PUI_MakeColor(45, 45, 45),
      .offTextColor = PUI_MakeColor(158, 158, 158),
      .touchOutlineColor = PUI_MakeColor(24, 210, 200)
    };
  }
}