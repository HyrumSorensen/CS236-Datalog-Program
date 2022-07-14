#include <iostream>



using namespace std;

class SCC : public vector<Node> {
	private:
		vector<int> idNames;

	public:
		SCC() {}
		void addName(int name){
			idNames.push_back(name);
		}
		vector<int> getName() {
			return idNames;
		}

};