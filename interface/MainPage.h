//
// Created by Mircea on 5/6/2021.
//

#ifndef A89_915_NEGRAU_MIRCEA_MAINPAGE_H
#define A89_915_NEGRAU_MIRCEA_MAINPAGE_H

#include <QWidget>
#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QScreen>
#include "../functionality/AdminService.h"
#include "../functionality/UserService.h"

class MainPage : public QWidget {
Q_OBJECT
public:
    MainPage(AdminService &, UserService &, QWidget *parent = nullptr);

    ~MainPage() override;

private:
    QPushButton *admin_button;
    QPushButton *user_button;

    AdminService &admin_service;
    UserService &user_service;

    void initialize_page();

    void connect_signals();

    void admin_button_handler();

    void user_button_handler();

signals:

    void AdminLoginSignal();

    void UserLoginSignal();

public slots:

    void open_admin();

    void open_user();
};


#endif //A89_915_NEGRAU_MIRCEA_MAINPAGE_H
