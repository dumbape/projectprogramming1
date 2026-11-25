#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
const int MAX = 35;
const float RATE = 14.00f;
const float BAND_1 = 1400.00f;
const float BAND_2 = 700.00f;
const float BAND_3 = 180.00f;

/*
    the arrays here are initialized with {} here to prevent the empty elements from being field with garbage values.
    Instead, they are filled for 0's which will make it much easier for us to insert a value.
*/


void line(int i);
/*readded capitalizer*/
string capitalizer(string tempstr);
/*
    I added count to addrecord function because the program needs to know how many student records have already been added.
    I'm passing it by reference so that when a new record is saved, the updated number will also be d in main().
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
void sumreport(const string id[], const string name[],
    const int qty[], int count);
void classreport(const string id[], const string name[],
    const int qty[], int count);



int main() {
        string id[MAX] = {};
        string name[MAX] = {};
        char code[MAX] = {};
        int qty[MAX] = {};
        int count = 0;
        int menuvalue = 0;
    
        while (menuvalue!= 6){
            string searchID;
            bool validoption;
            displaymenu();
            do {
                //validation
                cout << "Please select your menu options: ";
                cin >> menuvalue;

                validoption = !cin.fail();

                if (validoption) {
                    if (menuvalue < 0 || menuvalue > 6 || cin.peek() != '\n')
                        validoption = false;
                }

                if (!validoption) {
                    cout << "Try again. ";
                    cin.clear();
                }

                cin.ignore(10000, '\n');

            } while (!validoption);
            switch (menuvalue)
            {
            default:
                break;
            case 1:
                addrecord(id, name, code, qty, count);
                break;
           case 2:
                cout << "\nDISPLAY ALL RECORDS\n\n";
                studentinfo(id, name, code, qty, count);
                break;
           case 3:{
                cout << "\nEnter a student ID to search: ";
                cin >> searchID;
                searchID = capitalizer(searchID);
                int index = searchstudent(id, count, searchID);

                if (index == -1)
                cout << "Student not found.\n\n";
                    else{
                cout << "STUDENT FOUND AT INDEX " << index+1 << ".\n";
                line(90);
                cout << left << setw(4) << "NO."
                << left << setw(15) << "STUDENT ID"
                << setw(30) << "STUDENT NAME"
                << setw(10) << "BLOCK"
                << setw(15) << "NIGHTS STAYED"
                << right << setw(15) << "FEE (RM)" << endl;
                 line(90);
                cout << left << setw(4) << index+1
                << left << setw(15) << id[index]
                << setw(30) << name[index]
                << setw(10) << code[index]
                << setw(15) << qty[index]
                << right << fixed << setprecision(2) << setw(15) << qty[index] * RATE << endl;
                line(90);
                cout << "\n";
                }
               
                break;
           }

           case 4:
                sumreport(id, name, qty, count);
                break;
           case 5:
                classreport(id, name, qty, count);
                break;
            

            }
        }
        cout << "The program has ended. Goodbye and have a good day\n";
        return 0;
    }


/*
below here are functions
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
string capitalizer(string tempstr){
    for (int i = 0; i < tempstr.length(); i++) {
    if (tempstr[i] >= 'a' && tempstr[i] <= 'z')
        tempstr[i] = tempstr[i] - 32;
    }
    return tempstr;
}


/*
    function to print out line borders (too lazy to repeatedly write the same line function over and over again)
    the programmer can insert the width of the lines so that it will fit whatever need they have.
*/
void line(int i) {

    cout  << setw(i) << setfill('-') << ""<<"\n" << setfill(' ');
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
        cout << "\nFULL CAPACITY\n\n";
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
    tempstr = capitalizer(tempstr);
    id[arraycounter] = tempstr;

    cout << "Please insert the student name: ";
    getline(cin >> ws, tempstr);
    tempstr = capitalizer(tempstr);
    name[arraycounter] = tempstr;

    do {
        cout << "Please insert the apartment block(A-E): ";
        cin >> tempchar;
    if (tempchar >= 'a' && tempchar <= 'z')
        tempchar = tempchar - 32;
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
    cout << "Record has been inserted\n\n";

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

    cout << "\nSTUDENT BOOKING RECORDS\n\n";
    line(90);
    cout << left << setw(4) << "NO."
        << left << setw(15) << "STUDENT ID"
        << setw(30) << "STUDENT NAME"
        << setw(10) << "BLOCK"
        << setw(15) << "NIGHTS STAYED"
        << right << setw(15) << "FEE (RM)" << endl;
    line(90);
    float fee;
    int i = 0;

    while (i < count)
    {
        fee = qty[i] * RATE;
        cout<< left << setw(4) << i+1
            << left << setw(15) << id[i]
            << setw(30) << name[i]
            << setw(10) << code[i]
            << setw(15) << qty[i]
            << right << fixed << setprecision(2) << setw(15) << fee << endl;

        i = i + 1;
    }
    line(90);
    cout << "\n";

}

/*
    This function generates a summary report of the student booking records.
    I use count to make sure the function only processes records that have
    actually been added. It calculates the total and average nights stayed,
    and identifies the student records with the highest and lowest nights.
*/
void sumreport(const string id[], const string name[], const int qty[], int count) {
    if (count == 0) {
        cout << "\nNo records found for summary report.\n\n";
        return;
    }

    float totalFee = 0.0f;
    int highestIdx = 0;
    int lowestIdx = 0;
    float highestFee = qty[0] * RATE;
    float lowestFee = qty[0] * RATE;

    for (int i = 0; i < count; i++) {
        float fee = qty[i] * RATE;
        totalFee += fee;

        if (fee > highestFee) {
            highestFee = fee;
            highestIdx = i;
        }
        if (fee < lowestFee) {
            lowestFee = fee;
            lowestIdx = i;
        }
    }

    float avgFee = totalFee / count;

    cout << "\nSUMMARY REPORT\n";
    cout << left << setw(24) << "Number of bookings" << ": " << count << endl;
    cout << left << setw(24) << "Total Fee (RM)" << ": " << fixed << setprecision(2) << totalFee << endl;
    cout << left << setw(24) << "Average Fee (RM)" << ": " << fixed << setprecision(2) << avgFee << endl;
    cout << endl;
    cout << left << setw(10) << "Highest" << ": " << name[highestIdx]
         << " (" << qty[highestIdx] << " -> " << fixed << setprecision(2) << highestFee << ")" << endl;
    cout << left << setw(10) << "Lowest" << ": " << name[lowestIdx]
         << " (" << qty[lowestIdx] << " -> " << fixed << setprecision(2) << lowestFee << ")" << endl;
    cout << endl;
}




/*
    I changed the previous classreport() function to follow our current
    program structure. Instead of using global arrays, I now pass the
    required arrays as parameters. I also added count so the function
    only processes records that have actually been added.
*/
void classreport(const string id[], const string name[],
    const int qty[], int count)
{
    if (count == 0)
    {
        cout << "\nNo records found.\n\n";
        return;
    }

    float fee;
    string classification;
    int num = 1;

    cout << "\nCLASSIFICATION REPORT\n";
    line(90);

    cout << left << setw(4) << "NO"
        << setw(15) << "STUDENT ID"
        << setw(30) << "STUDENT NAME"
        << right << setw(15) << "FEE (RM)"
        << "  " << left << setw(20) << "CLASSIFICATION"
        << endl;

    line(90);

    for (int i = 0; i < count; i++)
    {
        fee = qty[i] * RATE;

        if (fee >= BAND_1)
        {
            classification = "Full Semester";
        }
        else if (fee >= BAND_2)
        {
            classification = "Half Semester";
        }
        else if (fee >= BAND_3)
        {
            classification = "Short Stay";
        }
        else
        {
            classification = "Transit";
        }

        cout << left << setw(4) << num
            << setw(15) << id[i]
            << setw(30) << name[i]
            << right << setw(15) << fixed << setprecision(2) << fee
            << "  " << left << setw(20) << classification << endl;

        num++;
    }

    line(90);
}
