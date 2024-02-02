#include"gold.h"

Gold::Gold(Hero& hero_obs):Obstacle(hero_obs) {

	y = 420;
	single_score = 1;
	speed = 10;
	interval = WIN_WIDTH;
	number = 3;
}

bool Gold::obs_Hit() {
	if (hero.heroSlip) {
		if (hero.hero_x + hero.heroSlip1.getwidth() >= x && hero.hero_x + hero.heroSlip1.getwidth() <= x + img1.getwidth()
			&& hero.hero_y + hero.heroSlip1.getheight() >= y && hero.hero_y + hero.heroSlip1.getheight() <= y + img1.getheight() + 30) {
			return true;
		}
		return false;
	}
	else {
		if (hero.hero_x + hero.heroRun[0][1].getwidth() >= x && hero.hero_x + hero.heroRun[0][1].getwidth() <= x + img1.getwidth()
			&& hero.hero_y + hero.heroRun[0][1].getheight() >= y && hero.hero_y + hero.heroRun[0][1].getheight() <= y + img1.getheight() + 30) {
			return true;
		}
		return false;
	}

}