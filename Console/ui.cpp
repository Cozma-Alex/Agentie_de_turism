#include "ui.h"
#include <iostream>
#include <string>

using namespace std;

void ConsoleUI::ui_print(const vector<Offer>& offers) {
    if(offers.empty())
    {
        cout<<"There are no offers\n";
        return;
    }
    cout<<"offers:\n";
    for (const auto& offer:offers) {
        cout << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << endl;
    }
    cout<<"End of the offers list!\n";
}

void ConsoleUI::ui_print_wishlist(const vector<Offer>& offers) {
    if(offers.empty())
    {
        cout<<"There are no offers\n";
        return;
    }
    cout<<"offers:\n";
    for (const auto& offer:offers) {
        cout << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << endl;
    }
    cout<<"End of the offers list!\n";
}

void ConsoleUI::ui_add_offer() {
    string name,type,destination, price;
    cout<<"Give name:";
    getline(cin>>ws, name);
    cout<<"Give type:";
    getline(cin, type);
    cout<<"Give destination:";
    getline(cin, destination);
    cout<<"Give price:";
    getline(cin, price);
    service.add_offer(name, destination, type, price);
    cout<<"Offer succesfully added!\n";
}

void ConsoleUI::ui_remove_offer() {
    string name;
    cout<<"Give name:";
    cin >> name;
    service.remove_offer(name);
    cout<<"Offer successfully removed!\n";
}

void ConsoleUI::ui_update_offer() {
    string name,type,destination, price;
    cout<<"Give name:";
    getline(cin>>ws, name);
    cout<<"Give type:";
    getline(cin, type);
    cout<<"Give destination:";
    getline(cin, destination);
    cout<<"Give price:";
    getline(cin, price);
    service.update_offer(name, destination, type, price);
    cout<<"Offer successfully updated!\n";
}

void ConsoleUI::ui_find_offer() {
    string name;
    cout<<"Give name:";
    getline(cin>>ws, name);
    Offer o;
    o = service.find_offer(name);
    cout << o.get_name() << " " << o.get_destination() << " " << o.get_type() << " " << o.get_price() << endl;
}

void ConsoleUI::ui_filter_by_destination() {
    string destination;
    cout<<"Give destination:";
    getline(cin>>ws, destination);
    auto offers2 = service.filter_by_destination(destination);
    if(offers2.empty())
    {
        cout<<"There are no offers\n";
        return;
    }
    cout<<"offers:\n";
    for(const auto& offer: offers2)
    {
        cout << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << " \n";
    }
    cout<<"End of the offers list.\n";
}

void ConsoleUI::ui_filter_by_price() {
    string price;
    cout<<"Give price:";
    getline(cin>>ws, price);
    auto offers2 = service.filter_by_price(price);
    if(offers2.empty())
    {
        cout<<"There are no offers\n";
        return;
    }
    cout<<"offers:\n";
    for(const auto& offer: offers2)
    {
        cout << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << " \n";
    }
    cout<<"End of the offers list.\n";
}

void ConsoleUI::ui_sort_by_name() {
    auto offers = service.sort_offers("name");
    if(offers.empty())
    {
        cout<<"There are no offers\n";
        return;
    }
    cout<<"offers:\n";
    for(const auto& offer: offers)
    {
        cout << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << " \n";
    }
    cout<<"End of the offers list.\n";
}

void ConsoleUI::ui_sort_by_destination() {
    auto offers = service.sort_offers("destination");
    if(offers.empty())
    {
        cout<<"There are no offers\n";
        return;
    }
    cout<<"offers:\n";
    for(const auto& offer: offers)
    {
        cout << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << " \n";
    }
    cout<<"End of the offers list.\n";
}

void ConsoleUI::ui_sort_by_type_and_price() {
    auto offers = service.sort_offers("type and price");
    if(offers.empty())
    {
        cout<<"There are no offers\n";
        return;
    }
    cout<<"offers:\n";
    for(const auto& offer: offers)
    {
        cout << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << " \n";
    }
    cout<<"End of the offers list.\n";
}

