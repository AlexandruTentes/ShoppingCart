#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

void cin_option(int & c)
{
	string str = "";

	try
	{
		cin >> str;
		c = stoi(str);
	}
	catch (...) {}
}

void cin_string(string& str)
{
	cin.ignore();
	getline(cin, str);
}

class Category
{
public:
	unsigned int CAT_ID = 0;
	string CAT_NAME = "";
	string DESCRIPTION = "";

public:
	void update_category(unsigned int CAT_ID, string& CAT_NAME, string& DESCRIPTION)
	{
		this->CAT_ID = CAT_ID;
		this->CAT_NAME = CAT_NAME;
		this->DESCRIPTION = DESCRIPTION;
	}

	void update_category(const Category& c)
	{
		this->CAT_ID = c.CAT_ID;
		this->CAT_NAME = c.CAT_NAME;
		this->DESCRIPTION = c.DESCRIPTION;
	}
};

class Product : public Category
{
public:
	unsigned int PID = 0;
	string name = "";
	unsigned int price = 0;

	void create_product(const Product& p)
	{
		this->PID = p.PID;
		this->name = p.name;
		this->price = p.price;
	}

	void create_product()
	{
		cout << "\n Name:";
		cin_string(name);
		cout << "\n Price:";
		cin >> price;
	}

	friend std::ostream& operator <<(std::ostream& os, const Product& data);
};

std::ostream& operator <<(std::ostream& os, const Product& data)
{
	os << "PID: " << data.PID << " Name: " << data.name << " Price: " << data.price;
	os << "    CAT_ID: " << data.CAT_ID << " CAT_NAME: " <<
		data.CAT_NAME << " DESC:" << data.DESCRIPTION;

	return os;
}

class Shop
{
public:
	unordered_map<string, vector<Product>> products;
	unordered_map<string, vector<Category>> categories;
	unordered_map<string, vector<Product>>cart;

	void add_item(Product p, string CAT_NAME)
	{
		if (categories[CAT_NAME].size() == 0)
		{
			cout << "\nCategory does not exist! Create it first:\n";

			Category c;

			cout << "\nCategory name created! Add description: ";
			getline(cin, c.DESCRIPTION);
			c.CAT_NAME = CAT_NAME;
			c.CAT_ID = g_PID_CATEGORY;
			g_PID_CATEGORY++;

			p.update_category(c);
			p.PID = g_PID_PRODUCTS;
			products[CAT_NAME].push_back(p);
			categories[CAT_NAME].push_back(c);
		}
		else
		{
			Category& tmp = categories[CAT_NAME][0];
			Category c;
			c.update_category(tmp.CAT_ID, tmp.CAT_NAME, tmp.DESCRIPTION);
			p.update_category(c);
			p.PID = g_PID_PRODUCTS;
			products[CAT_NAME].push_back(p);
			categories[CAT_NAME].push_back(c);
		}
		g_PID_PRODUCTS++;
	}
	void add_category()
	{
		string cat;
		string desc;
		cout << "\n Enter Category name:";
		cin_string(cat);

		if (categories[cat].size() == 0) {
			cout << "\n Enter Category description:";
			cin_string(desc);
			Category c;
			c.DESCRIPTION = desc;
			c.CAT_NAME = cat;
			c.CAT_ID = g_PID_CATEGORY;
			g_PID_CATEGORY++;
			categories[cat].push_back(c);
			cout << "\nCategory created!" << endl;
		}
		else {
			cout << "\nCategory already exists." << endl;
		}
	}

	void display_categories()
	{
		if (categories.size() == 0) {
			cout << "\nThere are currently no categories." << endl;
		}
		else {
			for (auto& item : categories)
			{
				for (auto& category : item.first)
				{
					cout << category << "\n";
				}
			}
		}
	}

	void printCategory(string cat)
	{
		if (products[cat].size() == 0)
		{
			cout << "No such category";
		}
		for (auto& item : products)
		{
			Product p;
			if (item.first == cat)
			{
				for (int i = 0; i < item.second.size(); i++)
				{
					cout << item.second[i] << endl;
				}

			}
		}
	}

