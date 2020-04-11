
#include <iostream>
#include <fstream>
#include <string>
#include "data.h"
#include <stdlib.h>

using namespace std;

city_list* find_city(List<city_list>& graph, string city)
{
	for (int i = 0; i <(int) graph.get_size(); i++)
	{
		if (graph.get_pointer(i)->data.city_name == city)
		{
			return &graph.get_pointer(i)->data;
			break;
		}
	}
}

bool all_visit_check(List<city_list>& graph)
{
	for (int i = 0; i < (int)graph.get_size(); i++)
	{
		if (graph.get_pointer(i)->data.visite == 0)
		{
			return 0;
		}
	}
	return 1;
}

void city_list_build(List<city_list>& list, ifstream& file)
{
	char c;
	city_list city;
	int i = 0;
	while (!file.eof())
	{
		c = file.get();
		if (c == ';')
		{
			i++;
			if (i > 0)
			{
				bool flag = 1;
				for (int i = 0; i < (int)list.get_size(); i++)
				{
					if (list.get_pointer(i)->data.city_name == city.city_name)
					{
						flag = 0;
						break;
					}
				}
				if (flag == 1)
				{
					list.push_back(city);
				}
				city.city_name.clear();
			}
			if (i == 2)
			{
				i = 0;

				c = file.get();

				while (c != '\n')
				{
					if (file.eof())
						return;
					c = file.get();
				}
			}
		}
		else
			city.city_name.push_back(c);
	}

}

void graph_build(List<city_list>& graph, ifstream& file)
{
	for (int i = 0; i < (int)graph.get_size(); i++)
	{
		graph.get_pointer(i)->data.list = new List<information>;
	}
	
	
	string first_city;
	string second_city;
	string way_to_s;
	string way_back_s;
	int way_to;
	int way_back;
	int i = 0;
	while (!file.eof())
	{
		char c = ' ';
		while (c != '\n')
		{
			c = file.get();
			if (file.eof())
				break;
			if (c == ';')
			{
				i++;
				continue;
			}
			if (i == 0)
				first_city.push_back(c);
			if (i == 1)
				second_city.push_back(c);
			if (i == 2)
				way_to_s.push_back(c);
			if (i == 3 && c!='\n')
				way_back_s.push_back(c);
		}
		i = 0;
		information tmp;
		if (way_to_s != "N/A")
		{
			
			way_to = atoi(way_to_s.c_str());
			
			
			tmp.price = way_to;
		
			tmp.road = find_city(graph, second_city);
			/*tmp.road = &find_city(graph, second_city);*/

			
			for (int i = 0; i < (int)graph.get_size(); i++)
			{
				if (graph.get_pointer(i)->data.city_name == first_city)
				{
					graph.get_pointer(i)->data.list->push_back(tmp);
					
					break;
				}
			}

			
		}
		if (way_back_s != "N/A")
		{
			way_back = atoi(way_back_s.c_str());
			
			tmp.price = way_back;

			tmp.road = find_city(graph, first_city);
			/*tmp.road = &find_city(graph, first_city);*/
			
			for (int i = 0; i < (int)graph.get_size(); i++)
			{
				if (graph.get_pointer(i)->data.city_name == second_city)
				{
					graph.get_pointer(i)->data.list->push_back(tmp);
					
					break;
				}
			}
		}
		way_to_s.clear();
		way_back_s.clear();
		first_city.clear();
		second_city.clear();

			
	}
}

void way_build(List<city_list>& graph, city_list* start_city)
{
	
	while (!all_visit_check(graph))
	{
		
		for (int i = 0; i <(int) start_city->list->get_size(); i++)
		{
			
			if (start_city->list->get_pointer(i)->data.price + start_city->way_price <
				start_city->list->get_pointer(i)->data.road->way_price)
			{
				start_city->list->get_pointer(i)->data.road->way_price =
					start_city->list->get_pointer(i)->data.price + start_city->way_price;
			}

		}

		for (int i = 0; i < (int)start_city->list->get_size(); i++)
		{
			if (start_city->list->get_pointer(i)->data.road->visite==0)
			{
				
				start_city->visite = 1;
				way_build(graph, start_city->list->get_pointer(i)->data.road);
				
			}
		}
		start_city->visite = 1;
	}
}

void show_way(List<city_list>& graph, string final_city, string first_city)
{
	if (final_city == first_city)
	{
		
		return;
	}
	for (int i = 0; i < graph.get_size(); i++)
	{
		for (int j = 0; j < graph.get_pointer(i)->data.list->get_size(); j++)
		{
			if (graph.get_pointer(i)->data.list->get_pointer(j)->data.road->city_name == final_city
				&& (graph.get_pointer(i)->data.list->get_pointer(j)->data.road->way_price -
					graph.get_pointer(i)->data.list->get_pointer(j)->data.price) == graph.get_pointer(i)->data.way_price)
			{

				cout << graph.get_pointer(i)->data.city_name<<"<-";
				show_way(graph, graph.get_pointer(i)->data.city_name, first_city);

			}
		}
	}
}

int main()
{

	ifstream input("input.txt");
	
	List<city_list> graph;
	city_list_build(graph, input);
	input.close();
	input.open("input.txt");
	graph_build(graph, input);
	input.close();

	cout << "Select the departure city:" << endl;
	int n;
	for (int i = 0; i < (int)graph.get_size(); i++)
	{
		graph.get_pointer(i)->data.visite = 0;
		graph.get_pointer(i)->data.way_price = 9999999;
		cout << i + 1 << ". " << graph.get_pointer(i)->data.city_name << endl;
	}

	cin >> n;
	n--;
	
	while (1)
	{
		if (n<0 || n>(int)graph.get_size())
		{
			cout << "There is no such city, choose another one" << endl;
			cin >> n;
			cout << endl;
			n--;
		}
		else
		{
			break;
		}
	}

	
	graph.get_pointer(n)->data.way_price = 0;

	city_list* start_city = &graph.get_pointer(n)->data;
	way_build(graph, start_city);
	int b;
	cout << "Select your destination city: ";
	cin >> b;
	
	while (1)
	{
		if (n<0 || n>(int)graph.get_size())
		{
			cout << "There is no such city, choose another one" << endl;
			cin >> n;
			cout << endl;
			n--;
		}
		else
		{
			break;
		}
	}

	b--;
	while (1)
	{
		if (n<0 || n>(int)graph.get_size())
		{
			cout << "There is no such city, choose another one" << endl;
			cin >> n;
			cout << endl;
			n--;
		}
		else
		{
			break;
		}
	}
	cout << graph.get_pointer(b)->data.city_name<<"<-";
	show_way(graph, graph.get_pointer(b)->data.city_name, graph.get_pointer(n)->data.city_name);
	cout <<"Price: "<< graph.get_pointer(b)->data.way_price;
	
	return 0;
}

