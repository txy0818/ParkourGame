#include"globalNumber.h"

HWND hwnd;
Hero hero(6);
Tortoise tortoise(hero);
Pole pole(hero);
Gold gold(hero);
Obstacle* obstacle[3] = { &tortoise,&pole,&gold };
//不能使用引用的数组

bool isdistance_obs = false;

bool isSwitch_enter = false;
bool isSwitch_exit = false;

bool isInit = false;
bool isput = false;

bool ishistory = false;
bool isreturn = false;
bool exit_game = false;
bool isexit = false;//游戏结束后的窗口转换
bool isrestart = false;

IMAGE init_bk;
IMAGE game_description;
IMAGE game_bk;
IMAGE exit_face;
IMAGE history_score;
IMAGE grade1;
IMAGE grade2;

int timecount = 0;
int bk_x = 0;

int grade_x = 10;
int grade_y = 10;
int score = 0;
int score_max = 0;

void controlmusic_obs() {

	mciSendString(_T("close ./music/hit.wav"), 0, 0, 0);//在easyx中
	mciSendString(_T("open ./music/hit.wav"), 0, 0, 0);
	mciSendString(_T("play ./music/hit.wav"), 0, 0, 0);

	mciSendString(_T("close ./music/bkmusic.mp3"), 0, 0, 0);
}
void controlmusic_gol() {

	mciSendString(_T("close ./music/golden.wav"), 0, 0, 0);
	mciSendString(_T("open ./music/golden.wav"), 0, 0, 0);
	mciSendString(_T("play ./music/golden.wav"), 0, 0, 0);
}

void Mapscore(int score, int x, int y, int scale) {

	//atoi不行
	IMAGE num1[10];
	IMAGE num2[10];//定义
	//char name[30];
	//for (int i = 0; i < 10; i++) {//0-9
	//	sprintf(name, "./images/%d.png", i);
	//	loadimage(&num2[i], name, scale, scale);

	//	sprintf(name, "./images/0%d.png", i);
	//	loadimage(&num1[i], name, scale, scale);//_T,TEXT,_TEXT,L都是用在字符串常量的  
	//	//不用考虑移植性写_T()了，因为_T(无名字符串常量)，_T("123");  不能char* p/char p[10];  _T(p); 错误
	//}
	////atoi不行
	//char str[30] = { 0 };
	//sprintf(str, "%d", score);//还是移植性问题
	//for (int i = 0; str[i] != '\0'; i++) {//写成  for (int i = 0; str[i] ; i++)

	//	int n = str[i] - '0';
	//	putimage(x, y, &num1[n], SRCAND);
	//	putimage(x, y, &num2[n], SRCPAINT);
	//	x += num1[0].getwidth() + 5;
	//}

	TCHAR name[30] = { 0 };
	for (int i = 0; i < 10; i++) {//0-9
		_stprintf(name, _T("./images/%d.png"), i);
		loadimage(&num2[i], name, scale, scale);

		_stprintf(name, _T("./images/0%d.png"), i);
		loadimage(&num1[i], name, scale, scale);//_T,TEXT,_TEXT,L都是用在字符串常量的  
		//不用考虑移植性写_T()了，因为_T(无名字符串常量)，_T("123");  不能char* p/char p[10];  _T(p); 错误
	}
	//atoi不行
	TCHAR str[30] = { 0 };
	_stprintf(str, _T("%d"), score);//还是移植性问题
	for (int i = 0; str[i] != '\0'; i++) {//写成  for (int i = 0; str[i] ; i++)

		int n = str[i] - '0';
		putimage(x, y, &num1[n], SRCAND);
		putimage(x, y, &num2[n], SRCPAINT);
		x += num1[0].getwidth() + 5;
	}

}

bool SwitchInterface(ExMessage msg, int x1, int x2, int y1, int y2) {

	if (msg.x >= x1 && msg.x <= x2 && msg.y >= y1 && msg.y <= y2) {
		return true;
	}
	return false;
}