	void remove_item(int PID)
	{
		bool foundPID = false;
		for (auto& item : products)
		{
			int count = 0;
			for (auto& product : item.second)
			{
				if (product.PID == PID) {
					foundPID = true;
					auto i = product;
					products[item.first].erase(products[item.first].begin() + count);
					break;
				}
				count++;
			}
		}
		if (!foundPID) {
			cout << "\n Product not found" << endl;
		}
		else {
			cout << "\n Product found and removed" << endl;
			foundPID = false;
		}
	}

	void addCart(string name, int quant)
	{
		for (auto& item : products)
		{
			for (auto& search : item.second)
			{
				if (search.name == name)
				{
					while (quant >= 0)
					{
						cart[name].push_back(search);
						quant--;
					}

				}
			}
		}
	}

	void clearCart()
	{
		cart.clear();
		cout << "\n Cart cleared";
	}

	void printCart()
	{
		int price;
		for (auto& item : cart)
		{
			price = item.second[0].price * item.second.size();
			cout << item.second[0] << " Quantity: " << item.second.size() << " Price: " << price << endl;

		}
	}

	void removeCart(string name, int quant)
	{
		bool foundCartItem = false;
		for (int i = 1; i <= quant; i++) {
			for (auto& item : cart)
			{
				int count = 0;
				for (auto& search : item.second)
				{
					if (search.name == name) {
						foundCartItem = true;
						cart[item.first].erase(cart[item.first].begin() + count);
						if (item.second.size() == 0) {
							cart.erase(name);
						}
						break;
					}
					count++;
				}
			}
		}
	}


	friend std::ostream& operator <<(std::ostream& os, const Shop& data);

private:
	int g_PID_PRODUCTS = 1;
	int g_PID_CATEGORY = 1;
};

std::ostream& operator <<(std::ostream& os, const Shop& data)
{
	for (auto& item : data.products)
	{
		for (auto& product : item.second)
		{
			os << product << "\n";
		}
		//		os<<item.first<<endl;
	}

	return os;
}
class Person_details
{

public:
	unsigned int ADMIN_ID = 0;
	string username = "";
	string password = "";
	void update_details(unsigned int ADMIN_ID, string& username, string& password)
	{
		this->ADMIN_ID = ADMIN_ID;
		this->username = username;
		this->password = password;
	}

	void update_details(const Person_details& pd)
	{
		this->ADMIN_ID = ADMIN_ID;
		this->username = pd.username;
		this->password = pd.password;
	}

	friend std::ostream& operator <<(std::ostream& os, const Person_details& data);
};

std::ostream& operator <<(std::ostream& os, const Person_details& data)
{
	os << "ID: " << data.ADMIN_ID << "USERNAME: " << data.username << 
		" PASSWORD: " << data.password;

	return os;
}

class Admin
{

public:
	unordered_map<string, vector<Person_details>> admins;
	void register_admin() {
		string username;
		string password;
		cout << "Username: " << endl;
		cin >> username;
		cout << "Password: " << endl;
		cin >> password;

		Person_details pd;
		pd.ADMIN_ID = g_ID_ADMIN;
		pd.username = username;
		pd.password = password;
		//			pd.update_details(g_ID_ADMIN, username, password);
		g_ID_ADMIN++;
		admins[username].push_back(pd);

		for (auto& item : admins)
		{
			for (auto& admin : item.second)
			{
				cout << admin << "\n";
			}
			//		os<<item.first<<endl;
		}
	}
	bool sign_in(string username, string password) {
		bool is_admin;
		bool foundUsername = false;
		bool foundPassword = false;
		for (auto& item : admins)
		{
			if (item.first == username) {
				for (auto& admin : item.second)
				{
					if (admin.password == password) {
						foundPassword = true;
					}
				}
				foundUsername = true;
				break;
			}
		}
		if (!foundUsername) {
			cout << "\nUsername does not exist. Please Register." << endl;
			is_admin = false;
		}
		else if (!foundPassword) {
			cout << "\nPassword is incorrect." << endl;
			is_admin = false;
		}
		else if (foundUsername && foundPassword) {
			cout << "\nYou are now logged in." << endl;
			is_admin = true;
		}
		else {
			is_admin = false;
		}

		return is_admin;
	}
private:
	int g_ID_ADMIN = 1;
};

