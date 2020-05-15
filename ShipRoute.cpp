/*
 * ShipRoute.cpp
 *
 *  Created on: 6 ����� 2020
 *      Author: Dell
 */


#include "ShipRoute.h"
/*
 * remove the consecutively ports and return true iff there
 * are no consecutive ports
 */
bool consecutPort(vector<SeaportCode> &in)
{
	bool result=true;
	std::vector<SeaportCode>::iterator it1=in.begin();
	std::vector<SeaportCode>::iterator it2=in.begin();
	++it2;
	while(it2<in.end())
	{
		if(*it1==*it2)
		{
			result=false;
			in.erase(it2);
			continue;
		}
		it1++;it2++;
	}
	return result;
}
ShipRoute::ShipRoute(string path)
	{
		ifstream f;
		f.open(path);
		std::vector<SeaportCode> tmp;
		route=tmp;
		std::vector<Error> tmpE;
		errors=tmpE;
		routeTokens(f,route,errors);
		if(!consecutPort(route))
		{
			this->errors.push_back(Error(Error::errorType::ConsecutivePorts));
		}
		if(this->route.size()==1)
		{
			this->errors.push_back(Error(Error::errorType::OnlySingleValidPort));
		}



	}
bool ShipRoute::before(RouteIterator itr,SeaportCode a,SeaportCode b)
{
	RouteIterator end=this->end();
	for(;itr!=end;++itr)
	{
		if(*itr==a)
		{
			return true;
		}
		if(*itr==b)
		{
			return false;
		}
	}
	return true;
}



