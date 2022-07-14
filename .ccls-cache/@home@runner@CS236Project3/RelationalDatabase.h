#pragma once

#include "DatalogProgram.h"
#include <vector>

using namespace std;

class RelationalDatabase {
private:
vector<Relation> relationVector;
vector<int> selectCounter;
DatalogProgram dp;

public:
	RelationalDatabase( DatalogProgram dp) :  dp(dp) {}

	void CreateDatabase() {
		vector<Predicate> schemes = dp.GetSchemes();
		vector<Predicate> facts = dp.GetFacts();
		vector<Predicate> queries = dp.GetQueries();
		vector<Rule> rules = dp.GetRules();
//schemes
		for (long unsigned int i = 0; i < schemes.size(); i++){
			vector<string> paramNames;
			for(long unsigned int j = 0; j < schemes.at(i).GetParameters().size(); j++){
				paramNames.push_back(schemes.at(i).GetParameters().at(j).GetName());
			}
			Scheme s = Scheme(paramNames);
			Relation r = Relation(schemes.at(i).getName(), s);
			relationVector.push_back(r);
		}
//facts
		for (long unsigned int i = 0; i < facts.size(); i++){
			vector<string> paramNames;
			string name = facts.at(i).getName();
			for(long unsigned int j = 0; j < facts.at(i).GetParameters().size(); j++){
				paramNames.push_back(facts.at(i).GetParameters().at(j).GetName());
			}
			Tuple t = Tuple(paramNames);
			GetRelation(name, t);
		}


		//queries
		for (long unsigned int i = 0; i < queries.size(); i++){
			Relation r = 	relationVector.at(getRelIndex(queries.at(i).getName()));
			for (long unsigned int j = 0; j < queries.at(i).getParameters().size(); j++) {
				if (queries.at(i).getParameters().at(j).GetType() == STRING) {
					r = r.select(j, queries.at(i).getParameters().at(j).GetName());
				}
				if (queries.at(i).getParameters().at(j).GetType() == ID) {
					string identName = queries.at(i).getParameters().at(j).GetName();
					for (long unsigned int k = j; k < queries.at(i).getParameters().size(); k++) {
						if (identName == queries.at(i).getParameters().at(k).GetName()){
							r = r.select(j, k);
						}
				}
				
			}
		}
		selectCounter.push_back(r.getSize());
		vector<int> indexVector;
		set<string> idNames;
		vector<string> setNames;
		for (long unsigned int j = 0; j < queries.at(i).getParameters().size(); j++){
			
			if (queries.at(i).getParameters().at(j).GetType() == ID && idNames.find(queries.at(i).getParameters().at(j).GetName()) == idNames.end()) {
				idNames.insert(queries.at(i).getParameters().at(j).GetName());
				setNames.push_back(queries.at(i).getParameters().at(j).GetName());
				indexVector.push_back(j);
			}
		}
				r = r.project(indexVector);
			
				r = r.rename(setNames);
				cout << queries.at(i).toString() << "? ";
				if (selectCounter.at(i) > 0) {
					cout << "Yes(" << selectCounter.at(i) << ")" << endl;
				}
				else{
					cout << "No" << endl;
				}
				
				cout << r.toString();
	}
			
}
	void GetRelation(string name, Tuple t){
		for(long unsigned int i = 0; i < relationVector.size(); i++){
			if (name == relationVector.at(i).GetName()){
				relationVector.at(i).addTuple(t);
			}
	}
}
	unsigned int getRelIndex(string name){
		for(long unsigned int i = 0; i < relationVector.size(); i++){
			if (name == relationVector.at(i).GetName()){
				return i;
			}
		}
		return -1;
	}
};