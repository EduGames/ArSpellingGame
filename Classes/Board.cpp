/* 
 * File:   Board.cpp
 * Author: mohheader
 * 
 * Created on January 20, 2015, 11:06 PM
 */

#include "Board.h"
USING_NS_CC;

Board* Board::createWithLetter(const char name) {
    Board *widget = new (std::nothrow) Board;
    if (widget && widget->init("images/ui/board.png", TextureResType::LOCAL) && widget->initWithLetter(name)) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool Board::initWithLetter(const char c) {
    setName(&c);
    setScale(0.5);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    auto text = ui::Text::create();
    text->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    text->setString(&c);
    text->setPosition(Vec2(25,30));
    text->setFontSize(35);
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
