#include "tcpgroup.h"

TcpGroup::TcpGroup(QString id, QString name):m_id(id), m_name(name)
{

}

QString TcpGroup::id()
{
	return m_id;
}

QString TcpGroup::name()
{
	return m_name;
}
