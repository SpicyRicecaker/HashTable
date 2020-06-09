/*
  Author: Andy Li
  Date: 06/07/2020
  StudentList: A program that can store the first name, last name, id, and gpa of multiple students using hash tables. It features 3 main functions: the add, delete, and print functions, which can add a new student to the list, remove a student from the list based on their ID, and print out the list of students, respectively.
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib> // This is used to generate random numbers

using namespace std;

//A student needs a first name, last name, id, gpa, and the next student in the linked list, for collisions
struct Student{
    char fNm[999];
    char lNm[999];
    char id[7];
    float gpa;
    Student* next = NULL;
};

//The add function asks the user to input student information, and inserts it into the table via hashfunction, utilizing hashing
void add(Student*** stuList, int &hashSize);
//The getRid function removes a student from the hashtable based off id, finds location by hashing
void getRid(Student*** stuList, int &hashSize);
//The print function loops through the entire hash table array and linked lists to print each student
void print(Student*** stuList, int hashSize);
//The print regular function doesn't include the arrows and commas, more like a list format
void printRegular(Student*** stuList, int hashSize);
//The generate students generates up to 1000 students at a time and stores them in the the hash table
void generateStudents(Student*** stuList, int &hashSize, char** fFN, char** fLN);
//The quit function sets running to false
void quit(bool &running);
//The get valid (x) functions are very redundant, they all process input and store into struct
//Makes sure that input is not null
void getValidFirstName(Student* &temp);
void getValidLastName(Student* &temp);
//Makes sure that id is 6 digits
void getValidId(Student* &temp);
//Makes sure that GPA is a float
void getValidGpa(Student* &temp);
//Very important function. Calls hashAlgorithm to find the place to insert new students, while also rehashing given more than 3 collisions
void hashFunction(Student* temp, Student*** stuList, int &hashSize);
//Traverses linked list to find its length
int linkedLength(Student* head);
//Adds to a linked list through the head
void linkedAdd(Student* &oldHead, Student* newHead);
//Prints the linked list with arrows by traversal
void linkedPrint(Student* head);
//Prints the linked list without arrows by traversal
void linkedPrintReg(Student* head);
//Takes in an integer and exponent and returns the result
int pow(int base, int exponent);
//Returns the absolute value of the int inputted
int abs(int a);
//Uses the hashing algorithm to turn a string of characters into a hash code
int hashAlgorithm(char* id, int hashSize);
//Turns an integer to a 6 digit id in char* form
char* intToSixId(int n);

//The add method prompts the user for the firstname, lastname, id, and gpa of a student and adds that student along into the hash table of students, making sure to validate user input.
void add(Student*** stuList, int &hashSize){
    //Allocates the student to heap memory
    Student* temp = new Student;
    //Prompting the user for the first name
    //Also validate
    getValidFirstName(temp);

    //Prompt user for last name
    //Then validate user input the same way as first name
    getValidLastName(temp);

    //Prompt user for ID of the student
    getValidId(temp);

    //Prompt user for gpa
    getValidGpa(temp);

    //Hash it in!
    hashFunction(temp, stuList, hashSize);
   
    cout << "Student added! :)" << endl;
}

//The getRid method prompts the user for an ID of a student and removes it from the studentList
void getRid(Student*** stuList, int &hashSize){
    //Prompt and validate userinput for the ID of a student
    cout << "Please enter the id of the student. :)" << endl;

    while(true){
    //Validates user inputted id
        bool allDig = true;
        char in[999];
        cin.getline(in, 999);
        cin.clear();

        int inLen = strlen(in);
        for(int a = 0; a < inLen; a++){
            if(!isdigit(in[a])){
                allDig = false;
            }
        }

        //If input is good
        if(allDig && strlen(in) == 6){
            //Run through the HASH TABLE BB
            //Set current to the beginning of the linked list that the hash algorithm resulted in
            Student** curr = &((*stuList)[hashAlgorithm(in, hashSize)]);
            Student* past = *curr;
            while(true){
                //While we're not at the end of the linked list
                if(curr!=NULL){
                    //Once we've found a match
                    if(strcmp((*curr)->id, in) == 0){
                        //Remember current's next
                        Student* currNext = (*curr)->next;
                        //delete *curr;
                        //Set current to its next
                        *curr = currNext;
                        //Set past also to its next, this accounts for root case
                        past->next = currNext;
                        cout << "Student removed! :)" << endl;
                        return;
                    }
                }else{
                    break;
                }
                //Otherwise keep traversing the list
                past = *curr;
                curr = &(((*curr)->next));
            }
            //If we've escaped while loop without returning we know that the id was not found
            cout << "That id does not exist. :o" << endl;
            return;
        }
        //Reprompt
        cout << "Please enter a six digit number. :)" << endl;
    }
}


//The print function prints the first and last name, ID, and gpa of all students in the student list
void print(Student*** stuList, int hashSize){
    bool empty = true;
    //Goes through the hash table and prints the linked list of slots that are not null
    for(int a = 0; a < hashSize; a++){
        if((*stuList)[a] != NULL){
            empty = false;
            linkedPrint((*stuList)[a]);
        }
    }
    //If we've hit nothing, table is empty
    if(empty){
        cout << "The student list is empty! ;)" << endl;
    }
}

//The quit function exits the program
void quit(bool &running){
    running = false;
    cout << "Program will now exit. CY@! ;)" << endl;
}

//The main method for student list
int main(){

    //Format output to two decimal points
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    char commandIn[999];

    bool running = true;

    //Make an array of student pointers, then make a pointer pointing to this particular array
    int hashSize = 100;
    Student** stuL = new Student*[hashSize];
    Student*** stuList = &stuL;

    //Arrays of student first and last names that will be filled by file info when RNG is called.
    char* fileFirstNames[1001];
    char** fFN = &fileFirstNames[0];
    fFN[0] = NULL;
    char* fileLastNames[1001];
    char** fLN = &fileLastNames[0];

    //Prompt and validate user for a command, then transition to the corresponding function accordingly
    cout << "Please enter a command. Type \"help\" for help. :)" << endl;
    while(running){
        //Each iteration we look for a command
        cin.getline(commandIn, 999);
        cin.clear();

        //Set everything to caps
        int commandInLen = strlen(commandIn);
        for(int a = 0; a < commandInLen; a++){
            commandIn[a] = toupper(commandIn[a]);
        }

        if(strcmp(commandIn, "ADD") == 0){
            add(stuList, hashSize);
        }else if(strcmp(commandIn, "TABLE") == 0){
            print(stuList, hashSize);
        }else if(strcmp(commandIn, "PRINT") == 0){
            printRegular(stuList, hashSize);
        }
        else if(strcmp(commandIn, "DELETE") == 0){
            getRid(stuList, hashSize);
        }
        else if(strcmp(commandIn, "QUIT") == 0){
            quit(running);
        }
        else if(strcmp(commandIn, "HELP") == 0){
            cout << "----------\n\"add\" to add a new student.\n\"delete\" to delete a student.\n\"table\" to print the student list in hash table format.\n\"print\" to print in regular format.\n\"RNG\" to generate and add a random number of students from 0-1000.\n\"quit\" to exit the program. :)\n----------" << endl;
        }else if(strcmp(commandIn, "RNG") == 0){
            generateStudents(stuList, hashSize, fFN, fLN);
        }else{
            cout << "Please enter a valid command, and type \"help\" for help. :)" << endl;
        }
    }
}

//Basically makes sure that the name is not NULL or has no spaces, stores into fNm of struct
void getValidFirstName(Student* &temp){
    cout << "Please enter the first name of the student. :)" << endl;
    while(true){
        bool noSpace = true;

        //Get the user input, store it into the vector, reset error flags, ignore the characters after the first 50
        cin.getline(temp->fNm, 999);
        cin.clear();

        //If the fullname does not equal null
        if(strlen(temp->fNm) != 0){
            //Check if there are no spaces
            int fNmLen = strlen(temp->fNm);
            for(int a = 0; a < fNmLen; a++){
                if(temp->fNm[a] == ' '){
                    noSpace = false;
                }
            }
            if(noSpace){
                //Then continue
                noSpace = true;
                break;
            }
        }

        //If input is null or has space
        cout << "The student's first name is empty, or includes spaces... :/" << endl;
    }
}

//Basically makes sure that the name is not NULL or has no spaces, stores into lNm of struct
void getValidLastName(Student* &temp){
    cout << "Please enter the last name of the student. :)" << endl;
    while(true){
        bool noSpace = true;

        cin.getline(temp->lNm, 999);
        cin.clear();

        if(strlen(temp->lNm) != 0){
            int lNmLen = strlen(temp->lNm);
            for(int a = 0; a < lNmLen; a++){
                if(temp->lNm[a] == ' '){
                    noSpace = false;
                }
            }
            if(noSpace){
                break;
            }
        }

        cout << "At least put \"Snow\" or something :o" << endl;
    }
}

//Checks to make sure that the string the user inputted is 6 digits and all digits
void getValidId(Student* &temp){
    cout << "Please enter the ID of the student. :)" << endl;

    while(true){

        bool alldigit = true;

        char in[999];

        //Get input
        cin.getline(in,999);
        cin.clear();

        //Make sure that the input is all digits
        int inLen = strlen(in);
        for(int a = 0; a < inLen; a++){
            if(!isdigit(in[a])){
                alldigit = false;
            }
        }

        //If it's also 6 characters in length then continue
        if(alldigit && strlen(in) == 6){
            strcpy(temp->id, in);
            break;
        }
        cout << "Please enter a six digit number. :/" << endl;
    }
}

//
void getValidNumber(char* numToAdd){
    cout << "Please enter the amount of random names that will be added, from 0 to 1000. :)" << endl;

    while(true){

        bool alldigit = true;

        //Get input
        cin.getline(numToAdd,999);
        cin.clear();

        //Make sure that the input is all digits
        int inLen = strlen(numToAdd);
        for(int a = 0; a < inLen; a++){
            if(!isdigit(numToAdd[a])){
                alldigit = false;
            }
        }

        //If it's also 6 characters in length then continue
        if(alldigit && strlen(numToAdd) <= 4 && strlen(numToAdd) >= 1){
            break;
        }
        cout << "Please enter a number between 0 and 1000. :/" << endl;
    }
}

//Makes sure that it's a float, also converts it into a float
void getValidGpa(Student* &temp){
    cout << "Please enter the gpa of the student. :)" << endl;

    while(true){
        char gpaIn[34];

        //Numbers that will be used to calculate number to the left and right of the decimal
        float gpaNum = 0;
        float gpaNuml = 0;
        int decInd = 0;

        //All digits and only one decimal point
        bool allDig = true;
        bool onePeriod = false;

        //Get input
        cin.getline(gpaIn, 34);
        cin.clear();

        //For each character of the input
        int gpaInLen = strlen(gpaIn);
        for(int a = 0; a < gpaInLen; a++){
            //If we've found the period for the first time
            if(gpaIn[a]=='.' && onePeriod == false){
                //Set onePeriod to true
                onePeriod = true;
                //Then check if there are numbers to the right of the decimal
                if(gpaIn[a+1]==0){
                    //If not, input is bad
                    allDig = false;
                    break;
                }
                //Otherwise, if we've stumbled across a second period, or something not a digit
            }else if(!isdigit(gpaIn[a])){
                //Input is bad
                allDig = false;
                break;
            }
        }
        //If input isn't bad
        if(allDig){
            //Convert from constant char array to float, then add to student list
            for(int a = 0; a < gpaInLen; a++){
                if(gpaIn[a]!='.'){
                    gpaNum += (gpaIn[a]-48);
                    gpaNum *= 10;
                }else{
                    gpaNum /= 10;
                    decInd = a;
                    break;
                }
            }
            for(int a = strlen(gpaIn)-1; a > decInd; a--){
                gpaNuml += (gpaIn[a]-48);
                gpaNuml /= 10;
            }
            temp->gpa = gpaNum+gpaNuml;
            break;
        }
        cout << "That gpa does not exist... :/" << endl;
    }

}

//Calls hashalgorithm to insert students where needed, resolves collisions too
void hashFunction(Student* temp, Student*** stuList, int &hashSize){
    //Hashing algorithm
    int index = hashAlgorithm(temp->id, hashSize);

    //Now we goto value at array.
    //If the spot is empty
    if((*stuList)[index] == NULL){
        //Fill up, return
        (*stuList)[index] = temp;
        return;
    }
    //Otherwise, there is a conflict.
    //If the arraysize is less than 3
    else if(linkedLength((*stuList)[index]) < 3){
        //Set current to the beginning node of the linked list
        Student** curr = &((*stuList)[index]);
        Student* past = *curr;
        while(true){
            if((*curr)!=NULL){
                //Replace any repeat IDs, by deleting first
                if(strcmp((*curr)->id, temp->id) == 0){
                    Student* currNext = (*curr)->next;
                    //delete *curr;
                    *curr = currNext;
                    past->next = currNext;
                    break;
                }
            }else{
                break;
            }
            past = *curr;
            curr = &(((*curr)->next));
        }
        //... then inserting
        linkedAdd((*stuList)[index], temp);
        return;
    }
    //Otherwise, there are more than 3 conflicts, and we need to rehash the entire table.
    else{
        //Create new array, double hashsize
        int newHashSize = hashSize*2;
        Student** newStuL = new Student*[newHashSize];
        Student*** newStuList = &newStuL;
        for(int a = 0; a < hashSize; ++a){
            //Traverse the old hashtable, insert everything into the new one, with the hashalgorithm now accounting for double the size
            Student* mew = (*stuList)[a];
            Student *mewN;
            while(true){
                if(mew!=NULL){
                    mewN = mew->next;
                    mew->next = NULL;
                    hashFunction(mew, newStuList, newHashSize);
                }else{
                    break;
                }
                mew = mewN;
            }
        }
        //Deallocate old table
        delete[] (*stuList);
        //Set old table pointer to new table
        (*stuList) = newStuL;
        //Set old hashsize to new hashsize
        hashSize = newHashSize;
        //Insert the node that had the conflict
        hashFunction(temp, stuList, hashSize);
    }
}

//Traverses linked list and returns the length
int linkedLength(Student* head){
    int length = 0;
    while(true){
        if(head != NULL){
            length++;
        }else{
            break;
        }
        head = head->next;
    }
    return length;
}

//Inserts at the linked list head
void linkedAdd(Student* &oldHead, Student* newHead){
    //set newHead next to oldHead
    newHead->next = oldHead;
    //setoldHead to newHead!
    oldHead = newHead;
}

//Prints linked list, assumes head is not null
void linkedPrint(Student* head){
    while(true){
        if(head!= NULL){
            cout << head->fNm << ", " << head->lNm << ", " << head->id << ", " << head->gpa << " -> ";
        }else{
            break;
        }
        head = head->next;
    }
    cout << "\n" << endl;
}

//Prints linked list, assumes head is not null, doesn't add arrows
void linkedPrintReg(Student* head){
    while(true){
        if(head!= NULL){
            cout << head->fNm << "  " << head->lNm << "  " << head->id << "  " << head->gpa << "\n" <<endl;
        }else{
            break;
        }
        head = head->next;
    }
}

int pow(int base, int exponent){
    int res = base;
    if(exponent == 0){
        return 1;
    }
    for(int a = 1; a < exponent; ++a){
        res = base*res;
    }
    return res;
}

int abs(int a){
    if(a < 0){
        return -1*a;
    }else{
        return a;
    }
}

//A really pointless formula that works to hash ascii codes so
int hashAlgorithm(char* id, int hashSize){
    long long int index = 0;
    //Loop through the student ID
    int idLen = strlen(id);
    for(int a = 0; a < idLen; ++a){
        //int HS = hashSize;
        int x = (int)(id[a]);
        switch(a){
            //3Hs^2x^3
            case 1:
                index += (2 * pow(x, 1));
                break;
                //6Hsx^2
            case 2:
                index += (3 * pow(x, 2));
                break;
                //9x
            case 3:
                index += (5 * pow(x, 1));
                break;
                //6x
            case 4:
                index += (7 * pow(x, 2));
                break;
                //9Hsx^2
            case 5:
                index += (3 * pow(x, 1));
                break;
                //7hs^2x^3
            case 6:
                index += (5 * pow(x, 2));
                break;
        }
    }
    //Take the modulus of that over hashSizse, which should equal final index
    index = abs((index%hashSize));
    return index;
}

//Generates between 0 and 1000 students by reading from a first name and last name file
void generateStudents(Student*** stuList, int &hashSize, char** fFN, char** fLN){
    //Prompt User to select the amount of random names that will be added, from 0 to 1000

    char numberToAdd[999];
    char* numToAdd = &numberToAdd[0];

    getValidNumber(numToAdd);

    int nameNumber = atoi(numToAdd);

    //Tell user that students with existing IDs will be overwritten
    cout << "Students with overlapping IDs will be overwritten. Are your sure you want to proceed? (y/n) :o" << endl;
    while(true){
        cin.getline(numToAdd, 999);
        cin.clear();

        numToAdd[0] = toupper(numToAdd[0]);

        if(strcmp(numToAdd, "Y") == 0){
            break;
        }else if (strcmp(numToAdd, "N") == 0){
            return;
        }
        cout << "Please enter Y/N. :/" << endl;
    }

    //If fFN is NULL, we know that we have to read in file names
    if(fFN[0] == NULL){
        char* buffer = new char[1001];
        //Read in First Names
        ifstream stream;
        stream.open("firstNames.txt");
        int counter = 0;
        while(stream.getline(buffer, 1001)){
            fFN[counter] = buffer;
            buffer = new char[1001];
            ++counter;
        }
        stream.close();
        //Read in Last Names
        stream.open("lastNames.txt");
        counter = 0;
        while(stream.getline(buffer, 1001)){
            //Need to uncapitalize everything that is not first letter
            int bufferLen = strlen(buffer);
            for(int a = 1; a < bufferLen; ++a){
                buffer[a] = tolower(buffer[a]);
            }
            fLN[counter] = buffer;
            buffer = new char[1001];
            ++counter;
        }
        stream.close();
        delete[] buffer;
        buffer = NULL;
    }

    //Int id counter = 0
    //int idCounter = 0;
    //For loop
    for(int a = 0; a < nameNumber; ++a){
        Student* temp = new Student;
        //Generate 2 random ints from 0 to 1000
        int firstNameIndex = rand()%1000;
        int lastNameIndex = rand()%1000;
        //Generate 1 random float number from 0 to 10
        float gpa = ((float)rand())/((float)(RAND_MAX/10));
        //Grab corresponding first and last names from file
        strcpy(temp->fNm,fFN[firstNameIndex]);
        strcpy(temp->lNm,fLN[lastNameIndex]);
        //Then gpa
        temp->gpa = gpa;
        //Then id
        strcpy(temp->id, intToSixId(a));
        //Hashfunction() in the student.
        hashFunction(temp, stuList, hashSize);
        //Increment the id counter, taken
    }
    cout << nameNumber << " students were successfully entered! :]" << endl;
}

char* intToSixId(int n){
    char temp[7];
    char* tmp = &temp[0];
    //123456
    int counter = 0;
    for(int a = 6; a >=1; --a){
        //(char)((int)((number/10^(digits-1))%10)-'0')
        tmp[counter++] = (char)((int)((n/(pow(10,(a-1))))%10)+'0');
    }
    return tmp;
}

void printRegular(Student*** stuList, int hashSize){
    bool empty = true;
    for(int a = 0; a < hashSize; a++){
        if((*stuList)[a] != NULL){
            empty = false;
            linkedPrintReg((*stuList)[a]);
        }
        }
    if(empty){
        cout << "The student list is empty!" << endl;
    }
}
