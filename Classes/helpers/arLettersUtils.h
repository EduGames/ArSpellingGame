/* 
 * File:   arLettersUtils.h
 * Author: mohheader
 *
 * Created on January 27, 2015, 10:34 PM
 */

#ifndef ARLETTERSUTILS_H
#define	ARLETTERSUTILS_H
#include "cocos2d.h"
class arLettersUtils {
public:
    arLettersUtils();
    arLettersUtils(const arLettersUtils& orig);
    virtual ~arLettersUtils();
    static int getLetterNumber(std::string letter);
private:

};

#endif	/* ARLETTERSUTILS_H */

