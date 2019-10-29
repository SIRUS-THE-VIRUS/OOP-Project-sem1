#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#define max_item 20
using namespace std;
string tmpName, line;
int num_line = 0;
int tmpTimeprep = 0;
float tmpPrice = 0;
int i = 0;
int attempt=0;

class Item {
private:
	int itemId;
	string name;
	float price;
	int prepTime;
	int quantity;
public:
	Item() {
		itemId = 0;
		name = "NULL";
		price = 0.00;
		prepTime = 0;
		quantity = 0;
	}
	//Set or Mutator Functions
	void setItemId() {
		//Auto increment the ItemID
	}
	void setName(string name) {
		this->name = name;
	}
	void setPrice(float price) {
		this->price = price;
	}
	void setPrepTime(int prepTime) {
		this->prepTime = prepTime;
	}
	void setQuantity(int quantity) {
		this->quantity = quantity;
	}
	//Get or Accessor Functions
	int getItemId() {
		return itemId;
	}
	string getName() {
		return name;
	}
	float getPrice() {
		return price;
	}
	int getPrepTime() {
		return prepTime;
	}
	int getQuantity() {
		return quantity;
	}



};

class Order {
private:
	int orderId;
	float totalCost;
	int totalPrepTime;
	Item itemObj;
public:
	//set or Mutator Functions
	void setOrderId() {
		//auto increment the orderID
	}
	void setTotalCost(float totalCost) {
		this->totalCost = totalCost;
	}
	void setTotalPrepTime(int totalPrepTime) {
		this->totalPrepTime = totalPrepTime;
	}
	//get or Accessor Funtions
	int getOrderId() {
		return orderId;
	}
	float getTotalCost() {
		return totalCost;
	}
	int getTotalPrepTime() {
		return totalPrepTime;
	}
};

class Menu {
private:
	float price[max_item];
	int prepTime[max_item];
	string itemName[max_item];
	Item itemObj[max_item];
public:
	//Set or Mutator Functions
	void setPrice(float price) {
		this->price[i] = price;
		itemObj[i].setPrice(price);
		i++;
	}
	void setPrepTime(int prepTime) {
		this->prepTime[i] = prepTime;
		itemObj[i].setPrepTime(prepTime);
	}
	void setItemName(string itemName) {
		cout << i;
		this->itemName[i] = itemName;
		itemObj[i].setName(itemName);
	}
	//Get or Accessor Functions not done yet
	float getPrice(int m) {
		return price[m];
	}
	int getPrepTime(int m) {
		return prepTime[m];
	}
	string getItemName(int m) {
		return itemName[m];
	}
	//File not working yet
	void to_File() {
		ofstream outfile;
		outfile.open("file.txt", ios::out);
		for (int m = 0; m < i; m++) {
			outfile << itemName[m] << endl;
			outfile << prepTime[m] << endl;
			outfile << price[m] << endl;
		}
		outfile.close();
	}
};

class Users {
protected:
	string username;
	string password;
	Menu menuObj;
public:
	bool toLogin(string username, string password) {
		if (this->username == username && this->password == password)
			return true;
		else
			attempt++;
			return false;
	}
	void searchItems(string item) {
		string tmpitem;
		ifstream infile;
		infile.open("file.txt");
		for (int m = 0; m < i * 3; m++) {
			infile >> tmpitem;
			if (item == tmpitem) {
				cout << tmpitem << "was found" << endl;
			}
		}
	}
};

class Admin : public Users {
private:
	string tmpName;
	int tmpTimeprep;
	float tmpPrice;
public:
	Admin() {
		Users::username = "admin";
		Users::password = "admin";
		//when it starts it is going to store everything from the file respectively
		i = 0;
		ifstream infile;
		infile.open("file.txt");
		while (infile >> tmpName >> tmpTimeprep >> tmpPrice) {
			menuObj.setItemName(tmpName);
			menuObj.setPrepTime(tmpTimeprep);
			menuObj.setPrice(tmpPrice);
		}
		infile.close();
	}
	// add everything to the file and stuff
	void addNewItem() {
		cout << "Enter Item Name : ";
		getline(cin, tmpName);
		cout << "Enter Item PrepTime : ";
		cin >> tmpTimeprep;
		cout << "Enter Item Price : ";
		cin >> tmpPrice;
		cin.ignore();
		menuObj.setItemName(tmpName);
		menuObj.setPrepTime(tmpTimeprep);
		menuObj.setPrice(tmpPrice);
		menuObj.to_File();
		ofstream counterfile;
		counterfile.open("counter.txt", ios::out);
		counterfile << i << endl;
		counterfile.close();
	}
	void editNewItem(string item) {
		int m = 0;
		int tmpI = i;
		cout << tmpI;
		string tmpitem;
		ifstream infile;
		infile.open("file.txt");
		// Don't remember why it works but just don't trouble the increments and stuff
		while (infile >> tmpName >> tmpTimeprep >> tmpPrice) {
			m++;
			if (item == tmpName) {
				i = m - 1;
				cout << "Enter Item Name : ";
				getline(cin, tmpName);
				cout << "Enter Item PrepTime : ";
				cin >> tmpTimeprep;
				cout << "Enter Item Price : ";
				cin >> tmpPrice;
				cin.ignore();
				cout << tmpI;
				menuObj.setItemName(tmpName);
				menuObj.setPrepTime(tmpTimeprep);
				menuObj.setPrice(tmpPrice);
				i = tmpI;
				cout << i;
				menuObj.to_File();
				ofstream counterfile;
				counterfile.open("counter.txt", ios::out);
				counterfile << i << endl;
				counterfile.close();
				cout << i;
				break;
			}
		}

	}
	void DelNewItem(string item) {
		int m = 0;
		string tmpitem;
		ifstream infile;
		infile.open("file.txt");
		// open a temporary file where we write all the data that is not to be deleted
		ofstream outfile("temp.txt");
		while (infile >> tmpName >> tmpTimeprep >> tmpPrice) {
			if (item != tmpName) {
				outfile << tmpName << endl;
				outfile << tmpTimeprep << endl;
				outfile << tmpPrice << endl;
				ofstream counterfile;
				counterfile.open("counter.txt", ios::out);
				counterfile << i << endl;
				counterfile.close();
			}
		}
		infile.close();
		outfile.close();
		// delete the old file and rename the temp file to the old file
		remove("file.txt");
		rename("temp.txt", "file.txt");
	}

};

