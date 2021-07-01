//
// Created by Mircea on 3/27/2021.
//

#ifndef A45_915_NEGRAU_MIRCEA_USERSERVICE_H
#define A45_915_NEGRAU_MIRCEA_USERSERVICE_H

#include "../repository/Repository.h"
#include "../repository/FileRepository.h"
#include "CommandManager.h"
#include "../domain/AddCommand.h"
#include "../domain/UpdateCommand.h"
#include "../domain/RemoveCommand.h"

class UserService {
private:
    VirtualRepository &watchlist, &repository;
    CommandManager &commandManager;
public:
/// Constructor
    explicit UserService(VirtualRepository &, VirtualRepository &, CommandManager &);

/// Method to append to the watchlist the given tutorial
    void add_tutorial(Tutorial &);

/// Method to remove from the watchlist the tutorial matching the given link
/// If the tutorial is not found an exception is thrown
    void remove_tutorial(const string &);

/// Method to return the given tutorial's repository index\n
/// Returns -1 if the repository does not contain the tutorial
    int find_tutorial(const Tutorial &) const;

/// Method to return all tutorials from the watchlist
    vector get_all_watchlist_tutorials() const;

/// Method to return all tutorials from the repository not already found in the watchlist
    vector get_all_tutorials_missing_from_watchlist() const;

/// Method to return all tutorials from the repository not already found in the watchlist filtered by presenter
    vector get_all_tutorials_missing_from_watchlist_filtered(const string &) const;

    void undo();

    void redo();

    Command* get_undo();

    Command* get_redo();

    void open_save_file();

    int get_size();
};


#endif //A45_915_NEGRAU_MIRCEA_USERSERVICE_H
