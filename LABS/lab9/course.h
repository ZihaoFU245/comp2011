#include <cstring>

class Course
{
private:
    char *course_ID;   // Course ID, e.g., COMP2011
    char *course_name; // Course name, e.g., Programming_with_C++
    int start_time;    // Start timestamp of the exam
    int end_time;      // End timestamp of the exam
    int num_students;  // Number of students that will attend the final exam

public:
    //====================
    // Constructors
    // Default constructor
    Course();

    // Another constructor
    // ID: course ID (you can assume it not nullptr)
    // name: course name (you can assume it not nullptr)
    // s: exam start timestamp
    // e: exam end timestep
    // num_stu: number of students
    Course(const char *ID, const char *name, int s, int e, int num_stu);

    // Destructor
    ~Course();

    //====================
    // Accessor member functions
    const char *get_course_ID() const;
    const char *get_course_name() const;
    int get_start_time() const;
    int get_end_time() const;
    int get_num_stu() const;

    //====================
    // Mutator member functions
    // With the same parameter difinitions as the constructor
    void set(const char *ID, const char *name, int s, int e, int num_stu);
};
