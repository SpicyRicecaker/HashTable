/*
  Author: Andy Li
  Date: 06/07/2020
  StudentList: A program that can store the first name, last name, id, and gpa of multiple students using hash tables. It features 3 main functions: the add, delete, and print functions, which can add a new student to the list, remove a student from the list based on their ID, and print out the list of students, respectively.

*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <iterator>

using namespace std;

//A student needs a first name, last name, id, and gpa.
struct Student{
    char fNm[999];
    char lNm[999];
    char id[7];
    float gpa;
    Student* next = NULL;
};

void add(Student*** stuList, int &hashSize);
void getRid(Student*** stuList, int &hashSize);
void print(Student*** stuList, int hashSize);
void generateStudents(Student*** stuList, int &hashSize);
void quit(bool &running);
void getValidFirstName(Student* &temp);
void getValidLastName(Student* &temp);
void getValidId(Student* &temp);
void getValidGpa(Student* &temp);
void hashFunction(Student* temp, Student*** stuList, int &hashSize);
int linkedLength(Student* head);
void linkedAdd(Student* &oldHead, Student* newHead);
void linkedPrint(Student* head);
int pow(int base, int exponent);
int abs(int a);
int hashAlgorithm(char* id, int hashSize);


//The add method prompts the user for the firstname, lastname, id, and gpa of a student and adds that student along into the list of students, making sure to validate user input.
void add(Student*** stuList, int &hashSize){


    //Allocates the student to heap memory
    //stuList->push_back(new Student());

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

    //Hash it in somehow!!
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    hashFunction(temp, stuList, hashSize);
   
    cout << "Student added! :)" << endl;
}

//The getRid method prompts the user for an ID of a student and removes it from the studentList
void getRid(Student*** stuList, int &hashSize){
    //Prompt and validate userinput for the ID of a student
    cout << "Please enter the id of the student. :)" << endl;

    while(true){
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

            Student** curr = &((*stuList)[hashAlgorithm(in, hashSize)]);
            Student* past = *curr;
            while(true){
                if(curr!=NULL){
                    if(strcmp((*curr)->id, in) == 0){
                        Student* currNext = (*curr)->next;
                        //delete *curr;
                        *curr = currNext;
                        past->next = currNext;
                        cout << "Student removed! :)" << endl;
                        return;
                    }
                }else{
                    break;
                }
                past = *curr;
                curr = &(((*curr)->next));
            }
        }
        cout << "That id does not exist. :o" << endl;
        return;
    }
    cout << "Please enter a six digit number. :)" << endl;
}


//The print function prints the first and last name, ID, and gpa of all students in the student list
void print(Student*** stuList, int hashSize){
    for(int a = 0; a < hashSize; a++){
        if((*stuList)[a] != NULL){
            linkedPrint((*stuList)[a]);
        }
    }
}

//The quit function exits the program
void quit(bool &running){
    cout << "Program will now exit. CY@! ;)" << endl;
    running = false;
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

    while(running){
        //Prompt and validate user for a command, then transition to the corresponding function accordingly
        cout << "Please enter a command. Type \"help\" for help. :)" << endl;

        while(true){
            //cout << "hash size is " << hashSize << endl;
            cin.getline(commandIn, 999);
            cin.clear();

            int commandInLen = strlen(commandIn);
            for(int a = 0; a < commandInLen; a++){
                commandIn[a] = toupper(commandIn[a]);
            }

            if(strcmp(commandIn, "ADD") == 0 || strcmp(commandIn, "PRINT") == 0 || strcmp(commandIn, "DELETE") == 0 || strcmp(commandIn, "QUIT") == 0 || strcmp(commandIn, "HELP") == 0){
                break;
            }

            cout << "Please enter a valid command, and type \"help\" for help. :)" << endl;

        }

        if(strcmp(commandIn, "ADD") == 0){
            add(stuList, hashSize);
        }else if(strcmp(commandIn, "PRINT") == 0){
            print(stuList, hashSize);
        }
        else if(strcmp(commandIn, "DELETE") == 0){
            getRid(stuList, hashSize);
        }
        else if(strcmp(commandIn, "QUIT") == 0){
            quit(running);
        }
        else if(strcmp(commandIn, "HELP") == 0){
            cout << "Type \"add\" to add a new student. Type \"delete\" to delete a student. type \"quit\" to exit the program. :)\n" << endl;
        }


    }
}

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
        Student** curr = &((*stuList)[index]);
        Student* past = *curr;
        while(true){
            if(curr!=NULL){
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
            //Traverse linked list
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
        delete[] (*stuList);
        (*stuList) = newStuL;
        hashSize = newHashSize;
        cout << "IT'S REPEATING FOREVER LOL" << endl;
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
    cout << endl;
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
    cout << "index before" << index << endl;
    index = abs((index%hashSize));
    cout << "index after" << index << endl;
    return index;
}

void generateStudents(Student*** stuList, int &hashSize){

}
