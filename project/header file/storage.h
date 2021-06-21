#pragma once
#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstring>

using namespace std;

class Storage
{
private:
	long long int storageCapacity = 0;
	long long int blockSize = 0;
	long long int totalBlocks = 0;
	//This vector will be the actual physical memory of the system and shows the replica of actual physical memory where data will be stored
	vector<int> physicalMemory;		
	//This vector will store the record of the free spaces available in the system
	vector<int*> freePool;				
	struct MemoryBlock
	{
		//its just a data that will be stored in the file
		int* data_address = NULL;		
		MemoryBlock* next = NULL;
	};
	//This structure wull keep the record of the file information in the system
	struct FileAddressInfo {					
		long long int fileSize = 0;
		long long int fileBlockSize = 0;
		MemoryBlock* start = NULL;
	};
	//This HashMap is like a iNode implementation that maintain the record of fileID and its respective FileAddressInfo
	unordered_map <string, FileAddressInfo*> iNode;	

	//The use of this function is to allocate initialize system memory and freePool memory
	void set_storageData(long long int);				
	
	void populate_iNode(string, long long int, long long int);

	//This function is used to create the linkedList of Memory Block, bacically assigning freepool space and storing address to linkedlist
	void storeFileData(string);				
public:
	//This function is the main funcion of the class to initiate the handle the handle the memory type
	Storage(long long int,long long int);	
	//This function will print the current stats of the memory
	void getStorageDetail();
	//This function will allocate memory for the file and store index in the iNode map.
	void addFile(string, long long int);
	//This funtion will give the data address where blocks are present in a file
	void retrieveFileData(string);			
	//This function will be used to delete a file if a file exist
	void deleteFile(string);				
	 
};

