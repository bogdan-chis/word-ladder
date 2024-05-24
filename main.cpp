#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <set>


#include "TestNode.h"
#include "TestGraph.h"
#include "Dictionary.h"

#include <Windows.h>
#include <ctime>
#include <chrono>

using namespace std;


void runTestNode()
{
	TestNode tn;
	tn.testEqOperator();
	tn.testGetInfo();
	tn.testGetIdx();
	tn.testSetInfo();
	cout << "Testing Node: DONE\n";
	cout << "-----------------------------------------------------\n";
}

void runTestGraph()
{
	TestGraph tg;
	tg.testGetInbounds();
	tg.testSetInbounds();
	tg.testIsEdge();
	tg.testAddEdge();
	cout << "Testing Graph: DONE\n";
	cout << "-----------------------------------------------------\n";
}

void runAllTests()
{
	runTestNode();
	runTestGraph();
}



void readFromFiles(Dictionary& d, int limit, map <int, string>& stringMap)
{
	string fileName = "";
	int dim = 0;
	for (int i = 1; i <= limit; i++)
	{
		fileName = "";
		fileName += std::to_string(i) + ".txt";
		d.readFromFile(fileName, stringMap, dim);
	}
	d.readFromFile("27.txt", stringMap, dim);
	d.readFromFile("29.txt", stringMap, dim);
}

void readFromFile(Dictionary& d, int fileNum, map <int, string>& stringMap, int &dim)
{
	string fileName = "";
	fileName += std::to_string(fileNum) + ".txt";
	d.readFromFile(fileName, stringMap, dim);
}

void createGraphFromDictionary(Graph<string>& g, const Dictionary d, map<string, int> intMap)
{
	map <string, vector<string>> words = d.getWords();
	for (auto itMap = words.begin(); itMap != words.end(); ++itMap)
	{
		vector<string> currentWords = itMap->second;
		for (auto itVec1 = currentWords.begin(); itVec1!= currentWords.end(); ++itVec1)
		{
			Node<string> source(intMap[(*itVec1)], (*itVec1));
			for (auto itVec2 = itVec1 + 1; itVec2 != currentWords.end(); ++itVec2)
			{
				Node<string> dest(intMap[(*itVec2)], (*itVec2));
				g.addEdge(source, dest);
			}
		}
	}
}



void printMenu()
{
	cout << "\n-------------------\n";
	cout << "0. Exit\n";
	cout << "1. Automatic mode\n";
	cout << "2. Playing mode\n";
	cout << "3. Analytics mode\n";
	cout << "-------------------\n";
}

void getOperation(int &op, int limit)
{
	cout << "Please enter a valid option: ";
	cin >> op;
	if (op < 0 || op > limit)
		return getOperation(op, limit);
}

void getPlayerName(string& playerName)
{
	cout << "Please enter your name: ";
	cin >> playerName;
	return;
}

void getWord(string& word, map<string, int> intMap)
{
	cout << "Please enter a valid word: ";
	cin >> word;
	try {
		// throws error if intMap[error] does not exist
		int id = intMap[word];
		cout << "Id of word " << word << " is " << id << '\n';
	}
	catch (...)
	{
		cout << "Invalid word. '"<< word<< "' was not found in the dictionary\n";
		getWord(word, intMap);
	}
}

void getDimension(int& d)
{
	cout << "Please enter the number of letters: ";
	cin >> d;

	if (d < 1 || (d > 25 && (d != 27 && d != 29)))
	{
		cout << "Invallid word dimension\n";
		getDimension(d);
	}
}

void selectNrOfLetters(int& nrOfLetters)
{
	cout << "Please enter the number of letters: ";
	cin >> nrOfLetters;
}

void viewSol(vector<int> sol, map<int, string> stringMap)
{
	
	cout << "\tThis is the path:\n\t";
	cout << stringMap[sol[0]];
	for (int i = 1; i < sol.size(); i ++)
	{
		cout << " -> " << stringMap[sol[i]];
	}
	cout << '\n';
}


