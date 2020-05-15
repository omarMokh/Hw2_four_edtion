/*
 * FileManager2.h
 *
 *  Created on: 6 באפר׳ 2020
 *      Author: Dell
 */
 
 /*
 * this module contains functions that we used to manage the files
 * some of this functions have been used by different classes
 */

#ifndef FILEMANAGER2_H_
#define FILEMANAGER2_H_
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <fstream>
#include <sstream>
#include "Container.h"
#include<vector>
#include "Error.h"

using namespace std;

bool planTokens(ifstream & f,vector<int> &y,vector<Error> &errors);

bool hasOnlyDigits(string &number);
void containerTokens(ifstream &f,vector<Container> &result,vector<Error> &errors);
bool routeTokens(ifstream &f,vector<SeaportCode> &result,vector<Error> &errors);





#endif /* FILEMANAGER2_H_ */
