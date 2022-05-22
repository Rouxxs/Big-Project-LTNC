#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>

class Highscore
{
public:
    std::string name;
    int recent;
	int score;

    Highscore();
};

#endif