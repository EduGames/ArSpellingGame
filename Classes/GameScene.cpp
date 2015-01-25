/* 
 * File:   GameScene.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 7:20 PM
 */

#include "GameScene.h"
#include "Item.h"
#include "MainMenuScene.h"
#include "helpers/wordsXMLHelper.h"

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
    _item_name = item_name;
    moving_board = nullptr;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    initMenu();
    initHint();

    auto bg = Sprite::create("images/ui/background.jpg");
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(bg,-1);
    
    auto item = Item::create();
    item->setImage(item_name);
    item->setPosition(Vec2(visibleSize.width /2  + origin.x - item->getContentSize().width / 2, visibleSize.height /2 + origin.y - item->getContentSize().height / 2));
    addChild(item);
    
    initTargets();
    initBoards();
    initTouchEvents();

    return true;
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event) {
    if(hintBtn->getBoundingBox().containsPoint(touch->getLocation())){
        showHint();
        return true;
    }
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
    if(hintShowCompleted) hideHint();
    if(moving_board == nullptr) return;
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
            checkForGameSolved();
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

void GameScene::menuCloseCallback()
{
    auto myScene = MainMenu::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0,255,255)));
}

void GameScene::checkForGameSolved() {
    for( auto board : boards){
        if(!board->IsSolved()) return;
    }
    setGameSolved();
}

void GameScene::setGameSolved() {
    CCLOG("Game Ended !!");
    showNextLevelBtn();
}

void GameScene::showNextLevelBtn() {
    nxtLevelBtn->runAction(FadeIn::create(0.2));
}

void GameScene::showHint() {
    auto scale = ScaleTo::create(0.3, .65);
    hintBtn->runAction(scale);
    hint_container->setVisible(true);
}

void GameScene::hideHint() {
    auto scale = ScaleTo::create(0.3, 0.5);
    hintBtn->runAction(scale);
    hint_container->setVisible(false);
}

void GameScene::initMenu() {
    nxtLevelBtn = MenuItemImage::create(
                                           "images/ui/next_btn-hd.png",
                                           "images/ui/next_btn-hd.png",
                                           CC_CALLBACK_0(GameScene::goToNextLvl, this));
    
    nxtLevelBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    nxtLevelBtn->setScale(0.5);
    nxtLevelBtn->setPosition(Vec2(origin.x + visibleSize.width -  nxtLevelBtn->getContentSize().width/2 ,
                                 origin.y + visibleSize.height /2));
    nxtLevelBtn->setOpacity(0);
    
    auto closeItem = MenuItemImage::create(
                                           "images/ui/back_btn-hd.png",
                                           "images/ui/back_btn-hd.png",
                                           CC_CALLBACK_0(GameScene::menuCloseCallback, this));
    closeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    closeItem->setScale(0.5);
    closeItem->setPosition(Vec2(origin.x +  closeItem->getContentSize().width/2 ,
                                 origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nxtLevelBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void GameScene::initHint(){
    hintShowCompleted = false;
    hintBtn = Sprite::create("images/ui/help_btn-hd.png");
    hintBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    hintBtn->setScale(0.5);
    hintBtn->setPosition(Vec2(origin.x +  hintBtn->getContentSize().width + 7,
                                 origin.y + visibleSize.height - hintBtn->getContentSize().height/2));
    addChild(hintBtn,1);
    
    
    hint_container = ui::Layout::create();
    hint_container->setLayoutType(ui::LayoutType::RELATIVE);
    hint_container->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    hint_container->setPosition(Vec2(visibleSize.width /2, visibleSize.height /2));
    hint_container->setContentSize(Size(_item_name.length() * (35) , 63 ));
    hint_container->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    hint_container->setBackGroundColor(Color3B::ORANGE);
    auto text = ui::Text::create();
    text->setString(_item_name);
    text->setFontSize(60);
    auto rlp = ui::RelativeLayoutParameter::create();
    rlp->setAlign(ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
    text->setLayoutParameter(rlp);
    hint_container->addChild(text);
    addChild(hint_container, 9);
    
    auto delay = DelayTime::create(2);
    auto move = MoveTo::create(0.7 , hintBtn->getPosition());
    auto scale = ScaleTo::create(0.7, 0.2);
    auto actionS = Spawn::create(move, scale, NULL);
    auto actionSR = Spawn::create(MoveTo::create(0.0001 , Vec2(visibleSize.width /2, visibleSize.height /2)), ScaleTo::create(0.0001, 1), NULL);
    auto action = Sequence::create(delay, actionS, Hide::create(),actionSR,
            CallFunc::create( CC_CALLBACK_0(GameScene::onHintShowCompleted,this)),
            NULL);
    hint_container->runAction(action);

}

void GameScene::initTargets() {
    targets_container = ui::Layout::create();
    targets_container->setLayoutType(ui::Layout::Type::HORIZONTAL);
    targets_container->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    targets_container->setPosition(Vec2(visibleSize.width /2  + origin.x, 75));
    targets_container->setContentSize(Size(_item_name.length() * (52 + 10) , 63 ));

    auto lp = ui::LinearLayoutParameter::create();
    lp->setMargin(ui::Margin(5,0,5,0));
    for(char& c : _item_name) {
        std::string cd = &c;
        auto targetImage = ui::ImageView::create("images/ui/board-target.png");
        targetImage->setLayoutParameter(lp);
        targetImage->setName(cd);
        targets_container->addChild(targetImage);
    }
    targets_container->setScale(0.5);
    addChild(targets_container);
}

void GameScene::initBoards() {
    std::vector<char> shuffled(_item_name.begin(), _item_name.end());
    std::random_shuffle(shuffled.begin(),shuffled.end());
    int i = 0;
    for(char& c : shuffled){
        auto boardImage = Board::createWithLetter(c);
        boardImage->setOriginalPosition(Vec2( 70, 50 + i * 50));
        addChild(boardImage);
        boards.pushBack(boardImage);
        i++;
    }
}

void GameScene::initTouchEvents() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onHintShowCompleted() {
    auto scaleB = ScaleTo::create(0.3, .65);
    auto scale = ScaleTo::create(0.2, .5);
    hintBtn->runAction(Sequence::create(scaleB,scale, NULL));
    hintShowCompleted = true;
}

void GameScene::goToNextLvl() {
    auto myScene = GameScene::createScene(wordsXMLHelper::getNextWord(_item_name));
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0,255,255)));
}
