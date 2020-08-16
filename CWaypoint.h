/*
 * CWaypoint.h
 *
 *  Created on: 01-Nov-2015
 *      Author: VIKRANT
 */

#ifndef CWAYPOINT_H_
#define CWAYPOINT_H_

#include <iostream>
using namespace std;


/*.h file is the best to put #define since this file is included in the main.cpp
 and thus the values in #define can be read by the main() and the values can remain
 hidden from the end user as well*/
#define DEGREE 1
#define MMSS 2

//#define SHOWADDRESS
/* #ifdef allows to part of the code to be compiled only if the macro that is specified
as the parameter has been defined */

class CWaypoint
{
protected:
/*variables which can then be inherited in another class*/
	string m_name;
	double m_latitude;
	double m_longitude;

private:
	void calculateXYZ(double& x, double& y, double& z);

protected:
/*These functions can be accessed only by other public functions of this class*/
/* @param &deg the value of deg passed by reference
* @param &mm the value of mm is passed by reference
* @param &ss the value of ss is passed by reference
* @return returns void*/
	void transformLongitude2degmmss(int& deg, int& mm, double& ss) const;

/* @param &deg the value of deg passed by reference
* @param &mm the value of mm is passed by reference
* @param &ss the value of ss is passed by reference
* @return returns void*/
	void transformLatitude2degmmss(int& deg, int& mm, double& ss) const;


public:
/*@param name used to store a default value and call by value
 * @param latitude used to store a default value and call by value
 * @param longitude used to store a default value and call by value
 * @return no return type for constructor*/
	CWaypoint(string name = "no value", double latitude=0.00, double longitude=0.00);

/*@param name used to set a value to protected m_name
* @param latitude used to set a value to protected m_latitude
* @param longitude used to set value to protected m_longitude
* @return returns void*/
	void set(string name, double latitude, double longitude);

/*@return returns string m_name*/
	string getName()const;

/*@return returns double m_latitude*/
	double getLatitude() const;

/*@return returns double m_longitude*/
	double getLongitude() const;

/**
* The function returns the object contents by reference to the object
* @param &name the value of name passed by reference
* @param &latitude the value of latitude is passed by reference
* @param &longitude the value of longitude is passed by reference
* @return returns void*/
	void getAllDataByReference(string& name, double& latitude, double& longitude) const;

/* @param const Object of CWayapoint
 * @return returns distance in double */
	double calculateDistance(const CWaypoint& wp);

/*@param format which takes the value of 1 or 0 using #define
 *@return returns void */
	virtual void print(int format);

/**
 *The function overloads << operator for printing object content unconventionally
 *@param cwp reference type of CWaypoint
 *@param out reference type of ostream
 *@return object of type ostream
 **/
	friend ostream& operator<<(ostream& out, const CWaypoint& cwp);

/*Virtual destructor necessary for a class having virtual function*/
	virtual ~CWaypoint();
};



#endif /* CWAYPOINT_H_ */
