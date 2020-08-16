#include "CPOIDatabase.h"
#include "CPOI.h"
#include<iostream>
using namespace std;

#include<fstream>

/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOIDATABASE.CPP
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

//System Include Files

//Own Include Files
//Method Implementations
CPOIDatabase::CPOIDatabase()
{

}

void CPOIDatabase::addPoi(CPOI const& poi)
{
	//poiMap.insert(std::make_pair(poi.getName(),poi));
	addWpOrPoi(poi);
}

CPOI* CPOIDatabase::getPointerToPoi(string name)
{
CPOI* pointerToPoi = NULL; //set pointer to NULL before scanning the database
//
////search for the find() function to replace for loop in map exclusive!!!!!! IMP...
//
//	std::map<string,CPOI>::iterator it;
//	for(it=poiMap.begin(); it!=poiMap.end(); ++it)
//	{
//		if(it->first==name)
//		{
//			pointerToPoi=&it->second;
//		}
//	}
//	if (pointerToPoi == NULL)
//	{
//		cout << "ERROR: COULD NOT FIND POI IN THE POI DATABASE" << endl;
//	}

getPointerToWpOrPoi(name);
return pointerToPoi; //returns NULL pointer if no match


}

void CPOIDatabase::print()
{
//	std::map<string,CPOI>::iterator it;
//	for(it=poiMap.begin(); it!=poiMap.end(); ++it)
//	{
//		it->second.print(MMSS);
//	}
	printWpOrPoi();

}

void CPOIDatabase::clearPoiMap()
{
//poiMap.clear();
   clearMap();
}

const map<string, CPOI> CPOIDatabase::getPoiMap() const
{
	//return &poiMap;
	return getMap();
}
