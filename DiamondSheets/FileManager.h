#pragma once

#include <qwidget.h>
#include <qfile.h>
#include <DiamondSheets.h>
#include "qfileinfo.h"

class Cell;
class GoogleDriveApi;
class QListWidget;

class FileManager : public QObject
{
	Q_OBJECT

	enum FileStates
	{
		NONE,
		SAVED,
		EDITED,
	};

	enum FileGoogleDriveStates
	{
		G_NONE,
		G_SAVED,
		G_EDITED,
	};

public:
	FileManager(QWidget* parent);

	void NewFile();
	void OpenFile();
	bool SaveFile();

	void OpenFileGoogleDrive();
	void SaveFileGoogleDrive();

	bool EnsureFileSaved();

public Q_SLOTS:
	void SetFileStateEdited();
	void FileDownloaded(QString fileName, QString content);
	void ShowFilesList(QStringList& fileNames, QStringList& fileIds);

Q_SIGNALS:
	void SetTitle(QString title);
	void SetDefaultTableModel();
	void Serialize(QTextStream& out);
	void Deserialize(QTextStream& in);

private:
	FileStates fileState = NONE;
	FileGoogleDriveStates fileGoogleDriveState = G_NONE;

	QString activeFilePath = "";
	QString activeFileName = "";
	QString activeFileGoogleDriveId = "";

	const QString appName = "Diamond Sheets";

	bool edited = false;

	QWidget* parent;
	GoogleDriveApi* googleDrive;
};

