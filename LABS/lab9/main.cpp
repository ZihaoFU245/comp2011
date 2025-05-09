//For Windows: g++ -o lab10.exe Course.cpp Classroom.cpp main.cpp
//For Max: g++ -o lab10.out Course.cpp Classroom.cpp main.cpp
#include "classroom.h"
#include <iostream>
#include <fstream>

using namespace std;

const int MAX_PATH_SIZE = 100; //Maximum string length of the input file name
const int MAX_ROOM_ID_SIZE = 20; //Maximum string length of room ID
const int MAX_COURSE_ID_SIZE = 20; //Maximum string length of course ID
const int MAX_COURSE_NAME_SIZE = 100; //Maximum string length of course name

int main()
{
    //====================
    //Read the course information from the input file
    cout<<"Enter the path of input file: ";
    char DB_path[MAX_PATH_SIZE+1];
    cin>>DB_path;
    ifstream DB_input(DB_path);
    if (!DB_input)
    {
        cerr << "Error: Cannot open "<<DB_path<<endl;
        return -1;
    }
    char room_ID[MAX_ROOM_ID_SIZE+1];
    int quota;
    int num_courses;
    DB_input>>room_ID;
    DB_input>>quota;
    DB_input>>num_courses;
    Classroom classroom(room_ID, quota);
    int course_cnt = 0; //Course conter
    while (!DB_input.eof())
    {
        char course_ID[MAX_COURSE_ID_SIZE+1];
        char course_name[MAX_COURSE_NAME_SIZE+1];
        int start_time;
        int end_time;
        int num_students;
        DB_input>>course_ID;
        DB_input>>course_name;
        DB_input>>start_time;
        DB_input>>end_time;
        DB_input>>num_students;
        classroom.receive_app(course_ID, course_name, start_time, end_time, num_students);
        ++course_cnt;
        if(course_cnt==num_courses)
            break;
        
    }
    DB_input.close();
    //====================
    //Generate the final week time table of the classroom
    classroom.gen_timetable();
    //====================
    //Pring the generated timetable
    classroom.print_timetable();

    return 0;
}
