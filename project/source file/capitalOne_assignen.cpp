// capitalOne_assignen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"storage.h"
#include"inputHandler.h"
#define MAX_INPUT_LENGTH 256          //maximum size of the input in string

int main()
{
    //Inputs
    char systemStorageString[MAX_INPUT_LENGTH]; // input would be in string Ex: 1Mb or 1 mb, 1 GB etc
    long long int systemStorage = 0; // 
    char indvidualBlockSizeString[MAX_INPUT_LENGTH];
    long long int indvidualBlockSize = 0;

    cout << "**********WELCOME***********" << endl;

    //storage main input
    cout << "Enter system storage size with unit Ex: 1Mb or 1 mb, 1 GB etc" << endl;
    cin.getline(systemStorageString, MAX_INPUT_LENGTH);

    //handling input
    if (!InputAdapter::validateInput(strlen(systemStorageString)))
        return -1;
    systemStorage = InputAdapter::getConvertedMemoryFromString(systemStorageString);
    cout << "After conversion: system size in kb " << systemStorage << endl;


    //storage block input
    cout << "Enter the individual block with unit Ex: 1Mb or 1 mb, 1 GB etc" << endl;
    cin.getline(indvidualBlockSizeString, MAX_INPUT_LENGTH);

    //handling input
    if (!InputAdapter::validateInput(strlen(indvidualBlockSizeString)))
        return -1;
    indvidualBlockSize = InputAdapter::getConvertedMemoryFromString(indvidualBlockSizeString);
    cout << "After conversion: system size in kb " << indvidualBlockSize << endl;

    cout << endl << endl; // For better formatting
    
    Storage storageManager = Storage(systemStorage, indvidualBlockSize);

    cout << "Current memory details of storage system" << endl;
    storageManager.getStorageDetail();

    //This is the input variable that has to be used to do operation in switch
    int inputChoice = 0;      

    do
    {
        cout << endl;
        cout << "Menu -------------------------" << endl;
        cout << "Press 0 to exit from the File System Manager" << endl;
        cout << "Press 1 to store new file in the system" << endl;
        cout << "Press 2 to retrieve existing file from the system" << endl;
        cout << "Press 3 to delete existing file from the system" << endl << endl;

        cout << "Enter your input" << endl;
        cin >> inputChoice;

        switch (inputChoice)
        {
        case 1:
        {            
            //add file
            //input the file name and the size of the file
            string fileName = "";
            long long int size = 0;
            cout << "Enter the file name" << endl;
            cin >> fileName;
            if (!InputAdapter::validateInput(fileName.size()))
                break;
            cout << "Enter the size of the file value and unit" << endl;
            char sizeString[MAX_INPUT_LENGTH];

            //handling input
            cin.ignore();
            cin.getline(sizeString, MAX_INPUT_LENGTH);
            if (InputAdapter::validateInput(strlen(sizeString)))
            {
                size = InputAdapter::getConvertedMemoryFromString(sizeString);
                cout << "After conversion: file size in kb " << size << endl;
                storageManager.addFile(fileName, size);
            }
            break;
        }
        case 2:
        {
            //retrieve file
            string fileName = "";
            cout << "Enter the file name" << endl;
            cin >> fileName;
            if (InputAdapter::validateInput(fileName.size()))
                storageManager.retrieveFileData(fileName);
            break;
        }
        case 3:
        {
            //delete file
            string fileName = "";
            cout << "Enter the file name" << endl;
            cin >> fileName;
            if (InputAdapter::validateInput(fileName.size()))
                storageManager.deleteFile(fileName);
            break;
        }
        default:
            cout << "Input Exception: Invalid input size";
            break;
        }
        //Printing current system memory details
        storageManager.getStorageDetail();
        
    } while (inputChoice);
    
                    
}

