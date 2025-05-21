#include "libs.hpp"
#include "vars.hpp"

// initializare gpio pentru butoane, led-uri si pinul speaker-ului
void gpio_init() {
    // butoanele pe d2 si d3 ca intrare cu rezistenta pull-up
    DDRD &= ~((1 << BUTTON1) | (1 << BUTTON2));
    PORTD |= (1 << BUTTON1) | (1 << BUTTON2);

    // led-urile pe d4 si d5 ca iesire
    DDRD |= (1 << RED_PIN) | (1 << GREEN_PIN);
    PORTD |= (1 << RED_PIN) | (1 << GREEN_PIN); // led-urile stinse

    // speaker power pe a1 ca iesire
    DDRC |= (1 << SPEAKER_POWER);
    PORTC &= ~(1 << SPEAKER_POWER); // initial stins
}

// initializare adc pentru citire analogica
void adc_init() {
    ADMUX = (1 << REFS0); // referinta = AVCC
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // activeaza adc, prescaler = 64
}

// timer0 pentru a genera o intrerupere la fiecare 1ms
void timer0_init() {
    TCCR0A = (1 << WGM01); // mod CTC
    TCCR0B = (1 << CS01) | (1 << CS00); // prescaler 64
    OCR0A = 249; // compare value pentru 1ms la 16mhz
    TIMSK0 = (1 << OCIE0A); // activare intrerupere
}