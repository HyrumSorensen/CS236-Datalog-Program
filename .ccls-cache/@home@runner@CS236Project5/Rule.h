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
	int GetSize() {
		return predVector.size();
	}
	Predicate getBodyPredicate(int index) {
		return predVector.at(index);
	}
	void addBodyPredicate(Predicate pre) {
		predVector.push_back(pre);
	}

	void addPredicates(vector<Predicate> pre){
		predVector = pre;
	}

	Predicate GetLeftPredicate() {
		return leftPredicate;
	}
	vector<Predicate> GetRightPredicate(){
		return predVector;
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
			out << ".";
			return out.str();
	}
};