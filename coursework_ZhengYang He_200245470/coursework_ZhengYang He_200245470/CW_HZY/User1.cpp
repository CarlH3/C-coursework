#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<vector>
#include<algorithm>
using namespace std;



class System 
{
private:
protected:
public:	
	int count;
	bool running;
	char choice;
	string userN;
	string userP;
	
	System()
	{
		running = true;
	}

	void Run()
	{
		while (running)
		{
			Menu();
		}
	}

	virtual void Menu()
	{
		cout << "*****************" << endl;
		cout << "1.Login" << endl;
		cout << "2.Register" << endl;
		cout << "3.Show " << endl;
		cout << "4.Exit " << endl;
		cout << "*****************" << endl;
		cin >> choice;
		switch (choice) {
		case '1':
			Enter();
			break;
		case '2':
			Register();
			break;
		case '3':
			Show();
			break;
		case '4':
			Exit();
			break;
		default:
			system("cls");
			cout << "error, please choose right one" << endl;
			break;
		}
	}

	void Enter()
	{
		string userNT = "";
		string userPT = "";
		string all;
		ifstream in("password.txt", ios::in);
		try {
			
			if (!in.is_open())
			{
				throw - 1;
			}

		}
		catch (int err) {
			cout << "open file failed." << endl;
			cout << "Please creat a file which named password.txt to store name and password " << endl;
			return;
		}
		while (getline(in, all, '\n'))
		{
			userNT = "";
			userPT = "";
			
			for (auto str : all)
			{
				if (str == ' ')
				{
					break;
				}
				userNT = userNT + str;
			}
			for (int i =0;i<all.size();i++)
			{
				if (all[i] == ' ')
				{
					i++;
					for ( i;i < all.size(); i++)
					{
						userPT = userPT + all[i];
					}
					
				}
			}
		}

		cout << "please enter your user name : ";
		cin >> userN;

		if (userN == userNT)
		{	
			
			cout << "Now we get the user name, ";
			cout << "please enter your password : ";
			
			cin >> userP;
			encode(userP);

			if (userP == userPT)
			{
				cout << "password right,welcome to the system! " << endl;
			}

			int count = 0;

			while (userP != userPT)
			{
				
				if (count == 2)
				{
					cout << "out of the system " << endl;
					exit(0);
				}
				count++;
				cout << "You enter wrong password,please try again : " << endl;
				cin >> userP;
				encode(userP);
				
				if (userP == userPT )
				{
					cout << "password right,welcome to the system! " << endl;
					break;
				}
				
			}
		}
		else
		{
			cout << "There is no user in the file,please register!" << endl;
		}


	}

	void Show()
	{
		cout << "System will show u the userName and encrypted_password: " << endl;
		print(userN);
		print(userP);
	}

	void Register()
	{
		ofstream out;
		out.open("password.txt",ios::app);
		
		if (!out.is_open())
		{
			cout << "open file failed." << endl;
		}
		else 
		{
			cout << "Open file succeed." << endl;
			cout << "Context will be savd to the txt . " << endl;
		}

		cout << "please enter your user name : " << endl;
		cin >> userN;

		cout << "please enter your user password : ";
		cin >> userP;
		
		encode(userP);

		out << userN << ' ' << userP << endl;
		out.close();
		cout << " Save done,close the file. " << endl;

	}

	string encode(string userP1)
	{
		int offset = 0;
		string encrypted_password = "";
		for (int str_id = 0; str_id < userP1.length(); str_id++)
		{
			int asc = userP1[str_id] + offset;
			count = Collatz(asc);
			encrypted_password += to_string(count);
			offset = count;
		}
		userP1 = encrypted_password;
		userP = userP1;
		return userP;
	}
	
	int Collatz(int num)
	{
		count = 0;
		while (num != 1)
		{
			if (num % 2 == 0)
			{
				num = num / 2;
				count += 1;
			}
			else
			{
				num = num * 3 + 1;
				count += 1;
			}
		}

		return count;
	}

	template <typename T>
	void print(T value)
	{
		cout << " "<< value << " " << endl;
	}

	void Exit()
		{
		cout << "out of the system " << endl;
			exit(0);
		}

	~System()
		{
			cout << "the system will log out!" << endl;
		}

};

class GSystem : public System
{
	virtual void Menu()
	{
		cout << "*****************" << endl;
		cout << "1.Login" << endl;
		cout << "2.Register" << endl;
		cout << "3.Show " << endl;
		cout << "4.Exit " << endl;
		cout << "5.Generate " << endl;
		cout << "*****************" << endl;
		cin >> choice;
		switch (choice) {
		case '1':
			Enter();
			break;
		case '2':
			Register();
			break;
		case '3':
			Show();
			break;
		case '4':
			Exit();
			break;
		case '5':
			GPassword();
			break;
		default:
			system("cls");
			cout << "error, please choose right one" << endl;
			break;
		}
	}

	void GPassword()
	{
		srand((unsigned)time(NULL));

		fstream my("passwordtest.txt", ios::out | ios::trunc);
		if (!my.is_open())
		{
			cout << "Open file failed. " << endl;
		}
		else
		{
			cout << "open filed,now start generating passwords. " << endl;
		}


		vector<int> at;
		
		for (int i = 97; i <= 122; i++)
		{
			at.push_back(i);
		}
		vector<int> Tem;
		Tem = at;
		random_shuffle(Tem.begin(), Tem.end());
		Tem.erase(Tem.begin() + 10, Tem.end());
		for (int i = 1; i < 101; i++) //first 10000 password in 10 
		{
			for (int j = 0; j < 100; j++)
			{

				string genPwd = "";
				
				
				for (int k = 0; k < i; k++)
				{
					int tR = (rand() % 10);
					auto tmpChar = (char)Tem[tR];
					genPwd = genPwd + tmpChar;
				}
				auto p = encode(genPwd);
				//cout << p << endl;
				my << p << endl;
			}
		}

		vector<int> ar;
		for (int i = 1; i <= 255; i++)
		{
			ar.push_back(i);
		}
		for (int i = 1; i < 101; i++) //second 10000 password in 256
		{
			for (int j = 0; j < 100; j++)
			{
				string genPwd = "";
				vector<int> tmpVec = ar;
				auto step = 0;
				for (int k = 0; k < i; k++)
				{
					random_shuffle(tmpVec.begin(), tmpVec.end());
					step = step + Collatz(tmpVec[k]);
					genPwd = genPwd + to_string(step);
				}

				auto p = encode(genPwd);
				//cout << p << endl;
				my << p << endl;
			}
		}
		cout << endl;
		cout << "20000 passwords done " << endl;
		cout << endl;

	}
};


inline void display() {
	cout << "student number : 200245470" << endl;
	cout << "student name : ZhengYang He " << endl;
}

void func(System* obj)
{
	obj->Run();
}


int main()
{
	display();
	//System* s = new System;
	//s->Run();
	//s->Run();
	GSystem* s = new GSystem;
	func(s);
	delete s;
	//cout << s->encode("A friend to all is a friend to none") << endl;
}