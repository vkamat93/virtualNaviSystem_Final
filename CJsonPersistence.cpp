/*
 * CJsonPersistence.cpp
 *
 *  Created on: 05-Jan-2016
 *      Author: VIKRANT
 */

#include "CJsonPersistence.h"
#include<fstream>

void CJsonPersistence::setMediaName(std::string name)
{
	filename=name+".txt";
}

bool CJsonPersistence::writeData(const TemplateDB<string, CWaypoint>& waypointDb,
		const TemplateDB<string, CPOI>& poiDb)
{
/******FOR WAYPOINTS********/

//creating a temporary WpMap by assigning it the copy of the original WpMap
const map<string, CWaypoint> tempWpMap=waypointDb.getMap();

	ofstream fout;
	fout.open(filename.c_str());
	if(fout.is_open()==1)
	{
		fout<<"{"<<endl<<" \"waypoints\": "<<"["<<endl;
		writeOwnFunc(tempWpMap,fout);
//		for(map<string,CWaypoint>::const_iterator it=tempWpMap->begin(); it!=tempWpMap->end();++it)
//		{
//			string Wpname;
//			double WpLat, WpLong;
//			it->second.getAllDataByReference(Wpname, WpLat, WpLong);
//			fout<<"    {"<<endl<<"    \"name\": "<<"\""<<Wpname<<"\""<<","<<endl;
//			fout<<"     \"latitude\": "<<WpLat<<","<<endl;
//			fout<<"     \"longitude\": "<<WpLong<<endl;
//			fout<<"    }"<<","<<endl;
//		}
		fout<<" ]"<<","<<endl;

/******FOR POIS******/

//creating a temporary PoiMap by assigning it the copy of the original PoiMap
const map<string, CPOI> tempPoiMap=poiDb.getMap();

fout<<" \"pois\": "<<"["<<endl;
writeOwnFunc(tempPoiMap, fout);
//for (map<string, CPOI>::const_iterator it = tempPoiMap->begin();it != tempPoiMap->end(); ++it)
//	{
//	string Poiname, PoiDescription;
//	double PoiLat, PoiLong;
//	t_poi Poitype;
//	it->second.getAllDataByReference(Poiname, PoiLat, PoiLong, Poitype,
//		PoiDescription);
//		switch (Poitype)
//		    {
//		  case RESTAURANT:
//			  fout<<"    {"<<endl;
//			  fout<<"     \"name\": "<<"\""<<Poiname<<"\""<<","<<endl;
//			  fout<<"     \"latitude\": "<<PoiLat<<","<<endl;
//			  fout<<"     \"longitude\": "<<PoiLong<<","<<endl;
//			  fout<<"     \"type\": "<<"RESTAURANT"<<","<<endl;
//			  fout<<"     \"description\": "<<"\""<<PoiDescription<<"\""<<endl;
//			  fout<<"    }"<<","<<endl;
//			break;
//		  case SIGHTSEEING:
//			  fout<<"    {"<<endl;
//			  fout<<"     \"name\": "<<"\""<<Poiname<<"\""<<","<<endl;
//			  fout<<"     \"latitude\": "<<PoiLat<<","<<endl;
//			  fout<<"     \"longitude\": "<<PoiLong<<","<<endl;
//			  fout<<"     \"type\": "<<"SIGHTSEEING"<<","<<endl;
//			  fout<<"     \"description\": "<<"\""<<PoiDescription<<"\""<<endl;
//			  fout<<"    }"<<","<<endl;
//			break;
//		  case SHOPPING:
//			  fout<<"    {"<<endl;
//			  fout<<"     \"name\": "<<"\""<<Poiname<<"\""<<","<<endl;
//			  fout<<"     \"latitude\": "<<PoiLat<<","<<endl;
//			  fout<<"     \"longitude\": "<<PoiLong<<","<<endl;
//			  fout<<"     \"type\": "<<"SHOPPING"<<","<<endl;
//			  fout<<"     \"description\": "<<"\""<<PoiDescription<<"\""<<endl;
//			  fout<<"    }"<<","<<endl;
//			break;
//		  default:
//			fout << "NO such type found" << endl;
//			}
//		}
    fout<<" ]"<<endl<<"}";
	fout.close();
		}
		else
		{
			cout<<"Error:Database File cannot be opened for write operation!!"<<endl;
		}
	return true;
}

