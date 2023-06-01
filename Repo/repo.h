#pragma once
#include "..//Domain/offer.h"

#include <utility>
#include <vector>
#include <string>
#include <ostream>

using namespace std;

class Repo_Offer{
public:
    Repo_Offer() = default;

    virtual void add(const Offer& a) = 0;

    virtual void remove(int poz) = 0;

    virtual void update(const Offer& a, int poz) = 0;

    virtual const Offer& find(const string& denumire)= 0;

    virtual vector<Offer> getAll() noexcept = 0;

    virtual vector<Offer> getAllWishlist() noexcept = 0;

    virtual void clear() = 0;

    virtual void add_wishlist(Offer& a) = 0;

    virtual int find_pos(const string& denumire) = 0;

    virtual void repo_export(string& filename) = 0;

    virtual void replace(vector<Offer>) = 0;

    virtual void add_all_to_wishlist() = 0;

    virtual ~Repo_Offer() {}
};

class Repo_Offer_memory: public Repo_Offer{
    vector<Offer> all;
    vector<Offer> wishlist;
    [[nodiscard]] bool exist(const Offer& a);

public:
    Repo_Offer_memory() = default;

    /// adaugare in lista all noua activitate
    /// \param a - const Offer&
    void add(const Offer& a) override;

    /// stergere din lista all activitatea de pe pozitia pos
    /// \param pos - int
    void remove(int pos) override;

    /// update activitatea de pe pozitia pos cu activitatea a
    /// \param a - const Offer&
    /// \param pos - int
    void update(const Offer& a, int pos) override;

    const Offer& find(const string& name) override;

    vector<Offer> getAll() noexcept override;

    vector<Offer> getAllWishlist() noexcept override;

    void clear() override;

    void add_wishlist(Offer &offer) override;

    int find_pos(const string& name) override;

    void repo_export(string& filename) override;

    void replace(vector<Offer>) override;

   ~Repo_Offer_memory() override = default;

    void clear_all(){
        all.clear();
    };

    void add_all_to_wishlist() override;
};

class RepoException{
    string msg;

public:
    explicit RepoException(string m):msg(std::move( m )){}

    string get_msg() const {
        return msg;
    }

    friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);

class Repo_Offer_file: public Repo_Offer_memory{
    string file = "..//file.csv";

    void load_from_file(string& file_input);

    void save_to_file(string& file_output);

public:
    Repo_Offer_file() = default;

    /// adaugare in lista all noua activitate
    /// \param a - const Offer&
    void add(const Offer& a) override{
        load_from_file(file);
        Repo_Offer_memory::add(a);
        save_to_file(file);
    }
    /// stergere din lista all activitatea de pe pozitia pos
    /// \param pos - int
    void remove(int pos) override{
        load_from_file(file);
        Repo_Offer_memory::remove(pos);
        save_to_file(file);
    }

    /// update activitatea de pe pozitia pos cu activitatea a
    /// \param a - const Offer&
    /// \param pos - int
    void update(const Offer& a, int pos) override{
        load_from_file(file);
        Repo_Offer_memory::update(a, pos);
        save_to_file(file);
    }

    const Offer & find(const string& name) override{
        load_from_file(file);
        return Repo_Offer_memory::find(name);
    }

    vector<Offer> getAll()noexcept override{
        load_from_file(file);
        return Repo_Offer_memory::getAll();
    }

    vector<Offer> getAllWishlist() noexcept override{
        return Repo_Offer_memory::getAllWishlist();
    }

    void clear() override{
        Repo_Offer_memory::clear();
    }

    void add_wishlist(Offer &offer) override{
        Repo_Offer_memory::add_wishlist(offer);
    }

    int find_pos(const string& name) override{
        load_from_file(file);
        return Repo_Offer_memory::find_pos(name);
    }

    void repo_export(string& filename) override{
        Repo_Offer_memory::repo_export(filename);
    }

    void replace(vector<Offer> offer) override{
        load_from_file(file);
        Repo_Offer_memory::replace(offer);
        save_to_file(file);
    }

    void add_all_to_wishlist() override{
        Repo_Offer_memory::add_all_to_wishlist();
    }

    ~Repo_Offer_file() override = default;
};