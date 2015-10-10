#pragma once

#include "Global.h"
#include "DialogLayer.h"
#include "BackGroundLayer.h"
#include "PlayerLayer.h"
#include "Bullet.h"
#include "Trash.h"
#include "EnemyLayer.h"
#include "Danmaku.h"

#include "StateMachine.h"

class GameScene : public Scene
{
protected:
	bool effectFlag; //音效标志
	DialogLayer* dialog; //对话层
	BackGroundLayer* bg; //背景层
	PlayerLayer* player; //主角层
	Vector<Bullet*> bullets; //子弹组
	Vector<Trash*> trashs; //小怪组
	EnemyLayer* enemy; //Boss层
	Vector<Danmaku*> danmakus; //弹幕组

	StateMachine* stateMachine; //状态机

	float trashSpeed;
	float bulletSpeed;

	bool bossFlag;

	int score;

public:
	CREATE_FUNC(GameScene);
	bool init();

	void initDialog(); //初始化对话层
	bool isDialogFinish() { return dialog->isFinish(); } //对话是否结束
	void removeDialog(); //对话结束
	void initBackGround();

	void setTrashSpeed(float s);
	void setBulletSpeed(float s);

	void initTrash(); //初始化小怪
	void attack(); //主角发射子弹
	void checkBullet(); //子弹向右移动，检查子弹移出屏幕，与敌人相交
	void trashAttack(); //小怪进攻
	void checkTrash(); //小怪向左移动，检查小怪移出屏幕

	int getScore();

	void initBoss(); //初始化Boss
	void danmakuAttack(int num, int angelDeg, int speed); //Boss弹幕攻击
	void P2P(Point Aim, Point Source, int num, int angelDeg, int speed);
	void createDanmaku(string filename, Point& pos, Point& aim, int dis, int speed);
	void checkDanmaku(); //检查弹幕移出屏幕， 与主角相交

	bool checkLose(); //检查是否游戏失败
	void lose();
	bool checkWin();
	void win();

	void setEffectFlag(bool flag); //设置音效标志

	StateMachine* getStateMachine(); //返回状态机指针
	void update(float dt);

	void createQuitButton(string normal, string selected);
	void quitGame(Ref* pSender); //退出游戏
};

