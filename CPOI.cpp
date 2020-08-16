#include "CPOI.h"
#include "CWaypoint.h"
#include "CGPSSensor.h"
/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.CPP
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

//System Include Files

//Own Include Files
//Method Implementations

void CPOI::print(int format)
{
/*value of the object is got by *this, thus overloaded << does the functionality which u
 * have of the POI print*/
cout<<*this;
}

CPOI::CPOI(t_poi type, string name, string description, double latitude,
		double longitude)
{
	m_type = type;
	m_description = description;
	m_name = name;
	m_latitude = latitude;
	m_longitude = longitude;

}

void CPOI::getAllDataByReference(string& name, double& latitude,
		double& longitude, t_poi& type, string& description) const
{
	name = m_name;
	latitude = m_latitude;
	longitude = m_longitude;
	type = m_type;
	description = m_description;
}

ostream& operator<<(ostream& out, const CPOI& cpoi)
{
	out << "Point of Interest" << endl << "==============" << endl;

	/*To get appropriate statement depending on the enum type of POI*/
		switch (cpoi.m_type)
		{
		case RESTAURANT:
			out << "of type Restaurant : " << cpoi.m_description << endl;
			break;

		case SIGHTSEEING:
			out << "of type Sightseeing : " << cpoi.m_description << endl;
			break;

		case SHOPPING:
			out << "of type Shopping: " << cpoi.m_description << endl;
			break;

		default:
			out << "NO such type found" << endl;
		};

		int degLat, minLat, degLon, minLon;
		double secLat, secLon;

	//calling the transformation functions
	cpoi.transformLatitude2degmmss(degLat, minLat, secLat);
	cpoi.transformLongitude2degmmss(degLon, minLon, secLon);

	out<<cpoi.getName()<<" on latitude = "<<degLat<<"deg "<<minLat<<"min "<<secLat<<"s ";
	out<<"and on longitude = "<<degLon<<"deg "<<minLon<<"min "<<secLon<<"sec"<<endl;

return out;
}
