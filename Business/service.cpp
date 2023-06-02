#include "service.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

void ServiceOffer::add_offer(const std::string &name, const std::string &destinationi,
                             const std::string &type, const string &price) {
    Offer a{name, destinationi, type, price};
    Offer_Validator::validate(a);
    repo->add(a);
    UndoActions.push_back(std::make_unique<UndoAdd>(a, this->repo));
}

void ServiceOffer::remove_offer(const std::string &name) {
    int pos = 0;
    for (const auto& offer: getAll()) {
        {
            if (name == offer.get_name()) {
                repo->remove(pos);
                UndoActions.push_back(std::make_unique<UndoDelete>(offer, this->repo));
                return;
            }
            pos++;
        }
    }
    throw RepoException("There is no offer with this name");
}

void ServiceOffer::update_offer(const std::string &name, const std::string &destination,
                                const std::string &type, const string &price) {
    int pos = 0;
    Offer a{name, destination, type, price};
    Offer_Validator::validate(a);
    for (const auto& offer: getAll()){
        {
            if(name == offer.get_name()){
                repo->update(a, pos);
                UndoActions.push_back(std::make_unique<UndoUpdate>(offer, this->repo));
                return;
            }
            pos++;
        }
    }
    throw RepoException("There is no offer with this name");
}

const Offer &ServiceOffer::find_offer(const std::string &name) {
    return repo->find(name);
}

vector<Offer> ServiceOffer::filter_by_destination(const string &destination) {
    vector<Offer> filtered;
    vector<Offer> offers = getAll();
    std::copy_if(offers.begin(), offers.end(), back_inserter(filtered), [&destination](Offer &a){return
            a.get_destination() == destination;});
    return filtered;
}

vector<Offer> ServiceOffer::filter_by_price(const string& price) {
    vector<Offer> offers = getAll();
    vector<Offer> filtered;
    std::copy_if(offers.begin(), offers.end(), back_inserter(filtered), [&price](Offer &a){return a.get_price() == price;});
    return filtered;
}

vector<Offer> ServiceOffer::sort_offers(const string& type_of_sort){
    vector<Offer> offers = getAll();
    if(type_of_sort == "name")
        sort(offers.begin(), offers.end(), cmp_names);
    if(type_of_sort == "destination")
        sort(offers.begin(), offers.end(), cmp_destination);
    if(type_of_sort == "type and price")
        sort(offers.begin(), offers.end(), cmp_type_and_price);
    repo->replace(offers);
    return offers;}

bool ServiceOffer::cmp_names(const Offer& a, const Offer& b)
{
    return a.get_name() < b.get_name();
}

bool ServiceOffer::cmp_destination(const Offer& a, const Offer& b)
{
    return a.get_destination() < b.get_destination();
}

bool ServiceOffer::cmp_type_and_price(const Offer& a, const Offer& b)
{
    if(a.get_type() == b.get_type())
        return a.get_price() < b.get_price();
    return a.get_type() < b.get_type();
}

void ServiceOffer::clear_wishlist() {
    repo->clear();
    notify();
}

void ServiceOffer::add_to_wishlist(const string &name) {
    Offer o = find_offer(name);
    repo->add_wishlist(o);
    notify();
}

void ServiceOffer::generate_wishlist(int nr) {
    repo->clear();
    vector<Offer> offers = getAll();
    if(nr>offers.size())
        for(int i=1;i<nr;i+=offers.size())
        {
            repo->add_all_to_wishlist();
            nr-=offers.size();
        }
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(offers.begin(), offers.end(), std::default_random_engine(seed));
    while(nr){
        repo->add_wishlist(offers[offers.size() - nr]);
        nr--;
    }
    notify();
}

map<string, vector<Offer>> ServiceOffer::generate_report() {
    map<string, vector<Offer>> report;
    vector<Offer> oferte = getAll();
    for (const auto& offer: oferte) {
        report[offer.get_type()].push_back(offer);
    }
    return report;
}

void ServiceOffer::undo() {
    if(UndoActions.empty()){
        throw RepoException("There are no more undo actions\n");
    }
    UndoActions.back()->doUndo();
    UndoActions.pop_back();
}

void ServiceOffer::export_CSV(basic_string<char, char_traits<char>, allocator<char>> filename) {
    repo->repo_export(filename);
}
