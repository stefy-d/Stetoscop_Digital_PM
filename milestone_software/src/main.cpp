
#include "libs.hpp" // biblioteci standard
#include "init.hpp" // initializare gpio, adc, timer
#include "vars.hpp" // variabile globale
#include "screen.hpp" // functii pentru afisarea pe display
#include "heart.hpp"  // bitmap-uri pentru afisare


// citeste valoarea analogica de la channel-ul specificat
uint16_t analog_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // selecteaza canalul adc
    ADCSRA |= (1 << ADSC); // porneste conversia
    while (ADCSRA & (1 << ADSC)); // asteapta pana se termina
    return ADC; // returneaza valoarea citita
}

// citesc starea unui buton (apasat = true)
bool is_button_pressed(uint8_t pin) {
    return !(PIND & (1 << pin)); // 0 e apasat
}

// state-urile in care se poate afla programul
typedef enum { BEGIN, RECORD } State;
State currentState = BEGIN;

int main() {
    cli(); // dezactiveaza intreruperile globale
    gpio_init(); // configurare pini
    adc_init();  // configurare adc
    timer0_init(); // configurare timer
    sei(); // activeaza intreruperile globale

    Wire.begin(); // initializare i2c

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        exit(1);
    }

    begin_screen(); // afisez ecranul initial

    // variabile de stare
    uint32_t lastBlink = 0;
    bool ledOn = false;
    int beatCount = 0;
    bool beatDetected = false;
    uint32_t recordStartTime = 0;

    while (1) {
        if (currentState == BEGIN) {
            // setez led-urile in stare initiala
            PORTD |= (1 << RED_PIN);
            PORTD &= ~(1 << GREEN_PIN);
            PORTC &= ~(1 << SPEAKER_POWER); // dezactivez difuzorul

            // la apasarea butonului 1 trec in stare de inregistrare
            if (is_button_pressed(BUTTON1)) {
                _delay_ms(200); // debounce

                // resetez variabilele 
                currentState = RECORD;
                beatCount = 0;
                beatDetected = false;
                recordStartTime = time_millies();

                display.clearDisplay();
                display.setCursor(20, 25);
                display.setTextSize(1);
                display.println("Inregistrare...");
                display.display();
                _delay_ms(700);
                display.clearDisplay();
            }
        } else if (currentState == RECORD) {
            // led verde stins, rosu aprins si speaker pornit
            PORTD |= (1 << GREEN_PIN);
            PORTD &= ~(1 << RED_PIN);
            PORTC |= (1 << SPEAKER_POWER);

            int x = 0;
            int lastY = SCREEN_HEIGHT / 2;

            // bucla pentru starea de inregistrare
            while (currentState == RECORD) {

                // la apasarea butonului 2 trec inregistrarea se opreste si trec
                // in starea de inceput
                if (is_button_pressed(BUTTON2)) {
                    _delay_ms(200);
                    currentState = BEGIN;
                    PORTC &= ~(1 << SPEAKER_POWER); // opresc speaker

                    // calculez timpul in care s-a inregistrat si bpm-ul
                    uint32_t duration = (time_millies() - recordStartTime) / 1000;
                    uint8_t bpm;

                    if (duration > 0) {
                        bpm = (beatCount * 60) / duration;
                    } else {
                        bpm = 0;
                    }

                    // afisez datele
                    result_screen(bpm, duration, beatCount);
                    begin_screen();
                    break;  // ies din bucla de inregistrare
                }

                // led rosu clipeste la fiecare 500ms
                if (time_millies() - lastBlink >= 500) {
                    ledOn = !ledOn;
                    if (ledOn)
                        PORTD &= ~(1 << RED_PIN);
                    else
                        PORTD |= (1 << RED_PIN);

                    lastBlink = time_millies();
                }

                // citeste valoare microfon
                uint16_t micValue = analog_read(MIC_PIN);
                int y = map(micValue, 900, 1000, SCREEN_HEIGHT, 20); // conversie in coordonate ecran

                // numar bataile detectate
                if (micValue > PEAK_THRESHOLD && !beatDetected) {
                    beatCount++;
                    beatDetected = true;
                }

                if (micValue < PEAK_THRESHOLD) {
                    beatDetected = false;
                }

                // curata coloana curenta
                display.drawFastVLine(x, 0, SCREEN_HEIGHT, SSD1306_BLACK);

                // desenez semnalul curent
                if (micValue >= MIC_THRESHOLD) {
                    display.drawLine(x, lastY, x, y, SSD1306_WHITE);
                    lastY = y;
                } else {
                    display.drawLine(x, lastY, x, SCREEN_HEIGHT / 2, SSD1306_WHITE);
                    lastY = SCREEN_HEIGHT / 2;
                }

                display.display();
                // trec mai departe pe ecran
                x++;
                if (x >= SCREEN_WIDTH) 
                  x = 0;

                _delay_ms(2); // intarziere intre semnale
            }
          }
    }
}
