#include "common.h"
#include "fstream"

static void capFrameRate(long *then, float *remainder);

int main(int argc, char *argv[])
{
	long then;
	float remainder;

    GameStage game;
	
	then = SDL_GetTicks();
	
	remainder = 0;

	std::ifstream ifile;
	ifile.open("text/highscores.txt", std::ios::in);
	int n = 0;
	while (!ifile.eof() && n < 8)
	{
		std::string s;
		std::getline(ifile, s, '|');
		int score = 0;
		ifile >> score;
		ifile.ignore();
		if(s != "")
			game.highscores[n].name = s;
		game.highscores[n].score = score;
		n++;
	}
	ifile.close();

	while (game.running)
	{	
		game.prepareScene();
		if (game.titleFlag == true)
		{
			game.doInput();
			game.doTitle();
			game.showTitle();
		}
		else if (game.highscoreFlag == true)
		{
			game.doInput();
			game.doHighscore();
			game.showHighscore();
		}
		else if (game.highscoreFlag != true && game.titleFlag != true)
		{
			game.doInput();
			game.logic();
			game.draw();
		}

		game.presentScene();
		capFrameRate(&then, &remainder);
	}

	std::ofstream ofile;
	ofile.open("text/highscores.txt", std::ios::trunc);
	
	for (int i = 0; i < 8; i++)
	{
		ofile << game.highscores[i].name << '|' << game.highscores[i].score << std::endl;
	}

	ofile.close();

	game.cleanup();

	return 0;
}

static void capFrameRate(long *then, float *remainder)
{
	long wait, frameTime;
	
	wait = 16 + *remainder;
	
	*remainder -= (int)*remainder;
	
	frameTime = SDL_GetTicks() - *then;
	
	wait -= frameTime;
	
	if (wait < 1)
	{
		wait = 1;
	}
		
	SDL_Delay(wait);
	
	*remainder += 0.667;
	
	*then = SDL_GetTicks();
}

