#include"pole.h"


Pole::Pole(Hero& hero_obs):Obstacle(hero_obs) {

	y = 0;
	single_score = 3;
	speed = 10;
	interval = 3 * WIN_WIDTH;
	number = 2;
}

bool Pole::obs_Hit() {
	if (hero.heroSlip) {
		if (hero.hero_x + hero.heroSlip1.getwidth() >= x + 10 && hero.hero_x + hero.heroSlip1.getwidth() <= x + img1.getwidth() - 10
			&& hero.hero_y >= y + 20 && hero.hero_y <= y + img1.getheight() - 50) {
			return true;
		}
		return false;
	}
	else {//为什么修改的时候直接运行开始就pole碰撞，原因：先写的碰撞检测，再写的各种物体的坐标移动
		//现在我先写坐标移动再写碰撞检测（不行）  改改
		//就应该先写的碰撞检测，再写的各种物体的坐标移动  
		if (hero.hero_x + hero.heroRun[0][1].getwidth() >= x && hero.hero_x + hero.heroRun[0][1].getwidth() <= x + img1.getwidth()
			&& hero.hero_y > y && hero.hero_y < y + img1.getheight()) {
			return true;
		}
		return false;
	}
}
