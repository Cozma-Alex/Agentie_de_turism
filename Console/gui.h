#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include "..//Business/service.h"
#include "wishlists.h"
#include <map>
#include <QFormLayout>
#include <QTableWidget>
#include <QLabel>
#include "QDialog"

using namespace std;

class Offer_ui:public QWidget, public Observer{

    ServiceOffer &service;

    QListWidget *offers;
    vector<Offer> elements;

    QTableWidget *table_wishlist;

    QWidget *page1;
    QWidget *page2;
    QTabWidget *tab_widget;

    QVBoxLayout *main_box_layout;
    QHBoxLayout *main_data_and_wishlist_buttons;
    QHBoxLayout *h_layout;

    QFormLayout *h_wishlist_buttons;
    QFormLayout *new_data_layout;
    QFormLayout *CRUD_layout;
    QFormLayout *filters_layout;
    QFormLayout *sort_layout;

    QLineEdit *nameEdit;
    QLineEdit *destinationEdit;
    QLineEdit *typeEdit;
    QLineEdit *priceEdit;
    QLineEdit *numberEdit;

    QPushButton *add_button;
    QPushButton *update_button;
    QPushButton *remove_button;
    QPushButton *find_button;
    QPushButton *undo_button;

    QPushButton *destination_filter_button;
    QPushButton *price_filter_button;
    QPushButton *remove_all_filters_button;

    QPushButton *sort_by_name_button;
    QPushButton *sort_by_destination_button;
    QPushButton *sort_by_type_and_price_button;

    QPushButton *add_wishlist_button_main;
    QPushButton *generate_wishlist_button_main;
    QPushButton *clear_wishlist_button_main;
    QPushButton *read_only_wishlist;
    QPushButton *generate_and_clear_wishlist;

    // WISHLIST

    QListWidget *wishlist;
    vector<Offer> elem_report;

    QVBoxLayout *main_wishlist_box_layout;
    QHBoxLayout *h_wishlist_layout;
    QFormLayout *new_data_wishlist_layout;
    QFormLayout *methods_wishlist_layout;

    QLineEdit *name_wishlist_edit;
    QLineEdit *offer_number;
    QLineEdit *export_file;

    QPushButton *add_wishlist_button;
    QPushButton *generate_wishlist_button;
    QPushButton *export_wishlist_button;
    QPushButton *clear_wishlist_button;

    // METHODS

    void restart(vector<Offer> offer);

    void connection();

    int selec_index();

    void initGuiCmps(QWidget *widget);

    void define_main();

    void define_data_layout();

    void define_CRUD_layout();

    void define_filter_layout();

    void define_sort_layout();

    void define_wishlist_buttons();

    void define_tabs();

    void define_main_wishlist();

    void define_data_layout_wishlist();

    void define_methods_wishlist();

    void connect_wishlist();

    void restart_wishlist(vector<Offer> offer);

    void table_wishlist_define();

private slots:
    void read_only_wishlist_window(){
        auto read_only = new Read_only_wishlist{service};
        read_only->show();
    }

    void generate_and_clear_wishlist_window(){
        auto gen_clear = new Generare_and_Clear_wishlist{service};
        gen_clear->show();
    }

public:
    Offer_ui(ServiceOffer &serv) : service{serv}{
        service.register_observer(this);
        initGuiCmps(this);
    }

    void update(){
        this->restart_wishlist(service.getAllWishlist());
    }

    ~Offer_ui(){
        service.unregister_observer(this);
    }
};