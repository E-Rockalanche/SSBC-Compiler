#include "LabelList.hpp"

void LabelList::define(const string label, const unsigned int address,
		const unsigned int tokenIndex){
	labels[label].define(address, tokenIndex);
}

bool LabelList::isDefined(const string label){
	return (labels[label].getAddress() >= 0);
}

void LabelList::addOccurrence(const string label, const unsigned int address,
		LabelList::Option option){
	labels[label].addOccurrence(address, option);
}

int LabelList::getAddress(const string label){
	return labels[label].getAddress();
}

LabelList::OccurrenceList LabelList::getOccurrences(const string label){
	return labels[label].getOccurrences();
}

int LabelList::getTokenIndex(const string label){
	return labels[label].getTokenIndex();
}

LabelList::UndefinedList LabelList::getUndefined(){
	UndefinedList undefinedList;
	for(map<string, Entry>::iterator it = labels.begin();
			it != labels.end(); it++){
		OccurrenceList occurrences = it->second.getOccurrences();
		for(unsigned int i = 0; i < occurrences.size(); i++){
			pair<string, unsigned int> occurrence(it->first,
				occurrences[i].first);
			undefinedList.push_back(occurrence);
		}
	}
	return undefinedList;
}