#include "WifiMenu.h"
#include "Display.h"
#include "Menu.h"
#include <WiFi.h>


void waitBackButton()
{
    while (digitalRead(BTN_BACK) == HIGH)
    {
        delay(10);
    }

    while (digitalRead(BTN_BACK) == LOW)
    {
        delay(10);
    }
}

void wifiScan()
{
    lcd.fillScreen(TFT_BLACK);

    lcd.setTextSize(2);

    lcd.setCursor(10,10);
    lcd.println("Scanning...");

    WiFi.mode(WIFI_STA);

    WiFi.disconnect(true);

    delay(200);

    int networks = WiFi.scanNetworks();

    lcd.fillScreen(TFT_BLACK);

    lcd.setCursor(10,10);

    lcd.printf("Found %d\n\n",networks);

    int y = 40;

    for(int i=0;i<networks;i++)
    {
        lcd.setCursor(5,y);

        lcd.printf("%d ",i+1);

        lcd.print(WiFi.SSID(i));

        lcd.setCursor(220,y);

        lcd.print(WiFi.RSSI(i));

        y += 18;

        if(y>215)
            break;
    }

    lcd.setCursor(10,225);

    lcd.print("BACK");
    
    waitBackButton();
}

void wifiAccessPoint()
{
    WiFi.mode(WIFI_AP);

    WiFi.softAP("ESP32-FW","12345678");

    lcd.fillScreen(TFT_BLACK);

    lcd.setTextSize(2);

    lcd.setCursor(10,10);

    lcd.println("Access Point");

    lcd.println();

    lcd.print("SSID : ");

    lcd.println("ESP32-FW");

    lcd.println();

    lcd.print("PASS : ");

    lcd.println("12345678");

    lcd.println();

    lcd.print("IP : ");

    lcd.println(WiFi.softAPIP());

    lcd.setCursor(10,225);

    lcd.print("BACK");

    waitBackButton();
}

void wifiStationInfo()
{
    lcd.fillScreen(TFT_BLACK);

    lcd.setTextSize(2);

    lcd.setCursor(10,10);

    if(WiFi.status()!=WL_CONNECTED)
    {
        lcd.println("Not Connected");
    }
    else
    {
        lcd.print("SSID : ");

        lcd.println(WiFi.SSID());

        lcd.println();

        lcd.print("IP : ");

        lcd.println(WiFi.localIP());

        lcd.println();

        lcd.print("RSSI : ");

        lcd.println(WiFi.RSSI());

        lcd.println();

        lcd.print("MAC : ");

        lcd.println(WiFi.macAddress());
    }

    lcd.setCursor(10,225);

    lcd.print("BACK");

    waitBackButton();
}
