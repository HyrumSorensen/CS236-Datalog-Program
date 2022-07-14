#pragma once
#include "Predicate.h"
#include <vector>
#include <sstream>

using namespace std;

class Rule {
	private:
		Predicate leftPredicate;
		vector<Predicate> predVector;
	public:

	Rule(Predicate leftPredicate) : leftPredicate(leftPredicate){}

	void addPredicates(vector<Predicate> pre){
		predVector = pre;
	}
	string toString(){
		stringstream out;
		out << leftPredicate.toString();
		out << " :- ";
		for (long unsigned int i = 0; i < predVector.size(); i++){
			out << predVector.at(i).toString();
			if (i != predVector.size()-1){
				out << ",";
			}
		}
			return out.str();
	}
};