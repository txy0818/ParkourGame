#include"obstacle.h"

Obstacle::Obstacle(Hero& hero_obs) :hero(hero_obs) {//数据成员为引用，必须写在初始化列表中
	isCross = false;
	isExist = true;
}

bool Obstacle::obs_leaveScreen() {

	if (x + img1.getwidth() < 0) {
		return true;
	}
	return false;
}

bool Obstacle::obs_inScreen() {

	if (x  < WIN_WIDTH && x+img1.getwidth() > 0) {
		return true;
	}
	return false;
}
