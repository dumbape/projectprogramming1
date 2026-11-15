#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
const int MAX = 35;
const float RATE = 14.00;
const float BAND_1 =1400;
const float BAND_2 =700;
const float BAND_3 =180;

/*  
    the arrays here are initialized with {} here to prevent the empty elements from being field with garbage values.
    Instead, they are filled for 0's which will make it much easier for us to insert a value.
*/ 


void line(int i);
void addrecord(string (&id)[MAX],string (&name)[MAX],char (&block)[MAX],int (&nights)[MAX]);
void displaymenu();
void recordtable(string (id)[MAX],string (name)[MAX],char (block)[MAX],int (nights)[MAX]);



int main(){
    string id[MAX] = {}; 
    string name[MAX] = {};
    char code[MAX] = {};
    int qty[MAX] = {};
    
//9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9 testing values to check whether capcity check works or not
    displaymenu();
    addrecord(id,name,code,qty);
    recordtable(id,name,code,qty);
}

/*
below here are functions
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/*  
    function to print out line borders (too lazy to repeatedly write the same line function over and over again)
    the programmer can insert the width of the lines so that it will fit whatever need they have.
*/ 
void line(int i){
        cout << setfill('-') << setw(i) << "\n"
        << setfill(' ');
}

void addrecord(string (&id)[MAX],string (&name)[MAX],char (&block)[MAX],int (&nights)[MAX]){
    /*
    This block of code under here is to fill move the input of the program to an empty array element to prevent accidentally overwriting previous 
    elements that have been written. How it works is it will run a loop where arraycounter would add up (to move from one element to the next) until it finds an element that is blank
    ("" for string,''for char, 0 for int). the loop will only stop where the index contains an empty element and the value of that index is stored in arraycounter. any corrosponding
    value that is to be added will be stored at the empty index value stored in arraycounter and prevents overwriting old data.

    However, this operation is only to be done once as doing it multiple times for a single line of student data is redundant because there is no way to input the data of each column seperately from each other
    */
    int arraycounter = 0;
    string tempstr;
    char tempchar;
    float tempfloat;
    //checking whether the array has already achieved max capacity
    //if true then it will exit this function with a message
    if (nights[MAX-1] != 0){
        cout << "\nFULL CAPACITY\n"; 
        return;
    }
    //checking free spaces
    while (nights[arraycounter] != 0)
        arraycounter++;



    /*
    The blocks of code below here are to input new data with data validation intergrated within it.
    */
    cout << "\nPlease insert the student ID: ";
    cin >> tempstr;
    id[arraycounter] = tempstr;

    cout << "Please insert the student name: ";
    getline(cin>> ws,tempstr);
    name[arraycounter] = tempstr;

    do{
        cout << "Please insert the apartment block (A-E, write in capital letters): ";
        cin >> tempchar;
        if (tempchar <= 'E' && tempchar >= 'A')
            break;
        cin.ignore(100,'\n');
        cout << "Try again. ";
    } while (tempchar > 'E' || tempchar < 'A');
    block[arraycounter] = tempchar;

    do{
    //validation
        cin.clear(); 
        cin.ignore(100000, '\n');
        cout << "Please insert the nights stayed: ";
        cin >> tempfloat;
        if (cin.good())
            break;
        cout << "Try again. ";
    }while (cin.fail());
    nights[arraycounter] = tempfloat;

}
void displaymenu(){

    string menuarray[6] = {
        "ADD A RECORD",
        "DISPLAY ALL RECORDS",
        "SEARCH BY STUDENT ID",
        "SUMMARY REPORT",
        "CLASSIFICATION REPORT",
        "EXIT"
    };
    line(30);
    cout << "HOSTEL ROOM BOOKING SYSTEM" << endl;
    line(30);   
    for(int i=0;i<6; i++){
        cout << setw(3) << left << i+1 << "." << menuarray[i] << "\n";
    }
    line(30);
}

void recordtable(string (id)[MAX],string (name)[MAX],char (block)[MAX],int (nights)[MAX]){
    int recordno = 0;
    line(86);
    cout << endl;
    cout << left << setw(5) << "NO" << setw(15) << "STUDENT ID"<< setw(30) << "STUDENT NAME" << setw(5) << "BLOCK"
    << right << setw(15) << "TOTAL NIGHTS" << setw(15) << "AMOUNT (RM)"<< endl;
    line(86);
    while (nights[recordno] != 0){
        cout << left << fixed << setprecision(2) << setw(4) << recordno+1 << setw(15) << id[recordno] << setw(30) << name[recordno] << setw(5) << block[recordno] 
        << right << setw(15) << nights[recordno] << setw(15) << nights[recordno] * RATE
        << endl;
        recordno++;
    }
    line(86);
    cout << endl;
}
