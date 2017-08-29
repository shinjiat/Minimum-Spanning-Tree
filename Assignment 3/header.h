#ifndef header_h
#define header_h
#include <iostream>
#include <string>
using namespace std;
//STRUCT
struct nodes
{
	int FROM;
	int TO;
	int WEIGHT;

	int MST_FROM;
	int MST_TO;
	int MST_WEIGHT;

};

//FUNCTION DECLARATION
void enterGraph(int &numberNode, int &numberOfEntry);
void readGraph(int &numberNode, int &numberOfEntry);
void findLargest(int numberNode, int numberOfEntry, int &largest, string signal);
void sort(int numberOfEntry, int sortOption);
void calculate(int numberNode, int numberOfEntry, int largest, string signal);
int randomEdge(int numberNode);
#endif // header_h