class Customer : public Users {
private:

public:
	Customer() {
		Users::username = "cust1";
		Users::password = "qwerty";
		//when it is called it is going to store everything from the file respectively
		i = 0;
		num_line = 0;
		ifstream infile;
		infile.open("file.txt");
		cout << i;
		while (infile >> tmpName >> tmpTimeprep >> tmpPrice) {
			menuObj.setItemName(tmpName);
			menuObj.setPrepTime(tmpTimeprep);
			menuObj.setPrice(tmpPrice);
		}
		infile.close();
	}
	void viewMenu() { //Display is working just need to make it look pretty now
		cout << "*********Menu*********" << endl;
		cout << "**********************" << endl;
		for (int m = 0; m < i; m++) {
			cout << menuObj.getItemName(m) << endl;
			cout << menuObj.getPrepTime(m) << endl;
			cout << menuObj.getPrice(m) << endl;
			cout << "*************************" << endl;
		}
	}


};

int main() {
	int option;
	int decision;
	string username, password, searchItem;
	do {
		int choice = 0;
		cout << "who are you 1)admin 2) customer 3) EXIT" << endl;
		cin >> option;
		cin.ignore();//ignore the newline
		if (option == 1) {
			cout << "Enter Username: " << endl;
			getline(cin, username);
			cout << "Enter Password: " << endl;
			getline(cin, password);
			Admin adminObj;

			if (adminObj.toLogin(username, password)) {
				while (choice != 5) {
					system("cls");
					cout << "ADMINISTRATOR Panel" << endl;
					cout << "1) Add new items to menu" << endl;
					cout << "2) Edit menu items" << endl;
					cout << "3) Delete menu items" << endl;
					cout << "4) Search for menu items" << endl;
					cout << "5) SIGN OUT" << endl;
					cin >> choice;
					cin.ignore();
					switch (choice) {
					case 1:
						adminObj.addNewItem();
						break;
					case 2:
						cout << "Enter the name of the item you want to edit:" << endl;
						getline(cin, searchItem);
						adminObj.editNewItem(searchItem);
						break;
					case 3:
						cout << "Enter the name of the item you want to delete:" << endl;
						getline(cin, searchItem);
						adminObj.DelNewItem(searchItem);
						break;
					case 4:
						while (true) {
							cout << "Enter item you would like to search for: " << endl;
							getline(cin, searchItem);
							adminObj.searchItems(searchItem);
							cout << "Search another item? 1) yes 2) no" << endl;
							cin >> decision;
							cin.ignore();
							if (decision == 2)
								break;
						}
						break;
					case 5:
						break;
					default:
						cout << "Invalid option selected";
					}
				}
			}
		}
		else if (option == 2) {
			cout << "Enter Username: " << endl;
			getline(cin, username);
			cout << "Enter Password: " << endl;
			getline(cin, password);
			Customer customerObj;
			if (customerObj.toLogin(username, password)) {
				while (choice != 4) {
					system("cls");
					cout << "Customer Panel" << endl;
					cout << "1) View all items on menu" << endl;
					cout << "2) Search for items" << endl;
					cout << "3) View order" << endl;
					cout << "4) SIGN OUT" << endl;
					cin >> choice;
					cin.ignore();
					switch (choice) {
					case 1:
						customerObj.viewMenu();
						break;
					case 2:
						while (true) {
							cout << "Enter item you would like to search for: " << endl;
							getline(cin, searchItem);
							customerObj.searchItems(searchItem);
							cout << "Search another item? 1) yes 2) no" << endl;
							cin >> decision;
							cin.ignore();
							if (decision == 2)
								break;
						}
						break;
					case 3:
						break;
					case 4:
						break;
					default:
						cout << "Invalid option selected";
					}
				}
			}
		}
	} while (option != 3 && attempt <3);
	system("pause");
	return 0;
}