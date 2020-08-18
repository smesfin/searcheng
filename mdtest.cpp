#include <iostream>
#include "md_parser.h"
#include "util.h"
#include <fstream>
#include <stdexcept>
#include <cctype>
using namespace std;

int main() {
	MDParser parser;
     set<string> terms;
     set<string> links;
     parser.parse("test-small/page1.md", terms, links);

     cout << "Terms: " << endl;
     for(set<string>::iterator it = terms.begin(); 
     	it != terms.end(); ++it) {
     	cout << *it << " ";
     }
     cout << endl << endl << "Links: " << endl;
     for(set<string>::iterator it = links.begin(); 
     	it != links.end(); ++it) {
     	cout << *it << " ";
     }

	return 0; 
}