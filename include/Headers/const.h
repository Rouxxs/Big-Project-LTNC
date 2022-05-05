#ifndef CONST_H
#define CONST_H

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720; 

const int MAX_NAME_LENGTH = 32;

const int MAX_KEYBOARD_KEYS = 350;
const int MAX_MOUSE_BUTTONS	= 6;

const int MAX_SND_CHANNELS = 16;

const double PI = 3.14159265358979323846;

const int PLAYER_SPEED = 6;

const int FPS = 60;

const int WORD_WIDTH = 18;
const int WORD_HEIGHT = 29;

const int GRID_SIZE = 64;

const int GLYPH_WIDTH = 18;
const int GLYPH_HEIGHT = 29;
enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};

enum
{
	WPN_PISTOL,
	WPN_UZI,
	WPN_SHOTGUN,
	WPN_MAX
};
#endif