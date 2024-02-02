#pragma once

//或
//#ifndef _GOLD_H
//#define _GOLD_H
//#endif // !_GOLD_H

#include"obstacle.h"

class Gold :public Obstacle{
public:
	Gold(Hero& hero_obs);
	virtual bool obs_Hit();
};

