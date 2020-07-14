#include <Keyboard.h>

void kbd_set_keys();
int row_col_key(int row, int col);

#define NUMCOLS 14
int cols[] = {
    PIN_F0, /* ESC */ 
    PIN_F1, /* F1 */  
    PIN_F4, /* F2 */  
    PIN_F5, /* F3 */  
    PIN_F6, /* F4 */  
    PIN_F7, /* F5 */  
    PIN_B6, /* F6 */  
    PIN_B5, /* F7 */ 
    PIN_B4, /* F8 */ 
    PIN_D7, /* F9 */ 
    PIN_D6, /* F10 */
    PIN_D4, /* F11 */
    PIN_D5, /* F12 */
    PIN_C7  /* DEL */
};
#define NUMROWS 7
int rows[] = {
    PIN_B0, /* ESC */
    PIN_B1, /* ~ ` */  
    PIN_B2, /* TAB */  
    PIN_B3, /* CAPS*/  
    PIN_B7, /* SHIFT */
    PIN_D0, /* PGUP */ 
    PIN_D1  /* PGDN */ 
};
#define NUMKEYS 6
int keys[NUMKEYS];
int mods;

void setup() {
    /* COLUMNS */
    for (int c = 0; c < NUMCOLS; ++c) {
        pinMode(cols[c], INPUT_PULLUP);
        digitalWrite(cols[c], HIGH); /* high means off */
    }
    /* ROWS */
    for (int r = 0; r < NUMROWS; ++r) {
        pinMode(rows[r], OUTPUT); 
    }
    Keyboard.begin();
    delayMicroseconds(10);
    Keyboard.releaseAll();
}

void loop() {
    /* remove pressed keys */
    mods = 0;
    for (int i = 0; i < NUMKEYS; ++i) {
        keys[i] = 0;
    }
    int spot = 0;      /* allows mutiple keys at the same time */
    /* scan matrix  */
    for (int r = 0; r < NUMROWS; ++r) {
        digitalWrite(rows[r], LOW); /* send power to the current column */
        for (int c = 0; c < NUMCOLS; ++c) {
            if (!digitalRead(cols[c])) { /* try to read low signal from column */
                int key = row_col_qwerty(r, c);   /* get key value */
                if (key != 0 && spot < NUMKEYS) { /* not modifier */
                    keys[spot] = key;             /* save key */
                    spot += 1;  /* move to next key */
                }
            }
        }
        digitalWrite(rows[r], HIGH); /* remove power from current column */
    }
    /* press keys */
    Keyboard.set_modifier(mods);
    kbd_set_keys();             /* apply the keys */
    Keyboard.send_now();
}

void kbd_set_keys() {
    Keyboard.set_key1(keys[0]);
    Keyboard.set_key2(keys[1]);
    Keyboard.set_key3(keys[2]);
    Keyboard.set_key4(keys[3]);
    Keyboard.set_key5(keys[4]);
    Keyboard.set_key6(keys[5]);
}

