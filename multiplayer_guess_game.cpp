#include <iostream>
#include <ctime>
#include <limits>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

int get_input();

class Player
{
private:
    string name;
    int steps = 0;
    int chances = 5;
    int target;
    int guess;
    bool win = false;
    bool started = false;

public:
    Player(const string n, const int t) : name(n), target(t) {}

    static Player create_player(string name, int t)
    {
        return Player(name, t);
    }

    string get_name()
    {
        return name;
    }

    void set_status(bool status)
    { // start or end game
        started = status;
    }

    bool check_played()
    { // ture = win
        if (started == false)
        {
            return false;
        }
        return true;
    }

    bool play()
    {
        int input;
        cout << name << " : " << endl;
        input = get_input();
        if (target == input)
        {
            cout << "You get the correct number! :)" << endl;
            cout << name << " is the winner! " << endl;
            return true;
        }
        else if (target < input)
        {
            cout << "Your number is bigger than than it(:" << endl;
        }
        else
        {
            cout << "Your number is less than the number(:" << endl;
        }
        ++steps;

        if (steps >= chances)
        {
            win = false;
            started = false;
            cout << name << " : is out(:" << endl;
            return false;
        }

        return false;
    }
};

int generate_num()
{
    int num;
    srand(time(0));
    num = rand() % 100 + 1;
    return num;
}

int get_input()
{
    int input;
    cout << "Enter your gusses, between 1 and 100 : " << endl;
    while (!(cin >> input) || input < 1 || input > 100)
    {
        cout << "Invalid input: " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return input;
}

void start_game()
{
    int target;
    int numplayers;
    vector<Player> player;
    string temp_name;
    bool game_status;
    target = generate_num();

    cout << "Enter the number of players: " << endl;
    cin >> numplayers;

    for (int i = 1; i <= numplayers; ++i)
    {
        temp_name = "Player" + to_string(i);
        player.push_back(Player::create_player(temp_name, target));
    }

    for (Player &p : player)
    {
        p.set_status(true);
    }

    while (true)
    {
        try
        {   bool temp , all=false;
            for (Player &p : player)
            {   

                if (p.check_played() == false)
                {   
                    temp = false;
                    continue;
                }
                else
                {   
                    temp = true;
                    game_status = p.play();
                    if (game_status == true)
                    {
                        throw string("game ends!");
                    }
                }
                
                all = temp || false;
            }

            if (all == false) {
                throw string("You all loose, try again.");
            }

        }
        catch (const string &e)
        {
            cout << e << endl;
            break;
        }
    }
}

int main()
{
    start_game();
    return 0;
}
