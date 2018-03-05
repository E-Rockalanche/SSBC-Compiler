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

	typedef pair<unsigned int, Option> Occurrence; 
	typedef vector<Occurrence> OccurrenceList;
	typedef pair<string, unsigned int> Reference;
	typedef vector<Reference> UndefinedList;

	void clearLocal();
	void setGlobal(string label);
	void define(string label, unsigned int address);
	bool isDefined(string label);

	void addOccurrence(string label, unsigned int address,
		Option option = NONE);
	unsigned int getAddress(string label);

	OccurrenceList getOccurrences(string label);
	UndefinedList getUndefinedReferences();

private:
	class Entry{
	public:
		Entry();
		void setGlobal();
		void define(unsigned int address);
		int getAddress();
		int getTokenIndex();
		void addOccurrence(unsigned int address, Option option);
		OccurrenceList getOccurrences();
		bool isLocal();

	private:
		OccurrenceList occurrences;
		int address;
		bool local;
	};
	
	typedef map<string, Entry> EntryMap;
	EntryMap labels;
};

#endif