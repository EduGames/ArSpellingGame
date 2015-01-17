/* 
 * File:   GameScene.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 7:20 PM
 */

#include "GameScene.h"
#include "Item.h"
USING_NS_CC;
Scene* GameScene::createScene(std::string item_name)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::createWithItem(item_name);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameScene* GameScene::createWithItem(std::string item_name) {
    GameScene *gameScene = new (std::nothrow) GameScene();
    if (gameScene && gameScene->initWithItem(item_name))
    {
        gameScene->autorelease();
        return gameScene;
    }
    CC_SAFE_DELETE(gameScene);
    return nullptr;
}

bool GameScene::initWithItem(std::string item_name) {
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto bg = Sprite::create("images/ui/background.jpg");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(bg,-1);
    
    auto item = Item::create();
    item->setImage(item_name);
    item->setPosition(Vec2(visibleSize.width /2  + origin.x - item->getContentSize().width / 2, visibleSize.height /2 + origin.y - item->getContentSize().height / 2));
    addChild(item);
    
    return true;
}