void saveCurrentDateTimeToFile(const string& filename) {
	// Get the current time
	std::time_t currentTime = std::time(nullptr);

	// Convert the time to a string representation
	std::string timeString = std::ctime(&currentTime);

	// Open the file
	std::ofstream file(filename, std::ios::app);

	// Check if the file is opened successfully
	if (file.is_open()) {
		// Write the time string to the file
		file << timeString;
		//cout << "Current date and time saved to " << filename << std::endl;
	}
	else {
		std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
	}

	// Close the file
	file.close();
}

void saveToFile(const std::string& filename, const std::vector<int>& userSol, const std::vector<int>& sol, const Node<std::string>& startNode, const Node<std::string>& endNode, const std::map<int, std::string>& stringMap, const std::string& playerName, int hints) {
	std::time_t currentTime = std::time(nullptr);

	string timeString = std::ctime(&currentTime);

	// Open the file in append mode
	ofstream outputFile(filename, std::ios::app);

	// Check if the file is opened successfully
	if (!outputFile.is_open()) {
		std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
		return;
	}

	// Write the time string to the file
	outputFile << timeString;

	// Write the current data to the file
	outputFile << '\t' << playerName << "'s Game Data\n\n";
	outputFile << "Start word: { " << startNode.getInfo() << " }\n";
	outputFile << "End word: { " << endNode.getInfo() << " }\n";
	outputFile << "Hints used: " << hints << '\n';

	outputFile << "Words used: ";
	for (size_t i = 0; i < userSol.size(); i++) {
		outputFile << stringMap.at(userSol[i]);
		if (i != userSol.size() - 1) {
			outputFile << " -> ";
		}
	}
	outputFile << '\n';

	// -1 because the first move is the start element
	outputFile << "\n\t" << playerName << " did a total number of " << userSol.size() - 1 << " moves\n";
	outputFile << "\tThe optimal number of moves was " << sol.size() - 1 << " moves\n";

	outputFile << "\n------------------------------------------------------------------------\n";

	cout << "Game data saved to file " << filename << '\n';

	outputFile.close();
}

void showHint(Node<string> currentNode, Node<string> nextNode)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	string currentInfo = currentNode.getInfo();
	string nextInfo = nextNode.getInfo();

	int size = currentInfo.size();
	cout << "\nThis is the hint:\n";
	for (int i = 0; i < size; i++)
	{
		if (currentInfo[i] != nextInfo[i]) {
			SetConsoleTextAttribute(hConsole, 12);
			cout << nextInfo[i];
			SetConsoleTextAttribute(hConsole, 7);
		}
		else {
			cout << nextInfo[i];
		}
	}
	cout << '\n';
}

void getMove(Node<string> currentNode, Node<string> endNode, vector<int> sol, map<int, string> stringMap, map<string, int> intMap, Node<string>& moveNode, Graph<string> g, int nrOfLetters, int& hints, bool hint = false)
{
	if (hint)
	{
		hints++;
		sol = g.Dijkstra(currentNode, endNode);

		Node<string> nextNode;
		for (int it = 0; it < sol.size(); it ++)
		{
			if (sol[it] == currentNode.getIdx())
			{
				nextNode.setInfo(stringMap[sol[it + 1]]);
				nextNode.setIdx(intMap[nextNode.getInfo()]);
			}
		}
		showHint(currentNode, nextNode);
	}

	cout << "\nPlease enter a valid word: ";
	string word;
	cin >> word;

	try {
		if (word.size() != nrOfLetters)
		{
			throw std::runtime_error("\nInvalid word. It should have " + std::to_string(nrOfLetters) + " letters\n");
		}
		else
		{
			moveNode = g.findNode(word);
			if (!(g.isEdge(currentNode, moveNode)))
			{
				// there is no edge
				throw  std::runtime_error("\nInvalid word. You cannot go from { " + currentNode.getInfo() + " } to { " + word + " }\n");
			}
			else {
				// there is an edge but the move is not correct
				if (moveNode == endNode)
				{
					cout << "Congratulations. You have completed the game\n";
					return;
				}
				vector<int> newSol = g.Dijkstra(moveNode, endNode);
				cout << "\n\tYour move is correct\n";
			}
		}
	}
	catch (std::runtime_error e)
	{
		cout << e.what();
		cout << "\nDo you want to use a hint? [y/n]: ";
		char c;
		cin >> c;
		if (tolower(c) == 'y')
			hint = true;
		else
			hint = false;
		getMove(currentNode, endNode, sol, stringMap, intMap, moveNode, g, nrOfLetters, hints, hint);
	}
}

