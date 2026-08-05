#ifndef DISPLAY_H
#define DISPLAY_H

#include <LovyanGFX.hpp>

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7789 _panel;
    lgfx::Bus_SPI _bus;

public:

    LGFX()
    {
        {
            auto cfg = _bus.config();

            cfg.spi_host = SPI2_HOST;
            cfg.spi_mode = 0;

            cfg.freq_write = 27000000;
            cfg.freq_read = 16000000;

            cfg.pin_sclk = 12;
            cfg.pin_mosi = 11;
            cfg.pin_miso = -1;

            cfg.pin_dc = 9;

            _bus.config(cfg);

            _panel.setBus(&_bus);
        }

        {
            auto cfg = _panel.config();

            cfg.pin_cs = 8;
            cfg.pin_rst = 10;
            cfg.pin_busy = -1;

            cfg.panel_width = 240;
            cfg.panel_height = 320;

            cfg.memory_width = 240;
            cfg.memory_height = 320;

            cfg.offset_x = 0;
            cfg.offset_y = 0;

            cfg.invert = true;

            cfg.rgb_order = false;

            cfg.readable = false;

            _panel.config(cfg);
        }

        setPanel(&_panel);
    }
};

extern LGFX lcd;

void displayBegin();

#endif