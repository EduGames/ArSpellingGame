/* 
 * File:   MenuView.cpp
 * Author: mohammed
 * 
 * Created on August 6, 2015, 11:08 PM
 */

#include "MenuView.h"
USING_NS_CC;

MenuView* MenuView::createWithWord(const Word word) {
    MenuView *widget = new (std::nothrow) MenuView;
    if (widget && widget->initWithWord(word)) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool MenuView::initWithWord(Word word) {
    if(Node::init()){
        this->word = word;
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
        
        nxtLevelBtn = MenuItemImage::create(
                                           "images/ui/next_btn-hd.png",
                                           "images/ui/next_btn-hd.png",
                                           CC_CALLBACK_0(MenuView::goToNextLvl, this));
    
        nxtLevelBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        nxtLevelBtn->setScale(0.5);
        nxtLevelBtn->setPosition(Vec2(origin.x + nxtLevelBtn->getContentSize().width/2 ,
                                     origin.y + visibleSize.height /2 - nxtLevelBtn->getContentSize().height / 2));
        nxtLevelBtn->setScaleX(-0.5);
        nxtLevelBtn->setOpacity(0);
        nxtLevelBtn->setEnabled(false);


        wordSoundBtn = MenuItemImage::create(
                                               "images/ui/sound_btn-hd.png",
                                               "images/ui/sound_btn-hd.png",
                                               CC_CALLBACK_0(MenuView::playWordsound, this));

        wordSoundBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        wordSoundBtn->setScale(0.5);
        wordSoundBtn->setPosition(Vec2(origin.x + wordSoundBtn->getContentSize().width/2 ,
                                     origin.y + visibleSize.height /2 + wordSoundBtn->getContentSize().height / 4));
        wordSoundBtn->setScaleX(-0.5);
        wordSoundBtn->setOpacity(0);
        wordSoundBtn->setEnabled(false);


        auto closeItem = MenuItemImage::create(
                                               "images/ui/back_btn-hd.png",
                                               "images/ui/back_btn-hd.png",
                                               CC_CALLBACK_0(MenuView::menuCloseCallback, this));
        closeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        closeItem->setScale(0.5);
        closeItem->setScaleX(-0.5);
        closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                     origin.y + visibleSize.height - closeItem->getContentSize().height/2));

        // create menu, it's an autorelease object
        auto menu = Menu::create(closeItem, nxtLevelBtn, wordSoundBtn, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
        
        return true;
    }
    return false;
}

void MenuView::goToNextLvl() {
    auto myScene = GameScene::createScene(wordsXMLHelper::getNextWord(word.english));
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0,255,255)));
}

void MenuView::playWordsound(){
    soundUtils::playword(word.english);
}

void MenuView::menuCloseCallback()
{
    auto myScene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0,255,255)));
}

void MenuView::showNextLevelBtn() {
    nxtLevelBtn->runAction(FadeIn::create(0.2));
    nxtLevelBtn->setEnabled(true);
    
    wordSoundBtn->runAction(FadeIn::create(0.2));
    wordSoundBtn->setEnabled(true);
}