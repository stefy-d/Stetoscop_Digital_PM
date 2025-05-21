#include "libs.hpp"

// dimensiunea ecranului oled
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // reset nefolosit (conectat la vcc)

// definirea obiectului display global
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// mapare pini folositi
#define MIC_PIN 0       // adc0 - citire analogica de la microfon
#define RED_PIN PD4     // led rosu pe pin D4
#define GREEN_PIN PD5   // led verde pe pin D5
#define BUTTON1 PD2     // buton 1 pe pin D2
#define BUTTON2 PD3     // buton 2 pe pin D3
#define SPEAKER_POWER PC1 // speaker (alimentare) pe A1

// praguri pentru detectia sunetului (hearbeat)
#define PEAK_THRESHOLD 985  // praag pentru detectia unei batai
#define MIC_THRESHOLD 0     // prag minim pentru desen pe display

// contor global de milisecunde, volatile ca sa nu fie optimizat de compilator
volatile uint32_t systicks = 0;