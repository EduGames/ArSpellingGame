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
        setLayoutType(ui::Layout::Type::RELATIVE);
        setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        setScale(0.55);
        
        addChild(ui::ImageView::create("images/ui/yellow-square-big.png"));
        return true;
    }
    return false;
}

void Item::setImage(std::string image) {
    addChild(ui::ImageView::create("images/fruits/"+image+".png"));
}