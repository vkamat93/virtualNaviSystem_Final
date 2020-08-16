/*
 * CRoute.h
 *
 *  Created on: 07-Nov-2015
 *      Author: VIKRANT
 */

#ifndef CROUTE_H_
#define CROUTE_H_

#include "CPOIDatabase.h"
#include "CWpDatabase.h"
#include<list>

/*This class does the job of linking the POI database, adding Waypoints and POIs,
 * printing them, calculating the closest POI and its distance from current location and
 * logic for error messages in this Navigation System*/
class CRoute
{
private:
std::list<CWaypoint*> myRoute;

/*pointer variable of type CPOIDatabase*/
CPOIDatabase* m_pPoiDatabase;

/*pointer variable of type CWpDatabase*/
CWpDatabase* m_pWpDatabase;

/*To keep the count of POIs to check whether POI exist in route*/
int countOfPois;

public:
/**
 *Constructor used to initialize the database pointers to NULL
 */
 CRoute();

/**
 * Operator overloading of = for assigning one route to the other
 * @param oldRoute as reference type object of CRoute
 * @return CRoute& because for return we need actual value of object not a copy
 **/
CRoute& operator=(const CRoute& oldRoute);

/*Copy constructor*/
CRoute(CRoute const& origin);

/**
 *Connects with the POI database
 *@param pPoiDB is pointer of type CPOIDatabase which stores address of our POI database
 *@return returns void
 **/
	void connectToPoiDatabase(CPOIDatabase* pPoiDB);

/**
 *Connects with the Waypoint database
 *@param pWpDB is pointer of type WpDatabase which stores address of our WP database
 *@return returns void
 **/
	void connectToWpDatabase(CWpDatabase* pWpDB);

/**
 *
 */
	void addWaypoint(string name);

/**
 *
 */
	void addPoi(string namePoi, string nameWp);

/**
 *Prints the waypoints and POIs in our route by dynamic casting
 *@return returns void */
	void print();

/**Appends a POI or Waypoint or both to the end of our route
 * @param name of the POI or Waypoint which is to be added to the end of the route
 * @return object of type CRoute
 */
CRoute operator+=(string name);

/**
 * The function adds two routes if they are connected to same POI and WP databases
 * @param object of the second route of type CRoute passed by reference
 * @return object of type CRoute
 */
CRoute operator+(const CRoute& r2);

/**Returns the shortest distance from current position to any POI in route and POI details
 *@param object of CWaypoint type for current position and POI type for the POI
 *@return shortest distance value in double
 */
double getDistanceNextPoi(CWaypoint const& wp, CPOI& poi);

/*Destructor*/
~CRoute();
};


#endif /* CROUTE_H_ */
