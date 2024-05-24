#include "TestNode.h"

void TestNode::testEqOperator()
{
	std::cout << "Testing Operator == ...\n";
	Node<int> n1(1, 1);
	Node<int> n2(1, 1);
	Node<int> n3(3, 2);

	Node<std::string> n4(4, "A");
	Node<std::string> n5(4, "A");

	assert(n1 == n2);
	assert(!(n1 == n3));
	assert(n4 == n5);
}

void TestNode::testGetInfo()
{
	std::cout << "Testing Get Info...\n";
	Node<int> n1(1, 2);
	assert(n1.getInfo() == 2);

	Node<std::string> n2(2, "A");
	assert(n2.getInfo() == "A");
}

void TestNode::testGetIdx()
{
	std::cout << "Testing Get Index ... \n";
	Node<int> n1(1, 1);
	Node<std::string>n2(2, "A");
	Node<double>n3(3, 3.14156);

	assert(n1.getIdx() == 1);
	assert(n2.getIdx() == 2);
	assert(n3.getIdx() == 3);
}

void TestNode::testSetInfo()
{
	std::cout << "Testing Set Info ... \n";
	Node<int> n1(1, 1);
	Node<std::string>n2(2, "A");
	Node<double>n3(3, 3.14156);

	n1.setInfo(2);
	n2.setInfo("B");
	n3.setInfo(2.71);

	assert(n1.getInfo() == 2);
	assert(n2.getInfo() == "B");
	assert(n3.getInfo() == 2.71);

}