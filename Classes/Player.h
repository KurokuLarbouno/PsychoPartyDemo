#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

class Player
{
public:
	Player();
	Player(const char *csbname, cocos2d::Layer &parent);
	Player(Node *parent);
	~Player();
	void update(float delta);
	void onKeyPressed(int callDir);
	void onKeyReleased(int callDir);
	void dirLinsten(Point mPt);
	int _dir[5] = { 0, 0, 0, 0 };
private:
	//byte _dir = 0000;//�N��"���k�W�U"
	float speed = 200;//����/�C��
	Node * _root;
	Node * _gun;
};

