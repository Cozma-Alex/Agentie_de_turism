#pragma once

#include "..//Repo/repo.h"
#include "..//Validator/validate.h"
#include "undo.h"
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <map>
#include <memory>
#include <iterator>

using namespace std;

class ServiceOffer{
    Repo_Offer* repo;
    vector<unique_ptr<ActionUndo>> UndoActions;
public:
    ServiceOffer(Repo_Offer *rep, Offer_Validator &val): repo{rep}{}

    vector<Offer> getAll() noexcept{
        return repo->getAll();
    }

    vector<Offer> getAllWishlist() noexcept{
        return repo->getAllWishlist();
    }
    
    /// preia parametrii din ui si ii trimite sub forma de Offer in repo pentru adaugare
    /// \param name const string& - titlul noii activitati
    /// \param destinationi const string& - descrierea noii activitati
    /// \param type const string& - tipul noii activitati
    /// \param price int - price noii activitati
    void add_offer(const std::string &name, const std::string &destinationi, const std::string &type, const string& price);

    /// remove activitatea cu titlul name
    /// \param name const string&
    /// \return 1 - se realizeaza stergerea
    ///         0 - nu se realizeaza stergerea
    void remove_offer(const std::string &name);

    /// update activitatea cu titlul name
    /// \param name const string& - titlul activitatii modificate
    /// \param destination const string& - descrierea activitatii modificate
    /// \param type const string& - tipul activitatii modificate
    /// \param price int - price activitatii modificate
    /// \return 1 - se realizeaza modificarea
    ///         0 - nu se realizeaza modificarea
    void update_offer(const std::string &name, const std::string &destination, const std::string &type, const string& price);

    const Offer & find_offer(const std::string &name);

    vector<Offer> filter_by_destination(const string& destination);

    vector<Offer> filter_by_price(const string& price);

    vector<Offer> sort_offers(const string &type_of_sort);

    static bool cmp_names(const Offer &a, const Offer &b);

    static bool cmp_destination(const Offer &a, const Offer &b);

    static bool cmp_type_and_price(const Offer &a, const Offer &b);

    void clear_wishlist();

    void add_to_wishlist(const string &name);

    void generate_wishlist(int nr);

    map<string, vector<Offer>> generate_report();

    void undo();

    void export_CSV(basic_string<char, char_traits<char>, allocator<char>> filename);

    void memory_set(const string& rep){
        if(rep == "File"){
            repo = new Repo_Offer_file();
        }
        if (rep == "Memory")
            repo = new Repo_Offer_memory();
    }
};

