/* 
 * File:   Word.h
 * Author: mohammed
 *
 * Created on August 6, 2015, 10:44 PM
 */

#ifndef WORD_H
#define	WORD_H
#include <string>
class Word {
public:
    Word(std::string arabic_word, std::string english_word) : 
        arabic(arabic_word), english(english_word){};
    std::string arabic;
    std::string english;
    Word(){};
private:
    
};

#endif	/* WORD_H */

