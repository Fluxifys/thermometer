#include "screens.h"

static void drawHouse(Adafruit_SSD1306 &display, int x, int y)
{
    display.drawRect(x, y + 20, 36, 32, SSD1306_WHITE);

    display.drawLine(x,       y + 20, x + 18, y, SSD1306_WHITE);
    display.drawLine(x + 18,  y,      x + 36, y + 20, SSD1306_WHITE);

    display.drawRect(x + 26, y + 2, 4, 10, SSD1306_WHITE);
}

static void drawSun(Adafruit_SSD1306 &display, int cx, int cy)
{
    int r = 10;

    display.drawCircle(cx, cy, r, SSD1306_WHITE);

    int ray = r + 6;

    display.drawLine(cx, cy - ray, cx, cy - r, SSD1306_WHITE);
    display.drawLine(cx, cy + ray, cx, cy + r, SSD1306_WHITE);

    display.drawLine(cx - ray, cy, cx - r, cy, SSD1306_WHITE);
    display.drawLine(cx + ray, cy, cx + r, cy, SSD1306_WHITE);

    display.drawLine(cx - ray, cy - ray, cx - r, cy - r, SSD1306_WHITE);
    display.drawLine(cx + ray, cy - ray, cx + r, cy - r, SSD1306_WHITE);
    display.drawLine(cx - ray, cy + ray, cx - r, cy + r, SSD1306_WHITE);
    display.drawLine(cx + ray, cy + ray, cx + r, cy + r, SSD1306_WHITE);
}

void showIndoorScreen(Adafruit_SSD1306 &display, float indoorTemp)
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Inomhus:");

    display.setTextSize(2);
    display.setCursor(0, 28);
    display.print(indoorTemp, 1);
    display.println("C");

    drawHouse(display, 92, 18);

    display.display();
}

void showHumidityScreen(Adafruit_SSD1306 &display, float hum)
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Luftfukt:");

    display.setTextSize(2);
    display.setCursor(0, 28);
    display.print(hum, 0);
    display.print("%");

    drawHouse(display, 92, 18);

    display.display();
}

void showOutdoorScreen(Adafruit_SSD1306 &display, float outdoorTemp)
{
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Utomhus:");

    display.setTextSize(2);
    display.setCursor(0, 28);
    display.print(outdoorTemp, 1);
    display.println("C");

    drawSun(display, 92 + 18, 38);

    display.display();
}
