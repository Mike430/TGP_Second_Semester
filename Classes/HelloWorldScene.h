#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "Game_Scene.h"
#include "ui/CocosGUI.h"
#include <string.h>
#include "SimpleAudioEngine.h"
#include "AnimationHelper.h"

using namespace std;

//=========================================//
class HelloWorld : public cocos2d::Layer
{
private:
	cocos2d::Node* _rootNode;
	cocos2d::ui::Button* _beginButton;
	cocos2d::ui::Button* _tutorialButton;
	cocos2d::Scene* _gameScene;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void BeginButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void TutorialButtonPressed(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif // __HELLOWORLD_SCENE_H__
