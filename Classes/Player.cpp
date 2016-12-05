#include "Player.h"

Player::Player() {
	_root = nullptr;
};

Player::Player(const char *csbname, cocos2d::Layer &parent) {	//以程式置入NODE
	_root = CSLoader::createNode(csbname);
	//_root->retain();
	parent.addChild(_root);
	_gun = _root->getChildByName("gun");
};

Player::Player(Node *parent) {									//處理ccStudio已置入的NODE
	_root = parent->getChildByName("Player");
	_root->retain();
	_gun = _root->getChildByName("gun");
};

Player::~Player() {
	if (_root != nullptr) _root->release();
};

void Player::update(float delta) {//查看旗標後移動
	if (_dir[0]) { //左
		_root->setPosition(_root->getPosition().x - speed * delta, _root->getPosition().y);
	}
	if (_dir[1]) { //右
		_root->setPosition(_root->getPosition().x + speed * delta, _root->getPosition().y);
	}
	if (_dir[2]) { //上
		_root->setPosition(_root->getPosition().x, _root->getPosition().y + speed * delta);
	}
	if (_dir[3]) { //下
		_root->setPosition(_root->getPosition().x, _root->getPosition().y - speed * delta);
	}

};

void Player::onKeyPressed(int callDir) {//加入方向(加入者為1，其餘0)
	
	switch (callDir)
	{
	case 1:
		_dir[0] = 1;
		break;
	case 2:
		_dir[1] = 1;
		break;
	case 3:
		_dir[2] = 1;
		break;
	case 4:
		_dir[3] = 1;
		break;
	}
};

void Player::onKeyReleased(int callDir) {//移除方向(移除者為0，其餘1)

	switch (callDir)
	{
	case 1:
		_dir[0] = 0;
		break;
	case 2:
		_dir[1] = 0;
		break;
	case 3:
		_dir[2] = 0;
		break;
	case 4:
		_dir[3] = 0;
		break;
	}
};

void Player::dirLinsten(Point mPt) {
	//取得玩家與滑鼠相對座標
	//註：滑鼠起始點為左上，世界座標為左下；所以將mPt.y加負號並做補償。可以以玩家為中心畫出四個象限
	float angleRadians = atanf(-(mPt.x - _root->getPosition().x) / (-mPt.y - _root->getPosition().y + 720));
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	//此為處理1,2與3,4象限的區隔
	if ((-mPt.y - _root->getPosition().y + 720) > 0) {
		_gun->setRotation(-angleDegrees);
	}else {
		_gun->setRotation(-angleDegrees + 180);
	}
}