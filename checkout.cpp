// Danny Cristea
// Section 1
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu();
void readBooks(vector<Book *> &myBooks);
int readPersons(vector<Person *> &myCardholders);
void readRentals(vector<Book *> &myBooks, vector<Person *> myCardholders);
void bookCheckout(vector<Book *> &myBooks, vector<Person *> myCardholders);
void bookReturn(vector<Book *> &myBooks);
void availableBooks(vector<Book *> myBooks);
void outstandingRentals(vector<Book *> myBooks);
void cardholderRentals(vector<Book *> myBooks, vector <Person *> myCardholders);
void openCard(vector<Person *> &myCardholders, int &newID);
void closeCard(vector<Person *> &myCardholders);
void updateFiles(vector<Book *> myBooks, vector<Person *> myCardholders);
void handleMemory(vector<Book *> myBooks, vector<Person *> myCardholders);
void readRentalsFile(vector<int> &rentedBooks, vector<int> &cardIDs);
int checkCardholder(vector<Person *> myCardholders, int id);
int checkBookID(vector<Book *> myBooks, int bookID);
int findBookIndex(vector<Book *> myBooks, int bookID);
int findCardholderIndex(vector<Person *> myCardholders, int cardID);

int main()
{
		vector<Book *> books;
		vector<Person *> cardholders;
		int newID = 0;

		readBooks(books);
		newID = readPersons(cardholders);
		readRentals(books, cardholders);

		int choice;
		do
		{
				printMenu();
				cin >> choice;
				cout << endl;
				switch(choice)
				{
						case 1:
								bookCheckout(books, cardholders);
								break;

						case 2:
								bookReturn(books);
								break;

						case 3:
								availableBooks(books);
								break;

						case 4:
								outstandingRentals(books);
								break;

						case 5:
								cardholderRentals(books, cardholders);
								break;

						case 6:
								openCard(cardholders, newID);
								break;

						case 7:
								closeCard(cardholders);
								break;

						case 8:
								updateFiles(books, cardholders);
								handleMemory(books, cardholders);
								break;

						default:
								cout << "Invalid entry" << endl;
								break;
				}
				cout << endl;
	 } while(choice != 8);
			return 0;
}

void printMenu()
{
		cout << "----------Library Book Rental System----------" << endl;
		cout << "1.  Book checkout" << endl;
		cout << "2.  Book return" << endl;
		cout << "3.  View all available books" << endl;
		cout << "4.  View all outstanding rentals" << endl;
		cout << "5.  View outstanding rentals for a cardholder" << endl;
		cout << "6.  Open new library card" << endl;
		cout << "7.  Close library card" << endl;
		cout << "8.  Exit system" << endl;
		cout << "Please enter a choice: ";
}

void readBooks(vector<Book *> &myBooks)
{
	int id;
	string title, author, category, discard;
	ifstream readData;
	Book *bookPtr = nullptr;

	readData.open("books.txt");

	while(readData >> id)
	{
		getline(readData, discard);
		getline(readData, title);
		getline(readData, author);
		getline(readData, category);
		bookPtr = new Book(id, title, author, category);
		myBooks.push_back(bookPtr);
	}
	bookPtr = nullptr;

	readData.close();
}

int readPersons(vector<Person *> &myCardholders)
{
	int cardID;
	bool active;
	string firstName, lastName;
	ifstream readData;
	Person *personPtr = nullptr;

	readData.open("persons.txt");

	while(readData >> cardID)
	{
		readData >> active;
		readData >> firstName;
		readData >> lastName;
		personPtr = new Person(cardID, active, firstName, lastName);
		myCardholders.push_back(personPtr);
	}
	personPtr = nullptr;
	readData.close();

	return (cardID + 1);
}

int checkBookID(vector<Book *> myBooks, int bookID)
{
	int isValid = -1;

	for(int i = 0; i < myBooks.size(); i++)
	{
		if(bookID == myBooks[i]->getId())
		{
			isValid = 0;
			return isValid;
		}
	}
	return isValid;
}

int checkCardholder(vector<Person *> myCardholders, int id)
{
	int isValid = -1, cardHolder = 0, cardID = id;

	for(int i = 0; i < myCardholders.size(); i++)
	{
		if(cardID == myCardholders[i]->getId() && myCardholders[i]->isActive() == 1)
		{
			return cardHolder = i;
		}
	}
	return isValid;
}

