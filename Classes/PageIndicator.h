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
    void addPage();
    static PageIndicator* create();
//private:
    std::vector<PageIndicatorItem* > list;
};

#endif	/* PAGEINDECATOR_H */

