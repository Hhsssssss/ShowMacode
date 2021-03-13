#include <cstdio>
#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    const string filePath1 = "CPP/train_data/training-1.txt";
    freopen(filePath1.c_str(), "r", stdin);
    const string outputPath = "CPP/temp_data/temp_output.txt";
    freopen(outputPath.c_str(), "w", stdout);
    string s;
    while(cin >> s) {
        cout << s << endl;
    }
}