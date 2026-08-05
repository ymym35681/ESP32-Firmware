#ifndef MENU_H
#define MENU_H

#include <Arduino.h>

// ===== Buttons =====
#define BTN_UP      4
#define BTN_DOWN    5
#define BTN_OK      6
#define BTN_BACK    13

// ===== Pages =====
enum Page
{
    PAGE_MAIN,
    PAGE_WIFI
};

extern Page currentPage;

void menuInit();

void menuLoop();

#endif