//
// Created by Mircea on 5/6/2021.
//

#ifndef A89_915_NEGRAU_MIRCEA_USERPAGE_H
#define A89_915_NEGRAU_MIRCEA_USERPAGE_H

#include <QtWidgets>
#include "../functionality/AdminService.h"
#include "../functionality/UserService.h"
#include <windows.h>
#include <algorithm>
#include "MainPage.h"
#include "TutorialsTableModel.h"


class UserPage : public QWidget {
Q_OBJECT
public:
    explicit UserPage(AdminService &, UserService &, QWidget *parent = nullptr);

    ~UserPage() override;

private:
    int max_rows;
    AdminService &admin_service;
    UserService &user_service;
    TutorialsTableModel* tableModel;
    QTableView* tableView;
    QListWidget *watchlist;
    QLineEdit *filter_edit;
    QPushButton *remove_tutorial_button;
    QPushButton *get_filtered_button;
    QPushButton *save;
    QPushButton *back_button;
    QPushButton *undo_button;
    QPushButton *redo_button;
    QRadioButton *radio_html;
    QRadioButton *radio_csv;
    QSortFilterProxyModel* proxyModel;
    std::string save_path = R"(C:\Users\Mircea\CLionProjects\a89-915-Negrau-Mircea\data\watchlist)";

    void initialize_page();

    void connect_signals();

    void open_as_html(vector &);

    void open_as_csv(vector &);

    void remove_tutorial_button_handler();

    void filter_tutorials_button_handler();

    void save_button_handler();

    void back_button_handler();

signals:

    void back_to_main_menu_signal();

public slots:

    void undo_handler();

    void redo_handler();

    void back_to_main_menu();
};


#endif //A89_915_NEGRAU_MIRCEA_USERPAGE_H
