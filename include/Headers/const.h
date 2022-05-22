#ifndef CONST_H
#define CONST_H

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720; 

const int ARENA_WIDTH = (SCREEN_WIDTH * 5);
const int ARENA_HEIGHT = (SCREEN_HEIGHT * 5);

const int MAX_KEYBOARD_KEYS = 350;
const int MAX_MOUSE_BUTTONS	= 6;

const int MAX_SND_CHANNELS = 16;

const double PI = 3.14159265358979323846;

const int PLAYER_SPEED = 6;

const int FPS = 60;

const int WORD_WIDTH = 18;
const int WORD_HEIGHT = 29;

const int GRID_SIZE = 80;

const int GRID_RENDER_WIDTH = (SCREEN_WIDTH / GRID_SIZE);
const int GRID_RENDER_HEIGHT = ((SCREEN_HEIGHT / GRID_SIZE) + 1);

const int GLYPH_WIDTH = 18;
const int GLYPH_HEIGHT = 29;

const int MAX_SCORE_NAME_LENGTH = 16;
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

enum
{
	SIDE_NONE,
	SIDE_PLAYER,
	SIDE_ENEMY
};

enum
{
	HEATH_ITEM,
	UZI_ITEM,
	SHOTGUN_ITEM,
	BONUS_POINT
};
#endif