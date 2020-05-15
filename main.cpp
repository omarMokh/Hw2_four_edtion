#include <iostream>
#include "Simulator.h"
#include <memory>
//#include <dlfcn.h>
#include "../interfaces/AbstractAlgorithm.h"
#include "../algorithm/algorithm.h"

using namespace std;
//hellow
/*
struct DLCloser
{
	void operator()(void *dlhandle) const noexcept{
	std::cout<<"cosint";
	dlclose(dlhandle);
	}
};
*/
int main()
{/*
	std::shared_ptr<AbstractAlgorithm> handle1(dlopen("../algorithm/_007_a.so",RTLD_LAZY));
	if(!handle1)
		std::cout<<"open faild"<<endl;
	else{
		std::cout<<"open 007 okey"<<endl;
		}*/
	vector<shared_ptr<AbstractAlgorithm>> algo;
	shared_ptr<AbstractAlgorithm> a=std::make_shared<Algorithm>();
	shared_ptr<AbstractAlgorithm> b=std::make_shared<Algorithm>();

	//algo.push_back(b);
	string inPath = "/home/omarabomokh/eclipseWorkspaceCPP/Hw2_2edtion/simolator2";
	string outPath = "/home/omarabomokh/eclipseWorkspaceCPP/Hw2_2edtion";
	Simulator S(inPath,outPath,algo);

}
