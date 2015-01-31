/* 
 * File:   lettersSoundUtils.h
 * Author: mohheader
 *
 * Created on January 27, 2015, 10:31 PM
 */

#ifndef LETTERSSOUNDUTILS_H
#define	LETTERSSOUNDUTILS_H
#include "cocos2d.h"

class soundUtils : public cocos2d::Node {
public:
    CREATE_FUNC(soundUtils);
    static void playSound(std::string letter);
    static void playword(std::string word);
private:

};

#endif	/* LETTERSSOUNDUTILS_H */

