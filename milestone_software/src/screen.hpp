#include "libs.hpp"
#include "vars.hpp"
#include "heart.hpp"

// intrerupere care creste contorul la fiecare 1ms (timer0)
ISR(TIMER0_COMPA_vect) {
    systicks++;
}

// functie care returneaza timpul curent in milisecunde
uint32_t time_millies() {
    return systicks;
}

// afisare ecran de start
void begin_screen() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 20);
    display.println(F("Apasa B1 pentru \n     inregistrare"));
    display.display();
}

// afisarea rezultatelor masurarii bpm pe ecran
void result_screen(uint8_t bpm, uint32_t duration, uint8_t beatCount) {
    unsigned long pulseStart = time_millies();
    bool big = false;

    // aprind led-ulin functie de intervalul bpm

    if (bpm >= 60 && bpm <= 100) {
        // valoare normala inseamna ca led-ul verde e aprins
        PORTD |= (1 << RED_PIN);
        PORTD &= ~(1 << GREEN_PIN);
    } else if ((bpm >= 40 && bpm < 60) || (bpm > 100 && bpm <= 120)) {
        // valoare in afara limitelor dar nu extrem inseamna ca led-ul e portocaliu
        // pentru a simula portocaliul aprind si rosu si verde
        PORTD &= ~(1 << RED_PIN);
        PORTD &= ~(1 << GREEN_PIN);
    } else {
        // valoare extrema inseamna ca led-ul rosu e aprins
        PORTD &= ~(1 << RED_PIN);
        PORTD |= (1 << GREEN_PIN);
    }

    // la afisarea rezultatului afisez animatia inimioarei si datele obtinute
    // mentin informatiile pe ecran timp de 7 secunde
    while (time_millies() - pulseStart < 7000) {
        display.clearDisplay();

        if (big) {
            display.drawBitmap(0, 22, heartBig, 30, 26, SSD1306_WHITE);
        } else {
            display.drawBitmap(2, 24, heartSmall, 24, 15, SSD1306_WHITE);
        }

        display.setTextSize(1);
        display.setCursor(40, 22);
        display.print("BPM: ");
        display.println(bpm);

        display.setCursor(40, 32);
        display.print("Durata: ");
        display.print(duration);
        display.println("s");

        display.setCursor(40, 42);
        display.print("Batai: ");
        display.println(beatCount);

        display.display();

        _delay_ms(300);
        big = !big;
    }
}