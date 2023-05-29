#pragma once
#include "..//Domain/offer.h"
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Validation{
    string msg;

public:
    explicit Validation(string  errors): msg{std::move(errors )}{}

    friend ostream& operator<<(ostream& out, const Validation& ex);

    const string& get_msg() const{
        string mesg;

        return msg;
    }
};

ostream& operator<<(ostream& out, const Validation& ex);

class Offer_Validator{
public:
    static void validate(const Offer& a);
};