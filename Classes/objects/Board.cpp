/* 
 * File:   Board.cpp
 * Author: mohheader
 * 
 * Created on January 20, 2015, 11:06 PM
 */

#include "Board.h"
USING_NS_CC;

Board* Board::createWithLetter(const std::string name) {
    Board *widget = new (std::nothrow) Board;
    if (widget && widget->init("images/ui/board-hd.png", TextureResType::LOCAL) && widget->initWithLetter(name)) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool Board::initWithLetter(const std::string c) {
    setName(c);
    setScale(0.5);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    auto text = ui::Text::create();
    text->setFontName("fonts/font.ttf");
    text->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    text->setString(c);
    text->setPosition(Vec2(50,60));
    text->setFontSize(70);
    addChild(text);
    return true;
}

void Board::setOriginalPosition(const Vec2 & p) {
    setPosition(p);
    _originalPosition = p;
}

cocos2d::Vec2 Board::getOriginalPosition() {
    return _originalPosition;
}
