/* 
 * File:   PageIndecator.h
 * Author: mohheader
 *
 * Created on January 17, 2015, 10:34 AM
 */

#ifndef PAGEINDECATOR_H
#define	PAGEINDECATOR_H
#include "cocos2d.h"
#include <ui/CocosGUI.h>
#include "PageIndicatorItem.h"
class PageIndicator : public cocos2d::ui::Layout{
public:
    CREATE_FUNC(PageIndicator);
    bool init();
    void addPage();
    void setCurrentPage(int index);
//private:
    std::vector<PageIndicatorItem* > list;
    cocos2d::ui::ImageView* cur_ind;
};

#endif	/* PAGEINDECATOR_H */

