//
// Created by Mircea on 5/26/2021.
//

#ifndef A10_915_NEGRAU_MIRCEA_1_COMMAND_H
#define A10_915_NEGRAU_MIRCEA_1_COMMAND_H

#include "Tutorial.h"
#include "../repository/VirtualRepository.h"

class Command {
protected:
    Tutorial tutorial;
    VirtualRepository &repository;
public:
    Command(VirtualRepository &repository, const Tutorial &tutorial) : repository{repository}, tutorial{tutorial} {}

    virtual void execute() = 0;

    virtual void undo() = 0;

    virtual void redo() = 0;

    virtual std::string get_type() = 0;
};


#endif //A10_915_NEGRAU_MIRCEA_1_COMMAND_H
