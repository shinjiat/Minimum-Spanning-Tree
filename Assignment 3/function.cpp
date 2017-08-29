//FUNCTION DEFINITION FILE

#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib>
#include "header.h"
using namespace std;

int dummydata, dummyFROM, dummyTO, dummyWEIGHT;
nodes N[50];//INSTANTIATING OBJECTS, ASSUMING MAX 50 NODES
nodes backupNodes[50];
//SORT THE STRUCTURE BASED ON WHAT VALUE(sortOption, 1 or 2) IS ENTERED
void sort(int numberOfEntry, int sortOption)
{


	int tempFrom, tempTo, tempCost;
    //SORT BY WEIGHT IN ORDER TO IMPROVE THE EFFICIENCY
	if(sortOption == 1)
	{
		//SORTING THE ARRAYS BY WEIGHT
		for(int j = 0; j < numberOfEntry - 2; j++)
		{
			for(int m = j + 1; m < numberOfEntry - 1; m++)
			{
				if(N[j].WEIGHT > N[m].WEIGHT)
				{
					tempFrom = N[j].FROM;
					tempTo   = N[j].TO;
					tempCost = N[j].WEIGHT;

					N[j].FROM = N[m].FROM;
					N[j].TO   = N[m].TO;
					N[j].WEIGHT = N[m].WEIGHT;

					N[m].FROM = tempFrom;
					N[m].TO = tempTo;
					N[m].WEIGHT = tempCost;
				}
			}
		}

  	}

  	else
  	{

		//SORT THE ARRAYS BY MST_FROM NODE
		for(int j = 0; j < numberOfEntry - 1; j++)
		{
			for(int m = j + 1; m < numberOfEntry; m++)
			{
				if(N[j].MST_FROM > N[m].MST_FROM)
				{
					tempFrom = N[j].MST_FROM;
					tempTo   = N[j].MST_TO;
					tempCost = N[j].MST_WEIGHT;

					N[j].MST_FROM = N[m].MST_FROM;
					N[j].MST_TO   = N[m].MST_TO;
					N[j].MST_WEIGHT = N[m].MST_WEIGHT;

					N[m].MST_FROM = tempFrom;
					N[m].MST_TO = tempTo;
					N[m].MST_WEIGHT = tempCost;
				}
			}
		}

  	}

}

