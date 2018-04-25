#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const vector<string> allNotes = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
const vector<int> majorScale = {2, 2, 1, 2, 2, 2, 1};
const vector<int> minorScale = {2, 1, 2, 2, 1, 2, 2};

map<string, set<string>> generateScales(){
    map<string, set<string>> scales;

    for(int i=0; i < allNotes.size(); i++){
        const string& note = allNotes[i];

        set<string> majorScaleNotes;
        set<string> minorScaleNotes;

        int currentMajorNoteIndex = i;
        int currentMinorNoteIndex = i;

        for(int j=0; j<7; j++){
            majorScaleNotes.insert(allNotes[currentMajorNoteIndex]);
            minorScaleNotes.insert(allNotes[currentMinorNoteIndex]);

            currentMajorNoteIndex += majorScale[j];
            currentMinorNoteIndex += minorScale[j];

            if(currentMajorNoteIndex >= 12){
                currentMajorNoteIndex -= 12;
            }
            if(currentMinorNoteIndex >= 12){
                currentMinorNoteIndex -= 12;
            }
        }

        scales["M" + note] = majorScaleNotes;
        scales["m" + note] = minorScaleNotes;
    }

    return scales;
}

string translateNote(const string& note){
    if(note[note.size()-1] == 'b'){
        string newNote = note.substr(0, note.size()-1);
        
        for(int i=0; i<allNotes.size(); i++){
            if(allNotes[i] == newNote){
                if(i == 0){
                    return allNotes[11];
                }

                return allNotes[i-1];
            }
        }
    }else if(note[note.size()-1] == '#' && find(allNotes.begin(), allNotes.end(), note) == allNotes.end()){
        string newNote = note.substr(0, note.size()-1);
        
        for(int i=0; i<allNotes.size(); i++){
            if(allNotes[i] == newNote){
                return allNotes[i+1];
            }
        }
    }

    return note;
}

int main(){
    const map<string, set<string>> scales = generateScales();
    
    /*for(const pair<string, set<string>>& scale : scales){
        cout << scale.first << " ->";

        for(string note : scale.second){
            cout << " " << note;
        }

        cout << endl;
    }*/

    int n;
    cin >> n;

    for(int i=1; i<=n; i++){
        cout << "Case #" << i << ":";

        int noteCount;
        cin >> noteCount;

        set<string> notes;

        while(noteCount-->0){
            string t;
            cin >> t;
            notes.insert(translateNote(t));
        }

        int count = 0;

        for(const pair<string, set<string>>& scale : scales){
            bool valid = true;

            for(string note : notes){
                if(scale.second.find(note) == scale.second.end()){
                    valid = false;
                    break;
                }
            }

            if(valid){
                cout << " " << scale.first;
                ++count;
            }
        }

        if(count == 0){
            cout << " None";
        }

        cout << endl;
    }
}