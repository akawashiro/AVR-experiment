#define F_CPU 1000000UL  // 1 MHz

#include <avr/io.h>
#include <util/delay.h>

void turn_off_all() {
    PORTB = 0x00;
    PORTD = 0xff;
    PORTA = 0x01;
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

    char buf_PORTD = 0xff;
    char buf_PORTA = 0x01 | PORTA;
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
    }
}

int is_full(const char* const data) {
    char c = 0b11111111;
    for (char y = 0; y < 8; y++) {
        if (*(data + y) != c) return 0;
    }
    return 1;
}

int main(void) {
    char matrix_data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    char full_data[8] = {-1, -1, -1, -1, -1, -1, -1, -1};

    // Anodes of LEDs are connected DDRB[0:7].
    // Anodes are used as Y-axis.
    DDRB = 0xff;

    // Casodes of LEDs are connected DDRB[0:6] and DDRA[0:0].
    // Casodes are used as X-Axis.
    DDRA = 0x03;
    DDRD = 0x7f;

    turn_off_all();
    char y = 0, x = 0;
    while (1) {
        for (uint8_t i = 0; i < 32; i++) {
            draw(matrix_data);
        }
        if (is_full(matrix_data)) {
            matrix_data[0] = 0;
            matrix_data[1] = 0;
            matrix_data[2] = 0;
            matrix_data[3] = 0;
            matrix_data[4] = 0;
            matrix_data[5] = 0;
            matrix_data[6] = 0;
            matrix_data[7] = 0;
            y = 0;
            x = 0;

            PORTA |= (1 << 1);
            while (1) {
                for (uint8_t i = 0; i < 32; i++) {
                    draw(matrix_data);
                }
                for (uint8_t i = 0; i < 32; i++) {
                    draw(full_data);
                }
            }
        } else {
            if (0 < y) {
                matrix_data[y - 1] ^= (1 << x);
            }
            matrix_data[y] ^= (1 << x);
            if (y == 7 || ((matrix_data[y + 1] & (1 << x)) != 0)) {
                x = (x + 1) % 8;
                y = 0;
            } else {
                y++;
            }
        }
    }
}
