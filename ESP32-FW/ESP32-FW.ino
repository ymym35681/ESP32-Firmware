#include "Display.h"
#include "Menu.h"

void setup()
{
    displayBegin();

    menuInit();
}

void loop()
{
    menuLoop();
}