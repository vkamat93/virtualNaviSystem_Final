/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDATABASE.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H
#include "CPOI.h"
#include "TemplateDB.h"
#include<map>

//This class is used to make a database of the POIs and store all their details
class CPOIDatabase : public TemplateDB<string,CPOI>
{
private:

	std::map<string,CPOI> poiMap;

public:

/*Default Constructor
 *@return no return type in Constructor */
    CPOIDatabase();

/**
 * This function adds the POIs to the database one by one
 *@param poi is the object passed by reference so that all object is stored in the POI map
 *@return returns void
 **/
    void addPoi(CPOI const& poi);

/*This function is used to check whether desired POI in route exists in the Database
 *@param name to get a name of the POI which is to be checked for existence in Database
 *@return returns a pointer of type CPOI*/
    CPOI* getPointerToPoi(string name);

/*This function clears the Poi Map which is then used for the REPLACE case in ReadFile
 * @return void*/
void clearPoiMap();

/**This function prints the Poi database for testing purposes
 *@return void
 **/
void print();

const map<string,CPOI> getPoiMap() const;

};
/********************
**  CLASS END
*********************/
#endif /* CPOIDATABASE_H */
