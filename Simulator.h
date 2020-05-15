/*
 * Simulator.h
 *
 *  Created on: 13 ����� 2020
 *      Author: Dell
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <utility>
#include <sstream>
#include <vector>
#include<algorithm>
#include <tuple>
#include "AbstractAlgorithm.h"
#include "Error.h"
#include "Container.h"
#include "ContainerId.h"
#include "SeaportCode.h"
#include "ShipRoute.h"
#include "ShipFloor.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <filesystem>
#include <bits/stdc++.h>
#include <memory>



using namespace std;

class Simulator{
public:
	string inRootPath;
	string outRootPath;
	ofstream generalErrors;
	ofstream generalResults;
	vector<shared_ptr<AbstractAlgorithm>> algorithms;
	Simulator(string inpath,string outpath,vector<shared_ptr<AbstractAlgorithm>> algo);
	/*get the child path from the perent*/
	string fullpath( string const parent,string last)
	{
		return parent+"/"+last;
	}
	

	
	
	bool makeFile(string parent,string name)
	{
		if (mkdir(fullpath(parent,name).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1){
				cout<<"fatal error we cant create the result file so the simulation stopped"<<endl;
			        cerr << "Error :  " << strerror(errno) << endl;
			        return false ;
			}
		return true;

	}
	bool makeFile(string fullPath)
	{
		if (mkdir(fullPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1){
				cout<<"fatal error we can't create the result file so the simulation stopped"<<endl;
			        cerr << "Error :  " << strerror(errno) << endl;
			        return false ;
			}
		return true;


	}



	void read_directory(const std::string& name, vector<string>& v);

	bool  runTheAlgorithm(string inPath,string outPath,AbstractAlgorithm &algo,int algo_index);

};



#endif /* SIMULATOR_H_ */
