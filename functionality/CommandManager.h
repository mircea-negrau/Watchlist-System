//
// Created by Mircea on 5/26/2021.
//

#ifndef A10_915_NEGRAU_MIRCEA_1_COMMANDMANAGER_H
#define A10_915_NEGRAU_MIRCEA_1_COMMANDMANAGER_H


#include "../domain/Command.h"

class CommandManager {
private:
    std::vector<Command *> undoHistory;
    std::vector<Command *> redoHistory;
public:
    CommandManager();

    void undo();

    void redo();

    Command *get_undo();

    Command *get_redo();

    void executeCommand(Command *command);
};


#endif //A10_915_NEGRAU_MIRCEA_1_COMMANDMANAGER_H
