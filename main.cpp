#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

string command = "";
char ch;
string file_contents = "";
bool quit = false;
string password = "";
fstream password_file;
const char alpha_num[] = "0123456789"
						 "!@#$%^&*"
						 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
						 "abcdefghijklmnopqrstuvwxyz";
int arrLen = sizeof(alpha_num) - 1;
unsigned int length = 0;

char generate()
{
	return alpha_num[rand() % arrLen];
}

void operate()
{
	cout << "> ";
	cin >> command;
	srand(time(0));
	if (command == "$show")
	{
		password_file.open("passwords.txt", ios::in);
		while (getline(password_file, file_contents))
		{
			cout << file_contents << endl;
		}
		password_file.close();
	}
	else if(command== "$help")
	{	
		cout << "Welcome to passwordMan v1.0. This is a simple password manager written in c++." << endl;
		cout << "The commands are: \n\"$quit\" to quit\n\"$new\" for generating new passwords\n\"$clear\" to clear all the stored passwords" << endl;
	}
	else if (command == "$new")
	{
		string site_name;
		cout << "Length of the password: ";
		cin >> length;
		if(length < 5)
			cout << "The length must be greater than 5!" << endl;
		else
		{
			for (int i = 0; i < length; i++)
			{
				password += generate();
			}
			cout << "User/Site name: ";
			cin >> site_name;
			password_file.open("passwords.txt", ios::app);
			password_file << "Site name: " << site_name << endl;
			password_file << "Password: " << password << endl;
			password_file << "\n";
			password_file.close();
			cout << password << endl;
		}
	}
	else if (command == "$clear")
	{
		string option;
		cout << "Do you want to proceed [y/n]: ";
		cin >> option;
		if (option == "y")
		{
			password_file.open("passwords.txt", ios::out);
			password_file << "";
			password_file.close();
			cout << "Cleared all passwords!" << endl;
		}
		else if(option == "n")
		{
			cout << "Aborted!" << endl;
		}
		else{
			cout << "Invalid option!" << endl;	
		}
	}
	else if(command == "$quit")
	{
		quit = true;
	}
	else
	{
		cout << "Command not found!" << endl;
	}
}

int main()
{
	while (!quit)
	{
		operate();
	}

	return 0;
}
