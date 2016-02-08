#ifndef __SCORE_SCENE_H__
#define __SCORE_SCENE_H__
//=========================================//
//INCLUDES
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include <string.h>
#include "SimpleAudioEngine.h"

using namespace std;

//=========================================//

class Score_Scene : public cocos2d::Layer
{
private:
	cocos2d::Node* _rootNode;
	cocos2d::ui::Button* _playAgainButton;
	cocos2d::ui::Button* _mainMenuButton;

	cocos2d::ui::Text* player1Text;
	cocos2d::ui::Text* player2Text;

	int _leftScore, _rightScore;
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(int leftScore, int rightScore);
	void setScores(int leftScore, int rightScore);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;

	virtual void update(float deltaTime) override;

	// implement the "static create()" method manually
	CREATE_FUNC(Score_Scene);

	void PlayAgainButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
	void MainMenuButtonPressed(Ref *sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif // __SCORE_SCENE_H__