/* 
 * File:   FruitsPage.cpp
 * Author: mohheader
 * 
 * Created on January 15, 2015, 6:24 PM
 */

#include "FruitsPage.h"
#include "objects/SmallItem.h"
#include "scenes/GameScene.h"
USING_NS_CC;

FruitsPage* FruitsPage::createWithList(Size size, std::vector<std ::string> images) {
    FruitsPage* fp = FruitsPage::create();
    fp->setLayoutType(ui::Layout::Type::VERTICAL);
    fp->setContentSize(size);
    fp->addItems(images);
    
    return fp;
}


void FruitsPage::addItems(std::vector<std ::string> images) {
    auto lp = ui::LinearLayoutParameter::create();
    lp->setGravity(ui::LinearGravity::CENTER_HORIZONTAL);
    
    auto layout = ui::Layout::create();
    layout->setLayoutType(ui::Layout::Type::HORIZONTAL);
    layout->setContentSize(Size(360, getContentSize().height / 2.5));
    layout->setLayoutParameter(lp);
    layout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    layout->setScaleX(-1);
    
    auto layout2 = ui::Layout::create();
    layout2->setLayoutType(ui::Layout::Type::HORIZONTAL);
    layout2->setContentSize(Size(360, getContentSize().height / 2.5));
    layout2->setLayoutParameter(lp);
    layout2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    layout2->setScaleX(-1);
    unsigned int halfSize = 3;//images.size() / 2;
    
    for (unsigned int i = 0; i < images.size(); i++) {
        auto imageContainer = SmallItem::create();
        imageContainer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        imageContainer->setScaleX(-1);
        imageContainer->setImage(images.at(i));
        imageContainer->setEnabled(true);
        imageContainer->setTouchEnabled(true);
        imageContainer->addClickEventListener(CC_CALLBACK_1(FruitsPage::onClick, this));
        
        if(i < halfSize){
            layout->addChild(imageContainer);
        }else{
            layout2->addChild(imageContainer);
        }
    }
    addChild(layout);
    addChild(layout2);
}

void FruitsPage::onClick(Ref* pSender){
    SmallItem* slider = dynamic_cast<SmallItem*>(pSender);
    auto myScene = GameScene::createScene(slider->name);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0,255,255)));
}