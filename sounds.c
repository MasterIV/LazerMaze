void init_sound() {
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;
}

void move_cursor_sound() {
    NR10_REG = 0x15;
    NR11_REG = 0x96;
    NR12_REG = 0x73;
    NR13_REG = 0xBB;
    NR14_REG = 0x85;
}

void explosion_sound() {
    NR41_REG = 0x00;
    NR42_REG = 0xB8;
    NR43_REG = 0x7B;
    NR44_REG = 0xC0;
}

void victory_sound() {
    NR10_REG = 0x77;
    NR11_REG = 0x07;
    NR12_REG = 0xF7;
    NR13_REG = 0xA4;
    NR14_REG = 0x86;

    delay(1250);

    NR10_REG = 0x53;
    NR11_REG = 0x00;
    NR12_REG = 0xF7;
    NR13_REG = 0xE2;
    NR14_REG = 0x84;
    delay(100);

    NR10_REG = 0x53;
    NR11_REG = 0x00;
    NR12_REG = 0xF7;
    NR13_REG = 0xE2;
    NR14_REG = 0x84;
}

void game_over_sound() {
    NR10_REG = 0x4F;
    NR11_REG = 0x96;
    NR12_REG = 0xB7;
    NR13_REG = 0xBB;
    NR14_REG = 0x85;
}

void random_music() {
    UBYTE i;
    for(i=0;i!=6;i++) {
        NR21_REG = 0x00;
        NR22_REG = 0xF1;
        NR23_REG = 0xB6;
        NR24_REG = 0x83;

        delay(170);
    }

    for(i=0;i!=6;i++) {
        NR21_REG = 0x00;
        NR22_REG = 0xB1;
        NR23_REG = 0xE2;
        NR24_REG = 0x84;

        delay(170);
    }

    for(i=0;i!=6;i++) {
        NR21_REG = 0x80;
        NR22_REG = 0xB1;
        NR23_REG = 0x0E;
        NR24_REG = 0x86;

        delay(170);
    }

    for(i=0;i!=6;i++) {
        NR21_REG = 0x40;
        NR22_REG = 0xB1;
        NR23_REG = 0x58;
        NR24_REG = 0x82;

        delay(170);
    }
}