//FUNCTION THAT ALLOW USER TO ENTER GRAPH INFO MANUALLY
//VALIDATION IS DONE ON EVERY INPUT
void enterGraph(int &numberNode, int &numberOfEntry)
{

    RESTART:
    /*
    PROGRAM WILL RESTART AT HERE IF NUMBER OF NODE ENTERED BY USER DID NOT MATCHED THE TOTAL UNIQUE NUMBERS ENTERED BY THE END OF THIS FUNCTION
    EXAMPLE : NUMBER OF NODE ENTERED : 3 BUT USER ENTERED
    1 2 3
    2 3 4
    4 3 5
    //THIS IS 4(1, 2, 3, 4) TOTAL OF UNIQUE NUMBERS
    */

	int uniqueNumber;
	int i = 0, check = 0, r = 0;

	cout << "\nEnter the number of nodes in the graph for validation checking later." << endl;
	cout << "Number of nodes : ";
	cin >> numberNode;

	while(!cin || numberNode < 1)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "\nInvalid entry, please enter number that is larger than 0 only!" << endl;
		cout << "Number of nodes : ";
		cin >> numberNode;
	}


	cout << "\nPlease enter the info of a graph." << endl;
	cout << "*\"From To Weight\", please leave a space between the numbers." << endl;
	cout << "Example : 1 2 4 as in from Node 1 to Node 2 with a Weight of 4" << endl;
	cout << "Terminate input by entering 0 0 0" << endl;

	do
	{
		cout << "Node " << i + 1 << ": ";
		cin >> N[i].FROM >> N[i].TO >> N[i].WEIGHT;

        //PROGRAM WILL NOT TAKE ANY ALPHABET, CHARACTER OR NEGATIVE NUMBERS
		while(!cin || N[i].FROM < 0 || N[i].TO < 0 || N[i].WEIGHT < 0)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "\nInvalid entry, please enter number that is larger than or equal to 0 only!" << endl;
				cout << i+1 << ") From Node : ";
				cin >> N[i].FROM;
			}

		if(N[i].FROM == 0 && N[i].TO == 0 && N[i].WEIGHT == 0)
		{
			check = 1;
		}

		i++;

    //EXIT INPUT LOOP IF CONDITION MET
    //WHICH 3 INPUT ARE ALL 0
	}while(check != 1);


	//MERGING ARRAY TO FIND DUPLICATED NODES
	numberOfEntry = i;
	int total_index = i*2;
	int j = 0;
	int merge_array[total_index];

	for(int i = 0; i < total_index; i++)
	{
		merge_array[i] = N[j].FROM;
		merge_array[i+1] = N[j].TO;
		j++;
		i++;
	}


    for (int i = 0; i != total_index; i++)
    {
        for (int j = 0; j != i; j++)
        {
            if((i != j) && (merge_array[j] == merge_array[i]))
            {
                //DUPLICATED NUMBER FOUND
                r++;
                break;
            }
        }
    }

    //MINUS 1 BECAUSE OF 000 ENTRY
    uniqueNumber = total_index - r - 1;


    if(numberNode != uniqueNumber)
    {
    	cout << "Number of nodes entered did not match!" << endl;
    	cout << "Number of nodes entered by : " << numberNode << endl;
    	cout << "Number of unique nodes entered : " << uniqueNumber << endl;
		cout << "Press enter to restart the program..." << endl;
		cin.ignore().get();

    	cout << endl << endl;
    	goto RESTART; //RESTART THE PROGRAM
    }

}

//FUNCTION TO READ GRAPH INFO FROM A FILE
//FILE NAME IS USER ENTERED
void readGraph(int &numberNode, int &numberOfEntry)
{
	int i = 0;
	string filename;

	cout << "Filename : ";
	cin >> filename;

	ifstream infile;
	infile.open(filename.c_str());


    //FILE NAME VALIDATION
	while(!infile)
	{
		cout << "\nError! File name \"" << filename << "\" was not found!" << endl;
		cout << "1) Please check if the file name entered contains the file extension" << endl;
		cout << "Example : graph should be graph.txt" << endl;
		cout << "2) Please confirm the file is in the same directory with the cpp." << endl;
		cout << "Filename : ";
		cin >> filename;

		infile.open(filename.c_str());
	}

	infile >> numberNode;

	while(!infile.eof())
	{
		infile >> N[i].FROM >> N[i].TO >> N[i].WEIGHT;
		i++;
	}

    //KEEPING THE VALUE OF i
	numberOfEntry = i;

}

//FINDING THE LARGEST VALUE
//USED IN CALCULATION PART IN ORDER TO FIND THE LIGHTEST WEIGHT
void findLargest(int numberNode, int numberOfEntry, int &largest, string signal)
{

		if(signal == "this is a deleting signal")
		{
			//replace all the variables afte deletion
			for(int i = 0; i < numberOfEntry; i++)
			{
				N[i].FROM = backupNodes[i].FROM;
				N[i].TO = backupNodes[i].TO;
				N[i].WEIGHT = backupNodes[i].WEIGHT;
			}



          cout << "\nAfter delete" << endl;
	     for(int i = 0; i < numberOfEntry-2; i++)
	     {
	     	cout << "Node " << i + 1 << ")  ";
			cout << N[i].FROM << " -> " << N[i].TO << " : " << N[i].WEIGHT;

			if(dummydata == i)
			{
				cout << "*<--deleted edge was here (" << dummyFROM << " -> " << dummyTO << " : " << dummyWEIGHT << ")";
			}

			cout << endl;
	     }
	     numberOfEntry = numberOfEntry - 1;
		}


		cout << "\nTotal Nodes(Unique) : " << numberNode << endl;
		cout << "Total of Entries    : " << numberOfEntry - 1 << endl;
		largest = 0;

		for(int i = 0; i < numberOfEntry; i++)
		{
			if(N[i].WEIGHT> largest)
			{
				largest = N[i].WEIGHT;
			}
		}


}

