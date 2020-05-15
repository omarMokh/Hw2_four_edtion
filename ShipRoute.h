/*
 * ShipRoute.h
 *
 *  Created on: 6 באפר׳ 2020
 *      Author: Dell
 */

#ifndef SHIPROUTE_H_
#define SHIPROUTE_H_
     
  
/*
 * shipRoute.cpp
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
#include <stack>
#include<array>
#include"SeaportCode.h"
#include<fstream>
#include<iterator>
#include "Error.h"
#include "FileManager2.h"
/*
 * this class contains the ship route and its iterator
 *
 */
using namespace std;

class ShipRoute{
	std::vector<SeaportCode> route;
	std::vector<Error> errors;

public:

	std::vector<Error> &getErrors()
	{
		return this->errors;
	}
	const std::vector<SeaportCode>& getRoute() const {
		return route;
	}
	ShipRoute():route(){}
	/*
	 * init the route by given path
	 */
	ShipRoute(string path);
	/*iner class*/

	class RouteIterator{
		std::vector<SeaportCode>::iterator itr;

	public:
		RouteIterator():itr(NULL){}

		RouteIterator(std::vector<SeaportCode>::iterator itr):itr(itr){}
		RouteIterator operator++(){
			itr++;
			return RouteIterator(itr);
		}
		SeaportCode operator*()
		{
			return *itr;
		}
		bool operator!=( RouteIterator other)
		{
			return itr!=other.itr;
		}
		RouteIterator& operator=(const RouteIterator &other)
		{
			if(&other!=this){
				this->itr=other.itr;
			}
			return *this;
		}
		bool operator<(const RouteIterator &other)
		{
			return this->itr<other.itr;
		}



	};

	RouteIterator begin()
	{
		return RouteIterator(route.begin());
	}
	RouteIterator end()
	{
		return RouteIterator(route.end());
	}
	bool passInthePort(SeaportCode code,RouteIterator itr)
		{
		++itr;
			for(;itr<end();++itr)
			{
				if(*itr==code)
				{
					return true;
				}
			}
			return false;

		}
	/*
	 * this method gets iterator
	 */

	bool before(RouteIterator itr,SeaportCode a,SeaportCode b);
	ShipRoute& operator=(const ShipRoute &route)
	{
		if(&route !=this)
		{
			this->route=route.route;
			this->errors=route.errors;
		}
		return *this;
	}

	const std::vector<Error>& getErrors() const {
		return errors;
	}
};


#endif /* SHIPROUTE_H_ */

