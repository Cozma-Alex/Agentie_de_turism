#include "..//Business/service.h"
#include <cassert>

class Tests{
    ServiceOffer& service;

    void test_add_offer();

    void test_remove_offer();

    void test_update_offer();

    void test_find_offer();

    void test_filter();

    void test_sort();

    void test_wishlist();

    void test_report();

    void test_undo();

    void test_export();

public:
    explicit Tests(ServiceOffer& service): service{service}{}

    Tests(const Tests& ot) = default;

    void test_all();
};
