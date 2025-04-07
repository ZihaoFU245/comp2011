
// Given case 2: input/output2.txt
// The purpose of is test duel action only with the same type
void testcase2()
{
    const int num = 3;
    char aliceMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_WIND, MONSTER_TYPE_ICE};
    char aliceMonsterPower[num] = {7, 8, 9};
    char bobMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_WIND, MONSTER_TYPE_ICE};
    char bobMonsterPower[num] = {8, 8, 8};

    ActionStatus status[num];
    int i;
    int alicePoints[num];
    int bobPoints[num];

    for (i = 0; i < num; i++)
    {
        alicePoints[i] = 0;
        bobPoints[i] = 0;
        status[i] = handleActionDuel(aliceMonsterType, aliceMonsterPower, bobMonsterType, bobMonsterPower,
                                     i, i, alicePoints[i], bobPoints[i]);
    }

    ActionStatus expectedStatus[num] = {ACTION_STATUS_BOB_WIN, ACTION_STATUS_DRAW, ACTION_STATUS_ALICE_WIN};
    int expectedAlicePoints[num] = {0, 1, 3};
    int expectedBobPoints[num] = {3, 1, 0};

    for (i = 0; i < num; i++)
    {
        if (status[i] == expectedStatus[i] &&
            alicePoints[i] == expectedAlicePoints[i] &&
            bobPoints[i] == expectedBobPoints[i])
            cout << "Pass" << endl;
        else
            cout << "Fail" << endl;
    }
}

// Given case 3: input/output3.txt
// The purpose of is test duel action only with the advantage type
void testcase3()
{
    // Advantage attack rules:
    // Fire +3 attack towards ICE
    // ICE  +3 attack towards WIND
    // WIND +3 attack towards FIRE
    const int num = 3;
    char aliceMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_ICE, MONSTER_TYPE_WIND};
    char aliceMonsterPower[num] = {3, 3, 3};
    char bobMonsterType[num] = {MONSTER_TYPE_ICE, MONSTER_TYPE_WIND, MONSTER_TYPE_FIRE};
    char bobMonsterPower[num] = {5, 5, 5};

    ActionStatus status[num];
    int i;
    int alicePoints[num];
    int bobPoints[num];

    for (i = 0; i < num; i++)
    {
        alicePoints[i] = 0;
        bobPoints[i] = 0;
        status[i] = handleActionDuel(aliceMonsterType, aliceMonsterPower, bobMonsterType, bobMonsterPower,
                                     i, i, alicePoints[i], bobPoints[i]);
    }

    ActionStatus expectedStatus[num] = {ACTION_STATUS_ALICE_WIN, ACTION_STATUS_ALICE_WIN, ACTION_STATUS_ALICE_WIN};
    int expectedAlicePoints[num] = {3, 3, 3};
    int expectedBobPoints[num] = {0, 0, 0};

    for (i = 0; i < num; i++)
    {
        if (status[i] == expectedStatus[i] &&
            alicePoints[i] == expectedAlicePoints[i] &&
            bobPoints[i] == expectedBobPoints[i])
            cout << "Pass" << endl;
        else
            cout << "Fail" << endl;
    }
}

// Given case 4: input/output4.txt
// A unit test for battle
void testcase4()
{
    const int num = 3;
    char aliceMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_ICE, MONSTER_TYPE_WIND};
    char aliceMonsterPower[num] = {6, 5, 4};
    char bobMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_ICE, MONSTER_TYPE_WIND};
    char bobMonsterPower[num] = {5, 5, 5};
    int alicePoint = 0, bobPoint = 0, countAliceWin = 0, countBobWin = 0, countDraw = 0;
    ActionStatus status;

    ActionStatus expectedStatus = ACTION_STATUS_DRAW;
    int expectedAlicePoint = 4, expectedBobPoint = 4, expectedCountAliceWin = 1, expectedCountBobWin = 1, expectedCountDraw = 1;

    status = handleActionBattle(num,
                                aliceMonsterType,
                                aliceMonsterPower,
                                bobMonsterType,
                                bobMonsterPower,
                                alicePoint,
                                bobPoint,
                                countAliceWin,
                                countBobWin,
                                countDraw);

    if (status == expectedStatus &&
        alicePoint == expectedAlicePoint &&
        bobPoint == expectedBobPoint &&
        countAliceWin == expectedCountAliceWin &&
        countBobWin == expectedCountBobWin &&
        countDraw == expectedCountDraw)
    {
        cout << "Pass" << endl;
    }
    else
    {
        cout << "Fail" << endl;
    }
}

