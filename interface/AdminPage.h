//
// Created by Mircea on 5/6/2021.
//

#ifndef A89_915_NEGRAU_MIRCEA_ADMINPAGE_H
#define A89_915_NEGRAU_MIRCEA_ADMINPAGE_H

#include <QtWidgets>
#include <QtCore>
#include "../functionality/AdminService.h"
#include "../functionality/UserService.h"
#include "MainPage.h"


class AdminPage : public QWidget {
Q_OBJECT
public:
    explicit AdminPage(AdminService &, UserService &, QWidget *parent = nullptr);

    ~AdminPage() override;

private:
    AdminService &admin_service;
    UserService &user_service;
    QListWidget *tutorials_list;
    QLineEdit *title_edit;
    QLineEdit *presenter_edit;
    QLineEdit *likes_edit;
    QLineEdit *minutes_edit, *seconds_edit;
    QLineEdit *link_edit;
    QPushButton *add_tutorial_button;
    QPushButton *update_tutorial_button;
    QPushButton *delete_tutorial_button;
    QPushButton *undo_button;
    QPushButton *redo_button;
    QPushButton *back_button;

    void initialize_page();

    void connect_signals();

    void populate_tutorials_list();

    void add_tutorial_button_handler();

    void update_tutorial_button_handler();

    void delete_tutorial_button_handler();

    void back_button_handler();

    void selected_item_changed();

signals:

    void tutorials_updated_signal();

    void back_to_main_menu_signal();

public slots:

    void undo_handler();

    void redo_handler();

    int get_selected_index();

    void back_to_main_menu();
};


#endif //A89_915_NEGRAU_MIRCEA_ADMINPAGE_H
