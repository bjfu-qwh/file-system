#include "../include/core.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv)
{
    string config = fetchDiskLocation();
    cout << config << endl;
    return 0;
}