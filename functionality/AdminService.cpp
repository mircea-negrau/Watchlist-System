//
// Created by Mircea on 3/27/2021.
//

#include "AdminService.h"

AdminService::AdminService(VirtualRepository &repository, CommandManager &commandManager) : repository{repository},
                                                                                            commandManager{
                                                                                                    commandManager} {}

void AdminService::add_tutorial(const string &title,
                                const string &presenter,
                                int minutes, int seconds,
                                int likes,
                                const string &link) {
    try {
        TutorialValidator::is_valid_tutorial(title, presenter, minutes, seconds, likes, link);
    } catch (ValidationError &error) {
        throw error;
    }
    Tutorial tutorial{title, presenter, minutes, seconds, likes, link};
    bool tutorial_exists = this->find_tutorial(tutorial) != -1;
        if (!tutorial_exists) {
            auto *command = new AddCommand{repository, tutorial};
            commandManager.executeCommand(command);
    } else
        throw ServiceError("Tutorial already exists!");
}

void AdminService::update_tutorial(const string &title,
                                   const string &presenter,
                                   int minutes, int seconds,
                                   int likes,
                                   const string &link) {
    try {
        TutorialValidator::is_valid_tutorial(title, presenter, minutes, seconds, likes, link);
    } catch (ValidationError &error) {
        throw error;
    }
    Tutorial tutorial{title, presenter, minutes, seconds, likes, link};
    bool tutorial_exists = this->find_tutorial(tutorial) != -1;
    if (tutorial_exists) {
        auto *command = new UpdateCommand{repository, tutorial};
        commandManager.executeCommand(command);
    } else
        throw ServiceError("Tutorial does not exist!");
}

void AdminService::remove_tutorial(const string &link) {
    Tutorial tutorial;
    tutorial.set_link(link);
    int index = this->find_tutorial(tutorial);
    bool tutorial_exists = index != -1;
    if (tutorial_exists) {
        auto *command = new RemoveCommand{repository, repository.get_all_tutorials()[index]};
        commandManager.executeCommand(command);
        return;
    }
    throw ServiceError("Tutorial does not exist!");
}

void AdminService::increase_likes(const string &link) {
    Tutorial dummy_tutorial = Tutorial(), tutorial;
    dummy_tutorial.set_link(link);
    int index = this->find_tutorial(dummy_tutorial);
    tutorial = this->repository.get_all_tutorials()[index];
    string title, presenter;
    int minutes, seconds, likes;
    title = tutorial.get_title();
    presenter = tutorial.get_presenter();
    minutes = tutorial.get_length().first;
    seconds = tutorial.get_length().second;
    likes = tutorial.get_likes() + 1;
    this->update_tutorial(title, presenter, minutes, seconds, likes, link);
}

int AdminService::find_tutorial(const Tutorial &tutorial) {
    auto tutorials = this->repository.get_all_tutorials();
    auto iterator = std::find(tutorials.begin(), tutorials.end(), tutorial);
    if (iterator != tutorials.end()) {
        int index = std::distance(tutorials.begin(), iterator);
        return index;
    } else
        return -1;
}

vector AdminService::get_all_tutorials() const {
    return this->repository.get_all_tutorials();
}

void AdminService::undo() {
    commandManager.undo();
}

void AdminService::redo() {
    commandManager.redo();
}