void playGame(Node<string> currentNode, Node<string> endNode, vector<int> sol, map<int, string> stringMap, map<string, int> intMap, Graph<string> g, int nrOfLetters, vector<int>& userSol, int& hints)
{

	//viewSol(sol, stringMap);
	// agni -> anni -> anti -> acti -> acta -> alta -> alba -> abba -> abra -> aura -> dura -> duma -> yuma ->
	Node<string> moveNode;
	getMove(currentNode, endNode, sol, stringMap, intMap, moveNode, g, nrOfLetters, hints);
	
	userSol.push_back(moveNode.getIdx());

	if (moveNode == endNode)
		return;
	playGame(moveNode, endNode, sol, stringMap, intMap, g, nrOfLetters, userSol, hints);
}


int computeMinutesDifference(const string& dateStr1, const string& dateStr2) {
	// Parse date strings into tm structures
	std::tm tm1 = {}, tm2 = {};
	std::istringstream ss1(dateStr1), ss2(dateStr2);
	ss1 >> std::get_time(&tm1, "%a %b %d %T %Y");
	ss2 >> std::get_time(&tm2, "%a %b %d %T %Y");

	// Convert tm structures to time_t values
	std::time_t time1 = std::mktime(&tm1);
	std::time_t time2 = std::mktime(&tm2);

	// Calculate the difference in seconds
	std::time_t difference = std::difftime(time2, time1);

	// Convert difference to minutes (rounding to nearest minute)
	int minutes = static_cast<int>(std::round(difference / 60.0));

	return minutes;
}

bool loadUserData(const string filename, std::vector<string>& moves) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file " << filename << std::endl;
		return false;
	}

	string line;
	string move;
	while (std::getline(file, line)) {
		if (line.empty()) {
			moves.push_back(move);
			move.clear();
		}
		else {
			move += line + '\n';
		}
	}
	if (!move.empty()) {
		moves.push_back(move);
	}

	file.close();
	return true;
}

// Function to compute statistics
void computeStatistics(const vector<string> moves) {
	std::set<string> uniqueWords;
	int totalMoves = 0;
	int totalOptimalMoves = 0;

	for (const auto& move : moves) {
		std::istringstream iss(move);
		string word;
		while (iss >> word) {
			if (word == "Words" && (iss >> word) && word == "used:") {
				while (iss >> word) {
					if (word != "->")
						uniqueWords.insert(word);
				}
			}
			else if (word == "did") {
				if ((iss >> word) && word == "a" && (iss >> word) && word == "total") {
					if ((iss >> word) && word == "number" && (iss >> word) && word == "of") {
						if ((iss >> word)) {
							totalMoves += std::stoi(word);
						}
					}
				}
			}
			else if (word == "optimal") {
				if ((iss >> word) && word == "number" && (iss >> word) && word == "of" && (iss >> word) && word == "moves" 
						&& (iss >> word) && word == "was") {
					if ((iss >> word)) {
						totalOptimalMoves += std::stoi(word);
					}
				}
			}  
		}
	}
	
	cout << "\tNumber of unique words used: " << uniqueWords.size() << std::endl;
	cout << "\tTotal number of moves: " << totalMoves << std::endl;
	cout << "\tTotal number of optimal moves: " << totalOptimalMoves << std::endl;
}

