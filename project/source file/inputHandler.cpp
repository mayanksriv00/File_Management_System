#include "inputHandler.h"
static long long int value = 0;
pair<long long int, string> InputAdapter::splitInputInActualMemory(char value[])
{
	//breaking sentence in unit and value
	vector<string> wordsVector;
	
	int index = 0;
	long long int memoryValue = 0;
	string memoryUnit = "";
	//This will extract the value from sentence
	while (index < strlen(value) && isdigit(value[index]))			
	{
		memoryValue = (memoryValue * 10) + (value[index] - '0');
		index += 1;
	}
	//will manage extra spaces in sentence
	while (index < strlen(value) && value[index] == ' ')		
		index += 1;
	//will store the unit of the input ex: kb,mb,gb etc
	while (index < strlen(value) && isalpha(value[index]))		
	{
		memoryUnit += tolower(value[index]);
		index+=1;
	}
	pair<long long int, string> memoryUnitPair;
	memoryUnitPair.first = memoryValue;
	memoryUnitPair.second = memoryUnit;
	return memoryUnitPair;
}
//this function will actuall do the conversion form gb or mb to kb (note: kb is considered as lowest unit)
long long int InputAdapter::calculate(pair<long long int, string> memoryUnitPair)				
{
	long long int result = 0;
	if (memoryUnitPair.second.compare("gb") == 0)
		result = ((memoryUnitPair.first) * 1024) * 1024;
	else if (memoryUnitPair.second.compare("mb") == 0)
		result = memoryUnitPair.first * 1024;
	else
		result = memoryUnitPair.first;

	return result;
}
//this function will accept string and give calculate memory, after actual memory conversion
long long int InputAdapter::getConvertedMemoryFromString(char inputString[])
{
	pair<long long int, string> memoryUnitPair=splitInputInActualMemory(inputString);
	long long int convertedMemory = calculate(memoryUnitPair);
	return convertedMemory;
}
int InputAdapter::validateInput(int length)
{
	if (length == 0)
	{
		cout << "[Input String Exception] : Input is invalid, Please give correct input" << endl;
		return 0;
	}
	return 1;
}