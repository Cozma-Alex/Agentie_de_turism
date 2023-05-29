#include "validate.h"
#include <sstream>

void Offer_Validator::validate(const Offer &a) {
    string msgs;
    if(a.get_name().empty())
        msgs += "invalid name!\n";
    if(a.get_destination().empty())
        msgs += "invalid destination!\n";
    if(a.get_price().empty() or a.get_price()[0] == '0' or !isdigit(a.get_price()[0]))
        msgs += "invalid price!\n";
    if(a.get_type().empty())
        msgs += "invalid price!\n";
    if(!msgs.empty())
        throw Validation(msgs);
}

ostream& operator<<(ostream& out, const Validation& ex){
    for(const auto& msg : ex.msg)
        out<< msg<<" ";
    return out;
}