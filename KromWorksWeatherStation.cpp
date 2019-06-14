#include "KromWorksWeatherStation.hpp"

Weatherstation::Weatherstation(BMP280 &BMP280, oled &display) : chip(BMP280), display(display) {}

void Weatherstation::startUp()
{
    display.clearScreen();
    display.resetCursor();
    display.drawText(" Hola!");
    hwlib::wait_ms(2000);
    display.resetCursor();
    display.drawText("starting\n");
    chip.reset();
    display.drawText("done!");
    hwlib::wait_ms(1000);
    display.resetCursor();
    display.clearScreen();
    display.drawText("reading\n");
    display.drawText("param...");
    chip.readTempParam();
    chip.readPressParam();
    display.resetCursor();
    display.clearScreen();
    display.drawText(" done!");
    hwlib::wait_ms(500);
    display.resetCursor();
    display.clearScreen();
    display.drawText("fetching\n");
    display.drawText("id...");
    chip.readId();
    display.resetCursor();
    display.clearScreen();
    display.drawText("id: ");
    display.drawByte(chip.returnData().id);
    hwlib::wait_ms(500);
    display.resetCursor();
    display.clearScreen();
    display.drawText("welcome!");
    hwlib::wait_ms(2000);
}

void Weatherstation::measurementCyle()
{
    chip.readPTRegisters();
    chip.calculateTemp();
    display.clearScreen();
    display.resetCursor();
    display.drawTemp(chip.returnData().realTemp / 100);
    display.drawText(" C");
}

void Weatherstation::intervalMeasurement(uint16_t time)
{
    measurementCyle();
    hwlib::wait_ms(time);
}