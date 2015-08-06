/* 
 * File:   GameScene.cpp
 * Author: mohheader
 * 
 * Created on January 17, 2015, 7:20 PM
 */

#include "GameScene.h"
#include "MainMenuScene.h"
#include "helpers/wordsXMLHelper.h"
#include "libs/pugixml/pugixml.hpp"
#include "helpers/soundUtils.h"
#include "objects/HintView.h"

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
    word = Word(wordsXMLHelper::getArabicWord(item_name), item_name);
    moving_board = nullptr;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    //TODO: Move Menu from Here
    initMenu();
    hint = HintView::createWithWord(word);
    addChild(hint, 999);

    auto bg = Sprite::create("images/ui/background-hd.jpg");
    bg->setScale(0.5);
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(bg,-1);
    
    item = Item::create();
    item->setImage(item_name);
    item->setPosition(Vec2(visibleSize.width /2  + origin.x - item->getContentSize().width / 2, visibleSize.height /2 + origin.y - item->getContentSize().height / 4));
    addChild(item);
    
    initTargets();
    initBoards();
    initTouchEvents();

    return true;
}
void GameScene::playWordsound(){
    soundUtils::playword(word.english);
}

bool GameScene::onTouchBegan(Touch* touch, Event* unused_event) {
    if(hint->handleOnTouchBegan(touch)) return true;
    for (auto board: this->boards){
        if(board->getBoundingBox().containsPoint(touch->getLocation())){
            soundUtils::playSound(board->getName());
            if(!board->IsSolved()) moving_board = board;
            return true;
        }
    }
    if(item->getBoundingBox().containsPoint(touch->getLocation())){
        playWordsound();
        return true;
    }
    return false;
}

void GameScene::onTouchMoved(Touch* touch, Event* unused_event) {
    if(moving_board == nullptr) return;
    moving_board->setPosition(touch->getLocation());
}

void GameScene::onTouchEnded(Touch* touch, Event* unused_event) {
    hint->handleOnTouchEnd(touch);
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
        Vec2 targetPosition = moving_board->getPosition() + 
            ((moving_board->getOriginalPosition() - moving_board->getPosition()).getNormalized() * 10);
       
        for(auto board : boards){
            if (board->getBoundingBox().intersectsRect(moving_board->getBoundingBox())){
                Vec2 offset = (moving_board->getPosition() - board->getPosition()).getNormalized() * board->getBoundingBox().size.width;
                targetPosition += offset;
                if (!boardInsideScreen(moving_board, targetPosition)){
                    targetPosition -= 3 * offset;
                }
            }
        }
        if (!boardInsideScreen(moving_board, targetPosition)){
                targetPosition = moving_board->getPosition() + 
            ((moving_board->getOriginalPosition() - moving_board->getPosition()).getNormalized() * moving_board->getBoundingBox().size.width);
        }
        auto moveTo = MoveTo::create(0.5, targetPosition);
        auto action = EaseElasticOut::create(moveTo, 0.5);
        moving_board->runAction(action);
    }
    moving_board = nullptr;
}

bool GameScene::boardInsideScreen(Board* moving_board, cocos2d::Vec2 targetPosition) {
    Size rect = moving_board->getBoundingBox().size;
    if ( targetPosition.x + rect.width > visibleSize.width || targetPosition.x - rect.width < 0 ||
            targetPosition.y + rect.height > visibleSize.height || targetPosition.y - rect.height < 0){
        CCLOG("OUTSIDE SCREEN");
        return false;
    }
    CCLOG("INSIDE SCREEN");
    return true;
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
    
    wordSoundBtn->runAction(FadeIn::create(0.2));
    wordSoundBtn->setEnabled(true);
}

void GameScene::initMenu() {
    nxtLevelBtn = MenuItemImage::create(
                                           "images/ui/next_btn-hd.png",
                                           "images/ui/next_btn-hd.png",
                                           CC_CALLBACK_0(GameScene::goToNextLvl, this));
    
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
                                           CC_CALLBACK_0(GameScene::playWordsound, this));
    
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
                                           CC_CALLBACK_0(GameScene::menuCloseCallback, this));
    closeItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    closeItem->setScale(0.5);
    closeItem->setScaleX(-0.5);
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nxtLevelBtn, wordSoundBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
}

void GameScene::initTargets() {
    targets_container = ui::Layout::create();
    targets_container->setLayoutType(ui::Layout::Type::HORIZONTAL);
    targets_container->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    targets_container->setPosition(Vec2(visibleSize.width /2  + origin.x, 60));
    targets_container->setContentSize(Size((word.arabic.length() /2) * (109 + 4) , 126 ));

    auto lp = ui::LinearLayoutParameter::create();
    lp->setMargin(ui::Margin(5,0,5,0));
    
    std::vector<std::string> ar;
    for (unsigned int i = 0; i < word.arabic.size(); i= i + 2) {
        std::ostringstream doss;
        doss <<  word.arabic.at(i) <<  word.arabic.at(i + 1);
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
    ossL << "layouts/layout_" << (word.arabic.size() / 2) << ".xml";
    std::string file_path = FileUtils::getInstance()->fullPathForFilename(ossL.str());
    pugi::xml_document _levelData;
    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    pBuffer = FileUtils::getInstance()->getFileData(file_path.c_str(), "r", &bufferSize);
    _levelData.load_buffer(pBuffer,bufferSize);
    auto layoutsParent = _levelData.child("psd");
    std::vector<std::string> ar;
    for (unsigned int i = 0; i < word.arabic.size(); i= i + 2) {
        std::ostringstream doss;
        doss <<  word.arabic.at(i) <<  word.arabic.at(i + 1);
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

void GameScene::goToNextLvl() {
    auto myScene = GameScene::createScene(wordsXMLHelper::getNextWord(word.english));
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(0,255,255)));
}