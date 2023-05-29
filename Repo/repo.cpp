#include "repo.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

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
    } }

void Repo_Offer_memory::repo_export(string &filename) {
    vector<Offer> offers = getAllWishlist();
    ofstream out(filename, ios::trunc);
    for (const auto& offer:offers) {
        out << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << endl;
    }
    out.close();
}

void Repo_Offer_memory::replace(vector<Offer> offers)
{
    all = offers;
}

ostream& operator<<(ostream& out, const RepoException& ex){
    out<<ex.msg;
    return out;
}

void Repo_Offer_file::load_from_file(string &file) {
    Repo_Offer_memory::clear_all();
    std::ifstream in(file);
    while(!in.eof())
    {
        string name;
        in >> name;
        string destination;
        in >> destination;
        string type;
        in >> type;
        string price;
        in >> price;
        if(!name.empty() and !destination.empty() and !type.empty() and !price.empty())
        {
            Offer o{name, destination, type, price};
            Repo_Offer_memory::add(o);
        }
    }
    in.close();
}

void Repo_Offer_file::save_to_file(string &file) {
    ofstream out(file, ios::trunc);
    for (const auto& offer:Repo_Offer_memory::getAll()) {
        if(!offer.get_name().empty())
            out << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << endl;
    }
    Repo_Offer_memory::clear_all();
    out.close();
}
