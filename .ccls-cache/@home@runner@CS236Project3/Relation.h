#include <string>
#include <set>
#include <sstream>
using namespace std;

class Relation {

 private:
	
  string name;
  Scheme scheme;
  set<Tuple> tuples;
 public:
	string GetName(){
		return name;
	}

  Relation(const string& name, const Scheme& scheme)
    : name(name), scheme(scheme) { }

  void addTuple(const Tuple& tuple) {
    tuples.insert(tuple);
  }
 Relation select(int index, const string& value){
    Relation result(name, scheme);
    for (auto& tuple : tuples) {
      if (tuple.at(index) == value){
				result.addTuple(tuple);
				}
			}
    return result;
  }
Relation select(int index, int index2) {
    Relation result(name, scheme);
    for (auto& tuple : tuples)
      if (tuple.at(index) == tuple.at(index2)){
				result.addTuple(tuple);
				}
    return result;
  }
Relation project(vector<int> position){
	vector<string> paramNames;
	
	for (long unsigned int i = 0; i < position.size(); i++){
			paramNames.push_back(scheme.at(position.at(i)));
	}
	Scheme s = Scheme(paramNames);
	Relation result(name, s);
	//
	for (auto& i : tuples) {
		Tuple tempTuple;
		for (long unsigned int j = 0; j < position.size(); j++){
			tempTuple.push_back(i.at(position.at(j)));
		}
		result.addTuple(tempTuple);
	}
	return result;
}

Relation rename(vector<string> schemes){
	Scheme s = Scheme(schemes);
	Relation r(name, s);
	for (auto& i : tuples) {
		r.addTuple(i);
	}
	return r;
}
int getSize(){
	return tuples.size();
}
string toString() const {
    stringstream out;
    for (auto& tuple : tuples)
      out << "  " << tuple.toString(scheme) << endl;
		if (out.str() != "  \n") {
    return out.str();
			}
		else {
			return "";
		}
	}

};