/* 
 * File:   ItemsPageView.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 10:30 AM
 */

#include "PageViewWIndicator.h"
USING_NS_CC;
PageViewWIndicator* PageViewWIndicator::createW() {
    PageViewWIndicator* pageView = PageViewWIndicator::create();
    pageView->setTouchEnabled(true);
    pageView->setCustomScrollThreshold(0.4);
    return pageView;
}
