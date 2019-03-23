#include "clientuser.h"

ClientUser::ClientUser(QString username, QString userpwer):m_username(username), m_userpowerpoint(userpwer)
{
}

QString ClientUser::username()
{
	return m_username;
}

QString ClientUser::userpowerpoint()
{
	return m_userpowerpoint;
}

QString ClientUser::msg()
{
	return m_msg;
}
