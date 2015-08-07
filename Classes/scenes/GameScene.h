/* 
 * File:   GameScene.h
 * Author: mohheader
 *
 * Created on January 17, 2015, 7:20 PM
 */

#ifndef GAMESCENE_H
#define	GAMESCENE_H
#include "cocos2d.h"
#include "objects/Board.h"
#include <ui/CocosGUI.h>
#include "objects/Item.h"
#include "gameViews/HintView.h"
#include "gameViews/MenuView.h"
#include "gameViews/GameView.h"
#include "../vo/Word.h"

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

class HintView;
class MenuView;
class GameView;

class GameScene : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(std::string item_name);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool initWithItem(std::string item_name);
    static GameScene* createWithItem(std::string item_name);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    
    void setGameSolved();
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    Item* item;
    Word word;
    
    void showNextLevelBtn();
    void initTargets();
    void initBoards();
    void initTouchEvents();
    
    void playWordsound();
    bool boardInsideScreen(Board* moving_board,cocos2d::Vec2 targetPosition);
    
    HintView* hint;
    MenuView* menu;
    GameView* game;
};

#endif	/* GAMESCENE_H */

