//
// Created by Mircea on 5/28/2021.
//

#ifndef A10_915_NEGRAU_MIRCEA_1_TUTORIALSTABLEMODEL_H
#define A10_915_NEGRAU_MIRCEA_1_TUTORIALSTABLEMODEL_H

#include <QAbstractTableModel>
#include "../functionality/UserService.h"

class TutorialsTableModel : public QAbstractTableModel {
private:
    UserService &service;
public:
    explicit TutorialsTableModel(UserService &service, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex{}) const override;

    int columnCount(const QModelIndex &parent = QModelIndex{}) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void createNewRow(Tutorial &tutorial);

    void undoRemoveRow();

    void undoAddRow();

    void redoAddRow();

    void redoRemoveRow();

    void removeRow(QModelIndex index, std::string &link);

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    ~TutorialsTableModel();
};

#endif //A10_915_NEGRAU_MIRCEA_1_TUTORIALSTABLEMODEL_H
