#pragma once
#include<iostream>
#include<cstring>
#include<vector>
#include<ctype.h>
using namespace std;
class InputAdapter
{
	//This function will break the input string to know unit(kb,mb,gb) and also get number value
	static pair<long long int, string> splitInputInActualMemory(char[]);		
	//this function will actaully help in converting the input size in kb
	static long long int calculate(pair<long long int, string>);					
public:
	//this function will accept string and give calculate memory, after actual memory conversion
	static long long int getConvertedMemoryFromString(char[]);
	static int validateInput(int);
};

