#include <iostream>
#include <vector>

using namespace std;

bool isReflexive(const vector<vector<int>> &m)
{
    for (int i = 0; i < (int)m.size(); ++i)
        if (m[i][i] != 1)
            return false;
    return true;
}

bool isIrreflexive(const vector<vector<int>> &m)
{
    for (int i = 0; i < (int)m.size(); ++i)
        if (m[i][i] != 0)
            return false;
    return true;
}

bool isSymmetric(const vector<vector<int>> &m)
{
    int n = m.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (m[i][j] != m[j][i])
                return false;
    return true;
}

bool isAntisymmetric(const vector<vector<int>> &m)
{
    int n = m.size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (i != j && m[i][j] == 1 && m[j][i] == 1)
                return false;
    return true;
}

bool isTransitive(const vector<vector<int>> &m)
{
    int n = m.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (m[i][j] == 1)
            {
                for (int k = 0; k < n; ++k)
                {
                    if (m[j][k] == 1 && m[i][k] == 0)
                        return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    int n;
    cout << "=== Relation Property Checker ===\n";
    cout << "Enter the size of the matrix (n x n): ";
    while (!(cin >> n) || n <= 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input! Enter a positive integer for n: ";
    }

    vector<vector<int>> matrix(n, vector<int>(n));

    cout << "\nEnter the relation matrix (" << n << " x " << n << ")\n"
         << "Use 1 for a relation, 0 for no relation. Enter " << n << " values per row.\n";

    for (int i = 0; i < n; ++i)
    {
        bool validRow = false;
        while (!validRow)
        {
            cout << "Row " << i + 1 << ": ";
            validRow = true;
            for (int j = 0; j < n; ++j)
            {
                if (!(cin >> matrix[i][j]) || (matrix[i][j] != 0 && matrix[i][j] != 1))
                {
                    validRow = false;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input. Please enter only 0 or 1 for each entry in the row.\n";
                    break;
                }
            }
            if (validRow)
                cin.ignore(10000, '\n');
        }
    }

    cout << "\n========================================\n";
    cout << "CHECKING PROPERTIES OF THE RELATION\n";
    cout << "========================================\n\n";

    // Reflexive / Irreflexive
    bool reflex = isReflexive(matrix);
    bool irreflex = isIrreflexive(matrix);
    cout << (reflex ? "The relation is Reflexive.\n" : "The relation is NOT Reflexive.\n");
    cout << (irreflex ? "The relation is Irreflexive.\n" : "The relation is NOT Irreflexive.\n");

    // Symmetric
    cout << (isSymmetric(matrix) ? "The relation is Symmetric.\n" : "The relation is NOT Symmetric.\n");

    // Antisymmetric
    cout << (isAntisymmetric(matrix) ? "The relation is Antisymmetric.\n"
                                     : "The relation is NOT Antisymmetric.\n");

    // Transitive
    cout << (isTransitive(matrix) ? "The relation is Transitive.\n"
                                  : "The relation is NOT Transitive.\n");

    return 0;
}
