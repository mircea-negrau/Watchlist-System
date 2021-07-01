//
// Created by Mircea on 5/26/2021.
//

#include "CommandManager.h"

CommandManager::CommandManager() = default;

void CommandManager::undo() {
    if (!undoHistory.empty()) {
        Command *lastCommand = undoHistory.back();
        lastCommand->undo();
        redoHistory.push_back(lastCommand);
        undoHistory.pop_back();
    }
}

void CommandManager::redo() {
    if (!redoHistory.empty()) {
        Command *lastCommand = redoHistory.back();
        lastCommand->redo();
        undoHistory.push_back(lastCommand);
        redoHistory.pop_back();
    }
}

void CommandManager::executeCommand(Command *command) {
    command->execute();
    redoHistory.clear();
    undoHistory.emplace_back(command);
}

Command *CommandManager::get_undo() {
    if (!undoHistory.empty()) {
        Command *lastCommand = undoHistory.back();
        return lastCommand;
    } else return nullptr;
}

Command *CommandManager::get_redo() {
    if (!redoHistory.empty()) {
        Command *lastCommand = redoHistory.back();
        return lastCommand;
    } else return nullptr;
}
