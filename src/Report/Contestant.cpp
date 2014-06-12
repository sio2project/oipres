#include "Contestant.h"

Contestant::Contestant(int userID, const QString &name, const QString &username) : userID(userID), name(name), username(username)
{
}

void Contestant::setUserID(const int newUserID)
{
	this->userID = newUserID;
}

void Contestant::setName(const QString &newName)
{
	this->name = newName;
}

void Contestant::setUsername(const QString &newUsername)
{
	this->username = newUsername;
}

int Contestant::getUserID() const
{
	return this->userID;
}

QString Contestant::getName() const
{
	return this->name;
}

QString Contestant::getUsername() const
{
	return this->username;
}
