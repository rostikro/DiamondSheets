#pragma once

#include <QObject>

class QNetworkAccessManager;
class QHttpMultiPart;

class GoogleDriveApi : public QObject
{
	Q_OBJECT

public:
	GoogleDriveApi();

	//void CreateFolder(QString name);
	void UploadFile(QString name, QString& buff);
	void UpdateFile(QString id, QString name, QString& buff);
	void OpenFile(QString id);
	
	void GetFiles();

private:
	bool TryLoadTokens();
	QHttpMultiPart* PrepareMultiPartBody(QString name, QString& buff);

Q_SIGNALS:
	void SetActiveFileGoogleDriveId(QString id);
	void FileDownloaded(QString fileName, QString content);
	void FilesListReceived(QStringList& fileNames, QStringList& fileIds);

private:
	QNetworkAccessManager* networkAccessManager = nullptr;

	bool authenticated = false;
	QString accessToken;
};
