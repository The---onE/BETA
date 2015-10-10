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
	bool effectFlag; //��Ч��־
	DialogLayer* dialog; //�Ի���
	BackGroundLayer* bg; //������
	PlayerLayer* player; //���ǲ�
	Vector<Bullet*> bullets; //�ӵ���
	Vector<Trash*> trashs; //С����
	EnemyLayer* enemy; //Boss��
	Vector<Danmaku*> danmakus; //��Ļ��

	StateMachine* stateMachine; //״̬��

	float trashSpeed;
	float bulletSpeed;

	bool bossFlag;

	int score;

public:
	CREATE_FUNC(GameScene);
	bool init();

	void initDialog(); //��ʼ���Ի���
	bool isDialogFinish() { return dialog->isFinish(); } //�Ի��Ƿ����
	void removeDialog(); //�Ի�����
	void initBackGround();

	void setTrashSpeed(float s);
	void setBulletSpeed(float s);

	void initTrash(); //��ʼ��С��
	void attack(); //���Ƿ����ӵ�
	void checkBullet(); //�ӵ������ƶ�������ӵ��Ƴ���Ļ��������ཻ
	void trashAttack(); //С�ֽ���
	void checkTrash(); //С�������ƶ������С���Ƴ���Ļ

	int getScore();

	void initBoss(); //��ʼ��Boss
	void danmakuAttack(int num, int angelDeg, int speed); //Boss��Ļ����
	void P2P(Point Aim, Point Source, int num, int angelDeg, int speed);
	void createDanmaku(string filename, Point& pos, Point& aim, int dis, int speed);
	void checkDanmaku(); //��鵯Ļ�Ƴ���Ļ�� �������ཻ

	bool checkLose(); //����Ƿ���Ϸʧ��
	void lose();
	bool checkWin();
	void win();

	void setEffectFlag(bool flag); //������Ч��־

	StateMachine* getStateMachine(); //����״̬��ָ��
	void update(float dt);

	void createQuitButton(string normal, string selected);
	void quitGame(Ref* pSender); //�˳���Ϸ
};

