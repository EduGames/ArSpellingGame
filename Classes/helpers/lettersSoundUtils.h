/* 
 * File:   lettersSoundUtils.h
 * Author: mohheader
 *
 * Created on January 27, 2015, 10:31 PM
 */

#ifndef LETTERSSOUNDUTILS_H
#define	LETTERSSOUNDUTILS_H
#include "cocos2d.h"

class lettersSoundUtils : public cocos2d::Node {
public:
    lettersSoundUtils();
    lettersSoundUtils(const lettersSoundUtils& orig);
    virtual ~lettersSoundUtils();
    
    static void playSound(std::string letter);
private:

};

#endif	/* LETTERSSOUNDUTILS_H */

