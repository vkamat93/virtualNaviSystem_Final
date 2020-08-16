/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.H
 * Author          :
 * Description     :
 *
 *
 ****************************************************************************/

#ifndef CPOI_H
#define CPOI_H

#include<iostream>
using namespace std;
#include "CWaypoint.h" //else inheritance error: expected class-name before '{' token

enum t_poi
{
	RESTAURANT, SIGHTSEEING, SHOPPING,
};

//This class is used for creating Points of Interest to be used in the Route
class CPOI: public CWaypoint //inheriting public and protected members of CWaypoint
{
private:
	t_poi m_type;
	string m_description;

public:

/* This function prints all details of the POIs
 * @return returns void*/
	void print(int format);

/*@param type used for enum type of POI
 *@param name used to store the name of the POI
 *@param description used to store the description of the POI
 *@param latitude used to store the latitude of POI
 *@param longitude used to store the longitude of POI
 *@return NO return type in constructor*/
	CPOI(t_poi type = RESTAURANT, string name = "defaultName",
			string description = "defaultDescription", double latitude = 0.0,
			double longitude = 0.0);

/*@param &name used to get name of POI by reference
 *@param &latitude used get latitude of POI by reference
 *@param &longitude used to get the longitude of POI by reference
 *@param &type used to get the enum type of POI by reference
 *@param &description used to get description of POI
 *@return returns void*/
	void getAllDataByReference(string& name, double& latitude, double& longitude,
			t_poi& type, string& description) const;

/**
 *The function overloads << operator for printing object content unconventionally
 *@param cwp reference type of CPOI
 *@param out reference type of ostream
 *@return object of type ostream
 **/
	friend ostream& operator<<(ostream& out, const CPOI& cpoi);

};
/********************
 **  CLASS END
 *********************/
#endif /* CPOI_H */
