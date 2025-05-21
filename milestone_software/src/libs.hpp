// biblioteci standard
#include <avr/io.h>         // acces direct la registri (gpio, adc, etc)
#include <avr/interrupt.h>  // permite definirea si activarea intreruperilor
#include <util/delay.h>     // functii de intarziere (precise in ms sau us)
#include <stdint.h>         // definirea tipurilor uint8_t, uint16_t, etc
#include <stdbool.h>        // definirea tipului boolean: true/false

// biblioteci pentru display oled i2c ssd1306
#include <Wire.h>               // biblioteca i2c (folosita de display)
#include <Adafruit_GFX.h>       // biblioteca pentru afiseaza grafica pe display
#include <Adafruit_SSD1306.h>   // biblioteca specifica pentru ecrane ssd1306