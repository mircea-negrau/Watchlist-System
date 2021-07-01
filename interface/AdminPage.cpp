//
// Created by Mircea on 5/6/2021.
//

#include "AdminPage.h"

AdminPage::AdminPage(AdminService &admin_service, UserService &user_service, QWidget *parent) : user_service{
        user_service}, admin_service{admin_service}, QWidget{parent} {
    this->initialize_page();
    this->connect_signals();
    this->populate_tutorials_list();
}

void AdminPage::connect_signals() {
    QObject::connect(this, &AdminPage::tutorials_updated_signal, this, &AdminPage::populate_tutorials_list);
    QObject::connect(this->add_tutorial_button, &QPushButton::clicked, this, &AdminPage::add_tutorial_button_handler);
    QObject::connect(this->update_tutorial_button, &QPushButton::clicked, this,
                     &AdminPage::update_tutorial_button_handler);
    QObject::connect(this->delete_tutorial_button, &QPushButton::clicked, this,
                     &AdminPage::delete_tutorial_button_handler);
    QObject::connect(this->tutorials_list, &QListWidget::itemSelectionChanged, this,
                     [this]() { this->selected_item_changed(); });
    QObject::connect(this->back_button, &QPushButton::clicked, this, &AdminPage::back_button_handler);
    QObject::connect(this->undo_button, &QPushButton::clicked, this, &AdminPage::undo_handler);
    QObject::connect(this->redo_button, &QPushButton::clicked, this, &AdminPage::redo_handler);
    QObject::connect(this, SIGNAL(back_to_main_menu_signal()), this, SLOT(back_to_main_menu()));
    auto *undo_shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
    QObject::connect(undo_shortcut, &QShortcut::activated, this, &AdminPage::undo_handler);
    auto *redo_shortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);
    QObject::connect(redo_shortcut, &QShortcut::activated, this, &AdminPage::redo_handler);
}

void AdminPage::initialize_page() {
    this->setWindowTitle("Admin Page");
    this->setStyleSheet("QWidget { background-color:#181818; font: bold 20px 'Verdana'; }"
                        "QRadioButton { color:#f1f1f1; }"
                        "QLabel { color:#f1f1f1; }"
                        "QListWidget { background-color:#121212; color:#f1f1f1; selection-background-color:#303030; }"
                        "QLineEdit { background-color:#121212; color:#f1f1f1; }"
                        "QMessageBox { background-color:#181818; }"
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
                        "QPushButton:pressed { background-color: #d7d7d7; color:#181818; border-style: inset; }");
    auto *main_layout = new QHBoxLayout{this};

    this->tutorials_list = new QListWidget{};
    this->tutorials_list->setMinimumWidth(350);
    this->tutorials_list->setSelectionMode(QAbstractItemView::SingleSelection);
    main_layout->addWidget(this->tutorials_list);

    auto *selected_tutorial = new QWidget{};
    auto *vertical_layout = new QVBoxLayout{selected_tutorial};

    auto *tutorial_data_widget = new QWidget{};
    auto *form_layout = new QFormLayout{tutorial_data_widget};
    this->title_edit = new QLineEdit{};
    this->title_edit->setMinimumWidth(500);
    this->presenter_edit = new QLineEdit{};
    this->presenter_edit->setMinimumWidth(500);
    this->likes_edit = new QLineEdit{};
    this->likes_edit->setValidator(new QIntValidator(0, INT_MAX, this));
    this->likes_edit->setMinimumWidth(500);
    this->minutes_edit = new QLineEdit{};
    this->minutes_edit->setMinimumWidth(500);
    this->minutes_edit->setValidator(new QIntValidator(0, INT_MAX, this));
    this->seconds_edit = new QLineEdit{};
    this->seconds_edit->setMinimumWidth(500);
    this->seconds_edit->setValidator(new QIntValidator(0, INT_MAX, this));
    this->link_edit = new QLineEdit{};
    this->link_edit->setMinimumWidth(500);

    auto *title_label = new QLabel{"Title:"};
    title_label->setBuddy(this->title_edit);
    auto *presenter_label = new QLabel{"Presenter: "};
    presenter_label->setBuddy(this->presenter_edit);
    auto *likes_label = new QLabel{"Likes:"};
    likes_label->setBuddy(this->likes_edit);
    auto *minutes_label = new QLabel{"Minutes:"};
    minutes_label->setBuddy(this->minutes_edit);
    auto *seconds_label = new QLabel{"Seconds:"};
    seconds_label->setBuddy(this->seconds_edit);
    auto *link_label = new QLabel{"Link:"};
    link_label->setBuddy(this->link_edit);

    form_layout->addRow(title_label, this->title_edit);
    form_layout->addRow(presenter_label, this->presenter_edit);
    form_layout->addRow(likes_label, this->likes_edit);
    form_layout->addRow(minutes_label, this->minutes_edit);
    form_layout->addRow(seconds_label, this->seconds_edit);
    form_layout->addRow(link_label, this->link_edit);

    vertical_layout->addWidget(tutorial_data_widget);

    auto *tutorial_buttons_widget = new QWidget{};
    auto *tutorial_buttons_layout = new QHBoxLayout{tutorial_buttons_widget};
    this->add_tutorial_button = new QPushButton("ADD");
    this->update_tutorial_button = new QPushButton("UPDATE");
    this->delete_tutorial_button = new QPushButton("DELETE");
    tutorial_buttons_layout->addWidget(this->add_tutorial_button);
    tutorial_buttons_layout->addWidget(this->update_tutorial_button);
    tutorial_buttons_layout->addWidget(this->delete_tutorial_button);

    vertical_layout->addWidget(tutorial_buttons_widget);

    auto *undo_redo_widget = new QWidget{};
    auto *undo_redo_layout = new QHBoxLayout{undo_redo_widget};
    this->undo_button = new QPushButton("UNDO");
    this->redo_button = new QPushButton("REDO");
    this->back_button = new QPushButton("BACK");
    undo_redo_layout->addWidget(undo_button);
    undo_redo_layout->addWidget(redo_button);
    undo_redo_layout->addWidget(this->back_button);

    vertical_layout->addWidget(undo_redo_widget);

    main_layout->addWidget(this->tutorials_list);
    main_layout->addWidget(selected_tutorial);
}

