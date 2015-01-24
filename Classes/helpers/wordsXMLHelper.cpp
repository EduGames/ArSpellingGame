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
    _levelData.load_file(file_path.c_str());
    auto words = _levelData.child("words").children();
    for (pugi::xml_node word: words){
        auto wordString = word.text().as_string();
        if ( wordString == currentWord ) {
            if(wordString != _levelData.child("words").last_child().text().as_string())
                return word.next_sibling().text().as_string();
        };
    }
    return _levelData.child("words").first_child().text().as_string();
}
