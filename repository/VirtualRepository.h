//
// Created by Mircea on 4/8/2021.
//

#ifndef A67_915_NEGRAU_MIRCEA_VIRTUALREPOSITORY_H
#define A67_915_NEGRAU_MIRCEA_VIRTUALREPOSITORY_H


#include "../domain/Tutorial.h"
#include "../validation/Exceptions.h"
#include <vector>

typedef std::vector<Tutorial> vector;

class VirtualRepository {
public:
    virtual void add_tutorial(const Tutorial &) = 0;

    virtual void update_tutorial(Tutorial &) = 0;

    virtual void remove_tutorial(const Tutorial &) = 0;

    virtual unsigned long long get_size() = 0;

    virtual vector get_all_tutorials() = 0;

    virtual std::string get_file_path() = 0;
};


#endif //A67_915_NEGRAU_MIRCEA_VIRTUALREPOSITORY_H
