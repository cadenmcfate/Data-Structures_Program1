//program1cosc2_McFate.cpp
//Spellchecks the contents of book.txt against the contents of dict.txt
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
	//storing the dictionary in a linked list
	inFile.open("dict.txt"); 
	while (!inFile.eof()) {
		if (inFile >> buffer) {
			buffer = cleanWord(buffer);
			if (buffer.size() == 0) { continue; }
			if (buffer.size() > largestWordSize) { largestWordSize = buffer.size(); } //getting the length of the longest word for sorting.
			dic.insert(buffer);
		}
	}
	inFile.close();	
	dic.sort(largestWordSize); //sorting the dictionary by increasing word length.
	//dictionary is loaded up and sorted, start timer.
	timer.Start();
	inFile.open("book.txt");
	while (!inFile.eof()) {
		if (inFile >> buffer) {
			buffer = cleanWord(buffer);
			if (buffer.size() == 0) { continue; } //empty word
			if (!isalpha(buffer[0])) { uncheckedCount++;  continue; } //starts with a non-letter
			currentCompares = dic.find(buffer);
			if (currentCompares > 0) { validWords++; validCompares += currentCompares; } //currentCompares is a positive value if the word was found in the dictionary.
			else { invalidWords++; invalidCompares += currentCompares; mispelledVec.push_back(buffer); } //currentCompares is a negative value if the word wasn't found.
		}
	}
	invalidCompares *= -1; //adjusting invalidCompares to be positive.
	timer.Stop();
	oFile.open("misspelled.txt"); //writing all the misspelled words to misspelled.txt
	for (int i = 0; i < mispelledVec.size(); i++) {
		oFile << mispelledVec[i] << endl;
	}
	oFile.close();
	cout << "dictionary size " << dic.getSize() << endl; //results
	cout << "Done checking and these are the results" << endl;
	cout << "finished in time: " << timer.Time() << endl;
	cout << "There are " << validWords << " words found in the dictionary" << endl;
	cout << "\t " << validCompares << " compares. Average: " << validCompares/validWords << endl;
	cout << "There are " << invalidWords << " words NOT found in the dictionary" << endl;
	cout << "\t " << invalidCompares << " compares. Average: " << invalidCompares/invalidWords << endl;
	cout << "There are " << uncheckedCount << " words not checked." << endl;
	return 0;
}


string cleanWord(string word) {
	for (int i = 0; i < word.size(); i++) {
		if (isdigit(word[i]) || int(word[i]) == int('\'') || ((int(word[i]) >= int('a')) && (int(word[i]) <= int('z')))) {
			continue; //acceptable characters. digits, apostrophes, and lowercase letters.
		}
		else if (isupper(word[i])) {
			word[i] = tolower(word[i]); //uppercase to lowercase
			continue;
		}
		else {
			word.erase(i, 1); //remove the invalid character 
			i--;
		}
	}
	return word;
}