bool admin_choice(bool is_admin, Admin& object) {
	int reg_choice = 0;
	while (!is_admin && reg_choice != 3) {
		cout << "1. Register\n";
		cout << "2. Sign In\n";
		cout << "3. Back\n";

		cin_option(reg_choice);
		switch (reg_choice)
		{
		case 1:
		{
			object.register_admin();
			break;
		}
		case 2:
		{
			string username;
			string password;
			cout << "Username: " << endl;
			cin >> username;
			cout << "Password: " << endl;
			cin >> password;
			is_admin = object.sign_in(username, password);
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
			cout << "\nInvalid choice." << endl;
			break;
		}
		}

	}
	return is_admin;
}
int main()
{
	Shop shop;
	Admin admin;
	while (true) {
		cout << "\nOptions:\n";
		cout << "1. Admin\n";
		cout << "2. User\n";
		cout << "3. Exit\n";

		int user_choice;
		cin_option(user_choice);

		bool is_admin = false;
		bool is_user = false;

		if (user_choice == 1) {
			is_admin = admin_choice(is_admin, admin);
		}
		else if (user_choice == 2) {
			is_user = true;
		}
		else if (user_choice == 3) {
			return 0;
			break;
		}

		while (is_admin || is_user) {
			cout << "\nOptions:\n";
			if (is_admin || is_user) {
				cout << "1. Add to cart\n";
				cout << "2. Remove from cart\n";
				cout << "3. Clear cart\n";
				cout << "4. Print cart\n";
				cout << "5. Print categories\n";
				cout << "6. Print all\n";
			}
			if (!is_admin && is_user) {
				cout << "7. Back\n";
			}
			if (is_admin && !is_user) {
				cout << "\nAdmin Options:\n";
				cout << "8. Add product\n";
				cout << "9. Remove product\n";
				cout << "10. Add Category\n";
				cout << "11. Log out\n";
			}
			int c;
			cin_option(c);

			switch (c)
			{
			case 1:
			{
				string name;
				int quant;
				cout << "\n Enter name of product: ";
				cin_string(name);
				cout << "\n enter quantity";
				cin >> quant;
				shop.addCart(name, quant);
				break;
			}
			case 2:
			{
				__cplusplus;
				string str;
				int q;
				cout << "\nProduct name: ";
				cin_string(str);
				cout << "\nQuantity: ";
				cin >> q;
				shop.removeCart(str, q);
				break;
			}
			case 3:
			{
				shop.clearCart();
				break;
			}
			case 4:
			{
				shop.printCart();
				break;
			}
			case 5:
			{
				string cat;
				cout << "\n Category:";
				cin_string(cat);
				shop.printCategory(cat);
				break;
			}
			case 6:
			{
				cout << shop;
				break;
			}
			case 7:
			{
				if (!is_admin && is_user) {
					is_admin = false;
					is_user = false;
				}
				else {
					cout << "\nInvalid option" << endl;
				}
				break;
			}
			case 8:
			{
				if (is_admin) {
					Product p;
					string cat;
					p.create_product();
					cout << "\n Category:";
					cin_string(cat);
					shop.add_item(p, cat);
				}
				else {
					cout << "\nInvalid option" << endl;
				}
				break;
			}
			case 9:
			{
				if (is_admin) {
					int PID;
					cout << "\n Enter product PID to remove :";
					cin >> PID;
					shop.remove_item(PID);
				}
				else {
					cout << "\nInvalid option" << endl;
				}
				break;
			}
			case 10:
			{
				if (is_admin) {
					shop.add_category();
				}
				else {
					cout << "\nInvalid option" << endl;
				}
				break;
			}
			case 11:
			{
				if (is_admin) {
					is_admin = false;
				}
				else {
					cout << "\nInvalid option" << endl;
				}
				break;
			}
			default:
			{
				cout << "\nInvalid option" << endl;
				break;
			}
			}
		}
	}

}

/*
Build Shopping cart
Admin
---------------------
1) Add products
	 PID PNAME PRICE CAT_ID
	 111 LUX   40    11
	 112 SUNSILK 80  12
2) Add Categories
	 CAT_ID CAT_NAME DESCRIPTION
	 11     SOAP     Some desc
	 12     SHAMPOO  some ----
3) See all records based on
		a) CAT_NAME
		b) Range Price  (20-50)
		c) Complete details
		   111 LUX   40    SOAP     Some desc
User
---------------
1) Place the order by Product details
   before that he should be able to view
	  Products a)All products
			   b) Based on category
2) Based on Quantity (Calulate price) add to cart
3) Products added to the cart should have
	a) Remove item/Product
	b) Clear Cart
*/