int row_col_qwerty(int row, int col) {
    int key = 0;
    if (row == 0 && col == 0) { key = KEY_ESC; }
    else if (row == 0 && col == 1)  { key = KEY_F1; }
    else if (row == 0 && col == 2)  { key = KEY_F2; }
    else if (row == 0 && col == 3)  { key = KEY_F3; }
    else if (row == 0 && col == 4)  { key = KEY_F4; }
    else if (row == 0 && col == 5)  { key = KEY_F5; }
    else if (row == 0 && col == 6)  { key = KEY_F6; }
    else if (row == 0 && col == 7)  { key = KEY_F7; }
    else if (row == 0 && col == 8)  { key = KEY_F8; }
    else if (row == 0 && col == 9)  { key = KEY_F9; }
    else if (row == 0 && col == 10) { key = KEY_F10; }
    else if (row == 0 && col == 11) { key = KEY_F11; }
    else if (row == 0 && col == 12) { key = KEY_F12; }
    else if (row == 0 && col == 13) { key = KEY_DELETE; }
    else if (row == 1 && col == 0)  { key = KEY_TILDE; }
    else if (row == 1 && col == 1)  { key = KEY_1; }
    else if (row == 1 && col == 2)  { key = KEY_2; }
    else if (row == 1 && col == 3)  { key = KEY_3; }
    else if (row == 1 && col == 4)  { key = KEY_4; }
    else if (row == 1 && col == 5)  { key = KEY_5; }
    else if (row == 1 && col == 6)  { key = KEY_6; }
    else if (row == 1 && col == 7)  { key = KEY_7; }
    else if (row == 1 && col == 8)  { key = KEY_8; }
    else if (row == 1 && col == 9)  { key = KEY_9; }
    else if (row == 1 && col == 10) { key = KEY_0; }
    else if (row == 1 && col == 11) { key = KEY_MINUS; }
    else if (row == 1 && col == 12) { key = KEY_EQUAL; }
    else if (row == 1 && col == 13) { key = KEY_BACKSPACE; }
    else if (row == 2 && col == 0)  { key = KEY_TAB; }
    else if (row == 2 && col == 1)  { key = KEY_Q; }
    else if (row == 2 && col == 2)  { key = KEY_W; }
    else if (row == 2 && col == 3)  { key = KEY_E; }
    else if (row == 2 && col == 4)  { key = KEY_R; }
    else if (row == 2 && col == 5)  { key = KEY_T; }
    else if (row == 2 && col == 6)  { key = KEY_Y; }
    else if (row == 2 && col == 7)  { key = KEY_U; }
    else if (row == 2 && col == 8)  { key = KEY_I; }
    else if (row == 2 && col == 9)  { key = KEY_O; }
    else if (row == 2 && col == 10) { key = KEY_P; }
    else if (row == 2 && col == 11) { key = KEY_LEFT_BRACE; }
    else if (row == 2 && col == 12) { key = KEY_RIGHT_BRACE; }
    else if (row == 2 && col == 13) { key = KEY_BACKSLASH; }
    else if (row == 3 && col == 0)  { key = KEY_CAPS_LOCK; }
    else if (row == 3 && col == 1)  { key = KEY_A; }
    else if (row == 3 && col == 2)  { key = KEY_S; }
    else if (row == 3 && col == 3)  { key = KEY_D; }
    else if (row == 3 && col == 4)  { key = KEY_F; }
    else if (row == 3 && col == 5)  { key = KEY_G; }
    else if (row == 3 && col == 6)  { key = KEY_H; }
    else if (row == 3 && col == 7)  { key = KEY_J; }
    else if (row == 3 && col == 8)  { key = KEY_K; }
    else if (row == 3 && col == 9)  { key = KEY_L; }
    else if (row == 3 && col == 10) { key = KEY_SEMICOLON; }
    else if (row == 3 && col == 11) { key = KEY_QUOTE; }
    else if (row == 3 && col == 12) { key = 0; }
    else if (row == 3 && col == 13) { key = KEY_ENTER; }
    else if (row == 4 && col == 0)  { mods |= MODIFIERKEY_SHIFT; }
    else if (row == 4 && col == 1)  { key = 0; }
    else if (row == 4 && col == 2)  { key = KEY_Z; }
    else if (row == 4 && col == 3)  { key = KEY_X; }
    else if (row == 4 && col == 4)  { key = KEY_C; }
    else if (row == 4 && col == 5)  { key = KEY_V; }
    else if (row == 4 && col == 6)  { key = KEY_B; }
    else if (row == 4 && col == 7)  { key = KEY_N; }
    else if (row == 4 && col == 8)  { key = KEY_M; }
    else if (row == 4 && col == 9)  { key = KEY_COMMA; }
    else if (row == 4 && col == 10) { key = KEY_PERIOD; }
    else if (row == 4 && col == 11) { key = KEY_SLASH; }
    else if (row == 4 && col == 12) { key = 0; }
    else if (row == 4 && col == 13) { mods |= MODIFIERKEY_RIGHT_SHIFT; }
    else if (row == 5 && col == 0)  { key = KEY_PAGE_UP; }
    else if (row == 5 && col == 1)  { key = 0x65; } /* MENU */
    else if (row == 5 && col == 2)  { mods |= MODIFIERKEY_CTRL | MODIFIERKEY_ALT | MODIFIERKEY_GUI; } /* FN */
    else if (row == 5 && col == 3)  { key = 0; }
    else if (row == 5 && col == 4)  { mods |= MODIFIERKEY_ALT; }
    else if (row == 5 && col == 5)  { key = 0; }
    else if (row == 5 && col == 6)  { key = KEY_SPACE; }
    else if (row == 5 && col == 7)  { key = 0; }
    else if (row == 5 && col == 8)  { mods |= MODIFIERKEY_RIGHT_ALT; }
    else if (row == 5 && col == 9)  { key = 0; }
    else if (row == 5 && col == 10) { mods |= MODIFIERKEY_CTRL | MODIFIERKEY_ALT | MODIFIERKEY_GUI; } /* FN */
    else if (row == 5 && col == 11) { key = KEY_HOME; }
    else if (row == 5 && col == 12) { key = KEY_UP; }
    else if (row == 5 && col == 13) { key = KEY_END; }
    else if (row == 6 && col == 0)  { key = KEY_PAGE_DOWN; }
    else if (row == 6 && col == 1)  { key = KEY_INSERT; }
    else if (row == 6 && col == 2)  { mods |= MODIFIERKEY_GUI; }
    else if (row == 6 && col == 3)  { key = 0; }
    else if (row == 6 && col == 4)  { mods |= MODIFIERKEY_CTRL; }
    else if (row == 6 && col == 5)  { key = 0; }
    else if (row == 6 && col == 6)  { mods |= MODIFIERKEY_RIGHT_GUI; } /* HYPER: right super. Make xkb interpret right super as hyper by editing entry in /usr/share/X11/xkb/symbols/pc */
    else if (row == 6 && col == 7)  { key = 0; }
    else if (row == 6 && col == 8)  { mods |= MODIFIERKEY_RIGHT_CTRL; }
    else if (row == 6 && col == 9)  { key = 0; }
    else if (row == 6 && col == 10) { mods |= MODIFIERKEY_GUI; }
    else if (row == 6 && col == 11) { key = KEY_LEFT; }
    else if (row == 6 && col == 12) { key = KEY_DOWN; }
    else if (row == 6 && col == 13) { key = KEY_RIGHT; }
    return key;
}

