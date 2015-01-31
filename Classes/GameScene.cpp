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
#include "libs/pugixml/pugixml.hpp"
#include "helpers/soundUtils.h"

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
    _item_name_english = item_name;
    _item_name = wordsXMLHelper::getArabicWord(item_name);
    moving_board = nullptr;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    initMenu();
    initHint();

    auto bg = Sprite::create("images/ui/background-hd.jpg");
    bg->setScale(0.5);
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(bg,-1);
    
    auto item = Item::create();
    item->setImage(item_name);
    item->setPosition(Vec2(visibleSize.width /2  + origin.x - item->getContentSize().width / 2, visibleSize.height /2 + origin.y - item->getContentSize().height / 4));
    addChild(item);
    
    initTargets();
    initBoards();
    initTouchEvents();

    return true;
}
void GameScene::playWordsound(){
    soundUtils::playword(_item_name_english);
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
                && ( moving_board->getName() == target->getName())
        ){
            soundUtils::playSound(moving_board->getName());
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
    auto action = Sequence::create(DelayTime::create(1), 
            CallFunc::create( CC_CALLBACK_0(GameScene::playWordsound,this)),
            CallFunc::create( CC_CALLBACK_0(GameScene::showNextLevelBtn,this)),
            NULL);
    runAction(action);
}

void GameScene::showNextLevelBtn() {
    nxtLevelBtn->runAction(FadeIn::create(0.2));
    nxtLevelBtn->setEnabled(true);
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
    nxtLevelBtn->setPosition(Vec2(origin.x + nxtLevelBtn->getContentSize().width/2 ,
                                 origin.y + visibleSize.height /2));
    nxtLevelBtn->setScaleX(-0.5);
    nxtLevelBtn->setOpacity(0);
    nxtLevelBtn->setEnabled(false);
    
    auto closeItem = MenuItemImage::create(
                                           "images/ui/back_btn-hd.png",
                                           "images/ui/back_btn-hd.png",
                                           CC_CALLBACK_0(GameScene::menuCloseCallback, this));
    closeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    closeItem->setScale(0.5);
    closeItem->setScaleX(-0.5);
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
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
    hintBtn->setPosition(Vec2(origin.x +  hintBtn->getContentSize().width / 2,
                                 origin.y + visibleSize.height - hintBtn->getContentSize().height/2));
    addChild(hintBtn,1);
    
    
    hint_container = ui::Layout::create();
    hint_container->setLayoutType(ui::LayoutType::RELATIVE);
    hint_container->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    hint_container->setPosition(Vec2(visibleSize.width /2, visibleSize.height /2));
    hint_container->setContentSize(Size(_item_name.length() * (35) , 63 ));
    hint_container->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    hint_container->setBackGroundColor(Color3B::ORANGE);
    auto text = Label::createWithSystemFont(_item_name, "fonts/font.ttf", 60);
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
            CallFunc::create( CC_CALLBACK_0(GameScene::playWordsound,this)),
            delay->clone(),
            actionS, Hide::create(),actionSR,
            CallFunc::create( CC_CALLBACK_0(GameScene::onHintShowCompleted,this)),
            NULL);
    hint_container->runAction(action);
    
}

void GameScene::initTargets() {
    targets_container = ui::Layout::create();
    targets_container->setLayoutType(ui::Layout::Type::HORIZONTAL);
    targets_container->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    targets_container->setPosition(Vec2(visibleSize.width /2  + origin.x, 60));
    targets_container->setContentSize(Size((_item_name.length() /2) * (109 + 4) , 126 ));

    auto lp = ui::LinearLayoutParameter::create();
    lp->setMargin(ui::Margin(5,0,5,0));
    
    std::vector<std::string> ar;
    for (unsigned int i = 0; i < _item_name.size(); i= i + 2) {
        std::ostringstream doss;
        doss <<  _item_name.at(i) <<  _item_name.at(i + 1);
        ar.push_back(doss.str());
    }
    for (int i = ar.size(); i --> 0;) {
        auto targetImage = ui::ImageView::create("images/ui/board-target-hd.png");
        targetImage->setLayoutParameter(lp);
        targetImage->setName(ar.at(i));
        targets_container->addChild(targetImage);
    }
    targets_container->setScale(0.5);
    addChild(targets_container);
}

void GameScene::initBoards() {
    std::ostringstream ossL;
    ossL << "layouts/layout_" << (_item_name.size() / 2) << ".xml";
    std::string file_path = FileUtils::getInstance()->fullPathForFilename(ossL.str());
    pugi::xml_document _levelData;
    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    pBuffer = FileUtils::getInstance()->getFileData(file_path.c_str(), "r", &bufferSize);
    _levelData.load_buffer(pBuffer,bufferSize);
    auto layoutsParent = _levelData.child("psd");
    std::vector<std::string> ar;
    for (unsigned int i = 0; i < _item_name.size(); i= i + 2) {
        std::ostringstream doss;
        doss <<  _item_name.at(i) <<  _item_name.at(i + 1);
        ar.push_back(doss.str());
    }
    std::random_shuffle(ar.begin(),ar.end());
    for (unsigned int i = 0; i < ar.size(); i++) {
        auto boardImage = Board::createWithLetter(ar.at(i));
        std::ostringstream oss;
        oss << "board-" << (i) + 1;
        auto coord = layoutsParent.find_child_by_attribute("name",oss.str().c_str());
        int x = (int) ( coord.attribute("x").as_float() * visibleSize.width);
        int y = (int) ((1- coord.attribute("y").as_float() )* visibleSize.height);
        boardImage->setOriginalPosition(Vec2( x, y));
        addChild(boardImage, 8);
        boards.pushBack(boardImage);
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
    auto myScene = GameScene::createScene(wordsXMLHelper::getNextWord(_item_name_english));
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0,255,255)));
}
