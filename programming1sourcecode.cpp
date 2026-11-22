#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
const int MAX = 35;
const float RATE = 14.00;
const float BAND_1 = 1400;
const float BAND_2 = 700;
const float BAND_3 = 180;

/*
    the arrays here are initialized with {} here to prevent the empty elements from being field with garbage values.
    Instead, they are filled for 0's which will make it much easier for us to insert a value.
*/


void line(int i);
/*
    I added count to addrecord function because the program needs to know how many student records have already been added.
    I'm passing it by reference so that when a new record is saved, the updated number will also be available in main().
*/
void addrecord(string(&id)[MAX], string(&name)[MAX], char(&block)[MAX], int(&nights)[MAX], int &count);
void displaymenu();
void recordtable(string(id)[MAX], string(name)[MAX], char (block)[MAX], int (nights)[MAX]);
/*
    These are the two functions I'm adding for searching student records and displaying all the records.
    I'm keeping them separate so that each function can handle its own job when main() calls it.
*/
int searchstudent(const string id[], int count, string searchID);
void studentinfo(const string id[], const string name[], const char code[],
    const int qty[], int count);



int main() {
        string id[MAX] = {};
        string name[MAX] = {};
        char code[MAX] = {};
        int qty[MAX] = {};
        int count = 0;

        addrecord(id, name, code, qty, count);
        addrecord(id, name, code, qty, count);

        cout << "\nDISPLAY ALL RECORDS\n";
        studentinfo(id, name, code, qty, count);

        string searchID;
        cout << "\nEnter a student ID to search: ";
        cin >> searchID;

        int index = searchstudent(id, count, searchID);

        if (index == -1)
            cout << "Student not found.\n";
        else
            cout << "Student found at index " << index << ".\n";

        return 0;
    }


/*
below here are functions
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

/*
    function to print out line borders (too lazy to repeatedly write the same line function over and over again)
    the programmer can insert the width of the lines so that it will fit whatever need they have.
*/
void line(int i) {
    cout << setfill('-') << setw(i) << "\n"
        << setfill(' ');
}

void addrecord(string(&id)[MAX], string(&name)[MAX], char(&block)[MAX], int(&nights)[MAX], int &count) {
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
    int tempint;
    //checking whether the array has already achieved max capacity
    //if true then it will exit this function with a message
    if (id[MAX - 1] != "") {
        cout << "\nFULL CAPACITY\n";
        return;
    }
    //checking free spaces
    while (id[arraycounter] != "")
        arraycounter++;



    /*
    The blocks of code below here are to input new data with data validation intergrated within it.
    */
    cout << "\nPlease insert the student ID: ";
    cin >> tempstr;
    id[arraycounter] = tempstr;

    cout << "Please insert the student name: ";
    getline(cin >> ws, tempstr);
    name[arraycounter] = tempstr;

    do {
        cout << "Please insert the apartment block (A-E, write in capital letters): ";
        cin >> tempchar;
        if (tempchar > 'E' || tempchar < 'A') {
            cin.ignore(100000, '\n');
            cout << "Try again. ";
        }
    } while (tempchar > 'E' || tempchar < 'A');
    block[arraycounter] = tempchar;

    /*
    I changed the nights stayed validation because the original code only checked whether the input failed.
    The assignment also requires the number of nights to be a non-negative integer, so I added checks for negative numbers and extra characters.
    I kept the original do-while loop so the user can keep trying until a valid number is entered.
    */
    bool validNights;

    do {
        //validation
        cout << "Please insert the nights stayed: ";
        cin >> tempint;

        validNights = !cin.fail();

        if (validNights) {
            if (tempint < 0 || cin.peek() != '\n')
                validNights = false;
        }

        if (!validNights) {
            cout << "Try again. ";
            cin.clear();
        }

        cin.ignore(100000, '\n');

    } while (!validNights);

    nights[arraycounter] = tempint;
    /*
    I added this so the program keeps track of how many student records have been saved.
    Adam's arraycounter still finds the next empty position, while count tells the other functions how many records are stored.
    */
    count = count + 1;

}
void displaymenu() {

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
    for (int i = 0;i < 6; i++) {
        cout << setw(3) << left << i + 1 << "." << menuarray[i] << "\n";
    }
    line(30);
}

/*
    I noticed that recordtable() and studentinfo() both display the student records.
    Since studentinfo() already handles this and uses count to avoid going through empty array positions,
    I don't think we need to call recordtable() anymore.
    I've left Adam's original function here for now so we can decide together whether to remove it later.
*/
void recordtable(string(id)[MAX], string(name)[MAX], char (block)[MAX], int (nights)[MAX]) {
    int recordno = 0;
    line(86);
    cout << endl;
    cout << left << setw(5) << "NO" << setw(15) << "STUDENT ID" << setw(30) << "STUDENT NAME" << setw(5) << "BLOCK" << right << setw(15) << "TOTAL NIGHTS" << setw(15) << "AMOUNT (RM)" << endl;
    line(86);
    while (id[recordno] != "" || recordno < MAX) {
        cout << left << fixed << setprecision(2) << setw(5) << recordno + 1 << setw(15) << id[recordno] << setw(30) << name[recordno] << setw(5) << block[recordno] << right << setw(15) << nights[recordno] << setw(15) << nights[recordno] * RATE
            << endl;
        recordno++;
    }
    line(86);
    cout << endl;
}

/*
    This function goes through the student IDs one by one to find the student we're looking for.
    If it find a matching ID, it returns its position in the array so main() knows which student's information to display.
    If none of the IDs match, it returns -1 to let main() know that the student wasn't found.
*/
int searchstudent(const string id[], int count, string searchID)
{
    int i = 0;

    while (i < count)
    {
        if (id[i] == searchID)
        {
            return i;
        }

        i = i + 1;
    }

    return -1;
}

/*
    This function displays all the student records that have been added so far.
    I use count to make sure the program only goes through the records that actually exist instead of checking all 35 spaces in the arrays.
    I also calculate the booking fee for each student using their number of nights and the rate per night.
*/
void studentinfo(const string id[], const string name[], const char code[],
    const int qty[], int count)
{
    if (count == 0)
    {
        cout << "No records found" << endl;
        return;
    }

    cout << "\nSTUDENT BOOKING RECORDS\n";
    cout << left << setw(15) << "STUDENT ID"
        << setw(30) << "STUDENT NAME"
        << setw(10) << "BLOCK"
        << setw(15) << "NIGHTS STAYED"
        << right << setw(15) << "FEE (RM)" << endl;

    float fee;
    int i = 0;

    while (i < count)
    {
        fee = qty[i] * RATE;

        cout << left << setw(15) << id[i]
            << setw(30) << name[i]
            << setw(10) << code[i]
            << setw(15) << qty[i]
            << right << fixed << setprecision(2) << setw(15) << fee << endl;

        i = i + 1;
    }
}
