#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
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

int main(){
    int cases;
    cin >> cases;

    for(int c=1; c<=cases; c++){
        int width;

        cin >> width;

        Matrix<bool> board(width, 3);

        long long result = getPossibilities(board);

        cerr << "Case #" << c << ": " << result << endl;
        cout << "Case #" << c << ": " << result << endl;
    }
}