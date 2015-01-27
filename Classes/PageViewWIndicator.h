/* 
 * File:   ItemsPageView.h
 * Author: mohheader
 *
 * Created on January 17, 2015, 10:30 AM
 */

#ifndef PAGEVIEWWINDICATOR_H
#define	PAGEVIEWWINDICATOR_H

#include "cocos2d.h"
#include "PageIndicator.h"
#include <ui/CocosGUI.h>
class PageViewWIndicator : public cocos2d::ui::Layout{
public:
    CREATE_FUNC(PageViewWIndicator);
    PageIndicator* _indicator;
    cocos2d::ui::PageView* pageView;
    bool init();
    void addPage(Layout* page);
    void updatePageIndicator();
    void setCurrentPage(int index);
    int getPagesCount();
private:
    
};

#endif	/* PAGEVIEWWINDICATOR_H */