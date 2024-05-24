#include "TestGraph.h"

void TestGraph::testGetInbounds()
{
	cout << "Testing Get Inbounds ... \n";
	map<string, vector<Node<string>>> stringData = {
		{"*NA", {Node<string>(1, "ANA"), Node<string>(2, "ENA")}},
		{"A*A", {Node<string>(1, "ANA"), Node<string>(3, "ARA")}},
		{"AN*", {Node<string>(1, "ANA"), Node<string>(4, "ANI")}}
	};
	Graph<string> g(stringData);
    auto stringResult = g.getInbounds();
	assert(stringResult == stringData);




    std::map<int, std::vector<Node<int>>> intData = {
        {1, {Node<int>(1, 10), Node<int>(2, 20)}},
        {2, {Node<int>(3, 30)}},
        {3, {Node<int>(1, 40)}}
    };

    Graph<int> graph(intData);
    auto intResult = graph.getInbounds();
    assert(intResult.size() == intData.size());
    assert(intResult == intData);
}

void TestGraph::testSetInbounds()
{
    cout << "Testing Set Inbounds ... \n";
    map<int, vector<Node<int>>> intData = {
       {1, {Node<int>(1, 10), Node<int>(2, 20)}},
       {2, {Node<int>(3, 30)}},
       {3, {Node<int>(1, 40)}}
    };

    Graph<int> graph(intData);
    auto intResult = graph.getInbounds();
    assert(intResult == intData);

    std::map<int, std::vector<Node<int>>> intData2 = {
       {1, {Node<int>(1, 100), Node<int>(2, 200)}},
       {2, {Node<int>(3, 300)}},
       {3, {Node<int>(1, 400)}}
    };

    graph.setInbounds(intData2);
    
    auto intResult2 = graph.getInbounds();
    assert(intResult2 == intData2);
}

void TestGraph::testIsEdge()
{
    cout << "Testing Is Edge ... \n";
    map<int, vector<Node<int>>> intData = {
       {10, {Node<int>(2, 20), Node<int>(3, 30)}},
       {20, {Node<int>(1, 10)}},
       {30, {Node<int>(1, 10)}}
    };
    Node<int> n1(1, 10);
    Node<int> n2(2, 20);
    Node<int> n3(3, 30);
    Node<int> n4(4, 40);
    Graph<int> intG(intData);

    assert(intG.isEdge(n1, n2));
    assert(intG.isEdge(n3, n1));
    assert(!(intG.isEdge(n2, n4)));
    assert(intG.isEdge(n2, n2));
    assert(intG.isEdge(n1, n3));
}

void TestGraph::testAddEdge()
{
    cout << "Testing Add Edge... \n";
    Node<int> n1(1, 10);
    Node<int> n2(2, 20);
    Node<int> n3(3, 30);
    Node<int> n4(4, 40);

    map<int, vector<Node<int>>> intData = {
      {10, {n2, n3}},
      {20, {n1}},
      {30, {n1}},
    };

    Graph<int> intG(intData);

    intG.addEdge(n1, n2);
    intG.addEdge(n1, n3);
    intG.addEdge(n1, n4);
    intG.addEdge(n4, n3);
    intG.addEdge(n4, n2);

    map<int, vector<Node<int>>> expResult = {
        {10, {n2, n3, n4}},
        {20, {n1, n4}},
        {30, {n1, n4}},
        {40, {n1, n3, n2}}
    };
    Graph<int> expGraph(expResult, 6);

    //cout << intG << '\n';
    //cout << expGraph << '\n';
    assert(intG == expGraph);
}

void TestGraph::testUCS()
{
    return;
}