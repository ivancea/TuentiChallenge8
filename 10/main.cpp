#include <iostream>
#include <vector>
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

long long getPossibilities(const Matrix<bool>& invalidPartners, int rangeStart, int rangeEnd){
    if(rangeEnd - rangeStart <= 0){
        return 0;
    }

    long long total = 0;

    // Connecting the {rangeStart} point
    // i+=2 because no odd elements range allowed
    for(int i=rangeStart+1; i<rangeEnd; i+=2){
        if(!invalidPartners.get(0,i)){
            long long possibilities = getPossibilities(invalidPartners, rangeStart+1, i);

            if(possibilities != 0){
                possibilities *= getPossibilities(invalidPartners, i+1, rangeEnd);
            }

            total += possibilities;
        }
    }

    return total;
}

int main(){
    int cases;
    cin >> cases;

    for(int c=1; c<=cases; c++){
        int people, invalidPartnerCount;

        cin >> people >> invalidPartnerCount;

        Matrix<bool> invalidPartners(people, people);

        for(int i=0; i<invalidPartnerCount; i++){
            int a, b;
            cin >> a >> b;

            invalidPartners.set(a,b, true);
            invalidPartners.set(b,a, true);
        }

        long long result = getPossibilities(invalidPartners, 0, people);

        cout << "Case #" << c << ": " << result << endl;
    }
}