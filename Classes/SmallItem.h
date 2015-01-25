/* 
 * File:   smallItem.h
 * Author: mohheader
 *
 * Created on January 25, 2015, 10:58 AM
 */

#ifndef SMALLITEM_H
#define	SMALLITEM_H

#include "cocos2d.h"
#include <ui/CocosGUI.h>
class SmallItem : public cocos2d::ui::Layout{
public:
    CREATE_FUNC(SmallItem);
    bool init();
    void setImage(std::string image);
    std::string name;
protected:
    std::string YELLOW_SQUARE_IMAGE = "images/ui/yellow-square-small-hd.png";
    std::string IMAGE_SUFFIX = ".png";
};

#endif	/* SMALLITEM_H */

