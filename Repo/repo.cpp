#include "repo.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void Repo_Offer_memory::add(const Offer &a){
    if(exist(a)){
        throw RepoException("There is already an offer with this name!");
    }
    all.push_back(a);
}

void Repo_Offer_memory::remove(int pos) {
    all.erase(all.begin() + pos);
}

void Repo_Offer_memory::update(const Offer &a, int pos) {
    all[pos] = a;
}

bool Repo_Offer_memory::exist(const Offer &a) {
    string name = a.get_name();
    auto result = find_if(all.begin(), all.end(), [&name](const Offer& a){return a.get_name() == name;});
    if(result == all.end())
        return false;
    else return true;
}

const Offer& Repo_Offer_memory::find(const string& name) {
    auto result = find_if(all.begin(), all.end(), [&name](const Offer& a){return a.get_name() == name;});
    if(result == all.end())
        throw RepoException("There is no offer with this name!");
    else return *result;
}

vector<Offer> Repo_Offer_memory::getAll()noexcept {
    return all;
}

vector<Offer> Repo_Offer_memory::getAllWishlist()noexcept {
    return wishlist;
}

void Repo_Offer_memory::clear() {
    wishlist.clear();
}

void Repo_Offer_memory::add_wishlist(Offer &offer) {
    wishlist.push_back(offer);
}

int Repo_Offer_memory::find_pos(const string& name) {
    int pos=0;
    for (auto &offer: getAll()) {
        if(offer.get_name() == name)
            return pos;
        pos++;
    } return -1;}

void Repo_Offer_memory::repo_export(string &filename) {
    vector<Offer> offers = getAllWishlist();
    ofstream out(filename, ios::trunc);
    for (const auto& offer:offers) {
        out << offer.get_name() << "," << offer.get_destination() << "," << offer.get_type() << "," << offer.get_price() << endl;
    }
    out.close();
}

void Repo_Offer_memory::replace(vector<Offer> offers)
{
    all = offers;
}

void Repo_Offer_memory::add_all_to_wishlist() {
    wishlist=all;
}

ostream& operator<<(ostream& out, const RepoException& ex){
    out<<ex.msg;
    return out;
}

void Repo_Offer_file::load_from_file(string &file_input) {
    Repo_Offer_memory::clear_all();
    std::ifstream in(file_input);
    string line;
    while(getline(in,line))
    {
        vector<string>str;
        stringstream ss(line);
        string cell;

        while(getline(ss,cell,','))
            str.push_back(cell);

        string name=str[0];
        string destination=str[1];
        string type=str[2];
        string price=str[3];

        Offer o{name, destination, type, price};
        Repo_Offer_memory::add(o);
    }
    in.close();
}

void Repo_Offer_file::save_to_file(string &file_output) {
    ofstream out(file_output, ios::trunc);
    for (const auto& offer:Repo_Offer_memory::getAll()) {
        if(!offer.get_name().empty())
            out << offer.get_name() << "," << offer.get_destination() << "," << offer.get_type() << "," << offer.get_price() << endl;
    }
    Repo_Offer_memory::clear_all();
    out.close();
}

