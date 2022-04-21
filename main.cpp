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
void invertImage(){
    // nested for loops to loop on the matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // subtract image pixels from 255 to get white or black colors
            image[i][j] = 255 - image[i][j];
        }
    }
}


void mergeImage()
{
    unsigned char mergedImage[SIZE][SIZE];
    unsigned char image2[SIZE][SIZE];
    char mergedImageFileName[100];
    // load another image to merge with the first image
    cout << "Enter the image file name you want to merge with: ";
    cin >> mergedImageFileName;
    strcat(mergedImageFileName, ".bmp");
    readGSBMP(mergedImageFileName, image2);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            // get the average of pixels of the two images
            mergedImage[i][j] = (image[i][j] + image2[i][j]) / 2;
            image[i][j] = mergedImage[i][j];
        }
    }
}
void flipImage(){
    unsigned char newImage[SIZE][SIZE];
    // nested for loops to loop on the matrix
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            newImage[i][j] = image[SIZE - i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }
}
void rotateImage() {
    unsigned char newImage[SIZE][SIZE];
    cout << "Choose degree of rotation:" << endl;
    cout << "1-90 degrees." << endl;
    cout << "2-180 degrees." << endl;
    cout << "3-270 degrees." << endl;
    int option;
    cin >> option;
    if (option == 1) {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                newImage[j][255 - i] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                image[i][j] = newImage[i][j];
            }
        }
    }
    if (option == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[255 - i][255 - j] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                image[i][j] = newImage[i][j];
            }
        }
    }
    if (option == 3) {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                newImage[255 - j][i] = image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                image[i][j] = newImage[i][j];
            }
        }
    }
}

