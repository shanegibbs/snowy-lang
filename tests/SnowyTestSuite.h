#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

#include <Log.h>
#include <SnowyAssert.h>

using namespace std;

namespace Snowy
{

class TestSuite;

typedef void (*TestFunc)();
typedef void (*AddTestsFunc)(TestSuite&);

class Test
{
public:
    Test(const string path, TestFunc f) : path(path), f(f)
    {
        Log::setup();
    }
    int run(string* filter) const
    {
        if (filter != nullptr && path.compare(0, filter->size(), *filter) != 0) {
            return 0;
        }

        cerr << path << ": ";
        try {
            f();
            cerr << "\x1b[32mOK\x1b[0m" << endl;
        } catch (FatalLogEvent e) {
            cerr << "FAIL" << endl;
        }
        return 1;
    }
    static bool SortAsc(const Test* a, const Test* b)
    {
        return a->path.compare(b->path) < 0;
    }
    static bool SortDesc(const Test* a, const Test* b)
    {
        return a->path.compare(b->path) > 0;
    }
private:
    const string path;
    const TestFunc f;
};

class TestSuite
{
public:
    TestSuite()
    {
        single_pass = false;
        filter = nullptr;
        tests_run_count = 0;
    }
    ~TestSuite()
    {
        for (const Test* t : script) {
            delete t;
        }
        if (filter != nullptr) {
            delete filter;
        }
    }
    void setFilter(string* f)
    {
        filter = f;
        single_pass = true;
    }
    void add(const string path, TestFunc f)
    {
        script.push_back(new Test(path, f));
    }
    void add(const AddTestsFunc f)
    {
        f(*this);
    }
    int run()
    {
        int r;
        auto start_time = chrono::high_resolution_clock::now();

        if (!single_pass) {
            cerr << "* Running tests in natural order..." << endl;
        }

        r = run_script();
        if (r != 0) {
            return r;
        }

        if (!single_pass) {
            cerr << "* Running tests in ascending order..." << endl;
            sort(script.begin(), script.end(), Test::SortAsc);
            r = run_script();
            if (r != 0) {
                return r;
            }

            cerr << "* Running tests in descending order..." << endl;
            sort(script.begin(), script.end(), Test::SortDesc);
            r = run_script();
            if (r != 0) {
                return r;
            }
        }

        auto time = chrono::high_resolution_clock::now() - start_time;
        cerr << "----------------------------------------" << endl;
        double seconds = chrono::duration_cast<chrono::milliseconds>(time).count() / 1000.0f;
        cerr << "Ran " << tests_run_count << " tests in " << seconds << "s" << endl;

        cerr << endl << "\x1b[32mOK\x1b[0m" << endl;
        return 0;
    }
    int run_script()
    {
        for (const Test* t : script) {
            tests_run_count += t->run(filter);
        }
        return 0;
    }
private:
    vector<const Test*> script;
    int tests_run_count;
    bool single_pass;
    string* filter;
};

}