void judgehitAndmoveposition() {

	if (isInit) {

		for (auto i : obstacle) {
			if (i->isExist) {
				if (i->number == TORTOISE || i->number == POLE) {

					if (i->obs_Hit()) {
						controlmusic_obs();
						hero.heroJump = false;//也可以写在主函数中
						hero.heroSlip = false;//防止（1）在下滑时或跳跃时撞上的情况，如果不写这2句，重玩时会为下滑或跳跃
						/*obstacle[0]->isCross = false;
						obstacle[1]->isCross = false;*///必须写  有可能撞柱子时，乌龟还未离开屏幕，之后重玩或返回首页再玩跳跃乌龟不加分

						Sleep(30);//防止碰撞声还没完就贴了结束图片
						BeginBatchDraw();
						putimage(0, 0, &exit_face);
						FlushBatchDraw();
						isexit = true;
						if (score_max < score) {
							score_max = score;
						}
						break;
					}
					else if (hero.hero_x > i->x + i->img1.getwidth() && !i->isCross) {
						i->isCross = true;
						score += i->single_score;
					}
				}
				else {
					if (i->obs_Hit()) {
						controlmusic_gol();

						i->x = rand() % WIN_WIDTH + WIN_WIDTH;
						i->isExist = true;
						score += i->single_score;
					}

				}

			}

		}

		//下标移动和坐标的移动
		bk_x -= BK_Speed;
		if (bk_x == -WIN_WIDTH) {
			bk_x = 0;
		}

		for (int i = 0; i < 3; i++) {
			if (obstacle[i]->isExist) {
				obstacle[i]->x -= obstacle[i]->speed;
			}
		}
		hero.jumpandslip();
	}

}


void Maps() {


	//障碍物的游戏中的设置  2种方法:（1）按while循环次数设置障碍物  （2）直接设置障碍物   我用第二种
	//static int frame = 0;
	//int re_frame = 200;
	//frame += 5;
	//if (frame >= re_frame) {
	//	if (!isTortoise) {
	//		isTortoise = true;
	//		//tortoise_x = rand() % (2 * WIN_WIDTH) + WIN_WIDTH;
	//		tortoise_x = WIN_WIDTH+tortoise1.getwidth();
	//	}
	//	re_frame = rand() % 101 + 200;//200-300
	//}

	if (isInit) {

		for (int i = 0; i < 3; i++) {
			if (!obstacle[i]->isExist) {
				obstacle[i]->isExist = true;
				obstacle[i]->isCross = false;
				obstacle[i]->x = rand() % obstacle[i]->interval + WIN_WIDTH;
			}
			if (obstacle[i]->obs_leaveScreen()) {
				obstacle[i]->isCross = false;
				obstacle[i]->isExist = false;
			}
		}

		if (obstacle[1]->obs_leaveScreen()) {
			isdistance_obs = false;
		}

	}


	//为什么写在这个位置：写在controlgame中不行，因为只有消息传入才执行，那判断柱子出现在屏幕的及时性没了
	// 
	//防止屏幕上乌龟和柱子在人物准备跨越障碍物时而乌龟和柱子在同一位置使人物必然死亡的解决方案
	//(1)当乌龟比柱子先出现在屏幕上，无该情况
	//(2)当柱子先出现在屏幕上，就会有这种情况，我的方法：当柱子已出现在屏幕，如果乌龟存在且未在屏幕，将乌龟与柱子距离调大些，防止这种情况的发生
	if (obstacle[1]->obs_inScreen() && !isdistance_obs) {

		//测试
		//cout << "pole <<<<" << endl;
		//cout << "pole x:" << obstacle[1]->x << endl;
		//cout << "pole  >>>" << endl;

		if (obstacle[0]->isExist && !obstacle[0]->obs_inScreen() && !obstacle[0]->obs_leaveScreen()) {
			//cout << "see>>>>" << endl;
			//cout << "tortoise  x  原:" << obstacle[0]->x << endl;
			//cout << "set<<<<<<" << endl;
			while (true) {
				if (obstacle[0]->x - obstacle[1]->x - obstacle[1]->img1.getwidth() > 700) {
					isdistance_obs = true;
					//cout << "watch<<<<<<" << endl;
					//cout << "tortoise  x:" << obstacle[0]->x << endl;
					//cout << "watch<<<<<<" << endl;
					break;
				}
				else {
					obstacle[0]->x = rand() % (2 * WIN_WIDTH) + WIN_WIDTH;
				}
			}


		}
	}



	BeginBatchDraw();

	//要先白底黑图  SRCAND，再黑底彩图   SRCPAINT
	if (isInit) {
		putimage(bk_x, 0, &game_bk);//贴图有顺序：如果把game_bk放在hero和成绩的代码下面，就将hero和成绩覆盖了
		putimage(grade_x, grade_y, &grade1, SRCAND);
		putimage(grade_x, grade_y, &grade2, SRCPAINT);
		Mapscore(score, 50, 20, 20);
		hero.putMaps();
		for (auto i : obstacle) {
			if (i->isExist) {
				putimage(i->x, i->y, &i->img1, SRCAND);
				putimage(i->x, i->y, &i->img2, SRCPAINT);
			}
		}
	}

	FlushBatchDraw();
	//注意：最好在贴图的前后写上双缓冲
	//注意：最好在贴图的前后写上双缓冲

}

