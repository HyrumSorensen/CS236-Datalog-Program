#include <string>
#include <set>
#include <sstream>
#include <algorithm>
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
int GetSize(){
	return tuples.size();
}
static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
		       const Tuple& leftTuple, const Tuple& rightTuple) {
	  for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
      const string& leftName = leftScheme.at(leftIndex);
      const string& leftValue = leftTuple.at(leftIndex);
			    for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
      const string& rightName = rightScheme.at(rightIndex);
      const string& rightValue = rightTuple.at(rightIndex);
      if(rightName == leftName && leftValue != rightValue) {
				return false;
			}
    }
   }
    return true;
}
Relation join(Relation& r) {
		const Scheme& leftScheme = scheme;
    const Scheme& rightScheme = r.scheme;
    vector<string> newScheme = leftScheme;
    vector<int> indexs;
    for (long unsigned int i = 0; i < rightScheme.size(); i++) {
      if (find(leftScheme.begin(), leftScheme.end(), rightScheme.at(i)) == leftScheme.end()) {
        newScheme.push_back(rightScheme.at(i));
        indexs.push_back(i);
      }
    }

    Scheme s = Scheme(newScheme);
    string newName = name + r.GetName();
    Relation newR = Relation(newName, s);

    for (const Tuple& leftTuple : tuples) {
      for (const Tuple& rightTuple : r.tuples) {
        if (joinable(leftScheme, rightScheme, leftTuple, rightTuple)) {
          Tuple newTuple = leftTuple;
          for (unsigned int k = 0; k < indexs.size(); k++) {
            newTuple.push_back(rightTuple.at(indexs.at(k)));
          }
          newR.addTuple(newTuple);
        }
      }
    }
    return newR;
	}

	bool relationUnion(Relation r) {
		for (auto& tuple : r.tuples) {
			if (tuples.find(tuple) == tuples.end()) {
			addTuple(tuple);
			cout << "  " << tuple.toString(scheme) << endl;
			}
		}
		return true;
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
Scheme GetScheme() {
	return scheme;
}

};