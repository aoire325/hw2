#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "TimeCode.h"

using namespace std;

int main() {
    ifstream file("Space_Corrected.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    vector<vector<string>> csvData;
    string line;
    
    vector<TimeCode> v;
    bool firstLine = true;
    while (getline(file, line)) {

        if (firstLine) {
            firstLine = false;
            continue;
        }

        size_t utcPosition = line.find(" UTC");

        if (utcPosition != string::npos) {
            string hour = line.substr(utcPosition - 5, 2);
            string min = line.substr(utcPosition - 2, 2);

            int h = stoi(hour);
            int m = stoi(min);

            TimeCode tmp(h, m, 0);
            v.push_back(tmp);
        }
    }
    cout << v.size() << " data points" << endl;
    TimeCode totalTime;
        for (const auto& timeCode : v) {
            totalTime = totalTime + timeCode;  
        }
        TimeCode averageTime;
        if (!v.empty()) {
            averageTime = totalTime / static_cast<double>(v.size());
        }
        cout << "AVERAGE: " << averageTime.ToString() << endl;
	
    file.close();
    
    return 0;
}
