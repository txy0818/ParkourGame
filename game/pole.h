#pragma once

#include"obstacle.h"

class Pole :public Obstacle {
public:
	Pole(Hero& hero_obs);
	virtual bool obs_Hit();
};
