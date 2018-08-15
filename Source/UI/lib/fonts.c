#include "fonts.h"

int PUI_Font_Init(void) {
  TTF_Init();
  InterUI_Regular = TTF_OpenFont("romfs:/Inter-UI-Regular.ttf", 24);
  InterUI_Regular_Large = TTF_OpenFont("romfs:/Inter-UI-Regular.ttf", 32);
  InterUI_Regular_Italic = TTF_OpenFont("romfs:/Inter-UI-Italic.ttf", 24);
  InterUI_Regular_Italic_Large = TTF_OpenFont("romfs:/Inter-UI-Italic.ttf", 32);

  InterUI_Medium = TTF_OpenFont("romfs:/Inter-UI-Medium.ttf", 24);
  InterUI_Medium_Large = TTF_OpenFont("romfs:/Inter-UI-Medium.ttf", 32);
  InterUI_Medium_Italic = TTF_OpenFont("romfs:/Inter-UI-MediumItalic.ttf", 24);
  InterUI_Medium_Italic_Large = TTF_OpenFont("romfs:/Inter-UI-MediumItalic.ttf", 32);

  InterUI_Bold = TTF_OpenFont("romfs:/Inter-UI-Bold.ttf", 24);
  InterUI_Bold_Large = TTF_OpenFont("romfs:/Inter-UI-Bold.ttf", 32);
  InterUI_Bold_Italic = TTF_OpenFont("romfs:/Inter-UI-BoldItalic.ttf", 24);
  InterUI_Bold_Italic_Large = TTF_OpenFont("romfs:/Inter-UI-BoldItalic.ttf", 32);

  InterUI_Black = TTF_OpenFont("romfs:/Inter-UI-Black.ttf", 24);
  InterUI_Black_Large = TTF_OpenFont("romfs:/Inter-UI-Black.ttf", 32);
  InterUI_Black_Italic = TTF_OpenFont("romfs:/Inter-UI-BlackItalic.ttf", 24);
  InterUI_Black_Italic_Large = TTF_OpenFont("romfs:/Inter-UI-BlackItalic.ttf", 32);

  Title_Font = TTF_OpenFont("romfs:/Inter-UI-Medium.ttf", 36);
  return 0;
}

void PUI_Font_Close(void) {
  // TODO: Simplify closing fonts
  TTF_CloseFont(InterUI_Regular);
  TTF_CloseFont(InterUI_Regular_Large);
  TTF_CloseFont(InterUI_Regular_Italic);
  TTF_CloseFont(InterUI_Regular_Italic_Large);

  TTF_CloseFont(InterUI_Medium);
  TTF_CloseFont(InterUI_Medium_Large);
  TTF_CloseFont(InterUI_Medium_Italic);
  TTF_CloseFont(InterUI_Medium_Italic_Large);

  TTF_CloseFont(InterUI_Bold);
  TTF_CloseFont(InterUI_Bold_Large);
  TTF_CloseFont(InterUI_Bold_Italic);
  TTF_CloseFont(InterUI_Bold_Italic_Large);

  TTF_CloseFont(InterUI_Black);
  TTF_CloseFont(InterUI_Black_Large);
  TTF_CloseFont(InterUI_Black_Italic);
  TTF_CloseFont(InterUI_Black_Italic_Large);
  
  TTF_CloseFont(Title_Font);
  TTF_Quit();
}