/*
 * CRoute.cpp0
 *
 *  Created on: 07-Nov-2015
 *      Author: VIKRANT
 */

#include "CRoute.h"
#include <iostream>
#include "CWpDatabase.h"
using namespace std;

CRoute::CRoute()
{
/*Initially it must contain no address so that it will later get address of object
*passed for connecting Database*/
	m_pPoiDatabase = NULL;
	m_pWpDatabase = NULL;

/*To initialize the count of POIs in our route to zero*/
	countOfPois=0;
}

CRoute& CRoute::operator=(const CRoute& oldRoute)
{
	this->myRoute=oldRoute.myRoute;
	this->m_pPoiDatabase=oldRoute.m_pPoiDatabase;
	this->m_pWpDatabase=oldRoute.m_pWpDatabase;
	return *this;
}

CRoute::CRoute(CRoute const& origin)
{
	//using the overloaded = operator as defined before
	*this=origin;
}

void CRoute::connectToPoiDatabase(CPOIDatabase* pPoiDB = NULL)
{
/*here we want the address of the database so in CNavigationSystem we have object of
 * database and &object gives address of 'real database' which is then
 * assigned to m_pPoiDatabase*/

/*pass address of object of database to the the database pointer present here in
* CRoute but currently not pointing anywhere,ie,NULL pointer*/
	m_pPoiDatabase = pPoiDB;
}

void CRoute::connectToWpDatabase(CWpDatabase* pWpDB = NULL)
{
/*here we want the address of the database so in CNavigationSystem we have object of
 * database and &object gives address of 'real database' which is then
 * assigned to m_pPoiDatabase*/

/*pass address of object of database to the the database pointer present here in
* CRoute but currently not pointing anywhere,ie,NULL pointer*/
	m_pWpDatabase = pWpDB;
}

void CRoute::addWaypoint(string name)
{
/*To check if m_pPoiDatabase holds address of the database,i.e database connected*/
	if (m_pWpDatabase != NULL)
	{
		if (m_pWpDatabase->getPointerToWaypoint(name) != NULL)
		{
			//To check if the last element in the route is the same Waypoint
			//listName.back() gives the last element in the list
			if (m_pWpDatabase->getPointerToWaypoint(name) != myRoute.back())
			{
				myRoute.push_back(m_pWpDatabase->getPointerToWaypoint(name));
			}
			else
			{
				cout << name << " cannot be added immediately after the same Waypoint"
						<< endl;
			}
		}
		else
		{
			cout << "ERROR: COULD NOT FIND WAYPOINT IN THE WAYPOINT DATABASE"
					<< endl;
		}
	}
	else
	{
		cout<<"ERROR: WAYPOINT DATABASE NOT CONNECTED"<<endl;
	}
}

void CRoute::addPoi(string namePoi, string afterWp)
{
	int checkForWpInRoute = 0; //flag to check if there is 'afterWp' Waypoint in route
	if (m_pPoiDatabase != NULL)
	{
		if (myRoute.size() == 0)
		{
			cout << "ERROR: YOUR ROUTE IS EMPTY, THUS POI CAN'T BE ADDED" << endl;
		}
	    else if (m_pPoiDatabase->getPointerToPoi(namePoi) != NULL)
		{
			if (m_pWpDatabase->getPointerToWaypoint(afterWp) != NULL)
			{
				std::list<CWaypoint*>::iterator itemp;
				for (std::list<CWaypoint*>::iterator itr = myRoute.begin();
						itr != myRoute.end(); ++itr)
				{
					//done to avoid adding POI after POI with a Waypoint name
					//Using RTTI to detect type of object at runtime dynamically
					CPOI* temp = dynamic_cast<CPOI*>(*itr);
					if (temp == NULL) //then it is a waypoint
					{
						if ((*itr)->getName() == afterWp)
						{
							itemp = itr;
							checkForWpInRoute = 1; //'afterWp' Waypoint found
						}
					}
				}
				if(checkForWpInRoute==1)
				{
					myRoute.insert(++itemp,m_pPoiDatabase->getPointerToPoi(namePoi));
					countOfPois++; //there is a POI in route
				}
				else
				{
					cout<<"ERROR: SPECIFIED WAYPOINT NOT FOUND IN YOUR ROUTE"<<endl;
				}
			}
		}
	}
	else
	{
		cout << "ËRROR: POI DATABASE NOT CONNECTED" << endl;
	}
}

