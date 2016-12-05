#include "AnimationAction.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

//#define DOUBLEJUMP 1

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

AnimationAction::AnimationAction() {
	_myPlayer = nullptr;
}


Scene* AnimationAction::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AnimationAction::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

AnimationAction::~AnimationAction()
{
	if (_myPlayer != nullptr) delete _myPlayer;
	_rootM->release();
	AnimationCache::destroyInstance();  // ���� AnimationCache ���o���귽
	SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

// on "init" you need to initialize your instance
bool AnimationAction::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("AnimationAction.csb");
    addChild(rootNode);
	_rootM = rootNode->getChildByName("Mouse");
	_rootM->retain();

	_myPlayer = new Player(rootNode);
	
	/*--------------------------------------KeyBoardEvent--------------------------------------------*/
	_listenerK = EventListenerKeyboard::create();
	_listenerK->onKeyPressed = CC_CALLBACK_2(AnimationAction::onKeyPressed, this);
	_listenerK->onKeyReleased = CC_CALLBACK_2(AnimationAction::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerK, this);

	/*----------------------------------------MouseEvent---------------------------------------------*/
	_listenerM = EventListenerMouse::create();
	_listenerM->onMouseMove = CC_CALLBACK_1(AnimationAction::onMouseMove, this);
	_listenerM->onMouseDown = CC_CALLBACK_1(AnimationAction::onMouseDown, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listenerM, this);
	/*-----------------------------------------------------------------------------------------------*/

	_listener1 = EventListenerTouchOneByOne::create();	//�Ыؤ@�Ӥ@��@���ƥ��ť��
	_listener1->onTouchBegan = CC_CALLBACK_2(AnimationAction::onTouchBegan, this);		//�[�JĲ�I�}�l�ƥ�
	_listener1->onTouchMoved = CC_CALLBACK_2(AnimationAction::onTouchMoved, this);		//�[�JĲ�I���ʨƥ�
	_listener1->onTouchEnded = CC_CALLBACK_2(AnimationAction::onTouchEnded, this);		//�[�JĲ�I���}�ƥ�
	
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//�[�J��Ыت��ƥ��ť��
	this->schedule(CC_SCHEDULE_SELECTOR(AnimationAction::doStep));
    return true;
}



void AnimationAction::doStep(float dt)
{
	_myPlayer->update(dt);
	_rootM->setPosition(_mousePt.x, -_mousePt.y + 720);

	_myPlayer->dirLinsten(_mousePt);

}

bool AnimationAction::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//Ĳ�I�}�l�ƥ�
{
	Point touchLoc = pTouch->getLocation();

	return true;
}

void  AnimationAction::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I���ʨƥ�
{
	Point touchLoc = pTouch->getLocation();

}

void  AnimationAction::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //Ĳ�I�����ƥ� 
{
	Point touchLoc = pTouch->getLocation();

//	���� RotateBy ���֥[�ĪG   ---------------------------------
	//auto actionbody = this->getChildByTag(101);
	//actionbody->runAction(_myAction);
	//CCLOG("%d", actionbody->getNumberOfRunningActions());
//--------------------------------------------------------------
}

/*--------------------------------------KeyBoardEvent--------------------------------------------*/
void AnimationAction::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		_myPlayer->onKeyPressed(1);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		_myPlayer->onKeyPressed(2);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		_myPlayer->onKeyPressed(3);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		_myPlayer->onKeyPressed(4);
		break;
	}
}

void AnimationAction::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		_myPlayer->onKeyReleased(1);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		_myPlayer->onKeyReleased(2);
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		_myPlayer->onKeyReleased(3);
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		_myPlayer->onKeyReleased(4);
		break;
	}
}

void AnimationAction::onMouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	_mousePt = e->getLocation();
}

void AnimationAction::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
}

