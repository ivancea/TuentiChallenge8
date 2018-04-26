#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

template<typename T>
class Matrix {
    int _width, _height;

    T** _matrix;

public:
    Matrix(int width, int height) : _width(width), _height(height) {
        _matrix = new T*[width];

        for(int i=0; i<width; i++){
            _matrix[i] = new T[height];
        }
    }

    Matrix(const Matrix&) = delete;

    ~Matrix(){
        for(int i=0; i<_width; i++){
            delete[] _matrix[i];
        }

        delete[] _matrix;
    }

    void setAll(T value){
        for(int i=0; i<_width; i++){
            for(int j=0; j<_height; j++){
                _matrix[i][j] = value;
            }
        }
    }

    void set(int x, int y, T value){
        _matrix[x][y] = value;
    }

    T get(int x, int y) const {
        return _matrix[x][y];
    }

    int getWidth() const {
        return _width;
    }

    int getHeight() const {
        return _height;
    }
};

struct Position {
    int x, y;

    Position(int _x, int _y) : x(_x), y(_y) {}
};

const char KNIGHT = 'S';
const char PRINCESS = 'P';
const char DESTINATION = 'D';
const char GROUND = '.';
const char TRAMPOLINE = '*';
const char LAVA = '#';

Position findSquare(const Matrix<char>& ground, char square){
    for(int i=0; i<ground.getWidth(); i++){
        for(int j=0; j<ground.getHeight(); j++){
            if(ground.get(i,j) == square){
                return Position(i,j);
            }
        }
    }

    return Position(-1, -1);
}

void fillDistances(const Matrix<char>& ground, Matrix<int>& distances, Position initialPosition){
    queue<Position> queuedPositions;

    queuedPositions.emplace(initialPosition);

    while(queuedPositions.size() > 0){
        Position currentPosition = queuedPositions.front();
        queuedPositions.pop();
        int nextValue = distances.get(currentPosition.x, currentPosition.y) + 1;
        bool isTrampoline = ground.get(currentPosition.x, currentPosition.y) == TRAMPOLINE;

        for(int i=-2; i<=2; i++){
            if(i == 0) continue;
            for(int j=-2; j<=2; j++){
                if(j == 0 || abs(i) == abs(j)) continue;
                
                Position nextPosition(currentPosition.x + (isTrampoline ? i*2 : i), currentPosition.y + (isTrampoline ? j*2 : j));

                if(nextPosition.x >= 0 && nextPosition.x < ground.getWidth() && nextPosition.y >= 0 && nextPosition.y < ground.getHeight()
                && ground.get(nextPosition.x, nextPosition.y) != LAVA
                && (distances.get(nextPosition.x, nextPosition.y) == -1 || distances.get(nextPosition.x, nextPosition.y) > nextValue)){
                    distances.set(nextPosition.x, nextPosition.y, nextValue);
                    queuedPositions.emplace(nextPosition);
                }
            }
        }
    }
}

int main(){
    int n;
    cin >> n;

    for(int c=1; c<=n; c++){
        cout << "Case #" << c << ": ";

        int width, height;
        cin >> height >> width;

        Matrix<char> ground(width, height);
        Matrix<int> distances(width, height);

        for(int j=0; j<height; j++){
            string t;
            cin >> t;
            
            for(int k=0; k<t.size(); k++){
                ground.set(k, j, t[k]);
            }
        }

        Position knight = findSquare(ground, KNIGHT);
        Position princess = findSquare(ground, PRINCESS);
        Position destination = findSquare(ground, DESTINATION);

        distances.setAll(-1);
        distances.set(knight.x, knight.y, 0);

        fillDistances(ground, distances, knight);

        if(distances.get(princess.x, princess.y) == -1){
            cout << "IMPOSSIBLE" << endl;

            continue;
        }

        int totalDistance = distances.get(princess.x, princess.y);

        distances.setAll(-1);
        distances.set(princess.x, princess.y, 0);

        fillDistances(ground, distances, princess);

        if(distances.get(destination.x, destination.y) == -1){
            cout << "IMPOSSIBLE" << endl;

            continue;
        }

        totalDistance += distances.get(destination.x, destination.y);

        cout << totalDistance << endl;
    }
}