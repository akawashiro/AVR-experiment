#define F_CPU 1000000UL  // 1 MHz

#include <avr/io.h>
#include <util/delay.h>

// void loop_anode() {
//     PORTB = 1 << 3;  // 1
//     _delay_ms(100);
//     PORTB = 1 << 0;  // 2
//     _delay_ms(100);
//     PORTB = 1 << 4;  // 3
//     _delay_ms(100);
//     PORTB = 1 << 1;  // 4
//     _delay_ms(100);
//     PORTB = 1 << 7;  // 5
//     _delay_ms(100);
//     PORTB = 1 << 2;  // 6
//     _delay_ms(100);
//     PORTB = 1 << 6;  // 7
//     _delay_ms(100);
//     PORTB = 1 << 5;  // 8
//     _delay_ms(100);
//     PORTB = 0x00;
// }
//
// void check_all_LEDs(){
//    while (1) {
//     PORTD = 0xff - (1 << 0);  // 1
//     loop_anode();
//     _delay_ms(100);
//     PORTD = 0xff - (1 << 1);  // 2
//     loop_anode();
//     _delay_ms(100);
//
//     PORTD = 0xff;
//     PORTA = 0xff - (1 << 0);  // 3
//     loop_anode();
//     _delay_ms(100);
//     PORTA = 0xff;
//
//     PORTD = 0xff - (1 << 5);  // 4
//     loop_anode();
//     _delay_ms(100);
//     PORTD = 0xff - (1 << 6);  // 5
//     loop_anode();
//     _delay_ms(100);
//     PORTD = 0xff - (1 << 4);  // 6
//     loop_anode();
//     _delay_ms(100);
//     PORTD = 0xff - (1 << 3);  // 7
//     loop_anode();
//     _delay_ms(100);
//     PORTD = 0xff - (1 << 2);  // 8
//     loop_anode();
//     _delay_ms(100);
//     PORTD = 0xff;
//
//     _delay_ms(100);
// }
// }

void turn_off_all() {
    PORTB = 0x00;
    PORTD = 0xff;
    PORTA = 0xff;
}

void turn_on_YX(char y, char x) {
    switch (y) {
        case 0:
            PORTB = 1 << 5;
            break;
        case 1:
            PORTB = 1 << 6;
            break;
        case 2:
            PORTB = 1 << 2;
            break;
        case 3:
            PORTB = 1 << 7;
            break;
        case 4:
            PORTB = 1 << 1;
            break;
        case 5:
            PORTB = 1 << 4;
            break;
        case 6:
            PORTB = 1 << 0;
            break;
        case 7:
            PORTB = 1 << 3;
            break;
    }
    switch (x) {
        case 0:
            PORTA = 0xff;
            PORTD = 0xff - (1 << 2);
            break;
        case 1:
            PORTA = 0xff;
            PORTD = 0xff - (1 << 3);
            break;
        case 2:
            PORTA = 0xff;
            PORTD = 0xff - (1 << 4);
            break;
        case 3:
            PORTA = 0xff;
            PORTD = 0xff - (1 << 6);
            break;
        case 4:
            PORTA = 0xff;
            PORTD = 0xff - (1 << 5);
            break;
        case 5:
            PORTA = 0xff - (1 << 0);
            PORTD = 0xff;
            break;
        case 6:
            PORTA = 0xff;
            PORTD = 0xff - (1 << 1);
            break;
        case 7:
            PORTA = 0xff;
            PORTD = 0xff - (1 << 0);
            break;
    }
    _delay_ms(1);
}

void draw_line(const char line_data, char y) {
    switch (y) {
        case 0:
            PORTB = 1 << 5;
            break;
        case 1:
            PORTB = 1 << 6;
            break;
        case 2:
            PORTB = 1 << 2;
            break;
        case 3:
            PORTB = 1 << 7;
            break;
        case 4:
            PORTB = 1 << 1;
            break;
        case 5:
            PORTB = 1 << 4;
            break;
        case 6:
            PORTB = 1 << 0;
            break;
        case 7:
            PORTB = 1 << 3;
            break;
    }

    PORTD = 0xff;
    PORTA = 0xff;
    char buf_PORTD = 0xff;
    char buf_PORTA = 0xff;
    if (line_data & (1 << 7)) {
        buf_PORTD ^= (1 << 2);
    }
    if (line_data & (1 << 6)) {
        buf_PORTD ^= (1 << 3);
    }
    if (line_data & (1 << 5)) {
        buf_PORTD ^= (1 << 4);
    }
    if (line_data & (1 << 4)) {
        buf_PORTD ^= (1 << 6);
    }
    if (line_data & (1 << 3)) {
        buf_PORTD ^= (1 << 5);
    }
    if (line_data & (1 << 2)) {
        buf_PORTA ^= (1 << 0);
    }
    if (line_data & (1 << 1)) {
        buf_PORTD ^= (1 << 1);
    }
    if (line_data & (1 << 0)) {
        buf_PORTD ^= (1 << 0);
    }
    PORTD = buf_PORTD;
    PORTA = buf_PORTA;
    _delay_ms(1);
}

// `data' must be 8 length.
void draw(const char* const data) {
    for (char y = 0; y < 8; y++) {
        draw_line(*(data + y), y);
        // for (char x = 0; x < 8; x++) {
        // if (*(data + y) & (1 << (7 - x))) {
        // turn_on_YX(y, x);
        // }
        // }
    }
}

int main(void) {
    char circle_data[8] = {0b00111100, 0b01111110, 0b11000011, 0b11000011,
                           0b11000011, 0b11000011, 0b01111110, 0b00111100};

    char cross_data[8] = {0b11000011, 0b11000011, 0b01100110, 0b00111100,
                          0b00111100, 0b01100110, 0b11000011, 0b11000011};

    // Anodes of LEDs are connected DDRB[0:7].
    // Anodes are used as Y-axis.
    DDRB = 0xff;

    // Casodes of LEDs are connected DDRB[0:6] and DDRA[0:0].
    // Casodes are used as X-Axis.
    DDRA = 0x03;
    DDRD = 0x7f;

    turn_off_all();
    while (1) {
        for (uint8_t i = 0; i < 255; i++) {
            draw(circle_data);
        }
        for (uint8_t i = 0; i < 255; i++) {
            draw(cross_data);
        }
    }
}
