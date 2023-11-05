#include "DiamondSheets.h"

#include "Models/TableModel.h"
#include "FileManager.h"
#include "GoogleApi.h"
#include <QCloseEvent>
#include <QMessageBox>

DiamondSheets::DiamondSheets(QWidget* parent)
    : ui(new Ui::DiamondSheetsClass()), QMainWindow(parent), fileManager(new FileManager(this)), tableModel(new TableModel(this)), google(new GoogleApi())
{
    ui->setupUi(this);
    setCentralWidget(ui->tableView);
    ui->tableView->setModel(tableModel);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &DiamondSheets::ContextMenuRequested);
    connect(fileManager, &FileManager::SetDefaultTableModel, tableModel, &TableModel::SetDefault);
    connect(fileManager, &FileManager::SetTitle, this, &DiamondSheets::setWindowTitle);
    connect(tableModel, &TableModel::EditCompleted, fileManager, &FileManager::SetFileStateEdited);
    connect(fileManager, &FileManager::Serialize, tableModel, &TableModel::Serialize);
    connect(fileManager, &FileManager::Deserialize, tableModel, &TableModel::Deserialize);
    connect(google, &GoogleApi::Authenticated, [=]() { authorizeGoogle->setText("Змінити акаунт"); });

    // Menu bar setup
    newFile = new QAction("Новий", this);
    openFile = new QAction("Відкрити", this);
    saveFile = new QAction("Зберегти", this);
    showAbout = new QAction("Про програму", this);

    newFile->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    openFile->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    saveFile->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

    fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction(newFile);
    fileMenu->addAction(openFile);
    fileMenu->addSeparator();
    fileMenu->addAction(saveFile);

    // Google
    authorizeGoogle = new QAction(google->IsAuthenticated() ? "Змінити акаунт" : "Авторизуватись", this);
    saveFileGoogle = new QAction("Зберегти файл", this);
    openFileGoogle = new QAction("Відкрити файл", this);

    googleMenu = menuBar()->addMenu("Google Диск");
    googleMenu->addAction(openFileGoogle);
    googleMenu->addAction(saveFileGoogle);
    googleMenu->addSeparator();
    googleMenu->addAction(authorizeGoogle);

    connect(openFileGoogle, &QAction::triggered, [=]() { fileManager->OpenFileGoogleDrive(); });
    connect(saveFileGoogle, &QAction::triggered, [=]() { fileManager->SaveFileGoogleDrive(); });
    connect(authorizeGoogle, &QAction::triggered, [=]() { google->Authenticate(); });

    helpMenu = menuBar()->addMenu("Допомога");
    helpMenu->addAction(showAbout);

    connect(newFile, &QAction::triggered, [=]()
        {
            ui->tableView->clearFocus();
            fileManager->NewFile();
        });
    connect(openFile, &QAction::triggered, [=]() { fileManager->OpenFile(); });
    connect(saveFile, &QAction::triggered, [=]() { fileManager->SaveFile(); });
    connect(showAbout, &QAction::triggered, [=]() { ShowInfo(); });

    // Context menu actions setup
    addRowUp = new QAction("Вставити рядок вище", this);
    addRowDown = new QAction("Вставити рядок нижче", this);
    addColumnLeft = new QAction("Вставити стовпчик зліва", this);
    addColumnRight = new QAction("Вставити стовпчик справа", this);
    deleteRow = new QAction("Видалити рядок", this);
    deleteColumn = new QAction("Видалити стовпчик", this);

    // Context menu setup
    ctxMenu = new QMenu(this);
    ctxMenu->addAction(addRowUp);
    ctxMenu->addAction(addRowDown);
    ctxMenu->addSeparator();
    ctxMenu->addAction(addColumnLeft);
    ctxMenu->addAction(addColumnRight);
    ctxMenu->addSeparator();
    ctxMenu->addAction(deleteRow);
    ctxMenu->addAction(deleteColumn);

    connect(addRowUp, &QAction::triggered, [=]() { tableModel->AddRow(ctxMenuCellIndex); });
    connect(addRowDown, &QAction::triggered, [=]() { tableModel->AddRow(ctxMenuCellIndex, 1); });
    connect(addColumnLeft, &QAction::triggered, [=]() { tableModel->AddColumn(ctxMenuCellIndex); });
    connect(addColumnRight, &QAction::triggered, [=]() { tableModel->AddColumn(ctxMenuCellIndex, 1); });
    connect(deleteRow, &QAction::triggered, [=]() { tableModel->DeleteRow(ctxMenuCellIndex); });
    connect(deleteColumn, &QAction::triggered, [=]() { tableModel->DeleteColumn(ctxMenuCellIndex); });

    fileManager->NewFile();
}

DiamondSheets::~DiamondSheets()
{
    delete ui;
}

void DiamondSheets::closeEvent(QCloseEvent *event)
{
    if (fileManager->EnsureFileSaved())
        event->accept();
    else
        event->ignore();
}

void DiamondSheets::ShowInfo()
{
    QMessageBox::about(this, "Про прогаму", "Diamond Sheets\nВерсія 1.0\n©Romanets Corporation. Всі права захищено.");
}

void DiamondSheets::ContextMenuRequested(QPoint pos)
{
    ctxMenuCellIndex = ui->tableView->indexAt(pos);
    ctxMenu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}