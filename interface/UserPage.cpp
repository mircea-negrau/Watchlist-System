//
// Created by Mircea on 5/6/2021.
//

#include <fstream>
#include "UserPage.h"

UserPage::UserPage(AdminService &admin_service, UserService &user_service, QWidget *parent) : admin_service{
        admin_service}, user_service{user_service}, QWidget{parent} {

    this->initialize_page();
    this->connect_signals();
}

void UserPage::connect_signals() {
    QObject::connect(this->remove_tutorial_button, &QPushButton::clicked, this,
                     &UserPage::remove_tutorial_button_handler);
    QObject::connect(this->get_filtered_button, &QPushButton::clicked, this,
                     &UserPage::filter_tutorials_button_handler);
    QObject::connect(this->save, &QPushButton::clicked, this,
                     &UserPage::save_button_handler);
    QObject::connect(this->back_button, &QPushButton::clicked, this, &UserPage::back_button_handler);
    QObject::connect(this->undo_button, &QPushButton::clicked, this, &UserPage::undo_handler);
    QObject::connect(this->redo_button, &QPushButton::clicked, this, &UserPage::redo_handler);
    QObject::connect(this, SIGNAL(back_to_main_menu_signal()), this, SLOT(back_to_main_menu()));
    auto *undo_shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
    QObject::connect(undo_shortcut, &QShortcut::activated, this, &UserPage::undo_handler);
    auto *redo_shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);
    QObject::connect(redo_shortcut, &QShortcut::activated, this, &UserPage::redo_handler);
}

void UserPage::initialize_page() {
    this->setWindowTitle("User Page");
    auto *main_layout = new QHBoxLayout{this};
    this->setStyleSheet("QWidget { background-color:#181818; font: bold 20px 'Verdana'; }"
                        "QRadioButton { color:#f1f1f1; }"
                        "QLabel { color:#f1f1f1; }"
                        "QListWidget { background-color:#121212; color:#f1f1f1; selection-background-color:#303030; }"
                        "QLineEdit { background-color:#121212; color:#f1f1f1; }"
                        "QPushButton {\n"
                        "    background-color: #303030;\n"
                        "    border-style: outset;\n"
                        "    border-width: 1px;\n"
                        "    border-radius: 10px;\n"
                        "    border-color: #303030;\n"
                        "    color: #909090;\n"
                        "    min-width: 7em;\n"
                        "    padding: 6px;"
                        "    margin: 6px;"
                        "}"
                        "QTableView {\n"
                        "   background-color: #303030;\n"
                        "   color:#f1f1f1;\n"
                        "}\n"
                        "QHeaderView {\n"
                        "   color:#f1f1f1\n"
                        "}"
                        "QPushButton:pressed { background-color: #d7d7d7; color:#181818; border-style: inset; }");

    auto *left_widget = new QWidget{};
    auto *left_vertical_layout = new QVBoxLayout{left_widget};

    this->tableModel = new TutorialsTableModel{this->user_service};
    tableView = new QTableView;
    proxyModel = new QSortFilterProxyModel{};
    tableView->setSortingEnabled(true);
    proxyModel->setSourceModel(this->tableModel);
    proxyModel->setFilterFixedString("");
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(1);
    tableView->setModel(proxyModel);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->resizeColumnsToContents();
    max_rows = tableView->model()->rowCount();

    left_widget->setMinimumWidth(1252);
    left_vertical_layout->addWidget(tableView);

    auto *buttons_widget = new QWidget{};
    auto *buttons_layout = new QHBoxLayout{buttons_widget};
    this->undo_button = new QPushButton("UNDO");
    this->remove_tutorial_button = new QPushButton("REMOVE");
    this->redo_button = new QPushButton("REDO");
    buttons_layout->addWidget(this->undo_button);
    buttons_layout->addWidget(this->remove_tutorial_button);
    buttons_layout->addWidget(this->redo_button);

    left_vertical_layout->addWidget(buttons_widget);

    auto *right_widget = new QWidget{};
    auto *filter_layout = new QVBoxLayout{right_widget};
    this->filter_edit = new QLineEdit{};
    this->get_filtered_button = new QPushButton("Filter");
    this->get_filtered_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->get_filtered_button->setMaximumWidth(300);
    this->get_filtered_button->setMinimumWidth(200);
    this->back_button = new QPushButton("Back");
    this->save = new QPushButton("Open");
    filter_edit->setPlaceholderText("Presenter");
    filter_layout->addWidget(this->filter_edit);
    filter_layout->addWidget(this->get_filtered_button);
    radio_html = new QRadioButton("HTML");
    radio_html->setChecked(true);
    radio_csv = new QRadioButton("CSV");
    filter_layout->addWidget(radio_html);
    filter_layout->addWidget(radio_csv);
    filter_layout->addWidget(this->save);
    filter_layout->addWidget(this->back_button);

    main_layout->addWidget(left_widget);
    main_layout->addWidget(right_widget);
}