void AdminPage::populate_tutorials_list() {
    if (this->tutorials_list->count() > 0)
        this->tutorials_list->clear();
    for (const auto &tutorial : this->admin_service.get_all_tutorials()) {
        QString new_item = QString::fromStdString(tutorial.get_title());
        auto *item = new QListWidgetItem{new_item};
        this->tutorials_list->addItem(item);
    }
    if (!this->admin_service.get_all_tutorials().empty())
        this->tutorials_list->setCurrentRow(0);
}

void AdminPage::add_tutorial_button_handler() {
    std::string title = this->title_edit->text().toStdString();
    std::string presenter = this->presenter_edit->text().toStdString();
    int likes = this->likes_edit->text().toInt();
    int minutes = this->minutes_edit->text().toInt();
    int seconds = this->seconds_edit->text().toInt();
    std::string link = this->link_edit->text().toStdString();
    try {
        this->admin_service.add_tutorial(title, presenter, minutes, seconds, likes, link);
        auto *message = new QMessageBox;
        message->setWindowTitle("Successful");
        message->setText("Tutorial added successfully!");
        message->setIcon(QMessageBox::Information);
        message->exec();
        this->populate_tutorials_list();
    } catch (std::runtime_error &error) {
        QMessageBox::critical(nullptr, "Error", error.what());
    }
}

void AdminPage::update_tutorial_button_handler() {
    std::string title = this->title_edit->text().toStdString();
    std::string presenter = this->presenter_edit->text().toStdString();
    int likes = this->likes_edit->text().toInt();
    int minutes = this->minutes_edit->text().toInt();
    int seconds = this->seconds_edit->text().toInt();
    std::string link = this->link_edit->text().toStdString();
    try {
        this->admin_service.update_tutorial(title, presenter, minutes, seconds, likes, link);
        QMessageBox::information(nullptr, "Successful", "Tutorial updated successfully!");
        int selected_row = this->get_selected_index();
        this->populate_tutorials_list();
        this->tutorials_list->setCurrentRow(selected_row);
    } catch (std::runtime_error &error) {
        QMessageBox::critical(nullptr, "Error", error.what());
    }
}

void AdminPage::delete_tutorial_button_handler() {
    std::string link = this->link_edit->text().toStdString();
    try {
        this->admin_service.remove_tutorial(link);
        QMessageBox::information(nullptr, "Successful", "Tutorial removed successfully!");
        int selected_row = this->get_selected_index();
        if (selected_row != 0)
            selected_row--;
        this->populate_tutorials_list();
        this->tutorials_list->setCurrentRow(selected_row);
    } catch (std::runtime_error &error) {
        QMessageBox::critical(nullptr, "Error", error.what());
    }
}

void AdminPage::back_button_handler() {
    emit back_to_main_menu_signal();
}

void AdminPage::selected_item_changed() {
    int index = this->get_selected_index();
    if (index == -1)
        return;
    if (index >= this->admin_service.get_all_tutorials().size())
        return;
    Tutorial selected_tutorial = this->admin_service.get_all_tutorials()[index];
    this->title_edit->setText(QString::fromStdString(selected_tutorial.get_title()));
    this->presenter_edit->setText(QString::fromStdString(selected_tutorial.get_presenter()));
    this->likes_edit->setText(QString::number(selected_tutorial.get_likes()));
    this->minutes_edit->setText(QString::number(selected_tutorial.get_length().first));
    this->seconds_edit->setText(QString::number(selected_tutorial.get_length().second));
    this->link_edit->setText(QString::fromStdString(selected_tutorial.get_link()));
}

int AdminPage::get_selected_index() {
    if (this->tutorials_list->count() == 0)
        return -1;
    QModelIndexList index = this->tutorials_list->selectionModel()->selectedIndexes();
    if (index.empty()) {
        this->title_edit->clear();
        this->presenter_edit->clear();
        this->likes_edit->clear();
        this->minutes_edit->clear();
        this->seconds_edit->clear();
        this->link_edit->clear();
        return -1;
    }
    int position = index.at(0).row();
    return position;
}

void AdminPage::back_to_main_menu() {
    auto *widget = new MainPage{this->admin_service, this->user_service};
    widget->show();
    close();
}

void AdminPage::undo_handler() {
    admin_service.undo();
    emit tutorials_updated_signal();
}

void AdminPage::redo_handler() {
    admin_service.redo();
    emit tutorials_updated_signal();
}

AdminPage::~AdminPage() = default;
