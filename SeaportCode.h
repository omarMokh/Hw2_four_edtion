/*
 * SeaportCode.h
 *
 *  Created on: 6 באפר׳ 2020
 *      Author: Dell
 */

 /*
 * This class is about Port Id, in this class you can use
 * the constructor to change string to port Id if the string
 * Appropriate to id format ,in other word: the string is small or big English letters.
 * if the string is valid then error data member will contain valid
 * else error will contain the unvalid string with Appropriate  error type
 *
 */
#ifndef SEAPORTCODE_H_
#define SEAPORTCODE_H_

/*
 * SeaPortCode.h
 *
 *  Created on: 6 באפר׳ 2020
 *      Author: Dell
 */


#include <iostream>
#include <string>
#include "Error.h"

using namespace std;
class SeaportCode{
	std::string code;
	Error error;
	Error::errorType checkValid(std::string code1);

public:
	SeaportCode():code(""),error(Error::errorType::emptyPortCode){}
	SeaportCode(std::string code):code(code),error(checkValid(code),code)
	{


	}
	friend bool operator==(const SeaportCode &code1,const SeaportCode &code2){
		return code1.code==code2.code&&code1.error==code2.error ;
	}
	friend bool operator!=(const SeaportCode &code1,const SeaportCode &code2){
			return !(code1.code==code2.code&&code1.error==code2.error) ;
		}

	friend std::ostream& operator<<(std::ostream& out,const SeaportCode &code)
	{
		if(code.error.getType()){
			return out<<code.code;

		}
		return out<<"unvalid Code"<<endl;
	}

	const std::string& getCode() const {
		return code;
	}
    SeaportCode& operator=(const SeaportCode& s) {
        if(&s != this) {
        	code=s.code;
        	this->error=s.error;

        }
        return *this;
    }

	Error getError() const {
		return error;
	}
	string toString()
	{
		return this->code;
	}
};

#endif /* SEAPORTCODE_H_ */
