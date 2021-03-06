typedef enum {
  C3, Cd3, D3, Dd3, E3, F3, Fd3, G3, Gd3, A3, Ad3, B3,
  C4, Cd4, D4, Dd4, E4, F4, Fd4, G4, Gd4, A4, Ad4, B4,
  C5, Cd5, D5, Dd5, E5, F5, Fd5, G5, Gd5, A5, Ad5, B5,
  C6, Cd6, D6, Dd6, E6, F6, Fd6, G6, Gd6, A6, Ad6, B6,
  C7, Cd7, D7, Dd7, E7, F7, Fd7, G7, Gd7, A7, Ad7, B7,
  C8, Cd8, D8, Dd8, E8, F8, Fd8, G8, Gd8, A8, Ad8, B8,
  SILENCE
} Pitch;

const UWORD frequencies[] = { //values based on a formula used by the GB processor
  44, 156, 262, 363, 457, 547, 631, 710, 786, 854, 923, 986,
  1046, 1102, 1155, 1205, 1253, 1297, 1339, 1379, 1417, 1452, 1486, 1517,
  1546, 1575, 1602, 1627, 1650, 1673, 1694, 1714, 1732, 1750, 1767, 1783,
  1798, 1812, 1825, 1837, 1849, 1860, 1871, 1881, 1890, 1899, 1907, 1915,
  1923, 1930, 1936, 1943, 1949, 1954, 1959, 1964, 1969, 1974, 1978, 1982,
  1985, 1988, 1992, 1995, 1998, 2001, 2004, 2006, 2009, 2011, 2013, 2015,
  0
};

enum DurationNote
{
    LONG = 0xF4U,
    SHORT = 0xF1U,
    LONG_LONG = 0xF7U
};

//Define Instrument names
//Instruments should be confined to one channel
//due to different registers used between ch1, 2, 3, 4
typedef enum {
	NONE,
	MELODY,  //channel 1
	HARMONY, //channel 1
	SNARE,   //channel 2
    WAVE,    //channel 3
	CYMBAL   //channel 4
} Instrument;

//Define a Note as having a Pitch, Instrument, and volume envelope
typedef struct {
	Instrument i;
	Pitch p;
	UINT16 env;
} Note;

const Note game_ch1[] = {
  {MELODY, E3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, E3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, F3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, G3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, F3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, E3, SHORT},
  {NONE, SILENCE, LONG},
  
  {MELODY, D3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, C3, SHORT},
  {NONE, SILENCE, LONG},
	
	//bar 2
	
  {MELODY, C3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, D3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, E3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, D3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, C3, SHORT},
  {NONE, SILENCE, LONG},
	
  {MELODY, C3, LONG},
  {NONE, SILENCE, LONG},
  
  {NONE, SILENCE, SHORT},
  {NONE, SILENCE, LONG},
	
  {NONE, SILENCE, SHORT},
  {NONE, SILENCE, SHORT},
};

const Note game_ch2[] = {
  {CYMBAL, G3, SHORT},
  {NONE, SILENCE, LONG_LONG},
	
  {NONE, SILENCE, LONG_LONG},
  {NONE, SILENCE, LONG_LONG},
	
  {WAVE, D3, SHORT},
  {NONE, SILENCE, LONG_LONG},
	
  {NONE, SILENCE, LONG_LONG},
  {NONE, SILENCE, LONG_LONG},
	
  {CYMBAL, G3, SHORT},
  {NONE, SILENCE, LONG_LONG},
	
  {NONE, SILENCE, LONG_LONG},
  {NONE, SILENCE, LONG_LONG},
	
  {WAVE, D3, SHORT},
  {NONE, SILENCE, LONG_LONG},
	
  {NONE, SILENCE, LONG_LONG},
  {NONE, SILENCE, LONG_LONG},
	
	//bar 2
	
	  {CYMBAL, G3, SHORT},
  {NONE, SILENCE, LONG_LONG},
	
  {NONE, SILENCE, LONG_LONG},
  {NONE, SILENCE, LONG_LONG},
	
  {WAVE, D3, SHORT},
  {NONE, SILENCE, LONG_LONG},
	
  {NONE, SILENCE, LONG_LONG},
  {NONE, SILENCE, LONG_LONG},
	
  {WAVE, G3, SHORT},
  {NONE, SILENCE, LONG_LONG},
	
  {NONE, SILENCE, LONG_LONG},
  {NONE, SILENCE, LONG_LONG},
	
  {CYMBAL, G3, SHORT},
  {CYMBAL, G3, SHORT},
	
  {NONE, SILENCE, LONG_LONG},
  {NONE, SILENCE, LONG_LONG},
};

const Note completion_notes[] = {
    {MELODY, D6, SHORT},
    {MELODY, C6, SHORT},
    {MELODY, B5, SHORT},
    {MELODY, A5, SHORT},
    {MELODY, G5, SHORT},
};
