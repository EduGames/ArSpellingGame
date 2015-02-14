/* 
 * File:   PageIndicatorItem.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 10:35 AM
 */

#include "PageIndicatorItem.h"
USING_NS_CC;

bool PageIndicatorItem::init() {
    if(ui::Layout::init()){
        setLayoutType(ui::LayoutType::RELATIVE);
        setContentSize(Size(35,36));
        active = ui::ImageView::create("images/ui/Screen_indicator_active-hd.png");
        active->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        active->setScale(0.5);

        inactive = ui::ImageView::create("images/ui/Screen_indicator_inactive-hd.png");
        inactive->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        inactive->setScale(0.5);
        inactive->setVisible(false);
        addChild(active);
        addChild(inactive);
        return true;
    }
    return false;
}

void PageIndicatorItem::activate() {
    inactive->setVisible(false);
}

void PageIndicatorItem::deactivate() {
    inactive->setVisible(true);
}
