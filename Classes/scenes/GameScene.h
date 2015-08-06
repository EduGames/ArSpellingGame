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
#include "objects/HintView.h"
#include "objects/MenuView.h"
#include "../vo/Word.h"

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

class HintView;
class MenuView;
class GameScene : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(std::string item_name);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool initWithItem(std::string item_name);
    static GameScene* createWithItem(std::string item_name);

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    Item* item;
    Word word;
    
    Board* moving_board;
    cocos2d::Vector<Board*> boards;
    
    cocos2d::ui::Layout *targets_container;
    
    void checkForGameSolved();
    void setGameSolved();
    void showNextLevelBtn();
    void initTargets();
    void initBoards();
    void initTouchEvents();
    
    void playWordsound();
    bool boardInsideScreen(Board* moving_board,cocos2d::Vec2 targetPosition);
    
    HintView* hint;
    MenuView* menu;
};

#endif	/* GAMESCENE_H */

