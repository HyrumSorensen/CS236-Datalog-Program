#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Node.h"
#include "Graph.h"
#include "RelationalDatabase.h"
#include <iostream>
#include <fstream>
#include <sstream>



int main(int argc, char *argv[]) {

// predicate names for fake rules
  // first is name for head predicate
  // second is names for body predicates
 pair<string,vector<string>> ruleNames[] = {
    { "A", { "B", "C" } },
    { "B", { "A", "D" } },
    { "B", { "B" } },
    { "E", { "F", "G" } },
    { "E", { "E", "F" } },
  };

  vector<Rule> rules;

  for (auto& rulePair : ruleNames) {
    string headName = rulePair.first;
    Rule rule = Rule(Predicate(headName));
    vector<string> bodyNames = rulePair.second;
    for (auto& bodyName : bodyNames)
      rule.addBodyPredicate(Predicate(bodyName));
    rules.push_back(rule);
  }

  Graph graph = RelationalDatabase::makeGraph(rules);
  //cout << graph.toString();
	graph.DFSForest();
	

	/*

	if (argc != 2) {
		cout << "Not enough arguments" << endl;
	}

	string fileName = argv[1];

	ifstream input(fileName);
	stringstream inputString;
	string line;
	while (!input.eof()) {
		getline (input, line);
		inputString << line;
		inputString << "\n";
	}

	Scanner s = Scanner(inputString.str());
  Token t = s.scanToken();
	
	while (t.returnType() != EF) {
		t = s.scanToken();
		t.toString();
	}
	//s.printAllTokens();
	//cout << "Total Tokens = " << s.returnTotTokens() << endl;
	vector<Token> allTokens = s.returnAllTokens();
	Parser p = Parser(allTokens);
	p.scheme();
	RelationalDatabase rd = RelationalDatabase(p.GetData());
	rd.CreateDatabase();


	return 0;
	*/
}