#include "cmdhandler.h"
#include "util.h"
#include <set>
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

PrintHandler::PrintHandler()
{

}

PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

OutgoingHandler::OutgoingHandler() {

}

OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}

bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";

}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        if(eng->retrieve_page(name) == NULL) {
            return HANDLER_ERROR;
        }
        set<WebPage*> temp = eng->retrieve_page(name)->outgoing_links();
        ostr << temp.size() << endl;
        for(set<WebPage*>::iterator it = temp.begin(); it != temp.end();
            ++it) {
            ostr << (*it)->filename() << endl;     
        }    
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

IncomingHandler::IncomingHandler(){

}

IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}

bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";
}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        if(eng->retrieve_page(name) == NULL) {
            return HANDLER_ERROR;
        }
        set<WebPage*> temp = eng->retrieve_page(name)->incoming_links();
        ostr << temp.size() << endl;
        for(set<WebPage*>::iterator it = temp.begin(); it != temp.end();
            ++it) {
            ostr << (*it)->filename() << endl;     
        }
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

ANDHandler::ANDHandler(){

}

ANDHandler::ANDHandler(Handler* next)
    : Handler(next)
{
    
}

bool ANDHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";
}

Handler::HANDLER_STATUS_T ANDHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;
    vector<string> termlist;
    WebPageSet temp;
    while(instr >> name) {
        termlist.push_back(name);
    }
    temp = eng->search(termlist,&combiner);  
    display_hits(temp, ostr);    
    return HANDLER_OK;
}

ORHandler::ORHandler(){

}

ORHandler::ORHandler(Handler* next)
    : Handler(next)
{

}

bool ORHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";
}

Handler::HANDLER_STATUS_T ORHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;
    vector<string> termlist;
    WebPageSet temp;
    while(instr >> name) {
        termlist.push_back(name);
    } 
    temp = eng->search(termlist,&combiner);    
    display_hits(temp, ostr); 
    return HANDLER_OK;   
}

DIFFHandler::DIFFHandler(){

}

DIFFHandler::DIFFHandler(Handler* next)
    : Handler(next)
{

}

bool DIFFHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";
}

Handler::HANDLER_STATUS_T DIFFHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;
    vector<string> termlist;
    WebPageSet temp;
    while(instr >> name) {
        termlist.push_back(name);
    }
    temp = eng->search(termlist,&combiner);  
    display_hits(temp, ostr);    
    return HANDLER_OK;
}
