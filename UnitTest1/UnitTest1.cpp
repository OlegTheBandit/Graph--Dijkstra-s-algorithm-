#include "pch.h"


#include "..///Graphs/Graphs.cpp"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		
	public:
		List<city_list> graph;
	
		TEST_METHOD(test_city_list_builder)
		{
			
			ifstream input("D:\\Aistr\\4th term\\Graphs\\UnitTest1\\test.txt");
			city_list_build(graph, input);
			Assert::AreEqual(graph.get_pointer(0)->data.city_name, (string)"St. Petersburg");
			Assert::AreEqual(graph.get_pointer(1)->data.city_name, (string)"Moskow");
			Assert::AreEqual(graph.get_pointer(2)->data.city_name, (string)"Habarovsk");
			Assert::AreEqual(graph.get_pointer(3)->data.city_name, (string)"Vladivostok");
			Assert::AreEqual((int)graph.get_size(), 4);
			input.close();
		}
		TEST_METHOD(graph_build_test)
		{
			ifstream input("D:\\Aistr\\4th term\\Graphs\\UnitTest1\\test.txt");
			city_list_build(graph, input);
			input.close();
			input.open("D:\\Aistr\\4th term\\Graphs\\UnitTest1\\test.txt");
			graph_build(graph, input);
			input.close();
			Assert::AreEqual(graph.get_pointer(0)->data.list->get_pointer(0)->data.road->city_name, (string)"Moskow");
			Assert::AreEqual(graph.get_pointer(0)->data.list->get_pointer(1)->data.road->city_name, (string)"Habarovsk");
			Assert::AreEqual(graph.get_pointer(0)->data.list->get_pointer(2)->data.road->city_name, (string)"Vladivostok");
		}
		TEST_METHOD(way_build_test)
		{
			ifstream input("D:\\Aistr\\4th term\\Graphs\\UnitTest1\\test.txt");
			city_list_build(graph, input);
			input.close();
			input.open("D:\\Aistr\\4th term\\Graphs\\UnitTest1\\test.txt");
			graph_build(graph, input);
			input.close();
			for (int i = 0; i < (int)graph.get_size(); i++)
			{
				graph.get_pointer(i)->data.visite = 0;
				graph.get_pointer(i)->data.way_price = 9999999;
				cout << i + 1 << ". " << graph.get_pointer(i)->data.city_name << endl;
			}
			graph.get_pointer(0)->data.way_price = 0;

			city_list* start_city = &graph.get_pointer(0)->data;
			way_build(graph, start_city);
			Assert::AreEqual(graph.get_pointer(1)->data.way_price, 10);
			Assert::AreEqual(graph.get_pointer(2)->data.way_price,	14);
			Assert::AreEqual(graph.get_pointer(3)->data.way_price, 20);
		}
		TEST_METHOD(show_way_test)
		{
			ifstream input("D:\\Aistr\\4th term\\Graphs\\UnitTest1\\test.txt");
			city_list_build(graph, input);
			input.close();
			input.open("D:\\Aistr\\4th term\\Graphs\\UnitTest1\\test.txt");
			graph_build(graph, input);
			input.close();
			for (int i = 0; i < (int)graph.get_size(); i++)
			{
				graph.get_pointer(i)->data.visite = 0;
				graph.get_pointer(i)->data.way_price = 9999999;
				cout << i + 1 << ". " << graph.get_pointer(i)->data.city_name << endl;
			}
			graph.get_pointer(0)->data.way_price = 0;

			city_list* start_city = &graph.get_pointer(0)->data;
			way_build(graph, start_city);
			show_way(graph, graph.get_pointer(3)->data.city_name, graph.get_pointer(3)->data.city_name);
		}
	};
}
