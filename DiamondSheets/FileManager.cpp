#include "FileManager.h"
#include <qstring.h>
#include <QFileDialog>
#include <qmessagebox.h>
#include "Models/TableModel.h"
#include <QInputDialog>
#include "GoogleDriveApi.h"
#include <QListWidget>

#include "Cell.h"
#include <QListWidget>

FileManager::FileManager(QWidget* parent)
	: googleDrive(new GoogleDriveApi())
{
	this->parent = parent;

	connect(googleDrive, &GoogleDriveApi::SetActiveFileGoogleDriveId, [=](QString id) { activeFileGoogleDriveId = id; qDebug() << id; });
	connect(googleDrive, &GoogleDriveApi::FileDownloaded, this, &FileManager::FileDownloaded);

	connect(googleDrive, &GoogleDriveApi::FilesListReceived, this, &FileManager::ShowFilesList);
}

void FileManager::NewFile()
{
	if (!EnsureFileSaved())
		return;

	edited = false;
	fileState = NONE;
	fileGoogleDriveState = G_NONE;

	activeFileGoogleDriveId = "";
	activeFilePath = "";
	activeFileName = "";

	Q_EMIT SetDefaultTableModel();
	Q_EMIT SetTitle("Untitled - " + appName);
}

void FileManager::OpenFile()
{
	if (!EnsureFileSaved())
		return;

	QString filePath = QFileDialog::getOpenFileName(parent, "Open file", "/", "Spreadsheet files (*.csv)");

	if (filePath.isEmpty())
		return;

	activeFilePath = filePath;


	QFile file(activeFilePath);
	QFileInfo fileInfo(file);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(parent, "Помилка відкриття файлу", file.errorString());
		return;
	}

	QTextStream in(&file);
	Q_EMIT Deserialize(in);
	file.close();

	edited = false;
	fileState = SAVED;
	fileGoogleDriveState = G_NONE;

	activeFileName = fileInfo.baseName();
	activeFileGoogleDriveId = "";

	Q_EMIT SetTitle(activeFileName + " - " + appName);
}

bool FileManager::SaveFile()
{
	if (fileState == SAVED)
		return true;

	if (activeFilePath.isEmpty())
	{
		QString fileName = QFileDialog::getSaveFileName(parent, "Save file", "/", "Spreadsheet files (*.csv)");

		if (fileName.isEmpty())
			return false;

		activeFilePath = fileName;
	}

	QFile file(activeFilePath);
	QFileInfo fileInfo(file);

	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::information(parent, "Помилка при збереженні файлу", file.errorString());
		return false;
	}

	QTextStream out(&file);
	Q_EMIT Serialize(out);
	file.close();

	edited = false;
	fileState = SAVED;

	activeFileName = fileInfo.baseName();

	Q_EMIT SetTitle(activeFileName + " - " + appName);

	return true;
}

void FileManager::SaveFileGoogleDrive()
{
	if (fileGoogleDriveState == G_SAVED)
		return;

	if (activeFileName.isEmpty())
	{
		QString fileName = QInputDialog::getText(parent, "Diamond Sheets", "Введіть назву файла");
		if (fileName.isEmpty())
			return;

		activeFileName = fileName;
	}

	QString buff;
	QTextStream out(&buff);
	Q_EMIT Serialize(out);

	if (activeFileGoogleDriveId.isEmpty())
		googleDrive->UploadFile(activeFileName, buff);
	else
		googleDrive->UpdateFile(activeFileGoogleDriveId, activeFileName, buff);

	edited = false;
	fileGoogleDriveState = G_SAVED;

	Q_EMIT SetTitle(activeFileName + " - " + appName);
}

void FileManager::OpenFileGoogleDrive()
{
	googleDrive->GetFiles();
}

void FileManager::ShowFilesList(QStringList& fileNames, QStringList& fileIds)
{
	QListWidget* listWidget = new QListWidget();
	listWidget->addItems(fileNames);
	connect(listWidget, &QListWidget::doubleClicked, [=](const QModelIndex& index)
		{
			googleDrive->OpenFile(fileIds[index.row()]);

			listWidget->close();
		});

	listWidget->show();
}

void FileManager::FileDownloaded(QString fileName, QString content)
{
	QTextStream in(&content);
	Q_EMIT Deserialize(in);

	edited = false;
	fileState = NONE;
	fileGoogleDriveState = G_SAVED;

	activeFileName = fileName;

	Q_EMIT SetTitle(activeFileName + " - " + appName);
}

void FileManager::SetFileStateEdited()
{
	qDebug() << "EDITED";
	if (edited)
		return;

	fileState = EDITED;
	if (fileGoogleDriveState != G_NONE)
		fileGoogleDriveState = G_EDITED;

	edited = true;

	Q_EMIT SetTitle("*" + (activeFileName.isEmpty() ? "Untitled" : activeFileName) + " - " + appName);
}

bool FileManager::EnsureFileSaved()
{
	if (fileState == SAVED || fileState == NONE)
		return true;

	QMessageBox saveQuestion(parent);
	saveQuestion.setWindowTitle("Diamond Sheets");
	saveQuestion.setText("Чи ви хочете зберегти файл?");
	saveQuestion.addButton("Так", QMessageBox::YesRole);
	saveQuestion.addButton("Ні", QMessageBox::NoRole);
	saveQuestion.addButton("Відмінити", QMessageBox::RejectRole);
	int response = saveQuestion.exec();

	if (response == 2) // Reject
		return false;
	if (response == 0) // Save
		return SaveFile();

	return true; // Not to save
}
