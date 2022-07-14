#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[]) {
	  vector<string> names = { "ID", "Name", "Major" };

  Scheme scheme(names);

  Relation relation("student", scheme);

  vector<string> values[] = {
    {"'42'", "'Ann'", "'CS'"},
    {"'32'", "'Bob'", "'CS'"},
    {"'64'", "'Ned'", "'EE'"},
    {"'16'", "'Jim'", "'EE'"},
  };

  for (auto& value : values) {
    Tuple tuple(value);
    cout << tuple.toString(scheme) << endl;
    relation.addTuple(tuple);
  }

  cout << "relation:" << endl;
  cout << relation.toString();

}
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


	return 0;
	
}
*/