#include "searcheng.h"
#include <set>

using namespace std;

// Place your function implementations for your derived
// WebPageSetCombiner classes here
WebPageSet ANDCombine::combine(const WebPageSet& setA, const WebPageSet& setB){
	WebPageSet temp;
	for(set<WebPage*>::iterator it = setB.begin(); it != setB.end(); ++it) {
		if((setA.find(*it) != setA.end() || setA.size() == 0) && 
			temp.find(*it) == temp.end()) {
			temp.insert(*it);
		}
	}
	return temp;
}

WebPageSet ORCombine::combine(const WebPageSet& setA, const WebPageSet& setB){
	WebPageSet temp = setA;
	for(set<WebPage*>::iterator it = setB.begin(); it != setB.end(); ++it) {
		if(setA.find(*it) == setA.end() && temp.find(*it) == temp.end()) {
			temp.insert(*it);
		}
	}
	return temp;	
}

WebPageSet DIFFCombine::combine(const WebPageSet& setA, const WebPageSet& setB){
	WebPageSet temp = setA;
	for(set<WebPage*>::iterator it = setA.begin(); it != setA.end(); ++it) {
		if(setB.find(*it) != setB.end()) {
			temp.erase(*it);
		}
	}
	return temp;
}