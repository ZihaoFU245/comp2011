// === Region: Headers ===
// iostream and cstring are included.
// Do not include extra header files
// =======================
#include <iostream>
#include <cstring>
using namespace std;

// === Region: Constants ===
const int MAX_NUM_MONSTERS = 20;

// Advantage attack rules:
// Fire +3 attack towards ICE
// ICE  +3 attack towards WIND
// WIND +3 attack towards FIRE
const int MONSTER_TYPE_ADVANTAGE = 3;
const char MONSTER_TYPE_FIRE = 'F';
const char MONSTER_TYPE_WIND = 'W';
const char MONSTER_TYPE_ICE = 'I';

// Status for Action
enum ActionStatus
{
    ACTION_STATUS_DRAW = 0,
    ACTION_STATUS_ALICE_WIN,
    ACTION_STATUS_BOB_WIN
};

// Game point adjustment constants
const int POINT_WIN = 3;
const int POINT_DRAW = 1;



// Given Helper functions:
//   Compare 2 character arrays,
//   return true if they are equal, otherwise, return false
bool equalCharArray(const char arr1[], const char arr2[])
{
    if (strcmp(arr1, arr2) == 0)
        return true;
    return false;
}
// print status text based on the status
void printStatusText(ActionStatus status)
{
    if (status == ACTION_STATUS_DRAW)
        cout << "Draw";
    else if (status == ACTION_STATUS_ALICE_WIN)
        cout << "Alice wins";
    else
        cout << "Bob wins";
    cout << " " << endl;
}
// print the points of Alice and Bob
void printPoints(int alicePoint, int bobPoint)
{
    cout << "Alice point = " << alicePoint << endl;
    cout << "Bob point = " << bobPoint << endl;
}
// print the counts
void printCounts(int countAliceWin, int countBobWin, int countDraw)
{
    cout << "Alice wins " << countAliceWin << " time(s)" << endl;
    cout << "Bob wins " << countBobWin << " time(s)" << endl;
    cout << "Draw " << countDraw << " time(s)" << endl;
}
// copy a character array using a loop
void copyCharArray(const char fromArr[], char toArr[], int num)
{
    for (int i = 0; i < num; i++)
        toArr[i] = fromArr[i];
}

// copy and paste the code from pa1.cpp
// Students should ONLY write code in pa1.cpp
// No code should be added or modify in this file
#include "pa1.cpp"    //Remove this for final testing!!!!!!!!!!!!!!!!!!

