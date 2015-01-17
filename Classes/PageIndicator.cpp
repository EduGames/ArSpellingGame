/* 
 * File:   PageIndecator.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 10:34 AM
 */

#include "PageIndicator.h"
USING_NS_CC;
PageIndicator* PageIndicator::create() {
    PageIndicator* pi = static_cast<PageIndicator*>(ui::Layout::create());
    pi->setLayoutType(ui::Layout::Type::HORIZONTAL);

    auto lp = ui::LinearLayoutParameter::create();
    lp->setGravity(ui::LinearGravity::CENTER_HORIZONTAL);
    pi->setLayoutParameter(lp);
    
    return pi;
}

void PageIndicator::addPage() {
    setContentSize(Size(35 * (getChildrenCount() + 1),36));
    
    PageIndicatorItem* pii = PageIndicatorItem::create();
//    pii->setTag(3);
    addChild(pii);
}


