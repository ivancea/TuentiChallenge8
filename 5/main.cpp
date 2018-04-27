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

boolean solveFindingDuplicated(const vector<string>& parts, const string& original, const set<int>& ignoredIndexes){
    vector<int> indexes;

    for(int i=0; i<parts.size(); i++){
        indexes.push_back(i);
    }

    for(int count=2; count < parts.size()/2; count++){
        long long checksum = 0;

        do{
            long long currentChecksum = 0;
            bool shouldContinue = false;

            for(int i=0; i<count; i++){
                shouldContinue = ignoredIndexes.find(indexes[i]) != ignoredIndexes.end();

                if(shouldContinue){
                    break;
                }

                currentChecksum += indexes[i] * pow(count, i);
            }

            if(shouldContinue || checksum != 0 && checksum == currentChecksum){
                continue;
            }

            checksum = currentChecksum;

            string str;

            int totalLength = 0;

            for(int i=0; i<count; i++){
                totalLength += parts[indexes[i]].size();
            }

            if(totalLength != original.size()){
                continue;
            }

            for(int i=0; i<count; i++){
                str += parts[indexes[i]];
            }

            if(str != original){
                continue;
            }

            set<int> usedIndexes;

            for(int i=0; i<count; i++){
                usedIndexes.insert(indexes[i]);
            }

            for(int index : ignoredIndexes){
                usedIndexes.insert(index);
            }

            if(trySolution(usedIndexes)){
                cout << "FOUND: " << str << endl;

                return true;
            }
        }while(next_permutation(indexes.begin(), indexes.end()));
    }

    return false;
}

bool solve(const vector<string>& parts){
    vector<int> indexes;

    for(int i=0; i<parts.size(); i++){
        indexes.push_back(i);
    }

    for(int count=2; count < parts.size()/2; count++){
        long long checksum = 0;

        do{
            long long currentChecksum = 0;

            for(int i=0; i<count; i++){
                currentChecksum += indexes[i] * pow(count, i);
            }

            if(checksum != 0 && checksum == currentChecksum){
                continue;
            }

            checksum = currentChecksum;

            string str;

            set<int> usedIndexes;

            for(int i=0; i<count; i++){
                usedIndexes.insert(indexes[i]);
                str += parts[indexes[i]];
            }

            if(solveFindingDuplicated(parts, str, usedIndexes)){
                return true;
            }
        }while(next_permutation(indexes.begin(), indexes.end()));
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

    sendLine("TEST");

    // Start!
    readLine();
    
    for(int c=1; c<=20; c++){
        string data = readLine();
        vector<string> parts = split(data, ' ');
        
        if(!solve(parts)){
            cout << "ERROR" << endl;

            return 1;
        }
    }
}