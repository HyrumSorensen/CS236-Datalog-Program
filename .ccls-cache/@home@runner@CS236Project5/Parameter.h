#pragma once
#include "Token.h"
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

class Parameter {
	private:

	TokenType type;
	string value;
	
	public:

	Parameter(TokenType type, string value) : type(type), value(value){}
	string GetName() {
		return value;
	}
	TokenType GetType(){
		return type;
	}
	string toString(){

	stringstream out;
	out << value;
	return out.str();
	}
};

