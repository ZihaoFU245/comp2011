#include "course.h"

//===================
// Implementation of the constructors
Course::Course()
{
    course_ID = course_name = nullptr;
    start_time = 0;
    end_time = 0;
    num_students = 0;
}

Course::Course(const char *ID, const char *name, int s, int e, int num_stu)
{
    course_ID = course_name = nullptr; 
    set(ID, name, s, e, num_stu);
}
//===================
// Implementation of the destructor
Course::~Course() 
{
    delete [] course_ID;
    delete [] course_name;
}

//===================
// Impelmentation of the accessor member funcstions
const char* Course::get_course_ID() const
{
    return course_ID;
}

const char* Course::get_course_name() const
{
    return course_name;
}

int Course::get_start_time() const
{
    return start_time;
}

int Course::get_end_time() const
{
    return end_time;
}

int Course::get_num_stu() const
{
    return num_students;
}

//====================
// Implementation of the mutator member function
// Task 1: Implement the mutator member function
void Course::set(const char *ID, const char *name, int s, int e, int num_stu)
{
    course_ID = new char[strlen(ID)+1];
    course_name = new char[strlen(name)+1];
    strcpy(course_ID, ID);
    strcpy(course_name, name);
    start_time = s;
    end_time = e;
    num_students = num_stu;
}
