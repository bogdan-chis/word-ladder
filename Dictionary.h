#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using std::cout;

using std::ifstream;

using std::map;
using std::vector;
using std::string;


class Dictionary
{
private:
	map <string, vector<string>> words;
public:
	//Dictionary(const map <string, vector<string>>& _words = { {} }) : words{ _words } {};
	Dictionary() : words{  }{};

	vector<string> generatePatterns(const string& word)
	{
		vector<string> patterns = {};
		string currentPattern = "";
		for (short int i = 0; i < word.size(); i ++)
		{
			currentPattern = word;
			currentPattern[i] = '*';
			patterns.push_back(currentPattern);
		}
		return patterns;
	}

	const map <string, vector<string>>& getWords() const{ return words; };

	void add(const string& word, map <int, string>& stringMap, int& dim)
	{
		//cout << "Adding the word " << word << '\n';
		if (stringMap[dim] == "")
		{
			stringMap[dim] = word;
			dim++;
		}

		vector <string> patterns = generatePatterns(word);
		for (string pattern : patterns)
		{
			if (pattern != "") {
				words[pattern].push_back(word);
			}
		}
	}

	void readFromFile(const string& fileName, map <int, string>& stringMap, int &dim)
	{
		ifstream in(fileName);

		//cout << "Reading from file " << fileName << '\n';

		if (!in.is_open()) {
			cout << "Error opening file: " << fileName << '\n';
		}

		string word;
		while (getline(in, word))
		{
			//cout << "Reading the word " << word << '\n';
			add(word, stringMap, dim);
		}
		in.close();
	}

	void view() const
	{
		for (auto itMap = words.begin(); itMap != words.end(); ++itMap)
		{
			vector<string> words = itMap->second;
			std::cout << "The key is " << itMap->first << "\n";
			std::cout << "The words are: ";
			for (auto itVec = words.begin(); itVec != words.end(); ++itVec)
			{
				std::cout << *itVec << " -> ";
			}
			std::cout << "\n-----------------------------------------------\n";
		}
	}

	friend std::ostream& operator<< (std::ostream& os, const Dictionary& di);
};

