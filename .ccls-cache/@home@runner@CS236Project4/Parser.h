#include <vector>
#include "Token.h"
#include "DatalogProgram.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"


class Parser {
 private:
  vector<Token> tokens;
	vector<Parameter> parameters;
	vector<Predicate> predicates;
	DatalogProgram dp;
	bool error = false;
 public:
 int queryCounter = 0;
  Parser(const vector<Token>& tokens) : tokens(tokens) { }
	vector<Parameter> getCopy(){
		vector<Parameter> copy;
		for(long unsigned int i = 0; i < parameters.size(); i++){
				copy.push_back(parameters.at(i));
		}
		parameters.clear();
		return copy;
	}
	DatalogProgram GetData() {
		return dp;
	}
	vector<Predicate> getPredCopy() {
		vector<Predicate> copy;
		for(long unsigned int i = 0; i < predicates.size(); i++){
			copy.push_back(predicates.at(i));
		}
		predicates.clear();
		return copy;
	}

 TokenType tokenType() const {
    return tokens.at(0).returnType();
  }
  void advanceToken() {
    tokens.erase(tokens.begin());
  }
  void throwError() {
    cout << "Failure!" << endl << "  " << tokens.at(0).toString() << endl;
		exit(0);
  }

	void matchComment() {
		if (tokenType() == COMMENT){
			match(COMMENT);
			matchComment();
		}
	}
	

	void match(TokenType t) {
    //cout << "match: " << t << endl;
    if (tokenType() == t && error == false){
      advanceToken();
		}
    else{
      throwError();
			error = true;
		}
  }
	void mixtureList() {
		if (tokenType() == COMMA) {
			match(COMMA);
			Parameter p = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p);
			if (tokenType() == ID){
				match(ID);
			}
			else if (tokenType() == STRING) {
				match(STRING);
			}
			else {throwError();
			}
			mixtureList();
		}
	}
	void stringList() {
		if (tokenType() == COMMA){
			match(COMMA);
			Parameter p = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p);
			dp.domainPush(tokens.at(0).returnValue());
			match(STRING);
			stringList();
		}
		else {
			// lambda
		}
	}
	void idList() {
    if (tokenType() == COMMA) {
      match(COMMA);
			Parameter p = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p);
      match(ID);
      idList();
    } else {
      // lambda
    }
  }
	void predicateList() {
		if (tokenType() == COMMA){
			match(COMMA);
			Predicate pred = Predicate(tokens.at(0).returnValue());
			match(ID);
			match(LEFT_PAREN);
			Parameter p2 = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p2);
			if(tokenType() == ID) {
				match(ID);
			}
			else if (tokenType() == STRING){
				match(STRING);
			}
			mixtureList();
			match(RIGHT_PAREN);
			pred.addParameters(getCopy());
			predicates.push_back(pred);
			predicateList();
		}
	}
	void scheme() {
		matchComment();
		if (tokenType() == SCHEMES) {
			match(SCHEMES);
			match(COLON);
			scheme();
		}
    else if (tokenType() == ID) {
			Predicate pre = Predicate(tokens.at(0).returnValue());
      match(ID);
      match(LEFT_PAREN);
			Parameter p = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p);
      match(ID);
      idList();
      match(RIGHT_PAREN);
			pre.addParameters(getCopy());
			dp.schemePush(pre);
			matchComment();
			scheme();
    }
		 else {
			 if (tokenType() == FACTS) {
				if (dp.getSchemeSize() == 0) throwError();
				fact();
			}
			else{
      throwError();
			}
    }
  }
	void fact() {
		matchComment();
		if (tokenType() == FACTS){
			match(FACTS);
			match(COLON);
			fact();
		}
		else if (tokenType() == ID){
			Predicate pre = Predicate(tokens.at(0).returnValue());
			match(ID);
			match(LEFT_PAREN);
			Parameter p = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p);
			dp.domainPush(tokens.at(0).returnValue());
			match(STRING);
			stringList();
			match(RIGHT_PAREN);
			match(PERIOD);
			pre.addParameters(getCopy());
			dp.factPush(pre);
			matchComment();
			fact();
		}

			else{
				if (tokenType() == RULES){
				rule();
			}
			else{
				throwError();
			}
		}
	}
	

	void rule() {
		matchComment();
		if (tokenType() == RULES){
			match(RULES);
			match(COLON);
			rule();
		}
		else if (tokenType () == ID) {
			Predicate pre = Predicate(tokens.at(0).returnValue());
			match(ID);
			match(LEFT_PAREN);
			Parameter p = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p);
			match(ID);
			idList();
			match(RIGHT_PAREN);
			pre.addParameters(getCopy());
			Rule r = Rule(pre);
			match(COLON_DASH);
			Predicate pred = Predicate(tokens.at(0).returnValue());
			match(ID);
			match(LEFT_PAREN);
			Parameter p2 = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p2);
			match(ID);
			//idList();
			mixtureList();
			match(RIGHT_PAREN);
			pred.addParameters(getCopy());
			predicates.push_back(pred);
			predicateList();
			match(PERIOD);
			r.addPredicates(getPredCopy());
			dp.rulePush(r);
			matchComment();
			rule();
		}
		else{
				if (tokenType() == QUERIES){
				query();
			}
			else{
				throwError();
			}
		}
	}
	void query(){
		if (tokenType() == QUERIES && queryCounter == 0){
			match(QUERIES);
			match(COLON);
			queryCounter = 1;
			query();
		}
		else if (tokenType() == ID) {
			Predicate pre = Predicate(tokens.at(0).returnValue());
			match(ID);
			match(LEFT_PAREN);
			Parameter p = Parameter(tokens.at(0).returnType(), tokens.at(0).returnValue());
			parameters.push_back(p);
			if (tokenType() == ID){
				match(ID);
			}
			else if (tokenType() == STRING) {
				match(STRING);
			}
			else {throwError();
			}		
		mixtureList();
		match(RIGHT_PAREN);
		match(Q_MARK);
		pre.addParameters(getCopy());
		dp.queryPush(pre);

		query();
		}
		else{
			if (dp.getQuerySize() == 0){
					throwError();
			}

			if (tokenType() == EF){
			//	cout << "Success!" << endl << dp.toString();
			}
			else{
				throwError();
			}
		}
	}

};