/* 
 * File:   GameScene.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 7:20 PM
 */

#include "GameScene.h"
#include "Item.h"
#include "MainMenuScene.h"

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
    
    moving_board = nullptr;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
     auto closeItem = MenuItemImage::create(
                                           "images/ui/back_btn-hd.png",
                                           "images/ui/back_btn-hd.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    closeItem->setScale(0.5);
    closeItem->setPosition(Vec2(origin.x +  closeItem->getContentSize().width/2 ,
                                 origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto bg = Sprite::create("images/ui/background.jpg");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(bg,-1);
    
    auto item = Item::create();
    item->setImage(item_name);
    item->setPosition(Vec2(visibleSize.width /2  + origin.x - item->getContentSize().width / 2, visibleSize.height /2 + origin.y - item->getContentSize().height / 2));
    addChild(item);
    
    
    targets_container = ui::Layout::create();
    targets_container->setLayoutType(ui::Layout::Type::HORIZONTAL);
    targets_container->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    targets_container->setPosition(Vec2(visibleSize.width /2  + origin.x, 75));
    targets_container->setContentSize(Size(item_name.length() * (52 + 10) , 63 ));
    
    auto lp = ui::LinearLayoutParameter::create();
    lp->setMargin(ui::Margin(5,0,5,0));
    for(char& c : item_name) {
        std::string cd = &c;
        auto targetImage = ui::ImageView::create("images/ui/board-target.png");
        targetImage->setLayoutParameter(lp);
        targetImage->setName(cd);
        targets_container->addChild(targetImage);
    }
    targets_container->setScale(0.5);
    addChild(targets_container);
    
    std::vector<char> shuffled(item_name.begin(), item_name.end());
    std::random_shuffle(shuffled.begin(),shuffled.end());
    int i = 0;
    for(char& c : shuffled){
        auto boardImage = Board::createWithLetter(c);
        boardImage->setPosition(Vec2( 70, 50 + i * 50));
        boardImage->setOriginalPosition(Vec2( 70, 50 + i * 50));
        addChild(boardImage);
        boards.pushBack(boardImage);
        i++;
    }
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event) {
    for (auto board: this->boards){
        if(board->getBoundingBox().containsPoint(touch->getLocation()) && !board->IsSolved()){
            moving_board = board;
            return true;
        }
    }
    return false;
}

void GameScene::onTouchMoved(Touch* touch, Event* unused_event) {
    if(moving_board == nullptr) return;
    moving_board->setPosition(touch->getLocation());
}

void GameScene::onTouchEnded(Touch* touch, Event* unused_event) {
    bool solved = false;
    for(auto target : targets_container->getChildren()){
        auto g = targets_container->convertToWorldSpace(target->getPosition());
        if(moving_board->getBoundingBox().containsPoint(g)
                && ( moving_board->getName().at(0) == target->getName().at(0))
        ){
            moving_board->setPosition(g);
            auto rL = RotateTo::create(0.1,30);
            auto rR = RotateTo::create(0.1,-30);
            auto rO = RotateTo::create(0.1,0);
            auto seq = Sequence::create(rL,rR,rL,rO,NULL);
            moving_board->runAction(seq);
            moving_board->setIsSolved(true);
            solved = true;
            break;
        }
    }
    if(!solved){
        auto moveTo = MoveTo::create(0.5,moving_board->getOriginalPosition());
        auto action = EaseElasticOut::create(moveTo, 0.5);
        moving_board->runAction(action);
    }
    moving_board = nullptr;
}

void GameScene::menuCloseCallback(Ref* pSender)
{   auto myScene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0,255,255)));
}