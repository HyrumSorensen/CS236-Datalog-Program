#pragma once

#include "Token.h"
#include <string>
#include <vector>
#include <iostream>
class Scanner
{
private:
    string input;
    unsigned int lineNum = 1;
		unsigned int totalTokens = 0;
		vector<Token> tokenVector;
public:
    Scanner(const string &input) : input(input)
    {}
		int returnTotTokens() {
			return totalTokens;
		}
    Token scanToken()
    {
				int commentLine;
        string values = "";
        TokenType type = EF;
        unsigned int size = 0;
				string tempInput;
				if (input.size() != 1) {
        while (input.size() != 0 && isspace(input.at(0))) {
            if (input.at(0) == '\n' && input.size() != 1){
                lineNum++;
						}
							input = input.substr(1);
				}
				commentLine = lineNum;
				if (input.size() == 0) {
				type = EF;
				string values = "";
				totalTokens++;
        Token newToken = Token(type, values, commentLine);
        tokenVector.push_back(newToken);
				return newToken;
				}
				commentLine = lineNum;
        switch (input.at(0))
        {	
						case '\'':
							size = 2;
							tempInput = input;
							tempInput = tempInput.substr(1);
							while (tempInput.size() != 0 &&tempInput.at(0) != '\'') {
								if (tempInput.at(0) == '\n') {
									lineNum++;
								}
								tempInput = tempInput.substr(1);
								size++;
								if (tempInput.size() == 0){
									size--;
									lineNum--;
									type = UNDEFINED;
									break;
								}
							}
							if (type != UNDEFINED){
								type = TokenType::STRING;
							}
							break;
						case '#':
							if (input.size() > 1 && input.at(1) == '|') {
								size = 2;
								tempInput = input;
								while (tempInput.size() != 0 && tempInput.substr(0,2) != "|#") {
									if (tempInput.at(0) == '\n'){
										lineNum++;
									}
									tempInput = tempInput.substr(1);
									size++;
									if (tempInput.size() == 1) {
										type = UNDEFINED;
										size = 1;
									}
								}
							}
							else {
								tempInput = input;
								while (tempInput.size() != 0 &&tempInput.at(0) != '\n') {
									tempInput = tempInput.substr(1);
									size++;
								}
							}
							if (type != UNDEFINED) {
								type = COMMENT;
							}
							break;
            case ',':
              size = 1;
              type = COMMA;
              break;
						case '.':
							size = 1;
							type = PERIOD;
							break;
						case '?':
							size = 1;
							type = Q_MARK;
							break;
						case '(':
							size = 1;
							type = LEFT_PAREN;
							break;
						case ')':
							size = 1;
							type = RIGHT_PAREN;
							break;
						case ':':
							if (input.size() > 1 && input.substr(0,2) == ":-"){
								size = 2;
								type = COLON_DASH;
								break;
							}
							else {
							size = 1;
							type = COLON;
							break;
						}
						case '*':
							size = 1;
							type = MULTIPLY;
							break;
						case '+':
							size = 1;
							type = ADD;
							break;
						default:
							if (isalpha(input.at(0))){
								tempInput = input;
								size = 0;
								while (!isspace(tempInput.at(0)) && (isalpha(tempInput.at(0)) || isdigit(tempInput.at(0)))){
									tempInput = tempInput.substr(1);
									size++;
								}
								if (input.substr(0,size) == "Queries") {
									size = 7;
									type = QUERIES;
								}
								else if (input.substr(0,size) == "Schemes") {
									size = 7;
									type = SCHEMES;
								}
								else if (input.substr(0,size) == "Facts") {
									size = 5;
									type = FACTS;
								}
								else if (input.substr(0,size) == "Rules") {
									size = 5;
									type = RULES;
								}
								else{
									type = ID;
								}
							}
							else {
								type = UNDEFINED;
								size = 1;
							}
				}
				values = input.substr(0,size);
				Token newToken = Token(type, values, commentLine);
				tokenVector.push_back(newToken);

      	input = input.substr(size, (input.size() - 1));
				totalTokens++;
       	return Token(newToken);
			}

			else {
				type = EF;
				string values = "";
				totalTokens++;
				Token newToken = Token(type, values, lineNum);
				tokenVector.push_back(newToken);
				return newToken;
			}
    }

			void printAllTokens() {
			for (long unsigned int i = 0; i < tokenVector.size(); i++) {
				cout << tokenVector.at(i).toString() << endl;
			}
		}
			vector<Token> returnAllTokens() {
				return tokenVector;
			}
};