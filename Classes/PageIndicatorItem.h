/* 
 * File:   PageIndicatorItem.h
 * Author: mohheader
 *
 * Created on January 17, 2015, 10:35 AM
 */

#ifndef PAGEINDICATORITEM_H
#define	PAGEINDICATORITEM_H
#include "cocos2d.h"
#include <ui/CocosGUI.h>
class PageIndicatorItem : public cocos2d::ui::Layout{
public:
    CREATE_FUNC(PageIndicatorItem);
    bool init();
    void activate();
    void deactivate();
//private:
    cocos2d::ui::ImageView* active;
    cocos2d::ui::ImageView* inactive;
};

#endif	/* PAGEINDICATORITEM_H */

