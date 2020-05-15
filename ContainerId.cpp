/*
 * ContainerId.cpp
 *
 *  Created on: 3 באפר׳ 2020
 *      Author: Dell
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;


#include "ContainerId.h"

Error::errorType ContainerId::checkValid(std::string id)
	{
	if(id.size()!=11) return Error::idSizeError;
	for(int i=0;i<4;i++)
	{
	char letter=id[i];
	if(!((int(letter)>=65 && int(letter)<=90)||(int(letter)>=97&&int(letter)<=122)))
		{
			return Error::errorType::unvalidIdFormat;
		}
	}
	for(int i=4;i<11;i++)
	{
		char letter=id[i];
		if(!(int(letter)>=48 &&int(letter)<=57))
		{
			return Error::errorType::unvalidIdFormat;
		}
	}
	return Error::errorType::valid;
	}
ContainerId::ContainerId(std::string id):id(id),error(checkValid(id),id)
	{



	}


















