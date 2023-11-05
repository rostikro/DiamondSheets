#include "GoogleDriveApi.h"

#include <QOAuth2AuthorizationCodeFlow>
#include <QDesktopServices>
#include <QOAuthHttpServerReplyHandler>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QBuffer>
#include <QJsonArray>

GoogleDriveApi::GoogleDriveApi()
	: networkAccessManager(new QNetworkAccessManager(this))
{
	if (TryLoadTokens())
		authenticated = true;
}

bool GoogleDriveApi::TryLoadTokens()
{
	QSettings settings("Diamond Studio", "Diamond Sheets", this);

	accessToken = settings.value("accessToken").toString();

	if (accessToken.isEmpty())
		return false;

	return true;
}

//void GoogleDriveApi::CreateFolder(QString name)
//{
//	QJsonObject obj;
//	obj["name"] = name;
//	obj["mimeType"] = "application/vnd.google-apps.folder";
//
//	QJsonDocument doc(obj);
//	QString json(doc.toJson(QJsonDocument::Compact));
//
//	QNetworkRequest request;
//	request.setUrl(QUrl("https://www.googleapis.com/drive/v3/files"));
//	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//	request.setRawHeader("Authorization", accessToken.toUtf8());
//
//	auto reply = networkAccessManager->post(request, json.toUtf8());
//
//	connect(reply, &QNetworkReply::finished, [=]()
//		{
//			qDebug() << "Create folder";
//			qDebug() << reply->readAll();
//		});
//}

QHttpMultiPart* GoogleDriveApi::PrepareMultiPartBody(QString name, QString& buff)
{
	QJsonObject obj;
	obj["name"] = name;
	QString json(QJsonDocument(obj).toJson(QJsonDocument::Compact));

	QHttpMultiPart* multipart = new QHttpMultiPart(QHttpMultiPart::RelatedType);

	QHttpPart metadata;
	metadata.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	metadata.setBody(json.toUtf8());

	QHttpPart file;
	file.setHeader(QNetworkRequest::ContentTypeHeader, "text/csv");
	file.setBody(buff.toUtf8());

	multipart->append(metadata);
	multipart->append(file);

	return multipart;
}

void GoogleDriveApi::UploadFile(QString name, QString& buff)
{
	auto multipart = PrepareMultiPartBody(name, buff);

	QNetworkRequest request;
	request.setUrl(QUrl("https://www.googleapis.com/upload/drive/v3/files?uploadType=multipart"));
	request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

	auto reply = networkAccessManager->post(request, multipart);

	multipart->setParent(reply);

	connect(reply, &QNetworkReply::finished, [=]()
		{
			qDebug() << "Upload file multipart";
			QJsonObject response(QJsonDocument::fromJson(reply->readAll()).object());
			qDebug() << response["id"].toString();
			Q_EMIT SetActiveFileGoogleDriveId(response["id"].toString());
			reply->deleteLater();
		});
}

void GoogleDriveApi::UpdateFile(QString id, QString name, QString& buff)
{
	auto multipart = PrepareMultiPartBody(name, buff);

	QNetworkRequest request;
	request.setUrl(QUrl("https://www.googleapis.com/upload/drive/v3/files/" + id + "?uploadType=multipart"));
	request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

	//auto reply = networkAccessManager->put(request, multipart);
	auto reply = networkAccessManager->sendCustomRequest(request, "PATCH", multipart);

	multipart->setParent(reply);

	connect(reply, &QNetworkReply::finished, [=]()
		{
			qDebug() << "Update file multipart";

			qDebug() << reply->readAll();
			reply->deleteLater();
		});
}

void GoogleDriveApi::OpenFile(QString id)
{
	QNetworkRequest request;
	request.setUrl(QUrl("https://www.googleapis.com/drive/v3/files/" + id));
	request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

	auto reply = networkAccessManager->get(request);

	connect(reply, &QNetworkReply::finished, [=]()
		{
			qDebug() << "Donwload file";
			QJsonObject response(QJsonDocument::fromJson(reply->readAll()).object());

			auto fileName = response["name"].toString();

			Q_EMIT SetActiveFileGoogleDriveId(response["id"].toString());

			// Second request to get file content
			QNetworkRequest requestContent;
			requestContent.setUrl(QUrl("https://www.googleapis.com/drive/v3/files/" + id + "?alt=media"));
			requestContent.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

			auto replyContent = networkAccessManager->get(requestContent);

			connect(replyContent, &QNetworkReply::finished, [=]()
				{
					Q_EMIT FileDownloaded(fileName, replyContent->readAll());
					replyContent->deleteLater();
				});

			reply->deleteLater();
		});
}

void GoogleDriveApi::GetFiles()
{
	QNetworkRequest request;
	request.setUrl(QUrl("https://www.googleapis.com/drive/v3/files"));
	request.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

	auto reply = networkAccessManager->get(request);

	connect(reply, &QNetworkReply::finished, [=]()
		{
			QStringList fileNames, fileIds;

			qDebug() << "Get files";
			QJsonObject response(QJsonDocument::fromJson(reply->readAll()).object());
			for (auto file : response["files"].toArray())
			{
				auto objFile = file.toObject();
				fileNames.push_back(objFile["name"].toString());
				fileIds.push_back(objFile["id"].toString());
			}

			Q_EMIT FilesListReceived(fileNames, fileIds);
		});
}
