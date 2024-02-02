#pragma once

#include"hero.h"
#include"global.h"

typedef enum {
	TORTOISE = 1,
	POLE,//2
	GOLD//3
}obstacle_type;

//抽象类（虚函数没有定义），不能实例化
class Obstacle {
public:
	Hero& hero;//为啥写引用，因为如果写指针，还要析构释放，但3个派生类都想要同一hero，析构时必然会出现问题
	int x;
	int y;
	int number;
	int speed;
	int interval;
	bool isExist;
	bool isCross;
	IMAGE img1;
	IMAGE img2;
	int single_score;

	Obstacle(Hero& hero_obs);
	virtual bool obs_Hit() = 0;
	bool obs_leaveScreen();
	bool obs_inScreen();
};