void initgame() {

	//开启音乐
	mciSendString(_T("open ./music/bkmusic.mp3"), 0, 0, 0);
	mciSendString(_T("play ./music/bkmusic.mp3 repeat"), 0, 0, 0);

	//load一系列图片
	//背景
	loadimage(&game_bk, _T("./images/bg.png"), 2 * WIN_WIDTH, WIN_HEIGHT);

	//退出背景
	loadimage(&exit_face, _T("./images/exitface.png"), WIN_WIDTH, WIN_HEIGHT);

	//人物
	//int sprintf(char* const _Buffer,char const* const _Format,...)   （MBCS 字符集即多字节字符集的函数）
	//对于sprintf  注意第一个参数的大小》=第二个即可
	//char name[30] = { 0 };//写for里面或外面都可以
	//for (int i = 0; i < 6; i++) {
	//	sprintf(name, "./images/playerRun%d.png", i);
	//	loadimage(&hero.heroRun[1][i], name);

	//	sprintf(name, "./images/playerRun0%d.png", i);
	//	loadimage(&hero.heroRun[0][i], name);//_T,TEXT,_TEXT,L都是用在字符串常量的  
	//	//不用考虑移植性写_T()了，因为_T(无名字符串常量)，_T("123");  不能char* p/char p[10];  _T(p); 错误
	//}
	//在这我解决不了移植性
	// (1)错误
	//TCHAR* name = new TCHAR[30];//TCHAR name[30]={0};
	//for (int i = 0; i < 6; i++) {
	//	sprintf(name, "./images/playerRun0%d.png", i);//不对  sprintf第一个参数为char*
	//	loadimage(&heroRun1[i], name);
	//}
	//(2)错误
	//不能char* p/char p[10];  _T(p); 错误

	//会了  会了
	TCHAR name[30] = { 0 };
	for (int i = 0; i < 6; i++) {
		_stprintf(name, _T("./images/playerRun%d.png"), i);
		loadimage(&hero.heroRun[1][i], name);
		_stprintf(name, _T("./images/playerRun0%d.png"), i);
		loadimage(&hero.heroRun[0][i], name);

	}


	loadimage(&hero.heroSlip1, _T("./images/playerSlip0.png"));
	loadimage(&hero.heroSlip2, _T("./images/playerSlip1.png"));

	//障碍物
	loadimage(&tortoise.img1, _T("./images/tortoise0.png"), 100, 100);
	loadimage(&tortoise.img2, _T("./images/tortoise1.png"), 100, 100);

	loadimage(&pole.img1, _T("./images/pole0.png"), 50, 400);
	loadimage(&pole.img2, _T("./images/pole1.png"), 50, 400);

	loadimage(&gold.img1, _T("./images/gold0.png"));
	loadimage(&gold.img2, _T("./images/gold1.png"));

	//成绩相关
	loadimage(&grade1, _T("./images/grade0.png"), 30, 30);
	loadimage(&grade2, _T("./images/grade1.png"), 30, 30);

	//设置一些坐标
	hero.hero_x = WIN_WIDTH / 5 - hero.heroRun[0][1].getwidth() / 2;//因为人物下滑和跑步图片width都是138px
	hero.hero_y = 500 - hero.heroRun[0][1].getheight();
	hero.jumpMax = 300 - hero.heroRun[0][1].getheight();

	isInit = true;
	pole.isExist = false;
	gold.isExist = false;
	tortoise.isExist = false;
	isput = true;
}

