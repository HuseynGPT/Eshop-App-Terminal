#pragma once


#pragma once
namespace Ecommerce
{
	namespace Database
	{
		class User
		{
			str _username;
			str _password;
		public:
			User()
			{
				_username = "";
				_password = "";
			}
			User(str username, str password)
			{
				setUsername(username);
				setPassword(password);
			}

			void setUsername(str username);
			void setPassword(str password);

			inline str getUsername()const;
			inline str getPassword()const;
			virtual ~User() = 0 {}
		};

		class Guest :public User
		{
			str _connected_date;
			float _balance;
		public:
			Guest() :User()
			{
				_connected_date = "";
			}
			Guest(str username, str password, float balance = 0) :User(username, password), _balance(balance)
			{
				_connected_date = "["  __DATE__ "] " __TIME__;
			}

			inline str GetConnectedDate()const;
			inline float GetBalance()const { return this->_balance; }
			void ShowMyInfo()
			{
				cout << "Username: " << this->getUsername() << endl;
				cout << "Connecter date: " << this->_connected_date << endl;
				cout << "Balance: " << this->_balance << endl;

			}
			~Guest() override
			{

			}
		};

		class Admin :public User
		{
		public:
			Admin() :User() {}
			Admin(str username, str password) :User(username, password) {}
			~Admin()override {}

		};

		class Telephone
		{
			static int id;
			int _id = id;
			str _marka;
			str _model;
			str _color;
			float _price;
			int _memory;
			int _storage;
			int _quantity;
		public:
			Telephone()
			{
				_id = 0;
				this->_marka = "";
				this->_model = "";
				this->_color = "";
				this->_memory = 0;
				this->_storage = 0;
				this->_quantity = 0;
			}
			Telephone(str marka, str model, str color, int memory, float price, int storage, int quantity)
			{
				id++;
				SetMarka(marka);
				SetModel(model);
				SetColor(color);
				this->_price = price;
				SetMemory(memory);
				SetStorage(storage);
				SetQuantity(quantity);

			}
			Telephone(const Telephone& t1)
			{
				this->_id++;
				SetMarka(t1._marka);
				SetModel(t1._model);
				SetColor(t1._color);
				this->_price = t1._price;
				SetMemory(t1._memory);
				SetStorage(t1._storage);
				SetQuantity(t1._quantity);
			}

			Telephone& operator=(const Telephone& t1)
			{
				this->_id = id++;
				SetMarka(t1._marka);
				SetModel(t1._model);
				SetColor(t1._color);
				this->_price = t1._price;

				SetMemory(t1._memory);
				SetStorage(t1._storage);
				SetQuantity(t1._quantity);
				return *this;
			}

			void SetMarka(str marka);
			void SetModel(str model);
			void SetColor(str color);
			void SetMemory(int memory);
			void SetStorage(int storage);
			void SetQuantity(int quantity);

			void WhenUserBuy() { this->_quantity--; }
			inline str GetMarka()const;
			inline str GetModel()const;
			inline str GetColor()const;
			inline int GetMemory()const;
			inline int GetStorage()const;
			inline int GetQuantity()const { return this->_quantity; }
			inline int GetId()const { return this->_id; }
			inline float GetPrice()const { return this->_price; }



			void Show()
			{
				cout << "ID: " << this->_id << endl
					<< "Marka; " << this->_marka << endl
					<< "Model: " << this->_model << endl
					<< "Price: " << this->_price << " $" << endl;
				cout << "----------------------------------\n";

			}
			void ShowDetailedInfo()
			{
				cout << "ID: " << this->_id << endl
					<< "Marka; " << this->_marka << endl
					<< "Model: " << this->_model << endl
					<< "Color: " << this->_color << endl
					<< "Price: " << this->_price << " $" << endl
					<< "Memory: " << this->_memory << endl
					<< "Storage: " << this->_storage << endl
					<< "Quantity: " << this->_quantity << endl;
				cout << "----------------------------------\n";


			}
		};


		class DbSet
		{
			Telephone** _items;
			int _items_count = 0;
		public:
			DbSet()
			{
				_items = nullptr;
			}

			DbSet(Telephone** _items, int item_count)
			{
				SetTelephone(_items, item_count);
			}

			void add(Telephone* item)
			{
				Telephone** new_items_list = new Telephone * [_items_count + 1] {};
				for (size_t i = 0; i < _items_count; i++)
					new_items_list[i] = new Telephone(*_items[i]);
				new_items_list[_items_count] = item;

				for (size_t i = 0; i < _items_count; i++)
					delete _items[i];
				delete[] _items;
				_items = new_items_list;
				_items_count++;

			}
			void deleteByid(const int& id)
			{
				Telephone** new_items_list = new Telephone * [_items_count - 1] {};
				int indexx = 0;
				int finded_index = 0;
				bool isCheck = false;
				for (size_t i = 0; i < _items_count; i++)
				{
					if (_items[i]->GetId() == id)
					{
						finded_index = i;
						isCheck = true;
						break;
					}

				}
				if (isCheck == false)
				{
					try
					{
						throw new InvalidArgument("User not found", __LINE__, __FILE__, __TIME__);
					}
					catch (const exception* ex)
					{
						cout << ex->what() << endl;
					}
				}
				else
				{
					for (size_t i = 0; i < finded_index; i++)
						new_items_list[i] = new Telephone(*_items[i]);

					for (size_t i = finded_index + 1; i < _items_count; i++)
						new_items_list[i - 1] = new Telephone(*_items[i]);

					for (size_t i = 0; i < _items_count; i++)
						delete _items[i];
					delete[] _items;

					_items = new_items_list;
					_items_count--;
					cout << "deleted sucesfuly" << endl;
				}



			}
			Telephone* getItem(const int& id)
			{
				for (size_t i = 0; i < _items_count; i++)
				{
					if (_items[i]->GetId() == id)
					{
						return this->_items[i];

					}
				}
			}


			void SetTelephone(Telephone** items, int items_count)
			{
				if (this->_items != nullptr)
				{
					for (size_t i = 0; i < _items_count; i++)
					{
						delete _items[i];
					}
					delete[] _items;
				}
				Telephone** new_items = new Telephone * [items_count] {};
				for (size_t i = 0; i < items_count; i++)
				{
					new_items[i] = new Telephone(*_items[i]);

				}

				_items = new_items;
				_items_count = items_count;
			}
			void ShowAll()
			{
				if (_items_count == 0)
				{
					try
					{

						throw new DatabaseException("List is empty", __LINE__, __FILE__, __TIME__);
					}
					catch (const exception* ex)
					{
						cout << ex->what() << endl;
					}
				}
				for (size_t i = 0; i < _items_count; i++)
					_items[i]->ShowDetailedInfo();
			}
			void ShowSmall()
			{
				if (_items_count == 0)
				{
					try
					{

						throw new DatabaseException("List is empty", __LINE__, __FILE__, __TIME__);
					}
					catch (const exception* ex)
					{
						cout << ex->what() << endl;
					}
				}
				for (size_t i = 0; i < _items_count; i++)
					_items[i]->Show();
			}

			inline Telephone** GetItems()const { return this->_items; }

		};

		int Telephone::id = 0;
	}


}