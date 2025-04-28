// === Header / Constant ===
// Necessary header files are included
// DO NOT include extra header files
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAX_STRING_LENGTH = 25;
enum SugarLevel
{
    None = 0,
    Half,
    Standard,
    Extra
};

// === Data structure ===
// Helper Structures for the Database
struct TeaType
{
    char name[MAX_STRING_LENGTH];
    int caffeine;
    TeaType *next;
};

struct MilkType
{
    char name[MAX_STRING_LENGTH];
    int calories;
    int stock;
    MilkType *next;
};

struct ToppingType
{
    char name[MAX_STRING_LENGTH];
    int calories;
    int stock;
    ToppingType *next;
};

struct ToppingListNode
{
    ToppingType *topping;
    ToppingListNode *next;
};

struct ReplacementListNode
{
    MilkType *milk;
    ReplacementListNode *next;
};

// Drink
struct Drink
{
    char name[MAX_STRING_LENGTH];
    int id;
    int price;
    TeaType *tea;
    MilkType *milk;
    ToppingListNode *toppings;
};
// Order
struct Order
{
    int number;
    Drink *drink;
    SugarLevel sugarLevel;
    int calories;
    int caffeine;
    Order *next;
};

// === Initializations ===
void initialize_database(TeaType *&teaTypes, MilkType *&milkTypes, ToppingType *&toppingTypes, const char *path)
{
    ifstream database(path);
    if (!database.is_open())
    {
        cout << "Error: Database file not found" << endl;
        exit(EXIT_FAILURE);
    }

    int numTea = -1, numMilk = -1, numTopping = -1;
    if (!(database >> numTea) || !(database >> numMilk) || !(database >> numTopping))
    {
        cout << "Error: Database file structure failed when inputting numbers" << endl;
        exit(EXIT_FAILURE);
    }
    if (numTea < 0 || numMilk < 0 || numTopping < 0)
    {
        cout << "Error: Database file structure failed when inputting numbers" << endl;
        exit(EXIT_FAILURE);
    }

    if (numTea > 0)
    {
        TeaType *current = new TeaType;
        teaTypes = current;
        if (!(database >> current->name) || !(database >> current->caffeine))
        {
            cout << "Error: Database file structure failed when inputting tea types" << endl;
            exit(EXIT_FAILURE);
        }
        current->next = nullptr;
        for (int i = 1; i < numTea; i++)
        {
            current->next = new TeaType;
            current = current->next;
            if (!(database >> current->name) || !(database >> current->caffeine))
            {
                cout << "Error: Database file structure failed when inputting tea types" << endl;
                exit(EXIT_FAILURE);
            }
            current->next = nullptr;
        }
    }
    else
    {
        teaTypes = nullptr;
    }

    if (numMilk > 0)
    {
        MilkType *current = new MilkType;
        milkTypes = current;
        if (!(database >> current->name) || !(database >> current->calories) || !(database >> current->stock))
        {
            cout << "Error: Database file structure failed when inputting milk types" << endl;
            exit(EXIT_FAILURE);
        }
        current->next = nullptr;
        for (int i = 1; i < numMilk; i++)
        {
            current->next = new MilkType;
            current = current->next;
            if (!(database >> current->name) || !(database >> current->calories) || !(database >> current->stock))
            {
                cout << "Error: Database file structure failed when inputting milk types" << endl;
                exit(EXIT_FAILURE);
            }
            current->next = nullptr;
        }
    }
    else
    {
        milkTypes = nullptr;
    }

    if (numTopping > 0)
    {
        ToppingType *current = new ToppingType;
        toppingTypes = current;
        if (!(database >> current->name) || !(database >> current->calories) || !(database >> current->stock))
        {
            cout << "Error: Database file structure failed when inputting topping types" << endl;
            exit(EXIT_FAILURE);
        }
        current->next = nullptr;
        for (int i = 1; i < numTopping; i++)
        {
            current->next = new ToppingType;
            current = current->next;
            if (!(database >> current->name) || !(database >> current->calories) || !(database >> current->stock))
            {
                cout << "Error: Database file structure failed when inputting topping types" << endl;
                exit(EXIT_FAILURE);
            }
            current->next = nullptr;
        }
    }
    else
    {
        toppingTypes = nullptr;
    }

    TeaType *testCurrent = teaTypes;
    while (testCurrent != nullptr && testCurrent->next != nullptr)
    {
        if (strcmp(testCurrent->name, testCurrent->next->name) >= 0)
        {
            cout << "Warning: Tea types are not sorted in alphabetical order" << endl;
        }
        testCurrent = testCurrent->next;
    }
    MilkType *testCurrentMilk = milkTypes;
    while (testCurrentMilk != nullptr && testCurrentMilk->next != nullptr)
    {
        if (strcmp(testCurrentMilk->name, testCurrentMilk->next->name) >= 0)
        {
            cout << "Warning: Milk types are not sorted in alphabetical order" << endl;
        }
        testCurrentMilk = testCurrentMilk->next;
    }
    ToppingType *testCurrentTopping = toppingTypes;
    while (testCurrentTopping != nullptr && testCurrentTopping->next != nullptr)
    {
        if (strcmp(testCurrentTopping->name, testCurrentTopping->next->name) >= 0)
        {
            cout << "Warning: Topping types are not sorted in alphabetical order" << endl;
        }
        testCurrentTopping = testCurrentTopping->next;
    }

    database.close();
}

