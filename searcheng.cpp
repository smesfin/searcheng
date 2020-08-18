#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

std::string extract_extension(const std::string& filename);


SearchEng::SearchEng(PageParser* noExtensionParser)
{
    if (NULL == noExtensionParser)
    {
        throw std::invalid_argument("default parser cannot be NULL");
    }
    this->noExtensionParser_ = noExtensionParser;

    // Add additional code if necessary


}

SearchEng::~SearchEng() {

}

void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const {
    set<WebPage*> first;
    if(Google.find(terms[0]) != Google.end()) {
        first = Google.find(terms[0])->second;
    }
    for(size_t i=1; i<terms.size(); ++i) {
        if(Google.find(terms[i]) != Google.end()) {
            first = combiner->combine(first,Google.find(terms[i])->second);
        }
    }
    return first;
}

void SearchEng::read_page(const std::string& filename){
    string ext = extract_extension(filename);
    if(Parsereg.find(ext) == Parsereg.end()) {
        throw std::invalid_argument("parser doesn't exist");
    }
    map<string,WebPage*>::iterator it = PageData.find(filename);
    if(it == PageData.end()) {             //allocates webpage data if doesn't exist
        WebPage* temp = new WebPage;
        temp->filename(filename);   
        PageData.insert(make_pair(filename,temp));
    }
    set<string> tempLinks;
    WebPage* page = PageData.find(filename)->second;
    StringSet terms; 
    Parsereg.find(ext)->second->parse(filename,terms,tempLinks);   
    for(set<string>::iterator it = tempLinks.begin(); it != tempLinks.end(); 
        ++it) {
        if(PageData.find(*it) == PageData.end()) {
            WebPage* temp = new WebPage;
            temp->filename(*it); 
            PageData.insert(make_pair(*it,temp));
        }
        (*page).add_outgoing_link(retrieve_page(*it));   //adds pages to outlinks
        PageData.find(*it)->second->add_incoming_link(page);  //adds temp to page inlinks
    }
    for(set<string>::iterator it = terms.begin(); it != terms.end();
        ++it) {
        if(Google.find(*it) == Google.end()) {
            set<WebPage*> tempset;
            tempset.insert(retrieve_page(filename));
            Google.insert(make_pair(*it,tempset));
            }
        else {
            Google.find(*it)->second.insert(retrieve_page(filename));
        }
    }
}


void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const {
    if(PageData.find(page_name) == PageData.end()) {
        throw std::invalid_argument("Page name doesn't exist");
    }
    if(Parsereg.find(extract_extension(page_name)) == Parsereg.end()) {
        throw std::logic_error("No valid parser");
    }
    PageParser* ptype = Parsereg.find(extract_extension(page_name))->second;
    ostr << ptype->display_text(page_name);
 }

WebPage* SearchEng::retrieve_page(const std::string& page_name) const{
    if(PageData.find(page_name) == PageData.end()) {
        return NULL;
    }
    return PageData.find(page_name)->second;
 }

void SearchEng::register_parser(const std::string& extension, PageParser* parser){
    Parsereg.insert(make_pair(extension,parser));
}


