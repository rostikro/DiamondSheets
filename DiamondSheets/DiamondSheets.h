#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DiamondSheets.h"

class FileManager;
class TableModel;
class GoogleApi;
class QCloseEvent;

class DiamondSheets : public QMainWindow
{
    Q_OBJECT

public:
    DiamondSheets(QWidget *parent = nullptr);
    ~DiamondSheets();

private:
    void closeEvent(QCloseEvent *event) override;

private Q_SLOTS:
    void ShowInfo();

    void ContextMenuRequested(QPoint pos);

private:
    Ui::DiamondSheetsClass* ui;
    TableModel* tableModel = nullptr;
    FileManager* fileManager = nullptr;
    GoogleApi* google = nullptr;

    // Menu bar
    QMenu* fileMenu;
    QMenu* googleMenu;
    QMenu* helpMenu;

    QAction* newFile;
    QAction* openFile;
    QAction* saveFile;

    QAction* openFileGoogle;
    QAction* saveFileGoogle;
    QAction* authorizeGoogle;

    QAction* showAbout;

    // Ctx menu
    QModelIndex ctxMenuCellIndex;
    QMenu* ctxMenu;
    
    // Ctx menu actions
    QAction* addRowUp;
    QAction* addRowDown;
    QAction* addColumnLeft;
    QAction* addColumnRight;
    QAction* deleteRow;
    QAction* deleteColumn;
};
