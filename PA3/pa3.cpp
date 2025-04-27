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
bool check_name_exist(TeaType *head , const char name[] , TeaType *&extracted)
{
    for (TeaType* current = head ; current ; current = current->next)
    {
        if (strcmp(current->name , name) == 0)
        {
            extracted = current;
            return true;
        }
    }
    return false;
}

bool check_name_exist(MilkType *head , const char name[] , MilkType *&extracted)
{
    for (MilkType* current = head ; current ; current = current->next)
    {
        if (strcmp(current->name , name) == 0)
        {
            extracted = current;
            return true;
        }
    }
    return false;
}

bool check_name_exist(Drink **&recipes , const int length , const char name[] , Drink *&extracted)
{
    for (int i = 0 ; i < length ; i++)
    {
        if (strcmp(recipes[i]->name , name) == 0)
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
    for (int i = 0 ; i < length ; i++)
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
    if (!(check_name_exist(teaTypes, tea , to_this_tea) && check_name_exist(milkTypes , milk , to_this_milk)))
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
        strcpy(NDrink->name , name);
        NDrink->tea = to_this_tea;
        NDrink->milk = to_this_milk;        

        recipes[0] = NDrink;
        numRecipes = 1;
        return true;
    }
    // otherwise , check duplicate ID / drink names
    // do not forget to update length
    int insertion_index = -1;
    if (!(check_duplications(recipes , numRecipes , name , id , insertion_index)))
    {
        return false;
    }
    Drink *NDrink = new Drink;
    NDrink->toppings = nullptr;
    NDrink->price = price;
    NDrink->id = id;
    strcpy(NDrink->name , name);
    NDrink->tea = to_this_tea;
    NDrink->milk = to_this_milk;

    Drink **NArr = new Drink *[numRecipes + 1];
    int insert_pos = insertion_index + 1;
    for (int i = 0 , j = 0 ; i < numRecipes + 1 ; i++)
    {
        if (i = insert_pos)
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

    for (int i = 0 ; i < numRecipes ; i++)
    {
        if (strcmp(recipes[i]->name , drink) == 0)
        {
            // succesfully locate the element
            Drink **NArr = nullptr;
            if (numRecipes > 1)
                NArr = new Drink *[numRecipes - 1];
            // copy to new array , i is the pos in old array to be ignored
            for (int j = 0 , k = 0 ; j < numRecipes - 1 ; j++ , k++)
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
ToppingListNode* ll_copy(ToppingListNode *source_head)
{
    if (!source_head)
        return nullptr;
    ToppingListNode *new_head = new ToppingListNode;
    new_head->topping = source_head->topping;
    new_head->next = ll_copy(source_head->next);
    return new_head;
}

int caffeineSum(TeaType *head)
{
    int sum = 0;
    for (TeaType *current = head ; current ; current = current->next)
    {
        sum += current->caffeine;
    }
    return sum;
}

int calorieSum(MilkType *M_head , ToppingListNode *T_head)
{
    //stop condition
    if (M_head == nullptr && T_head == nullptr)
        return 0;
    else if (M_head == nullptr || T_head == nullptr)
    {
        if (M_head == nullptr)
            return T_head->topping->calories + calorieSum(nullptr , T_head->next);
        else
            return M_head->calories + calorieSum(M_head->next , nullptr);
    }
    // recursion
    return M_head->calories + T_head->topping->calories + calorieSum(M_head->next , T_head->next);
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
    Order *insertion_place = nullptr; 
    /*
    if insertion_place is nullptr , then it's front insertion
    elif is not nullptr , middle insertion or 
        if , insertion_place->next = nullptr , end insertion
    */
    for (Order *current = pending ; current ; current = current->next)
    {
        if (current->number == number)
            return false;
        if (number > current->number)
            insertion_place = current;
    }
    Drink *source = nullptr;
    if (!(check_name_exist(recipes , numRecipes , drink , source)))
        return false;
    
    // copy Drink , deep copy Topping list
    Drink *NDrink = new Drink;
    NDrink->id = source->id;
    NDrink->milk = source->milk;
    NDrink->tea = source->tea;
    strcpy(NDrink->name , source->name);
    NDrink->price = source->price;
    NDrink->toppings = ll_copy(source->toppings);
    
    // caffine and calories calculations
    int caffiene = caffeineSum(NDrink->tea);
    int calories = calorieSum(NDrink->milk , NDrink->toppings);
    
    // create new order 
    Order *NOrder = new Order;
    NOrder->number = number;
    NOrder->caffeine;
    

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
    return false; // you many remove this line if you want
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
    return false; // you many remove this line if you want
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
    return false; // you many remove this line if you want
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
    return nullptr; // you many remove this line if you want
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
    return 0; // you many remove this line if you want
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
    return; // you many remove this line if you want
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
    return; // you many remove this line if you want
}

/**
 * function delete_pending_orders deletes the linked lists storing the pending orders
 *
 * @param pending: a pointer to the head of the pending order list
 */
void delete_pending_orders(Order *&pending)
{
    // TODO
    return; // you many remove this line if you want
}

/**
 * function delete_ready_orders deletes the linked lists storing the ready orders
 *
 * @param ready: an array of pointers to the head of the ready order list
 */
void delete_ready_orders(Order *ready[])
{
    // TODO
    return; // you many remove this line if you want
}

/**
 * function delete_replacement_circle deletes the circular linked list of milk replacements
 *
 * @param replacement: a pointer to the head of the replacement list
 */
void delete_replacement_circle(ReplacementListNode *&replacement)
{
    // TODO
    return; // you many remove this line if you want
}
