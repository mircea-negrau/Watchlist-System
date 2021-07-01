//
// Created by Mircea on 5/28/2021.
//

#include "TutorialsTableModel.h"
#include <QFont>
#include <QBrush>

TutorialsTableModel::TutorialsTableModel(UserService &service, QObject *parent) : QAbstractTableModel{parent},
                                                                                  service{service} {}

int TutorialsTableModel::rowCount(const QModelIndex &parent) const {
    return (int) this->service.get_size();
}

int TutorialsTableModel::columnCount(const QModelIndex &parent) const {
    return 6;
}

QVariant TutorialsTableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();

    std::vector<Tutorial> tutorials = this->service.get_all_watchlist_tutorials();

    if (row == tutorials.size()) {
        return QVariant();
    }

    Tutorial currentTutorial = tutorials[row];

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
            case 0:
                return QString::fromStdString(currentTutorial.get_title());
            case 1:
                return QString::fromStdString(currentTutorial.get_presenter());
            case 2:
                return QString::number(currentTutorial.get_likes());
            case 3:
                return QString::number(currentTutorial.get_length().first);
            case 4:
                return QString::number(currentTutorial.get_length().second);
            case 5:
                return QString::fromStdString(currentTutorial.get_link());
            default:
                break;
        }
    }
    if (role == Qt::FontRole) {
        QFont font("Times", 15, 10, true);
        font.setItalic(false);
        return font;
    }
    if (role == Qt::BackgroundRole) {
        if (row % 2 == 1) {
            return QBrush{QColor{181818}};
        }
    }

    return QVariant{};
}

QVariant TutorialsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0:
                    return QString{"Title"};
                case 1:
                    return QString{"Presenter"};
                case 2:
                    return QString{"Likes"};
                case 3:
                    return QString{"Minutes"};
                case 4:
                    return QString{"Seconds"};
                case 5:
                    return QString{"Link"};
                default:
                    break;
            }
        }
    }
    if (role == Qt::FontRole) {
        QFont font("Times", 15, 10, true);
        font.setBold(true);
        font.setItalic(false);
        return font;
    }

    return QVariant{};
}

void TutorialsTableModel::createNewRow(Tutorial &tutorial) {
    int geneIndex = this->rowCount();
    this->beginInsertRows(QModelIndex{}, geneIndex, geneIndex);
    service.add_tutorial(tutorial);
    this->endInsertRows();
}

void TutorialsTableModel::removeRow(QModelIndex index, std::string &link) {
    int geneIndex = index.row();
    this->beginRemoveRows(QModelIndex{}, geneIndex, geneIndex);
    this->service.remove_tutorial(link);
    this->endRemoveRows();
}

void TutorialsTableModel::undoRemoveRow() {
    int geneIndex = this->rowCount();
    this->beginInsertRows(QModelIndex{}, geneIndex, geneIndex);
    service.undo();
    this->endInsertRows();
}

void TutorialsTableModel::undoAddRow() {
    int geneIndex = this->rowCount() - 1;
    this->beginRemoveRows(QModelIndex{}, geneIndex, geneIndex);
    service.undo();
    this->endRemoveRows();
}

void TutorialsTableModel::redoRemoveRow() {
    int geneIndex = this->rowCount() - 1;
    this->beginRemoveRows(QModelIndex{}, geneIndex, geneIndex);
    service.redo();
    this->endRemoveRows();
}

void TutorialsTableModel::redoAddRow() {
    int geneIndex = this->rowCount();
    this->beginInsertRows(QModelIndex{}, geneIndex, geneIndex);
    this->service.redo();
    this->endInsertRows();
}

Qt::ItemFlags TutorialsTableModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

TutorialsTableModel::~TutorialsTableModel() = default;