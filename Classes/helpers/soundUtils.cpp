/* 
 * File:   lettersSoundUtils.cpp
 * Author: mohheader
 * 
 * Created on January 27, 2015, 10:31 PM
 */

#include "lettersSoundUtils.h"
#include "arLettersUtils.h"

//TODO: FIX !!!
#include "../../cocos2d/cocos/audio/include/SimpleAudioEngine.h"

USING_NS_CC;

lettersSoundUtils::lettersSoundUtils() {
}

lettersSoundUtils::lettersSoundUtils(const lettersSoundUtils& orig) {
}

lettersSoundUtils::~lettersSoundUtils() {
}

void lettersSoundUtils::playSound(std::string letter) {
    int number = arLettersUtils::getLetterNumber(letter);
    char numstr[21]; // enough to hold all numbers up to 64-bits
    std::sprintf(numstr, "%i", number);
    std::string result__ = numstr + std::string(".mp3");
    if (number < 10) result__ = "0" + result__;
    result__ = std::string("sounds/letters/02/") + result__;
    const char * audio_file = result__.c_str();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(audio_file);
}
