/* 
 * File:   MenuItem.cpp
 * Author: mohheader
 * 
 * Created on January 15, 2015, 6:27 PM
 */

#include "Item.h"
USING_NS_CC;
bool Item::init() {
    if(ui::Layout::init()){
        setContentSize(Size(120,120));
        setLayoutType(ui::Layout::Type::ABSOLUTE);
        auto i = ui::ImageView::create(YELLOW_SQUARE_IMAGE);
        i->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        i->setScale(0.40);
        i->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
        addChild(i);
        return true;
    }
    return false;
}

void Item::setImage(std::string image) {
    auto i = ui::ImageView::create("images/objects/"+image+IMAGE_SUFFIX);
    i->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    i->setScale(0.40);
    i->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    addChild(i);
    name = image;
}