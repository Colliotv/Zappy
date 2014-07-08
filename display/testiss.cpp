#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    string s = "1 2 3"; 
    istringstream iss(s);   
    int n;

    while (iss >> n) {
        cout << "* " << n << endl;
    } 
}
