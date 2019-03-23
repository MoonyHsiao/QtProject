#ifndef TCPUSER_H
#define TCPUSER_H
#include <QString>

class TcpUser
{
public:
    TcpUser(QString name, QString powerpoint);
	QString name();
	QString powerpoint();
private:
    QString m_name;
    QString m_powerpoint;
};

#endif // TCPUSER_H
