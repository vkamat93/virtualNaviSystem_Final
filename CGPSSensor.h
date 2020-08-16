/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSENSOR.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H
#include "CWaypoint.h"

/*This class is used to get the current position from the user in a navigation system
 * just as a real world GPS sensor would do*/
class CGPSSensor
{
public:

/*Constructor of this class. Not used in this exercise*/
    CGPSSensor();

/*@return returns an object of CWaypoint class with latitude and longitude in it*/
    CWaypoint getCurrentPosition();
};
/********************
**  CLASS END
*********************/
#endif /* CGPSSENSOR_H */
