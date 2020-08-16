/*
 * CJsonScanner.cpp
 *
 *  Created on: 10.12.2015
 *      Author: mnl
 */

#include <string>
#include "CJsonScanner.h"

using namespace std;

namespace APT {

CJsonScanner::CJsonScanner(std::istream& input) : jsonFlexLexer(&input) {
	token = 0;
}

CJsonScanner::~CJsonScanner() {
	if (token != 0) {
		delete token;
	}
}

CJsonToken* CJsonScanner::nextToken() {
	if (token != 0) {
		delete token;
		token = 0;
	}
	int scanResult = yylex();
	if (scanResult == -1) {
			string illegalChar(YYText());
			// Found illegal character, currently ignored.
			throw illegalChar; //this string has the invalid char
	}

//	/*try catch to catch invalid character exception*/
//	try
//	{
//	if (scanResult == -1) {
//		string illegalChar(YYText());
//		throw YYText();
//	}
//
//	}
//	catch(char const *e)
//	{
//		cout<<"Invalid character: "<<e<<" in Database line number: "<<scannedLine()<<endl;
//		/*To continue program execution after the exception is caught
//		 * since code inside the catch block is executed and the original
//		 * execution continues right after the catch block.*/
//		return nextToken();
//	}
	return token;
}

int CJsonScanner::scannedLine() {
	return yylineno;
}

} /* namespace APT */

int yyFlexLexer::yywrap() {
	return 1;
}

