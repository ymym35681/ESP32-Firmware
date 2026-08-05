#include "Display.h"

LGFX lcd;

void displayBegin()
{
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);

    lcd.init();

    lcd.setRotation(1);

    lcd.fillScreen(TFT_BLACK);

    lcd.setTextColor(TFT_WHITE);

    lcd.setTextSize(2);
}