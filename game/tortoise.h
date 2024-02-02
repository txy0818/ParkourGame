#pragma once

#include"obstacle.h"

class Tortoise :public Obstacle {
public:

	Tortoise(Hero& hero_obs);
	virtual bool obs_Hit();
};
