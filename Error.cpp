
#include "Error.h"


	Error::Error(int a)
	{
		switch(a)
		{
		case 0:
			 this->type=valid;
			 cout<<"should not reach this point(error.cpp)"<<endl;
			 break;
		case 2:
			this->type= errorType::DoblexyapearWithTheSameDAta;
			break;
		case 4:
			this->type=DoublexyApearWithDifferantData ;
			break;
		case 3:
			this->type=badFirstLineInShipRoute;
			break;
		case 1:
			this->type=errorType::notInTheShipDim;
			break;
		case 6:
			this->type=errorType::badportsymbolformat;
			break;
		case 5:
			this->type=ConsecutivePorts;
			break;
		case 8:
			this->type=errorType::OnlySingleValidPort;
			break;
		case 11:
			this->type=errorType::IdExist;
			break;
		case 12:
			this->type=nonValidweight;
			break;
		case 13:
			this->type=badPortFormatInportContainers;
			break;
		case 15:
			this->type=errorType::badIdFormatInportContainers;
			break;
		case 17:
			this->type=lastPortHasWaitingContainers;
			break;
		case 18:
			this->type=shipCapicityError;
			break;
	}
	}

	/*
	 * remove the Duplicates from given vector of errors
	 */
	 void removeDuplicates(std::vector<Error> &v)
	{
		std::sort(v.begin(),v.end(),[](Error a,Error b){return toInt(a)<toInt(b);});
		std::vector<Error>::iterator last;
		last=std::unique(v.begin(),v.end());
		v.erase(last,v.end());
		std::unique(v.begin(),v.end());
	}


	 int ErrorsToNumber(vector<Error> in)
	{
		if(in.empty())
			return 0;
		removeDuplicates(in);
		int result=0;
		for(Error er:in)
		{
			result+=toInt(er);
		}
		return result;
	}



	 void NumberToErrors(vector<Error> &result,int n)
	{
		if(n==0)
			return;
		std::string r;
		while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
		for(std::size_t i=0;i<r.size();i++)
		{
			if(r[i]=='1')
				result.push_back(Error(r.size()-i-1));
		}



	}

	 std::ostream& operator<<(std::ostream& out,const Error &err)
	{
		switch(err.type)
		{
		case Error::emptyPortCode:
			return out<<"empty port Code Error";
		case Error::portCodeSizeError:
			return out<<err.object<<" The size of the port code should be 5";
		case Error::unvalidPoerCodeFormat:
			return out<<err.object<<" is not valid port code";
		case Error::emptyContainer:
			return out<<"The Container is empty";
		case Error::unvalidContainerFormat:
			return out<<"unvalid container format";
		case Error::intigerPlanDimitions:
			return out<<"plan demintions must be integers";
		case Error::lineIncludeNonNumber:
			return out<<err.object<<" Line include non number";
			//start with a new errors as described in the homework
		case Error::unvalidId:
			return out<<"containers at port: illegal ID check ISO 6346";
		case Error::idSizeError:
			return out<<"containers at port: illegal ID check ISO 6346";
		case Error::unvalidIdFormat:
			return out<<"containers at port: illegal ID check ISO 6346";
		case Error::errorType::missinghashtagInShipRote:
			return out<<"Should be changed"<<endl;
		case Error::errorType::DoblexyapearWithTheSameDAta:
			return out<<"ship plan: bad line format after first line or duplicate x,y appearance with same data";
		case Error::errorType::DoublexyApearWithDifferantData:
			return out<<"ship plan: travel error - duplicate x,y appearance with different data";
		case Error::errorType::badFirstLineInShipRoute:
			return out<<" ship plan:  travel error - bad first line or file cannot be read altogether";
		case Error::errorType::notInTheShipDim:
			return out<<"ship plan: a given position exceeds the X/Y ship limits";
		case Error::errorType::badportsymbolformat:
			return out<<"travel route: bad port symbol format";
		case Error::errorType::ConsecutivePorts:
			return out<<"travel route: a port appears twice or more consecutively";
		case Error::errorType::OnlySingleValidPort:
			return out<<"travel route: travel error - file with only a single valid port";
		case Error::errorType::IdExist:
			return out<<"containers at port: ID already on ship";
		case Error::errorType::nonValidweight:
			return out<<"containers at port: bad line format, missing or bad weight";
		case Error::errorType::badPortFormatInportContainers:
			return out<<"containers at port: bad line format, missing or bad port dest";
		case Error::errorType::badIdFormatInportContainers:
			return out<<"containers at port: illegal ID check ISO 6346";
		case Error::errorType::lastPortHasWaitingContainers:
			return out<<"containers at port: last port has waiting containers ";
		case Error::shipCapicityError:
			return out<<"containers at port: total containers amount exceeds ship capacity";
		default:
			return out<<"we should not reach this case "<<err.type<<endl;

		}
	}
	 int toInt(const Error &err)
	{

		switch(err.type)
		{
		case Error::unvalidId:
			return pow(2,15);
		case Error::idSizeError:
			return pow(2,15);
		case Error::unvalidIdFormat:
			return pow(2,15);
		case Error::errorType::missinghashtagInShipRote:
			return pow(2,0);
		case Error::errorType::DoblexyapearWithTheSameDAta:
			return pow(2,2);
		case Error::errorType::DoublexyApearWithDifferantData:
			return pow(2,4);
		case Error::errorType::badFirstLineInShipRoute:
			return pow(2,3);
		case Error::errorType::notInTheShipDim:
			return pow(2,1);
		case Error::errorType::badportsymbolformat:
			return pow(2,6);
		case Error::errorType::ConsecutivePorts:
			return pow(2,5);
		case Error::errorType::OnlySingleValidPort:
			return pow(2,8);
		case Error::errorType::IdExist:
			return pow(2,11);
		case Error::errorType::nonValidweight:
			return pow(2,12);
		case Error::errorType::badPortFormatInportContainers:
			return pow(2,13);
		case Error::errorType::badIdFormatInportContainers:
			return pow(2,15);
		case Error::errorType::lastPortHasWaitingContainers:
			return pow(2,17);
		case Error::shipCapicityError:
			return pow(2,18);
		default:
			cout<<"should not reach this line(error.cpp)"<<endl;
			return 0;

	}
}
