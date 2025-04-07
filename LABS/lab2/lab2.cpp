#include <iostream>
using namespace std;

int main()
{
    // Set the overall precision to avoid displaying too many decimal places
    cout.precision(5);

    // The deficit in Hong Kong, in billion (B) Hong Kong dollars
    // Reference: https://www.budget.gov.hk/2023/eng/images/Budget2023Leaflet-EN-BarChart.png
    //
    // In Year 2024:
    //    Income: 642.4B
    //    Expenditure: 761B
    //
    // The official foreign currency reserve assets of Hong Kong amounted to US$421.4 billion as at the end of October 2024
    // Reference: https://www.hkma.gov.hk/eng/news-and-media/press-releases/2024/11/20241107-3/
    //
    // In Year 2024:
    // The total reserves in Hong Kong dollars is: 421.4 * 7.8 = 3286.92
    //
    // Assumption 1: We assume the input expenditure is larger than the income  (both of them are positive values)
    // Assumption 2: We assume the input deficitChangePercent is a non-negative value
    //
    //  For example:
    //   deficitChangePercent = 1
    //   the deficit keeps increasing by 1% every year
    //
    // Assumption 3: We assume the input reserves is a positive value

    int currentYear;
    double income, expenditure, reserves, deficit, deficitPercentChange;

    cout << "All currency values are in billion Hong Kong dollars" << endl;
    cout << "Enter the current year: ";
    cin >> currentYear;
    cout << "Enter the income: ";
    cin >> income;
    cout << "Enter the expenditure: ";
    cin >> expenditure;
    cout << "Enter the reserves: ";
    cin >> reserves;
    cout << "Enter the deficit increase percentage (%): ";
    cin >> deficitPercentChange;

    // === Start: Write your code within this region
    deficit = expenditure - income;
    while (reserves > 0)
    {
        reserves -= deficit;
        if (reserves > 0)
        {
            cout << "End of " << currentYear << " reserves = "
                 << reserves << endl;
        }
        else
        {
            cout << "End of " << currentYear << " reserves = "
                 << "zero or negative" << endl;
        }
        deficit = deficit * (1.0 + deficitPercentChange / 100.0);
        currentYear++;
    }

    // === End: Write your code within this region
    return 0;
}