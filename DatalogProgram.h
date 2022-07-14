#pragma once
#include "Scanner.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <sstream>
#include <set>

using namespace std;

class DatalogProgram {
	private:
		vector<Predicate> schemes;
		vector<Predicate> facts;
		vector<Predicate> queries;
		vector<Rule> rules;
		set<string> domains;
	public:
		DatalogProgram(){}

		int getQuerySize(){
			return queries.size();
		}
		int getSchemeSize(){
			return schemes.size();
		}
		void schemePush(Predicate pre){
			schemes.push_back(pre);
		}
		void queryPush(Predicate pre){
			queries.push_back(pre);
		}
		void factPush(Predicate pre){
			facts.push_back(pre);
		}
		void rulePush(Rule rule){
			rules.push_back(rule);
		}
		void domainPush(string domainString){
			domains.insert(domainString);
		}
		vector<Predicate> GetSchemes(){
			return schemes;
		}
		vector<Predicate> GetFacts(){
			return facts;
		}
		vector<Predicate> GetQueries(){
			return queries;
		}
		vector<Rule> GetRules(){
			return rules;
		}
		
		string toString() {
			stringstream out;
			out << "Schemes(" << schemes.size() << "):" << endl;
			for(long unsigned int i = 0; i < schemes.size(); i++){
				if (i == 0) out << "  ";
				out <<  schemes.at(i).toString() << endl;
				if (i < schemes.size() - 1) {
					out << "  ";
				}
			}
			out << "Facts(" << facts.size() << "):" << endl;
			for(long unsigned int i = 0; i < facts.size(); i++){
				if (i == 0) out << "  ";
				out << facts.at(i).toString() << "." << endl;
				if (i < facts.size() - 1) {
					out << "  ";
				}
			}
			out << "Rules(" << rules.size() << "):" << endl;
				for (long unsigned int i = 0; i < rules.size(); i++){
					if (i == 0) out << "  ";
					out << rules.at(i).toString() << "." << endl;
					if (i < rules.size() - 1){
						out << "  ";
					}
				}
			out << "Queries(" << queries.size() << "):" << endl;
			for(long unsigned int i = 0; i < queries.size(); i++){
				if (i == 0) out << "  ";
				out << queries.at(i).toString() << "?" << endl;
				if (i < queries.size() - 1) {
					out << "  ";
				}
			}
			out << "Domain(" << domains.size() << "):";
			 if (domains.size() != 0){
				out << endl << "  ";
			}
			set<string>::iterator it;
			for (it=domains.begin(); it!= domains.end();) {
				out << *it;
				it++;
				if (it != domains.end()) {
					out << endl << "  ";
				}
			}
			out << endl;


			
			return out.str();
		}
};
