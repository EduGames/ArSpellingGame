/* 
 * File:   FruitsPage.cpp
 * Author: mohheader
 * 
 * Created on January 15, 2015, 6:24 PM
 */

#include "FruitsPage.h"
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
//    layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
//    layout->setBackGroundColor(Color3B::BLUE);
    
    auto layout2 = ui::Layout::create();
    layout2->setLayoutType(ui::Layout::Type::HORIZONTAL);
    layout2->setContentSize(Size(360, getContentSize().height / 2.5));
    layout2->setLayoutParameter(lp);
    
    int halfSize = images.size() / 2;
    
    for (int i = 0; i < images.size(); i++) {
        std::string image = images.at(i);
        
        auto imageContainer = ui::Layout::create();
        imageContainer->setContentSize(Size(120,120));
        imageContainer->setLayoutType(ui::Layout::Type::RELATIVE);
        
        
        auto imageViewBG = ui::ImageView::create("images/ui/yellow-square-big.png");
        auto imageView = ui::ImageView::create("images/fruits/"+image+".png");
        
        imageContainer->addChild(imageViewBG);
        imageContainer->addChild(imageView);
        imageContainer->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        imageContainer->setScale(0.55);
        
        if(i < halfSize){
            layout->addChild(imageContainer);
        }else{
            layout2->addChild(imageContainer);
        }
    }
    addChild(layout);
    addChild(layout2);
}