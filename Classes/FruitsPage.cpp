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
    fp->createRow(images);
    return fp;
}


void FruitsPage::createRow(std::vector<std ::string> images) {
    auto layout = ui::Layout::create();
    layout->setLayoutType(ui::Layout::Type::HORIZONTAL);
    layout->setContentSize(Size(getContentSize().width - 150,getContentSize().height / 3));
    
    auto layout2 = ui::Layout::create();
    layout2->setLayoutType(ui::Layout::Type::HORIZONTAL);
    layout2->setContentSize(Size(getContentSize().width - 150,getContentSize().height / 3));
    
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