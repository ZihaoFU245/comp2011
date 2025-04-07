// === Region: Project Declaration ===
//
//  COMP2011 Spring 2025
//  PA1: Monster Game
//
//  Your name:
//  Your ITSC email:           zfuat@connect.ust.hk
//
//  Note: Generative AI is NOT allowed in completing your lab exercises or programming assignments
//  Reference: https://course.cse.ust.hk/comp2011/web/code.html
//
//  Declaration:
//  I declare that I am not involved in plagiarism
//  I understand that both parties (i.e., students providing the codes and students copying the codes) will receive 0 marks.
//
//  Project TA: Peter CHUNG (cspeter@cse.ust.hk)
//
//  For code-level questions, please send a direct email to the above TA.
//  Asking questions with code blocks in a public discussion forum (e.g., Piazza) may cause plagiarism issues
//  Usually, you will get the quickest response via a direct email.
//
// =====================================

/*
// Declare variables , for better writing
#include <cstring>
#include <iostream>
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

// remove above before compile

/* void handleActionDuel
 * @param aliceMonsterType: an array storing the monster types of Alice
 * @param aliceMonsterPower: an array storing the monster powers of alice
 * @param bobMonsterType: an array storing the monster types of Bob
 * @param bobMonsterPower: an array storing the monster powers of Bob
 * @param aliceIndex: The chosen monster index for Alice
 * @param bobIndex: The chosen monster index for Bob
 *
 * In this function, we have some return values and they are pass-by-reference
 *
 * @return alicePoint: The updated point for Alice
 * @return bobPoint: The updated point for bob
 *
 * @return a suitable ActionStatus (see the provided enum)
 */
ActionStatus handleActionDuel(const char aliceMonsterType[MAX_NUM_MONSTERS],
                              const char aliceMonsterPower[MAX_NUM_MONSTERS],
                              const char bobMonsterType[MAX_NUM_MONSTERS],
                              const char bobMonsterPower[MAX_NUM_MONSTERS],
                              int aliceIndex,
                              int bobIndex,
                              int &alicePoint,
                              int &bobPoint)
{
    // TODO: Implement handleActionDuel
    char Alice_type = aliceMonsterType[aliceIndex];
    char Alice_power = aliceMonsterPower[aliceIndex];
    char Bob_type = bobMonsterType[bobIndex];
    char Bob_power = bobMonsterPower[bobIndex];
    int A_power = static_cast<int>(Alice_power) - static_cast<int>('0');
    int B_power = static_cast<int>(Bob_power) - static_cast<int>('0');

    // MAIN LOGIC
    if ((Alice_type == MONSTER_TYPE_FIRE && Bob_type == MONSTER_TYPE_ICE) || (Alice_type == MONSTER_TYPE_ICE && Bob_type == MONSTER_TYPE_WIND) || (Alice_type == MONSTER_TYPE_WIND && Bob_type == MONSTER_TYPE_FIRE))
    {
        // ALICE ADVANTAGE
        A_power += MONSTER_TYPE_ADVANTAGE;
    }
    else if (Alice_type == Bob_type)
    {
        // NOT CHANGING ANYTHING
    }
    else
    {
        // BOB ADVANTAGE
        B_power += MONSTER_TYPE_ADVANTAGE;
    }

    if (A_power > B_power)
    {
        // ALICE WIN
        alicePoint += POINT_WIN;
        return ACTION_STATUS_ALICE_WIN;
    }
    else if (A_power == B_power)
    {
        // DRAW
        alicePoint += POINT_DRAW;
        bobPoint += POINT_DRAW;
        return ACTION_STATUS_DRAW;
    }
    else
    {
        // BOB WIN
        bobPoint += POINT_WIN;
        return ACTION_STATUS_BOB_WIN;
    }
}

/* void handleActionBattle
 * @param numMonsters: The number of monsters
 * @param aliceMonsterType: an array storing the monster types of Alice
 * @param aliceMonsterPower: an array storing the monster powers of alice
 * @param bobMonsterType: an array storing the monster types of Bob
 * @param bobMonsterPower: an array storing the monster powers of Bob
 *
 * In this function, we have some return values and they are pass-by-reference
 *
 * @return alicePoint: The updated point for Alice
 * @return bobPoint: The updated point for bob
 * @return countAliceWin: The number of wins for Alice
 * @return countBobWin: The number of wins for Bob
 * @return countDraw: The number of draws
 *
 * @return a suitable ActionStatus (see the provided enum).
 * Alice wins if Alice's totalPointChange > Bob's totalPointChange.
 * Draws if they are equal, otherwise, Bob wins.
 */
