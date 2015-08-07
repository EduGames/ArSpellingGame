/* 
 * File:   wordsXMLHelper.cpp
 * Author: mohheader
 * 
 * Created on January 24, 2015, 4:04 PM
 */

#include "wordsXMLHelper.h"
#include "libs/pugixml/pugixml.hpp"
USING_NS_CC;

std::string wordsXMLHelper::getNextWord(std::string currentWord) {
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
        if ( wordString == currentWord ) {
            if(wordString != _levelData.child("words").last_child().attribute("name").as_string())
                return word.next_sibling().attribute("name").as_string();
        };
    }
    return _levelData.child("words").first_child().attribute("name").as_string();
}

std::string wordsXMLHelper::getArabicWord(std::string currentWord) {
    std::vector<std::string> list;
    std::string file_path = FileUtils::getInstance()->fullPathForFilename("words.xml");
    pugi::xml_document _levelData;
    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    pBuffer = FileUtils::getInstance()->getFileData(file_path.c_str(), "r", &bufferSize);
    _levelData.load_buffer(pBuffer,bufferSize);
    return _levelData.child("words").find_child_by_attribute("name",currentWord.c_str()).text().as_string();
}
