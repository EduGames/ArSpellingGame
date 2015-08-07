/* 
 * File:   HintView.cpp
 * Author: mohammed
 * 
 * Created on August 6, 2015, 9:30 PM
 */

#include "HintView.h"
USING_NS_CC;

HintView* HintView::createWithWord(const Word word) {
    HintView *widget = new (std::nothrow) HintView;
    if (widget && widget->initWithWord(word)) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool HintView::initWithWord(Word word) {
    if(Node::init()){
        this->word = word;
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
    
        bool hintShowCompleted = false;
        hintBtn = Sprite::create("images/ui/help_btn-hd.png");
        hintBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        hintBtn->setScale(0.5);
        hintBtn->setPosition(Vec2(origin.x +  hintBtn->getContentSize().width / 2,
                                     origin.y + visibleSize.height - hintBtn->getContentSize().height/2));
        addChild(hintBtn,1);


        hint_container = ui::Layout::create();
        hint_container->setLayoutType(ui::LayoutType::RELATIVE);
        hint_container->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        hint_container->setPosition(Vec2(visibleSize.width /2, visibleSize.height /2));
        hint_container->setContentSize(Size(word.arabic.length() * (35) , 63 ));
        hint_container->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
        hint_container->setBackGroundColor(Color3B::ORANGE);
        auto text = Label::createWithSystemFont(word.arabic, "fonts/font.ttf", 60);
        text->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        text->setPosition(hint_container->getBoundingBox().size.width / 2,hint_container->getBoundingBox().size.height / 2);
        hint_container->addChild(text);
        addChild(hint_container, 9);

        auto delay = DelayTime::create(1);
        auto move = MoveTo::create(0.7 , hintBtn->getPosition());
        auto scale = ScaleTo::create(0.7, 0.2);
        auto actionS = Spawn::create(move, scale, NULL);
        auto actionSR = Spawn::create(MoveTo::create(0.0001 , Vec2(visibleSize.width /2, visibleSize.height /2)), ScaleTo::create(0.0001, 1), NULL);
        auto action = Sequence::create(delay->clone(), 
                CallFunc::create( CC_CALLBACK_0(HintView::playWordsound, this)),
                delay->clone(),
                actionS, Hide::create(),actionSR,
                CallFunc::create( CC_CALLBACK_0(HintView::onHintShowCompleted, this)),
                NULL);
        hint_container->runAction(action);
        return true;
    }
    return false;
}

void HintView::showHint() {
    auto scale = ScaleTo::create(0.3, .65);
    hintBtn->runAction(scale);
    hint_container->setVisible(true);
}

void HintView::hideHint() {
    auto scale = ScaleTo::create(0.3, 0.5);
    hintBtn->runAction(scale);
    hint_container->setVisible(false);
}

void HintView::onHintShowCompleted() {
    auto scaleB = ScaleTo::create(0.3, .65);
    auto scale = ScaleTo::create(0.2, .5);
    hintBtn->runAction(Sequence::create(scaleB,scale, NULL));
    hintShowCompleted = true;
}

bool HintView::handleOnTouchBegan(cocos2d::Touch* touch) {
    if(hintBtn->getBoundingBox().containsPoint(touch->getLocation())){
        showHint();
        return true;
    }
    return false;
}

void HintView::handleOnTouchEnd(cocos2d::Touch* touch) {
    if(hintShowCompleted) hideHint();
}

void HintView::playWordsound(){
    soundUtils::playword(word.english);
}