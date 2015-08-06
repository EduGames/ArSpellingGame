/* 
 * File:   HintView.h
 * Author: mohammed
 *
 * Created on August 6, 2015, 9:30 PM
 */

#ifndef HINTVIEW_H
#define	HINTVIEW_H
#include "cocos2d.h"
#include <ui/CocosGUI.h>
#include "../scenes/GameScene.h"
#include "../vo/Word.h"
#include "helpers/soundUtils.h"

class GameScene;
class HintView : public cocos2d::Node{
public:
    static HintView* createWithWord(const Word word);
    bool initWithWord(const Word word);
    cocos2d::ui::Layout *hint_container;
    cocos2d::Sprite* hintBtn;
    bool hintShowCompleted;
    
    void showHint();
    void hideHint();
    void onHintShowCompleted();
    bool handleOnTouchBegan(cocos2d::Touch* touch);
    void handleOnTouchEnd(cocos2d::Touch* touch);
    
    void playWordsound();
    
    Word word;
private:
    
};

#endif	/* HINTVIEW_H */

