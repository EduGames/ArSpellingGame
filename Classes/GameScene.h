/* 
 * File:   GameScene.h
 * Author: mohheader
 *
 * Created on January 17, 2015, 7:20 PM
 */

#ifndef GAMESCENE_H
#define	GAMESCENE_H
#include "cocos2d.h"
#include <ui/CocosGUI.h>
class GameScene : public cocos2d::Layer {
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(std::string item_name);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool initWithItem(std::string item_name);
    static GameScene* createWithItem(std::string item_name);
private:
    std::string _item_name;
};

#endif	/* GAMESCENE_H */