void calculate(int numberNode, int numberOfEntry, int largest, string signal)
{
	//remove first entry of 000 due to sorting
	if(signal == "this is a deleting signal")
	{
		for(int i = 0; i < numberOfEntry; i++)
		{
			N[i].FROM = N[i+1].FROM;
			N[i].TO = N[i+1].TO;
			N[i].WEIGHT = N[i+1].WEIGHT;
		}
	}
	//back up nodes before calculating, because this function will overwrite the original structure.
	//this back up structure will be used for displaying purpose later.
	for(int i = 0; i < numberOfEntry; i++)
	{
		backupNodes[i].FROM = N[i].FROM;
		backupNodes[i].TO = N[i].TO;
		backupNodes[i].WEIGHT = N[i].WEIGHT;
	}

	//SKIPPING 000 entry
	numberOfEntry = numberOfEntry - 1;


	int lowest, lowestIndex, lowestWeight, lightest, lighestIndex2;

	int check = 0, count = 0;
	int startIndex = 2; // FIRST INSERTION CONTAIN TWO VALUES
	lightest = largest;

	//GETTING THE FIRST LIGHTEST WEIGHT NODE
	for(int i = 0; i < numberOfEntry; i++)
	{
			if(N[i].WEIGHT < lightest)
			{
				lightest = N[i].WEIGHT;
				N[count].MST_FROM = N[i].FROM;
				N[count].MST_TO   = N[i].TO;
				N[count].MST_WEIGHT  = N[i].WEIGHT;
				count++;
				lighestIndex2 = i;
			}
	}


						//ASSIGNING MAX VALUE OF INTEGER TO THE MST VALUES IN THE NODES TO AVOID BEING COMPARE AGAIN
						N[lighestIndex2].FROM = largest + 1;
						N[lighestIndex2].TO = largest + 1;
						N[lighestIndex2].WEIGHT = largest + 1;



	lightest = largest;
	int lightestIndex, enterIf, largest2, check2, checkTotal;
	int checkFROM = 0, checkTO = 0;

	for(int a = 0; a < numberOfEntry; a++) //REPEAT BASED ON HOW MANY ENTRY
	{
	    //+1 BECAUSE MAYBE THE LARGEST VALUE CAN BE IN THE MST NODE
		largest2 = largest + 1;

		check = 0;
		for(int i = 0; i < numberOfEntry; i++)
		{
			for(int j = 0; j < count; j++)
			{
				if(N[i].FROM == N[j].MST_FROM || N[i].TO == N[j].MST_TO || N[i].TO == N[j].MST_FROM || N[i].FROM == N[j].MST_TO)
				{
					checkFROM=0;
					checkTO  =0;

					for(int k = 0; k < count; k++)
					{
						//CHECKING IF NUMBER IS ALREADY IN THE MST SET

						if(N[i].FROM == N[k].MST_FROM || N[i].FROM ==  N[k].MST_TO)
						{
							checkFROM = 1;
						}

						if(N[i].TO == N[k].MST_FROM || N[i].TO ==  N[k].MST_TO)
						{
							checkTO = 1;
						}

					}

						checkTotal = checkFROM + checkTO;

                        //ONLY ASSIGN IF WEIGHT IS LOWEST AND NEVER EXISTS BEFORE IN THE MST NODES
						if(N[i].WEIGHT < largest2 && checkTotal != 2)
						{
							largest2 = N[i].WEIGHT;
							check = 1;
							lightestIndex = i;
							lightest = N[i].WEIGHT;
						}
				}
			}
		}


						if(check == 1)
						{
                                //ASSIGN AFTER COMPARING IS DONE
                                N[count].MST_FROM = N[lightestIndex].FROM;
                                N[count].MST_TO   = N[lightestIndex].TO;
                                N[count].MST_WEIGHT  = N[lightestIndex].WEIGHT;

                                //SET TO LARGEST TO AVOID THESE MST NODES BEING COMPARED AGAINS
                                N[lightestIndex].FROM = largest + 1;
                                N[lightestIndex].TO = largest+ 1;
                                N[lightestIndex].WEIGHT = largest+ 1;
                                count++;
						}



	}

	int totalEdge = 0, totalLength = 0;

			numberOfEntry = count;
			sort(numberOfEntry, 2);


				string filename = "diagram before delete";
				//remove first entry of MST struct data due to deleted node
				if(signal == "this is a deleting signal")
				{
					for(int i = 0; i < numberOfEntry; i++)
					{
						N[i].MST_FROM = N[i+1].MST_FROM;
						N[i].MST_TO = N[i+1].MST_TO;
						N[i].MST_WEIGHT = N[i+1].MST_WEIGHT;
					}
					count = count - 1;

					//change file name if deletion was performed, this is to for better demonstration if to compare image side by side
					filename = "diagram after delete";
				}

            //WRITE MST NODES TO A FILE
            //SO graphviz CAN OPEN THE FILE AND USE THE MST NODES TO CREATE A GRAPH
			ofstream outfile;
			string filenamedot = filename + ".dot";
			outfile.open(filenamedot.c_str());

			outfile << "graph {" << endl;

			cout << "\nMinimum Spanning Tree" << endl;
			for(int i = 0; i < count; i++)
			{
				cout << "Node " << i + 1 << ")  ";
				cout << N[i].MST_FROM << " -> " << N[i].MST_TO << " : " << N[i].MST_WEIGHT << endl;

				//graphviz required input format
				outfile << N[i].MST_FROM << " -- " << N[i].MST_TO << " [label=\"" << N[i].MST_WEIGHT << "\"];" << endl;

				totalLength += N[i].MST_WEIGHT;

			}

			outfile << "}" << endl;
			outfile.close();

			cout << "\nTotal Edge   : " << count << endl;
			cout << "Total Length : " << totalLength << endl;

			string command = "dot -Tpng \"" + filename + ".dot\" -o \"" + filename + ".png\"";
			string openImageCommand = "eog \"" + filename + ".png\"";

			system (command.c_str());
			system (openImageCommand.c_str());

}


