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

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}


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
    std::string _item_name;
    std::string _item_name_english;
    
    Board* moving_board;
    cocos2d::Vector<Board*> boards;
    
    cocos2d::ui::Layout *targets_container;
    
    cocos2d::ui::Layout *hint_container;
    cocos2d::Sprite* hintBtn;
    bool hintShowCompleted;
    
    cocos2d::MenuItemImage * nxtLevelBtn;
    cocos2d::MenuItemImage * wordSoundBtn;
    
    void menuCloseCallback();
    void checkForGameSolved();
    void setGameSolved();
    void showNextLevelBtn();
    void initMenu();
    void initHint();
    void initTargets();
    void initBoards();
    void initTouchEvents();
    void showHint();
    void hideHint();
    void onHintShowCompleted();
    void goToNextLvl();
    
    void playWordsound();
};

#endif	/* GAMESCENE_H */

