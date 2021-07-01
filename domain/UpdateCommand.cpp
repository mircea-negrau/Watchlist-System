//
// Created by Mircea on 5/26/2021.
//

#include "UpdateCommand.h"


UpdateCommand::UpdateCommand(VirtualRepository &repository, const Tutorial &tutorial) : Command{repository, tutorial} {}

void UpdateCommand::execute() {
    repository.update_tutorial(tutorial);
}

void UpdateCommand::undo() {
    repository.update_tutorial(tutorial);
}

void UpdateCommand::redo() {
    repository.update_tutorial(tutorial);
}

std::string UpdateCommand::get_type() {
    return "update";
}