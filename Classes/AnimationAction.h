#ifndef __ANIMATIONACTION_SCENE_H__
#define __ANIMATIONACTION_SCENE_H__


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

#include "Player.h"

using namespace cocos2d;

class AnimationAction : public cocos2d::Layer
{
private:
	Point _mousePt = (Point(0.0f, 0.0f));
	Player *_myPlayer;
	Node *_rootM;
	int dir[5];
public:
	AnimationAction();
	~AnimationAction();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void doStep(float dt);

	//keyboard
	cocos2d::EventListenerKeyboard *_listenerK;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);//觸碰開始事件
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event); //觸碰結束事件 

	//mouse
	cocos2d::EventListenerMouse *_listenerM;
	void onMouseMove(Event *event);
	void onMouseDown(Event *event);
	//觸碰
	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	// implement the "static create()" method manually
    CREATE_FUNC(AnimationAction);
};

#endif // __HELLOWORLD_SCENE_H__
