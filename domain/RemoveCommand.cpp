//
// Created by Mircea on 5/26/2021.
//

#include "RemoveCommand.h"


RemoveCommand::RemoveCommand(VirtualRepository &repository, const Tutorial &tutorial) : Command{repository, tutorial} {}

void RemoveCommand::execute() {
    repository.remove_tutorial(tutorial);
}

void RemoveCommand::undo() {
    repository.add_tutorial(tutorial);
}

void RemoveCommand::redo() {
    repository.remove_tutorial(tutorial);
}


std::string RemoveCommand::get_type() {
    return "remove";
}