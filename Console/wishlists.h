#pragma once
#include <QWidget>
#include "QDebug"
#include <QPaintEvent>
#include "QTime"
#include <QPainter>
#include <QRect>
#include <QBrush>
#include <QStaticText>
#include <QListWidget>
#include <QPolygon>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include "QFormLayout"
#include <QMessageBox>
#include <map>
#include <iostream>
#include "../Business/service.h"



class Read_only_wishlist:public QWidget,public Observer{
    int nr;
    ServiceOffer &service;

    void paintEvent(QPaintEvent *event) override
    {
        Q_UNUSED(event);

        QPainter painter(this);

        int triangleSize = 30;
        QColor triangleColor = Qt::darkGreen;

        for (int i = 0; i < nr; ++i)
        {
            // Generate random position for each triangle
            int x = rand() % (width() - triangleSize);
            int y = rand() % (height() - triangleSize);

            // Create a triangle polygon
            QPolygon triangle;
            triangle << QPoint(x, y);
            triangle << QPoint(x + triangleSize, y);
            triangle << QPoint(x + triangleSize / 2, y + triangleSize);

            // Set the brush color for the triangle
            painter.setBrush(triangleColor);

            // Draw the triangle
            painter.drawPolygon(triangle);
        }
    }

public:
    explicit Read_only_wishlist(ServiceOffer &serv, QWidget *parent = nullptr):service{serv}{
        this->service.register_observer(this);
        srand(QTime::currentTime().msec());
        nr = service.getAllWishlist().size();
    }

    ~Read_only_wishlist(){
        this->service.unregister_observer(this);
    }

    void update(){
        nr=service.getAllWishlist().size();
    }
};

class Generare_and_Clear_wishlist:public QWidget,public Observer{
    ServiceOffer &service;

    QListWidget *offers_wishlist;
    vector<Offer> elements;

    QVBoxLayout *main_box_layout;
    QHBoxLayout *h_layout;

    QFormLayout *form_layout;

    QLineEdit *numberEdit;
    QPushButton *generate_wishlist;
    QPushButton *clear_wishlist;

    void setup(QWidget *widget){
        widget->resize(500,500);
        main_box_layout = new QVBoxLayout(widget);
        offers_wishlist = new QListWidget;
        main_box_layout->addWidget(offers_wishlist);

        h_layout = new QHBoxLayout;
        main_box_layout->addLayout(h_layout);
        form_layout = new QFormLayout;
        h_layout->addLayout(form_layout);

        numberEdit = new QLineEdit;
        numberEdit->setPlaceholderText("How many offers to wishlist");
        numberEdit->setFixedSize(310,40);
        form_layout->addWidget(numberEdit);

        generate_wishlist = new QPushButton("Generate Wishlist");
        clear_wishlist = new QPushButton("Clear Wishlsit");
        generate_wishlist->setFixedSize(310,50);
        clear_wishlist->setFixedSize(310,50);

        generate_wishlist->setStyleSheet(QString("background-color: rgb(46, 79, 79)"));
        clear_wishlist->setStyleSheet(QString("background-color: rgb(46, 79, 79)"));
        form_layout->addWidget(generate_wishlist);
        form_layout->addWidget(clear_wishlist);

        update();

        connection();
    }

    void connection(){
        QObject::connect(this->generate_wishlist,
                         &QPushButton::clicked,
                         [this](){
                             auto nr =(this->numberEdit->text().toStdString());
                             if(nr.empty())
                             {
                                 QMessageBox::warning(this, "Error", "There cannot be empty field");
                                 this->numberEdit->clear();
                                 return;
                             }
                             int number;
                             try{
                                 number = stoi(nr);}
                             catch (const std::exception& e) {
                                 QMessageBox::warning(this, "Error", "There needs to be a number in the field");
                                 this->numberEdit->clear();
                                 return;
                             }
                             if(number < 1)
                             {
                                 QMessageBox::warning(this, "Error", "An empty wishlist cannot be generated");
                                 this->numberEdit->clear();
                                 return;
                             }

                             if(number > 25)
                             {
                                 QMessageBox::warning(this,"Error","You cannot add more than 25 offers to your wishlist");
                                 this->numberEdit->clear();
                                 return;
                             }

                             this->service.generate_wishlist(number);

                             this->update();
                             this->numberEdit->clear();
                         });

        QObject::connect(this->clear_wishlist,
                         &QPushButton::clicked,
                         [this](){

                             this->service.clear_wishlist();

                             this->update();
                             this->numberEdit->clear();
                         });

    }

    int selectionIndex(){
        auto index = offers_wishlist->selectionModel()->currentIndex();
        return index.row();
    }

public:
    Generare_and_Clear_wishlist(ServiceOffer &serv):service{serv}{
        this->service.register_observer(this);
        setup(this);
        connection();
    }

    ~Generare_and_Clear_wishlist(){
        this->service.unregister_observer(this);
    }

    void update(){
        elements = service.getAllWishlist();
        this->offers_wishlist->clear();
        QStringList str_list;
        std::transform(elements.begin(), elements.end(), std::back_inserter(str_list), [](const Offer &offer){return QString::fromStdString(offer.to_string());});
        this->offers_wishlist->addItems(str_list);
    }
};
