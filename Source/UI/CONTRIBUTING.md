# Contributing
## Submitting Pull Requests
* Follow the coding-style defined [below](#code-style)
* Do not squash commits

## Submitting Issues
* Describe the issue in detail

## Code Style
* Use 2 spaces in lieu of tabs (this *should* be defined in the [.vscode/settings.json](/.vscode/settings.json) file if you use VS Code)
* At the top of every C source code file, include a header file with the same name as the c file. e.g. `precisionui.c` and `precisionui.h`
* Do **not** include anything other than the header file with the same name as the C source file, place your include statements in the header file.
* At the top of every header file, place the following two lines:

```c
#pragma once
#include "precisionui.h"
```