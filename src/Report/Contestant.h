#pragma once
#include "../main.h"

class Contestant
{
public:
	Contestant(int userID = 0, const QString &name = "", const QString &username = "");

	void setUserID(const int newUserID);
	void setName(const QString &newName);
	void setUsername(const QString &newUsername);

	int getUserID() const;
	QString getName() const;
	QString getUsername() const;

private:
	int userID;
	QString name;
	QString username;
};
