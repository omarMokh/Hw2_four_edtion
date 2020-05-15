
#ifndef ERROR_H_
#define ERROR_H_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Error{
public:
	enum errorType
	{
	valid=1
	,unvalidId
	,/*bnay*/idSizeError
	,/*bnay*/unvalidIdFormat=4,emptyPortCode=5
	,/*bnay*/portCodeSizeError=6
	,/*bnay*/unvalidPoerCodeFormat=7
	,emptyContainer=8
	,unvalidContainerFormat=9
	,intigerPlanDimitions
	,/*bnay*/lineIncludeNonNumber
	,/*bnay*/notInTheShipDim,
	/*bnay*/nonValidweight,
	missinghashtagInShipRote,
	badFirstLineInShipRoute
	,DoublexyApearWithDifferantData,
	DoblexyapearWithTheSameDAta
	,/*1*/equalormorenumbersofFloor
	,/*6*/badportsymbolformat
	,missinghashtagInShipPlan
	,ConsecutivePorts
	,OnlySingleValidPort
	,IdExist
	,missinghashtagInPortContainers
	,badPortFormatInportContainers
	,badIdFormatInportContainers
	,lastPortHasWaitingContainers
	,shipCapicityError
	};

	errorType type;

	string object="";
	/*
	 * c'tor that build error from number [1,18] as described in the homework
	 */
	Error(int a);
	/*
	 * given an Error convert this error to a number
	 */
	friend int toInt(const Error &in);


	/*
	 * given a vector of errors convert this error to number as described
	 * in the home work
	 */

	friend int ErrorsToNumber(vector<Error> in);

	/*
	 * given a number n convert this number to vector of errors
	 * this function the opposite of ErrorsToNumber described above
	 */

	friend void NumberToErrors(vector<Error> &result,int n);

	//C'tor
	Error(errorType type):type(type){}

	//Cto'r
	Error(errorType type,string object):type(type),object(object){}

	errorType getType() const
	{
		return type;
	}

	Error()
	{
		this->type=valid;
	}


	friend bool operator==(const Error &e1,const Error &e2)
		{
		return e1.type==e2.type;

		}


	friend std::ostream& operator<<(std::ostream& out,const Error &err);

	Error& operator=(const Error &e)
	{
		if(&e!=this)
		{
			type=e.type;
			object=e.object;
		}
		return *this;
	}





};




#endif /* ERROR_H_ */