void readRentals(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
	vector<int> rentedBooks;
	vector<int> cardIDs;
	Person *personPtr = nullptr;
	int bookID, bookIndex, userID, cardIndex;

	readRentalsFile(rentedBooks, cardIDs);

	for(int i = 0; i < rentedBooks.size(); i++)
	{
		bookID = rentedBooks[i];
		userID = cardIDs[i];
		bookIndex = findBookIndex(myBooks, bookID);
		cardIndex = findCardholderIndex(myCardholders, userID);
		personPtr = myCardholders[cardIndex];
		myBooks[bookIndex]->setPersonPtr(personPtr);
	}
	personPtr = nullptr;
}

void readRentalsFile(vector<int> &rentedBooks, vector<int> &cardIDs)
{
	ifstream readData;
	int bookID, cardID;

	readData.open("rentals.txt");

	while(readData >> bookID)
	{
		readData >> cardID;
		rentedBooks.push_back(bookID);
		cardIDs.push_back(cardID);
	}
	readData.close();
}

int findBookIndex(vector<Book *> myBooks, int bookID)
{
	for(int i = 0; i < myBooks.size(); i++)
	{
		if(bookID == myBooks[i]->getId())
		{
			return i;
		}
	}
}


int findCardholderIndex(vector<Person *> myCardholders, int cardID)
{
	for(int i = 0; i < myCardholders.size(); i++)
	{
		if(cardID == myCardholders[i]->getId())
		{
			return i;
		}
	}
}


void bookCheckout(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
	int cardID, cardIndex, bookID, bookIndex, isValid = 0, cardHolder = 0;
	string name;
	Person *personPtr = nullptr;

	cout << "Please enter the card ID: ";
	cin >> cardID;
	cardHolder = checkCardholder(myCardholders, cardID);
	if(cardHolder != -1)
	{
		cout << "Cardholder: " << myCardholders[cardHolder]->fullName() << endl;
	}
	else
	{
		cout << "Card ID not found\n";
		return;
	}

	cout << "Please enter the book ID: ";
	cin >> bookID;
	isValid = checkBookID(myBooks, bookID);
	if(isValid == -1)
	{
		cout << "Book ID not found\n";
		return;
	}
	else
	{
		for(int i = 0; i < myBooks.size(); i++)
		{
			if(bookID == myBooks[i]->getId() && myBooks[i]->getPersonPtr() != nullptr)
			{
				cout << "Book already checked out\n";
				return;
			}
		}
		for(int j = 0; j < myBooks.size(); j++)
		{
			if(bookID == myBooks[j]->getId())
			{
				cout << "Title: " << myBooks[j]->getTitle() << endl;
				cout << "Rental Completed\n";
				cardIndex = findCardholderIndex(myCardholders, cardID);
				bookIndex = findBookIndex(myBooks, bookID);
				personPtr = myCardholders[cardIndex];
				myBooks[bookIndex]->setPersonPtr(personPtr);
			}
		}
	}
}


void bookReturn(vector<Book *> &myBooks)
{
	int bookID, bookIndex, isValid = 0;
	Person *personPtr = nullptr;

	cout << "Please enter the book ID to return: ";
	cin >> bookID;
	isValid = checkBookID(myBooks, bookID);
	bookIndex = findBookIndex(myBooks, bookID);
	if(isValid == -1 || myBooks[bookIndex]->getPersonPtr() == nullptr)
	{
		cout << "Book ID not found\n";
		return;
	}
	else
	{
		for(int i = 0; i < myBooks.size(); i++)
		{
			if(bookID == myBooks[i]->getId())
			cout << "Title: " << myBooks[i]->getTitle() << endl;
			myBooks[bookIndex]->setPersonPtr(personPtr);
		}
	}
	cout << "Return Completed\n";
}


void availableBooks(vector<Book *> myBooks)
{
	int bookCounter = 0;

	for(int i = 0; i < myBooks.size(); i++)
	{
		if(myBooks[i]->getPersonPtr() == nullptr)
		{
			cout << "Book ID: " << myBooks[i]->getId() << endl;
			cout << "Title: " << myBooks[i]->getTitle() << endl;
			cout << "Author: " << myBooks[i]->getAuthor() << endl;
			cout << "Category: " << myBooks[i]->getCategory() << endl << endl;
			bookCounter++;
		}
	}
	if(bookCounter == 0)
	{
		cout << "No available books\n";
	}
}


void outstandingRentals(vector<Book *> myBooks)
{
	int rentalCounter = 0;

	for(int i = 0; i < myBooks.size(); i++)
	{
		if(myBooks[i]->getPersonPtr() != nullptr)
		{
			cout << "Book ID: " << myBooks[i]->getId() << endl;
			cout << "Title: " << myBooks[i]->getTitle() << endl;
			cout << "Author: " << myBooks[i]->getAuthor() << endl;
			cout << "Cardholder: " << myBooks[i]->getPersonPtr()->fullName() << endl;
			cout << "Card ID: " << myBooks[i]->getPersonPtr()->getId() << endl << endl;
			rentalCounter++;
		}
	}
	if(rentalCounter == 0)
	{
		cout << "No outstanding rentals\n";
	}
}


