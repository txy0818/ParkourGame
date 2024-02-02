#include"tortoise.h"

Tortoise::Tortoise(Hero& hero_obs):Obstacle(hero_obs) {

	y = 420;
	single_score = 2;
	speed = 15;
	interval = 2 * WIN_WIDTH;
	number = 1;
}

bool Tortoise::obs_Hit() {

	if (hero.heroSlip) {//必须坐标判断，不能直接返回TRUE
		if (hero.hero_x + hero.heroSlip1.getwidth() >= x + 15 && hero.hero_x + hero.heroSlip1.getwidth() <= x - 15 + img1.getwidth()
			&& hero.hero_y + hero.heroSlip1.getheight() >= y + 15 && hero.hero_y + hero.heroSlip1.getheight() <= y + img1.getheight() - 15) {
			return true;
		}
		return false;
	}
	else {
		if (hero.hero_x + hero.heroRun[0][1].getwidth() >= x + 15 && hero.hero_x + hero.heroRun[0][1].getwidth() <= x - 15 + img1.getwidth()
			&& hero.hero_y + hero.heroRun[0][1].getheight() >= y + 15 && hero.hero_y + hero.heroRun[0][1].getheight() <= y + img1.getheight() - 15) {
			return true;
		}
		return false;
	}
}