//
// Created by Mircea on 5/6/2021.
//

#include "MainPage.h"
#include "AdminPage.h"
#include "UserPage.h"

MainPage::MainPage(AdminService &admin_service, UserService &user_service, QWidget *parent) : admin_service{
        admin_service},
                                                                                              user_service{
                                                                                                      user_service},
                                                                                              QWidget{parent} {
    this->initialize_page();
    this->connect_signals();
}

void MainPage::connect_signals() {
    QObject::connect(this->admin_button, &QPushButton::clicked, this, &MainPage::admin_button_handler);
    QObject::connect(this->user_button, &QPushButton::clicked, this, &MainPage::user_button_handler);
    QObject::connect(this, SIGNAL(AdminLoginSignal()), this, SLOT(open_admin()));
    QObject::connect(this, SIGNAL(UserLoginSignal()), this, SLOT(open_user()));
}

void MainPage::initialize_page() {
    this->setWindowTitle("Main Page");
    this->setStyleSheet("QWidget { background-color:#181818; font: bold 20px 'Verdana'; }"
                        "QRadioButton { color:#f1f1f1; }"
                        "QLabel { color:#f1f1f1; font: bold 24px; margin: 16px; }"
                        "QListWidget { background-color:#121212; color:#f1f1f1; selection-background-color:#303030; }"
                        "QLineEdit { background-color:#121212; color:#f1f1f1; }"
                        "QPushButton {\n"
                        "    background-color: #303030;\n"
                        "    border-style: outset;\n"
                        "    border-width: 1px;\n"
                        "    border-radius: 15px;\n"
                        "    border-color: #303030;\n"
                        "    color: #909090;\n"
                        "    min-width: 7em;\n"
                        "    padding: 6px;\n"
                        "    margin: 6px;\n"
                        "}"
                        "QPushButton:pressed { background-color: #d7d7d7; color:#181818; border-style: inset; }");
    auto *main_layout = new QVBoxLayout{};
    this->setLayout(main_layout);

    auto *information = new QWidget{};
    auto *text_layout = new QVBoxLayout{};
    information->setLayout(text_layout);
    auto *label = new QLabel{"Choose login:"};
    label->setAlignment(Qt::AlignCenter);
    text_layout->addWidget(label);
    main_layout->addWidget(information);

    auto *buttons = new QWidget{};
    auto *horizontal_layout = new QHBoxLayout{};
    this->admin_button = new QPushButton("ADMIN");
    this->user_button = new QPushButton("USER");
    horizontal_layout->addWidget(this->admin_button);
    horizontal_layout->addWidget(this->user_button);
    buttons->setLayout(horizontal_layout);

    main_layout->addWidget(buttons);
}

void MainPage::admin_button_handler() {
    emit AdminLoginSignal();
}

void MainPage::user_button_handler() {
    emit UserLoginSignal();
}

void MainPage::open_admin() {
    auto *widget = new AdminPage{this->admin_service, this->user_service};
    widget->show();
    close();
}

void MainPage::open_user() {
    auto *widget = new UserPage{this->admin_service, this->user_service};
    widget->show();
    close();
}

MainPage::~MainPage() = default;
