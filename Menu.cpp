#include "Menu.h"
#include "Display.h"
#include "WifiMenu.h"

Page currentPage = PAGE_MAIN;

const char *mainMenu[] =
{
    "WiFi",
    "Bluetooth",
    "IR",
    "RFID / NFC",
    "Sub-GHz",
    "nRF24",
    "Files",
    "Tools",
    "Settings"
};

const int mainMenuCount = sizeof(mainMenu) / sizeof(mainMenu[0]);

const char *wifiMenu[] =
{
    "Scan Networks",
    "Access Point",
    "Station Info",
    "Back"
};

const int wifiMenuCount = sizeof(wifiMenu) / sizeof(wifiMenu[0]);

int selected = 0;

bool lastUp = HIGH;
bool lastDown = HIGH;
bool lastOK = HIGH;
bool lastBack = HIGH;

void drawHeader()
{
    uint16_t color = lcd.color565(0,60,120);

    lcd.fillRect(0,0,320,24,color);

    lcd.setTextColor(TFT_WHITE,color);

    lcd.setTextSize(2);

    lcd.drawString("Bruce S3",8,4);
}

void drawFooter()
{
    uint16_t color = lcd.color565(35,35,35);

    lcd.fillRect(0,220,320,20,color);

    lcd.setTextColor(TFT_WHITE,color);

    lcd.setTextSize(1);

    lcd.drawString("UP  DOWN  OK  BACK",8,224);
}

void drawMainMenu()
{
    lcd.fillScreen(TFT_BLACK);

    drawHeader();

    drawFooter();

    lcd.setTextSize(2);

    for(int i=0;i<mainMenuCount;i++)
    {
        int y = 34 + i*20;

        if(i==selected)
        {
            lcd.fillRoundRect(6,y-2,305,18,4,TFT_BLUE);
            lcd.setTextColor(TFT_WHITE,TFT_BLUE);
            lcd.drawString(">",12,y);
        }
        else
        {
            lcd.setTextColor(TFT_LIGHTGREY,TFT_BLACK);
        }

        lcd.drawString(mainMenu[i],28,y);
    }
}

void drawWifiMenu()
{
    lcd.fillScreen(TFT_BLACK);

    drawHeader();

    drawFooter();

    lcd.setTextSize(2);

    for(int i=0;i<wifiMenuCount;i++)
    {
        int y = 45 + i*28;

        if(i==selected)
        {
            lcd.fillRoundRect(6,y-2,305,24,4,TFT_BLUE);
            lcd.setTextColor(TFT_WHITE,TFT_BLUE);
            lcd.drawString(">",12,y);
        }
        else
        {
            lcd.setTextColor(TFT_LIGHTGREY,TFT_BLACK);
        }

        lcd.drawString(wifiMenu[i],28,y);
    }
}

void redraw()
{
    if(currentPage==PAGE_MAIN)
        drawMainMenu();
    else
        drawWifiMenu();
}

void menuInit()
{
    pinMode(BTN_UP,INPUT_PULLUP);
    pinMode(BTN_DOWN,INPUT_PULLUP);
    pinMode(BTN_OK,INPUT_PULLUP);
    pinMode(BTN_BACK,INPUT_PULLUP);

    redraw();
}
void menuLoop()
{
    bool up    = digitalRead(BTN_UP);
    bool down  = digitalRead(BTN_DOWN);
    bool ok    = digitalRead(BTN_OK);
    bool back  = digitalRead(BTN_BACK);

    // ===== UP =====
    if(lastUp == HIGH && up == LOW)
    {
        selected--;

        if(selected < 0)
        {
            if(currentPage == PAGE_MAIN)
                selected = mainMenuCount - 1;
            else
                selected = wifiMenuCount - 1;
        }

        redraw();
        delay(120);
    }

    // ===== DOWN =====
    if(lastDown == HIGH && down == LOW)
    {
        selected++;

        if(currentPage == PAGE_MAIN)
        {
            if(selected >= mainMenuCount)
                selected = 0;
        }
        else
        {
            if(selected >= wifiMenuCount)
                selected = 0;
        }

        redraw();
        delay(120);
    }

    // ===== OK =====
    if(lastOK == HIGH && ok == LOW)
    {
        if(currentPage == PAGE_MAIN)
        {
            if(selected == 0)
            {
                currentPage = PAGE_WIFI;
                selected = 0;
                redraw();
            }
        }
        else if(currentPage == PAGE_WIFI)
        {
            switch(selected)
            {
                case 0:
                    wifiScan();
                    redraw();
                    break;

                case 1:
                    lcd.fillScreen(TFT_BLACK);
                    lcd.setCursor(10,20);
                    lcd.setTextSize(2);
                    lcd.println("Access Point");
                    lcd.println();
                    lcd.println("Coming Soon...");
                    break;

                case 2:
                    lcd.fillScreen(TFT_BLACK);
                    lcd.setCursor(10,20);
                    lcd.setTextSize(2);
                    lcd.println("Station Info");
                    lcd.println();
                    lcd.println("Coming Soon...");
                    break;

                case 3:
                    currentPage = PAGE_MAIN;
                    selected = 0;
                    redraw();
                    break;
            }
        }

        delay(150);
    }

    // ===== BACK =====
    if(lastBack == HIGH && back == LOW)
    {
        if(currentPage != PAGE_MAIN)
        {
            currentPage = PAGE_MAIN;
            selected = 0;
            redraw();
        }

        delay(150);
    }

    lastUp = up;
    lastDown = down;
    lastOK = ok;
    lastBack = back;
}