#pragma once

#include <qobject.h>

class QOAuth2AuthorizationCodeFlow;
class QNetworkAccessManager;

class GoogleApi : public QObject
{
	Q_OBJECT

public:
	GoogleApi();

	bool IsAuthenticated() { return authenticated; }

private:
	void SaveTokens();
	bool TryLoadTokens();

public Q_SLOT:
	void Authenticate();

Q_SIGNALS:
	void Authenticated();

private:
	QOAuth2AuthorizationCodeFlow* google = nullptr;
	const QString clientId = "256493343603-hhps7fei3084d3bjscgb3iejmto4f0br.apps.googleusercontent.com";
	const QString secret = "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";

	bool authenticated = false;
	QString accessToken;
	QString refreshToken;
};

