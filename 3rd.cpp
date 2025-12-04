#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

static constexpr const char *COL_RESET = "\x1b[0m";
static constexpr const char *COL_HEADER = "\x1b[1;36m";
static constexpr const char *COL_PROMPT = "\x1b[1;33m";
static constexpr const char *COL_OK = "\x1b[1;32m";
static constexpr const char *COL_ERR = "\x1b[1;31m";
static constexpr const char *COL_INFO = "\x1b[1;35m";

static void enableAnsiColors()
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode))
        {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, mode);
        }
    }
#endif
}

long long gcd_with_steps(long long a, long long b)
{
    long long x = a;
    long long y = b;

    cout << COL_INFO << "Steps:" << COL_RESET << "\n";

    if (x == 0 && y == 0)
    {
        cout << COL_ERR << "gcd(0, 0) is undefined." << COL_RESET << "\n";
        return 0;
    }

    while (y != 0)
    {
        long long r = x % y;
        cout << "x = " << x << ", y = " << y << ", r = x % y = " << r << "\n";
        x = y;
        y = r;
    }

    cout << COL_OK << "Final GCD = " << x << COL_RESET << "\n";
    return x;
}

int runInteractive()
{
    enableAnsiColors();

    cout << COL_HEADER << "==============================================\n";
    cout << "          Euclidean Algorithm GCD Calculator             \n";
    cout << "==============================================" << COL_RESET << "\n\n";

    string line;
    while (true)
    {
        cout << COL_PROMPT << "Enter two integers (or 'q' to quit): " << COL_RESET;
        if (!std::getline(cin, line))
            break;

        size_t pos = line.find_first_not_of(" \t\r\n");
        if (pos == string::npos)
            continue;

        if (line[pos] == 'q' || line[pos] == 'Q')
        {
            cout << COL_OK << "Goodbye!" << COL_RESET << "\n";
            break;
        }

        stringstream ss(line);
        long long a = 0, b = 0;
        if (!(ss >> a >> b))
        {
            cout << COL_ERR << "Invalid input. Please type two integers separated by space." << COL_RESET << "\n";
            continue;
        }

        if (a < 0)
            a = llabs(a);
        if (b < 0)
            b = llabs(b);

        auto start = chrono::high_resolution_clock::now();
        long long result = gcd_with_steps(a, b);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> elapsed = end - start;

        cout << COL_OK << "Result: gcd(" << a << ", " << b << ") = " << result << COL_RESET << "\n";
        cout << "Computed in " << elapsed.count() << " ms\n\n";
    }

    return 0;
}

int main()
{
    return runInteractive();
}

#ifdef _WIN32
extern "C" int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    return main();
}
#endif
