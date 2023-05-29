#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "Console/ui.h"
#include "Tests/tests.h"
#include "Validator/validate.h"
#include "Console/gui.h"

int main(int argc, char* argv[]) {
    QApplication a(argc,argv);
    QApplication::setFont(QFont{"Roboto", 19});
    Offer_Validator valid;
    Repo_Offer *repo = new Repo_Offer_file;
    ServiceOffer service{repo, valid};
    Tests tests{service};
    //tests.test_all();
    Offer_ui ui{service};
    a.exec();
    delete repo;

    return 0;
}