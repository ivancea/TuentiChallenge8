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

map<int, long long> cache;

bool tryGetCache(int key, long long& ret){
    auto it = cache.find(key);
    if(it != cache.end()){
        ret = it->second;
        return true;
    }
    return false;
}

void setCache(int key,  long long value){
    cache[key] = value;
}

void resetCache(){
    cache.clear();
}

const long long Mod = 1000000007;

long long getPossibilities(const Matrix<bool>& invalidPartners, int rangeStart, int rangeEnd){
    if(rangeEnd - rangeStart <= 0){
        return 1;
    }

    long long total = 0;

    // Connecting {rangeStart} to {i}
    // i+=2 because no odd elements range allowed
    for(int i=rangeStart+1; i<rangeEnd; i+=2){
        if(!invalidPartners.get(rangeStart,i)){
            long long possibilities;
            
            if(!tryGetCache((rangeStart+1)*10000 + i, possibilities)){
                possibilities = getPossibilities(invalidPartners, rangeStart+1, i);
                setCache((rangeStart+1)*10000 + i, possibilities);
            }

            if(possibilities != 0){
                long long t;
                
                if(!tryGetCache((i+1)*10000 + rangeEnd, t)){
                    t = getPossibilities(invalidPartners, i+1, rangeEnd);
                    setCache((i+1)*10000 + rangeEnd, t);
                }

                possibilities *= t;
            }

            total = (total + possibilities) % Mod;
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

        invalidPartners.setAll(false);

        for(int i=0; i<invalidPartnerCount; i++){
            int a, b;
            cin >> a >> b;

            invalidPartners.set(a,b, true);
            invalidPartners.set(b,a, true);
        }

        long long result = getPossibilities(invalidPartners, 0, people);
        resetCache();

        cerr << "Case #" << c << ": " << result << endl;
        cout << "Case #" << c << ": " << result << endl;
    }
}