bool CJsonPersistence::readData(TemplateDB<string, CWaypoint>& waypointDb,
		TemplateDB<string, CPOI>& poiDb, MergeMode mode)
{
	enum StateType
	{
		WAITING_FOR_BEGIN_DB,
		WAITING_FOR_BEGIN_OBJECT,
		WAITING_FOR_DB_NAME,
		WAITING_FOR_DB_NAME_SEPERATOR,
		WAITING_FOR_NAME_SEPERATOR,
		WAITING_FOR_BEGIN_ARRAY,
		WAITING_FOR_NAME,
		WAITING_FOR_VALUE,
		WAITING_FOR_VALUE_SEPERATOR,
		WAITING_FOR_OBJECT_SEPERATOR,
		WAITING_FOR_ARRAY_SEPERATOR,
	//	WAITING_FOR_END_OBJECT,
	//	WAITING_FOR_END_DB,
	//	WAITING_FOR_END_ARRAY,
	};

	CJsonToken *token;
	ifstream fin; //creating object of ifstream to pass in the CJsonScannerobject
	CJsonScanner scanner(fin); //see the constructor of CJsonScanner
	fin.open(filename.c_str(),ios::app);

	int state=WAITING_FOR_BEGIN_DB;  //initializing the state for state diagram to begin
	string title_name,db_name,name,type,description;
	double latitude,longitude;
	t_poi poiType; //

	try
	{
	token=scanner.nextToken();
	}
	catch(string &e)
	{
	cout<<"Invalid character: "<<e<<" in Database line: "<<scanner.scannedLine()<<endl;
	}

	while(token!=NULL)
	{
	switch(state)
	{
	case WAITING_FOR_BEGIN_DB:
		if(token->getType()==CJsonToken::BEGIN_OBJECT)
		{
			state=WAITING_FOR_DB_NAME;
		}
		break;

	case WAITING_FOR_DB_NAME:
		if(token->getType()==CJsonToken::STRING)
		{
			db_name=((CJsonStringToken*)(token))->getValue();
			state=WAITING_FOR_DB_NAME_SEPERATOR;
		}
		break;

	case WAITING_FOR_DB_NAME_SEPERATOR:
		if(token->getType()==CJsonToken::NAME_SEPARATOR)
		{
			state=WAITING_FOR_BEGIN_ARRAY;
		}
		break;

	case WAITING_FOR_BEGIN_ARRAY:
		if(token->getType()==CJsonToken::BEGIN_ARRAY)
		{
			state=WAITING_FOR_BEGIN_OBJECT;
		}
		break;

	case WAITING_FOR_BEGIN_OBJECT:
		if(token->getType()==CJsonToken::BEGIN_OBJECT)
		{
			state=WAITING_FOR_NAME;
		}
		break;

	case WAITING_FOR_NAME:
		if(token->getType()==CJsonToken::STRING)
		{
			title_name=((CJsonStringToken*)(token))->getValue();
			state=WAITING_FOR_NAME_SEPERATOR;
		}
		else if(token->getType()==CJsonToken::VALUE_SEPARATOR)
		{
				cout << "ERROR: Wrong insertion of semicolon in database line: "
						<< scanner.scannedLine() - 1 << endl;
		}
		break;

	case WAITING_FOR_NAME_SEPERATOR:
		if(token->getType()==CJsonToken::NAME_SEPARATOR)
		{
			state=WAITING_FOR_VALUE;
		}

		break;

	case WAITING_FOR_VALUE:
		if(token->getType()==CJsonToken::STRING)
		{
			string temp=((CJsonStringToken*)(token))->getValue();
			if(title_name=="name")
			{
				name=temp;
				//cout<<name<<endl;
			}
			else if(title_name=="type")
			{
				type=temp;
				if(type=="RESTAURANT")
				{
					poiType=RESTAURANT; //giving enum types based on string saved
				}
				else if(type=="SIGHTSEEING")
				{
					poiType=SIGHTSEEING;
				}
				else if(type=="SHOPPING")
				{
					poiType=SHOPPING;
				}
			}
			else if(title_name=="description")
			{
				description=temp;
				//cout<<description<<endl;
			}

			state=WAITING_FOR_VALUE_SEPERATOR;
		}
		else if(token->getType()==CJsonToken::NUMBER)
		{
			double temp=((CJsonNumberToken*)(token))->getValue();
			if(title_name=="latitude")
			{
				latitude=temp;
				//cout<<latitude<<endl;
			}
			else if(title_name=="longitude")
			{
				longitude=temp;
				//cout<<longitude<<endl;
			}
			state=WAITING_FOR_VALUE_SEPERATOR;
		}
		break;

	case WAITING_FOR_VALUE_SEPERATOR:
		if(token->getType()==CJsonToken::VALUE_SEPARATOR)
		{
			state=WAITING_FOR_NAME;
		}
		else
		{
			//now adds the acquired data into a WP or POI object before proceeding
			if(db_name=="waypoints")
			{
				waypointDb.addWpOrPoi(CWaypoint(name,latitude,longitude));
			}
			else if(db_name=="pois")
			{
				poiDb.addWpOrPoi(CPOI(poiType,name,description,latitude,longitude));
			}
			state=WAITING_FOR_OBJECT_SEPERATOR; //proceeds to check whether more objects present or not
		}
		break;

	case WAITING_FOR_OBJECT_SEPERATOR:
		if(token->getType()==CJsonToken::VALUE_SEPARATOR)
		{
			state=WAITING_FOR_BEGIN_OBJECT;
		}
		else
		{
			state=WAITING_FOR_ARRAY_SEPERATOR;
		}
		break;

	case WAITING_FOR_ARRAY_SEPERATOR:
		if(token->getType()==CJsonToken::VALUE_SEPARATOR)
		{
			state=WAITING_FOR_DB_NAME;
		}
		else
		{
			state=WAITING_FOR_BEGIN_DB;
		}
		break;

	default:
		break;

	}
	try
	{
	token=scanner.nextToken();
	}
	catch(string &e)
	{
		cout<<"Invalid character: "<<e<<" in Database line: "<<scanner.scannedLine()<<endl;
	}
	}
	waypointDb.printWpOrPoi();
	poiDb.printWpOrPoi();
	return true;
}
