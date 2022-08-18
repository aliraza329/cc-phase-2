#pragma once

#include<iostream>
#include<string>
#include<fstream>
using namespace std; 

template<typename T>
class Stack
{
	T * arr;
	int max;
	int current;
public:
	
	Stack::Stack()
	{
		arr = nullptr;
		current = 0;
		max = 0;
	}
	Stack::~Stack()
	{
		delete arr;
	}

	void Stack::initialize_stack(int size)
	{

		arr = new T[size];
		max = size;
		current = 0;
	}
	void Stack::display()
	{
		cout << "Stack: ";
		for (int i = 0; i < current; i++)
		{
			cout << arr[i] << ' ';
		}
		cout << endl;
	}
	void Stack::push(T element)
	{
		if (current == max)
		{
			int new_size = max + 5;
			T *temp_data = new T[new_size];
			for (int i = 0; i < max; i++)
			{
				temp_data[i] = arr[i];
			}
			delete[]arr;
			arr = temp_data;
			temp_data = nullptr;
			max = new_size;
		}
		arr[current] = element;
		current++;
	}
	int Stack::pop()
	{
		if (current>0)
		{
			current--;
		}
		else
		{
			return -1;
		}
		return 0;

	}
	T Stack::Top()
	{
		if (current > 0)
		{
			return arr[current - 1];
		}
		return -1;
	}

	bool Stack::Is_Stack_Empty()
	{
		if (current == 0)
		{
			return true;
		}
		return false;
	}
	bool Stack::Is_Stack_Full()
	{
		if (current == max)
		{
			return true;
		}
		return false;
	}
		
};

