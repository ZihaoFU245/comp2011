#include <iostream>
#include "pa3.cpp"
using namespace std;

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


void testcase1()
{
    const char *database_path = "data//2-database.txt"; // use the second set for this test
    const char *recipe_path = "data//2-recipe.txt";
    cout << boolalpha;

    // set them ready
    TeaType *teatypes = nullptr;
    MilkType *milktypes = nullptr;
    ToppingType *Toppingtypes = nullptr;
    ReplacementListNode *replacements = nullptr;
    Drink **recipes = nullptr;
    int numRecipes = 0;
    Order *pending = nullptr;
    Order *ready[10] = {};

    // load
    initialize_database(teatypes, milktypes, Toppingtypes, database_path);
    initialize_recipe(teatypes, milktypes, Toppingtypes,recipes, numRecipes, recipe_path);

    remove_recipe("BlackTeaLatte", recipes, numRecipes);
    remove_recipe("GreenTeaLatte", recipes, numRecipes);
    remove_recipe("CoconutMilkTea", recipes, numRecipes);
    // change stocks and minitor effetcs
    create_recipe("testDrink", 10, 100, "GrapeTea", "SkimMilk", teatypes, milktypes, recipes, numRecipes);
    
    print_ingredients(teatypes, milktypes, Toppingtypes);


}

int main()
{
    testcase1();
}