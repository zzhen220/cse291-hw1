#include <assert.h>
#include <vector>
#include "CalcFramer.hpp"

using namespace std;

void CalcFramer::append(string chars)
{
    if(!v.empty()){
        v.erase(v.cend()-2,v.cend());
    }

	v.insert(v.cend(), chars.begin(), chars.end());
}

bool CalcFramer::hasMessage() const
{
	if(v.empty()){
        return false;
    }
    for(auto it=v.cbegin();it!=v.cend()-1;++it){
        if(*it=='\r' and *(it+1)=='\n'){
                return true;
        }
    }
    return false;
}

string CalcFramer::topMessage() const
{
	string out="";
	for(auto it = v.cbegin(); it != v.cend(); ++it){
        if(*it == '\r')
            break;
        out += *it;
    }
	return out;
}

void CalcFramer::popMessage()
{
    auto it = v.cbegin();
	for(it;it != v.cend(); ++it) {
        if (*it == '\n')
            break;
    }
        v.erase(v.begin(),++it);
}

void CalcFramer::printToStream(ostream& stream) const
{
	if (hasMessage()){
		stream << topMessage();
	}
}
