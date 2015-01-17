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
    PageIndicator* _indicator;
    cocos2d::ui::PageView* pageView;
    static PageViewWIndicator* create();
    void addPage(Layout* page);
    void setContentSize(const cocos2d::Size& contentSize);
private:
    
};

#endif	/* PAGEVIEWWINDICATOR_H */