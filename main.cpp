#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Node.h"
#include "SCC.h"
#include "Graph.h"
#include "RelationalDatabase.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>



int main(int argc, char *argv[]) {

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
	
}