/*
 * CJsonPersistence.h
 *
 *  Created on: 05-Jan-2016
 *      Author: VIKRANT
 */

#ifndef CJSONPERSISTENCE_H_
#define CJSONPERSISTENCE_H_

#include<map>
#include<fstream>
#include "CPersistentStorage.h"
#include "CJsonScanner.h" //it has token.h as well
using namespace APT;


class CJsonPersistence : public CPersistentStorage
{
private:
	/**
	 * Variable for the database txt file
	 */
	std::string filename;

	template <class T>
	void writeOwnFunc(const map<string,T> &funcMap, ofstream &out);

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
	bool writeData(const TemplateDB<string, CWaypoint>& waypointDb,
			const TemplateDB<string, CPOI>& poiDb);

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
	bool readData (TemplateDB<string, CWaypoint>& waypointDb,
			TemplateDB<string, CPOI>& poiDb, MergeMode mode);

};

template<class T>
inline void CJsonPersistence::writeOwnFunc(const map<string, T> &funcMap, ofstream &fout)
{
  for(typename map<string,T>::const_iterator itr=funcMap.begin(); itr!=funcMap.end(); ++itr)
	{
			fout<<"    {"<<endl;
			fout<<"     \"name\": "<<"\""<<itr->second.getName()<<"\""<<","<<endl;
			fout<<"     \"latitude\": "<<itr->second.getLatitude()<<","<<endl;
			fout<<"     \"longitude\": "<<itr->second.getLongitude()<<endl;

//dynamic cast to check if the current object pointed by iterator in map is POI
	const CPOI* temp=dynamic_cast<const CPOI*>(&(itr)->second);
		if (temp != NULL)    //Object pointed by iterator is a POI, go inside 'if' condn
		{
			string Poiname, PoiDescription;
			double PoiLat, PoiLong;
			t_poi Poitype;
			temp->getAllDataByReference(Poiname, PoiLat, PoiLong, Poitype,
					PoiDescription);
			switch (Poitype)
			{
			case RESTAURANT:
				fout.seekp(-2,ios::end);  //to go back to the longitude and insert',' after it
				fout<<","<<endl;
				fout << "     \"type\": " << "\"RESTAURANT\"" << "," << endl;
				fout << "     \"description\": " << "\"" << PoiDescription<< "\"" << endl;
				break;
			case SIGHTSEEING:
				fout.seekp(-2,ios::end);
				fout<<","<<endl;
				fout << "     \"type\": " << "\"SIGHTSEEING\"" << "," << endl;
				fout << "     \"description\": " << "\"" << PoiDescription<< "\"" << endl;
				break;
			case SHOPPING:
				fout.seekp(-2,ios::end);
				fout<<","<<endl;
				fout << "     \"type\": " << "\"SHOPPING\"" << "," << endl;
				fout << "     \"description\": " << "\"" << PoiDescription<< "\"" << endl;
				break;
			default:
				fout << "NO such type found" << endl;
			}
		}
		/*If else loop to catch last element and put comma only after '}' of last element*/
		if(itr!=--funcMap.end())
		{
			fout<<"    }"<<","<<endl;
		}
		else
		{
			fout<<"    }"<<endl;
		}

	}
}


#endif /* CJSONPERSISTENCE_H_ */
