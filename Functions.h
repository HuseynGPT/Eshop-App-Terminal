#pragma once
//################################################################################
// User class functions
void Database::User::setUsername(str username)
{
	if (username.size() >= 3)
	{
		this->_username = username; return;
	}
	else
	{

		throw new InvalidArgument("Username min. 6 character", __LINE__, __FILE__, __TIME__);


	}
}

void Database::User::setPassword(str password)
{
	if (password.size() >= 3)
	{
		_password = password;
		return;
	}
	else
	{

		throw new InvalidArgument("password min. 6 character", __LINE__, __FILE__, __TIME__);

	}
}

inline str Database::User::getUsername()const { return this->_username; }

inline str Database::User::getPassword()const { return this->_password; }


//################################################################################
// ---------------------------------------------------------------------------------
//################################################################################
//Database functions
inline str Database::Guest::GetConnectedDate()const { return this->_connected_date; }

//#################################################################################
// ---------------------------------------------------------------------------------
//################################################################################
// Telephone class methods

void Database::Telephone::SetMarka(str marka)
{
	if (marka.size() >= 3)
	{
		this->_marka = marka; return;
	}
	else
	{

		throw new InvalidArgument("Marka min. 3 character", __LINE__, __FILE__, __TIME__);



	}
}

void  Database::Telephone::SetModel(str model)
{
	if (model.size() >= 3)
	{
		this->_model = model; return;
	}
	else
	{

		throw new InvalidArgument("model min. 3 character", __LINE__, __FILE__, __TIME__);



	}
}

void Database::Telephone::SetColor(str color)
{
	if (color.size() >= 3)
	{
		this->_color = color; return;
	}
	else
	{

		throw new InvalidArgument("color min. 3 character", __LINE__, __FILE__, __TIME__);

	}
}

void Database::Telephone::SetMemory(int memory)
{
	if (memory >= 2 && memory <= 16)
	{
		this->_memory = memory; return;

	}
	else
	{

		throw new InvalidArgument("memory size min. 2,  max. 16 ", __LINE__, __FILE__, __TIME__);

	}
}

void Database::Telephone::SetStorage(int storage)
{
	if (storage >= 16 && storage <= 256)
	{
		this->_storage = storage; return;

	}
	else
	{

		throw new InvalidArgument("storage size min. 16,  max. 256 ", __LINE__, __FILE__, __TIME__);


	}

}

void Database::Telephone::SetQuantity(int quantity)
{
	if (quantity >= 1)
	{
		this->_quantity = quantity; return;

	}
	else
	{

		throw new InvalidArgument("quantity size min. 1 ", __LINE__, __FILE__, __TIME__);


	}

}

inline str Database::Telephone::GetMarka()const { return this->_marka; }

inline str Database::Telephone::GetModel()const { return this->_model; }

inline str Database::Telephone::GetColor()const { return this->_color; }

inline int Database::Telephone::GetMemory()const { return this->_memory; }

inline int Database::Telephone::GetStorage()const { return this->_storage; }


//#################################################################################
// ---------------------------------------------------------------------------------
//################################################################################
//Db set class methods

//################################################################################


//################################################################################
// ---------------------------------------------------------------------------------
//################################################################################
//Menu functions


void MyMenu(char**& arr, int count, int& _row, int& _column, int input)
{
	if (input == 224)
	{
		input = _getch();
		//UP
		if (int(input) == 72)
		{
			if (_row == 0)
			{
				arr[_row][_column] = ' ';
				_row = count - 1;
			}
			else
			{
				_row--;
				arr[_row + 1][_column] = ' ';
			}
		}
		//Down
		else if (int(input) == 80)
		{


			_row++;
			arr[_row - 1][_column] = ' ';


		}


		if (_row == -1 && input == 72)
		{
			_row = 0;
			arr[_row][_column] = ' ';
			_row = count - 1;
		}
		if (_row == count && input == 80)
		{


			arr[_row - 1][_column] = ' ';
			_row = 0;
		}


	}

}

void print_menu(char** arr, int a, int size)
{
	system("color 7");
	cout << "\n\n\n\n\n\n";
	for (size_t i = 0; i < size; i++)
	{
		if (i == a)
			SetConsoleTextAttribute(console, 37);
		else
			SetConsoleTextAttribute(console, 7);
		cout << "\t\t\t\t\t\t";
		cout << arr[i] << " ";
		SetConsoleTextAttribute(console, 7);
		cout << endl;


	}

}

Guest& Register()
{
	char ch;

	str username;
	str password;
	float balance;
	cout << "\t\t\t-------------------------------------" << endl;
	cout << "\t\t\t\tEnter your username --> "; cin >> username;
	cout << "\t\t\t-------------------------------------" << endl;
	cout << "\t\t\t\tEnter your password --> ";
	while (true)
	{
		ch = _getch();
		if (ch == 13)
			break;
		password.push_back(ch);
		cout << "*";
	}
	cout << endl;
	cout << "\t\t\t-------------------------------------" << endl;
	cout << "\t\t\t\tEnter your balance --> "; cin >> balance;
	cout << "\t\t\t-------------------------------------" << endl;
	Guest user(username, password, balance);
	ofstream file("users.txt", ios::app);

	if (file.is_open())
	{
		file << username << " " << password << " " << balance << endl;
		SetConsoleTextAttribute(console, 2);
		cout << "Registration complated!!\n";
		SetConsoleTextAttribute(console, 7);
		return user;
	}
	else
	{
		SetConsoleTextAttribute(console, 3);
		cout << "File not openning!!\n";
		SetConsoleTextAttribute(console, 7);

	}
	file.close();


}

bool SignUp(str& username, str& password)
{
	char ch;
	cout << "\t\t\t-------------------------------------" << endl;
	cout << "\t\t\t\tEnter your username --> "; cin >> username;
	cout << "\t\t\t-------------------------------------" << endl;
	cout << "\t\t\t\tEnter your password --> ";
	while (true)
	{
		ch = _getch();
		if (ch == 13)
			break;
		password.push_back(ch);
		cout << "*";
	}
	cout << "\t\t\t-------------------------------------" << endl;
	Guest user(username, password);

	ifstream file("users.txt");
	if (file.is_open())
	{
		str username1, password1;
		while (file >> username1 >> password1)
		{

			if (username1 == user.getUsername() && password1 == user.getPassword())
			{

				file.close();
				return true;
			}
		}
		file.close();
	}
	return false;
}



void getDataFromFile(Guest**& persons, int& count, str fileName)
{
	ifstream file(fileName, ios::in);



	string username, password;
	float balance;

	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> username;
			file >> password;
			file >> balance;


			Guest* newPerson = new Guest(username, password, balance);

			Guest** newPersonArray = new Guest * [count + 1];
			for (size_t i = 0; i < count; i++)
				newPersonArray[i] = persons[i];
			newPersonArray[count] = newPerson;
			count++;

			if (persons != NULL) delete[] persons;
			persons = newPersonArray;
		}

		file.close();
	}

}