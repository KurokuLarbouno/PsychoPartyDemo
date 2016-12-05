#include "Player.h"

Player::Player() {
	_root = nullptr;
};

Player::Player(const char *csbname, cocos2d::Layer &parent) {	//�H�{���m�JNODE
	_root = CSLoader::createNode(csbname);
	//_root->retain();
	parent.addChild(_root);
	_gun = _root->getChildByName("gun");
};

Player::Player(Node *parent) {									//�B�zccStudio�w�m�J��NODE
	_root = parent->getChildByName("Player");
	_root->retain();
	_gun = _root->getChildByName("gun");
};

Player::~Player() {
	if (_root != nullptr) _root->release();
};

void Player::update(float delta) {//�d�ݺX�ЫᲾ��
	if (_dir[0]) { //��
		_root->setPosition(_root->getPosition().x - speed * delta, _root->getPosition().y);
	}
	if (_dir[1]) { //�k
		_root->setPosition(_root->getPosition().x + speed * delta, _root->getPosition().y);
	}
	if (_dir[2]) { //�W
		_root->setPosition(_root->getPosition().x, _root->getPosition().y + speed * delta);
	}
	if (_dir[3]) { //�U
		_root->setPosition(_root->getPosition().x, _root->getPosition().y - speed * delta);
	}

};

void Player::onKeyPressed(int callDir) {//�[�J��V(�[�J�̬�1�A��l0)
	
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

void Player::onKeyReleased(int callDir) {//������V(�����̬�0�A��l1)

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
	//���o���a�P�ƹ��۹�y��
	//���G�ƹ��_�l�I�����W�A�@�ɮy�Ь����U�F�ҥH�NmPt.y�[�t���ð����v�C�i�H�H���a�����ߵe�X�|�ӶH��
	float angleRadians = atanf(-(mPt.x - _root->getPosition().x) / (-mPt.y - _root->getPosition().y + 720));
	float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
	//�����B�z1,2�P3,4�H�����Ϲj
	if ((-mPt.y - _root->getPosition().y + 720) > 0) {
		_gun->setRotation(-angleDegrees);
	}else {
		_gun->setRotation(-angleDegrees + 180);
	}
}