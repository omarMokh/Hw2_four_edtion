/*
 * FileManager2.cpp
 *
 *  Created on: 6 ����� 2020
 *      Author: Dell
 */




/*
 * FileManager.cpp
 *
 *  Created on: 5 ����� 2020
 *      Author: Dell
 */



#include "FileManager2.h"
bool hasOnlyDigits(string &number);
bool chechTheFileFirstLine(ifstream & f)
{
	string line;
	std::getline(f,line);
	std::stringstream sline(line);
	sline>>line;
	if(line=="#") return true;
	return  false;
}

/*
 * return false if you have an error in the first line
 */
bool planTokens(ifstream & f, vector<int> &result,vector<Error> &errors)
{

	string line;
	int line_number=1;
	bool first_line=true;
	while(std::getline(f,line))
	{

		std::stringstream sline(line);
		string first; std::getline(sline,first,',');
		string second; std::getline(sline,second,',');
		string third; std::getline(sline,third);
		std::stringstream tmp_first(first);
		std::stringstream tmp_second(second);
		std::stringstream tmp_third(third);
		tmp_first>>first;
		tmp_second>>second;
		tmp_third>>third;
		if(first_line)
		{
			first_line=false;
			if(!hasOnlyDigits(first) || !hasOnlyDigits(second) || !hasOnlyDigits(third))
			{
				errors.push_back(Error(Error::errorType::badFirstLineInShipRoute));
				return false;
			}
			else{
				result.push_back(stoi(first));
				result.push_back(stoi(second));
				result.push_back(stoi(third));

			}
		}/*not the first line*/
		else{
			if(!hasOnlyDigits(first) || !hasOnlyDigits(second) || !hasOnlyDigits(third))
			{
				errors.push_back(Error(Error::lineIncludeNonNumber,std::to_string(line_number)));
			}
			else{
				result.push_back(stoi(first));
				result.push_back(stoi(second));
				result.push_back(stoi(third));

			}

			}
		line_number++;
	}
return true;
}

bool hasOnlyDigits(string& number){
	bool has_only_digits = true;
	if(number=="") return false;
	for (size_t n = 0; n < number.length(); n++)
	  {
		char tmp=number[n];
	  if (!isdigit( tmp ))
		{
		has_only_digits = false;
		break;
		}
	  }
	return has_only_digits;
}
//return vector with containers

void containerTokens(ifstream &f,vector<Container> &result,vector<Error> &errors)
{

	string line;

	while(std::getline(f,line))
	{

		std::stringstream sline(line);
		string sId; std::getline(sline,sId,',');
		string sWeight; std::getline(sline,sWeight,',');
		string sPort; std::getline(sline,sPort);
		std::stringstream tmp_id(sId);
		std::stringstream tmp_weight(sWeight);
		std::stringstream tmp_port(sPort);
		tmp_id>>sId;
		tmp_weight>>sWeight;
		tmp_port>>sPort;
		vector<Error> cError;
		if(hasOnlyDigits(sWeight))
		{
			Container tmp_c(stoi(sWeight),sPort,sId);
			if(tmp_c.getError().getType()==Error::valid)
			{
				result.push_back(tmp_c);
			}else
			{
				tmp_c.getErrors(cError);
				for(Error e:cError)
				{
					if(e==Error::errorType::unvalidContainerFormat or e==Error::idSizeError )
					errors.push_back(Error(Error::errorType::badIdFormatInportContainers));
					if(e==Error::errorType::unvalidPoerCodeFormat or e==Error::errorType::portCodeSizeError)
						errors.push_back(Error(Error::errorType::badPortFormatInportContainers));
				}
			}


		}else
		{
			errors.push_back(Error(Error::nonValidweight,sWeight));

		}
	}

}
bool routeTokens(ifstream &f,vector<SeaportCode> &result,vector<Error> &errors)
{

	std::string line;
	while(std::getline(f,line))
		{

			std::stringstream sline(line);
			string sCode;sline>>sCode;
			SeaportCode code=sCode;
			if(code.getError().getType()==Error::valid)
			{
				result.push_back(code);
			}
			else{
				errors.push_back(Error(Error::errorType::badportsymbolformat));
			}
	}
	f.close();

return true;
}

