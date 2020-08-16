/*
 * CFileHandling.cpp
 *
 *  Created on: 07-Dec-2015
 *      Author: VIKRANT
 */

#include "CFileHandling.h"
#include <fstream>
#include <string>
#include <stdlib.h>  //for using atof
#include <typeinfo>
using namespace std;

void CFileHandling::setMediaName(string name)
{
	wpMediaName=name+"-wp.txt";
	poiMediaName=name+"-poi.txt";
}

bool CFileHandling::writeData(const CWpDatabase& waypointDb,const CPOIDatabase& poiDb)
{
	/*Calling the functions already defined in the CWpdatabase and CPOIDatabase class
	 * with the  specific database txt file name passed as parameter for Waypoint and
	 * CPOI respectively*/
	return true;
}

bool CFileHandling::readData(CWpDatabase& waypointDb, CPOIDatabase& poiDb,MergeMode mode)
{
/*********For Waypoint****************/

	//wpstrfull to get the entire line from file,wpstrcut to get the various fields
	string wpstrfull, wpstrcut;
	ifstream wpfin;
	double wplat, wplong;
	wpfin.open(wpMediaName.c_str(), ios::in); //c_str() converts string to character
	wpfin.seekg(0);  //Sets the pos of the next character to be extracted from the input stream.

	int wpfieldcount;  //To count the delimiters to check the number of fields
	int wplinenumber=0; //to keep track of line number for printing in error msg

	string wpstrarray[3]; //since we have three fields in waypoint
	if (mode == REPLACE)
	{
		waypointDb.clearWpMap();
	}
	while (!wpfin.eof())
	{
		getline(wpfin, wpstrfull); //gets the entire line by line from the specified file
		wplinenumber++;

		//To store the full string to display in error msg and to count the size of entry
		string wptempstr=wpstrfull;

	for (unsigned int i = 0; i < 3; i++)  //to check number of semicolons
	{
		/*using find_first_of() for taking both ; and , as delimiter*/
		unsigned int pos = wpstrfull.find_first_of(";,");

		/*npos is for garbage/invalid value when it can't find the given delimiters*/
		if (pos != string::npos)
		{
			wpfieldcount = i; //setting the count equal to number of delimiters

			wpstrcut = wpstrfull.substr(0, pos);
			wpstrfull.erase(0, wpstrcut.size() + 1);
			wpstrarray[i] = wpstrcut;
		}
		else
		{
			//for the last field which ends without a delimiter
			wpstrarray[i] = wpstrfull;
		}
	}

/*atof() converts string to float and returns value if successful else return 0*/
	wplat = atof(wpstrarray[1].c_str());
	wplong = atof(wpstrarray[2].c_str());

	CWaypoint wp(wpstrarray[0], wplat, wplong);

/*To add to Waypoint database and checking for the error conditions*/
		if (wptempstr.size() == 0)
		{
			cout << "Error: Blank entry in database in line number " << wplinenumber
					<< endl;
		}
		else
		{
			if (wpfieldcount == 1) //Correct format with three fields
			{
				if (wplat != 0 && wplong != 0)
				{
					waypointDb.addWaypoint(wp);
				}
				else
				{
					cout << "Error: Invalid coordinates in line number "
							<< wplinenumber << " : " << wptempstr << endl;
				}
			}
			else if (wpfieldcount < 1)
			{
				cout << "Error: Too less fields in line number " << wplinenumber
						<< " : " << wptempstr << endl;
			}
			else
			{
				cout << "Error: Too many fields in line number " << wplinenumber
						<< " : " << wptempstr << endl;
			}
		}

	}
	wpfin.close();

/********For POI****************/

	//poistrfull to get the entire line,poistrcut to get the various fields
	string poistrfull, poistrcut;
	ifstream poifin;
	double poilat, poilong;
	poifin.open(poiMediaName.c_str(), ios::in); //c_str() converts string to character
	poifin.seekg(0);  //Sets the position of the next character to be extracted from the input stream.

	int poifieldcount; //To count the delimiters to check the number of fields
	int poilinenumber=0;  //to keep track of line number for printing in error msg

	string poistrarray[5]; //since we have five fields in POI
	if (mode == REPLACE)
	{
		poiDb.clearPoiMap();
	}
	while (!poifin.eof())
	{
		getline(poifin, poistrfull); //gets the entire line by line from the specified file
		poilinenumber++;

		//To store the full string to display in error msg and to count the size of entry
		string poitempstr=poistrfull;

for (unsigned int i = 0; i < 5; i++)  //to check number of semicolons
	{
/*using find_first_of() for taking both ; and , as delimiter*/
		unsigned int pos = poistrfull.find_first_of(";,");

/*npos is a word for garbage/invalid value when it cant find the given character*/
			if (pos != string::npos)
			{
				poifieldcount=i; //setting the count equal to number of delimiters
				poistrcut = poistrfull.substr(0, pos);
				poistrfull.erase(0, poistrcut.size() + 1);
				poistrarray[i] = poistrcut;
			}
			else
			{
				//for the last field which ends without a delimiter
				poistrarray[i] = poistrfull;
			}
		}

/*atof() converts string to float and returns value if successful else return 0*/
		poilat = atof(poistrarray[3].c_str());
		poilong = atof(poistrarray[4].c_str());

		t_poi t;
		if (poistrarray[0] == "RESTAURANT")
		{
			t = RESTAURANT;
		}
		else if (poistrarray[0] == "SIGHTSEEING")
		{
			t = SIGHTSEEING;
		}
		else if (poistrarray[0] == "SHOPPING")
		{
			t = SHOPPING;
		}

		CPOI poi(t, poistrarray[1], poistrarray[2], poilat, poilong);

/*To add to Poi database and checking for the error conditions*/
		if (poitempstr.size() == 0)
		{
			cout << "Error: Blank entry in database in line number "
					<< wplinenumber << endl;
		}
		else
		{
			if (poifieldcount == 3)
			{
				if (poilat != 0 && poilong != 0)
				{
					poiDb.addPoi(poi);
				}
				else
				{
					cout << "Error: Invalid coordinates in line number "
							<< poilinenumber << " : " << poitempstr << endl;
				}
			}
			else if (poifieldcount < 3)
			{
				cout << "Error: Too less fields in line number "
						<< poilinenumber << " : " << poitempstr << endl;
			}
			else
			{
				cout << "Error: Too many fields in line number "
						<< poilinenumber << " : " << poitempstr << endl;
			}

		}
	}
	poifin.close();
	return true;
}
