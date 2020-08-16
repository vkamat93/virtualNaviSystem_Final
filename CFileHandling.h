/*
 * CFileHandling.h
 *
 *  Created on: 07-Dec-2015
 *      Author: VIKRANT
 */

#ifndef CFILEHANDLING_H_
#define CFILEHANDLING_H_

#include<iostream>
#include<string.h>
#include<map>


#include"CPersistentStorage.h"

class CFileHandling : public CPersistentStorage
{
private:
	/**
	 * Variable for the Waypoint database txt file
	 */
	std::string wpMediaName;
	/**
	 * Variable for the POI database txt file
	 */
	std::string poiMediaName;

public:
	/**
	* Set the name of the media to be used for persistent storage.
	* The exact interpretation of the name depends on the implementation
	* of the component.
	* @param name the media to be used
	*/
	void setMediaName(std::string name);

	/**
	* Write the data to the persistent storage.
	* @param waypointDb the data base with way points
	* @param poiDb the database with points of interest
	* @return true if the data could be saved successfully
	*/
	bool writeData (const CWpDatabase& waypointDb, const CPOIDatabase& poiDb);

	/**
	* Fill the databases with the data from persistent storage. If
	* merge mode is MERGE, the content in the persistent storage
	* will be merged with any content already existing in the data
	* bases. If merge mode is REPLACE, already existing content
	* will be removed before inserting the content from the persistent
	* storage.
	* @param waypointDb the the data base with way points
	* @param poiDb the database with points of interest
	* @param mode the merge mode
	* @return true if the data could be read successfully
	*/
	bool readData (CWpDatabase& waypointDb, CPOIDatabase& poiDb, MergeMode mode);

};

#endif /* CFILEHANDLING_H_ */
