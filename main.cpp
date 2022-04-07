#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"
using namespace std;
int half_size {SIZE / 2};

unsigned char image [SIZE][SIZE];
void loadImage(){
    char imageFileName[100];
    cout << "Enter the source image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    readGSBMP (imageFileName, image);
}
void saveImage(){
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;
    strcat (imageFileName, ".bmp");
    writeGSBMP (imageFileName, image);
}
void blackWhiteImage(){
    // nested for loops to loop on the pixels of image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // if pixels colors > 127, turn it to white
            if (image[i][j] > 127)
                image[i][j] = 255;
            // else, turn them to black
            else
                image[i][j] = 0;
        }
    }
}
int main() {
    while (true) {
        cout << "What do you like to do: " << endl;
        cout << "1-Black and white image." << endl;
        cout << "2-Invert image." << endl;
        cout << "3-Merge Images." << endl;
        cout << "4-Flip Image." << endl;
        cout << "5-Rotate Image." << endl;
        cout << "6-Darken and Lighten Image." << endl;
        cout << "7-Detect Image Edges." << endl;
        cout << "8-Enlarge Image." << endl;
        cout << "9-Shrink Image." << endl;
        cout << "a-Mirror Image." << endl;
        cout << "b-Shuffle Image." << endl;
        cout << "c-Blur Image." << endl;
        cout << "0-Exit." << endl;
        cout << "enter number or char: ";
        char option;
        cin >> option;
        if (option == '0') {
            break;
        }
        loadImage();
        switch (option) {
            case '1':
                blackWhiteImage();
                break;
            case '2':

                break;
            case '3':

                break;
            case '4':

                break;
            case '5':

                break;
            case '6':

                break;
            case '7':

                break;
            case '8':

                break;
            case '9':

                break;
            case 'a':

                break;
            case 'b':

                break;
            case 'c':

                break;
        }
        saveImage();
    }
}
