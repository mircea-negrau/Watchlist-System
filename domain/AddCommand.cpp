//
// Created by Mircea on 5/26/2021.
//

#include "AddCommand.h"

AddCommand::AddCommand(VirtualRepository &repository, const Tutorial &tutorial) : Command{repository, tutorial} {}

void AddCommand::execute() {
    repository.add_tutorial(tutorial);
}

void AddCommand::undo() {
    repository.remove_tutorial(tutorial);
}

void AddCommand::redo() {
    repository.add_tutorial(tutorial);
}

std::string AddCommand::get_type() {
    return "add";
}
