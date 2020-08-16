/*
 * CWaypoint.cpp
 *
 *  Created on: 01-Nov-2015
 *      Author: VIKRANT
 */

#include<math.h>
#include<iostream>
using namespace std;
#include "CWaypoint.h"

#define PI 3.141592 //used for calculation in acos, cos, sin functions


CWaypoint::CWaypoint(string name, double latitude, double longitude)
{

/*printed if SHOWADDRESS is defined using #define*/
#ifdef SHOWADDRESS
	cout<<"Constructor"<<endl<<"=========="<<endl;
	cout<<"Object created at "<<this<<endl;
	cout<<"Address of m_name : "<<&m_name<<endl;
	cout<<"Address of m_latitude : "<<&m_latitude<<endl;
	cout<<"Address of m_longitude : "<<&m_longitude<<endl;
	cout<<"Data occupied by m_name : "<<sizeof(m_name)<<" bytes"<<endl;
	cout<<"Data occupied by m_latitude : "<<sizeof(m_latitude)<<" bytes"<<endl;
	cout<<"Data occupied by m_longitude : "<<sizeof(m_longitude)<<" bytes"<<endl;
#endif

/*Calling set function from inside constructor for invocation at runtime*/
	set(name, latitude, longitude);
}

void CWaypoint::set(string name, double latitude, double longitude)
{
	m_name=name;

	//Checking validity of latitude
	if (latitude>= -90 && latitude<= 90)
	{
		m_latitude=latitude;
	}
	else
	{
		m_latitude=0;
	}

	//Checking validity of latitude
	if (longitude>= -180 && longitude<= 180)
	{
		m_longitude=longitude;
	}
	else
	{
		m_longitude=0;
	}

}

string CWaypoint::getName()const
{
	return m_name;
}

double CWaypoint::getLatitude() const
{
	return m_latitude;
}

double CWaypoint::getLongitude() const
{
	return m_longitude;
}

void CWaypoint::print(int format)
{
	if(format==1)
	{
		cout<<"Print method"<<endl<<"============"<<endl;
		cout<<getName()<<" on latitude = "<<getLatitude()<<" and longitude = "
					<<getLongitude()<<endl;
	}

	if(format==2)
	{
		//declaring local variables of the function
		int degLat, minLat, degLon, minLon;
		double secLat, secLon;

		//calling the transformation functions
		transformLatitude2degmmss(degLat, minLat, secLat);
		transformLongitude2degmmss(degLon, minLon, secLon);

		cout<<getName()<<" on latitude = "<<degLat<<"deg "<<minLat<<"min "<<secLat<<"s ";
		cout<<"and on longitude = "<<degLon<<"deg "<<minLon<<"min "<<secLon<<"sec"<<endl;
	}

}

void CWaypoint::transformLongitude2degmmss(int& deg, int& mm, double& ss) const
{
    //deg stores only the int part of m_latitude
	deg=m_longitude;

    //mm keeps only the int value and value after float used for ss calculation
    mm= (m_longitude - deg)*60;

    //typecasting used since the actual float value of mm,used for calculation of ss
    ss= 3600*((m_longitude - deg)-(float)mm/60);

}

void CWaypoint::transformLatitude2degmmss(int& deg, int& mm, double& ss) const
{
	//deg stores only the int part of m_longitude
	deg= m_latitude;

    //mm keeps only the int value and value after float used for ss calculation
    mm= (m_latitude - deg)*60;

    //typecasting used since the actual value of mm, used for calculation of ss
    ss= 3600*((m_latitude - deg)-(float)mm/60);

}

void CWaypoint::getAllDataByReference(string& name, double& latitude, double& longitude) const
{
   //the value gets assigned to the address of the passed parameters
   name=getName();
   latitude=getLatitude();
   longitude=getLongitude();

/*Commenting this since it will be printed when we use this function in the write to file
 * for the persistence problem statement
 *cout<<name<<" on latitude = "<<latitude<<" and longitude ="<<longitude<<endl;
 */
}

double CWaypoint::calculateDistance(const CWaypoint& wp)
{
	double dist;

	/*multiply the sin and cos parameters by PI/180 to convert from degree to radians
	 * because sin and cos take only radians value as parameters*/

	dist = 6378*(acos((sin(m_latitude*PI/180)*sin(wp.m_latitude*PI/180))
			           +(cos(m_latitude*PI/180)*cos(wp.m_latitude*PI/180)
					      *cos(wp.m_longitude*PI/180 - m_longitude*PI/180))));
	return dist;
}

ostream& operator<<(ostream& out, const CWaypoint& cwp)
{
	int degLat, minLat, degLon, minLon;
	double secLat, secLon;

	//calling the transformation functions
	cwp.transformLatitude2degmmss(degLat, minLat, secLat);
	cwp.transformLongitude2degmmss(degLon, minLon, secLon);

	out<<cwp.getName()<<" on latitude = "<<degLat<<"deg "<<minLat<<"min "<<secLat<<"s ";
	out<<"and on longitude = "<<degLon<<"deg "<<minLon<<"min "<<secLon<<"sec"<<endl;

return out;
}

/*Unused destructor*/
CWaypoint::~CWaypoint()
{

}