void darkenLightenImage(){
    unsigned char light[SIZE][SIZE];
    // load white image to merge with image to lighten it
    char imageFileName[100] = "White";
    strcat (imageFileName, ".bmp");
    readGSBMP (imageFileName, light);
    unsigned char dark[SIZE][SIZE];
    // load black image to merge with image to darken it
    char fileName[100] = "Black";
    strcat (fileName, ".bmp");
    readGSBMP (fileName, dark);
    cout << "Do you want to darken or lighten the image?" << endl;
    string choice;
    cin >> choice;
    if (choice == "lighten"){
        unsigned char lightImage[SIZE][SIZE];
        // nested for loops to loop on the matrix
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++){
                // get the average of pixels of the two images
             lightImage[i][j] = (image[i][j] + light[i][j])/2;
             image[i][j] = lightImage[i][j];
            }
        }
    }
    if (choice == "darken"){
        unsigned char darkImage[SIZE][SIZE];
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                // get the average of pixels of the two images
                darkImage[i][j] = (image[i][j] + dark[i][j])/2;
                image[i][j] = darkImage[i][j];
            }
        }
    }
}
int get_average(unsigned char image[SIZE][SIZE],int row,int column,int kernel_size){
    int half_size = floor(kernel_size / 2);
    int row_start = row - half_size >= 0 ? row - half_size : 0;
    int column_start = column - half_size >= 0 ? column - half_size : 0;
    int sum_siblings = {0};
    int counter = 0;
    for(int i = 0;i < kernel_size;i++){
        if (row_start + i >= SIZE){
            break;
        }
        for(int j = 0;j < kernel_size;j++){
            if (column_start + j >= SIZE){
                break;
            }
            sum_siblings += image[row_start + i][column_start + j];
            counter += 1;
        }
    }

    return sum_siblings / (counter);

}
void blurImage() {
    unsigned char newImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            int average {get_average(image,i,j,10)};
            newImage[i][j] = average;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }

}
int get_average(unsigned char image[SIZE][SIZE],int row,int column,int kernel_size){
    int half_size = floor(kernel_size / 2);
    int row_start = row - half_size >= 0 ? row - half_size : 0;
    int column_start = column - half_size >= 0 ? column - half_size : 0;
    int sum_siblings = {0};
    int counter = 0;
    for(int i = 0;i < kernel_size;i++){
        if (row_start + i >= SIZE){
            break;
        }
        for(int j = 0;j < kernel_size;j++){
            if (column_start + j >= SIZE){
                break;
            }
            sum_siblings += image[row_start + i][column_start + j];
            counter += 1;
        }
    }

    return sum_siblings / (counter);

}
void blurImage() {
    unsigned char newImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            int average {get_average(image,i,j,10)};
            newImage[i][j] = average;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = newImage[i][j];
        }
    }

}
void enlargeImage() {
    cout << "Which part do you want to enlarge:" << endl;
    cout << "1-1st quarter" << endl;
    cout << "2-2nd quarter" << endl;
    cout << "3-3rd quarter" << endl;
    cout << "4-4th quarter" << endl;
    int option;
    cin >> option;
    if (option == 1) {
        unsigned char newImage[SIZE][SIZE];
        //0,0 => 0,0 & 0,1 & 1,0 & 1,1
        //0,1 => 0,2 & 0,3 & 1,2 & 1,3
        int column_start_pointer = 0;
        int row_start_pointer = 0;
        for (int i = 0; i < half_size; i++) {
            for (int j = 0; j < half_size; j++) {
                for (int m = 0; m < 2; m++) {
                    for (int k = 0; k < 2; k++) {
                        newImage[row_start_pointer + m][column_start_pointer + k] = image[i][j];
                    }
                }
                column_start_pointer += 2;
            }
            column_start_pointer = 0;
            row_start_pointer += 2;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = newImage[i][j];
            }
        }
    }
   if (option == 2){
       unsigned char newImage[SIZE][SIZE];
       int column_start_pointer = 0;
       int row_start_pointer = 0;
       for (int i = 0; i < half_size; i++) {
           for (int j = half_size; j < SIZE; j++) {
               for(int m = 0;m < 2;m++){
                   for(int k = 0;k < 2;k++){
                       newImage[row_start_pointer + m][column_start_pointer + k] = image[i][j];
                   }
               }
               column_start_pointer += 2;
           }
           column_start_pointer = 0;
           row_start_pointer += 2;
       }
       for (int i = 0; i < SIZE; i++) {
           for (int j = 0; j< SIZE; j++) {
               image[i][j] = newImage[i][j];
           }
       }
  }
  if (option == 3){
      unsigned char newImage[SIZE][SIZE];
      int column_start_pointer = 0;
      int row_start_pointer = 0;
      for (int i = half_size; i < SIZE; i++) {
          for (int j = 0; j < half_size; j++) {
              for(int m = 0;m < 2;m++){
                  for(int k = 0;k < 2;k++){
                      newImage[row_start_pointer + m][column_start_pointer + k] = image[i][j];
                  }
              }
              column_start_pointer += 2;
          }
          column_start_pointer = 0;
          row_start_pointer += 2;
      }
      for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j< SIZE; j++) {
               image[i][j] = newImage[i][j];
          }
      }
  }
  if (option == 4){
      unsigned char newImage[SIZE][SIZE];
      int column_start_pointer = 0;
      int row_start_pointer = 0;
      for (int i = half_size; i < SIZE; i++) {
          for (int j = half_size; j < SIZE; j++) {
              for(int m = 0;m < 2;m++){
                  for(int k = 0;k < 2;k++){
                      newImage[row_start_pointer + m][column_start_pointer + k] = image[i][j];
                  }
              }
              column_start_pointer += 2;
          }
          column_start_pointer = 0;
          row_start_pointer += 2;
      }
      for (int i = 0; i < SIZE; i++) {
          for (int j = 0; j< SIZE; j++) {
              image[i][j] = newImage[i][j];
          }
      }
  }
}
void mirrorImage(){
cout << "Which part do you want to mirror: " << endl;
cout << "1-Upper." << endl;
cout << "2-Lower." << endl;
cout << "3-Right." << endl;
cout << "4-Left." << endl;
char choice;
cin >> choice;
if(choice == '1'){
    unsigned char upperImage[SIZE][SIZE];
    for (int i = 0; i < half_size; i++) {
        for (int j = 0; j < SIZE; j++) {
            upperImage[i][j] = image[i][j];
        }
    }
    for (int i = SIZE - 1; i >= half_size; i--) {
        for (int j = SIZE - 1; j >= 0; j--) {
            upperImage[i][j] = image[SIZE - 1 - i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = upperImage[i][j];
        }
    }
}
if (choice == '2'){
    unsigned char lowerImage[SIZE][SIZE];
    for (int i = SIZE - 1; i >= half_size; i--) {
        for (int j = SIZE - 1; j >= 0; j--) {
            lowerImage[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < half_size; i++) {
        for (int j = 0; j < SIZE; j++) {
            lowerImage[i][j] = image[SIZE - 1 - i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = lowerImage[i][j];
        }
    }
}
if (choice == '3'){
    unsigned char rightImage[SIZE][SIZE];
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = SIZE - 1; j >= half_size; j--) {
            rightImage[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < half_size; j++) {
            rightImage[i][j] = image[i][SIZE - 1 - j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            image[i][j] = rightImage[i][j];
        }
    }
}
if (choice == '4'){
    unsigned char leftImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < half_size; j++) {
            leftImage[i][j] = image[i][j];
        }
    }
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = SIZE - 1; j >= half_size; j--) {
            leftImage[i][j] = image[i][SIZE - 1 - j];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = leftImage[i][j];
        }
    }
}
}
int get_kernel(unsigned char image[SIZE][SIZE],int row,int column){
    if (row == 0 || row == SIZE - 1){
        return 0;
    }
    if (column == 0 || column == SIZE - 1){
        return 0;
    }
    int rt_sibling_pixel {image[row][column + 1]};
    int lft_sibling_pixel {image[row][column - 1]};
    int tp_lft_sibling_pixel {image[row + 1][column - 1]};
    int tp_rt_sibling_pixel {image[row + 1][column + 1]};
    int bt_lft_sibling_pixel {image[row - 1][column - 1]};
    int bt_rt_sibling_pixel {image[row - 1][column + 1]};
    int act_pixel {image[row][column]};
    int tp_sibling_pixel{image[row + 1][column]};
    int bt_sibling_pixel{image[row - 1][column]};
    int gx {-1*(lft_sibling_pixel + tp_lft_sibling_pixel + bt_lft_sibling_pixel) + (rt_sibling_pixel + tp_rt_sibling_pixel + bt_rt_sibling_pixel)};
    int gy {-1*(bt_lft_sibling_pixel + bt_rt_sibling_pixel + bt_sibling_pixel) + (tp_lft_sibling_pixel + tp_rt_sibling_pixel + tp_sibling_pixel)};
    return sqrt((gx*gx) + (gy*gy));

}
void detectImageEdges() {
    unsigned char newImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            int kernel_number {get_kernel(image,i,j)};
            if (kernel_number > 180){
                newImage[i][j] = 0;
            }else{
                newImage[i][j] = 255;
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            image[i][j] = newImage[i][j];
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
                invertImage();
                break;
            case '3':
                mergeImage()
                break;
            case '4':
                flipImage()
                break;
            case '5':
                rotateImage();
                break;
            case '6':
                darkenLightenImage();
                break;
            case '7':
                detectImageEdges()
                break;
            case '8':
                enlargeimage();
                break;
            case '9':

                break;
            case 'a':
                mirrorImage();
                break;
            case 'b':

                break;
            case 'c':
                blurImage();
                break;
        }
        saveImage();
    }
}
