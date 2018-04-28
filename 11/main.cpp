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

int getMaxLasers(Matrix<bool>& items){
    vector<bool> xLasers(items.getWidth());
    vector<bool> yLasers(items.getHeight());

    vector<int> xItemCounts(items.getWidth());
    vector<int> yItemCounts(items.getHeight());

    for(int i=0; i<items.getWidth(); i++){
        for(int j=0; j<items.getHeight(); j++){
            if(items.get(i,j)){
                xItemCounts[i]++;
                yItemCounts[j]++;
            }
        }
    }

    int remainingXLaserPositions = xLasers.size();
    int remainingYLaserPositions = yLasers.size();

    int totalLasers = 0;
    
    while(remainingXLaserPositions > 0 || remainingYLaserPositions > 0){
        int minXIndex = -1;
        int minXItems = 0;
        int minYIndex = -1;
        int minYItems = 0;

        for(int i=0; i<xLasers.size(); i++){
            if(!xLasers[i] && (minXIndex == -1 || xItemCounts[i] < minXItems)){
                minXIndex = i;
                minXItems = xItemCounts[i];
            }
        }

        for(int i=0; i<yLasers.size(); i++){
            if(!yLasers[i] && (minYIndex == -1 || yItemCounts[i] < minYItems)){
                minYIndex = i;
                minYItems = yItemCounts[i];
            }
        }

        //cerr << minXIndex << "(" << minXItems << ") || " << minYIndex << "(" << minYItems << ")" << endl;
        if(minYIndex == -1 || (minXIndex != -1 && minXItems < minYItems)){
            //cerr << "X " << minXIndex << endl;
            xLasers[minXIndex] = true;
            --remainingXLaserPositions;

            for(int i=0; i<items.getHeight(); i++){
                if(items.get(minXIndex, i) && !yLasers[i]){
                    yLasers[i] = true;
                    --remainingYLaserPositions;

                    // "Remove" gems that cannot be crossed by more than one laser
                    for(int j=0; j<items.getWidth(); j++){
                        if(items.get(j,i)){
                            items.set(j,i, false);
                            xItemCounts[j]--;
                        }
                    }
                }
            }
        }else{
            //cerr << "Y " << minYIndex << endl;
            yLasers[minYIndex] = true;
            --remainingYLaserPositions;

            for(int i=0; i<items.getWidth(); i++){
                if(items.get(i, minYIndex) && !xLasers[i]){
                    xLasers[i] = true;
                    --remainingXLaserPositions;

                    // "Remove" gems that cannot be crossed by more than one laser
                    for(int j=0; j<items.getHeight(); j++){
                        if(items.get(i,j)){
                            items.set(i,j, false);
                            yItemCounts[j]--;
                        }
                    }
                }
            }
        }

        //cerr << remainingXLaserPositions << " - " << remainingYLaserPositions << endl;

        ++totalLasers;
    }
    
    return max(totalLasers, max(items.getWidth(), items.getHeight()));
}

int main(){
    int cases;
    cin >> cases;

    for(int c=1; c<=cases; c++){
        int width, height, itemCount;

        cin >> width >> height >> itemCount;

        Matrix<bool> items(width, height);

        items.setAll(false);

        for(int i=0; i<itemCount; i++){
            int x, y;
            cin >> x >> y;

            items.set(x,y, true);
        }

        int result = getMaxLasers(items);

        cerr << "Case #" << c << ": " << result << endl;
        cout << "Case #" << c << ": " << result << endl;
    }
}