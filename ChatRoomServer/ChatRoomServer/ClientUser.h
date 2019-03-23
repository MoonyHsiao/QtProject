#ifndef CLIENTUSER_H
#define CLIENTUSER_H
#include <QString>

class ClientUser
{
public:
	ClientUser(QString username, QString userpwer);

	QString username();
	QString userpowerpoint();
	QString msg();
private:
    QString m_username;
    QString m_userpowerpoint;
    QString m_msg;
};

#endif // CLIENTUSER_H