void initialize_recipe(TeaType *teaTypes, MilkType *milkTypes, ToppingType *toppingTypes, Drink **&recipes, int &numRecipes, const char *path)
{
    ifstream recipe(path);
    if (!recipe.is_open())
    {
        cout << "Error: Recipe file not found" << endl;
        exit(EXIT_FAILURE);
    }
    if (!(recipe >> numRecipes))
    {
        cout << "Error: Recipe file structure failed when inputting numbers" << endl;
        exit(EXIT_FAILURE);
    }
    if (numRecipes < 0)
    {
        cout << "Error: Recipe file structure failed when inputting numbers" << endl;
        exit(EXIT_FAILURE);
    }
    if (numRecipes == 0)
    {
        recipes = nullptr;
        return;
    }
    recipes = new Drink *[numRecipes];
    for (int i = 0; i < numRecipes; i++)
    {
        recipes[i] = new Drink;
        if (!(recipe >> recipes[i]->name) || !(recipe >> recipes[i]->id) || !(recipe >> recipes[i]->price))
        {
            cout << "Error: Recipe file structure failed when inputting drink information " << i << "" << endl;
            exit(EXIT_FAILURE);
        }
        recipes[i]->tea = nullptr;
        recipes[i]->milk = nullptr;
        recipes[i]->toppings = nullptr;

        char tea[MAX_STRING_LENGTH];
        recipe >> tea;
        for (TeaType *current = teaTypes; current != nullptr; current = current->next)
        {
            if (strcmp(current->name, tea) == 0)
            {
                recipes[i]->tea = current;
                break;
            }
        }
        if (recipes[i]->tea == nullptr)
        {
            cout << "Error: Tea type not found - " << tea << " - when creating recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }

        char milk[MAX_STRING_LENGTH];
        recipe >> milk;
        for (MilkType *current = milkTypes; current != nullptr; current = current->next)
        {
            if (strcmp(current->name, milk) == 0)
            {
                recipes[i]->milk = current;
                break;
            }
        }
        if (recipes[i]->milk == nullptr)
        {
            cout << "Error: Milk type not found - " << milk << " - when creating recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }

        int numToppings = -1;
        if (!(recipe >> numToppings) || numToppings < 0)
        {
            cout << "Error: Recipe file structure failed when inputting number of toppings for recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }
        if (numToppings == 0)
            continue;
        ToppingListNode *current = new ToppingListNode;
        current->topping = nullptr;
        current->next = nullptr;
        recipes[i]->toppings = current;
        char toppingName[MAX_STRING_LENGTH];
        if (!(recipe >> toppingName))
        {
            cout << "Error: Recipe file structure failed when inputting topping information for recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }
        for (ToppingType *currentTopping = toppingTypes; currentTopping != nullptr; currentTopping = currentTopping->next)
        {
            if (strcmp(currentTopping->name, toppingName) == 0)
            {
                current->topping = currentTopping;
                current->next = nullptr;
                break;
            }
        }
        if (i == 0)
            cout << current->topping->name << endl;
        if (current->topping == nullptr)
        {
            cout << "Error: Topping type not found for recipe No. " << i << "" << endl;
            exit(EXIT_FAILURE);
        }
        for (int j = 1; j < numToppings; j++)
        {
            current->next = new ToppingListNode;
            current = current->next;
            current->topping = nullptr;
            current->next = nullptr;
            if (!(recipe >> toppingName))
            {
                cout << "Error: Recipe file structure failed when inputting topping information for recipe No. " << i << "" << endl;
                exit(EXIT_FAILURE);
            }
            for (ToppingType *currentTopping = toppingTypes; currentTopping != nullptr; currentTopping = currentTopping->next)
            {
                if (strcmp(currentTopping->name, toppingName) == 0)
                {
                    current->topping = currentTopping;
                    current->next = nullptr;
                    break;
                }
            }
            if (current->topping == nullptr)
            {
                cout << "Error: Topping type not found for recipe No. " << i << "" << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    recipe.close();

    for (int i = 1; i < numRecipes; i++)
    {
        if (recipes[i]->id <= recipes[i - 1]->id)
        {
            cout << "Warning: Recipe IDs are not in increasing order" << endl;
        }
    }
}

// === Pretty Printing ===
/**
 * function print_ingredients prints the information of the ingredients database
 * @param teaTypes: a linked list of TeaType
 * @param milkTypes: a linked list of MilkType
 * @param toppingTypes: a linked list of ToppingType
 */
void print_ingredients(TeaType *teaTypes, MilkType *milkTypes, ToppingType *toppingTypes)
{
    cout << "===================================" << endl;
    cout << "===    Ingredients Database     ===" << endl;
    cout << "===================================" << endl;

    cout << "  --- Tea Types ---" << endl;
    if (teaTypes == nullptr)
    {
        cout << "    (None)" << endl;
    }
    else
    {
        for (TeaType *current = teaTypes; current != nullptr; current = current->next)
        {
            cout << "    - " << left << setw(MAX_STRING_LENGTH) << current->name
                 << " (Caffeine: " << current->caffeine << "mg)" << endl;
        }
    }
    cout << endl; // Add spacing

    cout << "  --- Milk Types ---" << endl;
    if (milkTypes == nullptr)
    {
        cout << "    (None)" << endl;
    }
    else
    {
        for (MilkType *current = milkTypes; current != nullptr; current = current->next)
        {
            cout << "    - " << left << setw(MAX_STRING_LENGTH) << current->name
                 << " (Calories: " << current->calories << "kcal, Stock: " << current->stock << ")" << endl; // Added stock
        }
    }
    cout << endl; // Add spacing

    cout << "  --- Topping Types ---" << endl;
    if (toppingTypes == nullptr)
    {
        cout << "    (None)" << endl;
    }
    else
    {
        for (ToppingType *current = toppingTypes; current != nullptr; current = current->next)
        {
            cout << "    - " << left << setw(MAX_STRING_LENGTH) << current->name
                 << " (Calories: " << current->calories << "kcal, Stock: " << current->stock << ")" << endl; // Added stock
        }
    }

    cout << "===================================" << endl;
    cout << "=== End of Ingredients Database ===" << endl;
    cout << "===================================" << endl
         << endl; // Add final spacing
}

/**
 * function print_drink prints the information of a drink recipe
 * @param drink: a pointer to the drink to be printed
 */
void print_drink(Drink *drink)
{
    cout << "  ---------------------------------" << endl;
    cout << "  Drink ID:     " << drink->id << endl;
    cout << "  Drink Name:   " << drink->name << endl;
    cout << "  Price:        $" << drink->price << endl; // Added price for completeness
    cout << "  Tea:          " << drink->tea->name << " (Caffeine: " << drink->tea->caffeine << "mg)" << endl;
    cout << "  Milk:         " << drink->milk->name << " (Calories: " << drink->milk->calories << "kcal)" << endl;
    cout << "  Toppings:" << endl;
    if (drink->toppings == nullptr)
    {
        cout << "    - None" << endl;
    }
    else
    {
        ToppingListNode *current = drink->toppings;
        while (current != nullptr)
        {
            cout << "    - " << current->topping->name << " (Calories: " << current->topping->calories << "kcal)" << endl;
            current = current->next;
        }
    }
    cout << "  ---------------------------------" << endl;
}

/**
 * function print_recipe prints the information of a drink recipe
 * @param recipes: a pointer to the dynamic array of drinks
 * @param numRecipes: the number of drinks in the recipe
 *
 */
void print_recipe(Drink **recipes, int numRecipes)
{
    cout << "===================================" << endl;
    cout << "===       Drink Recipes         ===" << endl;
    cout << "===================================" << endl;
    if (numRecipes == 0)
    {
        cout << "  (No recipes available)" << endl;
    }
    else
    {
        for (int i = 0; i < numRecipes; i++)
        {
            print_drink(recipes[i]);
            if (i < numRecipes - 1)
            {
                cout << endl; // Add space between drinks
            }
        }
    }
    cout << "===================================" << endl;
    cout << "===    End of Drink Recipes     ===" << endl;
    cout << "===================================" << endl
         << endl; // Add final spacing
}

/**
 * function print_order prints the information of an order
 * @param order: a pointer to the order to be printed
 * @param isPending: a boolean indicating if the order is pending (true) or completed (false)
 */
void print_order(Order *order, bool isPending = true)
{
    cout << "  *********************************" << endl;
    cout << "  Order Number: " << order->number << endl;
    cout << "  Drink Name:   " << order->drink->name << endl;
    cout << "  Calories:     " << order->calories << "kcal" << endl;
    cout << "  Caffeine:     " << order->caffeine << "mg" << endl;
    cout << "  Sugar Level:  ";
    switch (order->sugarLevel)
    {
    case None:
        cout << "None";
        break;
    case Half:
        cout << "Half";
        break;
    case Standard:
        cout << "Standard";
        break;
    case Extra:
        cout << "Extra";
        break;
    }
    cout << endl;
    cout << "  Ingredients:" << endl;
    cout << "    * Tea:    " << order->drink->tea->name << endl;
    cout << "    * Milk:   " << order->drink->milk->name << endl;
    if (isPending)
    {
        // Only show stock information for pending orders
        cout << "              (Stock: " << order->drink->milk->stock << (order->drink->milk->stock <= 0 ? " - Needs Replacement!" : "") << ")" << endl;
    }
    cout << "    * Toppings:" << endl;
    if (order->drink->toppings == nullptr)
    {
        cout << "      - None" << endl;
    }
    else
    {
        ToppingListNode *current = order->drink->toppings;
        while (current != nullptr)
        {
            cout << "      - " << current->topping->name;
            if (isPending)
            {
                // Only show stock information for pending orders
                cout << " (Stock: " << current->topping->stock << (current->topping->stock <= 0 ? " - Will be Skipped!" : "") << ")";
            }
            cout << endl;
            current = current->next;
        }
    }
    cout << "  *********************************" << endl;
}

/**
 * function print_pending_orders prints the information of the pending order list
 * @param pending: a pointer to the head of the pending order list
 */
void print_pending_orders(Order *pending)
{
    cout << "===================================" << endl;
    cout << "===       Pending Orders        ===" << endl;
    cout << "===================================" << endl;
    if (pending == nullptr)
    {
        cout << "  (No pending orders)" << endl;
    }
    else
    {
        Order *current = pending;
        while (current != nullptr)
        {
            print_order(current, true); // Explicitly stating these are pending orders
            if (current->next != nullptr)
            {
                cout << endl; // Add space between orders
            }
            current = current->next;
        }
    }
    cout << "===================================" << endl;
    cout << "===    End of Pending Orders    ===" << endl;
    cout << "===================================" << endl
         << endl; // Add final spacing
}

/**
 * function print_ready_orders prints the information of the completed order list
 * @param ready: an array of pointers to the head of the completed order list
 */
void print_ready_orders(Order *ready[])
{
    cout << "###################################" << endl;
    cout << "###      Completed Orders       ###" << endl;
    cout << "###################################" << endl;
    bool anyReady = false;
    for (int i = 0; i < 10; i++)
    {
        if (ready[i] != nullptr)
        { // Only print bucket if it has orders
            anyReady = true;
            cout << "--- Orders ending with digit " << i << " ---" << endl;
            Order *current = ready[i];
            while (current != nullptr)
            {
                print_order(current, false); // These are completed orders, so passing false
                if (current->next != nullptr)
                {
                    cout << endl; // Add space between orders within a bucket
                }
                current = current->next;
            }
            cout << "--- End of orders ending with " << i << " ---" << endl
                 << endl;
        }
    }
    if (!anyReady)
    {
        cout << "  (No completed orders)" << endl
             << endl;
    }
    cout << "###################################" << endl;
    cout << "### End of Completed Orders     ###" << endl;
    cout << "###################################" << endl
         << endl; // Add final spacing
}

/**
 * function print_replacement_cycle prints the information of the milk replacement cycle
 * @param replacement: a pointer to the head of the replacement list (can be nullptr)
 */
void print_replacement_cycle(ReplacementListNode *replacement)
{
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~    Milk Replacements        ~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    if (replacement == nullptr)
    {
        cout << "  (No milk replacements available)" << endl;
    }
    else
    {
        ReplacementListNode *current = replacement;
        cout << "  Start -> ";
        do
        {
            cout << current->milk->name
                 << " (Cal: " << current->milk->calories << ", Stock: " << current->milk->stock << ")";
            current = current->next;
            cout << (current == replacement ? " -- Loop" : " -> "); // Indicate loop or next item
        } while (current != replacement);
        cout << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~ End of Milk Replacements    ~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << endl; // Add final spacing
}

// helpers for create_receipe
// milk type and tea type both have name attributes , so overload the function check name
bool check_name_exist(TeaType *head, const char name[], TeaType *&extracted)
{
    for (TeaType *current = head; current; current = current->next)
    {
        if (strcmp(current->name, name) == 0)
        {
            extracted = current;
            return true;
        }
    }
    return false;
}

bool check_name_exist(MilkType *head, const char name[], MilkType *&extracted)
{
    for (MilkType *current = head; current; current = current->next)
    {
        if (strcmp(current->name, name) == 0)
        {
            extracted = current;
            return true;
        }
    }
    return false;
}

bool check_name_exist(ToppingType *head, const char name[], ToppingType *&extracted)
{
    for (ToppingType *current = head; current; current = current->next)
    {
        if (strcmp(current->name, name) == 0)
        {
            extracted = current;
            return true;
        }
    }
    return false;
}

bool check_name_exist(Drink **&recipes, const int length, const char name[], Drink *&extracted)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(recipes[i]->name, name) == 0)
        {
            extracted = recipes[i];
            return true;
        }
    }
    return false;
}
/**name and id checking
 * @param arrRecipes: the array of Drinks
 * @param insertion_index: give the index to insert after
 * @return true if has no duplication else false
 */
bool check_duplications(Drink **&arrRecipes, const int length, const char name[], const int id, int &insertion_index)
{
    insertion_index = -1;
    for (int i = 0; i < length; i++)
    {
        if ((strcmp(arrRecipes[i]->name, name) == 0) || arrRecipes[i]->id == id)
        {
            return false;
        }
        if (id > arrRecipes[i]->id)
        {
            insertion_index = i; // if i is -1 , means it needs to be inserted at front
        }
    }
    return true;
}
// === Tasks ===
/**
 * function create_recipe creates a new drink recipe with no toppings and adds it to the correct place in the recipes array
 *
 * @param name: the name of the drink
 * @param id: the id of the drink
 * @param price: the price of the drink
 * @param tea: the name of the tea type of the drink
 * @param milk: the name of the milk type of the drink
 * @param teaTypes: an array of pointers to TeaType
 * @param milkTypes: an array of pointers to MilkType
 * @param recipes: a pointer to the dynamic array of recipes
 * @param numRecipes: the number of drinks in the recipe - MISSING in original description
 *
 * @return true if the drink is successfully created and added.
 *         false if:
 *         - a drink with the same name already exists
 *         - a drink with the same id already exists
 *         - the specified tea type doesn't exist in teaTypes
 *         - the specified milk type doesn't exist in milkTypes
 */
bool create_recipe(const char name[], const int id, const int price, const char tea[], const char milk[], TeaType *teaTypes, MilkType *milkTypes, Drink **&recipes, int &numRecipes)
{
    // TODO
    // shallow copying: DO NOT MODIFY TeaType and MilkType
    // 1. check if tea and milk exist
    TeaType *to_this_tea = nullptr;
    MilkType *to_this_milk = nullptr;
    if (!(check_name_exist(teaTypes, tea, to_this_tea) && check_name_exist(milkTypes, milk, to_this_milk)))
    {
        return false;
    }
    // special case for num_receipes is 0
    if (numRecipes == 0)
    {
        recipes = new Drink *[1];
        Drink *NDrink = new Drink;

        NDrink->toppings = nullptr; // No Topping
        NDrink->price = price;
        NDrink->id = id;
        strcpy(NDrink->name, name);
        NDrink->tea = to_this_tea;
        NDrink->milk = to_this_milk;

        recipes[0] = NDrink;
        numRecipes = 1;
        return true;
    }
    // otherwise , check duplicate ID / drink names
    // do not forget to update length
    int insertion_index = -1;
    if (!(check_duplications(recipes, numRecipes, name, id, insertion_index)))
    {
        return false;
    }
    Drink *NDrink = new Drink;
    NDrink->toppings = nullptr;
    NDrink->price = price;
    NDrink->id = id;
    strcpy(NDrink->name, name);
    NDrink->tea = to_this_tea;
    NDrink->milk = to_this_milk;

    Drink **NArr = new Drink *[numRecipes + 1];
    int insert_pos = insertion_index + 1;
    for (int i = 0, j = 0; i < numRecipes + 1; i++)
    {
        if (i == insert_pos)
            NArr[i] = NDrink;
        else
            NArr[i] = recipes[j++];
    }

    delete[] recipes;
    recipes = NArr;
    numRecipes++;
    return true;
}

/**
 * function remove_recipe removes a drink recipe from the recipes array and
 * reallocates memory for the array to maintain contiguous elements
 *
 * @param drink: the name of the drink to be removed
 * @param recipes: a pointer to the dynamic array of recipes
 * @param numRecipes: the number of drinks in the recipe array (will be decremented if successful)
 *
 * @return true if the drink is successfully found and removed
 *         false if the drink with the specified name doesn't exist
 */
bool remove_recipe(const char drink[], Drink **&recipes, int &numRecipes)
{
    // TODO
    // IDEA: go over the array, if found, get new array (size - 1), and use the index to copy to new array.
    // delete old array and set the new header

    for (int i = 0; i < numRecipes; i++)
    {
        if (strcmp(recipes[i]->name, drink) == 0)
        {
            // succesfully locate the element
            Drink **NArr = nullptr;
            if (numRecipes > 1)
                NArr = new Drink *[numRecipes - 1];
            // copy to new array , i is the pos in old array to be ignored
            for (int j = 0, k = 0; j < numRecipes - 1; j++, k++)
            {
                if (k == i)
                    k++;
                NArr[j] = recipes[k];
            }
            // delete the i_th element
            delete recipes[i];

            delete[] recipes;
            recipes = NArr;
            numRecipes--;

            if (numRecipes == 0)
                recipes = nullptr;

            return true;
        }
    }

    return false;
}

// helpers for create_order
/*This function would not delete the source linked list*/
ToppingListNode *ll_copy(ToppingListNode *source_head)
{
    if (!source_head)
        return nullptr;
    ToppingListNode *new_head = new ToppingListNode;
    new_head->topping = source_head->topping;
    new_head->next = ll_copy(source_head->next);
    return new_head;
}

int caffeineSum(TeaType *tea)
{
    if (tea != nullptr)
    {
        return tea->caffeine;
    }
    return 0;
}

int calorieSum(MilkType *milk, ToppingListNode *toppings)
{
    int totalCalories = 0;

    if (milk != nullptr)
    {
        totalCalories += milk->calories;
    }

    ToppingListNode *currrent = toppings;
    while (currrent != nullptr)
    {
        if (currrent->topping != nullptr)
        {
            totalCalories += currrent->topping->calories;
        }
        currrent = currrent->next;
    }
    return totalCalories;
}
// === Region: Order Functions ===
/**
 * function create_order creates a new order and inserts it into the pending list
 * in ascending order of number
 *
 * @param pending: a pointer to the head of the pending order list
 * @param number: the order number
 * @param drink: the name of the drink to order
 * @param recipes: a pointer to the dynamic array of recipes
 * @param numRecipes: the number of drinks in the recipe
 * @param sugarLevel: the sugar level of the drink
 *
 * @return true if the order is successfully created and added to the pending list
 *         false if:
 *         - an order with the same number already exists in the pending list
 *         - the specified drink name doesn't exist in the recipes array
 */
bool create_order(Order *&pending, const int number, const char drink[], Drink **&recipes, const int numRecipes, const SugarLevel sugarLevel)
{
    // TODO
    // Validation of number and identify the insertion position if no same number occured
    Order *prev = nullptr; // Node before the insertion point
    Order *current = pending;

    // Traverse the list to find the correct insertion point and check for duplicates
    while (current != nullptr && current->number < number)
    {
        prev = current;
        current = current->next;
    }

    // Check for duplicate number
    if (current != nullptr && current->number == number)
    {
        return false; // Duplicate order number found
    }

    Drink *source = nullptr;
    if (!(check_name_exist(recipes, numRecipes, drink, source)))
        return false;

    // copy Drink , deep copy Topping list
    Drink *NDrink = new Drink;
    NDrink->id = -1; // differentiating it from the original recipe
    NDrink->milk = source->milk;
    NDrink->tea = source->tea;
    strcpy(NDrink->name, source->name);
    NDrink->price = source->price;
    NDrink->toppings = ll_copy(source->toppings);

    // caffine and calories calculations
    int caffiene = caffeineSum(NDrink->tea);
    int calories = calorieSum(NDrink->milk, NDrink->toppings);

    // create new order
    Order *NOrder = new Order;
    NOrder->number = number;
    NOrder->caffeine = caffiene;
    NOrder->calories = calories;
    NOrder->drink = NDrink;
    NOrder->sugarLevel = sugarLevel;
    NOrder->next = nullptr; // Initialize next pointer

    // insertion to order linked list
    if (prev == nullptr)
    {
        // Insert at the beginning (or list was empty)
        NOrder->next = pending;
        pending = NOrder;
    }
    else
    {
        // Insert after prev
        NOrder->next = prev->next; // which is 'current'
        prev->next = NOrder;
    }

    return true;
}

bool check_order_exist(Order *head, const int num, Order *&extracted)
{
    for (Order *pos = head; pos; pos = pos->next)
    {
        if (pos->number == num)
        {
            extracted = pos;
            return true;
        }
    }
    return false;
}

bool check_topping_exist(Order *order, const char name[], ToppingListNode *&insert_after_node)
{
    ToppingListNode *current = order->drink->toppings;
    ToppingListNode *prev = nullptr;

    while (current != nullptr)
    {
        int diff = strcmp(current->topping->name, name);
        if (diff == 0)
        {
            insert_after_node = nullptr;
            return false;
        }
        if (diff > 0)
        {
            break;
        }
        prev = current;
        current = current->next;
    }
    insert_after_node = prev;
    return true;
}
/**
 * function add_topping_to_order adds a topping to a pending order's drink
 * and adds the topping's calories to the order's calorie count.
 * The toppings are maintained in alphabetical order by name.
 *
 * @param number: the order number of the pending order
 * @param topping: the name of the topping to add
 * @param toppingTypes: a linked list storing the topping types
 * @param pending: a pointer to the head of the pending order list
 *
 * @return true if the topping is successfully added
 *         false if:
 *         - the pending list is empty
 *         - no order with the specified number exists
 *         - the order already has this topping
 *         - the specified topping doesn't exist in the toppingTypes list
 */
bool add_topping_to_order(const int number, const char topping[], ToppingType *toppingTypes, Order *pending)
{
    // TODO
    Order *to_this_order = nullptr;
    ToppingListNode *insert_pos = nullptr;
    ToppingType *insert_which = nullptr;

    // Validate order existence first
    if (!pending || !(check_order_exist(pending, number, to_this_order)))
    {
        return false;
    }
    if (!(check_name_exist(toppingTypes, topping, insert_which)))
    {
        return false;
    }
    if (!(check_topping_exist(to_this_order, topping, insert_pos)))
    {
        return false;
    }

    // Update order calories
    to_this_order->calories += insert_which->calories;

    // prepare new node
    ToppingListNode *node = new ToppingListNode;
    node->next = nullptr;
    node->topping = insert_which;

    if (insert_pos == nullptr)
    {
        // Insert at the beginning of the topping list
        node->next = to_this_order->drink->toppings;
        to_this_order->drink->toppings = node;
    }
    else
    {
        // Insert after insert_pos
        node->next = insert_pos->next;
        insert_pos->next = node;
    }

    return true;
}

bool find_exact_topping(ToppingListNode *head, const char name[], ToppingListNode *&to_delete, ToppingListNode *&prev)
{
    prev = nullptr;
    for (ToppingListNode *pos = head; pos; prev = pos, pos = pos->next)
    {
        if (strcmp(pos->topping->name, name) == 0)
        {
            to_delete = pos;
            return true;
        }
    }
    return false;
}

/**
 * function remove_topping_from_order removes a topping from a pending order's drink
 * and subtracts the topping's calories from the order's calorie count
 *
 * @param number: the order number of the pending order
 * @param topping: the name of the topping to remove
 * @param pending: a pointer to the head of the pending order list
 *
 * @return true if the topping is successfully found and removed
 *         false if:
 *         - no order with the specified number exists in the pending list
 *         - the order's drink has no toppings
 *         - the specified topping doesn't exist in the order's toppings list
 */
bool remove_topping_from_order(const int number, const char topping[], Order *pending)
{
    // TODO
    Order *to_this_order = nullptr;
    ToppingListNode *to_delete = nullptr;
    ToppingListNode *prev = nullptr;

    if (!(check_order_exist(pending, number, to_this_order)))
        return false;
    if (!(to_this_order->drink->toppings))
        return false;
    if (!(find_exact_topping(to_this_order->drink->toppings, topping, to_delete, prev)))
        return false;

    // calorie tracking
    to_this_order->calories -= to_delete->topping->calories;
    // make deletion
    if (to_this_order->drink->toppings == to_delete)
    {
        // head case
        to_this_order->drink->toppings = to_delete->next;
        delete to_delete;
        to_delete = nullptr;
        return true;
    }
    else
    {
        // otherwise
        prev->next = to_delete->next;
        delete to_delete;
        to_delete = nullptr;
        return true;
    }
    return true;
}

/**
 * function build_replacement_list builds a circular linked list of milk replacements
 * sorted by calories in ascending order. The function creates new ReplacementListNode objects
 * that reference the existing MilkType objects.
 * When milk types have equal calories, their relative order from the original list is preserved.
 *
 * @param milkTypes: a linked list of MilkType objects
 * @param replacement: a reference to the pointer that will point to the head of the circular replacement list
 *
 * @return true if the replacement cycle is successfully built
 *         false if the milkTypes list is empty (nullptr)
 */
bool build_replacement_list(MilkType *milkTypes, ReplacementListNode *&replacement)
{
    // TODO
    if (milkTypes == nullptr)
    {
        replacement = nullptr;
        return false;
    }
    if (milkTypes->next == nullptr)
    {
        replacement = new ReplacementListNode;
        replacement->milk = milkTypes;
        replacement->next = replacement;
        return true;
    }
    // more than 1 item
    // find length
    int length = 0;
    for (MilkType *pos = milkTypes; pos; pos = pos->next)
        length++;
    // create an array for sorting
    MilkType **arr = new MilkType *[length];
    int index = 0;
    for (MilkType *pos = milkTypes; pos; pos = pos->next, index++)
    {
        arr[index] = pos;
    }

    // sorting
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - 1 - i; j++)
        {
            if (arr[j]->calories > arr[j + 1]->calories)
            {
                MilkType *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // construct the replacement list
    ReplacementListNode *head = new ReplacementListNode{arr[0], nullptr};
    ReplacementListNode *pos = head;
    for (int i = 1; i < length; i++)
    {
        // create new node
        ReplacementListNode *node = new ReplacementListNode{arr[i], nullptr};
        pos->next = node;
        pos = node;
    }
    pos->next = head;
    replacement = head;

    delete[] arr;
    return true;
}

ReplacementListNode *search_target_milk(const MilkType *target, const ReplacementListNode *list)
{
    if (!list)
        return nullptr;
    const ReplacementListNode *pos = list;
    do
    {
        if (pos->milk == target)
            return const_cast<ReplacementListNode *>(pos);
        pos = pos->next;
    } while (pos != list);
    return nullptr;
}

/**
 * function find_available_in_replacement_circle finds a milk replacement with available stock
 * starting from the position after the target milk in the circular list, going around once.
 *
 * @param targetMilk: a pointer to the original milk type that needs replacement
 * @param replacement: a pointer to the head of the replacement circular list
 *
 * @return a pointer to the first available milk replacement if found.
 *         Returns nullptr if:
 *         - The replacement list is empty (nullptr)
 *         - The targetMilk is not found in the replacement list
 *         - No milk with stock > 0 is found after traversing the entire circular list once
 */
MilkType *find_available_in_replacement_circle(MilkType *targetMilk, ReplacementListNode *replacement)
{
    // TODO
    if (replacement == nullptr)
        return nullptr;
    ReplacementListNode *beginning = nullptr;
    if ((beginning = search_target_milk(targetMilk, replacement)) == nullptr)
        return nullptr;
    // loop to find the replacement
    ReplacementListNode *pos = beginning->next;
    while (pos != beginning)
    {
        if (pos->milk->stock > 0)
            return pos->milk;
        pos = pos->next;
    }
    return nullptr;
}

/*Go through the topping list once , remove if stock <= 0, record calorie change.*/
bool check_toppings(ToppingListNode *head, int &calorie_change)
{
    calorie_change = 0;
    bool isComplete = true;
    // Drink -> ToppingListNode -> toppings -> stock
    ToppingListNode **ppos = &head;
    while (*ppos)
    {
        if ((*ppos)->topping->stock <= 0)
        {
            calorie_change -= (*ppos)->topping->calories;
            ToppingListNode *to_delete = *ppos;
            *ppos = to_delete->next;

            delete to_delete;
            isComplete = false;
        }
        else
        {
            ppos = &((*ppos)->next);
        }
    }
    return isComplete;
}

void move_order(Order *&pending, Order *this_order, Order *ready[])
{
    Order *prev = nullptr, *pos = pending;
    while (pos && pos != this_order)
    {
        prev = pos;
        pos = pos->next;
    }
    if (prev == nullptr)
    {
        // head case
        pending = pos->next;
    }
    else
    {
        prev->next = pos->next;
    }
    pos->next = nullptr;

    int bucket = (pos->number) % 10;
    pos->next = ready[bucket];
    ready[bucket] = pos;
}

void minus_topping_stock(ToppingListNode *head)
{
    for (ToppingListNode *pos = head ; pos ; pos = pos->next)
    {
        pos->topping->stock -= 1;
    }
}
/**
 * Moves an order from the pending list to the ready list, handling ingredient availability
 *
 * This function:
 * 1. Finds the specified order in the pending list
 * 2. Checks each ingredient's availability
 * 3. Makes substitutions where possible (for milk)
 * 4. Skips unavailable toppings
 * 5. Moves the order to the appropriate ready list
 *
 * @param number: The unique number of the order to process
 * @param pending: Reference to the head of the pending order list
 * @param ready: Array of pointers to the heads of ready order lists (buckets)
 * @param replacement: Pointer to the head of the circular replacement list for milk
 *
 * @return ORDER_NOT_READY (0) if the order cannot be processed (not found or
 *                           required ingredients unavailable without substitution)
 *         ORDER_READY_PERFECT (1) if the order is processed with all original ingredients
 *         ORDER_READY_MODIFIED (2) if the order is processed with substitutions or omissions
 */
int get_order_ready(const int number, Order *&pending, Order *ready[], ReplacementListNode *replacement)
{
    // TODO
    Order *this_order = nullptr;
    if (!pending)
        return 0;
    if (!check_order_exist(pending, number, this_order))
        return 0;
    // check if milk is avaliable
    int milk_stock = this_order->drink->milk->stock;
    /*
    Two cases:
        - milk_stock > 0, this milk is available.
          Further check toppings, and monitor calories
            * All toppings available , process and return 1
            * Not all availbale, remove, process and return 2
        - milk_stock <= 0, milk stock is unavailable,
          Further check replacement and monitor calories
            * No milk replacement, return 0
            * Has replacement:
                - Toppings available, process and return 2
                - Toppings unavailable , preocess and return 2.
    Helper function I need:
        * bool check_toppings (head , int &calorie_change)
            - go through topping linked list , remove if stock <= 0, record in calorie change
            -  return true if all toppings is ok , false otherwise
    */
    if (milk_stock > 0)
    {
        // -1 the milk stock
        this_order->drink->milk->stock -= 1;
        // Process order when milk is available
        int calorie_change = 0;
        bool isComplete = check_toppings(this_order->drink->toppings, calorie_change);
        // change calorie
        this_order->calories += calorie_change;
        if (isComplete)
        {
            // All toppings available
            // TODO: remove from pending list and add to ready, maybe a helper function here
            minus_topping_stock(this_order->drink->toppings);
            move_order(pending, this_order, ready);
            return 1;
        }
        else
        {
            // Not all available
            // call remove from pending list and add to ready
            minus_topping_stock(this_order->drink->toppings);
            move_order(pending, this_order, ready);
            return 2;
        }
    }
    else
    {
        // Process order when milk is unavailable or replacement is needed
        MilkType *target = this_order->drink->milk;
        MilkType *milkReplacement = find_available_in_replacement_circle(target, replacement);
        if (milkReplacement == nullptr)
            return 0;
        else
            this_order->drink->milk = milkReplacement;
        // minus 1 milk replacement stock
        milkReplacement->stock -= 1;
        // Adjust calories
        this_order->calories -= target->calories;
        this_order->calories += milkReplacement->calories;
        // check toppings
        int calorie_change = 0;
        check_toppings(this_order->drink->toppings, calorie_change);
        this_order->calories += calorie_change;
        // topping stock -1
        minus_topping_stock(this_order->drink->toppings);
        // func call
        move_order(pending, this_order, ready);
        return 2;
    }
    return 0;
}

// === Region: Destructors ===
/**
 * function delete_database deletes the linked lists storing the ingredients database
 *
 * @param teaTypes: an array of pointers to TeaType
 * @param milkTypes: an array of pointers to MilkType
 * @param toppingTypes: an array of pointers to ToppingType
 */
void delete_database(TeaType *&teaTypes, MilkType *&milkTypes, ToppingType *&toppingTypes)
{
    // TODO
    TeaType *Tpos = teaTypes;
    while (Tpos)
    {
        TeaType *next = Tpos->next;
        delete Tpos;
        Tpos = next;
    }
    // set it to nullptr
    teaTypes = nullptr;

    MilkType *Mpos = milkTypes;
    while (Mpos)
    {
        MilkType *next = Mpos->next;
        delete Mpos;
        Mpos = next;
    }
    milkTypes = nullptr;

    ToppingType *Topos = toppingTypes;
    while (Topos)
    {
        ToppingType *next = Topos->next;
        delete Topos;
        Topos = next;
    }
    toppingTypes = nullptr;
}

/**
 * function delete_recipe deletes the dynamic array storing the drink recipes
 *
 * @param recipes: a pointer to the dynamic array of drinks
 * @param numRecipes: the number of drinks in the recipe
 */
void delete_recipe(Drink **&recipes, int numRecipes)
{
    // TODO
    for (int i = 0; i < numRecipes; i++)
    {
        ToppingListNode *pos = recipes[i]->toppings;
        while (pos)
        {
            ToppingListNode *next = pos->next;
            delete pos;
            pos = next;
        }
        pos = nullptr;

        delete recipes[i];
    }

    delete[] recipes;
    recipes = nullptr;
}

/**
 * function delete_pending_orders deletes the linked lists storing the pending orders
 *
 * @param pending: a pointer to the head of the pending order list
 */
void delete_pending_orders(Order *&pending)
{
    // TODO
    Order *pos = pending;
    while (pos)
    {
        Order *next = pos->next;
        // delete pos->drink->topping list , drink , order
        ToppingListNode *toppingPos = pos->drink->toppings;
        while (toppingPos)
        {
            ToppingListNode *next = toppingPos->next;
            delete toppingPos;
            toppingPos = next;
        }

        delete pos->drink;
        delete pos;
        pos = next;
    }
    pending = nullptr;
}

/**
 * function delete_ready_orders deletes the linked lists storing the ready orders
 *
 * @param ready: an array of pointers to the head of the ready order list
 */
void delete_ready_orders(Order *ready[])
{
    // TODO
    for (int i = 0; i < 10; i++)
    {
        delete_pending_orders(ready[i]);
    }
}

/**
 * function delete_replacement_circle deletes the circular linked list of milk replacements
 *
 * @param replacement: a pointer to the head of the replacement list
 */
void delete_replacement_circle(ReplacementListNode *&replacement)
{
    // TODO
    if (replacement == nullptr)
        return;

    ReplacementListNode *pos = replacement->next;

    while (pos != replacement)
    {
        ReplacementListNode *next = pos->next;
        delete pos;
        pos = next;
    }
    delete replacement;
    replacement = nullptr;
}
