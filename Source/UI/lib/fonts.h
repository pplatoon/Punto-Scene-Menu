#pragma once
#include "precisionui.h"

TTF_Font *InterUI_Regular;
TTF_Font *InterUI_Regular_Large;
TTF_Font *InterUI_Regular_Italic;
TTF_Font *InterUI_Regular_Italic_Large;

TTF_Font *InterUI_Medium;
TTF_Font *InterUI_Medium_Large;
TTF_Font *InterUI_Medium_Italic;
TTF_Font *InterUI_Medium_Italic_Large;

TTF_Font *InterUI_Bold;
TTF_Font *InterUI_Bold_Large;
TTF_Font *InterUI_Bold_Italic;
TTF_Font *InterUI_Bold_Italic_Large;

TTF_Font *InterUI_Black;
TTF_Font *InterUI_Black_Large;
TTF_Font *InterUI_Black_Italic;
TTF_Font *InterUI_Black_Italic_Large;

TTF_Font *Title_Font;

int PUI_Font_Init(void);

void PUI_Font_Close(void);
