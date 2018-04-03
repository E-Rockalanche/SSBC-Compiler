#include "LabelList.hpp"

void LabelList::clearLocal(){
	EntryMap::iterator it = labels.begin();
	while(it != labels.end()){
		if ((it->second.getAddress() >= 0) && (it->second.isLocal())){
			EntryMap::iterator victim = it;
			it++;
			labels.erase(victim);
		}else{
			it++;
		}
	}
}

void LabelList::setGlobal(string label){
	labels[label].setGlobal();
}

void LabelList::define(string label, unsigned int address){
	labels[label].define(address);
}

bool LabelList::isDefined(string label){
	return (labels[label].getAddress() >= 0);
}

void LabelList::addOccurrence(string label, unsigned int address,
		int option){
	labels[label].addOccurrence(address, option);
}

unsigned int LabelList::getAddress(string label){
	return labels[label].getAddress();
}

LabelList::OccurrenceList LabelList::getOccurrences(string label){
	return labels[label].getOccurrences();
}

LabelList::UndefinedList LabelList::getUndefinedReferences(){
	UndefinedList undefinedList;
	for(EntryMap::iterator it = labels.begin();
			it != labels.end(); it++){
		OccurrenceList occurrences = it->second.getOccurrences();
		for(unsigned int i = 0; i < occurrences.size(); i++){
			Reference ref(it->first,
				occurrences[i].first);
			undefinedList.push_back(ref);
		}
	}
	return undefinedList;
}





LabelList::Entry::Entry(){
	address = -1;
	local = true;
}

void LabelList::Entry::setGlobal(){
	local = false;
}

void LabelList::Entry::define(unsigned int address){
	this->address = address;
	occurrences.clear();
}

int LabelList::Entry::getAddress(){
	return address;
}

void LabelList::Entry::addOccurrence(unsigned int address, int option = NONE){
	occurrences.push_back(Occurrence(address, option));
}

LabelList::OccurrenceList LabelList::Entry::getOccurrences(){
	return occurrences;
}

bool LabelList::Entry::isLocal(){
	return local;
}