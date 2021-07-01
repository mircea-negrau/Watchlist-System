//
// Created by Mircea on 3/27/2021.
//

#ifndef A45_915_NEGRAU_MIRCEA_ADMINSERVICE_H
#define A45_915_NEGRAU_MIRCEA_ADMINSERVICE_H

#include "../repository/Repository.h"
#include "../repository/FileRepository.h"
#include "../validation/TutorialValidator.h"
#include "../domain/AddCommand.h"
#include "../domain/UpdateCommand.h"
#include "../domain/RemoveCommand.h"
#include "CommandManager.h"
#include <algorithm>

class AdminService {
private:
    VirtualRepository &repository;
    CommandManager &commandManager;
public:
/// Constructor
    explicit AdminService(VirtualRepository &, CommandManager &);

/// Method to add a tutorial to the repository\n
/// param(title): title of tutorial\n
/// param(presenter): presenter of tutorial\n
/// param(minutes): minutes of the tutorial's length\n
/// param(seconds): seconds of the tutorial's length\n
/// param(likes): tutorial's amount of likes\n
/// param(link): link to tutorial\n
/// throws an error if the tutorial is already found in the repository
    void add_tutorial(const string &, const string &, int, int, int, const string &);


/// Method to update an existing tutorial from the repository\n
/// param(title): new title of tutorial\n
/// param(presenter): new presenter of tutorial\n
/// param(minutes): new minutes of the tutorial's length\n
/// param(seconds): new seconds of the tutorial's length\n
/// param(likes): tutorial's new amount of likes\n
/// param(link): link to tutorial\n
/// throws an error if the tutorial is not found in the repository
    void update_tutorial(const string &, const string &, int, int, int, const string &);


/// Method to return the given tutorial's repository index\n
/// Returns -1 if the repository does not contain the tutorial
    int find_tutorial(const Tutorial &);


/// Method to remove an existing tutorial from the repository\n
/// param(title): title of tutorial\n
/// param(presenter): presenter of tutorial\n
/// param(minutes): minutes of the tutorial's length\n
/// param(seconds): seconds of the tutorial's length\n
/// param(likes): tutorial's amount of likes\n
/// param(link): link to tutorial\n
/// throws an error if the tutorial is not found in the repository\n
    void remove_tutorial(const string &);


/// Method to increase by 1 the amount of likes the tutorial identified by the given link\n
/// param(link): link of the tutorial
    void increase_likes(const string &);


/// Method to return all tutorials from repository
    vector get_all_tutorials() const;

    void undo();
    void redo();
};


#endif //A45_915_NEGRAU_MIRCEA_ADMINSERVICE_H
