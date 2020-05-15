/*
 * ContainerId.h
 *
 *  Created on: 6 באפר׳ 2020
 *      Author: Dell
 */

 /*
 * This class is about Container Id, in this class you can use
 * the constructor to change string to Container Id if the string
 * Appropriate to id format ,in other word: the first 4 chars in the
 * string are numbers and the next 7 chars are big or small English letters
 * if the string is valid then error data member will contain valid
 * else error will contain the unvalid string with Appropriate  error type
 *
 */
#ifndef CONTAINERID_H_
#define CONTAINERID_H_

#define EV Error::valid

#include "Error.h"
#include <iostream>


class ContainerId{
	std::string id;
	Error error;
	Error::errorType checkValid(std::string id);
public:
	ContainerId():id(""),error(Error::unvalidId){}
	ContainerId(std::string id);
	friend std::ostream& operator<<(std::ostream& out,const ContainerId &id)
	{
		if(id.error.getType()==Error::valid)
		{
			return out<<id.id;
		}
		return out<<"unvalid Container ID";
	}
	ContainerId& operator=(const ContainerId& s){
		if(&s!=this){
			id=s.id;
			error=s.error;
		}
		return *this;
	}
	const std::string& getId() const {
		return id;
	}
	friend bool operator==(const ContainerId &id1,const ContainerId &id2){
	{
		return id1.id==id2.id && id1.error==id2.error;
	}
	}
	Error getError() const {
		return error;
	}
};

#endif /* CONTAINERID_H_ */