void ConsoleUI::ui_clear_wishlist() {
    service.clear_wishlist();
}

void ConsoleUI::ui_add_to_wishlist() {
    string name;
    cout<<"Give name:";
    getline(cin>>ws, name);
    service.add_to_wishlist(name);
}

void ConsoleUI::ui_generate_wishlist() {
    int nr;
    cout<<"Give the number of offers:";
    cin>>nr;
    if(0 >= nr or nr > service.getAll().size())
    {
        cout<<"Number of offers is invalid\n";
        return;
    }
    service.generate_wishlist(nr);
}

void ConsoleUI::ui_report() {
    map<string, vector<Offer>> report;
    report = service.generate_report();
    if(report.empty())
    {
        cout<<"There are no offers\n";
        return;
    }
    cout<<"Report:\n";
    for (const auto& type:report) {
        cout << type.first << ":\n";
        for (const auto& offer: type.second) {
            cout << offer.get_name() << " " << offer.get_destination() << " " << offer.get_type() << " " << offer.get_price() << " \n";
        }
    }
    cout<<"End of report\n";
}

void ConsoleUI::ui_undo() {
    service.undo();
}


void ConsoleUI::ui_export() {
    string file;
    cout<<"Give the name of the export file: ";
    getline(cin>>ws, file);
    service.export_CSV("..//" + file + ".csv");
}

void ConsoleUI::start()
{
    cout<<"How will the data be stored:\n";
    cout<<"1. File\n";
    cout<<"2. Internal memory\n";
    int type_memory;
    cin >> type_memory;
    switch (type_memory) {
        case 1:
            service.memory_set("File");
            break;
        case 2:
            service.memory_set("Memory");
            break;
        default:
            cout<<"Invalid Choice!\n";
    }
    cout<<"\n\n";
    while (true){
        cout<<"Number of offers in wishlist:"<<service.getAllWishlist().size()<<endl;
        cout<<"1. Add offer\n";
        cout<<"2. Print offers\n";
        cout<<"3. Remove offer\n";
        cout<<"4. Update offer\n";
        cout<<"5. Find offer\n";
        cout<<"6. Filter by destination\n";
        cout<<"7. Filter by price\n";
        cout<<"8. Sort by name\n";
        cout<<"9. Sort by destination\n";
        cout<<"10. Sort by type and price\n";
        cout<<"11. Clear Wishlist\n";
        cout<<"12. Add offer in Wishlist\n";
        cout<<"13. Generate Wishlist\n";
        cout<<"14. Print Wishlist\n";
        cout<<"15. Report\n";
        cout<<"16. Undo\n";
        cout<<"17. Export to CSV\n";
        cout<<"0. Exit\n";
        cout<<"Enter the order:";
        int command;
        cin >> command;
        try{
            switch (command) {
                case 1:
                    ui_add_offer();
                    break;
                case 2:
                    ui_print(service.getAll());
                    break;
                case 3:
                    ui_remove_offer();
                    break;
                case 4:
                    ui_update_offer();
                    break;
                case 5:
                    ui_find_offer();
                    break;
                case 6:
                    ui_filter_by_destination();
                    break;
                case 7:
                    ui_filter_by_price();
                    break;
                case 8:
                    ui_sort_by_name();
                    break;
                case 9:
                    ui_sort_by_destination();
                    break;
                case 10:
                    ui_sort_by_type_and_price();
                    break;
                case 11:
                    ui_clear_wishlist();
                    break;
                case 12:
                    ui_add_to_wishlist();
                    break;
                case 13:
                    ui_generate_wishlist();
                    break;
                case 14:
                    ui_print_wishlist(service.getAllWishlist());
                    break;
                case 15:
                    ui_report();
                    break;
                case 16:
                    ui_undo();
                    break;
                case 17:
                    ui_export();
                    break;
                case 0:
                    return;
                default:
                    cout<<"Invalid command!\n";
            }
        }
        catch(const RepoException& ex)
        {cout<<ex<<endl;}

        catch(const Validation& ev)
        {cout<<ev<<endl;}
    }
}
