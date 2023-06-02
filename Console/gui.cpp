#include "gui.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPushButton>
#include <iostream>


void Offer_ui::initGuiCmps(QWidget *widget) {

    widget->resize(900, 800);
    this->main_box_layout = new QVBoxLayout(widget);
    this->main_wishlist_box_layout = new QVBoxLayout();

    define_main();

    define_wishlist_buttons();

    define_data_layout();

    define_CRUD_layout();

    define_filter_layout();

    define_sort_layout();

    main_box_layout->addLayout(h_layout);

    define_main_wishlist();

    define_data_layout_wishlist();

    define_methods_wishlist();

    main_wishlist_box_layout->addLayout(h_wishlist_layout);

    define_tabs();

    this->restart(this->service.getAll());

    this->restart_wishlist(service.getAllWishlist());

    this->connection();

    this->connect_wishlist();
}

void Offer_ui::define_main() {
    this->page1 = new QWidget();
    this->offers = new QListWidget;
    this->main_data_and_wishlist_buttons = new QHBoxLayout;
    main_data_and_wishlist_buttons->addWidget(this->offers);
    this->main_box_layout->addLayout(main_data_and_wishlist_buttons);
    h_layout = new QHBoxLayout;
    new_data_layout = new QFormLayout;
    CRUD_layout = new QFormLayout;
}

void Offer_ui::define_data_layout() {
    this->nameEdit = new QLineEdit;
    this->destinationEdit = new QLineEdit;
    this->typeEdit = new QLineEdit;
    this->priceEdit = new QLineEdit;
    this->numberEdit = new QLineEdit;

    this->nameEdit->setFixedHeight(45);
    this->destinationEdit->setFixedHeight(45);
    this->typeEdit->setFixedHeight(45);
    this->priceEdit->setFixedHeight(45);

    this->nameEdit->setFixedWidth(310);
    this->destinationEdit->setFixedWidth(310);
    this->typeEdit->setFixedWidth(310);
    this->priceEdit->setFixedWidth(310);

    new_data_layout->setVerticalSpacing(30);
    new_data_layout->setHorizontalSpacing(30);
    new_data_layout->addRow(QString("Name"), this->nameEdit);
    new_data_layout->addRow(QString("Destination"), this->destinationEdit);
    new_data_layout->addRow(QString("Type"), this->typeEdit);
    new_data_layout->addRow(QString("Price"), this->priceEdit);

    numberEdit = new QLineEdit;
    numberEdit->setPlaceholderText("How many offers to wishlist");
    numberEdit->setFixedSize(310,40);
    new_data_layout->addRow(QString("Number"),numberEdit);

    h_layout->addLayout(new_data_layout);
}

void Offer_ui::define_CRUD_layout() {
    this->add_button = new QPushButton("Add");
    this->update_button = new QPushButton("Update");
    this->remove_button = new QPushButton("Remove");
    this->find_button = new QPushButton("Find");
    this->undo_button = new QPushButton("Undo");

    this->add_button->setStyleSheet(QString("background-color: rgb(96, 147, 158);"));
    this->remove_button->setStyleSheet(QString("background-color: rgb(96, 147, 158);"));
    this->update_button->setStyleSheet(QString("background-color: rgb(96, 147, 158);"));
    this->find_button->setStyleSheet(QString("background-color: rgb(96, 147, 158);"));
    this->undo_button->setStyleSheet(QString("background-color: rgb(96, 147, 158);"));

    CRUD_layout->addWidget(this->add_button);
    CRUD_layout->addWidget(this->update_button);
    CRUD_layout->addWidget(this->remove_button);
    CRUD_layout->addWidget(this->find_button);
    CRUD_layout->addWidget(this->undo_button);

    this->add_button->setFixedHeight(50);
    this->remove_button->setFixedHeight(50);
    this->update_button->setFixedHeight(50);
    this->undo_button->setFixedHeight(50);
    this->find_button->setFixedHeight(50);

    this->add_button->setFixedWidth(240);
    this->remove_button->setFixedWidth(240);
    this->update_button->setFixedWidth(240);
    this->undo_button->setFixedWidth(240);
    this->find_button->setFixedWidth(240);

    h_layout->addLayout(CRUD_layout);
}

