#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <chrono>
#include <thread>
#include <algorithm>

#include "sockets.cpp"
#include "strings.h"

using namespace std;

void thSleep(unsigned int milliseconds){
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

bool takeLineFrom(string& buffer, string& outputLine){
    size_t pos = buffer.find('\n');
    
    if(pos != string::npos){
        outputLine = buffer.substr(0, pos);
        
        buffer.erase(0, pos + 1);

        return true;
    }

    return false;
}

TCPClient client;

string readLine(){
    static string buffer;

    string line;

    while(!takeLineFrom(buffer, line)){
        string newData;

        while((newData = client.recv()).size() == 0){
            thSleep(50);
        }

        buffer += newData;
    }

    cout << "IN: " << line << endl;

    return line;
}

void sendLine(const string& data){
    client.send(data + "\n");
    cout << "OUT: " << data << endl;
}

boolean trySolution(const set<int> indexes){
    string result;
    bool first = true;

    for(int n : indexes){
        if(!first){
            result += ",";
        }
        first = false;
        result += to_string(n + 1);
    }
    
    sendLine(result);
    
    return readLine().find("not correct") == string::npos;
}

bool solve(const vector<string>& parts, const string& remainder, set<int>& usedIndexes){
    for(int i=0; i<parts.size(); i++){
        if(usedIndexes.find(i) == usedIndexes.end()){
            const string& bigger = remainder.size() > parts[i].size() ? remainder : parts[i];
            const string& smaller = remainder.size() > parts[i].size() ? parts[i] : remainder;

            if(bigger.compare(0, smaller.size(), smaller) == 0){
                usedIndexes.insert(i);

                string newRemainder = bigger.substr(smaller.size());

                if(newRemainder.size() == 0){
                    if(trySolution(usedIndexes)){
                        return true;
                    }
                }

                if(solve(parts, newRemainder, usedIndexes)){
                    return true;
                }

                usedIndexes.erase(i);
            }
        }
    }

    return false;
}

bool solve(const vector<string>& parts){
    for(int i=0; i<parts.size(); i++){
        set<int> usedIndexes;

        usedIndexes.insert(i);

        if(solve(parts, parts[i], usedIndexes)){
            return true;
        }
    }

    return false;
}

int main(){
    cout << "Connecting..." << endl;
    client.connect("52.49.91.111", 3241);

    // 20 cases, max 3 failures
    readLine();
    // Please, provide "TEST" or "SUBMIT"
    readLine();

    sendLine("SUBMIT");

    // Start!
    readLine();
    
    for(int c=1; c<=20; c++){
        cout << "\nCase " << c << endl;
        string data = readLine();
        vector<string> parts = split(data, ' ');
        
        if(!solve(parts)){
            cout << "ERROR" << endl;

            return 1;
        }
    }
}