/*
 * Container.h
 *
 *  Created on: 6 באפר׳ 2020
 *      Author: Dell
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_



#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <vector>
#include "SeaportCode.h"
#include "ContainerId.h"
#include "Error.h"
/*
 * This class is about Container, the 3 data members contains
 * the weight,destination ,id as there name.
 * the error data member contains appropriate error
 * in case the container is not valid
 *
 */

using namespace std;

class Container{
    int weight;
    SeaportCode destination;
    ContainerId id;
    Error error;
public:
    Container():weight(0),destination(),id(),error(Error::emptyContainer){}

    //constructor
    Container(int weight1,const string destination1,const string id1) :
    	weight(weight1) ,destination(destination1),id(id1) {
    	if((id.getError().getType()==1) && (destination.getError().getType()==1))
    	{error=Error::valid;}
    	else {error=Error::unvalidContainerFormat;}

    }
    /* check if the weight of empty container */
    Container(int wieght,SeaportCode destination,ContainerId id):weight(wieght),destination(destination),id(id),error(Error::valid){}


    Container(const Container& c) {
    	weight=c.weight;
    	destination=c.destination;
    	id=c.id;
    	error=c.error;
    }
    Container& operator=(const Container& s) {
        if(&s != this) {
            weight = s.weight;
            destination = s.destination;
            id=s.id;
            error=s.error;
        }
        return *this;
    }
    friend bool operator==(const Container& c1, const Container& c2) {
        return c1.weight==c2.weight && c1.destination==c2.destination && c1.id==c2.id;
    }

    friend std::ostream& operator<<(std::ostream& out, const Container& c) {
    	if(!c.error.getType()){
    		return out<< "block"<<endl;
    	}
        return out << "Container id:"<<c.id<<endl<<"Container weight:"<<c.weight<<endl<<"Container destination:"<<c.destination<<endl;
    }

	 SeaportCode getDestination()  {
		return destination;
	}


	const ContainerId& getId() const {
		return id;
	}



	int getWeight() const {
		return weight;
	}
	Error getError()
	{
		return error;
	}
	/*
	 * if the destination or the port are erroneous then
	 * this function contains the errors
	 */
	bool getErrors(vector<Error> &result)
	{
		if(error.getType()==1) return false;
		if(!(destination.getError().getType()==1)) result.push_back(destination.getError());
		if(!(id.getError().getType()==1)) result.push_back(id.getError());

		return true;
	}


};













#endif /* CONTAINER_H_ */
