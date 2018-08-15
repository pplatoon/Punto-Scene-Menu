#pragma once
#include "precisionui.h"
#include <stdarg.h>

typedef struct PUI_Element {
  int id;
  int x;
  int y;
  int x1;
  int y1;
  int x2;
  int y2;
  bool canFocus;
  bool canTap;
  bool tapped;
  bool focused;
  bool boolMeta;
  int intMeta;
  char* charMeta;
  void* anyMeta;
} PUI_Element;

/* Global *******************/
/*
 * Element IDs
 * 0: sidebar (not in element list)
 * 1: divider (grey line)
 * 2: blank space
 * 3: label
 * 4: toggle
 * 5: button
 */
PUI_Element ELEMENTS[128];
int ELEMENT_INDEX;
/****************************/

/* Sidebar ******************/
bool SIDEBAR_DRAWN;
int SIDEBAR_INDEX;
int SIDEBAR_LENGTH;
char *SIDEBAR_SEL;
char *SIDEBAR_LIST[128]; // please don't have more than 128 values in the sidebar, why even would you
int SIDEBAR_X1[128];
int SIDEBAR_Y1[128];
int SIDEBAR_X2[128];
int SIDEBAR_Y2[128];
void PUI_Element_Sidebar(int sz, ...);
char* PUI_Element_Sidebar_GetItem(int idx);
/****************************/

int PUI_Element_Divider(void);
int PUI_Element_Label(TTF_Font *font, char* text, bool centered);
int PUI_Element_Button(TTF_Font *font, char* text, bool centered);