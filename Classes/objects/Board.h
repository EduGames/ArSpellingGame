/* 
 * File:   Board.h
 * Author: mohheader
 *
 * Created on January 20, 2015, 11:06 PM
 */

#ifndef BOARD_H
#define	BOARD_H
#include "cocos2d.h"
#include <ui/CocosGUI.h>
class Board : public cocos2d::ui::ImageView {
public:
    static Board* createWithLetter(const std::string name);
    bool initWithLetter(const std::string name);
    char letter;
    void setOriginalPosition(const cocos2d::Vec2 & p);
    cocos2d::Vec2 getOriginalPosition();
    
    void setIsSolved(bool s){isSolved = s;};
    bool IsSolved(){ return isSolved;};
private:
    cocos2d::Vec2 _originalPosition;
    bool isSolved;
};

#endif	/* BOARD_H */

