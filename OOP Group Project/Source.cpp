#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#define max_item 20

#include <stdlib.h>
#include <time.h>
#include <math.h> 
#include <Windows.h>
using namespace std;

int autoItemId = 0;
int autoOrderId = 0;
string tmpName, line;
int num_line = 0;
int tmpTimeprep = 0;
int tmpItemId = 0;
float tmpPrice = 0;
int i = 0;
int attempt = 0;
float totalcost = 0;
int totalpreptime = 0;

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
		itemId = ++autoItemId;
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
		orderId = ++autoOrderId;
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
	int quantity[max_item];
	string itemName[max_item];
	Item itemObj[max_item];
public:
	//Set or Mutator Functions
	void setPrice(float price) {
		this->price[i] = price;
		itemObj[i].setPrice(price);
		i++;
	}
	//check this auto item id thing later
	void setItemId() {
		itemObj[i].setItemId();
	}
	void setPrepTime(int prepTime) {
		this->prepTime[i] = prepTime;
		itemObj[i].setPrepTime(prepTime);
	}
	void setQuantity(int quantity) {
		this->quantity[i] = quantity;
		itemObj[i].setQuantity(quantity);
	}
	void setItemName(string itemName) {
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
	int getQuantity(int m) {
		return quantity[m];
	}
	string getItemName(int m) {
		return itemName[m];
	}
	int getItemId(int m) {
		return itemObj[m].getItemId();
	}
	void to_File() {
		ofstream outfile;
		outfile.open("file.txt", ios::out);
		for (int m = 0; m < i; m++) {
			outfile << itemObj[m].getItemId() << endl;
			outfile << itemName[m] << endl;
			outfile << quantity[m] << endl;
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
	string tmpName;
	int tmpTimeprep;
	int tmpQuantity;
	float tmpPrice;
public:
	bool toLogin(string username, string password) {
		if (this->username == username && this->password == password)
			return true;
		else
			attempt++;
		return false;
	}
	//modify this for quantity (below)
	int searchItems(string item) {
		int count=0, flag = -1;
		string tmpitem;
		ifstream infile;
		infile.open("file.txt");
		while (infile >> tmpItemId >> tmpName >> tmpQuantity >> tmpTimeprep >> tmpPrice) {
			if (item == tmpName) {
				cout << "\nItem ID: " << tmpItemId << endl; 
				cout << "Item Name: "<< tmpName << endl;
				cout << "Item Quantity: "<< tmpQuantity << endl;
				cout << "Item Prep-time: "<< tmpTimeprep << endl;
				cout << "Item Price: $"<< tmpPrice << endl;	
				flag = 1;			
				return count;
			}
			else { 
				count++; 				
			}
		}
		if (flag == -1)
			cout << "\nItem was not found." << endl;
		return -1;
	}
};

class Admin : public Users {
private:

public:
	Admin() {
		Users::username = "admin";
		Users::password = "admin";
		//when it starts it is going to store everything from the file respectively
		i = 0;
		ifstream infile;
		infile.open("file.txt");
		while (infile >> tmpItemId >> tmpName >> tmpQuantity >> tmpTimeprep >> tmpPrice) {
			menuObj.setItemId();
			menuObj.setItemName(tmpName);
			menuObj.setQuantity(tmpQuantity);
			menuObj.setPrepTime(tmpTimeprep);
			menuObj.setPrice(tmpPrice);
		}
		infile.close();
	}
	// add everything to the file and stuff
	void addNewItem() {
		cout << "Enter Item Name : ";
		getline(cin, tmpName);
		cout << "\nEnter Item Quantity : ";
		cin >> tmpQuantity;
		cout << "\nEnter Item PrepTime (in minutes): ";
		cin >> tmpTimeprep;
		cout << "\nEnter Item Price: $";
		cin >> tmpPrice;
		cin.ignore();
		menuObj.setItemId();
		menuObj.setItemName(tmpName);
		menuObj.setQuantity(tmpQuantity);
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
		int flag = -1;
		string tmpitem;
		ifstream infile;
		infile.open("file.txt");
		// Don't remember why it works but just don't trouble the increments and stuff
		while (infile >> tmpItemId >>tmpName >> tmpQuantity >> tmpTimeprep >> tmpPrice) {
			m++;
			if (item == tmpName) {
				flag = 1;
				i = m - 1;
				cout << "Item Name: ";
				getline(cin, tmpName);
				cout << "\nQuantity: ";
				cin >> tmpQuantity;
				cout << "\nPrepTime (in minutes): ";
				cin >> tmpTimeprep;
				cout << "\nPrice: ";
				cin >> tmpPrice;
				cin.ignore();
				menuObj.setItemId();
				menuObj.setItemName(tmpName);
				menuObj.setQuantity(tmpQuantity);
				menuObj.setPrepTime(tmpTimeprep);
				menuObj.setPrice(tmpPrice);
				i = tmpI;
				menuObj.to_File();
				ofstream counterfile;
				counterfile.open("counter.txt", ios::out);
				counterfile << i << endl;
				counterfile.close();
				break;
			}
		}
		if (flag == -1)
			cout << "\nItem was not found." << endl;
	}
	void DelNewItem(string item) {
		int m = 0;
		int flag = -1;
		string tmpitem;
		ifstream infile;
		infile.open("file.txt");
		// open a temporary file where we write all the data that is not to be deleted
		ofstream outfile("temp.txt");
		while (infile >> tmpItemId >> tmpName >> tmpQuantity >> tmpTimeprep >> tmpPrice) {
			if (item != tmpName) {
				outfile << tmpItemId << endl;
				outfile << tmpName << endl;
				outfile << tmpQuantity << endl;
				outfile << tmpTimeprep << endl;
				outfile << tmpPrice << endl;
				ofstream counterfile;
				counterfile.open("counter.txt", ios::out);
				counterfile << i << endl;
				counterfile.close();
			}
		}
		if (flag == -1)
			cout << "\nItem not found." << endl;
		else 
			cout << "\n\nItem Deleted.\n";
		infile.close();
		outfile.close();
		// delete the old file and rename the temp file to the old file
		remove("file.txt");
		rename("temp.txt", "file.txt");
	}

};

class Customer : public Users {
private:
	Order orderObj[max_item];
public:
	Customer() {
		Users::username = "cust1";
		Users::password = "qwerty";
		//when it is called it is going to store everything from the file respectively
		i = 0;
		num_line = 0;
		ifstream infile;
		infile.open("file.txt");
		while (infile >> tmpItemId >> tmpName >> tmpQuantity >> tmpTimeprep >> tmpPrice) {
			menuObj.setItemId();
			menuObj.setItemName(tmpName);
			menuObj.setQuantity(tmpQuantity);
			menuObj.setPrepTime(tmpTimeprep);
			menuObj.setPrice(tmpPrice);
		}
		infile.close();
	}
	void setItemQuantity(int quantity) {
		menuObj.setQuantity(quantity);
	}
	void setOrderTotalCost(int m) {
		totalcost += menuObj.getPrice(m);
		orderObj[m].setTotalCost(totalcost);
	}
	void setOrderTotalPrepTime(int m) {
		totalpreptime += menuObj.getPrepTime(m);
		orderObj[m].setTotalPrepTime(totalpreptime);
	}
	void setOrderId(int m) {
		orderObj[m].setOrderId();
	}
	int getItemQuantity(int m) {
		return menuObj.getQuantity(m);
	}
	float getOrderTotalCost(int m) {
		return orderObj[m].getTotalCost();
	}
	int getOrderTotalPrepTime(int m) {
		return orderObj[m].getTotalPrepTime();
	}
	int getOrderId(int m) {
		return orderObj[m].getOrderId();
	}
	void viewMenu() { //Display is working just need to make it look pretty now
		cout << "\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
		for (int m = 0; m < i; m++) {			
			cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 " << "Item Name: " << menuObj.getItemName (m) << endl;
			cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 " << "Preparation Time (minutes): " << menuObj.getPrepTime (m) << endl;
			cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 " << "Price: $" << menuObj.getPrice (m) << endl;
			cout << "\n\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";	
		}
	}
	
}; 

int main() {
	int option;
	int decision;
	int location;
	int quantity;
	int searchOrder;
	int OrderID;
	int totalCost;
	int totalPrepTime;
	string username, password, searchItem;
	char screen[] = "\t\t\t\t\tWelcome to Barbican Beach Bar";
	for (i = 0; i <= strlen(screen); i++) {
		Sleep(50);
		putchar(screen[i]);
		fflush(stdout);
	}
	do {
		int choice = 0;
			system("cls");	
			cout << "\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  MAIN MENU  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
			cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 1.Admin";
			cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 2.Customer";
			cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 3.Exit Program";
			cout << "\n\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
			cout << "\n\nEnter Selection: ";
			cin >> option;	
			while (option < 1 || option > 3){
				cout << "\nInvalid Entry!\nEnter Selection: ";
				cin >> option;
			}
			system("cls");
			cin.ignore();//ignore the newline
			if (option == 1) {
				cout << "Enter Username: ";
				getline(cin, username);
				cout << "Enter Password: ";
				getline(cin, password);
				Admin adminObj;
	
				if (adminObj.toLogin(username, password)) {
					do{
						system("cls");
						cout << "\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  ADMINISTRATOR Panel  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 1.Add New Items to Menu";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 2.Edit menu items";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 3.Delete menu items";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 4.Search for menu items";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 5.SIGN OUT";
						cout << "\n\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";	
						cout << "Enter Selection: ";
						cin >> choice;
						cin.ignore();
						while (choice < 1 || choice > 5){
							cout << "\nInvalid Entry!\nEnter Selection: ";
							cin >> choice;
							cin.ignore();
						}
						system("cls");
						switch (choice) {
							case 1:
								adminObj.addNewItem();
								break;
							case 2:
								cout << "Enter the name of the item you want to edit: ";
								getline(cin, searchItem);
								system("cls");
								adminObj.editNewItem(searchItem);
								system("pause");
								break;
							case 3:
								cout << "Enter the name of the item you want to delete: ";
								getline(cin, searchItem);
								adminObj.DelNewItem(searchItem);								
								system("pause");
								break;
							case 4:
								while (true) {
									cout << "Enter item you would like to search for: ";
									getline(cin, searchItem);
									adminObj.searchItems(searchItem);
									cout << "\nSearch another item?" << endl;
									cout << "1.Yes" << endl;
									cout << "2.No" << endl;
									cout << "Option: ";
									cin >> decision;
									cin.ignore();
									if (decision == 2)
										break;
								}
								system("pause");
							break;	
						}
					} while (choice != 5);						
				} else {
					cout << "\nInvalid Admin Credentials.\n";
					system("pause");
					system("cls");
				}
			}
			else if (option == 2) {
				cout << "Enter Username: ";
				getline(cin, username);
				cout << "Enter Password: ";
				getline(cin, password);
				Customer customerObj;
				if (customerObj.toLogin(username, password)) {
					while (choice != 4) {
						system("cls");
						cout << "\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2  Customer Panel  \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 1.View all items on menu";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 2.Search for items";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 3.View order";
						cout << "\n\n\t\t\t\t\xDB\xDB\xDB\xDB\xB2 4.SIGN OUT";
						cout << "\n\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";	
						cout << "\nEnter Selection: ";						
						cin >> choice;
						cin.ignore();
						while (choice < 1 || choice > 4){
							cout << "\nInvalid Entry!\nEnter Selection: ";
							cin >> choice;
							cin.ignore();
						}
						system("cls");
						switch (choice) {
							case 1:
								int tmpid;
								customerObj.viewMenu();
								do {
									cout << "\n\nEnter the name of the item you would like to purchase (Enter END to complete order): ";
									getline(cin, searchItem);
									if (searchItem == "END") {
										//saves the order to file
										ofstream outfile("order.txt", ios_base::app);
										outfile << customerObj.getOrderId(location) << endl;
										outfile << customerObj.getOrderTotalPrepTime(location) << endl;
										outfile << customerObj.getOrderTotalCost(location) << endl;
										outfile.close();
										cout << "\nYour order number is: " << customerObj.getOrderId(location) << endl;
										break;
									}
									location = customerObj.searchItems(searchItem);
									cout << "\nHow much of that item do you want to purchase: ";
									cin >> quantity;
									if (quantity > customerObj.getItemQuantity(location)) {
										cout << "\nInsufficient quantities available to complete order.\n" << endl;
									}
									else {
										customerObj.setItemQuantity(customerObj.getItemQuantity(location) - quantity);
									}
									cin.ignore();
									if (location != -1) {
										customerObj.setOrderId(location);
										customerObj.setOrderTotalCost(location);
										customerObj.setOrderTotalPrepTime(location);
									}
								} while (searchItem != "END");
								cout << "\n";
								system("pause");
								break;
							case 2:
								while (true) {
									cout << "Enter item you would like to search for: ";
									getline(cin, searchItem);
									customerObj.searchItems(searchItem);
									cout << "\nSearch another item? \n1) yes \n2) no \nOption: ";
									cin >> decision;
									cin.ignore();
									if (decision == 2)
										break;
								}
								break;
							case 3:
								cout << "Enter Order Number or -1 to exit: ";
								cin >> searchOrder;
								if (searchOrder >= 0) {
									ifstream infile;
									infile.open("order.txt");
									while (infile >> OrderID >> totalCost >> totalPrepTime) {
										if (searchOrder == OrderID) {
											cout << "\n\nOrder ID: " <<OrderID << endl;
											cout << "Total Cost: " << totalCost << endl;
											cout << "Preparation Time (minutes): " << totalPrepTime << endl;
											cout << "\n\n";
										}
									}
									infile.close();
								}
								system("pause");
							break;
						}
					}
				} else {
					cout << "\nInvalid Customer Credentials.\n";
					system("pause");
					system("cls");
				}
			}
	} while (option != 3 && attempt < 3);
	system("pause");
	return 0;
}
