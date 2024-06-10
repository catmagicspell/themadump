#ifndef COMMON_H
#define COMMON_H
#pragma once

#include <pspsdk.h>
#include <pspkernel.h>
#include <libpspexploit.h>

#define RGB(r, g, b) (0xFF000000 | ((b) << 16) | ((g) << 8) | (r))
#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define BLACK RGB(0, 0, 0)
#define ORANGE RGB(255, 127, 0)
#define WHITE RGB(255, 255, 255)
#define YELLOW RGB(255, 255, 0)
#define GRAY RGB(103, 120, 137)

#define BackColor(color) pspDebugScreenSetBackColor(color)
#define TextColor(color) pspDebugScreenSetTextColor(color)
#define printf pspDebugScreenPrintf

#define VER_MAJOR 1
#define VER_MINOR 0

extern void kthread(void);
extern KernelFunctions *k_tbl;
#endif