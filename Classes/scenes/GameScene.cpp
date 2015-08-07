/* 
 * File:   GameScene.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 7:20 PM
 */

#include "GameScene.h"
#include "MainMenuScene.h"
#include "helpers/wordsXMLHelper.h"
#include "helpers/soundUtils.h"

USING_NS_CC;
Scene* GameScene::createScene(std::string item_name)
{
    auto scene = Scene::create();
    auto layer = GameScene::createWithItem(item_name);
    scene->addChild(layer);
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
    word = Word(wordsXMLHelper::getArabicWord(item_name), item_name);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto bg = Sprite::create("images/ui/background-hd.jpg");
    bg->setScale(0.5);
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(bg,-1);
    
    menu = MenuView::createWithWord(word);
    addChild(menu, 9999);
    
    hint = HintView::createWithWord(word);
    addChild(hint, 999);

    item = Item::create();
    item->setImage(item_name);
    item->setPosition(Vec2(visibleSize.width /2  + origin.x - item->getContentSize().width / 2, visibleSize.height /2 + origin.y - item->getContentSize().height / 4));
    addChild(item);
    
    game = GameView::createWithWord(word, this);
    addChild(game, 99);
    
    initTouchEvents();

    return true;
}

void GameScene::playWordsound(){
    soundUtils::playword(word.english);
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event) {
    if(hint->handleOnTouchBegan(touch)) return true;
    if(game->handleOnTouchBegan(touch)) return true;
    
    if(item->getBoundingBox().containsPoint(touch->getLocation())){
        playWordsound();
        return true;
    }
    return false;
}

void GameScene::onTouchMoved(Touch* touch, Event* unused_event) {
    game->handleOnTouchMoved(touch);
}

void GameScene::onTouchEnded(Touch* touch, Event* unused_event) {
    hint->handleOnTouchEnd(touch);
    game->handleOnTouchEnded(touch);
}

void GameScene::setGameSolved() {
    auto action = Sequence::create(DelayTime::create(1), 
            CallFunc::create( CC_CALLBACK_0(GameScene::playWordsound, this)),
            CallFunc::create( CC_CALLBACK_0(GameScene::showNextLevelBtn, this)),
            NULL);
    runAction(action);
}

void GameScene::showNextLevelBtn() {
    menu->showNextLevelBtn();
}

void GameScene::initTouchEvents() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
