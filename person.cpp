#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName)
{
		firstName = fName;
		lastName = lName;
		setActive(act);
		cardID = cardNo;
}

string Person::getFirstName()
{
		return firstName;
}

string Person::getLastName()
{
		return lastName;
}

int Person::getId()
{
		return cardID;
}

void Person::setActive(bool act)
{
	active = act;
}

bool Person::isActive()
{
	if(active == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

string Person::fullName()
{
		return firstName + " " + lastName;
}