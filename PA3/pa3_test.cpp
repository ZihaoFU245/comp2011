#include "pa3.cpp"
#include <cstdlib>
#include <string_view>
using namespace std;

// Special template for handling pointers (e.g., for boolean checks)
void print_result_impl(const char *expression_str, bool result)
{   
        cout << boolalpha;
        cout << expression_str  << "-> " << result << endl;
}

template <typename T>
void print_result_impl(const char *expression_str, T result)
{   
        cout << expression_str << "-> " << result << endl;
}

#define print_result(expression) print_result_impl(#expression, (expression))



void test0(){
    cout << "--- test0 ---" << endl;
}

void test1()
{
    cout << "--- test1 ---" << endl;
    const char *database_path = "data//1-database.txt";
    const char *recipe_path = "data//1-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_recipe("CheesyGrapes", 1, 36, "GrapeTea", "WholeMilk", teaTypes, milkTypes, recipes, numRecipes));
    print_result(create_recipe("CheesyGrapes", 1, 36, "GrapeTea", "WholeMilk", teaTypes, milkTypes, recipes, numRecipes));
    print_recipe(recipes, numRecipes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}


void test2()
{
    cout << "--- test2 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_recipe("CheesyGrapes", 4, 36, "GrapeTea", "WholeMilk", teaTypes, milkTypes, recipes, numRecipes));
    print_recipe(recipes, numRecipes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test3()
{
    cout << "--- test3 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_recipe("CheesyGrapes", 1, 36, "GrapeTea", "WholeMilk", teaTypes, milkTypes, recipes, numRecipes));
    print_recipe(recipes, numRecipes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test4()
{
    cout << "--- test4 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_recipe("CheesyGrapes", 3, 36, "GrapeTea", "WholeMilk", teaTypes, milkTypes, recipes, numRecipes));
    print_result(create_recipe("CheesyGrapes", 4, 36, "GrapeTea", "UNKNOWN", teaTypes, milkTypes, recipes, numRecipes));

    print_recipe(recipes, numRecipes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test5()
{
    cout << "--- test5 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(remove_recipe("CoconutMilkTea", recipes, numRecipes));
    print_recipe(recipes, numRecipes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test6()
{
    cout << "--- test6 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(remove_recipe("GreenTeaLatte", recipes, numRecipes));
    print_recipe(recipes, numRecipes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}


void test7()
{
    cout << "--- test7 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(remove_recipe("CheesyGrape", recipes, numRecipes));
    print_result(remove_recipe("CheesyGrape", recipes, numRecipes));
    print_recipe(recipes, numRecipes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test8()
{
    cout << "--- test8 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test9()
{
    cout << "--- test9 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_result(create_order(pending, 3, "BlackTeaLatte", recipes, numRecipes, None));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test10()
{
    cout << "--- test10 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_result(create_order(pending, 3, "BlackTeaLatte", recipes, numRecipes, None));
    print_result(create_order(pending, 5, "CoconutMilkTea", recipes, numRecipes, Half));
    print_result(create_order(pending, 4, "CoconutMilkTea", recipes, numRecipes, Standard));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test11()
{
    cout << "--- test11 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_result(create_order(pending, 3, "BlackTeaLatte", recipes, numRecipes, None));
    print_result(create_order(pending, 5, "CoconutMilkTea", recipes, numRecipes, Half));
    print_result(create_order(pending, 1, "UnknownMilkTea", recipes, numRecipes, Standard));
    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test12()
{
    cout << "--- test12 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "RedBean", toppingTypes, pending));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test13()
{
    cout << "--- test13 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "RedBean", toppingTypes, pending));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "CheeseFoam", toppingTypes, pending));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test14()
{
    cout << "--- test14 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "RedBean", toppingTypes, pending));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "GG", toppingTypes, pending));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test15()
{
    cout << "--- test15 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "RedBean", toppingTypes, pending));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "CheeseFoam", toppingTypes, pending));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "MangoPoppingBoba", toppingTypes, pending));
    print_pending_orders(pending);
    print_result(remove_topping_from_order(2, "RedBean", pending));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test16()
{
    cout << "--- test16 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(create_order(pending, 2, "GreenTeaLatte", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "RedBean", toppingTypes, pending));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "CheeseFoam", toppingTypes, pending));
    print_pending_orders(pending);
    print_result(add_topping_to_order(2, "MangoPoppingBoba", toppingTypes, pending));
    print_pending_orders(pending);
    print_result(remove_topping_from_order(2, "MangoPoppingBoba", pending));
    print_pending_orders(pending);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test17()
{
    cout << "--- test17 ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_recipe(recipes, numRecipes);
    print_result(remove_recipe("CheesyGrape", recipes, numRecipes));
    print_result(remove_recipe("CheesyGrape", recipes, numRecipes));
    print_recipe(recipes, numRecipes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test18()
{
    cout << "--- test18 ---" << endl;
    const char *database_path = "data//3-database.txt";
    const char *recipe_path = "data//3-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_result(build_replacement_list(milkTypes, milkReplacements));
    print_replacement_cycle(milkReplacements);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}


void test19()
{
    cout << "--- test19 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));

    print_ingredients(teaTypes, milkTypes, toppingTypes);

    print_result(create_order(pending, 1, "recipe1", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    print_result(get_order_ready(1, pending, ready, milkReplacements));
    print_ready_orders(ready);

    print_ingredients(teaTypes, milkTypes, toppingTypes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test20(){
    cout << "--- test20 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path =   "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order* pending = nullptr;
    Order* ready[10] = {nullptr};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));
    
    print_replacement_cycle(milkReplacements);
    print_ingredients(teaTypes, milkTypes, toppingTypes);

    print_result(create_order(pending, 1, "recipe1", recipes, numRecipes, Standard));
    print_result(create_order(pending, 2, "recipe1", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    print_result(get_order_ready(1, pending, ready, milkReplacements));
    print_result(get_order_ready(2, pending, ready, milkReplacements));
    print_ready_orders(ready);

    print_ingredients(teaTypes, milkTypes, toppingTypes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test21()
{
    cout << "--- test21 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));

    print_replacement_cycle(milkReplacements);
    print_ingredients(teaTypes, milkTypes, toppingTypes);

    for (int i=1; i<=3; i++)
        print_result(create_order(pending, i, "recipe3", recipes, numRecipes, Standard));
    for (int i=1; i<=6; i++)
        print_result(create_order(pending, i*4 + 3, "recipe5", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    for (int i=1; i<=3; i++)
        print_result(get_order_ready(i, pending, ready, milkReplacements));
    for (int i=1; i<=6; i++)
        print_result(get_order_ready(i*4 + 3, pending, ready, milkReplacements));
    print_ready_orders(ready);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test22()
{
    cout << "--- test22 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));

    for (int i=1; i<=100; i++)
        create_order(pending, i, "recipe3", recipes, numRecipes, Standard);

    for (int i=1; i<=100; i++)
        print_result(get_order_ready(i, pending, ready, milkReplacements));
    print_ready_orders(ready);
    print_replacement_cycle(milkReplacements);
    

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test23()
{
    cout << "--- test23 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    build_replacement_list(milkTypes, milkReplacements);

    for (int i=1; i<=2; i++){
        create_order(pending, i, "recipe3", recipes, numRecipes, Standard);
        print_result(add_topping_to_order(i, "Topping1", toppingTypes, pending));
    }
    print_pending_orders(pending);
    for (int i=1; i<=2; i++)
        print_result(get_order_ready(i, pending, ready, milkReplacements));
    print_ready_orders(ready);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test24()
{
    cout << "--- test24 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    build_replacement_list(milkTypes, milkReplacements);

    create_order(pending, 1, "recipe1", recipes, numRecipes, None);
    create_order(pending, 2, "recipe2", recipes, numRecipes, Standard);
    create_order(pending, 3, "recipe3", recipes, numRecipes, Standard);
    create_order(pending, 4, "recipe4", recipes, numRecipes, Standard);
    create_order(pending, 5, "recipe5", recipes, numRecipes, Standard);
    create_order(pending, 6, "recipe6", recipes, numRecipes, Standard);
    create_order(pending, 7, "recipe7", recipes, numRecipes, Standard);
    create_order(pending, 8, "recipe8", recipes, numRecipes, Standard);

    print_result(get_order_ready(1, pending, ready, milkReplacements));
    print_result(get_order_ready(2, pending, ready, milkReplacements));
    print_result(get_order_ready(3, pending, ready, milkReplacements));
    print_result(get_order_ready(4, pending, ready, milkReplacements));
    print_result(get_order_ready(5, pending, ready, milkReplacements));
    print_result(get_order_ready(6, pending, ready, milkReplacements));
    print_result(get_order_ready(7, pending, ready, milkReplacements));
    print_result(get_order_ready(8, pending, ready, milkReplacements));
    print_ready_orders(ready);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test25()
{
    cout << "--- test25 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    build_replacement_list(milkTypes, milkReplacements);

    create_order(pending, 1, "recipe1", recipes, numRecipes, Standard);
    create_order(pending, 2, "recipe2", recipes, numRecipes, Standard);
    create_order(pending, 3, "recipe3", recipes, numRecipes, Standard);
    create_order(pending, 4, "recipe4", recipes, numRecipes, Standard);
    create_order(pending, 11, "recipe5", recipes, numRecipes, Standard);
    create_order(pending, 12, "recipe6", recipes, numRecipes, Standard);
    create_order(pending, 13, "recipe7", recipes, numRecipes, Standard);
    create_order(pending, 14, "recipe8", recipes, numRecipes, Standard);

    print_result(get_order_ready(1, pending, ready, milkReplacements));
    print_result(get_order_ready(2, pending, ready, milkReplacements));
    print_result(get_order_ready(3, pending, ready, milkReplacements));
    print_result(get_order_ready(4, pending, ready, milkReplacements));
    print_result(get_order_ready(11, pending, ready, milkReplacements));
    print_result(get_order_ready(12, pending, ready, milkReplacements));
    print_result(get_order_ready(13, pending, ready, milkReplacements));
    print_result(get_order_ready(14, pending, ready, milkReplacements));
    print_ingredients(teaTypes, milkTypes, toppingTypes);
    print_ready_orders(ready);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test26()
{
    cout << "--- test26 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));

    print_result(create_order(pending, 1, "recipe1", recipes, numRecipes, Standard));
    print_result(create_order(pending, 2, "recipe2", recipes, numRecipes, Standard));
    print_result(create_order(pending, 3, "recipe3", recipes, numRecipes, Standard));
    print_result(create_order(pending, 4, "recipe4", recipes, numRecipes, Standard));
    print_result(create_order(pending, 11, "recipe5", recipes, numRecipes, Standard));
    print_result(create_order(pending, 12, "recipe6", recipes, numRecipes, Standard));
    print_result(create_order(pending, 13, "recipe7", recipes, numRecipes, Standard));
    print_result(create_order(pending, 14, "recipe8", recipes, numRecipes, Standard));
    print_pending_orders(pending);
    print_result(get_order_ready(1, pending, ready, milkReplacements));
    print_result(get_order_ready(3, pending, ready, milkReplacements));
    print_result(get_order_ready(4, pending, ready, milkReplacements));
    print_result(get_order_ready(2, pending, ready, milkReplacements));
    print_result(get_order_ready(11, pending, ready, milkReplacements));
    print_result(get_order_ready(12, pending, ready, milkReplacements));
    print_result(get_order_ready(13, pending, ready, milkReplacements));
    print_result(get_order_ready(14,pending ,ready ,milkReplacements));
    print_ready_orders(ready);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test27()
{
    cout << "--- test27 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));

    print_result(create_order(pending, 1, "recipe1", recipes, numRecipes, Standard));
    print_result(create_order(pending, 2, "recipe2", recipes, numRecipes, Standard));
    print_result(create_order(pending, 3, "recipe3", recipes, numRecipes, Standard));
    print_result(create_order(pending, 4, "recipe4", recipes, numRecipes, Standard));
    print_result(create_order(pending, 11, "recipe5", recipes, numRecipes, Standard));
    print_result(create_order(pending, 12, "recipe6", recipes, numRecipes, Standard));
    print_result(create_order(pending, 13, "recipe7", recipes, numRecipes, Standard));
    print_result(create_order(pending, 14, "recipe8", recipes, numRecipes, Standard));

    print_result(get_order_ready(1,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(2,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(3,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(4,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(12,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(13,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(14,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(11,pending ,ready ,milkReplacements ));
    print_ready_orders(ready);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

void test28()
{
    cout << "--- test28 ---" << endl;
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));

    create_order(pending, 1, "recipe1", recipes, numRecipes, Standard);
    create_order(pending, 2, "recipe2", recipes, numRecipes, Standard);
    create_order(pending, 3, "recipe3", recipes, numRecipes, Standard);
    create_order(pending, 4, "recipe4", recipes, numRecipes, Standard);
    create_order(pending, 11,"recipe5", recipes,numRecipes ,Standard );
    create_order(pending ,12,"recipe6", recipes,numRecipes ,Standard );
    create_order(pending ,13,"recipe7", recipes,numRecipes ,Standard );
    create_order(pending ,14,"recipe8", recipes,numRecipes ,Standard );

    print_result(get_order_ready(14,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(13,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(12,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(11,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(1,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(2,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(3,pending ,ready ,milkReplacements ));
    print_result(get_order_ready(4,pending ,ready ,milkReplacements ));
    print_ready_orders(ready );

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

// Test case focusing on remove_recipe edge cases
void test29()
{
    cout << "--- test29: remove_recipe edge cases ---" << endl;
    const char *database_path = "data//2-database.txt"; // Use a simple database
    const char *recipe_path = "data//2-recipe.txt";     // Use a simple recipe set

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    cout << "Initial recipes:" << endl;
    print_recipe(recipes, numRecipes);

    // Add a recipe with toppings to test memory leak fix
    print_result(create_recipe("TestDrinkWithToppings", 5, 40, "GreenTea", "WholeMilk", teaTypes, milkTypes, recipes, numRecipes));
    // Manually add toppings to the new recipe (since create_recipe doesn't add them)
    // Find the recipe first
    Drink* testDrink = nullptr;
    for(int i=0; i<numRecipes; ++i) {
        if(strcmp(recipes[i]->name, "TestDrinkWithToppings") == 0) {
            testDrink = recipes[i];
            break;
        }
    }
    if(testDrink) {
        ToppingType* topping1 = nullptr;
        ToppingType* topping2 = nullptr;
        check_name_exist(toppingTypes, "RedBean", topping1);
        check_name_exist(toppingTypes, "CheeseFoam", topping2);
        if(topping1) {
             testDrink->toppings = new ToppingListNode{topping1, nullptr};
             if(topping2) {
                 testDrink->toppings->next = new ToppingListNode{topping2, nullptr};
             }
        }
    }
    cout << "After adding TestDrinkWithToppings:" << endl;
    print_recipe(recipes, numRecipes);


    print_result(remove_recipe("NonExistentRecipe", recipes, numRecipes)); // Test remove non-existent
    print_result(remove_recipe("GreenTeaLatte", recipes, numRecipes));     // Test remove first
    cout << "After removing GreenTeaLatte:" << endl;
    print_recipe(recipes, numRecipes);

    print_result(remove_recipe("TestDrinkWithToppings", recipes, numRecipes)); // Test remove recipe with toppings (check for leaks offline)
    cout << "After removing TestDrinkWithToppings:" << endl;
    print_recipe(recipes, numRecipes);

    print_result(remove_recipe("CoconutMilkTea", recipes, numRecipes));    // Test remove last (after previous removals)
     cout << "After removing CoconutMilkTea:" << endl;
    print_recipe(recipes, numRecipes);

    // Remove remaining recipe
    print_result(remove_recipe("BlackTeaLatte", recipes, numRecipes));
    cout << "After removing BlackTeaLatte (should be empty):" << endl;
    print_recipe(recipes, numRecipes);
    print_result(remove_recipe("BlackTeaLatte", recipes, numRecipes)); // Test remove from empty

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes); // Should be safe even if recipes is nullptr
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

// Test case focusing on add/remove topping edge cases
void test30()
{
    cout << "--- test30: add/remove topping edge cases ---" << endl;
    const char *database_path = "data//2-database.txt";
    const char *recipe_path = "data//2-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);

    print_result(create_order(pending, 10, "GreenTeaLatte", recipes, numRecipes, Standard)); // Order with no initial toppings
    print_pending_orders(pending);

    // Add toppings, testing alphabetical order and duplicates
    print_result(add_topping_to_order(10, "RedBean", toppingTypes, pending));          // Add first
    print_result(add_topping_to_order(10, "CheeseFoam", toppingTypes, pending));       // Add alphabetically before RedBean
    print_result(add_topping_to_order(10, "MangoPoppingBoba", toppingTypes, pending)); // Add alphabetically after CheeseFoam, before RedBean
    print_pending_orders(pending);

    print_result(add_topping_to_order(10, "RedBean", toppingTypes, pending));          // Try adding duplicate
    print_result(add_topping_to_order(10, "NonExistentTopping", toppingTypes, pending));// Try adding non-existent topping type
    print_result(add_topping_to_order(99, "RedBean", toppingTypes, pending));          // Try adding to non-existent order
    print_pending_orders(pending); // Should be unchanged from previous print

    // Remove toppings, testing different positions and non-existent
    print_result(remove_topping_from_order(10, "CheeseFoam", pending));       // Remove first alphabetically
    print_pending_orders(pending);
    print_result(remove_topping_from_order(10, "RedBean", pending));          // Remove last alphabetically
    print_pending_orders(pending);
    print_result(remove_topping_from_order(10, "NonExistentTopping", pending));// Try removing non-existent topping from order
    print_result(remove_topping_from_order(10, "MangoPoppingBoba", pending)); // Remove the only remaining topping
    print_pending_orders(pending);
    print_result(remove_topping_from_order(10, "MangoPoppingBoba", pending)); // Try removing from order with no toppings
    print_result(remove_topping_from_order(99, "RedBean", pending));          // Try removing from non-existent order

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

// Test case focusing on get_order_ready edge cases
void test31()
{
    cout << "--- test31: get_order_ready edge cases ---" << endl;
    // Use database 5 which has stock variations
    const char *database_path = "data//5-database.txt";
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements)); // Build replacement list

    // Initial state
    print_ingredients(teaTypes, milkTypes, toppingTypes);
    print_replacement_cycle(milkReplacements);

    // Order 1: Recipe 1 (Tea1, Milk1(stock=1), Topping1(stock=1)) - Should be perfect
    print_result(create_order(pending, 1, "recipe1", recipes, numRecipes, Standard));
    // Order 2: Recipe 3 (Tea3, Milk3(stock=0), Topping3(stock=1)) - Needs milk replacement (Milk4), topping ok
    print_result(create_order(pending, 2, "recipe3", recipes, numRecipes, Standard));
    // Order 3: Recipe 5 (Tea5, Milk5(stock=1), Topping5(stock=0)) - Milk ok, topping skipped
    print_result(create_order(pending, 3, "recipe5", recipes, numRecipes, Standard));
    // Order 4: Recipe 7 (Tea7, Milk7(stock=0), Topping7(stock=0)) - Needs milk replacement (Milk8), topping skipped
    print_result(create_order(pending, 4, "recipe7", recipes, numRecipes, Standard));
    // Order 5: Recipe 1 again, Milk1 stock is now 0. Needs replacement (Milk2)
    print_result(create_order(pending, 5, "recipe1", recipes, numRecipes, Standard));
    // Order 6: Recipe 3 again, Milk3 stock is 0, Milk4 stock is now 0. Needs replacement (Milk5)
    print_result(create_order(pending, 6, "recipe3", recipes, numRecipes, Standard));
     // Order 7: Recipe 9 (Tea9, Milk9(stock=0)) - Milk9 is not in replacement list (assuming it's not in db 5) or no replacement has stock. Should fail.
    // Let's assume Milk9 exists but has stock 0 and no replacement available after others are used.
    // We'll simulate this by trying to process an order that exhausts replacements.
    // Let's use recipe 3 again until Milk5 runs out. Milk5 stock = 1 initially. Order 6 used it.
    print_result(create_order(pending, 7, "recipe3", recipes, numRecipes, Standard)); // This should fail later if Milk5 is out.

    print_pending_orders(pending);

    cout << "Processing orders..." << endl;
    print_result(get_order_ready(1, pending, ready, milkReplacements)); // Expect 1 (Perfect)
    print_ingredients(teaTypes, milkTypes, toppingTypes); print_ready_orders(ready);
    print_result(get_order_ready(2, pending, ready, milkReplacements)); // Expect 2 (Modified - Milk3 replaced by Milk4)
    print_ingredients(teaTypes, milkTypes, toppingTypes); print_ready_orders(ready);
    print_result(get_order_ready(3, pending, ready, milkReplacements)); // Expect 2 (Modified - Topping5 skipped)
    print_ingredients(teaTypes, milkTypes, toppingTypes); print_ready_orders(ready);
    print_result(get_order_ready(4, pending, ready, milkReplacements)); // Expect 2 (Modified - Milk7 replaced by Milk8, Topping7 skipped)
    print_ingredients(teaTypes, milkTypes, toppingTypes); print_ready_orders(ready);
    print_result(get_order_ready(5, pending, ready, milkReplacements)); // Expect 2 (Modified - Milk1 replaced by Milk2)
    print_ingredients(teaTypes, milkTypes, toppingTypes); print_ready_orders(ready);
    print_result(get_order_ready(6, pending, ready, milkReplacements)); // Expect 2 (Modified - Milk3 replaced by Milk5)
    print_ingredients(teaTypes, milkTypes, toppingTypes); print_ready_orders(ready);
    print_result(get_order_ready(7, pending, ready, milkReplacements)); // Expect 0 (No replacement for Milk3 as Milk4, Milk5 are out)
    print_ingredients(teaTypes, milkTypes, toppingTypes); print_ready_orders(ready);
    print_result(get_order_ready(99, pending, ready, milkReplacements)); // Expect 0 (Order not found)

    cout << "Final pending orders:" << endl;
    print_pending_orders(pending); // Should contain order 7 if it failed
    cout << "Final ready orders:" << endl;
    print_ready_orders(ready);
    cout << "Final ingredients:" << endl;
    print_ingredients(teaTypes, milkTypes, toppingTypes);

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

// Test case for complex interactions: stock depletion, replacements, skips
void test32()
{
    cout << "--- test32: Complex stock depletion and replacement ---" << endl;
    const char *database_path = "data//5-database.txt"; // Needs stock variation
    const char *recipe_path = "data//5-recipe.txt";

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));

    cout << "Initial State:" << endl;
    print_ingredients(teaTypes, milkTypes, toppingTypes);
    print_replacement_cycle(milkReplacements);

    // Create orders designed to deplete specific ingredients
    // Recipe1: Milk1(1), Topping1(1) -> Replacement Milk2(1)
    // Recipe3: Milk3(0), Topping3(1) -> Replacement Milk4(1) -> Milk5(1)
    // Recipe5: Milk5(1), Topping5(0) -> Replacement Milk6(1)
    // Recipe7: Milk7(0), Topping7(0) -> Replacement Milk8(1)

    // Order 1, 2 use Recipe 1 (depletes Milk1, then Milk2)
    print_result(create_order(pending, 1, "recipe1", recipes, numRecipes, Standard));
    print_result(create_order(pending, 2, "recipe1", recipes, numRecipes, Standard));
    // Order 3, 4 use Recipe 3 (depletes Milk4, then Milk5)
    print_result(create_order(pending, 3, "recipe3", recipes, numRecipes, Standard));
    print_result(create_order(pending, 4, "recipe3", recipes, numRecipes, Standard));
     // Order 5 uses Recipe 5 (depletes Milk6 as Milk5 is gone, skips Topping5)
    print_result(create_order(pending, 5, "recipe5", recipes, numRecipes, Standard));
    // Order 6 uses Recipe 7 (depletes Milk8, skips Topping7)
    print_result(create_order(pending, 6, "recipe7", recipes, numRecipes, Standard));
    // Order 7 uses Recipe 1 again (Milk1=0, Milk2=0 -> needs Milk3(0) -> Milk4(0) -> Milk5(0) -> Milk6(0) -> Milk7(0) -> Milk8(0) -> Fails)
    print_result(create_order(pending, 7, "recipe1", recipes, numRecipes, Standard));
    // Order 8 uses Recipe 3 again (Milk3=0, Milk4=0, Milk5=0 -> needs Milk6(0) -> Milk7(0) -> Milk8(0) -> Fails)
    print_result(create_order(pending, 8, "recipe3", recipes, numRecipes, Standard));
    // Order 9 uses Recipe 2 (Milk2(0), Topping2(1)) -> needs Milk3(0) -> Milk4(0) -> Milk5(0) -> Milk6(0) -> Milk7(0) -> Milk8(0) -> Fails
    print_result(create_order(pending, 9, "recipe2", recipes, numRecipes, Standard));


    cout << "Pending orders before processing:" << endl;
    print_pending_orders(pending);

    cout << "Processing orders..." << endl;
    print_result(get_order_ready(1, pending, ready, milkReplacements)); // Uses Milk1. Result: 1
    print_result(get_order_ready(2, pending, ready, milkReplacements)); // Uses Milk2. Result: 1
    print_result(get_order_ready(3, pending, ready, milkReplacements)); // Uses Milk4. Result: 2
    print_result(get_order_ready(4, pending, ready, milkReplacements)); // Uses Milk5. Result: 2
    print_result(get_order_ready(5, pending, ready, milkReplacements)); // Needs Milk6(1). Skips Topping5. Result: 2
    print_result(get_order_ready(6, pending, ready, milkReplacements)); // Needs Milk8(1). Skips Topping7. Result: 2
    print_result(get_order_ready(7, pending, ready, milkReplacements)); // Needs Milk3(0) -> Milk4(0) -> Milk5(0) -> Milk6(0) -> Milk7(0) -> Milk8(0) -> Fails
    print_result(get_order_ready(8, pending, ready, milkReplacements)); // Needs Milk4(0) -> Milk5(0) -> Milk6(0) -> Milk7(0) -> Milk8(0) -> Fails
    print_result(get_order_ready(9, pending, ready, milkReplacements)); // Needs Milk2(0) -> Milk3(0) -> Milk4(0) -> Milk5(0) -> Milk6(0) -> Milk7(0) -> Milk8(0) -> Fails

    cout << "Final pending orders:" << endl;
    print_pending_orders(pending); // Should contain 7, 8, 9
    cout << "Final ready orders:" << endl;
    print_ready_orders(ready);
    cout << "Final ingredients:" << endl;
    print_ingredients(teaTypes, milkTypes, toppingTypes); // Check stock levels

    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

// Renamed from test_all
void test33(int testNum){
    cout << "--- test " << testNum << ": Comprehensive System Test ---" << endl;
    const char *database_path = "data//6-database.txt";
    const char *recipe_path =   "data//6-recipe.txt";
    const char* teaNameList[] = {
        "BlackTea", "ChaiTea", "ChamomileTea", "EarlGrey", "GreenTea", 
        "HerbalTea", "JasmineTea", "Matcha", "OolongTea", "PeppermintTea", 
        "RooibosTea", "WhiteTea"
    };
    const char* milkNameList[] = {
        "AlmondMilk", "CashewMilk", "CoconutMilk", "FlaxMilk", "HempMilk", 
        "MacadamiaMilk", "OatMilk", "PeaMilk", "RiceMilk", "SkimMilk", 
        "SoyMilk", "WholeMilk"
    };
    const char* toppingNameList[] = {
        "AloeVera", "BlueBean", "CheeseFoam", "CoconutJelly", "GrassJelly", 
        "GreenBean", "LycheePoppingBoba", "MangoPoppingBoba", "PassionFruitPoppingBoba", 
        "Pudding", "RedBean", "StrawberryPoppingBoba", "TapiocaPearls"
    };
    char recipeNameList[100][25] = {"0"};
    const int MAX_ORDER_NUM = 1001;
    int pendingNumberList[MAX_ORDER_NUM] = {0};
    int milkNameCount = 12, teaNameCount = 12, toppingNameCount = 13, pendingNumberCount = 0;
    
    // Deterministic values based on test number instead of random
    int totalRecipe = 30 + (testNum % 5) * 10; // 30, 40, 50, 60, 70 recipes for tests 42-46
    int totalOrder = 128 + (testNum % 5) * 10;  // 88, 98, 108, 118, 128 orders for tests 42-46

    TeaType *teaTypes = nullptr;
    MilkType *milkTypes = nullptr;
    ToppingType *toppingTypes = nullptr;
    ReplacementListNode *milkReplacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};
    initialize_database(teaTypes, milkTypes, toppingTypes, database_path);
    initialize_recipe(teaTypes, milkTypes, toppingTypes, recipes, numRecipes, recipe_path);
    print_result(build_replacement_list(milkTypes, milkReplacements));

    print_ingredients(teaTypes, milkTypes, toppingTypes);
    print_recipe(recipes, numRecipes);

    // Stage 1: build replacement cycle
    print_replacement_cycle(milkReplacements);
    cout << endl << endl;

    // Stage 2: create recipes - deterministic selection
    for (int i = 0; i < totalRecipe; i++)
    {
        int teaIndex = (i * 3 + testNum) % teaNameCount;
        int milkIndex = (i * 7 + testNum) % milkNameCount;
        snprintf(recipeNameList[i], 25, "recipe%d", i + 1);
        print_result(create_recipe(recipeNameList[i], i, 10 + (i % 20), 
            teaNameList[teaIndex], milkNameList[milkIndex], teaTypes, milkTypes, recipes, numRecipes));
        
    }
    print_recipe(recipes, numRecipes);
    cout << endl << endl;

    // Stage 3: create orders - deterministic selection
    for (int i = 0; i < totalOrder; i++)
    {
        int recipeIndex = (i * 13 + testNum) % totalRecipe;
        int orderNum = i + 1; // Simple sequential order numbers

        pendingNumberList[pendingNumberCount] = orderNum;
        pendingNumberCount++;
        print_result(create_order(pending, orderNum, recipeNameList[recipeIndex], recipes, numRecipes, Standard));

        // Deterministic number of toppings (0-2)
        int numToppings = i % 3;
        for (int j = 0; j < numToppings; j++)
        {
            int toppingIndex = (i + j * 5 + testNum) % toppingNameCount;
            print_result(add_topping_to_order(orderNum, toppingNameList[toppingIndex], toppingTypes, pending));
        }
    }
    print_pending_orders(pending);
    cout << endl << endl;

    // Stage 4: get orders ready - deterministic selection
    for (int i = 0; i < pendingNumberCount; i++)
    {
        int orderNum = pendingNumberList[i];
        // Process every other order
        if (i % 2 == 0)
            print_result(get_order_ready(orderNum, pending, ready, milkReplacements));
    }
    print_ready_orders(ready);
    cout << endl << endl;
    print_ingredients(teaTypes, milkTypes, toppingTypes);

    // Stage 5: free memory
    delete_database(teaTypes, milkTypes, toppingTypes);
    delete_recipe(recipes, numRecipes);
    delete_pending_orders(pending);
    delete_ready_orders(ready);
    delete_replacement_circle(milkReplacements);
}

int main()
{
    int test_num;
    cin >> test_num;
    switch (test_num) {
        case 1: test1(); break;
        case 2: test2(); break;
        case 3: test3(); break;
        case 4: test4(); break;
        case 5: test5(); break;
        case 6: test6(); break;
        case 7: test7(); break;
        case 8: test8(); break;
        case 9: test9(); break;
        case 10: test10(); break;
        case 11: test11(); break;
        case 12: test12(); break;
        case 13: test13(); break;
        case 14: test14(); break;
        case 15: test15(); break;
        case 16: test16(); break;
        case 17: test17(); break;
        case 18: test18(); break;
        case 19: test19(); break;
        case 20: test20(); break;
        case 21: test21(); break;
        case 22: test22(); break;
        case 23: test23(); break;
        case 24: test24(); break;
        case 25: test25(); break;
        case 26: test26(); break;
        case 27: test27(); break;
        case 28: test28(); break;
        case 29: test29(); break; // Added test
        case 30: test30(); break; // Added test
        case 31: test31(); break; // Added test
        case 32: test32(); break; // Added test
        case 33: test33(33); break; // Renamed test_all

        default: test0(); break;
    }

    return 0;
}
