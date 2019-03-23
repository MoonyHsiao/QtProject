#include "tcpuser.h"

TcpUser::TcpUser(QString name, QString powerpoint):m_name(name), m_powerpoint(powerpoint)
{

}

QString TcpUser::name()
{
	return m_name;
}

QString TcpUser::powerpoint()
{
	return m_powerpoint;
}
