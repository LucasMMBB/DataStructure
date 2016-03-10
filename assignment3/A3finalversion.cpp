//Author: MAOXU LIU
//ECE 370 ASSIGNMENT 3.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct data
{
    string name;
    int score;
    data* next;
};


/*
Print out all node in the linked list right now.
*/
void visitData(data* myData)
{
    while(myData != NULL)
    {
        cout << myData->name << " " << myData->score << endl;
        myData = myData->next;
    }
}


/*
Insert one node to the linked list. If there is an existing one same as what we will insert,
Then delete the existing one and insert new one. The order of insertion is based on alphabetical
order of given name.
*/
void insertData(data** myData, string input)
{
    int flag, score;
    string name;

    struct data* tempPtr;
    struct data* tempData = new data;
    tempData->next = NULL;

    istringstream convert(input.substr(input.find(' ') + 1, input.length()));
    name = input.substr(0, input.find(' '));
    convert >> score;

    tempData->name = name;
    tempData->score = score;
    tempData->next = NULL;

    if(*myData != NULL)                                         
    {
        tempPtr = *myData;                                     
        flag = 0;

        if(tempPtr->name == name)                               
            tempPtr->score = score;
        else
        {
            while(flag == 0)
            {
                if(name < (*myData)->name)                      
                {
                    tempData->next = *myData;                   
                    *myData = tempData;                         
                    flag = 1;
                }
                else if(tempPtr->next != NULL)                  
                {
                    if(name < tempPtr->next->name)              
                    {
                        tempData->next = tempPtr->next;         
                        tempPtr->next = tempData;               
                        flag = 1;
                    }
                    else if(tempPtr->next->name == name)        
                    {
                        tempPtr->next->score = score;           
                        flag = 1;                               
                    }

                    tempPtr = tempPtr->next;                    

                }
                else                                            
                {
                    tempPtr->next = tempData;                   
                    flag = 1;                                  
                }
            }
        }
    }
    else
        *myData = tempData;                                      
}


/*
Given a node, delete if there is.
If the given node is not existing , then print "INVALID DELETE FOR THAT NODE"
*/
void deleteData(data** myData, string input)
{
    int flag;
    struct data* tempPtr = *myData;
    struct data* deletePtr;

    if(tempPtr->name == input)
    {
        cout << input << endl;
        *myData = (*myData)->next;
        delete tempPtr;
    }
    else
    {
        flag = 0;
        while(tempPtr->next != NULL)
        {
            if(tempPtr->next->name == input)
            {
                deletePtr = tempPtr->next;
                tempPtr->next = tempPtr->next->next;
                delete deletePtr;
                cout << input << endl;
                flag = 1;
            }
            tempPtr = tempPtr->next;
        }
        if(flag == 0)
            cout << "INVALID DELETE FOR " << input << endl;
    }
}

/*
Search the given node and print it if there is.
If not, print "invalid search"
*/
void dataSearch(data* myData, string input)
{
    int flag;
    struct data* tempPtr;

    tempPtr = myData;

    if(tempPtr->name == input)
        cout << tempPtr->name << " " << tempPtr->score << endl;
    else
    {
        flag = 0;

        while((tempPtr->name != input) && (tempPtr->next != NULL))
        {
            tempPtr = tempPtr->next;

            if(tempPtr->name == input)
            {
                cout << tempPtr->name << " " << tempPtr->score << endl;
                flag = 1;
            }
        }
        if(flag == 0)
            cout << "INVALID SEARCH FOR " << input << endl;
    }
}


/*
sort the linked list in ascending order
*/
void sortascData(data** myData)
{
    int flag;
    struct data *dataPtr = *myData;
    struct data *tempPtr, *tempHeader;
    tempHeader = dataPtr;

    flag = 1;                                                               
    while(flag != 0)                                                        
    {
        flag = 0;                                                           

        dataPtr = tempHeader;                                               
        while((dataPtr->next != NULL) && (flag == 0))                       
        {
            if(dataPtr->score > dataPtr->next->score)                       
            {                                                               
                tempHeader = dataPtr->next;                                 
                dataPtr->next = dataPtr->next->next;
                tempHeader->next = dataPtr;
                flag = 1;                                                  
            }
            if(dataPtr->next->next != NULL)                                 
                if(dataPtr->next->score > dataPtr->next->next->score)       
                {                                                           
                    tempPtr = dataPtr->next->next;
                    dataPtr->next->next = dataPtr->next->next->next;
                    tempPtr->next = dataPtr->next;
                    dataPtr->next = tempPtr;
                    flag = 1;                                               
                }

            dataPtr = dataPtr->next;                                        
        }
    }
    *myData = tempHeader;
}

int main()
{
    ifstream myFile;
    myFile.open("a3.txt");
    string input;

    struct data* myData;
    myData = NULL;

    if(myFile.good())
    {
        getline(myFile, input);

        while(!myFile.eof())
        {
            if(input == "%INSERT")
            {
                cout << "%INSERT" << endl;

                getline(myFile, input);

                while(input[0] != '%')
                {
                    insertData(&myData, input);
                    getline(myFile, input);
                }
                cout << endl;
            }
            else if(input == "%DELETE")
            {
                cout << "%DELETE" << endl;

                getline(myFile, input);

                while(input[0] != '%')
                {
                    deleteData(&myData, input);
                    getline(myFile, input);
                }
                cout << endl;
            }
            else if(input == "%VISIT")
            {
                cout << "%VISIT" << endl;

                visitData(myData);
                getline(myFile, input);
                cout << endl;
            }
            else if(input == "%SORTASC")
            {
                cout << "%SORTASC" << endl;

                sortascData(&myData);
                getline(myFile, input);
                cout << endl;
            }
            else if(input == "%SEARCH")
            {
                cout << "%SEARCH" << endl;

                getline(myFile, input);

                while(input[0] != '%')
                {
                    dataSearch(myData, input);
                    getline(myFile, input);
                }
                cout << endl;
            }
            else
            {
                cout << "Invalid entry" << endl;
                getline(myFile, input);
                cout << endl;
            }
            if(input == "%END")
            {
                cout << "%END" << endl;
                getline(myFile, input);
                cout << endl;
            }
        }
    }
    else
        cout << "Error! Can not open/find file." << endl;

    myFile.close();
    return 0;
}