// function normalGame: handle the normal game input and output
void normalGame()
{
    const char KEYWORD_ACTION_DUEL[] = "Duel";
    const char KEYWORD_ACTION_BATTLE[] = "Battle";
    const char KEYWORD_ACTION_MINI_BATTLE[] = "Mini-battle";
    const char KEYWORD_ACTION_REORDER[] = "Reorder";
    const char KEYWORD_ACTION_END[] = "!!";
    const char KEYWORD_PLAYER_ALICE[] = "Alice";
    int numMonsters;
    char aliceMonsterType[MAX_NUM_MONSTERS], bobMonsterType[MAX_NUM_MONSTERS];
    char aliceMonsterPower[MAX_NUM_MONSTERS], bobMonsterPower[MAX_NUM_MONSTERS];
    int alicePoint = 0, bobPoint = 0;
    char playerText[20], actionText[20];
    ActionStatus status;

    // input handling for the normal game mode
    int i, j;
    cin >> numMonsters;
    for (i = 0; i < 2; i++)
    {
        cin >> playerText;
        if (equalCharArray(playerText, KEYWORD_PLAYER_ALICE))
        {
            // Read data for Alice
            for (j = 0; j < numMonsters; j++)
            {
                cin >> aliceMonsterType[j];
            }
            for (j = 0; j < numMonsters; j++)
            {
                cin >> aliceMonsterPower[j];
            }
        }
        else
        {
            // Read data for Bob
            for (j = 0; j < numMonsters; j++)
            {
                cin >> bobMonsterType[j];
            }
            for (j = 0; j < numMonsters; j++)
            {
                cin >> bobMonsterPower[j];
            }
        }
    }

    // handling actions, until end of action is reached
    while (true)
    {
        cin >> actionText;
        if (equalCharArray(actionText, KEYWORD_ACTION_END))
        {
            cout << "Game finished" << endl;
            return;
        }

        if (equalCharArray(actionText, KEYWORD_ACTION_DUEL))
        {
            // Handle: Duel action
            // Format: Alice [Index of Alice] Bob [Index of Bob]
            int aliceIndex, bobIndex;
            cin >> playerText >> aliceIndex >> playerText >> bobIndex;

            status = handleActionDuel(aliceMonsterType,
                                      aliceMonsterPower,
                                      bobMonsterType,
                                      bobMonsterPower,
                                      aliceIndex,
                                      bobIndex,
                                      alicePoint,
                                      bobPoint);

            cout << "== Result of Duel: Alice " << aliceIndex << " Bob " << bobIndex << " ==" << endl;
            printStatusText(status);
            printPoints(alicePoint, bobPoint);
        }
        else if (equalCharArray(actionText, KEYWORD_ACTION_BATTLE))
        {
            // Handle: Battle action
            // No need to read extra output
            int countAliceWin = 0, countBobWin = 0, countDraw = 0;
            status = handleActionBattle(numMonsters,
                                        aliceMonsterType,
                                        aliceMonsterPower,
                                        bobMonsterType,
                                        bobMonsterPower,
                                        alicePoint, bobPoint,
                                        countAliceWin, countBobWin, countDraw);
            cout << "== Result of Battle ==" << endl;
            printStatusText(status);
            printCounts(countAliceWin, countBobWin, countDraw);
            printPoints(alicePoint, bobPoint);
        }
        else if (equalCharArray(actionText, KEYWORD_ACTION_MINI_BATTLE))
        {
            // Handle: Mini-battle action
            int numMonstersForMiniBattle;
            int aliceMiniBattleIndices[MAX_NUM_MONSTERS];
            int bobMiniBattleIndices[MAX_NUM_MONSTERS];
            int countAliceWin = 0, countBobWin = 0, countDraw = 0;

            cin >> numMonstersForMiniBattle;
            cin >> playerText; // skip the player text (Alice)
            for (i = 0; i < numMonstersForMiniBattle; i++)
                cin >> aliceMiniBattleIndices[i];
            cin >> playerText; // skip the player text (Bob)
            for (i = 0; i < numMonstersForMiniBattle; i++)
                cin >> bobMiniBattleIndices[i];

            cout << "== Result of Mini-Battle " << numMonstersForMiniBattle << " ==" << endl;
            cout << "Mini-Battle team for Alice: ";
            for (i = 0; i < numMonstersForMiniBattle; i++)
                cout << aliceMonsterType[aliceMiniBattleIndices[i]] << aliceMonsterPower[aliceMiniBattleIndices[i]] << " ";
            cout << endl;
            cout << "Mini-Battle team for Bob: ";
            for (i = 0; i < numMonstersForMiniBattle; i++)
                cout << bobMonsterType[bobMiniBattleIndices[i]] << bobMonsterPower[bobMiniBattleIndices[i]] << " ";
            cout << endl;
            status = handleActionMiniBattle(numMonstersForMiniBattle,
                                            aliceMonsterType, aliceMonsterPower,
                                            bobMonsterType, bobMonsterPower,
                                            aliceMiniBattleIndices, bobMiniBattleIndices,
                                            alicePoint, bobPoint,
                                            countAliceWin, countBobWin, countDraw);

            printStatusText(status);
            printCounts(countAliceWin, countBobWin, countDraw);
            printPoints(alicePoint, bobPoint);
        }
        else if (equalCharArray(actionText, KEYWORD_ACTION_REORDER))
        {
            cin >> playerText;
            int reorderIndices[MAX_NUM_MONSTERS];
            for (i = 0; i < numMonsters; i++)
                cin >> reorderIndices[i];

            char beforeType[MAX_NUM_MONSTERS];
            char beforePower[MAX_NUM_MONSTERS];

            if (equalCharArray(playerText, KEYWORD_PLAYER_ALICE))
            {
                // reorder for Alice
                copyCharArray(aliceMonsterType, beforeType, numMonsters);
                copyCharArray(aliceMonsterPower, beforePower, numMonsters);
                handleActionRecorder(numMonsters, aliceMonsterType, aliceMonsterPower, reorderIndices);
                cout << "== Result of Reorder for " << playerText << " ==" << endl;
                cout << "Before: ";
                for (i = 0; i < numMonsters; i++)
                    cout << beforeType[i] << beforePower[i] << " ";
                cout << endl;
                cout << "After: ";
                for (i = 0; i < numMonsters; i++)
                    cout << aliceMonsterType[i] << aliceMonsterPower[i] << " ";
                cout << endl;
            }
            else
            {
                // reorder for Bob
                copyCharArray(bobMonsterType, beforeType, numMonsters);
                copyCharArray(bobMonsterPower, beforePower, numMonsters);
                handleActionRecorder(numMonsters, bobMonsterType, bobMonsterPower, reorderIndices);
                cout << "== Result of Reorder for " << playerText << " ==" << endl;
                cout << "Before: ";
                for (i = 0; i < numMonsters; i++)
                    cout << beforeType[i] << beforePower[i] << " ";
                cout << endl;
                cout << "After: ";
                for (i = 0; i < numMonsters; i++)
                    cout << bobMonsterType[i] << bobMonsterPower[i] << " ";
                cout << endl;
            }
        }
    }
}

// Copy and paste the unit tests here
#include "pa1_unit_tests.cpp"




int not_main()
{
    // Keywords for the input handling
    const char KEYWORD_GAME_MODE[] = "Game-mode";
    const char KEYWORD_GAME_MODE_NORMAL[] = "normal";
    char gameModeText[20], gameMode[20];
    // input handling for game mode
    cin >> gameModeText >> gameMode;
    if (!equalCharArray(gameModeText, KEYWORD_GAME_MODE))
    {
        cout << "Wrong input format. Game terminated" << endl;
        return -1;
    }
    if (equalCharArray(gameMode, KEYWORD_GAME_MODE_NORMAL))
    {
        normalGame();
    }
    else
    {
        // Test mode: input one more test case number
        // This mode is for unit testing (i.e., testing one function at a time, with simplified output: Pass/Fail)

        // After the deadline, we will modify this file by adding more hidden cases
        // Most hidden cases will follow this pattern
        int whichTestCase;
        cin >> whichTestCase;
        switch (whichTestCase)
        {
        case 2:
            testcase2();
            break;
        case 3:
            testcase3();
            break;
        case 4:
            testcase4();
            break;
        case 5:
            testcase5();
            break;
        case 6:
            testcase6();
            break;
        case 7:
            testcase7();
            break;
        default:
            cout << "Invalid test case" << endl;
            break;
        }
    }
    return 0;
}

int main() {
    testcase2();cout << endl;
    testcase3();cout << endl;
    testcase4();cout << endl; 
    testcase5();cout << endl;
    testcase6();cout << endl;
    testcase7();cout << endl;  
}