void Offer_ui::define_filter_layout() {
    filters_layout = new QFormLayout;
    this->destination_filter_button = new QPushButton("Filter by destination");
    this->price_filter_button = new QPushButton("Filter by price");
    this->remove_all_filters_button = new QPushButton("Clear all filters");

    this->destination_filter_button->setPalette(QColor(Qt::darkGreen));
    this->price_filter_button->setPalette(QColor(Qt::darkGreen));
    this->remove_all_filters_button->setPalette(QColor(Qt::darkGreen));

    filters_layout->addWidget(destination_filter_button);
    filters_layout->addWidget(price_filter_button);
    filters_layout->addWidget(remove_all_filters_button);

    this->destination_filter_button->setFixedHeight(70);
    this->price_filter_button->setFixedHeight(70);
    this->remove_all_filters_button->setFixedHeight(70);
    this->destination_filter_button->setFixedWidth(250);
    this->price_filter_button->setFixedWidth(250);
    this->remove_all_filters_button->setFixedWidth(250);

    h_layout->addLayout(filters_layout);

}

void Offer_ui::define_sort_layout() {
    sort_layout = new QFormLayout;
    this->sort_by_name_button = new QPushButton("Sort by name");
    this->sort_by_destination_button = new QPushButton("Sort by destination");
    this->sort_by_type_and_price_button = new QPushButton("Sort by type and price");

    this->sort_by_name_button->setPalette(QColor(Qt::darkYellow));
    this->sort_by_destination_button->setPalette(QColor(Qt::darkYellow));
    this->sort_by_type_and_price_button->setPalette(QColor(Qt::darkYellow));

    sort_layout->addWidget(this->sort_by_name_button);
    sort_layout->addWidget(this->sort_by_destination_button);
    sort_layout->addWidget(this->sort_by_type_and_price_button);

    this->sort_by_name_button->setFixedHeight(70);
    this->sort_by_destination_button->setFixedHeight(70);
    this->sort_by_type_and_price_button->setFixedHeight(70);
    this->sort_by_name_button->setFixedWidth(250);
    this->sort_by_destination_button->setFixedWidth(250);
    this->sort_by_type_and_price_button->setFixedWidth(250);

    h_layout->addLayout(sort_layout);
}

void Offer_ui::define_wishlist_buttons() {

    h_wishlist_buttons = new QFormLayout;
    add_wishlist_button_main = new QPushButton("Add to wishlist");
    generate_wishlist_button_main = new QPushButton("Generate wishlist");
    clear_wishlist_button_main = new QPushButton("Clear wishlist");
    read_only_wishlist = new QPushButton("Open a read only Wishlist",this);
    generate_and_clear_wishlist = new QPushButton("Open an editable Wishlist",this);

    this->add_wishlist_button_main->setStyleSheet(QString("background-color: rgb(51, 19, 19);"));
    this->generate_wishlist_button_main->setStyleSheet(QString("background-color: rgb(51, 19, 19);"));
    this->clear_wishlist_button_main->setStyleSheet(QString("background-color: rgb(51, 19, 19);"));
    this->read_only_wishlist->setStyleSheet(QString("background-color: rgb(81, 19, 19);"));
    this->generate_and_clear_wishlist->setStyleSheet(QString("background-color: rgb(81, 19, 19);"));

    h_wishlist_buttons->addWidget(add_wishlist_button_main);
    h_wishlist_buttons->addWidget(generate_wishlist_button_main);
    h_wishlist_buttons->addWidget(clear_wishlist_button_main);
    h_wishlist_buttons->addWidget(read_only_wishlist);
    h_wishlist_buttons->addWidget(generate_and_clear_wishlist);
    main_data_and_wishlist_buttons->addLayout(h_wishlist_buttons);

    add_wishlist_button_main->setFixedSize(285,70);
    generate_wishlist_button_main->setFixedSize(285,70);
    clear_wishlist_button_main->setFixedSize(285,70);
    read_only_wishlist->setFixedSize(285,70);
    generate_and_clear_wishlist->setFixedSize(285, 70);
}


void Offer_ui::restart(vector<Offer> elems) {
    this->elements = elems;
    this->offers->clear();
    QStringList str_list;
    std::transform(elems.begin(), elems.end(), std::back_inserter(str_list), [](const Offer &offer){return QString::fromStdString(offer.to_string());});
    this->offers->addItems(str_list);
}

