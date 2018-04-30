#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

const long long Mod = 1000000007;

vector<long long> cache;
vector<long long> holeInTheBottomCache;

long long mod(long long n){
    return n % Mod;
}

// O(nlogn)
long long getPossibilitiesWithHoleInTheBottom(int width){
    long long possibilities = 0;

    // width-1 because the bottom block have to reach the top
    // i: top index
    for(int i=1; i<=width-1; i++){
        // j: center index
        // No double hole here
        for(int j=1; j<=width-1; j++){
            possibilities = mod(possibilities + cache[width-max(i,j)]);
        }
        
        // Double hole
        // j: center index
        for(int j=1; j<i; j++){
            possibilities = mod(possibilities + (i-j)*holeInTheBottomCache[width - i]);
        }
    }

    return possibilities;
}

// CACHE
long long getPossibilitiesWithHoleInTheBottomCached(int width){
    if(holeInTheBottomCache.size() > width){
        return holeInTheBottomCache[width];
    }

    for(int i=holeInTheBottomCache.size(); i <= width; i++){
        holeInTheBottomCache.push_back(getPossibilitiesWithHoleInTheBottom(i));
    }

    return holeInTheBottomCache[width];
}

// O(1)
long long calcBasicPossibilities(int width, int blockWidth){
    if(blockWidth == width){
        return 1;
    }

    // Center hole and top and bottom holes combinations
    long long rawPossibilities = blockWidth - 1 + blockWidth*blockWidth;

    return mod(rawPossibilities * cache[width - blockWidth]);
}

// O(1)
long long calcBigHolePossibilities(int width, int blockWidth){
    if(blockWidth >= width){
        return 0;
    }

    // Two lines entering (top/bottom and center)
    long long possibilities = mod(possibilities + (blockWidth - 1)*cache[width - blockWidth]); // Only one big hole

    return mod(possibilities*2);
}

// O(n)
long long calcDoubleHolePossibilities(int width, int blockWidth){
    if(blockWidth + 1 >= width){
        return 0;
    }

    long long possibilities = 0;

    /*
        ##-O
        #--O <-- Big hole
        #-OO <-- Small hole
    */

    const long long outPossibilities = getPossibilitiesWithHoleInTheBottomCached(width - blockWidth);

    // Two holes entering (top/bottom and center)
    // i: big hole index
    for(int i=1; i<blockWidth; i++){
        // j: small hole index (hole inside big hole)
        possibilities = mod(possibilities + (blockWidth-i)*outPossibilities);
    }

    // x2 because we consider bottom and top possibilities
    return mod(possibilities*2);
}

// O(1)
long long getPossibilities(int width){
    if(width <= 1){
        return 1;
    }

    if(width == 2){
        return 2;
    }

    long long total = 0;

    // i: Current max index
    for(int i=1; i<=width; i++){
        total = mod(total + calcBasicPossibilities(width, i));
        total = mod(total + calcBigHolePossibilities(width, i));
        total = mod(total + calcDoubleHolePossibilities(width, i));
    }

    return total > 1 ? total : 1;
}

// CACHE
long long getPossibilitiesCached(int width){
    if(cache.size() > width){
        return cache[width];
    }

    for(int i=cache.size(); i <= width; i++){
        cache.push_back(getPossibilities(i));
    }

    return cache[width];
}

int main(){
    int cases;
    cin >> cases;

    for(int c=1; c<=cases; c++){
        int width;

        cin >> width;

        long long result = getPossibilitiesCached(width);

        cerr << "Case #" << c << ": " << result << endl;
        cout << "Case #" << c << ": " << result << endl;
    }
}