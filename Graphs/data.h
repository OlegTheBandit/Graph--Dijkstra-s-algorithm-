
#pragma once
#include <iostream>
#include <string>
#include "List.h"

#ifndef data_h
using namespace std;



struct information
{
	int price;
	struct city_list *road;
};

 struct city_list
{
	
	bool visite;
	int way_price;
	string city_name;
	List<information> *list;
};





#define data_h
#endif //data_h