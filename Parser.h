#pragma once

#include"Lexical.h"
#include"Stack.h" 
using namespace std;

class Parser:protected Lexical
{
	void Read_Rule(int rule[][28])
	{
		ifstream read;
		read.open("parsing_table.txt", ios::in);
		for (int i = 1; i < 31; i++)
		{
			for (int j = 1; j < 28; j++)
			{
				read >> rule[i][j];
				read.ignore();
			}
		}
		read.close();
	}
	void Read_Grammer(int Grammer[][10])
	{
		ifstream read;
		read.open("grammer.txt", ios::in);
		int a, i = 1;
		int j = 0;
		while (!read.eof())
		{
			read >> a;
			Grammer[i][j] = a;
			j++;
			if (a == 999)
			{ 
				i++;
				j = 0;
			}
		}
	}
	void Read_Type(char type_name[][10])
	{
		ifstream read;
		string a;
		char tokens[25][10] = { '\0' };
		read.open("type.txt", ios::in);
		int i = 1;
		while (!read.eof())
		{
			read >> type_name[i];
			
			i++;
		}
		read.close();
	}
	int getLength(char arr[])
	{
		int i = 0;
		for (i = 0; arr[i] != '\0'; i++);
		return i;
	}
	bool matchToken(char token1[5], char token2[5])
	{
		if (getLength(token1) == getLength(token2))
		{

			for (int i = 0; token1[i] != '\0'; i++)
			{
				if (token1[i] != token2[i])
				{
					return false;

				}
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	int Find_Type(char token[], char type_name[30][10])
	{
		for (int i = 1; i < 27; i++)
		{
			if (matchToken(token, type_name[i])){
				return i;
			}
		}
		return -1;
	}

public:
	Parser()
	{

	}
	void Parser_Main();

	~Parser()
	{

	}
};
void Parser::Parser_Main()
{
	ifstream read;
	ofstream write;
	string a;
	char type[50] = { '\0' };

	Stack<int> s;

	s.initialize_stack(20);

	char type_name[30][10] = { '\0' };

	int rules[31][28] = { 0 };
	int grammer[59][10] = { 0 };
	Lexical_Code();
	Read_Type(type_name);
	Read_Rule(rules);
	Read_Grammer(grammer);
	read.open("token.txt", ios::in);
	s.push(27);
	s.push(-1);

	while (1)
	{
		read >> type;
		if (read.eof()){
			if (s.Top() != 27)
				cout << "Error" << endl;
			break;
		}
		read.ignore();
		read >> type;
		int type_number = Find_Type(type, type_name);
		cout << "Input is " << type << " and type number is : " << type_number << endl;
		if (type_number == s.Top())
		{
			cout << "Token matched: " << s.Top() << "	";
			s.pop();
			s.display();
			continue;
		}
		else if (s.Top() != 9)
		{
			while (1){

				if (s.Top() == 777)
				{
					s.pop();
				}
				if (s.Top() == type_number)
				{
					cout << "Token matched: " << s.Top() << endl;
					s.pop();
					s.display();
					break;
				}
				if (s.Top() > 0 && s.Top() != type_number)
				{
					break;
				}
				int newRule = rules[(s.Top())*-1][type_number];
				cout << "Rule number: " << newRule << endl;
				if (newRule == 777)
				{
					cout << "Error" << endl;
					s.pop();
					continue;
				}
				if (newRule == 888)
				{
					cout << "Error" << endl;
					break;
				}
				int i = 0;
				for (i; grammer[newRule][i] != 999; i++);
				s.pop();
				for (i = i - 1; i >= 0; i--)
				{
					s.push(grammer[newRule][i]);
					cout << grammer[newRule][i] << ' ';
				}
				s.display();
			}

		}
		else
		{
			break;
		}

	}
}

