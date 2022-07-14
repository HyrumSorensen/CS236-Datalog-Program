#pragma once

#include "Parameter.h"
#include <vector>

using namespace std;

class Predicate {
	private:
		string name;
		vector<Parameter> pVector;
	public:

		Predicate(string name) : name(name){}

		void addParameters(vector<Parameter> allparameters){
			pVector = allparameters;
	}

		string toString() {
			stringstream out;
			out << name << "(";
			for (long unsigned int i = 0; i <pVector.size(); i ++){
				out << pVector.at(i).toString();
				if (i < pVector.size() -1){
					out << ",";
				}
			}
			out << ")";
			return out.str();
		}
		string getName(){
			return name;
		}
		vector<Parameter> getParameters() {
			return pVector;
		}
		
};