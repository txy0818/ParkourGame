#pragma once

#include<iostream>
#include<easyx.h>
#include<vector>
using namespace std;

class Hero {
public:

	int hero_x;
	int hero_y;

	bool heroJump;
	bool heroSlip;

	//IMAGE heroRun[2][6];//1  2   不能写vector，因为没load时判断obs_hit需要用vector<IMAGE> v; v[0]但现在容器中无元素报错
	//思考：也能用vector，resize就行，定义了容器中的元素但未初始化
	vector<vector<IMAGE>> heroRun;
	IMAGE heroSlip1;
	IMAGE heroSlip2;
	int hero_index;

	int jumpMax;
	int jumpdistance;

	explicit Hero(int size);
	void jumpandslip();
	void putMaps();
};