void Offer_ui::define_tabs() {
    page1->setLayout(main_box_layout);

    page2->setLayout(main_wishlist_box_layout);

    tab_widget = new QTabWidget();
    tab_widget->addTab(page1,"Offers");
    tab_widget->addTab(page2,"Wishlist");
    tab_widget->resize(1300,785);

    tab_widget->show();
}

void Offer_ui::connection() {

    QObject::connect(this->offers,
                     &QListWidget::itemSelectionChanged,
                     [this](){
                         int i = this->selec_index();
                         if(i >= elements.size())
                             return;
                         auto elem = this->elements.at(i);
                         this->nameEdit->setText(QString::fromStdString(elem.get_name()));
                         this->destinationEdit->setText(QString::fromStdString(elem.get_destination()));
                         this->typeEdit->setText(QString::fromStdString(elem.get_type()));
                         this->priceEdit->setText(QString::fromStdString(elem.get_price()));
                     });

    QObject::connect(this->add_button,
                     &QPushButton::clicked,
                     [this](){
                         auto name = this->nameEdit->text().toStdString();
                         auto destination = this->destinationEdit->text().toStdString();
                         auto type = this->typeEdit->text().toStdString();
                         auto price = this->priceEdit->text().toStdString();

                         if(name.empty() or destination.empty() or type.empty() or price.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             return;
                         }
                         try{
                             this->service.add_offer(name, destination, type, price);
                         }
                         catch (const RepoException &ex){
                             QMessageBox::critical(this,"Error",QString::fromStdString(ex.get_msg()));
                             this->restart(this->service.getAll());
                             return;
                         }
                         catch (const Validation &ex) {
                             QMessageBox::critical(this,"Error",QString::fromStdString(ex.get_msg()));
                             this->restart(this->service.getAll());
                             return;
                         }
                         this->restart(this->service.getAll());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->update_button,
                     &QPushButton::clicked,
                     [this](){
                         auto name = this->nameEdit->text().toStdString();
                         auto destination = this->destinationEdit->text().toStdString();
                         auto type = this->typeEdit->text().toStdString();
                         auto price = this->priceEdit->text().toStdString();

                         if(name.empty() or destination.empty() or type.empty() or price.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             return;
                         }
                         try{
                             this->service.update_offer(name, destination, type, price);
                         }
                         catch (const RepoException &ex){
                             QMessageBox::critical(this,"Error",QString::fromStdString(ex.get_msg()));
                             this->restart(this->service.getAll());
                             return;
                         }
                         catch (const Validation &ex) {
                             QMessageBox::critical(this,"Error",QString::fromStdString(ex.get_msg()));
                             this->restart(this->service.getAll());
                             return;
                         }
                         this->restart(this->service.getAll());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->remove_button,
                     &QPushButton::clicked,
                     [this](){
                         auto name = this->nameEdit->text().toStdString();

                         if(name.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             return ;
                         }
                         try{
                             this->service.remove_offer(name);
                         }
                         catch (const RepoException &ex){
                             QMessageBox::critical(this,"Error",QString::fromStdString(ex.get_msg()));
                             this->restart(this->service.getAll());
                             return;
                         }
                         this->restart(this->service.getAll());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->find_button,
                     &QPushButton::clicked,
                     [this](){
                         auto name = this->nameEdit->text().toStdString();
                         if(name.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             return ;
                         }
                         try{
                             auto oferta = this->service.find_offer(name);
                             QMessageBox::information(this, "Found", QString::fromStdString(oferta.to_string()));
                         }
                         catch (const RepoException &ex) {
                             QMessageBox::critical(this, "Error", QString::fromStdString(ex.get_msg()));
                             this->restart(this->service.getAll());
                             return;
                         }
                         this->restart(this->service.getAll());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(
            this->undo_button,
            &QPushButton::clicked,
            [this](){
                try {
                    this->service.undo();
                }
                catch (const RepoException &ex) {
                    QMessageBox::warning(this,"Error",QString::fromStdString(ex.get_msg()));
                    return;
                }
                this->restart(this->service.getAll());

                this->nameEdit->clear();
                this->destinationEdit->clear();
                this->typeEdit->clear();
                this->priceEdit->clear();
            }
    );

    QObject::connect(this->destination_filter_button,
                     &QPushButton::clicked,
                     [this](){
                         auto name = this->destinationEdit->text().toStdString();
                         if(name.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             return ;
                         }
                         auto the_offers = service.filter_by_destination(name);
                         if(the_offers.empty())
                         {
                             QMessageBox::warning(this,"Error","There are no offers");
                             return;
                         }
                         this->restart(the_offers);

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->price_filter_button,
                     &QPushButton::clicked,
                     [this](){
                         auto price = this->priceEdit->text().toStdString();
                         if(price.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             return ;
                         }
                         auto the_offers = service.filter_by_price(price);
                         if(the_offers.empty())
                         {
                             QMessageBox::warning(this,"Error","There are no offers");
                             return;
                         }
                         this->restart(the_offers);

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->remove_all_filters_button,
                     &QPushButton::clicked,
                     [this](){
                         this->restart(service.getAll());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->sort_by_name_button,
                     &QPushButton::clicked,
                     [this](){
                         service.sort_offers("name");
                         this->restart(service.getAll());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->sort_by_destination_button,
                     &QPushButton::clicked,
                     [this](){
                         service.sort_offers("destination");
                         this->restart(service.getAll());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->sort_by_type_and_price_button,
                     &QPushButton::clicked,
                     [this](){
                         service.sort_offers("type and price");
                         this->restart(service.getAll());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });

    QObject::connect(this->add_wishlist_button_main,
                     &QPushButton::clicked,
                     [this](){
                         auto name = nameEdit->text().toStdString();
                         if(name.empty())
                         {
                             QMessageBox::warning(this,"Error","Name field is empty");
                             return ;
                         }
                         try {
                             this->service.add_to_wishlist(name);
                         }
                         catch (const RepoException &ex) {
                             QMessageBox::warning(this,"Error",QString::fromStdString(ex.get_msg()));
                             return ;
                         }
                         this->restart_wishlist(this->service.getAllWishlist());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                     });
    QObject::connect(this->generate_wishlist_button_main,
                     &QPushButton::clicked,
                     [this](){
                         auto nr =(this->numberEdit->text().toStdString());
                         if(nr.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             this->nameEdit->clear();
                             this->destinationEdit->clear();
                             this->typeEdit->clear();
                             this->priceEdit->clear();
                             this->numberEdit->clear();
                             return;
                         }
                         int number;
                         try{
                             number = stoi(nr);}
                         catch (const std::exception& e) {
                             QMessageBox::warning(this, "Error", "There needs to be a number in the field");
                             this->nameEdit->clear();
                             this->destinationEdit->clear();
                             this->typeEdit->clear();
                             this->priceEdit->clear();
                             this->numberEdit->clear();
                             return;
                         }
                         if(number < 1)
                         {
                             QMessageBox::warning(this, "Error", "An empty wishlist cannot be generated");
                             this->nameEdit->clear();
                             this->destinationEdit->clear();
                             this->typeEdit->clear();
                             this->priceEdit->clear();
                             this->numberEdit->clear();
                             return;
                         }

                         if(number > 25)
                         {
                             QMessageBox::warning(this,"Error","You cannot add more than 25 offers to your wishlist");
                             this->nameEdit->clear();
                             this->destinationEdit->clear();
                             this->typeEdit->clear();
                             this->priceEdit->clear();
                             this->numberEdit->clear();
                             return;
                         }

                         this->service.generate_wishlist(number);

                         this->restart_wishlist(this->service.getAllWishlist());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                         this->numberEdit->clear();
                     });

    QObject::connect(this->clear_wishlist_button_main,
                     &QPushButton::clicked,
                     [this](){

                         this->service.clear_wishlist();

                         this->restart_wishlist(this->service.getAllWishlist());

                         this->nameEdit->clear();
                         this->destinationEdit->clear();
                         this->typeEdit->clear();
                         this->priceEdit->clear();
                         this->numberEdit->clear();
                     });

    connect(read_only_wishlist, &QPushButton::clicked, this, &Offer_ui::read_only_wishlist_window);

    QObject::connect(generate_and_clear_wishlist,
                     &QPushButton::clicked,
                     [this](){
                         generate_and_clear_wishlist_window();
                     });

}

void Offer_ui::define_main_wishlist() {
    this->page2 = new QWidget();
    this->wishlist = new QListWidget;
    this->table_wishlist = new QTableWidget;
    this->main_wishlist_box_layout->addWidget(this->table_wishlist);
    h_wishlist_layout = new QHBoxLayout;
    new_data_wishlist_layout = new QFormLayout;
    methods_wishlist_layout = new QFormLayout;
}

void Offer_ui::define_data_layout_wishlist()
{
    this->name_wishlist_edit = new QLineEdit;
    this->offer_number = new QLineEdit;
    this->export_file = new QLineEdit;

    this->name_wishlist_edit->setFixedHeight(45);
    this->offer_number->setFixedHeight(45);
    this->export_file->setFixedHeight(45);

    this->name_wishlist_edit->setFixedWidth(270);
    this->offer_number->setFixedWidth(270);
    this->export_file->setFixedWidth(270);

    new_data_wishlist_layout->setVerticalSpacing(30);
    new_data_wishlist_layout->setHorizontalSpacing(30);

    new_data_wishlist_layout->addRow(QString("Name"), this->name_wishlist_edit);
    new_data_wishlist_layout->addRow(QString("Number of added offers"), this->offer_number);
    new_data_wishlist_layout->addRow(QString("File for export"), this->export_file);

    h_wishlist_layout->addLayout(new_data_wishlist_layout);
}

void Offer_ui::define_methods_wishlist()
{
    this->add_wishlist_button = new QPushButton("Add to wishlist");
    this->generate_wishlist_button = new QPushButton("Generate wishlist");
    this->clear_wishlist_button = new QPushButton("Clear wishlist");
    this->export_wishlist_button = new QPushButton("Export wishlist");

    this->add_wishlist_button->setStyleSheet(QString("background-color: rgb(51, 19, 19);"));
    this->generate_wishlist_button->setStyleSheet(QString("background-color: rgb(51, 19, 19);"));
    this->clear_wishlist_button->setStyleSheet(QString("background-color: rgb(51, 19, 19);"));
    this->export_wishlist_button->setStyleSheet(QString("background-color: rgb(51, 19, 19);"));

    this->methods_wishlist_layout->addWidget(this->add_wishlist_button);
    this->methods_wishlist_layout->addWidget(this->generate_wishlist_button);
    this->methods_wishlist_layout->addWidget(this->clear_wishlist_button);
    this->methods_wishlist_layout->addWidget(this->export_wishlist_button);

    this->add_wishlist_button->setFixedHeight(60);
    this->generate_wishlist_button->setFixedHeight(60);
    this->clear_wishlist_button->setFixedHeight(60);
    this->export_wishlist_button->setFixedHeight(60);

    this->add_wishlist_button->setFixedWidth(260);
    this->generate_wishlist_button->setFixedWidth(260);
    this->clear_wishlist_button->setFixedWidth(260);
    this->export_wishlist_button->setFixedWidth(260);

    h_wishlist_layout->addLayout(methods_wishlist_layout);
}

void Offer_ui::restart_wishlist(vector<Offer> elem) {
    this->elements = elem;
    this->wishlist->clear();
    QStringList str_list_name,str_list_dest,str_list_type,str_list_price;
    std::transform(elem.begin(), elem.end(), std::back_inserter(str_list_name), [](const Offer &offer){return QString::fromStdString(
            offer.get_destination());});
    this->wishlist->addItems(str_list_name);
    std::transform(elem.begin(), elem.end(), std::back_inserter(str_list_dest), [](const Offer &offer){return QString::fromStdString(
            offer.get_name());});
    this->wishlist->addItems(str_list_dest);
    std::transform(elem.begin(), elem.end(), std::back_inserter(str_list_type), [](const Offer &offer){return QString::fromStdString(
            offer.get_type());});
    this->wishlist->addItems(str_list_type);
    std::transform(elem.begin(), elem.end(), std::back_inserter(str_list_price), [](const Offer &offer){return QString::fromStdString(
            offer.get_price());});
    this->wishlist->addItems(str_list_price);

    table_wishlist_define();
}


void Offer_ui::connect_wishlist() {
    QObject::connect(this->add_wishlist_button,
                     &QPushButton::clicked,
                     [this](){
                         auto name = this->name_wishlist_edit->text().toStdString();

                         if(name.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             return;
                         }
                         try {
                             this->service.add_to_wishlist(name);
                         }
                         catch (const RepoException &ex) {
                             QMessageBox::warning(this,"Error",QString::fromStdString(ex.get_msg()));
                             return;
                         }

                         this->restart_wishlist(this->service.getAllWishlist());

                         this->name_wishlist_edit->clear();
                         this->offer_number->clear();
                         this->export_file->clear();
                     });

    QObject::connect(this->generate_wishlist_button,
                     &QPushButton::clicked,
                     [this](){
                         auto nr =(this->offer_number->text().toStdString());
                         if(nr.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             this->name_wishlist_edit->clear();
                             this->offer_number->clear();
                             this->export_file->clear();
                             return;
                         }
                         int number;
                         try{
                             number = stoi(nr);
                         }
                         catch (const std::exception& e) {
                             QMessageBox::warning(this, "Error", "There needs to be a number in the field");
                             this->name_wishlist_edit->clear();
                             this->offer_number->clear();
                             this->export_file->clear();
                             return;
                         }
                         if(number < 1)
                         {
                             QMessageBox::warning(this, "Error", "An empty wishlist cannot be generated");
                             this->name_wishlist_edit->clear();
                             this->offer_number->clear();
                             this->export_file->clear();
                             return;
                         }

                         if(number > 25)
                         {
                             QMessageBox::warning(this,"Error","You cannot add more than 25 offers to your wishlist");
                             this->name_wishlist_edit->clear();
                             this->offer_number->clear();
                             this->export_file->clear();
                             return;
                         }

                         this->service.generate_wishlist(number);

                         this->restart_wishlist(this->service.getAllWishlist());

                         this->name_wishlist_edit->clear();
                         this->offer_number->clear();
                         this->export_file->clear();
                     });

    QObject::connect(this->clear_wishlist_button,
                     &QPushButton::clicked,
                     [this](){

                         this->service.clear_wishlist();

                         this->restart_wishlist(this->service.getAllWishlist());

                         this->name_wishlist_edit->clear();
                         this->offer_number->clear();
                         this->export_file->clear();
                     });

    QObject::connect(this->export_wishlist_button,
                     &QPushButton::clicked,
                     [this](){
                         auto file = this->export_file->text().toStdString();
                         if(file.empty())
                         {
                             QMessageBox::warning(this, "Error", "There cannot be empty fields");
                             return;
                         }
                         if(service.getAllWishlist().empty())
                         {
                             {
                                 QMessageBox::warning(this, "Error", "The wishlist cannot be empty");
                                 return;
                             }
                         }
                         this->service.export_CSV("..//" + file);

                         this->restart_wishlist(this->service.getAllWishlist());

                         this->name_wishlist_edit->clear();
                         this->offer_number->clear();
                         this->export_file->clear();
                     });
}

void Offer_ui::table_wishlist_define() {
    table_wishlist->clear();
    table_wishlist->setColumnCount(4);
    table_wishlist->setHorizontalHeaderLabels({"Name","Destination","Type","Price"});
    auto count = this->wishlist->count();
    table_wishlist->setRowCount(count/4);
    for(int i=0;i<count/4;i++)
    {
        auto *item_name = new QTableWidgetItem(this->wishlist->item(i)->text());
        table_wishlist->setItem(i, 1, item_name);
        auto *item_dest = new QTableWidgetItem(this->wishlist->item(i+count/4)->text());
        table_wishlist->setItem(i,0,item_dest);
        auto *item_type = new QTableWidgetItem(this->wishlist->item(i + 2 * count / 4)->text());
        table_wishlist->setItem(i, 2, item_type);
        auto *item_price = new QTableWidgetItem(this->wishlist->item(i + 3 * count / 4)->text());
        table_wishlist->setItem(i, 3, item_price);
    }
    table_wishlist->setColumnWidth(0,200);
    table_wishlist->setColumnWidth(1,250);
    table_wishlist->setColumnWidth(2,200);
    table_wishlist->setColumnWidth(3,200);
}

int Offer_ui::selec_index() {
    auto index = this->offers->selectionModel()->currentIndex();
    return index.row();
}