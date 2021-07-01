//
// Created by Mircea on 5/26/2021.
//

#ifndef A10_915_NEGRAU_MIRCEA_1_ADDCOMMAND_H
#define A10_915_NEGRAU_MIRCEA_1_ADDCOMMAND_H


#include "Command.h"

class AddCommand : public Command {
public:
    AddCommand(VirtualRepository &repository, const Tutorial &tutorial);

    void execute() override;

    void undo() override;

    void redo() override;

    std::string get_type() override;
};


#endif //A10_915_NEGRAU_MIRCEA_1_ADDCOMMAND_H
