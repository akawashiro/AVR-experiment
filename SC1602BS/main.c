#include "hd44780.h" /* EZ-LCD include file */

int main(void) {
    uint8_t c;

    lcd_init(); /* LCDモジュールの初期化 */

    for (c = '0'; c - '0' < 32; c++) { /* LCDに文字を表示 */
        lcd_putc(c);
    }

    return 0;
}

