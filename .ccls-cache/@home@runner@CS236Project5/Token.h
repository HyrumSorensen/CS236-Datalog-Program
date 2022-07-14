#pragma once

#include <string>
#include <iostream>
#include <sstream>

using namespace std;



enum TokenType {

  COMMA, ID, SCHEMES, STRING, COMMENT, COLON, COLON_DASH, LEFT_PAREN, RIGHT_PAREN, QUERIES, FACTS, Q_MARK, RULES, PERIOD, ADD, MULTIPLY, UNDEFINED, EF
};

class Token {

  private:
  	TokenType type;
    string value;
    int line;
  public:
  	Token(TokenType type, string value, int line) : type(type), value(value), line(line) {

		 }

    string toString() {
    	stringstream out;
    	out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
    	return out.str();
    }
		
		string typeName(TokenType type) const {
    switch (type) {
    case COMMA:
      return "COMMA";
    case ID:
			return "ID";
    case SCHEMES:
			return "SCHEMES";
		case STRING:
			return "STRING";
		case COMMENT:
			return "COMMENT";
		case COLON:
			return "COLON";
		case COLON_DASH:
			return "COLON_DASH";
		case LEFT_PAREN:
			return "LEFT_PAREN";
		case RIGHT_PAREN:
			return "RIGHT_PAREN";
		case QUERIES:
			return "QUERIES";
		case FACTS:
			return "FACTS";
		case Q_MARK:
			return "Q_MARK";
		case RULES:
			return "RULES";
		case PERIOD:
			return "PERIOD";
		case ADD:
			return "ADD";
		case MULTIPLY:
			return "MULTIPLY";
		case UNDEFINED:
			return "UNDEFINED";
		case EF:
			return "EOF";
		}
		return 0;
	}
	TokenType returnType() const{
		return type;
	}
	string returnValue() const{
		return value;
	}
};
