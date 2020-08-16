/*
 * TemplateDB.h
 *
 *  Created on: 05-Jan-2016
 *      Author: VIKRANT
 */

#ifndef TEMPLATEDB_H_
#define TEMPLATEDB_H_

#include<map>
#include<string>
#include "CWaypoint.h"
#include "CPOI.h"
using namespace std;

template<class KEY,class T>

class TemplateDB
{
private:
	map<KEY,T> DBmap;

public:
	TemplateDB();
	void addWpOrPoi(T const& WpOrPoi);
	T* getPointerToWpOrPoi(string name);
	void printWpOrPoi();
	void clearMap();
	const map<KEY,T> getMap() const;
};

template<class KEY, class T>
inline TemplateDB<KEY, T>::TemplateDB()
{

}

template<class KEY, class T>
void TemplateDB<KEY, T>::addWpOrPoi(const T& WpOrPoi)
{
	DBmap.insert(make_pair(WpOrPoi.getName(),WpOrPoi));
}

template<class KEY, class T>
inline T* TemplateDB<KEY, T>::getPointerToWpOrPoi(string name)
{
	T* pointerToWpOrPoi=NULL;

	/*typename used for specifying that a dependent name in a template
	 *definition or declaration is a type.*/
	typename map<KEY,T>::iterator it;
	for(it=DBmap.begin(); it!=DBmap.end(); ++it)
	{
	 //checks if the key is the name passed, only then returns the object for that key
		if(it->first==name)
		{
			pointerToWpOrPoi=&it->second;
		}
	}
	return pointerToWpOrPoi; //returns NULL pointer if no match
}

template<class KEY, class T>
inline void TemplateDB<KEY, T>::printWpOrPoi()
{
	typename map<KEY,T>::iterator it;
		for(it=DBmap.begin(); it!=DBmap.end(); ++it)
		{
			it->second.print(MMSS);
		}
}

template<class KEY, class T>
inline void TemplateDB<KEY, T>::clearMap()
{
	DBmap.clear();
}

template<class KEY, class T>
inline const map<KEY, T> TemplateDB<KEY, T>::getMap() const
{
	return DBmap;
}


#endif /* TEMPLATEDB_H_ */
