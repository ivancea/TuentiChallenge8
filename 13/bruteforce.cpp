#include <iostream>
#include <set>

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

const int WIDTH = 5;

long long total = 0;

bool isValid(const Matrix<int>& mat){
    int lastTop;
    bool okTop = false;
    
    int lastMid;
    bool okMidTop = false;
    bool okMidBot = false;

    int lastBot;
    bool okBot = false;

    set<int> tops;
    set<int> mids;
    set<int> bots;

    tops.emplace(mat.get(0, 0));
    mids.emplace(mat.get(0, 1));
    bots.emplace(mat.get(0, 2));

    for(int i=0; i<mat.getWidth(); i++){
        int actualTop = mat.get(i, 0);
        int actualMid = mat.get(i, 1);
        int actualBot = mat.get(i, 2);

        if(i > 0){
            if(actualTop != lastTop){
                if(!okTop || tops.find(actualTop) != tops.end()){
                    return false;
                }

                okTop = false;
            }

            if(actualMid != lastMid){
                if(!okMidTop || !okMidBot || mids.find(actualMid) != mids.end()){
                    return false;
                }
                
                okMidTop = false;
                okMidBot = false;
            }

            if(actualBot != lastBot){
                if(!okBot || bots.find(actualBot) != bots.end()){
                    return false;
                }
                
                okBot = false;
            }
        }

        if(actualMid == actualTop){
            okTop = true;
            okMidTop = true;
        }

        if(actualMid == actualBot){
            okBot = true;
            okMidBot = true;
        }

        lastTop = actualTop;
        lastMid = actualMid;
        lastBot = actualBot;

        tops.emplace(actualTop);
        mids.emplace(actualMid);
        bots.emplace(actualBot);
    }

    if(!okTop || !okBot || !okMidTop || !okMidBot){
        return false;
    }

    return true;
}

void fillMatrix(Matrix<int>& mat, int index){
    if(index >= mat.getWidth() * mat.getHeight()){
        if(isValid(mat)){
            ++total;
            /*for(int i=0; i<mat.getHeight(); i++){
                for(int j=0; j<mat.getWidth(); j++){
                    cout << mat.get(j,i);
                }
                cout << endl;
            }
            cout << endl;*/
        }
    }else{
        for(int i=0; i<WIDTH; i++){
            mat.set(index%WIDTH, index/WIDTH, i);
            fillMatrix(mat, index + 1);
        }
    }
}

void fillRow(Matrix<int>& mat, int index, int value){
    if(index >= mat.getWidth()){
        fillMatrix(mat, mat.getWidth());
    }else{
        for(int i=index; i<mat.getWidth(); i++){
            mat.set(i,0, value);
            fillRow(mat, i+1, value+1);
        }
    }
}

void fillMatrix(Matrix<int>& mat){
    fillRow(mat, 0, 0);
}

int main(){
    Matrix<int> mat(WIDTH, 3);

    fillMatrix(mat);

    cout << total << endl;
}