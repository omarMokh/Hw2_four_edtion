





#include "Algorithm.h"
#include "../interfaces/AlgorithmRegistration.h"
REGISTER_ALGORITHM(Algorithm)

/*
 * remove the duplicates container id from the array
 */


	int Algorithm::getInstructionsForCargo(const std::string &pathIn,const std::string &pathOut)
	{/*we asuume that shipfloor class has no fatal error*/
		ifstream in;
		ofstream out;
		out.open(pathOut);
		in.open(pathIn);
		vector<Container> cList;
		vector<Error> tmp_err;
		containerTokens(in,cList,tmp_err); /*get alist of the containers and errors in the file*/
		this->errors=tmp_err;
		if(*(this->route_itr)==this->route.getRoute()[this->route.getRoute().size()-1])
		{
			//this is the last port
			if(!cList.empty())
			{
				this->errors.push_back(Error::errorType::lastPortHasWaitingContainers);
			}


		}
		for(std::vector<Container>::iterator it=cList.begin();it!=cList.end();)
		{
			if(this->plan.ContainerExist((*it).getId()))
			{//the container id is exist in the ship
				this->errors.push_back(Error(Error::errorType::IdExist));
				it=cList.erase(it);
				continue;
			}
			if(!this->route.passInthePort((*it).getDestination(), route_itr))
				{
					out<<"R"<<","<<(*it).getId()<<", the ship will not reach "<<(*it).getDestination()<<" port"<<endl;
					it=cList.erase(it);

				}
			else{
				++it;
			}

		}

		ShipRoute g=route;
		/*this is the number of the containers that we can't insert because there are no place*/
			int empty_places=plan.emptyPlaces()+plan.containersPortNumber(*this->route_itr);
			int delete_containers=(int)cList.size()-empty_places;
			for(int i=0;i<delete_containers;i++)
			{
				this->errors.push_back(Error(Error::errorType::shipCapicityError));
				out<<"R"<<","<<cList[cList.size()-1].getId()<<", there are no place in the ship"<<endl;

				cList.pop_back();

			}
		vector<Container> unload_list;/*list to be unload*/
		vector<tuple<int,int,int>> unload_pos;
		plan.unload(unload_list,*route_itr,unload_pos);
		for(std::size_t i=0;i<unload_list.size();i++)
		{
			out<<"U"<<","<<unload_list[i].getId()<<","<<std::get<0>(unload_pos[i])<<","<<std::get<1>(unload_pos[i])<<","<<std::get<2>(unload_pos[i])<<endl;
			this->steps++;
			if(unload_list[i].getDestination()!=*route_itr)
			{
				cList.push_back(unload_list[i]);
			}
		}
/* sort the containers start from the closest one to the fat one */
		std::sort(cList.begin(), cList.end(), [&g](Container a,Container  b){ return g.before(g.begin(),b.getDestination(),a.getDestination()); });
		Algorithm::xy xy(plan.getX_size(),plan.getY_size());
		for(std::size_t i=0;i<cList.size();i++)
		{

			if(this->plan.isHeapFull(xy.x, xy.y)){ ++xy;i--; continue;}
			{

				out<<"L"<<","<<cList[i].getId()<<","<<plan.getStructure()[xy.x][xy.y].size()<<","<<xy.x<<","<<xy.y<<endl;
				this->steps++;
				this->plan.insert(cList[i],xy.x,xy.y);
				++xy;
			}

		}
			in.close();out.close();
			++this->route_itr;
			return ErrorsToNumber(this->errors);

		}
