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
private:

};

#endif	/* ITEM_H */

