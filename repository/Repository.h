//
// Created by Mircea on 3/27/2021.
//

#ifndef A45_915_NEGRAU_MIRCEA_REPOSITORY_H
#define A45_915_NEGRAU_MIRCEA_REPOSITORY_H

#include "VirtualRepository.h"

class Repository : public VirtualRepository {
private:
    vector data;
public:

/// Constructor
    Repository();

/// Method to add a tutorial to the repository
    void add_tutorial(const Tutorial &) override;

/// Method to update the given tutorial in the repository
    void update_tutorial(Tutorial &) override;

/// Method to remove a tutorial from the repository
/// If the tutorial is not found, nothing happens
    void remove_tutorial(const Tutorial &) override;

/// Method to return all the tutorials from the repository
    vector get_all_tutorials() override;

    std::string get_file_path() override;

    unsigned long long get_size() override;
};


#endif //A45_915_NEGRAU_MIRCEA_REPOSITORY_H
