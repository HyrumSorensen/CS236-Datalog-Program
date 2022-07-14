#include <iostream>
#include <sstream>
#include <map>
#include <stack>


using namespace std;

class Graph {

 private:
	
  map<int,Node> nodes;
	stack<int> sortedStack;
	SCC component;
	vector<SCC> SCCVector;
	

 public:

  Graph(int size) {
    for (int nodeID = 0; nodeID < size; nodeID++)
      nodes[nodeID] = Node();
  }

	stack<int> getSorted(){
		return sortedStack;
	}

  void addEdge(int fromNodeID, int toNodeID) {
    nodes[fromNodeID].addEdge(toNodeID);
  }
	void DFSForest(){
		for (unsigned int i = 0; i < nodes.size(); i++){
			if (!nodes[i].isVisited()){
			nodes[i].visit();
			DFSForest(nodes[i]);
			sortedStack.push(i);
			}
		}	
		for (unsigned int i = 0; i < nodes.size(); i++){
			nodes[i].unVisit();
			}
	}
	
	void DFSForest(Node n){
		for (auto& adjN: n.adjacentNodes()) {
			if (!nodes[adjN].isVisited()) {
				nodes[adjN].visit();
				DFSForest(nodes[adjN]);
				sortedStack.push(adjN);
			}
		}
	}
	void findSCC(stack<int> order) {
		while (!order.empty()){
			if (!nodes[order.top()].isVisited()){
			nodes[order.top()].visit();
			findSCC(nodes[order.top()]);
			component.push_back(nodes[order.top()]);
			component.addName(order.top());
			SCCVector.push_back(component);
			component = SCC();
			}
			order.pop();
		}	
	}
	void findSCC(Node n) {
		for (auto& adjN: n.adjacentNodes()) {
			if (!nodes[adjN].isVisited()) {
				nodes[adjN].visit();
				findSCC(nodes[adjN]);
				component.push_back(nodes[adjN]);
				component.addName(adjN);
			}
		}
	}
	vector<SCC> getSCC() {
		return SCCVector;
	}
	
	string toString() {
			stringstream out;
		  for (auto& pair: nodes) {
      int nodeID = pair.first;
      Node node = pair.second;
			out << "R" << nodeID << ":" << node.toString() << endl;
    }
		return out.str();
	}

};