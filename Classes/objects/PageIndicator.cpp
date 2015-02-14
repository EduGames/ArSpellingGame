/* 
 * File:   PageIndecator.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 10:34 AM
 */

#include "PageIndicator.h"
USING_NS_CC;
bool PageIndicator::init() {
    if(ui::Layout::init()){
        setLayoutType(ui::Layout::Type::HORIZONTAL);
        auto lp = ui::LinearLayoutParameter::create();
        lp->setGravity(ui::LinearGravity::CENTER_HORIZONTAL);
        setLayoutParameter(lp);
        return true;
    }
    return false;
}

void PageIndicator::addPage() {
    setContentSize(Size(35 * (getChildrenCount() + 1),36));
    
    PageIndicatorItem* pii = PageIndicatorItem::create();
    pii->setTag(getChildrenCount());
    addChild(pii);
}

void PageIndicator::setCurrentPage(int index) {
    for(auto i : getChildren()){
        auto x = dynamic_cast<PageIndicatorItem*>(i);
        x->deactivate();
        if(x->getTag() == index) x->activate();
    }
}
