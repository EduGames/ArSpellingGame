/* 
 * File:   arLettersUtils.cpp
 * Author: mohheader
 * 
 * Created on January 27, 2015, 10:34 PM
 */

#include "arLettersUtils.h"
#include "platform/CCPlatformMacros.h"
#include "libs/pugixml/pugixml.hpp"
USING_NS_CC;
arLettersUtils::arLettersUtils() {
}

arLettersUtils::arLettersUtils(const arLettersUtils& orig) {
}

arLettersUtils::~arLettersUtils() {
}

int arLettersUtils::getLetterNumber(std::string letter) {
    std::vector<std::string> list;
    std::string file_path = FileUtils::getInstance()->fullPathForFilename("letters.xml");
    pugi::xml_document _levelData;
    unsigned char* pBuffer = NULL;
    ssize_t bufferSize = 0;
    pBuffer = FileUtils::getInstance()->getFileData(file_path.c_str(), "r", &bufferSize);
    _levelData.load_buffer(pBuffer,bufferSize);
    return _levelData.child("letters").find_child_by_attribute("letter",letter.c_str()).text().as_int();
}
