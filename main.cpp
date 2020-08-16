// GIT-Labor
// main.h

////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
#include <iostream>		// Header f�r die Standard-IO-Objekte (z.B. cout, cin)
#include <stdlib.h>
#include "CWayPoint.h"
#include "CGPSSensor.h"
#include "CPOI.h"
#include "CPOIDatabase.h"
#include "CRoute.h"
#include "CNavigationSystem.h"
#include "CWpDatabase.h"
#include "CPersistentStorage.h"
#include "CFileHandling.h"

// TODO: F�gen Sie hier weitere ben�tigte Header-Dateien der
// Standard-Bibliothek ein z.B.
// #include <string>

using namespace std;	// Erspart den scope vor Objekte der
						// C++-Standard-Bibliothek zu schreiben
						// z.B. statt "std::cout" kann man "cout" schreiben

// Inkludieren Sie hier die Header-Files Ihrer Klassen, z.B.
// #include "CFraction.h"


// Hauptprogramm
// Dient als Testrahmen, von hier aus werden die Klassen aufgerufen
int main (void)
{

/*Creating an object of class CNavigationSystem*/
CNavigationSystem cnav;

/*Calling run() function using object of CNavigationSystem*/
cnav.run();

return 0;
}
