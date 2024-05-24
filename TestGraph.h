#pragma once
#include "Graph.h"
#include <iostream>
#include <cassert>

#include <map>
#include <vector>
#include <string>

using std::map;
using std::vector;
using std::string;

using std::cout;

class TestGraph
{
public:
	void testGetInbounds();
	void testSetInbounds();
	void testIsEdge();
	void testAddEdge();
	void testUCS();
};

