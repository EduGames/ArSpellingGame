/* 
 * File:   ItemsPageView.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 10:30 AM
 */

#include "PageViewWIndicator.h"
USING_NS_CC;

bool PageViewWIndicator::init() {
    if(ui::Layout::init()){
        setLayoutType(ui::LayoutType::VERTICAL);
        pageView = ui::PageView::create();
        pageView->setCustomScrollThreshold(0.4);
        _indicator = PageIndicator::create();
        pageView->setContentSize(Size(570,280));
        _indicator->setContentSize(Size(120,36));
        addChild(pageView);
        addChild(_indicator);
        pageView->addEventListener(CC_CALLBACK_0(PageViewWIndicator::updatePageIndicator, this));
        return true;
    }
    return false;
}

void PageViewWIndicator::addPage(Layout* page) {
    pageView->insertPage(page, 0);
    _indicator->addPage();
    updatePageIndicator();
}
void PageViewWIndicator::updatePageIndicator(){
    setCurrentPage(pageView->getCurPageIndex());
}
void PageViewWIndicator::setCurrentPage(int index){
    _indicator->setCurrentPage(index);
    pageView->scrollToPage(index);
}

int PageViewWIndicator::getPagesCount(){
    return pageView->getChildrenCount();
}