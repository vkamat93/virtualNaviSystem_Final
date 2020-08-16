/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWPDATABASE.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CWPDATABASE_H
#define CWPDATABASE_H
#include "CWaypoint.h"
#include "TemplateDB.h"
#include<map>

class CWpDatabase : public TemplateDB<string,CWaypoint>
{
private:

	std::map<string,CWaypoint> WpMap;

public:
/*Default Constructor
 *@return no return type in Constructor */
    CWpDatabase();

/*This function adds the Waypoints to the database one by one
 *@param poi is the object passed by reference so that all object is stored in the DB map
 *@return returns void*/
    void addWaypoint(CWaypoint const& wp);

/*This function is used to check whether desired POI in route exists in the Database
 *@param name to get a name of the POI which is to be checked for existence in Database
 *@return returns a pointer of type CWaypoint*/
    CWaypoint* getPointerToWaypoint(string name);

/*
 * This function clears the Waypoint Map which is then used for the REPLACE case in ReadFile
 * @return void
 **/
    void clearWpMap();

/**This function prints the waypoint database for testing purposes
 *@return void
 **/
    void print();

/**
 * This function returns the copy of the WpMap to the child class of CPersistentStorage
 * for implementing the write to file function
 * @return map<string,CWaypoint>
 */
  const map<string,CWaypoint> getWpMap()const;
};
/********************
**  CLASS END
*********************/
#endif /* CWPDATABASE_H */
