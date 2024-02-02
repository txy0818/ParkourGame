//使用哪个字符集都可以

#include"globalNumber.h"
#include<Windows.h>

int main() {

	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	srand((unsigned)time(nullptr));

	//tortoise.hero = hero;//定义在全局中，此声明没有存储类或类型说明符  报错
	//pole.hero = hero;
	//gold.hero = hero;//类Gold gold;定义在全局，数据成员在全局访问不了
	//函数体外只能进行如变量或函数定义声明等，不能执行语句或调用函数
	//函数体外只能进行如变量或函数定义声明等，不能执行语句或调用函数
	//函数体外只能进行如变量或函数定义声明等，不能执行语句或调用函数

	initgraph(WIN_WIDTH, WIN_HEIGHT);
	hwnd = GetHWnd();
	SetWindowText(hwnd, _T("天天酷跑"));//增加移植性
	ExMessage msg;

	loadimage(&init_bk, _T("./images/initblk.png"), WIN_WIDTH, WIN_HEIGHT);
	putimage(0, 0, &init_bk);

	while (true) {
		while (true) {

			//思考：能用getmessage() 不能，controlgame（）中包括人物按键操作，因为游戏开始人物要连续运动，不能卡在这（只能用peekmessage）
			while (peekmessage(&msg)) {
				//513 按下鼠标左键
				//514 释放鼠标左键
				//515 双击鼠标左键
				//521 双击鼠标左键
				//512 鼠标滑动    msg.lbutton  为鼠标左键是否按下    所以点重玩后会进入peekmessage  为释放鼠标右键
				//只要点重玩或返回页面都会进入该循环，因为是左键的释放

				//键盘上键的按下和释放都是msg.vkcode 0x26（38）   下键 0x28（40）
				controlgame(msg);
			}

			timecount += getdelay();
			if (timecount >= 30) {
				timecount = 0;
				isput = true;
			}
			if (isput) {
				isput = false;
				Maps();
				judgehitAndmoveposition();//可以在这直接写碰撞检测，是因为未初始化游戏前，TOR_Hit()等都是false

				if (isexit) {
					break;
				}
			}
			//Sleep(30);//对于跳跃和下滑会有延时30ms   可以优化在贴图处加个开关，我实现一下
		}

		isInit = false;
		tortoise.isExist = false;
		pole.isExist = false;
		gold.isExist = false;
		hero.hero_y = 500 - hero.heroRun[0][1].getheight();

		while (isexit) {
			msg = getmessage(EX_MOUSE);//如果写成这样msg = getmessage();对于if (!msg.lbutton)  有很多按键都可以使该代码为TRUE，例如：上键，w，d，左键，右键很多
			//至于为什么不知道
			if (!msg.lbutton) {//鼠标左键是否按下
				continue;
			}

			controlover(msg);
			//退出
			if (exit_game) {
				return 0;
			}
			//重玩
			else if (isrestart) {
				isexit = false;
				isrestart = false;
				isInit = true;
				isput = true;
				mciSendString(_T("open ./music/bkmusic.mp3"), 0, 0, 0);
				mciSendString(_T("play ./music/bkmusic.mp3 repeat"), 0, 0, 0);
				score = 0;
				break;
			}
			//首页
			else if (isreturn) {
				isexit = false;
				isreturn = false;
				isInit = false;
				isput = false;
				score = 0;
				break;
			}
			else if (ishistory) {
				ishistory = false;
				continue;
			}
			else {//写这个是防止成绩退出时按的位置不符合else if (ishistory) 还有备用的再来一次
				continue;
			}
		}
	}
	EndBatchDraw();
	closegraph();

}

