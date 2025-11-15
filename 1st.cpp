#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using std::string;
using std::vector;

static void setup_utf8_console()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h != INVALID_HANDLE_VALUE)
    {
        DWORD mode = 0;
        if (GetConsoleMode(h, &mode))
        {
            SetConsoleMode(h, mode | 0x0004);
        }
    }
#endif
}

static inline const char *TF(bool b) { return b ? "T" : "F"; }
static inline const char *BIN(bool b) { return b ? "1" : "0"; }

static bool parseBool(const string &s, bool &out)
{
    string x;
    x.reserve(s.size());
    std::transform(s.begin(), s.end(), std::back_inserter(x),
                   [](unsigned char c)
                   { return static_cast<char>(std::tolower(c)); });
    if (x == "1" || x == "t" || x == "true" || x == "y" || x == "yes")
    {
        out = true;
        return true;
    }
    if (x == "0" || x == "f" || x == "false" || x == "n" || x == "no")
    {
        out = false;
        return true;
    }
    return false;
}

static string center(const string &s, size_t width)
{
    if (s.size() >= width)
        return s;
    size_t pad = width - s.size();
    size_t left = pad / 2, right = pad - left;
    return string(left, ' ') + s + string(right, ' ');
}

struct TableFmt
{
    string header;
    string separator;
    vector<string> cols;
    vector<size_t> widths;
};

static TableFmt make_format()
{
    TableFmt f;
    f.header = " p | q | ¬q | p ∨ ¬q | p ∧ q | (p ∨ ¬q) → (p ∧ q)";
    f.separator = "---|---|----|--------|-------|---------------------";
    size_t start = 0;
    while (true)
    {
        size_t bar = f.header.find('|', start);
        if (bar == string::npos)
        {
            f.cols.push_back(f.header.substr(start));
            break;
        }
        f.cols.push_back(f.header.substr(start, bar - start));
        start = bar + 1;
    }
    f.widths.reserve(f.cols.size());
    for (auto &seg : f.cols)
    {
        string view = seg;
        f.widths.push_back(view.size());
    }
    return f;
}

static string show_bool(bool b, bool useTF)
{
    return useTF ? TF(b) : BIN(b);
}

static void print_row(const vector<string> &values, const TableFmt &fmt)
{
    std::cout.flush();
    for (size_t i = 0; i < values.size(); ++i)
    {
        std::cout << (i == 0 ? "" : "|") << center(values[i], fmt.widths[i]);
    }
    std::cout << "\n";
}

struct Eval
{
    bool p, q;
    bool not_q, p_or_notq, p_and_q, implication;
};

static Eval eval(bool p, bool q)
{
    Eval e{p, q, !q, false, false, false};
    e.p_or_notq = p || e.not_q;
    e.p_and_q = p && q;
    e.implication = (!e.p_or_notq) || e.p_and_q;
    return e;
}

static void print_header(const TableFmt &fmt)
{
    std::cout << fmt.header << "\n"
              << fmt.separator << "\n";
}

static void print_single(bool p, bool q, bool useTF, const TableFmt &fmt)
{
    auto e = eval(p, q);
    print_header(fmt);
    print_row({show_bool(e.p, useTF), show_bool(e.q, useTF), show_bool(e.not_q, useTF), show_bool(e.p_or_notq, useTF), show_bool(e.p_and_q, useTF), show_bool(e.implication, useTF)}, fmt);
}

static void print_full(bool useTF, const TableFmt &fmt)
{
    print_header(fmt);
    for (bool p : {true, false})
    {
        for (bool q : {true, false})
        {
            auto e = eval(p, q);
            print_row({show_bool(e.p, useTF), show_bool(e.q, useTF), show_bool(e.not_q, useTF), show_bool(e.p_or_notq, useTF), show_bool(e.p_and_q, useTF), show_bool(e.implication, useTF)}, fmt);
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(&std::cout);
    setup_utf8_console();

    const TableFmt fmt = make_format();
    bool useTF = true;

    for (;;)
    {
        std::cout << "\n==== Truth Table (p ∨ ¬q) → (p ∧ q) ====\n"
                  << "1. Compute for custom p, q (print one row)\n"
                  << "2. Show full truth table (4 rows)\n"
                  << "3. Toggle output style (now: " << (useTF ? "T/F" : "1/0") << ")\n"
                  << "4. Exit\n"
                  << "Choose an option (1-4): ";

        int opt = 0;
        if (!(std::cin >> opt))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number 1-4.\n";
            continue;
        }
        std::cout << "\n";

        if (opt == 1)
        {
            std::string sp, sq;
            std::cout << "Enter p (" << (useTF ? "T/F" : "1/0") << "): ";
            if (!(std::cin >> sp))
                return 0;
            std::cout << "Enter q (" << (useTF ? "T/F" : "1/0") << "): ";
            if (!(std::cin >> sq))
                return 0;

            bool p, q;
            if (!parseBool(sp, p) || !parseBool(sq, q))
            {
                std::cout << "Invalid input. Use 1/0, T/F, true/false, Y/N.\n";
                if (!std::cin)
                    std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cout << "\n";
            print_single(p, q, useTF, fmt);
        }
        else if (opt == 2)
        {
            std::cout << "\n";
            print_full(useTF, fmt);
        }
        else if (opt == 3)
        {
            useTF = !useTF;
            std::cout << "Output style toggled to " << (useTF ? "T/F" : "1/0") << ".\n";
        }
        else if (opt == 4)
        {
            std::cout << "Goodbye!\n";
            break;
        }
        else
        {
            std::cout << "Invalid option. Enter 1-4.\n";
        }
    }
    return 0;
}
