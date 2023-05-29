#pragma once
#include "..//Business/service.h"

class ConsoleUI{
    ServiceOffer& service;

    void ui_add_offer();

    static void ui_print(const vector<Offer>& oferte);

    static void ui_print_wishlist(const vector<Offer>& offers);

    void ui_remove_offer();

    void ui_update_offer();

    void ui_find_offer();

    void ui_filter_by_destination();

    void ui_filter_by_price();

    void ui_sort_by_name();

    void ui_sort_by_destination();

    void ui_sort_by_type_and_price();

    void ui_clear_wishlist();

    void ui_add_to_wishlist();

    void ui_generate_wishlist();

    void ui_undo();

    void ui_report();

    void ui_export();

public:
    explicit ConsoleUI(ServiceOffer& service): service{service}{}

    ConsoleUI(const ConsoleUI& ot) = delete;

    void start();
};