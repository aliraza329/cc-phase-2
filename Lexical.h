#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std; 

class Lexical
{
	static int start;
	static int pointer;
	struct Character_Ascii
	{
		int acsii;
		char character;
	};
	bool Read_Transition_Table(int arr[46][24]);

	int Read_Character_Ascii(Character_Ascii *Cha);

	int Read_Accept_States(int *Accepting);
	int Get_ascii(const Character_Ascii *C, const int & len, const char &ch);
	bool Match_Keyword(string token);

	int getLength(char arr[]);
	void Token_Type(char *token, const int state, string &type);
	void Tokenization(string line, int ch_counter, int state);

	void Lexical_Analyzer(const int states_Table[46][24], const int *Accepting_states, const Character_Ascii *Cha, const int & ascii_count);
public:
	Lexical();
	~Lexical();
	void Lexical_Code();
	
};


