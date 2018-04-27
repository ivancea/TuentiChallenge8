#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

struct Note {
    long long start, end;
    int score;

    Note(long long _initialPosition, long long _length, long long _speed, int _score) {
        start = _initialPosition / _speed;
        end = (_initialPosition + _length) / _speed;
        score = _score;
    }

    bool operator<(const Note& note){
        return start < note.start;
    }
};

int solve(const vector<Note>& notes){
    vector<int> scores(notes.size());
    queue<int> indexesToUpdate;

    for(int i=0; i<notes.size(); i++){
        indexesToUpdate.push(i);
    }

    int maxScore = 0;

    while(indexesToUpdate.size() > 0){
        const int currentIndex = indexesToUpdate.front();
        indexesToUpdate.pop();
        const Note& currentNote = notes[currentIndex];
        int& currentScore = scores[currentIndex];
        
        if(maxScore < currentScore + currentNote.score){
            maxScore = currentScore + currentNote.score;
        }

        long long updateLimit = -1;

        for(int i=0; i<notes.size(); i++){
            if((updateLimit == -1 || notes[i].start <= updateLimit) && notes[i].start > currentNote.end && scores[i] < currentScore + currentNote.score){
                if(updateLimit == -1 || notes[i].end < updateLimit){
                    updateLimit = notes[i].end;
                }

                scores[i] = currentScore + currentNote.score;
                indexesToUpdate.push(i);
            }
        }
    }

    return maxScore;
}

int main(){
    int cases;
    cin >> cases;

    for(int c=1; c<=cases; c++){
        cerr << "Case #" << c << ": " << flush;
        cout << "Case #" << c << ": " << flush;

        int noteCount;
        cin >> noteCount;

        cerr << "(Notes: " << noteCount << ") " << flush;

        vector<Note> notes;

        for(int i=0; i<noteCount; i++){
            int initialposition, length, speed, score;
            cin >> initialposition >> length >> speed >> score;

            Note note(initialposition, length, speed, score);

            bool isRedundant = false;

            for(Note& existingNote : notes){
                if(note.start == existingNote.start && note.end == existingNote.end){
                    existingNote.score += note.score;
                    isRedundant = true;
                    
                    break;
                }
            }

            if(isRedundant){
                continue;
            }

            notes.push_back(note);
        }

        int extraScore = 0;

        for(int i=0; i<notes.size(); i++){
            bool anyOver = false;

            for(int j=0; j<notes.size(); j++){
                if(i != j && notes[i].start <= notes[j].end && notes[i].end >= notes[j].start){
                    anyOver = true;

                    break;
                }
            }

            if(!anyOver){
                extraScore += notes[i].score;
                notes.erase(notes.begin() + i, notes.begin() + i + 1);
                --i;
            }
        }

        cerr << "(Extra score: " << extraScore << ") " << flush;

        sort(notes.begin(), notes.end());

        //vector<vector<Note>> parts = divide(notes) // Divide into separated note blocks (not implemented because it wasn't needed to generate the submit)

        int maxScore = solve(notes);

        cerr << (maxScore + extraScore) << endl;
        cout << (maxScore + extraScore) << endl;
    }
}