int row_col_colemak(int row, int col) {
    int key = 0;
    if (row == 0 && col == 0) { key = KEY_ESC; }
    else if (row == 0 && col == 1)  { key = KEY_F1; }
    else if (row == 0 && col == 2)  { key = KEY_F2; }
    else if (row == 0 && col == 3)  { key = KEY_F3; }
    else if (row == 0 && col == 4)  { key = KEY_F4; }
    else if (row == 0 && col == 5)  { key = KEY_F5; }
    else if (row == 0 && col == 6)  { key = KEY_F6; }
    else if (row == 0 && col == 7)  { key = KEY_F7; }
    else if (row == 0 && col == 8)  { key = KEY_F8; }
    else if (row == 0 && col == 9)  { key = KEY_F9; }
    else if (row == 0 && col == 10) { key = KEY_F10; }
    else if (row == 0 && col == 11) { key = KEY_F11; }
    else if (row == 0 && col == 12) { key = KEY_F12; }
    else if (row == 0 && col == 13) { key = KEY_DELETE; }
    else if (row == 1 && col == 0)  { key = KEY_TILDE; }
    else if (row == 1 && col == 1)  { key = KEY_1; }
    else if (row == 1 && col == 2)  { key = KEY_2; }
    else if (row == 1 && col == 3)  { key = KEY_3; }
    else if (row == 1 && col == 4)  { key = KEY_4; }
    else if (row == 1 && col == 5)  { key = KEY_5; }
    else if (row == 1 && col == 6)  { key = KEY_6; }
    else if (row == 1 && col == 7)  { key = KEY_7; }
    else if (row == 1 && col == 8)  { key = KEY_8; }
    else if (row == 1 && col == 9)  { key = KEY_9; }
    else if (row == 1 && col == 10) { key = KEY_0; }
    else if (row == 1 && col == 11) { key = KEY_MINUS; }
    else if (row == 1 && col == 12) { key = KEY_EQUAL; }
    else if (row == 1 && col == 13) { key = KEY_BACKSPACE; }
    else if (row == 2 && col == 0)  { key = KEY_TAB; }
    else if (row == 2 && col == 1)  { key = KEY_Q; }
    else if (row == 2 && col == 2)  { key = KEY_W; }
    else if (row == 2 && col == 3)  { key = KEY_F; }
    else if (row == 2 && col == 4)  { key = KEY_P; }
    else if (row == 2 && col == 5)  { key = KEY_G; }
    else if (row == 2 && col == 6)  { key = KEY_J; }
    else if (row == 2 && col == 7)  { key = KEY_L; }
    else if (row == 2 && col == 8)  { key = KEY_U; }
    else if (row == 2 && col == 9)  { key = KEY_Y; }
    else if (row == 2 && col == 10) { key = KEY_SEMICOLON; }
    else if (row == 2 && col == 11) { key = KEY_LEFT_BRACE; }
    else if (row == 2 && col == 12) { key = KEY_RIGHT_BRACE; }
    else if (row == 2 && col == 13) { key = KEY_BACKSLASH; }
    else if (row == 3 && col == 0)  { key = KEY_CAPS_LOCK; }
    else if (row == 3 && col == 1)  { key = KEY_A; }
    else if (row == 3 && col == 2)  { key = KEY_R; }
    else if (row == 3 && col == 3)  { key = KEY_S; }
    else if (row == 3 && col == 4)  { key = KEY_T; }
    else if (row == 3 && col == 5)  { key = KEY_D; }
    else if (row == 3 && col == 6)  { key = KEY_H; }
    else if (row == 3 && col == 7)  { key = KEY_N; }
    else if (row == 3 && col == 8)  { key = KEY_E; }
    else if (row == 3 && col == 9)  { key = KEY_I; }
    else if (row == 3 && col == 10) { key = KEY_O; }
    else if (row == 3 && col == 11) { key = KEY_QUOTE; }
    else if (row == 3 && col == 12) { key = 0; }
    else if (row == 3 && col == 13) { key = KEY_ENTER; }
    else if (row == 4 && col == 0)  { mods |= MODIFIERKEY_SHIFT; }
    else if (row == 4 && col == 1)  { key = 0; }
    else if (row == 4 && col == 2)  { key = KEY_Z; }
    else if (row == 4 && col == 3)  { key = KEY_X; }
    else if (row == 4 && col == 4)  { key = KEY_C; }
    else if (row == 4 && col == 5)  { key = KEY_V; }
    else if (row == 4 && col == 6)  { key = KEY_B; }
    else if (row == 4 && col == 7)  { key = KEY_K; }
    else if (row == 4 && col == 8)  { key = KEY_M; }
    else if (row == 4 && col == 9)  { key = KEY_COMMA; }
    else if (row == 4 && col == 10) { key = KEY_PERIOD; }
    else if (row == 4 && col == 11) { key = KEY_SLASH; }
    else if (row == 4 && col == 12) { key = 0; }
    else if (row == 4 && col == 13) { mods |= MODIFIERKEY_RIGHT_SHIFT; }
    else if (row == 5 && col == 0)  { key = KEY_PAGE_UP; }
    else if (row == 5 && col == 1)  { key = 0x65; } /* MENU */
    else if (row == 5 && col == 2)  { mods |= MODIFIERKEY_CTRL | MODIFIERKEY_ALT | MODIFIERKEY_GUI; } /* FN */
    else if (row == 5 && col == 3)  { key = 0; }
    else if (row == 5 && col == 4)  { mods |= MODIFIERKEY_ALT; }
    else if (row == 5 && col == 5)  { key = 0; }
    else if (row == 5 && col == 6)  { key = KEY_SPACE; }
    else if (row == 5 && col == 7)  { key = 0; }
    else if (row == 5 && col == 8)  { mods |= MODIFIERKEY_RIGHT_ALT; }
    else if (row == 5 && col == 9)  { key = 0; }
    else if (row == 5 && col == 10) { mods |= MODIFIERKEY_CTRL | MODIFIERKEY_ALT | MODIFIERKEY_GUI; } /* FN */
    else if (row == 5 && col == 11) { key = KEY_HOME; }
    else if (row == 5 && col == 12) { key = KEY_UP; }
    else if (row == 5 && col == 13) { key = KEY_END; }
    else if (row == 6 && col == 0)  { key = KEY_PAGE_DOWN; }
    else if (row == 6 && col == 1)  { key = KEY_INSERT; }
    else if (row == 6 && col == 2)  { mods |= MODIFIERKEY_GUI; }
    else if (row == 6 && col == 3)  { key = 0; }
    else if (row == 6 && col == 4)  { mods |= MODIFIERKEY_CTRL; }
    else if (row == 6 && col == 5)  { key = 0; }
    else if (row == 6 && col == 6)  { mods |= MODIFIERKEY_RIGHT_GUI; } /* HYPER: right super. Make xkb interpret right super as hyper by editing entry in /usr/share/X11/xkb/symbols/pc */
    else if (row == 6 && col == 7)  { key = 0; }
    else if (row == 6 && col == 8)  { mods |= MODIFIERKEY_RIGHT_CTRL; }
    else if (row == 6 && col == 9)  { key = 0; }
    else if (row == 6 && col == 10) { mods |= MODIFIERKEY_GUI; }
    else if (row == 6 && col == 11) { key = KEY_LEFT; }
    else if (row == 6 && col == 12) { key = KEY_DOWN; }
    else if (row == 6 && col == 13) { key = KEY_RIGHT; }
    return key;
}
