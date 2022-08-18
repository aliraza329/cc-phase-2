#include"Lexical.h"

int Lexical::pointer = 0;
int Lexical::start = 0;
 
Lexical::Lexical()
{

}

bool Lexical::Read_Transition_Table(int arr[46][24])
{
	ifstream read;
	char ch = '\0';
	string number;
	string line;
	read.open("table.txt", ios::in);

	if (!read)
	{
		cout << "Table File not found!!!!!!!.............\n";
		return false;
	}
	int arrRow = 1, arrCol = 0;
	int num = 0;

	while (!read.eof())
	{
		getline(read, line);
		arrCol = 1;
		for (int i = 0; i < line.length(); i++)
		{

			ch = line[i];
			if (ch == ' ')
			{
				num = stoi(number);
				arr[arrRow][arrCol] = num;
				arrCol++;
				number.clear();
			}

			else
			{
				number.push_back(ch);
			}
		}
		arrRow++;
	}
	return true;
}

int Lexical::Read_Character_Ascii(Character_Ascii *Cha)
{
	ifstream fin;
	fin.open("ascii.txt", ios::in);
	int counter = 0;

	while (!fin.eof())
	{
		fin >> Cha[counter].character;
		fin.ignore();
		fin >> Cha[counter].acsii;
		counter++;
	}
	fin.close();
	return counter;

}

int Lexical::Read_Accept_States(int *Accepting)
{
	ifstream fin;
	fin.open("accepting.txt", ios::in);
	int i = 1;
	while (!fin.eof())
	{
		fin >> Accepting[i];
		i++;
	}
	return i;
	fin.close();
}
int Lexical::Get_ascii(const Character_Ascii *C, const int & len, const char &ch)
{
	for (int i = 0; i < len; i++)
	{
		if (C[i].character == ch)
			return C[i].acsii;
	}
	return 0;
}
bool Lexical::Match_Keyword(string token)
{
	ifstream read;
	string word;
	read.open("keyword.txt", ios::in);
	while (!read.eof())
	{
		read >> word;
		if (word == token)
		{
			read.close();
			return true;
		}
	}
	read.close();
	return false;
}

int Lexical::getLength(char arr[])
{
	int i = 0;
	for (i = 0; arr[i] != '\0'; i++);
	return i;
}
void Lexical::Token_Type(char *token, const int state, string &type)
{
	switch (state)
	{
	case 35:
		type = "ID";
		break;
	case 36:
		type = "sub";
		break;
	case 9:
		type = "Num";
		break;
	case 10:
		type = "increment";
		break;
	case 11:
		type = "add";
		break;
	case 12:
		type = "addEq";
		break;
	case 13:
		type = "mul";
		break;
	case 14:
		type = "div";
		break;
	case 16:
		type = "!Eq";
		break;
	case 18:
		type = ":Eq";
		break;
	case 20:
		type = "==";
		break;
	case 21:
		if (Match_Keyword(token)){
			type = "cout<<";
		}
		else
		{
			int len = getLength(token);
			token[len - 1] = '\0';
			token[len - 2] = '\0';
			start -= 2;
			pointer -= 2;
		}
		break;
	case 23:
		type = "<>";
		break;
	case 24:
		type = "<";
		break;
	case 25:
		type = "<<";
		break;
	case 27:
		type = ">>";
		break;
	case 28:
		type = ">";
		break;
	case 29:
		type = "[";
		break;
	case 30:
		type = "]";
		break;
	case 31:
		type = "{";
		break;
	case 32:
		type = "}";
		break;
	case 33:
		type = "(";
		break;
	case 34:
		type = ")";

		break;
	case 39:
		if (Match_Keyword(token)){

			type = token;
		}
		break;

	case 44:
		type = ";";
		break;
	case 45:
		type = ",";
		break;

	case 41:
		if (Match_Keyword(token)){
			type = "cin>>";
		}
		else
		{
			int len = getLength(token);
			token[len - 1] = '\0';
			token[len - 2] = '\0';
			start -= 2;
			pointer -= 2;
		}
		break;

	default:
		break;
	}

}
void Lexical::Tokenization(string line, int ch_counter, int state)
{
	ofstream Tokens, Error;

	Tokens.open("token.txt", ios::app);
	Error.open("error.txt", ios::app);

	char token[20] = { '\0' };
	string type = "Error";

	int len = ch_counter + start, index = 0;
	for (start; start < len; start++)
	{
		token[index] = line[start];
		index++;
	}

	Token_Type(token, state, type);

	if (type != "Error")
	{
		Tokens << "< " << token << " , " << type << " > " << endl;
	}
	else
	{
		Error << token << endl;
	}
	Tokens.close();
	Error.close();

}
void Lexical::Lexical_Analyzer(const int states_Table[46][24], const int *Accepting_states, const Character_Ascii *Cha, const int & ascii_count)
{
	ifstream fin;
	fin.open("source_code.txt", ios::in);

	int state = 1, ascii_value = 0, ch_counter = 0;
	bool flag = false;
	char ch = '\0';
	string line;

	while (!fin.eof())
	{
		getline(fin, line);
		state = 1;
		ch_counter = 0;
		pointer = 0;
		start = 0;

		for (pointer; line[pointer] != '\0'; pointer++)
		{
			flag = true;
			ch = line[pointer];
			ascii_value = Get_ascii(Cha, ascii_count, ch);
			if (ascii_value == 0)
			{
				if (ch == ' ' || ch == '\t')
				{
					state = states_Table[state][20];
				}
				else
				{
					flag = false;
					ch_counter++;
				}
			}
			else
			{
				state = states_Table[state][ascii_value];
				ch_counter++;
			}

			if (Accepting_states[state] != 0)
			{
				if (ch != ' '&& Accepting_states[state]<0)
				{
					ch_counter--;
					pointer--;
				}
				Tokenization(line, ch_counter, state);

				if (ch == ' ' || ch == '\t'){
					start++;
				}
				state = 1;
				ch_counter = 0;
			}
			else if (ch_counter == 0 && flag == true)
			{
				state = 1;
				start++;
			}
			else if (state == 0 || flag == false){
				bool startvar = false;
				if (ch != ' ' && flag == true && ch != '\t' && ch != '.'){
					ch_counter--;
					pointer--;
					startvar = true;
				}
				else if (ch == ' ')
				{
					pointer--;
					startvar = true;
				}
				else if (ch_counter != 1){
					state = states_Table[state][20];
					ch_counter--;
					pointer--;
				}
				Tokenization(line, ch_counter, state);
				state = 1;
				ch_counter = 0;

			}
			else if (state == 43)
			{
				ch_counter -= 2;
				pointer -= 2;

				Tokenization(line, ch_counter, state);
				state = 1;
				ch_counter = 0;
			}
			if (line[pointer + 1] == '\0' && ch_counter >0)
			{
				state = states_Table[state][20];
				if (state == 43)
				{
					ch_counter--;
					pointer--;
				}
				Tokenization(line, ch_counter, state);
				state = 1;
				ch_counter = 0;
			}
		}
	}
	cout << "Token and Error file are created!!!.........";
	fin.close();
}
void Lexical::Lexical_Code()
{
	int states_Table[46][24] = { 0 }, Accepting_states[46] = { 0 };
	Character_Ascii Cha[100];

	bool check = Read_Transition_Table(states_Table);
	if (!check)
	{
		return;
	}

	int ascii_count = Read_Character_Ascii(Cha);

	int total_accept = Read_Accept_States(Accepting_states);

	Lexical_Analyzer(states_Table, Accepting_states, Cha, ascii_count);

}

Lexical::~Lexical()
{

}