void engine()
{
	int operationsLimit = 3;
	Graph<string> g;
	Dictionary d;

	cout << "\t\tWelcome to WORD LADDER: THE GAME";
	while (true)
	{
		try {
			printMenu();
			int op;
			getOperation(op, operationsLimit);

			if (op == 0)
			{
				return;
			}
			else if (op == 1)
			{
				int dimensionRandomCoeff = 6;
				// temporary 

				cout << "Welcome to AUTOMATIC MODE. Here, both nodes were chosen by you\n";
				
				int dimension;
				getDimension(dimension);
				
				int nrOfWords = 0;
				map <int, string> stringMap;
				readFromFile(d, dimension, stringMap, nrOfWords);

				map<string, int> intMap;
				for (auto it : stringMap)
					intMap[it.second] = it.first;
				createGraphFromDictionary(g, d, intMap);


				string startWord;
				getWord(startWord, intMap);

				string endWord;
				getWord(endWord, intMap);

				Node<string> startNode(intMap[startWord], startWord);
				Node<string> endNode(intMap[endWord], endWord);


				cout << "\n\tThe starting node is " << startNode << '\n';
				cout << "\tThe end node is " << endNode << '\n';

				vector<int> sol = g.Dijkstra(startNode, endNode);
				viewSol(sol, stringMap);
			}
			else if (op == 2)
			{
				string playerName;
				getPlayerName(playerName);

				int nrOfLetters;
				int nrOfWords = 0;
				selectNrOfLetters(nrOfLetters);

				map <int, string> stringMap;
				readFromFile(d, nrOfLetters, stringMap, nrOfWords);
				map<string, int> intMap;
				for (auto it : stringMap)
					intMap[it.second] = it.first;
				createGraphFromDictionary(g, d, intMap);

				Node<string> startNode;
				Node<string> endNode;
				vector<int> sol;

				
				bool validPath;
				do
				{
					validPath = true;

					int startNumber = rand() % nrOfWords + 1;
					int endNumber = rand() % nrOfWords + 1;

					startNode = Node<string> (startNumber, stringMap[startNumber]);
					endNode = Node<string> (endNumber, stringMap[endNumber]);

					try {
						sol = g.Dijkstra(startNode, endNode);
					}
					catch (std::runtime_error e)
					{
						cout << e.what() << '\n';
						cout << "Generating another example...\n";
						validPath = false;
					}
				} while (!validPath);

				cout << "We have chosen two random nodes:\n";

				cout << "\tThe starting node is " << startNode << '\n';
				cout << "\tThe end node is " << endNode << '\n';

				string filename = "";
				filename += playerName + ".txt";

				saveCurrentDateTimeToFile(filename);
				cout << "Your task is to get from { " << startNode.getInfo() << " } to { " << endNode.getInfo() << " }\n";
				viewSol(sol, stringMap);

				vector<int> userSol;
				userSol.push_back(startNode.getIdx());
				int hints = 0;
				
				playGame(startNode, endNode, sol, stringMap, intMap, g, nrOfLetters, userSol, hints);
				

				saveToFile(filename, userSol, sol, startNode, endNode, stringMap, playerName, hints);
			}
			else if (op == 3)
			{
				// Unique words
				// Time spent playing
				// Total number of moves
				// Longest and shortest Moves
				// Average move lenght

				string username;
				getPlayerName(username);

				string filename = "";
				filename += username + ".txt";
				std::vector<std::string> moves;
				if (loadUserData(filename, moves)) {
					computeStatistics(moves);
				}
			}

		}
		catch (std::runtime_error e)
		{
			cout << "Error: " << e.what() << '\n';
		}
		catch (...)
		{
			cout << "Another error occured\n";
		}
	}
}

void myMain()
{
	Graph<string> g;
	Dictionary d;
	map <int, string> stringMap;
	int dim = 0;
	readFromFile(d, 4, stringMap, dim);

	map<string, int> intMap;
	for (auto it : stringMap)
		intMap[it.second] = it.first;


	createGraphFromDictionary(g, d, intMap);
	cout << g.getN() << " vertices and " << g.getM() << " edges\n";

	// afar five
	Node<string> start = g.findNode("afar");
	Node<string> end = g.findNode("five");

	cout << start << '\n' << end << '\n';
	vector<int> sol = g.Dijkstra(start, end);

	for (auto it : sol)
	{
		cout << stringMap[it] << " -> ";
	}
}

int main()
{
	engine();
	return 0;
}