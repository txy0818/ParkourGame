#include"hero.h"
#include"globalNumber.h"

Hero::Hero(int size) {
	for (int i = 0; i < 2; i++) {
		heroRun.emplace_back(vector<IMAGE>());
		heroRun[i].resize(size);
	}//关于vector中元素的初始化，我放在了main.cpp中，也可以直接在这里初始化图片(写在下面了)

	heroJump = false;
	heroSlip = false;
	hero_index = 0;
	jumpdistance = -Jump_Speed;
}


//Hero::Hero(int size) {
//
//	heroRun.emplace_back(vector<IMAGE>());
//	for (int j = 0; j < 6; j++) {
//		IMAGE img;
//		char name[30] = { 0 };
//		sprintf(name, "./images/playerRun0%d.png", j);
//		loadimage(&img, name);
//		heroRun[0].emplace_back(img);
//	}
//	heroRun.emplace_back(vector<IMAGE>());
//	for (int j = 0; j < 6; j++) {
//		IMAGE img;
//		char name[30] = { 0 };
//		sprintf(name, "./images/playerRun%d.png", j);
//		loadimage(&img, name);
//		heroRun[1].emplace_back(img);
//	}
//	heroJump = false;
//	heroSlip = false;
//	hero_index = 0;
//	jumpdistance = -Jump_Speed;
//}


void Hero::jumpandslip() {

	if (heroJump) {
		/*isput = true;*/  //如果在这写isput = true;就会使跳跃一帧一帧连续贴图，无时间间隔   本意：sleep会使跳跃等待30ms，想按下按键就跳跃，在controlgame的相应
		//位置加isput = true;即可
		if (hero_y + heroRun[0][1].getheight() > 500) {
			jumpdistance = -Jump_Speed;
			heroJump = false;

		}

		if (hero_y < jumpMax) {
			jumpdistance = Jump_Speed;
		}
		hero_y += jumpdistance;
	}
	else if (heroSlip) {
		/*isput = true;*/
		//程序运行一次，count只会定义一次
		static int count = 1;
		if (count > 20) {
			count = 0;
			heroSlip = false;
		}
		count++;
	}
	else {
		hero_index++;
		if (hero_index == 6) {
			hero_index = 0;
		}//或hero_index=(hero_index+1)%6;
	}

}

void Hero::putMaps() {
	if (!heroSlip) {
		putimage(hero_x, hero_y, &heroRun[0][hero_index], SRCAND);
		putimage(hero_x, hero_y, &heroRun[1][hero_index], SRCPAINT);
	}
	else {
		putimage(hero_x, hero_y, &heroSlip1, SRCAND);
		putimage(hero_x, hero_y, &heroSlip2, SRCPAINT);
	}
}