ActionStatus handleActionBattle(int numMonsters,
                                const char aliceMonsterType[MAX_NUM_MONSTERS],
                                const char aliceMonsterPower[MAX_NUM_MONSTERS],
                                const char bobMonsterType[MAX_NUM_MONSTERS],
                                const char bobMonsterPower[MAX_NUM_MONSTERS],
                                int &alicePoint,
                                int &bobPoint,
                                int &countAliceWin,
                                int &countBobWin,
                                int &countDraw)
{
    // TODO: Implement handleActionBattle
    int i;
    ActionStatus temp;
    for (i = 0; i < numMonsters; i++)
    {
        temp = handleActionDuel(aliceMonsterType, aliceMonsterPower,
                                bobMonsterType, bobMonsterPower,
                                i, i, alicePoint, bobPoint);

        if (temp == ACTION_STATUS_ALICE_WIN)
        {
            countAliceWin += 1;
        }
        else if (temp == ACTION_STATUS_BOB_WIN)
        {
            countBobWin += 1;
        }
        else
        {
            countDraw += 1;
        }
    }

    if (countAliceWin > countBobWin)
    {
        return ACTION_STATUS_ALICE_WIN;
    }
    else if (countAliceWin == countBobWin)
    {
        return ACTION_STATUS_DRAW;
    }
    else
    {
        return ACTION_STATUS_BOB_WIN;
    }
}

/* void handleActionMiniBattle
 * @param numMonstersForMiniBattle: The number of monsters for mini battle
 * @param aliceMonsterType: an array storing the monster types of Alice
 * @param aliceMonsterPower: an array storing the monster powers of alice
 * @param bobMonsterType: an array storing the monster types of Bob
 * @param bobMonsterPower: an array storing the monster powers of Bob
 *
 * In this function, we have some return values and they are pass-by-reference
 *
 * @return alicePoint: The updated point for Alice
 * @return bobPoint: The updated point for bob
 * @return countAliceWin: The number of wins for Alice
 * @return countBobWin: The number of wins for Bob
 * @return countDraw: The number of draws
 *
 * @return a suitable ActionStatus (see the provided enum).
 * Alice wins if Alice's totalPointChange > Bob's totalPointChange.
 * Draws if they are equal, otherwise, Bob wins.
 */
ActionStatus handleActionMiniBattle(int numMonstersForMiniBattle, // Loop
                                    const char aliceMonsterType[MAX_NUM_MONSTERS],
                                    const char aliceMonsterPower[MAX_NUM_MONSTERS],
                                    const char bobMonsterType[MAX_NUM_MONSTERS],
                                    const char bobMonsterPower[MAX_NUM_MONSTERS],
                                    const int aliceMiniBattleIndices[MAX_NUM_MONSTERS], // battle index
                                    const int bobMiniBattleIndices[MAX_NUM_MONSTERS],
                                    int &alicePoint,
                                    int &bobPoint,
                                    int &countAliceWin,
                                    int &countBobWin,
                                    int &countDraw)
{
    // TODO: Implement handleActionMiniBattle
    int index, a, b;
    ActionStatus temp;
    for (index = 0; index < numMonstersForMiniBattle; index++)
    {
        a = aliceMiniBattleIndices[index];
        b = bobMiniBattleIndices[index];

        // one battle
        temp = handleActionDuel(aliceMonsterType, aliceMonsterPower,
                                bobMonsterType, bobMonsterPower,
                                a, b, alicePoint, bobPoint);

        if (temp == ACTION_STATUS_ALICE_WIN)
        {
            countAliceWin += 1;
        }
        else if (temp == ACTION_STATUS_BOB_WIN)
        {
            countBobWin += 1;
        }
        else
        {
            countDraw += 1;
        }
    }

    if (countAliceWin > countBobWin)
    {
        return ACTION_STATUS_ALICE_WIN;
    }
    else if (countAliceWin == countBobWin)
    {
        return ACTION_STATUS_DRAW;
    }
    else
    {
        return ACTION_STATUS_BOB_WIN;
    }
}

/* void handleActionReorder
 * @param numMonsters: The number of monsters
 * @param monsterType: an array storing the monster types (array content should be reordered after this function)
 * @param monsterPower: an array storing the monster powers  (array content should be reordered after this function)
 * @param reorderIndices: The reorder indices
 *
 * No return value for this function
 */
void handleActionRecorder(int numMonsters,
                          char monsterType[MAX_NUM_MONSTERS],
                          char monsterPower[MAX_NUM_MONSTERS],
                          const int reorderIndices[MAX_NUM_MONSTERS])
{
    // TODO: Implement handleActionRecorder
    char new_power[MAX_NUM_MONSTERS];
    char new_type[MAX_NUM_MONSTERS];
    char temp_type, temp_power;
    int i, index;

    for (i = 0; i < numMonsters; i++)
    {
        index = reorderIndices[i];
        temp_type = monsterType[index];
        temp_power = monsterPower[index];
        new_power[i] = temp_power;
        new_type[i] = temp_type;
    }

    copyCharArray(new_power , monsterPower , numMonsters);
    copyCharArray(new_type , monsterType , numMonsters);
}
