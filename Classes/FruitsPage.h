/* 
 * File:   FruitsPage.h
 * Author: mohheader
 *
 * Created on January 15, 2015, 6:24 PM
 */

#ifndef FRUITSPAGE_H
#define	FRUITSPAGE_H
#include "cocos2d.h"
#include <ui/CocosGUI.h>
class FruitsPage : public cocos2d::ui::Layout {
public:
    CREATE_FUNC(FruitsPage);
    static FruitsPage* createWithList(cocos2d::Size size, std::vector<std ::string> images);
private:
    void addItems(std::vector<std ::string> images);
};

#endif	/* FRUITSPAGE_H */

