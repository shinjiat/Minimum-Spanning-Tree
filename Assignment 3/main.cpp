/*
	Teo Shin Jiat
	4947435
	Tested and compiled successfully on Windows 10 (Codeblocks)
	Please read instruction.docx in order to view the MST picture
	Function declaration in header.h
	Function definition in function.cpp


	**
	1) sudo apt-get install graphviz
	2) clear && g++ *.cpp *.h -o main && ./main

	**
*/


#include <iostream>
#include <limits>
#include <stdio.h>
#include <string>
#include <cstdlib> //system("");
#include <string.h>
#include "header.h"
using namespace std;


int main()
{

	//VARIABLE DECLARATION
	int numberNode, numberOfEntry, option, largest;

	cout << endl << endl;
	cout << "\t\t\t* * * * * * * * * * * * * * * * * * *" << endl;
	cout << "\t\t\t*  Minimum Spanning Tree Calculator *" << endl;
	cout << "\t\t\t* * * * * * * * * * * * * * * * * * *" << endl;

	cout << endl;
	cout << "\t\t\t[1] - Enter graph information" << endl;
	cout << "\t\t\t[2] - Read from file: " << endl;
	cout << "\t\t\tOption : ";
	cin >> option;
	cout << endl;

        //VALIDATION OF INPUT, ACCEPT ONLY 1 OR 2
		while(option != 1 && option != 2)
		{
		    //IF NOT NUMBER VALUE IS ENTERED
		    //CLEAR INPUT BUFFER
		    cin.clear();
		    cin.ignore();
			cout << "Invalid entry, please enter 1 or 2 only!" << endl;
			cout << "Option : ";
			option = 2;
			cin >> option;
		}

        //FUNCTION TO ENTER GRAPH INFO MANUALLY
		if(option == 1)
		{
			enterGraph(numberNode, numberOfEntry);
		}

        //FUNCTION TO READ GRAPH INFO FROM A FILE
        //FILE NAME IS USER INPUT
		else
		{
			readGraph(numberNode, numberOfEntry);
		}
char secondOption = '0';
string signal = "haven't delete edge yet";
do{

	findLargest(numberNode, numberOfEntry, largest, signal);


    //SORT THE NUMBERS BY WEIGHT
    //THE VALUE 1 INDICATING SORTING BY WEIGHT, VALUE 2 SORT BY NODE FROM VALUE
    //FUNCTION OVERLOADED
	sort(numberOfEntry, 1);



	//CALCULATION FUNCTION
	//WILL DISPLAY THE EDGE, WEIGHT AND THE MST IMAGE
	calculate(numberNode, numberOfEntry, largest, signal);

	cout << "\n\n____________________________________________________" << endl;
	cout << "Display again with a randomly selected \"EDGE\" deleted." << endl;
	cout << "Option : (Y/N) : ";
	cin >> secondOption;
        while(secondOption != 'Y' && secondOption != 'y' &&secondOption != 'N' &&secondOption != 'n')
        {
            cout << "Invalid option, please enter Y or N only!" << endl;
            cout << "Option : (Y/N) : ";
            cin >> secondOption;
        }

    if(secondOption == 'Y' || secondOption == 'y')
    {
    	signal = "this is a deleting signal";
        cout << "A randomly selected \"EDGE\" has been deleted." << endl;
        cout << "Now will redisplay the graph again." << endl;
        int randomIndex = randomEdge(numberOfEntry);
    }
}while(secondOption != 'N' && secondOption != 'n');

    cout << "\nProgram has been terminated..." << endl;
    return 0;

}
