/* 
 * File:   ItemsPageView.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 10:30 AM
 */

#include "PageViewWIndicator.h"
USING_NS_CC;

PageViewWIndicator* PageViewWIndicator::create() {
    PageViewWIndicator* view = static_cast<PageViewWIndicator*>(ui::Layout::create());
    view->setLayoutType(ui::LayoutType::VERTICAL);
    view->pageView = ui::PageView::create();
    view->pageView->setTouchEnabled(true);
    view->pageView->setCustomScrollThreshold(0.4);
    view->_indicator = PageIndicator::create();
    view->pageView->setContentSize(Size(570,320));
    view->_indicator->setContentSize(Size(120,120));
    view->addChild(view->pageView);
    view->addChild(view->_indicator);

    return view;
}

void PageViewWIndicator::addPage(Layout* page) {
    pageView->addPage(page);
    _indicator->addPage();
}

void PageViewWIndicator::setContentSize(const cocos2d::Size& contentSize) {
    ui::Layout::setContentSize(contentSize);   
}
