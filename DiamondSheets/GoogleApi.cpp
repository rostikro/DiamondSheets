#include "GoogleApi.h"

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

void GoogleApi::Authenticate()
{
	google->grant();
}

GoogleApi::GoogleApi()
	: google(new QOAuth2AuthorizationCodeFlow(this))
{
	google->setScope("https://www.googleapis.com/auth/drive.file");

	connect(google, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);

	google->setAuthorizationUrl(QUrl("https://accounts.google.com/o/oauth2/auth"));
	google->setAccessTokenUrl(QUrl("https://oauth2.googleapis.com/token"));
	google->setClientIdentifier(clientId);
	google->setClientIdentifierSharedKey(secret);

	google->setReplyHandler(new QOAuthHttpServerReplyHandler(8080, this));

	connect(google, &QOAuth2AuthorizationCodeFlow::granted, [=]()
		{
			qDebug() << google->token();
			accessToken = google->token();
			refreshToken = google->refreshToken();
			SaveTokens();
			Q_EMIT Authenticated();
		});

	if (TryLoadTokens())
		authenticated = true;
}

void GoogleApi::SaveTokens()
{
	QSettings settings("Diamond Studio", "Diamond Sheets", this);

	settings.setValue("accessToken", accessToken);
	settings.setValue("refreshToken", refreshToken);
}

bool GoogleApi::TryLoadTokens()
{
	QSettings settings("Diamond Studio", "Diamond Sheets", this);

	accessToken = settings.value("accessToken").toString();
	refreshToken = settings.value("refreshToken").toString();
	qDebug() << accessToken;
	google->setToken(accessToken);
	google->setRefreshToken(refreshToken);

	if (accessToken.isEmpty() || refreshToken.isEmpty())
		return false;

	return true;
}