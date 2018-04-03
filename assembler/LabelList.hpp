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
		LOW_BITS = -3,
		HIGH_BITS = -2,
		ADD_ONE = -1,
		NONE = 0,
		//>0 with offset
	};

	typedef pair<unsigned int, int> Occurrence; 
	typedef vector<Occurrence> OccurrenceList;
	typedef pair<string, unsigned int> Reference;
	typedef vector<Reference> UndefinedList;

	void clearLocal();
	void setGlobal(string label);
	void define(string label, unsigned int address);
	bool isDefined(string label);

	void addOccurrence(string label, unsigned int address,
		int option = NONE);
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
		void addOccurrence(unsigned int address, int option);
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