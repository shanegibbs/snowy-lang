#include <vector>
#include <iostream>

#include <Log.h>
#include <SnowyAssert.h>

namespace Snowy
{

typedef void (*TestFunc)();

class Test
{
public:
    Test(const string path, TestFunc f) : path(path), f(f) {
        Log::setup();
    }
    void run() const {
        cerr << path << ": ";
        f();
        cerr << "\x1b[32mOK\x1b[0m" << endl;
    }
private:
    const string path;
    const TestFunc f;
};

class TestSuite
{
public:
    TestSuite() {}
    void add(const string path, TestFunc f) {
        script.push_back(new Test(path, f));
    }
    int run() {
        for (const Test* t : script) {
            t->run();
        }
        return 0;
    }
private:
    vector<const Test*> script;
};

}
