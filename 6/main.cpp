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

void solve(const vector<Note>& notes, vector<int>& scores, const long long end){
    vector<bool> addedScoreNote(notes.size());
    queue<int> indexesToUpdate;

    for(int i=0; i<notes.size(); i++){
        indexesToUpdate.push(i);
    }

    while(indexesToUpdate.size() > 0){
        const int currentIndex = indexesToUpdate.front();
        indexesToUpdate.pop();
        const Note& currentNote = notes[currentIndex];
        int& currentScore = scores[currentIndex];

        currentScore += currentNote.score;
        addedScoreNote[currentIndex] = true;

        for(int i=0; i<notes.size(); i++){
            if(notes[i].start > currentNote.end && scores[i] - (addedScoreNote[i] ? notes[i].score : 0) < currentScore){
                indexesToUpdate.push(i);
            }
        }
    }
}

int main(){
    int cases;
    cin >> cases;

    for(int c=1; c<=cases; c++){
        cout << "Case #" << c << ": " << flush;

        int noteCount;
        cin >> noteCount;

        vector<Note> notes;
        vector<int> scores(noteCount);

        long long end = 0;

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

            if(note.end > end){
                end = note.end;
            }

            notes.push_back(note);
        }

        sort(notes.begin(), notes.end());

        solve(notes, scores, end);

        int maxScore = 0;

        for(int score : scores){
            if(score > maxScore){
                maxScore = score;
            }
        }

        cout << maxScore << endl;
    }
}