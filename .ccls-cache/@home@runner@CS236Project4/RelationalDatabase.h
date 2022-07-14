#pragma once

#include "DatalogProgram.h"
#include <vector>

using namespace std;

class RelationalDatabase {
private:
vector<Relation> relationVector;
vector<int> selectCounter;
int ruleCounter = 0;
int newSize = 0;
int oldSize = 0;
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

//rules
	vector<Graph> graphs = RelationalDatabase::makeGraph(rules);
	graphs.at(0).DFSForest();
	graphs.at(1).findSCC(graphs.at(0).getSorted());
	cout << "Rule Evaluation" << endl;
	for (unsigned int i = 0; i < graphs.at(1).getSCC().size(); i++) {
		for (unsigned int j; j < graphs.at(1).getSCC().at(i).size(); j++){
		cout << "SSC: R" << graphs.at(1).getSCC().at(i).getName().at(i);
		int ruleIndex = graphs.at(1).getSCC().at(i).getName().at(j);
		
	do {
		newSize = 0;
		oldSize = 0;
		for (long unsigned int z = 0; z < relationVector.size(); z++) {
			oldSize = oldSize + relationVector.at(z).GetSize();
		}
		for (long unsigned int a = 0; a < rules.size(); a++){
			cout << rules.at(ruleIndex).toString() << endl;
			Relation finalRelation = evaluateParams(rules.at(ruleIndex).GetRightPredicate().at(0), false);
			for (long unsigned int b = 0; j < rules.at(ruleIndex).GetRightPredicate().size(); b++) {
				if (b != 0) {
				Relation r = evaluateParams(rules.at(ruleIndex).GetRightPredicate().at(b), false);
				finalRelation = finalRelation.join(r);
				}
			}
		vector<int> indexVector;
			for (long unsigned int j = 0; j < rules.at(ruleIndex).GetLeftPredicate().GetParameters().size(); j++){
				for (long unsigned int k = 0; k < finalRelation.GetScheme().size(); k++) {
					if (rules.at(ruleIndex).GetLeftPredicate().GetParameters().at(j).GetType() == ID && rules.at(ruleIndex).GetLeftPredicate().GetParameters().at(j).GetName() == finalRelation.GetScheme().at(k)) {
						indexVector.push_back(k);
					}
				}
			}
		finalRelation = finalRelation.project(indexVector);
		finalRelation = finalRelation.rename(relationVector.at(getRelIndex(rules.at(ruleIndex).GetLeftPredicate().getName())).GetScheme());
		relationVector.at(getRelIndex(rules.at(ruleIndex).GetLeftPredicate().getName())).relationUnion(finalRelation);
		
		//cout << finalRelation.toString();
	}
		for (long unsigned int a = 0; a < relationVector.size(); a++) {
			newSize = newSize + relationVector.at(a).GetSize();
		}	
		ruleCounter++;
} while (oldSize != newSize);
		}
		}
		
		
			cout << endl << "Schemes populated after " << ruleCounter << " passes through the Rules." << endl << endl;
		


		//queries
		
		cout << "Query Evaluation" << endl;
		for (long unsigned int i = 0; i < queries.size(); i++){
			Relation r = evaluateParams(queries.at(i), true);
				cout << queries.at(i).toString() << "? ";
				if (selectCounter.at(i) > 0) {
					//i changed selectCounter.at(i) to r.getsize
					cout << "Yes(" << r.GetSize() << ")" << endl;
				}
				else{
					cout << "No" << endl;
				}
				
				cout << r.toString();
	}
			//here put end of comment out
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


	Relation evaluateParams(Predicate p, bool selectCond) {
		Relation r = 	relationVector.at(getRelIndex(p.getName()));
			for (long unsigned int j = 0; j < p.getParameters().size(); j++) {
				if (p.getParameters().at(j).GetType() == STRING) {
					r = r.select(j, p.getParameters().at(j).GetName());
				}
				if (p.getParameters().at(j).GetType() == ID) {
					string identName = p.getParameters().at(j).GetName();
					for (long unsigned int k = j; k < p.getParameters().size(); k++) {
						if (identName == p.getParameters().at(k).GetName()){
							r = r.select(j, k);
						}
				}
			}
		}
		if (selectCond) {
		selectCounter.push_back(r.GetSize());
			}
		vector<int> indexVector;
		set<string> idNames;
		vector<string> setNames;
		for (long unsigned int j = 0; j < p.getParameters().size(); j++){
			
			if (p.getParameters().at(j).GetType() == ID && idNames.find(p.getParameters().at(j).GetName()) == idNames.end()) {
				idNames.insert(p.getParameters().at(j).GetName());
				setNames.push_back(p.getParameters().at(j).GetName());
				indexVector.push_back(j);
			}
		}
				r = r.project(indexVector);
			
				r = r.rename(setNames);
		return r;
	}
static vector<Graph> makeGraph(const vector<Rule>& rules) {
		vector<Graph> graphs;
	 	Graph graph(rules.size());
	 	Graph reverseGraph(rules.size());
		for (unsigned fromID = 0; fromID < rules.size(); fromID++) {
      Rule fromRule = rules.at(fromID);
			for (unsigned pred = 0; pred < fromRule.GetSize(); pred++) {
					Predicate bodyPred = fromRule.getBodyPredicate(pred);
				for (unsigned toID = 0; toID < rules.size(); toID++) {
	  			Rule toRule = rules.at(toID);
					if (bodyPred.getName() == toRule.GetLeftPredicate().getName()) {
						graph.addEdge(fromID, toID);
						reverseGraph.addEdge(toID, fromID);
					}
				}
      }
    }
		cout << "Dependancy Graph" << endl << graph.toString() << endl;
		graphs.push_back(reverseGraph);
		graphs.push_back(graph);
    return graphs;

  }
};