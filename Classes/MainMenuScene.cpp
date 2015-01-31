#include "MainMenuScene.h"
#include "FruitsPage.h"
#include "PageViewWIndicator.h"
#include "libs/pugixml/pugixml.hpp"
#include "helpers/wordsXMLHelper.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // add "HelloWorld" splash screen"
    auto bg = Sprite::create("images/ui/background2-hd.jpg");
    bg->setScale(0.5);
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(bg,-1);
    
    PageViewWIndicator* pageView = PageViewWIndicator::create();
    pageView->setContentSize(visibleSize);
    pageView->setPositionY(-40);
    
    std::vector<std::string> list;
    std::string file_path = FileUtils::getInstance()->fullPathForFilename("words.xml");
    pugi::xml_document _levelData;

    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    pBuffer = FileUtils::getInstance()->getFileData(file_path.c_str(), "r", &bufferSize);
    _levelData.load_buffer(pBuffer,bufferSize);

    auto words = _levelData.child("words").children();
    for (pugi::xml_node word: words){
        auto wordString = word.attribute("name").as_string();
        list.push_back(wordString);
        if(list.size() >= 6){
            pageView->addPage(FruitsPage::createWithList(visibleSize, list));
            list.clear();
        }
    }
    if(list.size() >= 1){
        pageView->addPage(FruitsPage::createWithList(visibleSize, list));
        list.clear();
    }
    pageView->setCurrentPage(pageView->getPagesCount() - 1);
    this->addChild(pageView);
    return true;
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
