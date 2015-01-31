/* 
 * File:   MenuItem.h
 * Author: mohheader
 *
 * Created on January 15, 2015, 6:27 PM
 */

#ifndef ITEM_H
#define	ITEM_H
#include "cocos2d.h"
#include <ui/CocosGUI.h>
class Item : public cocos2d::ui::Layout {
public:
    CREATE_FUNC(Item);
    bool init();
    void setImage(std::string image);
    std::string name;
protected:
    std::string YELLOW_SQUARE_IMAGE = "images/ui/yellow-square-big-hd.png";
    std::string IMAGE_SUFFIX = ".png";
};

#endif	/* ITEM_H */

