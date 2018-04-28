#include <iostream>
#include <vector>
#include <map>

#include "Image.h"

using namespace std;

int getUnfitness(const vector<sf::Color>& a, const vector<sf::Color>& b){
    int total = 0;

    for(int i=0; i<a.size()/2; i++){
        total += abs(a[i].r - b[i].r);
        total += abs(a[i].g - b[i].g);
        total += abs(a[i].b - b[i].b);
    }

    return total;
}

void vectorToImage(const vector<vector<sf::Color>>& data, Image& image){
    for(int i=0; i<data.size(); i++){
        for(int j=0; j<data[i].size(); j++){
            image.set(i,j, data[i][j]);
        }
    }
}

vector<vector<sf::Color>> imageToVector(const Image& image){
    vector<vector<sf::Color>> data;

    data.resize(image.getX());

    for(int i=0; i<data.size(); i++){
        data[i].resize(image.getY());

        for(int j=0; j<data[i].size(); j++){
            data[i][j] = image.get(i,j);
        }
    }

    return data;
}

int main(){
    Image image;
    image.loadFromBMP("submit.bmp");

    if(!image.isValid()){
        cout << "ERROR: Couldn't load image" << endl;

        return 1;
    }

    vector<vector<sf::Color>> finalImage;
    vector<vector<sf::Color>> remainingLines = imageToVector(image);

    finalImage.push_back(move(remainingLines.back()));
    remainingLines.erase(remainingLines.begin() + remainingLines.size() - 1);

    cout << "Starting" << endl;

    while(remainingLines.size() > 0){
        int leftLesserUnfitness = getUnfitness(finalImage.front(), remainingLines.front());
        int leftIndex = 0;

        int rightLesserUnfitness = getUnfitness(finalImage.front(), remainingLines.front());
        int rightIndex = remainingLines.size() - 1;

        for(int i=1; i<remainingLines.size() && leftLesserUnfitness > 0 && rightLesserUnfitness > 0; i++){
            int currentLeftUnfitness = getUnfitness(finalImage.front(), remainingLines[i]);
            int currentRightUnfitness = getUnfitness(finalImage.back(), remainingLines[0]);

            if(currentLeftUnfitness < leftLesserUnfitness){
                leftLesserUnfitness = currentLeftUnfitness;
                leftIndex = i;
            }

            if(currentRightUnfitness < rightLesserUnfitness){
                rightLesserUnfitness = currentRightUnfitness;
                rightIndex = i;
            }
        }

        if(leftLesserUnfitness < rightLesserUnfitness){
            finalImage.insert(finalImage.begin(), move(remainingLines[leftIndex]));
            remainingLines.erase(remainingLines.begin() + leftIndex);
        }else{
            finalImage.push_back(move(remainingLines[rightIndex]));
            remainingLines.erase(remainingLines.begin() + rightIndex);
        }
    }

    vectorToImage(finalImage, image);

    image.saveToBMP("submitResult.bmp");
}