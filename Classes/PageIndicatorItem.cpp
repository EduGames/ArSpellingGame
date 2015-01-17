/* 
 * File:   PageIndicatorItem.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 10:35 AM
 */

#include "PageIndicatorItem.h"
USING_NS_CC;

PageIndicatorItem* PageIndicatorItem::create() {
    auto iv = static_cast<PageIndicatorItem*>(ui::ImageView::create("images/ui/Screen_indicator_inactive-hd.png"));
    iv->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    iv->setScale(0.5);
    return iv;
}
