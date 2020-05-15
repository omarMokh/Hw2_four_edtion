
#include "Simulator.h"

	Simulator::Simulator(string inpath,string outpath,vector<shared_ptr<AbstractAlgorithm>> algo):inRootPath(inpath),outRootPath(fullpath(outpath,"simolation_results"))
	,algorithms(algo)
	{
		vector<string> subFolders;
		read_directory(inRootPath,subFolders);
		if(this->makeFile(outRootPath)==false) return ;
		this->generalErrors.open(fullpath(outRootPath,"simulation_errors"));
		this->generalResults.open(fullpath(outRootPath,"simulation_results"));
		for(size_t algo_index=0;algo_index<this->algorithms.size();algo_index++)
		{
			string algo_result_full_path=fullpath(this->outRootPath,"algorithm_"+std::to_string(algo_index+1)+"_results");
			this->makeFile(algo_result_full_path);

			for(string x:subFolders) if(x!="." && x!="..")
			{
				string travel_path=fullpath(this->inRootPath,x);
				string full_travel_path_result=fullpath(algo_result_full_path,x);
				this->makeFile(full_travel_path_result);

				this->runTheAlgorithm(travel_path, full_travel_path_result,*(this->algorithms[algo_index]), algo_index+1);

			}

		}

	}
/*should be completed*/
bool existsFileTest (const std::string& name) {
	ifstream a(name);
	bool result=true;
	if (a.fail()) {
		result=false;
	}
	a.close();
	return result;
}



void Simulator::read_directory(const std::string& name, vector<string>& v)
{
    DIR* dirp = opendir(name.c_str());
	if(!dirp){
		return;
	}
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}
//return true iff key exist in the array
bool ErrorExist(vector<Error> &er,Error key)
{
	return std::any_of(er.begin(),er.end(),[key](Error r){return r==key;});
}

/*this function get port array and convert it array of coples so the first
one of the cuple contains the seaport and the secon contain the number of times we pass in this port*/
void convertTo2D(vector<pair<SeaportCode,int>> &result,vector<SeaportCode> const &input)
{
	int n=input.size();
	vector<pair<SeaportCode,int>> tmp(n);
	result=tmp;
	result[0].first=input[0];
	result[0].second=1;
	for(int i=0;i<n;i++)
	{
		int cur=1;

		for(int j=0;j<i;j++)
		{
			result[i].first=input[i];

			if(result[j].first==result[i].first) cur=result[j].second+1;
			result[i].second=cur;

		}
	}
}



bool Simulator:: runTheAlgorithm(string inPath,string outPath,AbstractAlgorithm &algo,int algo_index)
{


	/*check if the plan file exist*/
	if(!existsFileTest(fullpath(inPath,"plan")))
	{
		this->generalErrors<<"we can't run  algorithm "<<algo_index<<" on "<<inPath<<"because plan file is not exist "<<endl;
		return false;

	}
	ofstream errorsFile;
	errorsFile.open(fullpath(outPath,"errors"));
	int readshipplan_result=algo.readShipPlan(fullpath(inPath,"plan"));
	vector<Error> planErrors;
	NumberToErrors(planErrors,readshipplan_result);
	if(ErrorExist(planErrors,Error(Error::badFirstLineInShipRoute)))/*check if the dimintions of the plan are correct*/
	{
		this->generalErrors<<"we can't run  algorithm "<<algo_index<<" on "<<inPath<<" because it have unvalid ship dimintions "<<endl;
		errorsFile.close();
		return false;
	}
	if(!planErrors.empty())/*plan file have non errors*/
	{
		errorsFile<<"Plan Errors are:"<<endl;
		for(Error er:planErrors)
		{
			errorsFile<<er<<endl;
		}
	}
	if(!existsFileTest(fullpath(inPath,"route")))
		{
			this->generalErrors<<"we can't run algorithm "<<algo_index<<" on "<<inPath<<" because route file is not exist "<<endl;
			errorsFile.close();
			return false;

		}
	int readshiproute_result;
	readshiproute_result=algo.readShipRoute(fullpath(inPath,"route"));
	vector<Error> routeErrors;
	NumberToErrors(routeErrors,readshiproute_result);
	if(!routeErrors.empty())/*roure file have non fatal errors*/
		{
			errorsFile<<"Route Errors are: "<<endl;
			for(Error er:routeErrors)
			{
				errorsFile<<er<<endl;
			}
		}
	ShipRoute shipRoute(fullpath(inPath,"route"));
	int n=shipRoute.getRoute().size();
	vector<pair<SeaportCode,int>> route;
	convertTo2D(route,shipRoute.getRoute());

	for(int i=0;i<n;i++)
	{SeaportCode port=route[i].first;
	string cargo_file_name=fullpath(inPath,port.toString()+std::to_string((route[i].second)));
		if(!existsFileTest(cargo_file_name))
		{
			this->generalErrors<<"we can't run algorithm "<<algo_index<<" on "<<inPath<<" because "<<cargo_file_name<<"  file is not exist "<<endl;
				errorsFile.close();
				return false;


		}
		int getinstructionforcargo_result;
		getinstructionforcargo_result=algo.getInstructionsForCargo(fullpath(inPath,port.toString()+std::to_string((route[i].second))),fullpath(outPath,port.toString()+"_cargoData"+std::to_string(route[i].second)));
		vector<Error> portErrors;
		NumberToErrors(portErrors,getinstructionforcargo_result);
		if(!portErrors.empty())/* errors in the algorithm run*/
		{
			errorsFile<<"The Errors in " + port.toString() + std::to_string(route[i].second)+ " are: " <<endl;
			for(Error err:portErrors)
			{
				errorsFile<<err<<endl;
			}

		}

	}
		this->generalResults<<"Algorithm "<<algo_index<<" Results on "<<inPath<<" : "<<endl<<"algo.getSteps()"<<" stepes"<<endl ;

	return true;

}


