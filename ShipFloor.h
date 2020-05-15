
#ifndef SHIPFLOOR_H_
#define SHIPFLOOR_H_



#include"Container.h"
#include<fstream>
#include<stack>
#include<cstring>
#include"FileManager2.h"
#include<vector>
#include<iostream>
#include<algorithm>
#include "Error.h"
using namespace std;

class ShipFloor
{
public:
	 friend std::ostream& operator<<(std::ostream& out, ShipFloor& ship)
	 {
		 string result="\n x is: " + std::to_string(ship.x_size) + " y is: " +std::to_string(ship.y_size)+" ";

		 for(int x=0;x<ship.x_size;x++)
		 {
			 for(int y=0;y<ship.y_size;y++)
			 {
				 for(std::size_t h=0;h<ship.structure[x][y].size();h++)
				 {
					 result=result+ship.structure[x][y][h].getDestination().getCode()+"\n";
				 }
			 }
		 }
		 return out<<result;
	 }


	int x_size;
	int y_size;
	int h_size;
	/* this is 2D matrix of stacks were every stack indexed by [x,y] its a containers heap*/
	vector<vector<vector<Container> > > structure;
	/* this 2D matrix include the weight of every heap in the matrix*/
	vector<vector<int>> weight;

	vector<vector<int>> realDim;
	vector<Error> errors;
	bool fatalError;
//last update
	int checkDim(int x,int y,int z);
	bool unload(std::vector<Container> &result,SeaportCode portId,std::vector<tuple<int,int,int>> &con_place);

	ShipFloor():x_size(0),y_size(0),h_size(0),structure(),weight(),realDim(),fatalError(true){}

	int emptyPlaces();
	
	/*
 * given a port code return the number of the containers
 * in the ship that her destination is port
 */
	int containersPortNumber(SeaportCode port);
	
	bool insert(Container &a,int x,int y);

	ShipFloor(string path);
	bool isHeapFull(int x,int y)
	{
		int siz= this->structure[x][y].size();
		return siz==this->realDim[x][y];
	}
	bool insert( Container &a,int x,int y,int z);
	ShipFloor& operator=(const ShipFloor& ship)
	{
		if(&ship!=this)
		{
			this->h_size=ship.h_size;
			this->errors=ship.errors;
			this->realDim=ship.realDim;
			this->structure=ship.structure;
			this->weight=ship.weight;
			this->x_size=ship.x_size;
			this->y_size=ship.y_size;
			this->fatalError=ship.fatalError;
		}
		return *this;
	}

	 /*get the weight of [x,y] heap and return -1 iff x and y are not valid indexes*/
	 int getWight(int x,int y)
	 {
		 if(checkDim(x,y,0))
		 {
			 return this->weight[x][y];
		 }
		 return -1;

	 }

	 /*
	  * return true iff the container is arrely exist in the
	  * ship
	  */
	 bool ContainerExist(ContainerId id);
	int getH_size() const {
		return h_size;
	}
	int getX_size() const {
		return x_size;
	}
	int getY_size() const {
		return y_size;
	}

	vector<Error>& isIsValid()  {
		return errors;
	}

	const vector<vector<int> >& getRealDim() const {
		return realDim;
	}

	const vector<vector<vector<Container> > >& getStructure() const {
		return structure;
	}

	const vector<vector<int> >& getWeight() const {
		return weight;
	}

	bool isFatalError() const {
		return fatalError;
	}

	const vector<Error>& getErrors() const {
		return errors;
	}

};





#endif /* SHIPFLOOR_H_ */
