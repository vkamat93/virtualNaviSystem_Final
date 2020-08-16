/*
 * CNavigationSystem.cpp
 *
 *  Created on: 10-Nov-2015
 *      Author: VIKRANT
 */

#include<iostream>
using namespace std;

#include "CNavigationSystem.h"

CNavigationSystem::CNavigationSystem()
{
	//Connect poi database to Navigation system
    //m_route.connectToPoiDatabase(&m_PoiDatabase);

	//Connect waypoint database
	//m_route.connectToWpDatabase(&m_WpDatabase);

	/*adding elements to the Poi Database manually*/
//	m_PoiDatabase.addPoi(CPOI(RESTAURANT,"mensa HDA","Best mensa in the world",10,20));
//	m_PoiDatabase.addPoi(CPOI(SHOPPING,"growel","Best mall in the world",19,18));
//	m_PoiDatabase.addPoi(CPOI(RESTAURANT,"sitte","More expensive but also good",11,22));
//	m_PoiDatabase.addPoi(CPOI(SIGHTSEEING,"raigad","Best fort in the world",13,30));
//	m_PoiDatabase.addPoi(CPOI(SIGHTSEEING,"juhu","Best seaface location",33,30));
//	m_PoiDatabase.addPoi(CPOI(SIGHTSEEING, "mumbai", "Best Place ever", 23,56));

	/*Adding elements to Waypoint database manually*/
//	m_WpDatabase.addWaypoint(CWaypoint("berlin", 52.5166, 13.4));
//	m_WpDatabase.addWaypoint(CWaypoint("amsterdam", 52.3667, 4.9000));
//    m_WpDatabase.addWaypoint(CWaypoint("darmstadt", 49.8667, 8.6500));
//	m_WpDatabase.addWaypoint(CWaypoint("tokio", 35.6833, 139.6833));
//	m_WpDatabase.addWaypoint(CWaypoint("mumbai", 43, 56));

	/*To test the CFileHandling write*/
//	m_filehandle.setMediaName("DatabaseFile");
//	if(m_filehandle.writeData(m_WpDatabase,m_PoiDatabase)==true)
//	{
//		cout<<"Write successful"<<endl;
//	}
//	else
//	{
//		cout<<"Write failed!"<<endl;
//	}

	/*Testcase for read from database*/
//	m_filehandle.setMediaName("DatabaseFile");
//	m_filehandle.readData(m_WpDatabase,m_PoiDatabase,CPersistentStorage::MERGE);

}

void CNavigationSystem::enterRoute()
{

/*creating and adding Waypoints on our route*/
//		m_route.addWaypoint("barcelona");
//		m_route.addWaypoint("prague");
//		m_route.addWaypoint("rome");
//		m_route.addWaypoint("berlin");

/*adding points of interest on the route*/
//		m_route.addPoi("subway","rome");
//		m_route.addPoi("frankenstein","barcelona");
//		m_route.addPoi("infinity", "prague");
//		m_route.addPoi("mensa HDA", "berlin");
//		m_route.addPoi("growel","barcelona");


/*Testing the overloaded += operator*/
      //m_route+="mensa HDA";

/*To test copy constructor and overloaded = operator*/
//  CRoute cr1(m_route);
//	CRoute cr1=m_route;
//	cr1.addPoi("Juhu","amsterdam");


/*To test if the route adds from the database file created*/
//   m_route.connectToWpDatabase(&m_WpDatabase);
//   m_route.addWaypoint("barcelona");
//   m_route.addWaypoint("prague");
//   m_route.addWaypoint("rome");

/*To test the concatenating of two routes*/
//	CWpDatabase cwpd;
//	cwpd.addWaypoint(CWaypoint("Tokio", 35.6833, 139.6833));
//	cwpd.addWaypoint(CWaypoint("amsterdam",3, 4.9000));
//	cwpd.addWaypoint(CWaypoint("darmstadt", 4, 8));
//
//	CRoute cr2;
//	cr2.connectToWpDatabase(&cwpd);
//	cr2.connectToPoiDatabase(&m_PoiDatabase);
//	cr2.addWaypoint("amsterdam");
//	cr2.addWaypoint("darmstadt");
//	cr2.addPoi("HDA","darmstadt");
//

	CJsonPersistence cjp;
	cjp.setMediaName("databasefile");
//	cjp.writeData(m_WpDatabase,m_PoiDatabase);
	cjp.readData(m_WpDatabase,m_PoiDatabase,CPersistentStorage::MERGE);

}

void CNavigationSystem::printRoute()
{
/*Calls the print function with object of CRoute*/
	//m_route.print();

/*Calls the print function of the databases for checking if the database has been updated
 * after the readData function*/
//	m_WpDatabase.print();
//	m_PoiDatabase.print();

/*Testing the copy constructor and = operator*/
//	cr1.print();

/*Testing the concatenating of two routes*/
//	(m_route+cr2).print();
}

void CNavigationSystem::printDistanceCurPosNext()
{
/*Creating object of CGPSSensor*/
	CGPSSensor gps;

/*Details of position got through using the object of CWaypoint*/
	CWaypoint wp=gps.getCurrentPosition();

/*Creating an object of CPOI*/
	CPOI poi;

/*Check to determine whether indeed POI present on the route defined,using the dummy value
 * returned in getDistanceNextPoi as control check, if yes then print the shortest
 * distance and that particular POI details if no POI is found then distance is
 * not calculated and error message is printed */
	if(m_route.getDistanceNextPoi(wp,poi)!=-1.0)
	{
	cout<<"Distance to next POI: "<<m_route.getDistanceNextPoi(wp,poi)<<endl;
	poi.print(MMSS);
	}
	else
	{
		cout<<"Error: No POI found on your route"<<endl;
	}

}

void CNavigationSystem::run()
{
/*Calling the private functions from within run()*/
 enterRoute();
 printRoute();
 //printDistanceCurPosNext();
}



