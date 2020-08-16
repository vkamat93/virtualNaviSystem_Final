/*
 * CNavigationSystem.h
 *
 *  Created on: 10-Nov-2015
 *      Author: VIKRANT
 */

#ifndef CNAVIGATIONSYSTEM_H_
#define CNAVIGATIONSYSTEM_H_

#include "CWaypoint.h"
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPOIDatabase.h"
#include "CWpDatabase.h"
#include "CGPSSensor.h"
#include "CFileHandling.h"
#include "TemplateDB.h"
#include "CJsonPersistence.h"

/*This class is used to implement all the functions defined in previous classes as well
 * as to test all the testcases associated with the exercise*/
class CNavigationSystem
{
private:
	CRoute m_route;
	CPOIDatabase m_PoiDatabase;
	CWpDatabase m_WpDatabase;
	CGPSSensor m_GPSSensor;
//	CFileHandling m_filehandle;

/*private method called from run()
 *this function is used to set our Route by entering the desired Waypoints and POIs
 *@return returns void*/
	void enterRoute();

/*private method called from run()
 *this function is used to print Route by displaying the set Waypoints and POIs
 *@return returns void*/
	void printRoute();

/*private method called from run()
 *used to print the nearest POI and the distance till the same from our current position
 *@return returns void*/
	void printDistanceCurPosNext();

public:
/*Default constructor used to call constructor of Croute*/
	CNavigationSystem();

/*Calls the private functions of this class
 *@return returns void */
	void run();
};

#endif /* CNAVIGATIONSYSTEM_H_ */