void cardholderRentals(vector<Book *> myBooks, vector <Person *> myCardholders)
{
	int cardID, cardHolder, cardholderRentalsCntr = 0;

	cout << "Please enter the card ID: ";
	cin >> cardID;
	cardHolder = checkCardholder(myCardholders, cardID);
	if(cardHolder == -1)
	{
		cout << "Card ID not found\n";
		return;
	}
	else
	{
		cout << "Cardholder: " << myCardholders[cardHolder]->fullName() << endl;
		for(int i = 0; i < myBooks.size(); i++)
		{
			if(myBooks[i]->getPersonPtr() != nullptr && cardID == myBooks[i]->getPersonPtr()->getId())
			{
				cout << endl;
				cout << "Book ID: " << myBooks[i]->getId() << endl;
				cout << "Title: " << myBooks[i]->getTitle() << endl;
				cout << "Author: " << myBooks[i]->getAuthor() << endl;
				cardholderRentalsCntr++;
			}
		}
		if(cardholderRentalsCntr == 0)
		{
			cout << "No books currently checked out\n";
		}
	}
}


void openCard(vector<Person *> &myCardholders, int &newID)
{
	string firstName, lastName;
	bool active = 1;
	Person *personPtr = nullptr;

	cout << "Please enter the first name: ";
	cin >> firstName;
	cout << "Please enter the last name: ";
	cin >> lastName;

	for(int i = 0; i < myCardholders.size(); i++)
	{
		if(firstName == myCardholders[i]->getFirstName() && lastName == myCardholders[i]->getLastName())
		{
			myCardholders[i]->setActive(active);
			cout << "Card ID " << myCardholders[i]->getId() << " active\n";
			cout << "Cardholder: " << myCardholders[i]->fullName() << endl;
			return;
		}
	}

		personPtr = new Person(newID, active, firstName, lastName);
		myCardholders.push_back(personPtr);
		cout << "Card ID " << newID << " active\n";
		cout << "Cardholder: " << myCardholders.back()->fullName() << endl;
		personPtr = nullptr;
		newID++;
}


void closeCard(vector<Person *> &myCardholders)
{
	int cardID, cardHolder = 0, cardIndex;
	char confirmation;
	bool active = 0;

	cout << "Please enter the card ID: ";
	cin >> cardID;

	for(int i = 0; i < myCardholders.size(); i++)
	{
		if(cardID != myCardholders[i]->getId())
		{
			cardHolder++;
		}
	}
	cardIndex = findCardholderIndex(myCardholders, cardID);
	if(cardHolder == myCardholders.size())
	{
		cout << "Card ID not found\n";
		return;
	}
	if(active == myCardholders[cardIndex]->isActive())
	{
		cout << "Cardholder: " << myCardholders[cardIndex]->fullName() << endl;
		cout << "Card ID is already inactive\n";
		return;
	}
	else
	{
		cout << "Are you sure you want to deactivate card\n";
		cout << "(y/n)? ";
		cin >> confirmation;

		if(confirmation == 'y')
		{
			myCardholders[cardIndex]->setActive(active);
			cout << "Card ID deactivated\n";
			return;
		}
		else
		{
			return;
		}
	}
}


void updateFiles(vector<Book *> myBooks, vector<Person *> myCardholders)
{
	ofstream writeData;
	int bookID, cardID;
	bool active;
	string firstName, lastName;

	writeData.open("persons.txt");

	for(int i = 0; i < myCardholders.size(); i++)
	{
		cardID = myCardholders[i]->getId();
		active = myCardholders[i]->isActive();
		firstName = myCardholders[i]->getFirstName();
		lastName = myCardholders[i]->getLastName();
		writeData << cardID << " " << active << " " << firstName << " " << lastName << endl;
	}
	writeData.close();

	writeData.open("rentals.txt");

	for(int j = 0; j < myBooks.size(); j++)
	{
		if(myBooks[j]->getPersonPtr() != nullptr)
		{
			bookID = myBooks[j]->getId();
			cardID = myBooks[j]->getPersonPtr()->getId();
			writeData << bookID << " " << cardID << endl;
		 }
	}
	writeData.close();
}


void handleMemory(vector<Book *> myBooks, vector<Person *> myCardholders)
{
	for(int i = 0; i < myBooks.size(); i++)
	{
		delete myBooks[i];
		myBooks[i] = nullptr;
	}

	for(int j = 0; j < myCardholders.size(); j++)
	{
		delete myCardholders[j];
		myCardholders[j] = nullptr;
	}
}