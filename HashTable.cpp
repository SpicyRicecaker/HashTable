/*
  Author: Andy Li
  Date: 06/07/2020
  StudentList: A program that can store the first name, last name, id, and gpa of multiple students using vectors. It features 3 main functions: the add, delete, and print functions, which can add a new student to the list, remove a student from the list based on their ID, and print out the list of students, respectively. It uses a hash table to store the students

*/
#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>

using namespace std;

//A student needs a first name, last name, id, and gpa.
struct Student{
  char fNm[46];
  char lNm[46];
  char id[8];
  float gpa;
};

void add(vector<Student*>* stuList);
void getRid(vector<Student*>* stuList);
void print(vector<Student*>* stuList);
void quit(bool &running);

//The add method prompts the user for the firstname, lastname, id, and gpa of a student and adds that student along into the list of students, making sure to validate user input.
void add(vector<Student*>* stuList){

  //Prompting the user for the first name
  cout << "Please enter the first name of the student. :)" << endl;

  //Allocates the student to heap memory
  stuList->push_back(new Student());

  while(true){
    bool noSpace = true;

    //Get the user input, store it into the vector, reset error flags, ignore the characters after the first 50
    cin.get(stuList->at(stuList->size()-1)->fNm, 50);
    cin.clear();
    cin.ignore(999,'\n');

    //If the fullname does not equal null
    if(strlen(stuList->at(stuList->size()-1)->fNm) != 0){
      //Check if there are no spaces
      for(int a = 0; a < strlen(stuList->at(stuList->size()-1)->fNm); a++){
	if(stuList->at(stuList->size()-1)->fNm[a] == ' '){
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

  //Prompt user for last name
  cout << "Please enter the last name of the student. :)" << endl;

  //Then validate user input the same way as first name
  while(true){
    bool noSpace = true;

    cin.get(stuList->at(stuList->size()-1)->lNm, 50);
    cin.clear();
    cin.ignore(999,'\n');

    if(strlen(stuList->at(stuList->size()-1)->lNm) != 0){
      for(int a = 0; a < strlen(stuList->at(stuList->size()-1)->lNm); a++){
	if(stuList->at(stuList->size()-1)->lNm[a] == ' '){
	  noSpace = false;
	}
      }
      if(noSpace){
	break;
      }
    }

    cout << "At least put \"Snow\" or something :o" << endl;
  }

  //Prompt user for ID of the student
  cout << "Please enter the ID of the student. :)" << endl;

  while(true){

    bool alldigit = true;

    char in[8] = "";

    //Get input
    cin.get(in, 8);
    cin.clear();
    cin.ignore(999, '\n');

    //Make sure that the input is all digits
    for(int a = 0; a < strlen(in); a++){
      if(!isdigit(in[a])){
	alldigit = false;
      }
    }

    //If it's also 6 characters in length then continue
    if(alldigit && strlen(in) == 6){
      strcpy(stuList->at(stuList ->size()-1)->id, in);
      break;
    }
    cout << "Please enter a six digit number. :/" << endl;
  }

  //Prompt user for gpa
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
    cin.get(gpaIn, 34);
    cin.clear();
    cin.ignore(999, '\n');

    //For each character of the input
    for(int a = 0; a < strlen(gpaIn); a++){
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
      for(int a = 0; a < strlen(gpaIn); a++){
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
      stuList->at(stuList ->size()-1)->gpa = gpaNum+gpaNuml;
      break;
    }
    cout << "That gpa does not exist... :/" << endl;
  }
  cout << "Student added! :)" << endl;
}

//The getRid method prompts the user for an ID of a student and removes it from the studentList
void getRid(vector<Student*>* stuList){

  //Prompt and validate userinput for the ID of a student
  cout << "Please enter the id of the student. :)" << endl;

  while(true){

    bool exists = false;
    bool allDig = true;
    char in[8] = "";
    cin.get(in, 8);
    cin.clear();
    cin.ignore(999, '\n');

    for(int a = 0; a < strlen(in); a++){
      if(!isdigit(in[a])){
	allDig = false;
      }
    }

    //If input is good
    if(allDig && strlen(in) == 6){

      //Create an iterator of the student list
      vector<Student*>::iterator stuListIterator;

      //Run through the iterator
      for(stuListIterator=stuList->begin(); stuListIterator!=stuList->end(); ++stuListIterator){
	if(strcmp((*stuListIterator)->id, in) == 0){
	  //Delete the data that the iterator is pointing to and remove it from the student list
	  delete *stuListIterator;
	  stuList->erase(stuListIterator);
	  cout << "Student removed! :)" << endl;
	  return;
	}
      }

      cout << "That id does not exist. :o" << endl;
      return;
    }
    cout << "Please enter a six digit number. :)" << endl;
  }
}

//The print function prints the first and last name, ID, and gpa of all students in the student list
void print(vector<Student*>* stuList){
  //Make an iterator for the student list
  vector<Student*>::iterator stuListIterator;

  //Loop through the iterator, access the elements and print them
  for(stuListIterator=stuList->begin(); stuListIterator!=stuList->end(); ++stuListIterator){
    cout << (*stuListIterator)->fNm << ", " << (*stuListIterator)->lNm << ", " << (*stuListIterator)->id << ", " << (*stuListIterator)->gpa << endl;
  }

  if(stuList->begin() == stuList->end()){
    cout << "No students found! :)))" << endl;
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

  char commandIn[8] = "";

  bool running = true;

  //Make a vector of student pointers, then make a pointer to a vector of student pointers
  vector<Student*> stuL;
  vector<Student*>* stuList = &stuL;

  while(running){

    //Prompt and validate user for a command, then transition to the corresponding function accordingly
    cout << "Please enter a command. Type \"help\" for help. :)" << endl;

    while(true){
      cin.get(commandIn, 8);
      cin.clear();
      cin.ignore(999, '\n');

      for(int a = 0; a < strlen(commandIn); a++){
	commandIn[a] = toupper(commandIn[a]);
      }

      if(strcmp(commandIn, "ADD") == 0 || strcmp(commandIn, "PRINT") == 0 || strcmp(commandIn, "DELETE") == 0 || strcmp(commandIn, "QUIT") == 0 || strcmp(commandIn, "HELP") == 0){
	break;
      }

      cout << "Please enter a valid command, and type \"help\" for help. :)" << endl;

    }

    if(strcmp(commandIn, "ADD") == 0){
      add(stuList);
    }else if(strcmp(commandIn, "PRINT") == 0){
      print(stuList);
    }
    else if(strcmp(commandIn, "DELETE") == 0){
      getRid(stuList);
    }
    else if(strcmp(commandIn, "QUIT") == 0){
      quit(running);
    }
    else if(strcmp(commandIn, "HELP") == 0){
      cout << "Type \"add\" to add a new student. Type \"delete\" to delete a student. type \"quit\" to exit the program. :)\n" << endl;
    }


  }
}
