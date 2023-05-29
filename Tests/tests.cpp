#include <sstream>
#include "..//Business/service.h"
#include "..//Tests/tests.h"

void Tests::test_all() {

    service.memory_set("Memory");
    test_undo();
    test_export();
    test_add_offer();
    test_remove_offer();
    test_update_offer();
    test_find_offer();
    test_filter();
    test_sort();
    test_wishlist();
    test_report();
    service.memory_set("File");
    test_undo();
    test_export();
    test_add_offer();
    test_remove_offer();
    test_update_offer();
    test_find_offer();
    test_filter();
    test_sort();
    test_wishlist();
    test_report();
}

void Tests::test_add_offer() {
    service.add_offer("aaa", "aaa", "aaa", "4");
    const vector<Offer> &offers = service.getAll();
    assert(offers.size() == 1);
    try{
        service.add_offer("", "", "", "asd");
    }
    catch (Validation& ex) {
        stringstream sout;
        sout<<ex;
    }
    try {
        service.add_offer("aaa", "aaa", "aaa", "4");
    }
    catch (RepoException& ex) {
        stringstream sout;
        sout<<ex;
    }
}

void Tests::test_remove_offer() {
    service.add_offer("bbb", "bbb", "bbb", "2");
    service.remove_offer("bbb");
    const vector<Offer> &offers = service.getAll();
    assert(offers.size() == 1);
    service.remove_offer("aaa");
    try{
        service.remove_offer("bbb");
    }
    catch (RepoException& ex) {
        stringstream sout;
        sout<<ex;
    }
}

void Tests::test_update_offer() {
    service.add_offer("aaa", "aaa", "aaa", "4");
    service.update_offer("aaa", "bbb", "bbb", "9");
    vector<Offer> offers = service.getAll();
    assert(offers[0].get_name() == "aaa");
    assert(offers[0].get_type() == "bbb");
    assert(offers[0].get_price() == "9");
    assert(offers[0].get_destination() == "bbb");

    try{
        service.update_offer("", "", "", "asd");
    }
    catch (Validation& ex) {
        stringstream sout;
        sout<<ex;
    }

    try {
        service.update_offer("ccc", "aaa", "aaa", "4");
    }
    catch (RepoException& ex) {
        stringstream sout;
        sout<<ex;
    }
}

void Tests::test_find_offer() {
    Offer a = service.find_offer("aaa");
    assert(a.get_name() == "aaa");
    assert(a.get_type() == "bbb");
    assert(a.get_price() == "9");
    assert(a.get_destination() == "bbb");

    try{
        service.find_offer("ccc");
    }
    catch (RepoException& ex) {
        stringstream sout;
        sout<<ex;
    }
    service.remove_offer("aaa");
}

void Tests::test_filter() {
    service.add_offer("ccc", "ccc", "ccc", "6");
    auto offers = service.filter_by_destination("ccc");
    service.add_offer("aaa", "bbb", "bbb", "9");
    assert(offers[0].get_name() == "ccc");
    assert(offers[0].get_type() == "ccc");
    assert(offers[0].get_price() == "6");
    assert(offers[0].get_destination() == "ccc");

    auto filter = service.filter_by_price("9");
    assert(filter[0].get_name() == "aaa");
    assert(filter[0].get_type() == "bbb");
    assert(filter[0].get_price() == "9");
    assert(filter[0].get_destination() == "bbb");

    service.remove_offer("ccc");
    service.remove_offer("aaa");
}

void Tests::test_sort() {

    service.add_offer("bbb", "aaa", "bbb", "7");
    service.add_offer("aaa", "rrr", "qqq", "9");
    service.add_offer("ddd", "ttt", "qqq", "8");
    service.add_offer("ccc", "fff", "qqq", "5");

    auto sort_type_price = service.sort_offers("type si price");
    assert(sort_type_price[2].get_price() == "8");

    auto sort_name = service.sort_offers("name");
    assert(sort_name[0].get_name() == "aaa");

    auto sort_dest = service.sort_offers("destination");
    assert(sort_dest[0].get_destination() == "aaa");
}

void Tests::test_wishlist() {
    service.add_to_wishlist("aaa");
    assert(service.getAllWishlist().size() == 1);
    assert(service.getAllWishlist()[0].get_name() == "aaa");

    service.clear_wishlist();
    assert(service.getAllWishlist().empty());

    service.generate_wishlist(3);
    assert(service.getAllWishlist().size() == 3);
}

void Tests::test_report() {
    auto report = service.generate_report();
    assert(report.size() == 2);

    assert(report["qqq"].size() == 3);
    assert(report["bbb"][0].get_name() == "bbb");

    service.remove_offer("bbb");
    service.remove_offer("aaa");
    service.remove_offer("ccc");
    service.remove_offer("ddd");
}

void Tests::test_undo() {
    service.add_offer("bbb", "aaa", "bbb", "7");
    service.add_offer("aaa", "rrr", "qqq", "9");
    service.add_offer("ddd", "ttt", "qqq", "8");
    service.add_offer("ccc", "fff", "qqq", "5");

    service.undo();
    assert(service.getAll().size() == 3);
    service.undo();
    service.undo();
    service.undo();

    try{
        service.undo();
    }
    catch (RepoException& ex) {
        stringstream sout;
        sout<<ex;
    }

    service.add_offer("aaa", "rrr", "qqq", "9");
    service.update_offer("aaa", "qqq", "ttt", "6");
    service.undo();
    vector<Offer> offers = service.getAll();
    assert(offers[0].get_name() == "aaa");
    assert(offers[0].get_type() == "qqq");

    service.remove_offer("aaa");
    service.undo();
    assert(service.getAll().size() == 1);

    service.remove_offer("aaa");
}


void Tests::test_export() {
    service.add_offer("bbb", "aaa", "bbb", "7");
    service.add_offer("aaa", "rrr", "qqq", "9");
    service.add_offer("ddd", "ttt", "qqq", "8");
    service.add_offer("ccc", "fff", "qqq", "5");
    service.add_to_wishlist("aaa");
    service.export_CSV("..//test.csv");
    ifstream in2("..//test.csv");

    string Basic;
    getline(in2, Basic);
    assert(Basic == "aaa rrr qqq 9");

    in2.close();
    service.remove_offer("aaa");
    service.remove_offer("bbb");
    service.remove_offer("ccc");
    service.remove_offer("ddd");
    service.clear_wishlist();
}