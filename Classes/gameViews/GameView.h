/* 
 * File:   GameView.h
 * Author: mohammed
 *
 * Created on August 7, 2015, 11:06 AM
 */

#ifndef GAMEVIEW_H
#define	GAMEVIEW_H
#include "cocos2d.h"
#include "../vo/Word.h"
#include "../objects/Board.h"
#include "../scenes/GameScene.h"
#include "libs/pugixml/pugixml.hpp"

class GameScene;
class GameView : public cocos2d::Node{
public:
    static GameView* createWithWord(const Word word, GameScene* scene);
    bool initWithWord(const Word word, GameScene* scene);
    
    bool handleOnTouchBegan(cocos2d::Touch* touch);
    void handleOnTouchMoved(cocos2d::Touch* touch);
    void handleOnTouchEnded(cocos2d::Touch* touch);
    
    
    void initTargets();
    void initBoards();
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    GameScene* scene;
    Word word;
    
    
    Board* moving_board;
    cocos2d::Vector<Board*> boards;
    
    cocos2d::ui::Layout *targets_container;
    
    void setGameSolved();
    void checkForGameSolved();
    bool boardInsideScreen(Board* moving_board, cocos2d::Vec2 targetPosition);
};

#endif	/* GAMEVIEW_H */

