/* 
 * File:   MenuView.h
 * Author: mohammed
 *
 * Created on August 6, 2015, 11:08 PM
 */

#ifndef MENUVIEW_H
#define	MENUVIEW_H
#include "cocos2d.h"
#include "../vo/Word.h"
#include "helpers/soundUtils.h"
#include "../scenes/GameScene.h"
#include "../scenes/MainMenuScene.h"
#include "../helpers/wordsXMLHelper.h"

class GameScene;
class MenuView : public cocos2d::Node{
public:
    static MenuView* createWithWord(const Word word);
    bool initWithWord(const Word word);
    
    void goToNextLvl();
    void playWordsound();
    void menuCloseCallback();
    void showNextLevelBtn();
    cocos2d::MenuItemImage * nxtLevelBtn;
    cocos2d::MenuItemImage * wordSoundBtn;
    Word word;
private:

};

#endif	/* MENUVIEW_H */

