/* 
 * File:   smallItem.cpp
 * Author: mohheader
 * 
 * Created on January 25, 2015, 10:58 AM
 */

#include "SmallItem.h"
USING_NS_CC;
bool SmallItem::init() {
    if(ui::Layout::init()){
        setContentSize(Size(120,120));
        setLayoutType(ui::Layout::Type::ABSOLUTE);
        auto i = ui::ImageView::create(YELLOW_SQUARE_IMAGE);
        i->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        i->setScale(0.50);
        i->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
        addChild(i);
        return true;
    }
    return false;
}

void SmallItem::setImage(std::string image) {
    auto i = ui::ImageView::create("images/fruits/"+image+IMAGE_SUFFIX);
    i->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    i->setScale(0.50);
    i->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    addChild(i);
    name = image;
}