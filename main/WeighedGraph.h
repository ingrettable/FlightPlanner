#pragma once

#include <map>
#include <queue>
using namespace std;

class WeightedEdge {
private:
	wstring node1;
	wstring node2;
	float weight;

public:
	WeightedEdge(wstring initNode1, wstring initNode2, float initWeight) {
		this->node1 = initNode1;
		this->node2 = initNode2;
		this->weight = initWeight;
	}
	~WeightedEdge() {
		// NO POINTERS TO CLEAN UP
	}

	wstring getNode1() { return node1; }
	wstring getNode2() { return node2; }
	float getWeight() { return weight; }
};

template <typename T> 
class WeightedGraph {
private:
	std::map<wstring, T*> nodes;
	std::map<wstring, WeightedEdge*> edges;

public:
	WeightedGraph() {}

	void getKeys(vector<wstring>* keys) {
		for (const auto& keyPair : nodes) {
			wstring key = keyPair.first;
			keys->push_back(key);
		}
	}

	bool nodeExists(wstring testNode) {
		return this->nodes.count(testNode) > 0;
	}

	wstring getEdgeId(wstring node1, wstring node2) {
		return node1 + L"-" + node2;
	}

	void addNode(wstring nodeId, T* nodeData) {
		this->nodes[nodeId] = nodeData;
	}

	T* getNodeData(wstring nodeId) {
		return this->nodes[nodeId];
	}

	void addEdge(wstring node1, wstring node2, float weight) {
		wstring edgeId = this->getEdgeId(node1, node2);
		this->edges[edgeId] = new WeightedEdge(node1, node2, weight);
	}

	void removeEdge(wstring node1, wstring node2) {
		wstring edgeId = this->getEdgeId(node1, node2);
		WeightedEdge* edge = this->edges[edgeId];
	}

	bool hasNeighbor(wstring node1, wstring node2) {
		wstring edgeId = this->getEdgeId(node1, node2);
		return this->edges[edgeId] != this->edges.end();
	}

	float getNeighborWeight(wstring node1, wstring node2) {
		if (hasNeighbor(node1, node2)) {
			wstring edgeId = this->getEdgeId(node1, node2);
			return this->edges[edgeId]->getWeight();
		}
		return 0.0f;
	}

	void findPath(vector<wstring>* path, wstring node1, wstring node2) {
		//wcout << L"Finding path from " << node1 << L" to " << node2 << endl;
		queue<wstring> q;
		map<wstring, wstring> parent;
		q.push(node1);
		parent[node1] = L"";
		while (!q.empty()) {
			wstring current = q.front();
			q.pop();
			if (current == node2) {
				break;
			}
			vector<wstring> neighbors;
			for (const auto& e : edges) {
				WeightedEdge* edge = e.second;
				if (edge->getNode1() == current && parent.count(edge->getNode2()) == 0) {
					q.push(edge->getNode2());
					parent[edge->getNode2()] = current;
				}
				else if (edge->getNode2() == current && parent.count(edge->getNode1()) == 0) {
					q.push(edge->getNode1());
					parent[edge->getNode1()] = current;
				}
			}
		}
		if (parent.count(node2) == 0) {
			return;
		}
		wstring current = node2;
		while (current != L"") {
			path->push_back(current);
			current = parent[current];
		}
		reverse(path->begin(), path->end());
	}
};