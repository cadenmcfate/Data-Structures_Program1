//program1cosc2_McFate.cpp
//
//Caden McFate
//Programming assigment 1
//COSC 2030
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "timer.h"
#include "myList.h"
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::vector;

string cleanWord(string word);

int main(void) {
	Timer timer;
	int currentCompares;
	int validCompares = 0, invalidCompares = 0, uncheckedCount = 0, invalidWords = 0, validWords = 0, largestWordSize = 0;
	ifstream inFile;
	ofstream oFile;
	string buffer;
	myList<string> dic;
	vector<string> mispelledVec;
	inFile.open("dict.txt");
	while (!inFile.eof()) {
		if (inFile >> buffer) {
			buffer = cleanWord(buffer);
			if (buffer.size() == 0) { continue; }
			if (buffer.size() > largestWordSize) { largestWordSize = buffer.size(); }
			dic.insert(buffer);
		}
	}
	inFile.close();	
	dic.sort(largestWordSize);
	//dictionary is loaded up, start timer.
	timer.Start();
	inFile.open("book.txt");
	while (!inFile.eof()) {
		if (inFile >> buffer) {
			buffer = cleanWord(buffer);
			if (buffer.size() == 0) { continue; } //empty word
			if (!isalpha(buffer[0])) { uncheckedCount++;  continue; } //starts with a non-letter
			currentCompares = dic.find(buffer);
			if (currentCompares > 0) { validWords++; validCompares += currentCompares; }
			else { invalidWords++; invalidCompares += currentCompares; mispelledVec.push_back(buffer + " "); } //find returns a negative value of compares for word-not-found
		}
	}
	invalidCompares *= -1;
	timer.Stop();
	oFile.open("misspelled.txt");
	for (int i = 0; i < mispelledVec.size(); i++) {
		oFile << mispelledVec[i] << " ";
	}
	oFile.close();
	cout << "dictionary size " << dic.getSize() << endl;
	cout << "Done checking and these are the results" << endl;
	cout << "finished in time: " << timer.Time() << endl;
	cout << "There are " << validWords << " words found in the dictionary" << endl;
	cout << "\t " << validCompares << " compares. Average: " << validCompares/validWords << endl;
	cout << "There are " << invalidWords << " words NOT found in the dictionary" << endl;
	cout << "\t " << invalidCompares << " compares. Average: " << invalidCompares/invalidWords << endl;
	cout << "There are " << uncheckedCount << " words not checked." << endl;
}


string cleanWord(string word) {
	for (int i = 0; i < word.size(); i++) {
		if (isdigit(word[i]) || int(word[i]) == int('\'') || ((int(word[i]) >= int('a')) && (int(word[i]) <= int('z')))) {
			continue; //acceptable characters
		}
		else if (isupper(word[i])) {
			word[i] = tolower(word[i]); //make everything lowercase
		}
		else {
			word.erase(i, 1); //remove the invalid character 
			i--;
		}
	}
	return word;
}
