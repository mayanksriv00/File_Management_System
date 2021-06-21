#include "storage.h"

Storage::Storage(long long int storageCapacity, long long int blockSize)
{
	this->storageCapacity = storageCapacity;
	this->blockSize = blockSize;
	// Assuming that storage capacity is uniformly divided in block size
	this->totalBlocks = storageCapacity / blockSize;
	set_storageData(this->totalBlocks);
}
void Storage::set_storageData(long long int indBlock)
{
	//here '1' is used to initial physical memory. However, it can no other significance
	//Physical memory needs to be initialized to get address of the block.
	physicalMemory.resize(indBlock,1);			
	//free pool will store the address of the physical memory blocks
	freePool.resize(indBlock);					

	int index = 0;
	for(int i=0;i<physicalMemory.size();i++)
	{
		freePool[index] = &physicalMemory[i];
		index += 1;
	}
}
void Storage::getStorageDetail()
{
	//this piece of the code is intentionally commented for better console view of output, to know the actual memory address, 
	//one can uncomment this to see all details
	/*
	cout << endl;
	cout << "Total available physical Memory" << endl;
	for (auto it=physicalMemory.begin();it!=physicalMemory.end();++it)
		cout << *it<<" ";

	cout << endl;

	cout << "Current free pool situation" << endl;
	for (auto it = freePool.begin(); it != freePool.end(); ++it)
		cout << *it << " ";
	cout << endl;
	*/


	cout << endl <<"Total physical memory blocks size : " << physicalMemory.size() << endl;
	cout << "Total available block size : " << freePool.size() << endl;
	cout << "Current iNode (File dictionary) details" << endl;
	for (auto it = iNode.begin(); it != iNode.end(); ++it)
		cout <<"File Name --> " << it->first << " " <<"  File Structure Address -->" << it->second << endl;

	cout << endl;
}
void Storage::addFile(string fileName, long long int size)
{
	cout << "Initializing the file creation process" << endl;

	//checking for the available capacity
	if (size > this->storageCapacity)
	{
		cout << "[Insufficient Memory Error] : The file size is more than the available memmory size" << endl;
		return;
	}
	//Computing requied blocks for file
	long long int requiredFileBlocks = 0;
	if (size % this->blockSize != 0)
		requiredFileBlocks = 1;
	requiredFileBlocks += size / this->blockSize;
	// checking for available blocks
	if (requiredFileBlocks > this->totalBlocks)
	{
		cout << "[Insufficient Memory Blocks] : Free blocks not available to store file" << endl;
		return;
	}

	//Now populate the iNode and fileInfo structure
	populate_iNode(fileName, size, requiredFileBlocks);

	storeFileData(fileName);
}
void Storage::populate_iNode(string fileName, long long int size, long long int fileBlockSize)
{
	
	struct FileAddressInfo *fileDetail = NULL;
	fileDetail = new FileAddressInfo;

	fileDetail->fileSize = size;
	fileDetail->fileBlockSize = fileBlockSize;
	//assigning the key-->filename and value->structure of the file
	iNode[fileName] = fileDetail;			
	cout << "printing file size from the iNode "<<iNode[fileName]->fileSize;
}
void Storage::storeFileData(string fileName)
{
	struct MemoryBlock* head = NULL;
	struct MemoryBlock* tail = NULL;
	head = new MemoryBlock;
	tail = head;
	struct FileAddressInfo*fileDetail=iNode[fileName];

	long long int requiredFileBlocks = fileDetail->fileBlockSize;
	this->storageCapacity = this->storageCapacity - fileDetail->fileSize;;
	this->totalBlocks -= requiredFileBlocks;
	while (requiredFileBlocks--)
	{
		int* addr = freePool.back();
		freePool.pop_back();
		tail->next = new MemoryBlock;
		tail->next->data_address = addr;
		tail = tail->next;
	}
	MemoryBlock* tmp = head;
	head = head->next;
	delete tmp;
	fileDetail->start = head;
}
void Storage::retrieveFileData(string fileName)
{
	auto it = iNode.find(fileName);
	if (it == iNode.end())
	{
		cout << "[Error] : File does not exist in the Memory" << endl;
		return;
	}

	struct FileAddressInfo* structPointer = NULL;
	structPointer = iNode[fileName];
	MemoryBlock*head = structPointer->start;
	cout << endl << endl;
	cout << "printing address of the file" << endl;
	while (head != NULL)
	{
		cout << head->data_address << " ";
		head = head->next;
	}
	cout << endl << endl;
}
//deleting file from the storage
void Storage::deleteFile(string fileName)		
{
	auto it = iNode.find(fileName);
	if (it == iNode.end())
	{
		cout << "[Error]: File does not exist in the Memory" << endl;
		return;
	}
	struct FileAddressInfo* structPointer = NULL;
	structPointer = iNode[fileName];
	MemoryBlock* head = structPointer->start;
	long long int blockRecord = 0;
	while (head != NULL)
	{
		int* addr = head->data_address;
		this->freePool.push_back(addr);
		MemoryBlock* tmp = head;
		head = head->next;
		blockRecord++;
		delete tmp;
	}
	this->totalBlocks += blockRecord;
	this->storageCapacity += structPointer->fileSize;
	delete structPointer;
	iNode.erase(it);
}