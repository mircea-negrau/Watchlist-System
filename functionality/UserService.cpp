//
// Created by Mircea on 3/27/2021.
//

#include "UserService.h"
#include <windows.h>
#include <algorithm>

UserService::UserService(VirtualRepository &repository, VirtualRepository &watchlist, CommandManager &commandManager)
        : repository{repository}, watchlist{watchlist}, commandManager{commandManager} {}

void UserService::add_tutorial(Tutorial &tutorial) {
    auto *command = new AddCommand{watchlist, tutorial};
    commandManager.executeCommand(command);
}

void UserService::remove_tutorial(const string &link) {
    Tutorial tutorial;
    tutorial.set_link(link);
    int index = this->find_tutorial(tutorial);
    bool tutorial_exists = index != -1;
    if (tutorial_exists) {
        tutorial = get_all_watchlist_tutorials()[index];
        auto *command = new RemoveCommand{watchlist, tutorial};
        commandManager.executeCommand(command);
    } else
        throw ServiceError("Tutorial does not exist!");
}

int UserService::find_tutorial(const Tutorial &tutorial) const {
    auto tutorials = this->watchlist.get_all_tutorials();
    auto iterator = std::find(tutorials.begin(), tutorials.end(), tutorial);
    if (iterator != tutorials.end()) {
        int index = std::distance(tutorials.begin(), iterator);
        return index;
    } else
        return -1;
}

vector UserService::get_all_watchlist_tutorials() const {
    return this->watchlist.get_all_tutorials();
}

vector UserService::get_all_tutorials_missing_from_watchlist() const {
    vector tutorials = this->repository.get_all_tutorials();
    vector missing_tutorials;
    std::copy_if(tutorials.begin(), tutorials.end(), std::back_inserter(missing_tutorials),
                 [this](const Tutorial &tutorial) {
                     return this->find_tutorial(tutorial) == -1;
                 });
    return missing_tutorials;
}

vector UserService::get_all_tutorials_missing_from_watchlist_filtered(const string &filter) const {
    vector tutorials = this->repository.get_all_tutorials();
    vector missing_tutorials;
    std::copy_if(tutorials.begin(), tutorials.end(), std::back_inserter(missing_tutorials),
                 [this, filter](const Tutorial &tutorial) {
                     bool tutorial_is_not_added = this->find_tutorial(tutorial) == -1;
                     bool filter_matches = tutorial.get_presenter().find(filter) != std::string::npos;
                     return tutorial_is_not_added && filter_matches;
                 });
    return missing_tutorials;
}

void UserService::undo() {
    commandManager.undo();
}

void UserService::redo() {
    commandManager.redo();
}

void UserService::open_save_file() {
    string path = this->watchlist.get_file_path();
    ShellExecuteA(nullptr, "open", path.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

int UserService::get_size() {
    return (int)this->watchlist.get_size();
}

Command *UserService::get_undo() {
    return commandManager.get_undo();
}

Command *UserService::get_redo() {
    return commandManager.get_redo();
}
