#include <assert.h>
#include "CalcParser.hpp"

CalcInstruction CalcParser::parse(std::string insstr)
{
	CalcInstruction ret;
    if(insstr.empty()){
        ret.end=true;
        return ret;
    } else {
        ret.end=false;
    }
	if(!insstr.compare(0,3,"SET")){
        ret.op = 0;
    } else if (!insstr.compare(0,3,"ADD")){
		ret.op = 1;
	} else if (!insstr.compare(0,3,"SUB")){
		ret.op = 2;
    }
    ret.num = stoi(insstr.substr(4));
	// PUT YOUR CODE HERE
	return ret;
}