int randomEdge(int numberOfEntry)
{

	//random a number
	int maxNode = numberOfEntry - 1;
	srand (time(NULL));
	int randomIndex = rand() % maxNode + 1; //if there are 5 nodes, it will pick an index from 1 to 5, then in main.cpp, show the index's information
	int from, to, weight;
	dummydata = randomIndex;
	from = backupNodes[randomIndex].FROM;
	to = backupNodes[randomIndex].TO;
	weight = backupNodes[randomIndex].WEIGHT;
	dummyFROM = from;
	dummyTO = to;
	dummyWEIGHT = weight;


        cout << "Information of the randomly deleted edge : " << backupNodes[randomIndex].FROM << " -> " << backupNodes[randomIndex].TO << " : " << backupNodes[randomIndex].WEIGHT << endl;
        cout << endl;
     cout << "Before delete" << endl;
     for(int i = 0; i < numberOfEntry - 1; i++)
     {
     	cout << "Node " << i + 1 << ")  ";
     	cout << backupNodes[i].FROM << " -> " << backupNodes[i].TO << " : " << backupNodes[i].WEIGHT;
     	if(randomIndex == i)
     	{
     		cout << "*<--this is going to be deleted";
     	}

     		cout << endl;
     }
     //this function will also perform deletion of the edge(copy next index to current index)
     for(int i = randomIndex; i < numberOfEntry - 1; i++) // -1 to skip 000 entry
     {
     	//start at the random index
     	backupNodes[i].FROM = backupNodes[i+1].FROM; // assign next index to current index
     	backupNodes[i].TO = backupNodes[i+1].TO;
     	backupNodes[i].WEIGHT = backupNodes[i+1].WEIGHT;

     }




	return randomIndex;
}