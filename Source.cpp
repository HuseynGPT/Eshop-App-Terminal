#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
typedef string str;
#include"exceptions.h"
#include "Ecommerce.h"
using namespace Ecommerce;
using namespace Database;
#include "Functions.h"
#include <vector>

//########################################
int row = 0, column = 0;
int r = 0, c = 0;
int a = 0, b = 0;
int sutun = 0, setr = 0;
//########################################

char** reg_or_sign = new char* [3]
{
	new char[] {" Sign Up"},
		new char[] {" Register"},
		new char[] {" exit"},

};
char** admin_menu = new char* [4]
{
	new char[] {" Show all Products"},
		new char[] {" Add Product"},
		new char[] {" Delete Products"},
		new char[] {" Sign Out"}
};
char** user_menu = new char* [3]
{
	new char[] {" Buy product"},
		new char[] {" Show My info"},
		new char[] {" Sign Out"}
};

int main()
{
	int input;
	int registration_input;
	int items_count = 0;
	vector<Guest*> users;

	//getDataFromFile(persons, items_count, "users.txt");
	int user_menu_input;
	int inpt;
	int item_count = 0;
	Telephone** items = new Telephone * [item_count] {};
	DbSet db(items, item_count);
	while (true)
	{
	main_menu:
		system("cls");
		reg_or_sign[a][b] = '~';
		print_menu(reg_or_sign, a, 3);
		registration_input = _getch();
		MyMenu(reg_or_sign, 3, a, b, registration_input);
		if (a == 0 && registration_input == 13)
		{
			system("cls");
			str username;
			str password;

			if (SignUp(username, password))
			{
				if (username == "admin" && password == "admin123")
				{
					while (true)
					{
						system("cls");
						admin_menu[r][c] = '~';
						print_menu(admin_menu, r, 4);
						inpt = _getch();
						MyMenu(admin_menu, 4, r, c, inpt);

						if (r == 0 && inpt == 13)
						{
							system("cls");
							db.ShowAll();
							system("pause");

						}
						if (r == 1 && inpt == 13)
						{
							system("cls");
							str marka, model, color;
							float price;
							int memory, storage, quantity;
							cout << "Enter marka ---> "; cin >> marka;
							cout << "Enter model ---> "; cin >> model;
							cout << "Enter color ---> "; cin >> color;
							cout << "Enter price ---> "; cin >> price;
							cout << "Enter memory ---> "; cin >> memory;
							cout << "Enter storage ---> "; cin >> storage;
							cout << "Enter quantity ---> "; cin >> quantity;

							Telephone* new_t = new Telephone(marka, model, color, memory, price, storage, quantity);
							db.add(new_t);
						}

						if (r == 2 && inpt == 13)
						{
							system("cls");
							int id;
							cout << "Enter id --> "; cin >> id;
							db.deleteByid(id);
							system("pause");
						}
						if (r == 3 && inpt == 13)
						{
							goto main_menu;
						}

					}

				}
				else
				{
						system("cls");
					float balance;
					cout << "Enter your balance: "; cin >> balance;
					while (true)
					{
						system("cls");
						user_menu[sutun][setr] = '~';
						print_menu(user_menu, sutun, 3);
						user_menu_input = _getch();
						MyMenu(user_menu, 3, sutun, setr, user_menu_input);
						Guest* new_g = new Guest();
							

						if (sutun == 0 && user_menu_input == 13)
						{
							system("cls");
							int users_products_id;
							db.ShowSmall();
							cout << endl;
							cout << "Enter product id -- > "; cin >> users_products_id;
							Telephone* user_product = db.getItem(users_products_id);
							if (balance>= user_product->GetPrice())
							{
								balance = balance - user_product->GetPrice();

								user_product->WhenUserBuy();
								cout << "Thank for buying\n";
							}
							else
							{

								cout << "balansiniz azdir\n";
							}
							cout << "balansiniz--> " << balance << endl;
							system("pause");
						}
						else if (sutun == 1 && user_menu_input == 13)
						{
							system("cls");
							Guest* guest = new Guest();
							for (auto items : users)
							{
								if (items->getUsername().compare(username) == 0 && items->getPassword().compare(password))
								{
									guest = items;
									break;

								}
							}

							guest->ShowMyInfo();
							system("pause");
						}
						if (sutun == 2 && user_menu_input == 13)
							goto main_menu;
					}
				}
			}
			else
			{
				system("cls");
				try
				{
					throw new exception("Username or password wrong");
				}
				catch (exception* ex)
				{
					SetConsoleTextAttribute(console, 4);
					cout << ex->what() << endl;
				}
				SetConsoleTextAttribute(console, 7);
				system("pause");
			}

		}
		else if (a == 1 && registration_input == 13)
		{
			system("cls");
			Register();
			system("pause");
		}
		else if (a == 2 && registration_input == 13)
		{
			system("cls");
			break;
		}
	}
}

