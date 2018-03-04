#ifndef LABEL_LIST_HPP
#define LABEL_LIST_HPP

#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;

class LabelList{
public:
	enum Option{
		NONE,
		LOW_BITS,
		HIGH_BITS,
		ADD_ONE,
	};

	typedef vector<pair<unsigned int, Option>> OccurrenceList;
	typedef vector<pair<string, unsigned int>> UndefinedList;

	void define(const string label, const unsigned int address,
		const unsigned int tokenIndex);
	bool isDefined(const string label);
	void addOccurrence(const string label, const unsigned int address,
		Option option = NONE);
	int getAddress(const string label);
	OccurrenceList getOccurrences(const string label);
	int getTokenIndex(const string label);
	UndefinedList getUndefined();
private:

	class Entry{
	public:
		Entry(){
			address = -1;
			tokenIndex = -1;
		}
		void define(const unsigned int address, const unsigned int tokenIndex){
			this->address = address;
			this->tokenIndex = tokenIndex;
			occurrences.clear();
		}
		int getAddress(){return address;}
		int getTokenIndex(){return tokenIndex;}
		void addOccurrence(const unsigned int address, Option option = NONE){
			occurrences.push_back(pair<unsigned int, Option>(address, option));
		}
		OccurrenceList getOccurrences(){return occurrences;}
	private:
		OccurrenceList occurrences;
		int address;
		int tokenIndex;
	};
	
	map<string, Entry> labels;
};

#endif