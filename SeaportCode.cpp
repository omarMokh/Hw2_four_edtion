/*
 * SeaportCode.cpp
 *
 *  Created on: 3 áàôø× 2020
 *      Author: Dell
 */

#include "SeaportCode.h"

	Error::errorType SeaportCode::  checkValid(std::string code1)
	{
		if(code1.size()!=5) return Error::errorType::portCodeSizeError;
		for(char &letter:code1)
		{	/*check whether every letter in the code is legal capital or small english letter*/
			if(!((int(letter)>=65 && int(letter)<=90)||(int(letter)>=97&&int(letter)<=122)))
			{
				return Error::errorType::unvalidPoerCodeFormat;
			}

		}
		return Error::errorType::valid;
	}



