/* 
 * File:   Board.cpp
 * Author: mohheader
 * 
 * Created on January 20, 2015, 11:06 PM
 */

#include "Board.h"
USING_NS_CC;

Board* Board::createWithLetter(const char name) {
    auto b = static_cast<Board*>(ui::ImageView::create("images/ui/board.png"));
    b->initWithLetter(name);
    return b;
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
}