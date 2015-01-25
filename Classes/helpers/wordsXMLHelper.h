/* 
 * File:   wordsXMLHelper.h
 * Author: mohheader
 *
 * Created on January 24, 2015, 4:04 PM
 */

#ifndef WORDSXMLHELPER_H
#define	WORDSXMLHELPER_H
#include "cocos2d.h"
class wordsXMLHelper {
public:
    static std::string getNextWord(std::string currentWord);
    static std::string getArabicWord(std::string currentWord);
private:

};

#endif	/* WORDSXMLHELPER_H */

