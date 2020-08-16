#include "CWpDatabase.h"
#include "CWaypoint.h"
#include <fstream>

//System Include Files


//Own Include Files

//Method Implementations

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWPDATABASE.CPP
* Author          :
* Description     :
*
*
****************************************************************************/
CWpDatabase::CWpDatabase()
{

}


void CWpDatabase::addWaypoint(CWaypoint const& wp)
{
	/*Inserts the Waypoint object in the map with name as key and object as value*/
//	WpMap.insert(std::make_pair(wp.getName(),wp));
	addWpOrPoi(wp);

}

CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	CWaypoint* pointerToWaypoint = NULL; //set pointer to NULL before scanning database
//
//	std::map<string,CWaypoint>::iterator it;
//	for(it=WpMap.begin(); it!=WpMap.end(); ++it)
//		{
//		//checks if the key is the name passed, only then returns the object for that key
//			if(it->first==name)
//			{
//				pointerToWaypoint=&it->second;
//			}
//		}

	getPointerToWpOrPoi(name);
	return pointerToWaypoint; //returns NULL pointer if no match


}

void CWpDatabase::clearWpMap()
{
	//WpMap.clear();
	clearMap();
}

void CWpDatabase::print()
{
//	std::map<string,CWaypoint>::iterator it;
//	for(it=WpMap.begin(); it!=WpMap.end(); ++it)
//	{
//		it->second.print(MMSS);
//	}
	printWpOrPoi();

}

const map<string, CWaypoint> CWpDatabase::getWpMap() const
{
	//return &WpMap;
	return getMap();
}
