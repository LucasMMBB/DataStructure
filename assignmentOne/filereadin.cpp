
/*
    ECE 370
    Assignment One
    Professor: Dongming Zhao
    Author: Maoxu Liu
    University of Michigan-Dearborn
*/
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

struct Info
{
     char firstname [30];
     char lastname [30];
     long SSN;
     int age;
     char address [70];
}list[30],foundInfo[30];


int main () {
    int arr_num = 0;
    int i,j;
    char cont = 'y';
    bool done = 0;

//read in file;
  string line;
  ifstream inFile ("a1.txt");
  if (inFile.is_open())
  {


    while (!inFile.eof())
    {
          inFile.getline(list[arr_num].firstname,30,',');
          inFile.getline(list[arr_num].lastname,30);
          inFile >> list[arr_num].SSN;
          inFile >> list[arr_num].age;
          inFile.ignore(1000, '\n');
          inFile.getline(list[arr_num].address, 70, '\n');
          inFile.ignore(1000, '\n');
          arr_num++;
    }
    inFile.close();

cout<<"\n\n THE TOTAL NUMBER OF PEOPLE IN FILE IS "<<arr_num<<endl;
  }

  else cout << "Unable to open file";



// sorting in SSN ascending orden
    for(i=0;i<arr_num;i++)
    {
        for(j=i+1;j<arr_num;j++)
        {
            if(list[j].SSN<list[i].SSN)
            {
                Info temp;
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    for (int n=0;n<arr_num;n++){
            cout<<"THE INFO OF is as following"<<endl;
            cout<<list[n].firstname;
            cout<<", ";
            cout<<list[n].lastname<<endl;
            cout<<list[n].SSN<<endl;
            cout<<list[n].age<<endl;
            cout<<list[n].address<<endl;
    }





// Ask user whether to add a person or not;
    cout << endl;
        while(done == 0)
            {
                cout <<"Would you like to add another entry? [y/n]" << endl;
                cin >> cont;
                if(cont == 'y')
                {
                    cout << "What is the first name of the person?" << endl;
                    cin >> list[arr_num].firstname;
                    cout << "What is the last name of the person?" << endl;
                    cin >> list[arr_num].lastname;
                    cout << "What is the SSN  of the person?" << endl;
                    cin >> list[arr_num].SSN;
                    cout << "What is the age of the person?" << endl;
                    cin >> list[arr_num].age;
                    cout << "What is the address of the person?" << endl;
                    scanf(" %[^\n]s",list[arr_num].address);
                    cout <<endl<< "Entry added!" << endl;
                    arr_num ++;
                }
                else if(cont == 'n')
                {
                    done = 1;
                    break;
                    cout << endl;
                }
                else
                {
                    cout << "Please enter 'y' or 'n'" << endl;

                }

                cout<<"Total number of people after addition is "<<arr_num<<endl;
            }



// Search person by last name;
    int foundNum = 0;
    done = 0;
    char lastNameSearch[30];

    while(done == 0)
    {
        cout << endl;
        cout << "Would you like to search for a person by last name [y/n]" << endl;
        cin >> cont;
        if(cont == 'y')
        {
            cout <<"Please enter the persons last name" << endl;
            cin >> lastNameSearch;
            for(i=0;i<arr_num;i++)
            {
                if(strcmp(lastNameSearch,list[i].lastname) == 0)
                {
                    foundInfo[foundNum] = list[i];
                    cout<<"THE searched person INFO OF is as following"<<endl;
                    cout<<list[i].firstname;
                    cout<<", ";
                    cout<<list[i].lastname<<endl;
                    cout<<list[i].SSN<<endl;
                    cout<<list[i].age<<endl;
                    cout<<list[i].address<<endl;
                    foundNum++;
                }
            }
                if(foundNum == 0)
                    cout << "Not found"<< endl;
        }

        else if(cont == 'n')
        {
            done = 1;
            break;
        }
        else
        {
            cout << "Please enter y or n" << endl;
        }
    }



//Print all searched information
    cout<<"ALL SEARCHED PEOPLE ARE AS FOLLOWED";
    for(i=0;i<foundNum;i++)
    {
                    cout<<foundInfo[i].firstname;
                    cout<<", ";
                    cout<<foundInfo[i].lastname<<endl;
                    cout<<foundInfo[i].SSN<<endl;
                    cout<<foundInfo[i].age<<endl;
                    cout<<foundInfo[i].address<<endl;
                    cout<<"\n\n";
    }
  return 0;
}//main program ends

