#pragma once

#include "Node.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <utility>

using std::map;
using std::vector;
using std::pair;
using std::queue;


template <typename T>
class Graph
{
private:
	map<T, vector<Node<T>>> inbounds;
	unsigned int n;
	unsigned int m;
public:
	Graph(const map<T, vector<Node<T>>>& _inbounds = { {} }, unsigned int _m = 0) : inbounds{ _inbounds }, n{ static_cast<unsigned int> (inbounds.size()) }, m{ _m } {};

	map<T, vector<Node<T>>> getInbounds() const { return inbounds; };

	unsigned int getN() const { return n; };

	unsigned int getM() const { return m; };

	void setInbounds(map<T, vector<Node<T>>>& _inbounds) { inbounds = _inbounds; };

	bool isEdge(Node<T> source, Node<T> dest)
	{
		if (source == dest)
			return true;
		if (inbounds[source.getInfo()].empty() || inbounds[dest.getInfo()].empty())
			return false;



		bool firstEdge = false;
		bool secondEdge = false;

		vector<Node<T>>& sourceNeighbours = inbounds[source.getInfo()];
		vector<Node<T>>& destNeighbours = inbounds[dest.getInfo()];

		for (auto itVec = sourceNeighbours.begin(); itVec != sourceNeighbours.end() && !firstEdge; ++itVec)
		{
			if ((*itVec) == dest)
				firstEdge = true;
		}

		for (auto itVec = destNeighbours.begin(); itVec != destNeighbours.end() && !secondEdge; ++itVec)
		{
			if ((*itVec) == source)
				secondEdge = true;
		}
		return firstEdge && secondEdge;
	}

	void addEdge(Node<T> source, Node<T> dest)
	{
		if (isEdge(source, dest))
		{
			return;
			// std::cout << "An edge between " << source << " and " << dest << " already exists.\n";
		}
		else
		{
			if (inbounds[source.getInfo()].empty())
				n++;
			if (inbounds[dest.getInfo()].empty())
				n++;

			inbounds[source.getInfo()].push_back(dest);
			inbounds[dest.getInfo()].push_back(source);
			m += 2;
		}
	}

	Node<T> findNode(T info)
	{
		Node<T> sol;
		bool found = false;

		for (const auto& entry : inbounds) {
			for (const auto& currentNode : entry.second) {
				if (currentNode.getInfo() == info) {
					sol = currentNode;
					found = true;
					break; // Exit the inner loop since we found the node
				}
			}
			if (found) {
				break; // Exit the outer loop if we found the node
			}
		}

		if (!found) {
			// Node with the specified info not found
			throw std::runtime_error ("Node with info " + info + " not found.\n");
		}
		return sol;
	}

	vector<int> Dijkstra(Node<T> node1, Node<T> node2)
	{
		vector<int> sol; //current solution
		queue<Node<T>> q;


		int mindist[10000];
		int prev[10000];


		for (int i = 0; i < 10000; i++)
			mindist[i] = 0xffffff, prev[i] = -1;

		mindist[node1.getIdx()] = 0;
		q.push(node1);

		while (!q.empty()) {
			Node<T> currentNode = q.front();
			q.pop();
			for (auto neighbour : inbounds[currentNode.getInfo()]) {
				if (mindist[neighbour.getIdx()] > mindist[currentNode.getIdx()] + 1)
					mindist[neighbour.getIdx()] = mindist[currentNode.getIdx()] + 1, q.push(neighbour), prev[neighbour.getIdx()] = currentNode.getIdx();
			}
		}
		int currentIdx = node2.getIdx();
		if (prev[currentIdx] == -1)
			throw std::runtime_error("There is no path.");

		while (currentIdx != -1) {
			sol.push_back(currentIdx);
			currentIdx = prev[currentIdx];
		}
		std::reverse(sol.begin(), sol.end());
		return sol;
	}

	template <typename U>
	friend bool operator==(const Graph<U>&left, const Graph<U>&right);

	friend std::ostream& operator<<(std::ostream & os, const Graph<T>&g)
		{
			os << "This is a graph with " << g.n << " vertices " << " and " << g.m << " edges\n";
			for (const auto& entry : g.inbounds) {
				os << "Vertex " << entry.first << " has inbound nodes: ";
				for (const auto& node : entry.second) {
					os << node << " ";
				}
				os << "\n-------------------------------------------------\n";
			}
			return os;
		}
};

template <typename U>
bool operator==(const Graph<U>& left, const Graph<U>& right) {
	return (left.inbounds == right.inbounds) && (left.n == right.n) && (left.m == right.m);
}