void UserPage::remove_tutorial_button_handler() {
    QList<QModelIndex> indexes = tableView->selectionModel()->selectedIndexes();
    for (auto index:indexes) {
        std::string link = index.sibling(index.row(), 5).data().toString().toStdString();
        this->tableModel->removeRow(index, link);
    }
}

void UserPage::filter_tutorials_button_handler() {
    vector tutorials;
    string filter, answer;
    filter = this->filter_edit->text().toStdString();
    if (filter.empty()) {
        tutorials = this->user_service.get_all_tutorials_missing_from_watchlist();
    } else
        tutorials = this->user_service.get_all_tutorials_missing_from_watchlist_filtered(filter);
    if (tutorials.empty())
        QMessageBox::critical(nullptr, "Error", "No tutorials found!");
    else {
        bool stopped = false;
        while (!stopped) {
            for (auto &tutorial : tutorials) {
                const string &link = tutorial.get_link();
                ShellExecuteA(nullptr, "open", link.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
                QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Question", "Add to Watchlist?");
                if (reply == QMessageBox::Yes) {
                    this->tableModel->createNewRow(tutorial);
                }
                reply = QMessageBox::question(nullptr, "Question", "Continue to next?");
                if (reply == QMessageBox::No) {
                    stopped = true;
                    break;
                }
            }
            if (!stopped) {
                QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Question",
                                                                          "No tutorials left! Start from beginning?");
                if (reply == QMessageBox::No)
                    stopped = true;
                else {
                    if (filter.empty()) {
                        tutorials = this->user_service.get_all_tutorials_missing_from_watchlist();
                    } else
                        tutorials = this->user_service.get_all_tutorials_missing_from_watchlist_filtered(filter);
                    if (tutorials.empty()) {
                        QMessageBox::critical(nullptr, "Error", "No tutorials found!");
                        stopped = true;
                    }
                }
            }
        }
    }
}

void UserPage::open_as_html(vector &tutorials) {
    string full_save_path = this->save_path + ".html";
    std::ofstream output_stream(full_save_path);
    output_stream << "<!DOCTYPE html>\n"
                     "<html>\n"
                     "<head>\n"
                     "  <link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\">\n"
                     "  <title>Tutorial Watchlist</title>\n"
                     "</head>\n"
                     "<body style=\"background-color:#212529\">\n"
                     "<table class=\"table table-striped table-dark table-hover\">\n"
                     "<thead>\n"
                     "<tr>\n"
                     "  <th scope=\"col\">#</th>\n"
                     "  <th scope=\"col\">Title</th>\n"
                     "  <th scope=\"col\">Presenter</th>\n"
                     "  <th scope=\"col\">Duration</th>\n"
                     "  <th scope=\"col\">Likes</th>\n"
                     "  <th scope=\"col\">Link</th>\n"
                     "</tr>\n"
                     "</thead>\n"
                     "<tbody>\n";
    int row = 0;
    for_each(tutorials.begin(), tutorials.end(), [&output_stream, &row](auto &t) {
        output_stream << "<tr>\n";
        output_stream << "<th scope=\"row\">" << ++row << "</th>\n";
        output_stream << "<td>" << t.get_title() << "</td>\n";
        output_stream << "<td>" << t.get_presenter() << "</td>\n";
        auto length = t.get_length();
        output_stream << "<td>" << length.first << "m ";
        output_stream << length.second << "s</td>\n";
        output_stream << "<td>" << t.get_likes() << "</td>\n";
        output_stream << "<td><a href=\"https://" << t.get_link() << "\">Link</a></td>\n";
        output_stream << "</tr>\n";
    });
    output_stream << "</tbody>\n";
    output_stream << "</table>\n"
                     "</body>\n"
                     "</html>";
    ShellExecuteA(nullptr, "open", full_save_path.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

void UserPage::open_as_csv(vector &tutorials) {
    string full_save_path = this->save_path + ".csv";
    std::ofstream output_stream(save_path);
    for_each(tutorials.begin(), tutorials.end(), [&output_stream](auto &t) {
        output_stream << t;
    });
    ShellExecuteA(nullptr, "open", full_save_path.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

void UserPage::save_button_handler() {
    vector tutorials = this->user_service.get_all_watchlist_tutorials();
    if (this->radio_html->isChecked())
        this->open_as_html(tutorials);
    else
        this->open_as_csv(tutorials);
}

void UserPage::back_to_main_menu() {
    auto *widget = new MainPage{this->admin_service, this->user_service};
    widget->show();
    close();
}

void UserPage::undo_handler() {
    Command *last_command = user_service.get_undo();
    if (last_command != nullptr) {
        if (last_command->get_type() == "add") {
            tableModel->undoAddRow();
        } else {
            tableModel->undoRemoveRow();
        }
    }
}

void UserPage::redo_handler() {
    Command *last_command = user_service.get_redo();
    if (last_command != nullptr) {
        if (last_command->get_type() == "add") {
            tableModel->redoAddRow();
        } else {
            tableModel->redoRemoveRow();
        }
    }

}

void UserPage::back_button_handler() {
    emit back_to_main_menu_signal();
}


UserPage::~UserPage() = default;
