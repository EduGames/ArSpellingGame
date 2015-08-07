/* 
 * File:   GameView.cpp
 * Author: mohammed
 * 
 * Created on August 7, 2015, 11:06 AM
 */

#include "GameView.h"
#include "scenes/GameScene.h"
USING_NS_CC;
GameView* GameView::createWithWord(const Word word, GameScene* scene) {
    GameView *widget = new (std::nothrow) GameView;
    if (widget && widget->initWithWord(word, scene)) {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

bool GameView::initWithWord(const Word word, GameScene* scene) {
    if(Node::init()){
        this->word = word;
        this->scene = scene;
        
        visibleSize = Director::getInstance()->getVisibleSize();
        origin = Director::getInstance()->getVisibleOrigin();
        
        initTargets();
        initBoards();
        return true;
    }
    return false;
}

void GameView::initBoards() {
    moving_board = nullptr;
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

void GameView::initTargets() {
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

bool GameView::handleOnTouchBegan(cocos2d::Touch* touch) {
    for (auto board: this->boards){
        if(board->getBoundingBox().containsPoint(touch->getLocation())){
            soundUtils::playSound(board->getName());
            if(!board->IsSolved()) moving_board = board;
            return true;
        }
    }
    return false;
}

void GameView::handleOnTouchMoved(cocos2d::Touch* touch) {
    if(moving_board == nullptr) return;
    moving_board->setPosition(touch->getLocation());
}

void GameView::handleOnTouchEnded(cocos2d::Touch* touch) {
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

bool GameView::boardInsideScreen(Board* moving_board, cocos2d::Vec2 targetPosition) {
    Size rect = moving_board->getBoundingBox().size;
    if ( targetPosition.x + rect.width > visibleSize.width || targetPosition.x - rect.width < 0 ||
            targetPosition.y + rect.height > visibleSize.height || targetPosition.y - rect.height < 0){
        return false;
    }
    return true;
}

void GameView::checkForGameSolved() {
    for( auto board : boards){
        if(!board->IsSolved()) return;
    }
    setGameSolved();
}

void GameView::setGameSolved() {
    scene->setGameSolved();
}
