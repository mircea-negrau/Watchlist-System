//
// Created by Mircea on 5/6/2021.
//

#include <QtWidgets/QApplication>
#include <string>
#include "interface/MainPage.h"

typedef std::string string;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    string method;
    string repo_path = R"(C:\Users\Mircea\CLionProjects\a89-915-Negrau-Mircea\data\repository.txt)";
    string watchlist_path = R"(C:\Users\Mircea\CLionProjects\a89-915-Negrau-Mircea\data\watchlist.txt)";
    string watchlist_save = R"(C:\Users\Mircea\CLionProjects\a89-915-Negrau-Mircea\data\watchlist)";
    FileRepository repository{repo_path};
    FileRepository watchlist{watchlist_path,
                             method,
                             watchlist_save};
    CommandManager adminCommandManager, userCommandManager;
    AdminService admin_service{repository, adminCommandManager};
    UserService user_service{repository, watchlist, userCommandManager};
    MainPage gui{admin_service, user_service};
    gui.show();

    //test
    return QApplication::exec();
}