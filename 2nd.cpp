#include <bits/stdc++.h>
using namespace std;

pair<bool, long long> parse_ll(const string &s)
{
    try
    {
        size_t idx = 0;
        long long v = stoll(s, &idx, 10);
        if (idx != s.size())
            return {false, 0};
        return {true, v};
    }
    catch (...)
    {
        return {false, 0};
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "==================== Find Maximum Number ====================\n";
    cout << "This program finds the maximum number and the position (1-based) where it first appears.\n\n";

    cout << "Choose input mode:\n";
    cout << "  1) Fixed count: I will enter how many numbers (n), then you'll be prompted for each number.\n";
    cout << "  2) Free entry: Enter numbers one by one and type 'done' (or press Ctrl+D / Ctrl+Z) when finished.\n";
    cout << "Enter 1 or 2: ";
    cout.flush();

    int mode = 0;
    if (!(cin >> mode) || (mode != 1 && mode != 2))
    {
        cerr << "Invalid choice. Please run the program again and enter 1 or 2.\n";
        return 1;
    }

    string tmp;
    getline(cin, tmp);

    bool have_value = false;
    long long max_val = 0;
    size_t max_pos = 0;
    size_t count = 0;

    if (mode == 1)
    {
        cout << "\nFixed-count mode selected.\n";
        cout << "Enter the number of elements (n, non-negative integer): ";
        cout.flush();

        long long n_ll;
        if (!(cin >> n_ll) || n_ll < 0)
        {
            cerr << "Invalid n. Please run again and enter a non-negative integer for n.\n";
            return 1;
        }
        size_t n = static_cast<size_t>(n_ll);
        getline(cin, tmp);

        if (n == 0)
        {
            cout << "You entered n = 0. No numbers to read.\n";
        }
        else
        {
            bool eof_encountered = false;
            for (size_t i = 1; i <= n; ++i)
            {
                if (eof_encountered)
                    break;

                while (true)
                {
                    cout << "Enter element " << i << ": ";
                    cout.flush();
                    string line;
                    if (!std::getline(cin, line))
                    {
                        cout << "\nInput ended unexpectedly (EOF). Proceeding with numbers read so far.\n";
                        eof_encountered = true;
                        break;
                    }
                    auto start = line.find_first_not_of(" \t\r\n");
                    if (start == string::npos)
                    {
                        cout << "Empty input — please type a number (e.g., 42) or -5.\n";
                        continue;
                    }
                    auto end = line.find_last_not_of(" \t\r\n");
                    string token = line.substr(start, end - start + 1);

                    auto [ok, val] = parse_ll(token);
                    if (!ok)
                    {
                        cout << "Invalid number. Please type a valid integer (e.g., 123 or -45).\n";
                        continue;
                    }
                    ++count;
                    if (!have_value)
                    {
                        have_value = true;
                        max_val = val;
                        max_pos = count;
                    }
                    else if (val > max_val)
                    {
                        max_val = val;
                        max_pos = count;
                    }
                    break;
                }
            }
        }
    }
    else
    {
        cout << "\nFree-entry mode selected.\n";
        cout << "Type numbers one at a time. Type 'done' (without quotes) and press Enter when finished.\n";
        cout << "You can also finish input with EOF (Ctrl+D on Linux/macOS, Ctrl+Z then Enter on Windows).\n";

        while (true)
        {
            cout << "Enter number (or 'done'): ";
            cout.flush();
            string line;
            if (!getline(cin, line))
            {
                // EOF
                cout << "\n(End of input detected.)\n";
                break;
            }
            // Trim
            auto start = line.find_first_not_of(" \t\r\n");
            if (start == string::npos)
            {
                cout << "Empty input — type a number or 'done'.\n";
                continue;
            }
            auto end = line.find_last_not_of(" \t\r\n");
            string token = line.substr(start, end - start + 1);

            string lower = token;
            for (char &c : lower)
                c = char(tolower(c));
            if (lower == "done")
            {
                break;
            }

            auto [ok, val] = parse_ll(token);
            if (!ok)
            {
                cout << "Invalid number. Please type a valid integer (e.g., 100 or -7), or 'done' to finish.\n";
                continue;
            }
            ++count;
            if (!have_value)
            {
                have_value = true;
                max_val = val;
                max_pos = count;
            }
            else if (val > max_val)
            {
                max_val = val;
                max_pos = count;
            }
        }
    }

    cout << "\n==================== Result ====================\n";
    if (!have_value)
    {
        cout << "No valid numbers were provided. Maximum is undefined.\n";
    }
    else
    {
        cout << "Numbers read: " << count << "\n";
        cout << "Maximum value: " << max_val << "\n";
        cout << "First occurrence at position (1-based): " << max_pos << "\n";
    }
    cout << "===============================================\n";

    return 0;
}
