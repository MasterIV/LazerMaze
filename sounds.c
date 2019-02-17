#include "music.c"

UBYTE timerCounter;
UBYTE currentBeat;

void init_sound() {
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;
    timerCounter = 0;
    currentBeat = 0;
}

void setNote(Note *n){
    switch((*n).i){
            case MELODY:
                    NR21_REG = 0xC6U; //wave duty
                    NR22_REG = (*n).env; //envelope
                    NR23_REG = (UBYTE)frequencies[(*n).p]; //low bits of frequency
                    NR24_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8); //high bits of frequency (and sound reset)
            break;
            case HARMONY:
                    NR21_REG = 0xC0U; //wave duty for harmony is different
                    NR22_REG = (*n).env;
                    NR23_REG = (UBYTE)frequencies[(*n).p];
                    NR24_REG = 0x80U | ((UWORD)frequencies[(*n).p]>>8);
            break;
            case SNARE:
                   
            break;
            case WAVE:
            NR41_REG = 0x3A;
                NR42_REG = 0xA1;     
                NR43_REG = 0x78;         
                NR44_REG = 0xC0U;

            break;
            case CYMBAL:
                NR41_REG = 30;
                NR42_REG = 55;     
                NR43_REG = 50;         
                NR44_REG = 0xC0U;
            break;
    }
}


void play_gameplay_music() {
    setNote(&game_ch1[currentBeat]);
    setNote(&game_ch2[currentBeat]);
}


void update_music() {
    if (timerCounter >= 7){
            timerCounter = 0;
	  
            if (currentBeat < 31) //song length - 1
            {
                currentBeat++;
            }
            else
            {
                currentBeat = 0;
            }
	  
            play_gameplay_music();
    }
  
    timerCounter++;
}

void move_cursor_sound() {
    NR10_REG = 0x4F;
    NR11_REG = 0x80;
    NR12_REG = 0x71;
    NR13_REG = 0x90;
    NR14_REG = 0x81;
}

void explosion_sound() {
    NR41_REG = 0x00;
    NR42_REG = 0xB8;
    NR43_REG = 0x7B;
    NR44_REG = 0xC0;
}

void mine_windup_sound() {
    NR10_REG = 0x7D;
    NR11_REG = 0x81;
    NR12_REG = 0xF1;
    NR13_REG = 0x7D;
    NR14_REG = 0x87;
}

void title_sound() {
    setNote(&game_ch1[0]);
    setNote(&game_ch1[1]);
    delay(150);
    setNote(&game_ch1[0]);
    setNote(&game_ch1[1]);
    delay(150);
    setNote(&game_ch1[0]);
    setNote(&game_ch1[1]);
    delay(150);

    NR10_REG = 0x15;
    NR11_REG = 0x96;
    NR12_REG = 0x73;
    NR13_REG = 0xBB;
    NR14_REG = 0x85;
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

