#include "CGPSSensor.h"
#include "CWaypoint.h"

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.CPP
* Author          :
* Description     :
*
*
****************************************************************************/


//System Include Files


//Own Include Files

//Method Implementations

CGPSSensor::CGPSSensor()
{
/*Here constructor has no role in initialization thus is unused*/
}


CWaypoint CGPSSensor::getCurrentPosition()
{
/*defining local variables to store user entered values*/
   double latitude;
   double longitude;

/*To get the longitude as if from a real working sensor*/
   cout<<endl<<"GPS Sensor"<<endl<<"Enter Latitude: ";
   cin>>latitude;

/*To get the latitude as if from a real working sensor*/
   cout<<"Enter Longitude: ";
   cin>>longitude;

/*Passing the entered latitude and longitude to object of Cwaypoint which is returned*/
   CWaypoint wp("",latitude,longitude);
   return wp;
}
