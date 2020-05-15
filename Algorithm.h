/*
 * Algorithm.h
 *
 *  Created on: 7 ����� 2020
 *      Author: Dell
 */
 
#ifndef ALGORITHM_H_
#define ALGORITHM_H_


/*
 * Algorithm.cpp
 *
 *  Created on: 6 ����� 2020
 *      Author: Dell
 */


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include "ShipFloor.h"
#include "ShipRoute.h"
#include "FileManager2.h"
#include<algorithm>
#include <tuple>
#include "Error.h"
#include "WeightBalanceCalculator.cpp"
#include "AbstractAlgorithm.h"



using namespace std;
class Algorithm:public AbstractAlgorithm{
public:

	ShipRoute route;
	ShipFloor plan;
	ShipRoute::RouteIterator route_itr;
	vector<Error> errors;
	int steps=0;
	bool fatalError;
		/*
	 * this is inner helper class, it is 2d counter and
	 * it is used to distribute the containers
	 * as many as we can to the ship
	 */
class xy{
	public:
		int size_x;
		int size_y;
		int x=0;
		int y=0;
		xy(int x,int y):size_x(x-1),size_y(y-1){}
		void operator++()
		{

			if(x<size_x){x++;return;}
			if(x==size_x)
			{
				x=0;
				y=y==size_y?0:y+1;
			}
		}

		};
/*
 * is functions described in homework file
 */
	int getInstructionsForCargo(const std::string &pathIn,const std::string &pathOut)override;
	Algorithm():route(),plan(),route_itr(),fatalError(true){}
	int readShipPlan(const std::string& full_path_and_file_name) override{
		ShipFloor tmp(full_path_and_file_name);
		plan=tmp;
		this->fatalError=plan.isFatalError();
		return ErrorsToNumber(tmp.getErrors());

	}
	int readShipRoute(const std::string& full_path_and_file_name) override{
		ShipRoute tmp(full_path_and_file_name);
		route=tmp;
		route_itr=route.begin();
		return ErrorsToNumber(tmp.getErrors());

	}
	int setWeightBalanceCalculator(WeightBalanceCalculator& calculator) override
	{
		calculator.a++;
		return 1;
	}



	const vector<Error>& getErrors() const {
		return errors;
	}

	bool isFatalError() const {
		return fatalError;
	}

	const ShipFloor& getPlan() const {
		return plan;
	}

	 ShipRoute& getRoute()  {
		return route;
	}

	ShipRoute::RouteIterator getRouteItr() const {
		return route_itr;
	}

	int getSteps() const {
		return steps;
	}
};










#endif /* ALGORITHM_H_ */
