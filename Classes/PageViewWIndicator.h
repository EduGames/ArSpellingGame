/* 
 * File:   ItemsPageView.h
 * Author: mohheader
 *
 * Created on January 17, 2015, 10:30 AM
 */

#ifndef PAGEVIEWWINDICATOR_H
#define	PAGEVIEWWINDICATOR_H

#include "cocos2d.h"
#include <ui/CocosGUI.h>
class PageViewWIndicator : public cocos2d::ui::PageView{
public:
    CREATE_FUNC(PageViewWIndicator);
    static PageViewWIndicator* createW();
private:

};

#endif	/* PAGEVIEWWINDICATOR_H */

