/*
 * ShipFloor.cpp
 *
 *  Created on: 6 ����� 2020
 *      Author: Dell
 */

/*
 * Ship.cpp
 *
 *  Created on: 1 ����� 2020
 *      Author: Dell
 */
#include <tuple>
#include "ShipFloor.h"
/*
 * return 0 if the input is valid return 1
 * if the input have same data more than one time
 * return 2 if the input have same x,y with differant h
 */
int sameData(vector<int> &data)
{
	int result=0;
	int a,b,c,a2,b2,c2;
	for(size_t i=3;i<data.size();i+=3)
	{
		a=data[i];
		b=data[i+1];
		c=data[i+2];
		for(size_t j=3;j<data.size();j+=3)
		{
			a2=data[j];
			b2=data[j+1];
			c2=data[j+2];
			if(a==a2 and b==b2 and i!=j)
			{
				if(c==c2)
				{
					cout<<c<<c2<<endl;
					result=1;
				}
				if(c!=c2)
				{
					return 2;
				}

			}
		}
	}
	return result;
}
/*
 * return 1 if x,y,z are in the diminstions
 * return 0 if x,y are not in the limit
 * return -1 if z is not in the limit
 */
	int ShipFloor::checkDim(int x,int y,int z)
	{
		int result=1;
		if(x<x_size && y<y_size)
		{
			result=z<realDim[x][y]?1:-1;
		}
		else{
			return 0;
		}
		return result;

	}


	ShipFloor::ShipFloor(string path)
//init ship floor from file
	{//check the dim of the input and throw appropriate error
		ifstream f;
		vector<int> result;
		vector<Error> errors;
		f.open(path);
		if(!planTokens(f,result,errors))
		{
			this->fatalError=true;
			return ;
		}
		this->fatalError=false;
		this->errors=errors;
		int x,y,h;
		int n=result.size();
		if(n==0) {this->errors.push_back(Error::errorType::badFirstLineInShipRoute);return ;}
		if(n%3!=0){cout<<"this condition shold never be true"<<endl;}
		x=result[1];
		y=result[2];
		h=result[0];
		this->x_size=x;this->y_size=y;this->h_size=h;
		vector<vector<vector<Container> > > tmp (x,vector<vector<Container> >(y,vector <Container>()));
		structure=tmp;
		vector<vector<int>>  tmp_w(x,vector<int>(y,0));
		this->weight=tmp_w;
		vector<vector<int>>  tmp_realDim(x,vector<int>(y,h));
		realDim=tmp_realDim;
		int isSameData=sameData(result);
		if(isSameData!=0)
		{
			isSameData==2?this->errors.push_back(Error(Error::errorType::DoublexyApearWithDifferantData))
					:this->errors.push_back(Error(Error::errorType::DoblexyapearWithTheSameDAta));
		}
		int tmp1,tmp2,tmp3;
		for(size_t i=3;i<result.size();i+=3)
			{
			tmp1=result[i];
			tmp2=result[i+1];
			tmp3=result[i+2];

			if(checkDim(tmp1,tmp2,tmp3)!=1)
			{
				string errObject=std::to_string(tmp1)+" "+std::to_string(tmp2)+" "+std::to_string(tmp3);
				if(checkDim(tmp1,tmp2,tmp3)==0)
				{
					this->errors.push_back(Error(Error::notInTheShipDim,errObject));
				}
				else
				{
					this->errors.push_back(Error(Error::errorType::equalormorenumbersofFloor,errObject));
				}
			}
			else{
			realDim[tmp1][tmp2]=tmp3;
			}
			}
		f.close();



	}

bool contains(std::vector<SeaportCode>& key_list,SeaportCode key)
{
	for(size_t i=0;i<key_list.size();i++)
	{
		if(key_list[i]==key)
		{
			return true;
		}
	}
	return false;
}
/*
 * return true iff the container is arrely exist in the
 * ship
 */
bool ShipFloor::ContainerExist(ContainerId id)
{
	for(int x=0;x<x_size;x++)
	{
		for(int y=0;y<y_size;y++)
		{
			for(std::size_t h=0;h<this->structure[x][y].size();h++)
			 {
				 if(this->structure[x][y][h].getId()==id)
					 return true;
			 }
		}
	}
	return false;

}
bool ShipFloor::unload(std::vector<Container> &result,SeaportCode portId,std::vector<tuple<int,int,int>> &con_place)
{
	bool flag=false;
	int h;
	for(int x=0;x<x_size;x++)
	{
		for(int y=0;y<y_size;y++)
		{
			h=0;
			for(std::vector<Container>::iterator it = structure[x][y].begin(); it!=  structure[x][y].end();)
			{ /*check whather the container destinastion is in key list*/
				h++;
				SeaportCode tmp_seaport=(*it).getDestination();
				if(portId==tmp_seaport){
					result.push_back(*it);
					con_place.push_back({h-1,x,y});
					structure[x][y].erase(it);
				}
				else{
					++it;
				}
			} 
		}
	}
	std::reverse(result.begin(), result.end());
	std::reverse(con_place.begin(), con_place.end());
	return flag;
}
	int ShipFloor::emptyPlaces()
	{
		int result=0,current=0;
		for(int x=0;x < this->x_size;x++)
		{
			for(int y=0;y<this->y_size;y++)
			{
				current=this->structure[x][y].size();
				result+=this->realDim[x][y]-current;

			}
		}

		return result;
	}

	int ShipFloor::containersPortNumber(SeaportCode port)
	{
		int result=0;
		for(int x=0;x<x_size;x++)
			{
				for(int y=0;y<y_size;y++)
				{
					for(size_t h=0;h<structure[x][y].size();h++)
					{/*check whather the container destinastion is in key list*/
						SeaportCode tmp_seaport=this->structure[x][y][h].getDestination();
						if(port==tmp_seaport)
						{
							result++;
						}
					}
				}
			}
		return result;

	}

bool ShipFloor::insert(Container &a,int x,int y,int z)

	{
		bool result;
		result=(checkDim(x,y,z));
		if(result){
			int real=structure[x][y].size();
			result=real==z?true:false;
		}
		if(result)
		{
			structure[x][y].push_back(a); //I will fixthat
			weight[x][y]+=a.getWeight();
		}
		return result;

	}
bool ShipFloor::insert(Container &a,int x,int y)
{


	structure[x][y].push_back(a);
	return true;
}


