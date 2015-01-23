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
    static Board* createWithLetter(const char name);
    bool initWithLetter(const char name);
    char letter;
//    CC_SYNTHESIZE(cocos2d::Vec2, _originalPosition, OriginalPosition);
private:
};

#endif	/* BOARD_H */