// Given case 5: input/output5.txt
// A unit test for mini-battle
void testcase5()
{
    const int num = 5;
    const int numMonstersForMiniBattle = 3;

    char aliceMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_ICE, MONSTER_TYPE_WIND, MONSTER_TYPE_FIRE, MONSTER_TYPE_WIND};
    char aliceMonsterPower[num] = {6, 5, 4};
    char bobMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_ICE, MONSTER_TYPE_WIND, MONSTER_TYPE_WIND, MONSTER_TYPE_ICE};
    char bobMonsterPower[num] = {5, 5, 5};

    int aliceMiniBattleIndices[numMonstersForMiniBattle] = {0, 1, 2};
    int bobMiniBattleIndices[numMonstersForMiniBattle] = {0, 1, 2};

    int alicePoint = 0, bobPoint = 0, countAliceWin = 0, countBobWin = 0, countDraw = 0;
    ActionStatus status;

    status = handleActionMiniBattle(numMonstersForMiniBattle,
                                    aliceMonsterType,
                                    aliceMonsterPower,
                                    bobMonsterType,
                                    bobMonsterPower,
                                    aliceMiniBattleIndices,
                                    bobMiniBattleIndices,
                                    alicePoint,
                                    bobPoint,
                                    countAliceWin,
                                    countBobWin,
                                    countDraw);

    ActionStatus expectedStatus = ACTION_STATUS_DRAW;
    int expectedAlicePoint = 4, expectedBobPoint = 4, expectedCountAliceWin = 1, expectedCountBobWin = 1, expectedCountDraw = 1;

    if (status == expectedStatus &&
        alicePoint == expectedAlicePoint &&
        bobPoint == expectedBobPoint &&
        countAliceWin == expectedCountAliceWin &&
        countBobWin == expectedCountBobWin &&
        countDraw == expectedCountDraw)
    {
        cout << "Pass" << endl;
    }
    else
    {
        cout << "Fail" << endl;
    }
}

// Given case 6: input/output6.txt
// A unit test for mini-battle
void testcase6()
{
    const int num = 5;
    const int numMonstersForMiniBattle = 3;

    char aliceMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_ICE, MONSTER_TYPE_WIND, MONSTER_TYPE_FIRE, MONSTER_TYPE_WIND};
    char aliceMonsterPower[num] = {6, 5, 4};
    char bobMonsterType[num] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_ICE, MONSTER_TYPE_WIND, MONSTER_TYPE_WIND, MONSTER_TYPE_ICE};
    char bobMonsterPower[num] = {5, 5, 5};

    int aliceMiniBattleIndices[numMonstersForMiniBattle] = {2, 1, 0};
    int bobMiniBattleIndices[numMonstersForMiniBattle] = {2, 1, 0};

    int alicePoint = 0, bobPoint = 0, countAliceWin = 0, countBobWin = 0, countDraw = 0;
    ActionStatus status;

    status = handleActionMiniBattle(numMonstersForMiniBattle,
                                    aliceMonsterType,
                                    aliceMonsterPower,
                                    bobMonsterType,
                                    bobMonsterPower,
                                    aliceMiniBattleIndices,
                                    bobMiniBattleIndices,
                                    alicePoint,
                                    bobPoint,
                                    countAliceWin,
                                    countBobWin,
                                    countDraw);

    ActionStatus expectedStatus = ACTION_STATUS_DRAW;
    int expectedAlicePoint = 4, expectedBobPoint = 4, expectedCountAliceWin = 1, expectedCountBobWin = 1, expectedCountDraw = 1;

    if (status == expectedStatus &&
        alicePoint == expectedAlicePoint &&
        bobPoint == expectedBobPoint &&
        countAliceWin == expectedCountAliceWin &&
        countBobWin == expectedCountBobWin &&
        countDraw == expectedCountDraw)
    {
        cout << "Pass" << endl;
    }
    else
    {
        cout << "Fail" << endl;
    }
}

// Given case 7: input/output7.txt
// A unit test for reorder
void testcase7()
{
    const int numMonsters = 5;
    char monsterType[numMonsters] = {MONSTER_TYPE_FIRE, MONSTER_TYPE_ICE, MONSTER_TYPE_WIND, MONSTER_TYPE_FIRE, MONSTER_TYPE_WIND};
    char monsterPower[numMonsters] = {6, 5, 4, 3, 2};
    int reorderIndices[numMonsters] = {4, 0, 1, 3, 2};

    char expectedMonsterType[numMonsters] =
     {
        monsterType[ reorderIndices[0] ],
        monsterType[ reorderIndices[1] ],
        monsterType[ reorderIndices[2] ],
        monsterType[ reorderIndices[3] ],
        monsterType[ reorderIndices[4] ]
     };
    char expectedMonsterPower[numMonsters] = 
    {
        monsterPower[ reorderIndices[0] ],
        monsterPower[ reorderIndices[1] ],
        monsterPower[ reorderIndices[2] ],
        monsterPower[ reorderIndices[3] ],
        monsterPower[ reorderIndices[4] ]

    };

    handleActionRecorder(numMonsters, monsterType, monsterPower, reorderIndices);
    for (int i=0; i<numMonsters; i++) {
        if ( monsterType[i] ==  expectedMonsterType[i] && monsterPower[i] == expectedMonsterPower[i] )
            cout << "Pass" << endl;
        else
            cout << "Fail" << endl;
    }

}