#pragma once

#include<easyx.h>
#include<iostream>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include"hero.h"
#include"obstacle.h"
#include"tortoise.h"
#include"pole.h"
#include"gold.h"


void controlmusic_obs();
void controlmusic_gol();
void Mapscore(int score, int x, int y, int scale);
bool SwitchInterface(ExMessage msg, int x1, int x2, int y1, int y2);
void judgehitAndmoveposition();
void Maps();
void initgame();
int getdelay();
void controlgame(ExMessage msg);
void controlover(ExMessage msg);

//头文件中对全局变量只声明不定义    int a;是定义

extern HWND hwnd;
extern Hero hero;
extern Tortoise tortoise;
extern Pole pole;
extern Gold gold;
extern Obstacle* obstacle[3];
//不能使用引用的数组

extern bool isdistance_obs;

extern bool isSwitch_enter;
extern bool isSwitch_exit;

extern bool isInit;
extern bool isput;

extern bool ishistory;
extern bool isreturn;
extern bool exit_game;
extern bool isexit;//游戏结束后的窗口转换
extern bool isrestart;

extern IMAGE init_bk;
extern IMAGE game_description;
extern IMAGE game_bk;
extern IMAGE exit_face;
extern IMAGE history_score;
extern IMAGE grade1;
extern IMAGE grade2;

extern int timecount;
extern int bk_x;

extern int grade_x;
extern int grade_y;
extern int score;
extern int score_max;

