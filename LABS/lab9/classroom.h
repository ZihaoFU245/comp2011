#include "course.h"
#include <cstring>
#include <iostream>
using namespace std;

const int MAX_COURSES = 10;

class Classroom
{
private:
    char *room_ID;               // A dynamic array to store the ID of the classroom, e.g., RM2464
    int capacity;                // Number of seats
    Course courses[MAX_COURSES]; // A Course array records all the course applying to use this classroom as the exam place
    int num_app;                 // Number of courses applying to use this classroom, i.e., num of courses stored in the courses array
    int exam_list[MAX_COURSES];  // An array records the index of the courses that can use this classroom as their final exam place
                                //  e.g. if exam_list[0] is 1, it means courses[1] is the first course that can use this classroom
    int num_exams; // Number of exams that will be held in this class room

public:
    //====================
    // Constructor
    // ID: classroom ID (assume: not nullptr)
    // q: capacity
    Classroom(const char *ID, int q);
    // Destructor
    ~Classroom();

    //====================
    // Accessors
    // Print the timetable
    void print_timetable() const;

    //==========
    // Mutators
    // Receive the application of a couse
    void receive_app(const char *course_ID, const char *course_name, int start, int end, int num_stu);
    // Generate the final timetable
    void gen_timetable();
};
