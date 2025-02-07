#include <iostream>
#include <vector>
using namespace std;

// variables
const double PASSING_OVERALL = 36;
const double PASSING_EXAM_ONLY = 14;

const double MAX_LABS = 24;
const double MAX_PAS = 300;
const double MAX_QUIZ = 100;
const double MAX_MIDTERM = 100;
const double MAX_FINAL = 100;

const double WEIGHT_LABS = 10;
const double WEIGHT_PAS = 24;
const double WEIGHT_QUIZ = 5;
const double WEIGHT_MIDTERM = 25;
const double WEIGHT_FINAL = 36;

vector<int> io_operation()
{
    vector<int> user_input;
    int user_lab_score;
    int user_pa_score;
    int user_quiz;
    int user_midterm;
    int user_final;

    // get input
    cout << "Enter your total lab score (Max: " << MAX_LABS << "): ";
    cin >> user_lab_score;
    cout << "Enter your total PA score (Max: " << MAX_PAS << "): ";
    cin >> user_pa_score;
    cout << "Enter your quiz score (Max: " << MAX_QUIZ << "): ";
    cin >> user_quiz;
    cout << "Enter your midterm score (Max: " << MAX_MIDTERM << "): ";
    cin >> user_midterm;
    cout << "Enter your final score (Max: " << MAX_FINAL << "): ";
    cin >> user_final;

    user_input.push_back(user_lab_score);
    user_input.push_back(user_pa_score);
    user_input.push_back(user_quiz);
    user_input.push_back(user_midterm);
    user_input.push_back(user_final);
    return user_input;
}

void score_calculation(const vector<int> v)
{ // lab , pas,quiz,midterm,final
    float overall_passing_score = 0.1 * v.at(0) + 0.24 * v.at(1) + 0.05 * v.at(2) + 0.25 * v.at(3) + 0.36 * v.at(4);
    float exam_pass = 0.05 * v.at(2) + 0.25 * v.at(3) + 0.36 * v.at(4);

    cout << "Your exam only weighted score is: " << exam_pass << endl;
    cout << "Your overall score is: " << overall_passing_score << endl;
    if (overall_passing_score >= PASSING_OVERALL && exam_pass >= PASSING_EXAM_ONLY)
    {
        cout << "You passed! Take a rest!" << endl;
    }
    else
    {
        cout << "You failed! Please retake!" << endl;
    }
}

int main()
{
    vector<int> inputs;
    inputs = io_operation();
    score_calculation(inputs);
    return 0;
}