void controlgame(ExMessage msg) {

	//游戏内操作和界面切换
	if (msg.vkcode == VK_UP) {
		hero.heroJump = true;
		isput = true;
	}

	if (msg.vkcode == VK_DOWN) {
		hero.heroSlip = true;
		isput = true;
	}

	if (msg.lbutton && !isSwitch_enter && SwitchInterface(msg, 480, 960, 540, 640)) {
		isSwitch_enter = true;
		loadimage(&game_description, _T("./images/description.png"), WIN_WIDTH, WIN_HEIGHT);
		BeginBatchDraw();
		putimage(0, 0, &game_description);
		EndBatchDraw();
	}

	if (msg.lbutton && isSwitch_enter && SwitchInterface(msg, 770, 960, 570, 640)) {
		isSwitch_enter = false;
		BeginBatchDraw();
		putimage(0, 0, &init_bk);
		EndBatchDraw();
	}

	if (msg.lbutton && !isSwitch_enter && SwitchInterface(msg, 0, 550, 480, 640)) {
		initgame();
	}

}

int getdelay() {

	static unsigned long long last = 0;
	unsigned long long current = GetTickCount();//单位 ms
	if (last == 0) {
		last = current;
		return 0;
	}
	else {
		int ret = current - last;
		last = current;
		return ret;
	}
}

void controlover(ExMessage msg) {
	//退出之后的尝试

	//1重新开始
	if (!isSwitch_exit && SwitchInterface(msg, 0, 960, 0, 160)) {
		isrestart = true;
	}
	//2历史记录
	if (!isSwitch_exit && SwitchInterface(msg, 0, 960, 160, 320)) {
		isSwitch_exit = true;
		ishistory = true;

		loadimage(&history_score, _T("./images/hiscore.png"), WIN_WIDTH, WIN_HEIGHT);
		BeginBatchDraw();//一定要写双缓冲，否则看不到
		putimage(0, 0, &history_score);
		Mapscore(score_max, 500, 350, 100);
		Mapscore(score, 500, 150, 100);
		FlushBatchDraw();
	}
	//3退出游戏
	if (!isSwitch_exit && SwitchInterface(msg, 0, 960, 320, 450)) {
		exit_game = true;
	}
	//4返回界面
	if (!isSwitch_exit && SwitchInterface(msg, 0, 960, 450, 640)) {
		BeginBatchDraw();
		putimage(0, 0, &init_bk);
		FlushBatchDraw();
		isreturn = true;
	}
	//必须放在下面  要不然与4会有问题
	if (isSwitch_exit && SwitchInterface(msg, 800, 960, 500, 640)) {
		isSwitch_exit = false;
		ishistory = true;
		BeginBatchDraw();
		putimage(0, 0, &exit_face);
		FlushBatchDraw();
	}
}





