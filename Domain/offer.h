#pragma once
#include <string>
#include <iostream>
#include <utility>

using namespace std;

class Offer {
    string name;
    string destination;
    string type;
    string price;
public:

    Offer() = default;

    Offer(string  titl, string  descr, string  t, string pret): name{std::move(titl)}, destination{std::move(descr)}, type{std::move(t)}, price{std::move(pret)}{
        //cout<<"Construit cu parametri\n";
    }

    Offer(const Offer& ot): name{ot.name}, destination{ot.destination}, type{ot.type}, price{ot.price}{
        //cout<<"Construit prin copiere!\n";
    }

    string get_name() const{
        return name;
    }

    string get_destination() const{
        return destination;
    }

    string get_type() const{
        return type;
    }

    string get_price() const{
        return price;
    }

    string to_string() const{
        return name + " " + destination + " " + type + " " + price;
    }

    ~Offer(){
        //out<<"Distrus\n";
    }
};