double CRoute::getDistanceNextPoi(CWaypoint const& wp, CPOI& poi)
{
	/*If condition to check whether there are POIs specified on the route*/
	if(countOfPois!=0)
	{
	/*CPOI inherits CWaypoint so all its functions too and thus
	 * we use this function to calculate distance*/
		double smallestDist;
		int flag=0; //to catch occurence of first POI
		for (std::list<CWaypoint*>::iterator itr1 = myRoute.begin();
				itr1 != myRoute.end(); ++itr1)
		{
			//Using RTTI to detect type of object at runtime dynamically
			CPOI* temp1 = dynamic_cast<CPOI*>(*itr1);
			//object of type CPOI and no CPOI caught before
			if (temp1 != NULL && flag == 0)
			{
				smallestDist = temp1->calculateDistance(wp);
				poi = (*temp1);
				flag++; //first POI caught,now to go further without looping again
			}
		}

		for (std::list<CWaypoint*>::iterator itr = myRoute.begin();
				itr != myRoute.end(); ++itr)
		{
			//Using RTTI to detect type of object at runtime dynamically
			CPOI* temp = dynamic_cast<CPOI*>(*itr);
			if (temp != NULL) //object is of type CPOI
			{
				if (smallestDist > (temp)->calculateDistance(wp))
				{
					smallestDist = (temp)->calculateDistance(wp);
					poi = (*temp);  //to get the details of the nearest POI
				}
			}
		}
	return smallestDist;
	}
	/*If there is no POI specified on route return a dummy value in control logic
	 * used later for printing a error message in Distance calculation */
	else
	{
		return -1.0;
	}
}

void CRoute::print()
{
	cout<<"//*********************ROUTE************************//"<<endl;
	std::list<CWaypoint*>::iterator itemp;
	for(std::list<CWaypoint*>::iterator itr=myRoute.begin(); itr!=myRoute.end(); ++itr)
	{

/*If no dynamic cast used then cout<<(**i) will invoke the print routine of only CWaypoint
 * since it can't differentiate between the object types at runtime*/

/*itr now searches for CPOI type pointers dynamically at runtime done to avoid adding
 * poi after a poi with a Waypoint name*/
		CPOI* temp=dynamic_cast<CPOI*>(*itr);
		if(temp==NULL) //means it is of type CWaypoint
		{
			//itr is pointing to pointer thus the double pointer
			//now it prints Waypoints
		    cout<<(**itr);
		}
		else
		{
			//temp is already pointer pointing to object of CPOI
			//prints CPOIS
			cout<<*temp;
		}
		/*print is virtual, so the compiler prints the WP and POIS in their own individual formats*/
		//(*itr)->print(2);
	}

}

CRoute CRoute::operator +=(string name)
{
	this->addWaypoint(name);

		if(m_pWpDatabase->getPointerToWaypoint(name)!=NULL)
			{
		     this->addPoi(name,name);
			}
		else if(m_pPoiDatabase->getPointerToPoi(name)!=NULL)
		    {
			//To check if the last element in the route is the same POI
			if(m_pPoiDatabase->getPointerToPoi(name)!=*--myRoute.end())
			{
			myRoute.push_back(m_pPoiDatabase->getPointerToPoi(name));
		    }
			else
			{
				cout<<name<<" cannot be added immediately after the same Waypoint"<<endl;
			}
		    }
	return *this;
}

CRoute CRoute::operator +(const CRoute& r2)
{
	//Checking if both routes are connected to same database for POI and Waypoints
	if(this->m_pPoiDatabase==r2.m_pPoiDatabase && this->m_pWpDatabase==r2.m_pWpDatabase)
	{
		this->myRoute.insert(this->myRoute.end(), r2.myRoute.begin(), r2.myRoute.end());
	}
	else
	{
		cout<<"ERROR:Both routes not connected to the same databases"<<endl;
		this->myRoute.clear();
	}
	return *this;
}

/*Unused destructor*/
CRoute::~CRoute()
{

}
