#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main() {
  string filename;
  int width = 0;
  int height = 0;
  int targetWidth = 0;
  int targetHeight = 0;
  

  // Add code to validate input (Do in part 1)
  //cout << "Input filename: ";
  cin >> filename;

  //cout << "Input width and height: ";
  cin >> width ;
  if (cin.fail()) {
    cout << "Error: width is a non-integer value " << endl;
    return -1;
  }
    
  cin >> height;
  if (cin.fail()) {
    cout << "Error: height is a non-integer value " << endl;
    return -1;
  }

  cin >> targetWidth ;
  if (cin.fail()) {
    cout << "Error: target width is a non-integer value " << endl;
    return -1;
  }

  cin >> targetHeight;
  if (cin.fail()) {
    cout << "Error: target height is a non-integer value " << endl;
    return -1;
  }

  // Part 1: Error Checking | input > 0 | targetInput < Input | input is int value
  
  // int test = static_cast<int>(width);
  // if (test != width) {
  //   cout << "Error: width is a non-integer value " << endl;
  //   return -1;
  // }
  // test = static_cast<int>(height);
  // if (test != height) {
  //   cout << "Error: height is a non-integer value " << endl;
  //   return -1;
  // }
  // test = static_cast<int>(targetHeight);
  // if (test != targetHeight) {
  //   cout << "Error: targetHeight is a non-integer value " << endl;
  //   return -1;
  // }
  // test = static_cast<int>(targetWidth);
  // if (test != targetWidth) {
  //   cout << "Error: targetWidth is a non-integer value " << endl;
  //   return -1;
  // }
  
  if ( (width < 1) || (height < 1) || (targetWidth < 1) || (targetHeight < 1)) {
    if (width < 1) {
      cout << "Error: width must be greater than 0. You entered " << width << endl;
      return -1;
    }
    else if (height < 1) { 
      cout << "Error: height must be greater than 0. You entered " << height << endl;
      return -1;
    }
    else if (targetWidth < 1) {
      cout << "Error: target width must be greater than 0. You entered " << targetWidth << endl;
      return -1;
    }
    else if (targetHeight < 1) {
      cout << "Error: target height must be greater than 0. You entered " << targetHeight << endl;
      return -1;
    }
  
  }

  if ( (targetWidth > width) || (targetHeight > height)   ) {
    
    if (targetWidth > width) {
      cout << "Error: target width must be less than width, " << targetWidth << " is greater than " << width << endl;
      return -1;
    }
    else if (targetHeight > height) {
      cout << "Error: target height must be less than height, " << targetHeight << " is greater than " << height << endl;
      return -1;
    }

  }

  // int test = static_cast<int>(width);
  // if (test != width) {
  //   cout << "Error: width is a non-integer value " << endl;
  //   return -1;
  // }
  // test = static_cast<int>(height);
  // if (test != height) {
  //   cout << "Error: height is a non-integer value " << endl;
  //   return -1;
  // }
  // test = static_cast<int>(targetHeight);
  // if (test != targetHeight) {
  //   cout << "Error: targetHeight is a non-integer value " << endl;
  //   return -1;
  // }
  // test = static_cast<int>(targetWidth);
  // if (test != targetWidth) {
  //   cout << "Error: targetWidth is a non-integer value " << endl;
  //   return -1;
  // }
  //              ERROR CHECKING  FINISHED


  int originalWidth = width; // need to delete image array at end of program

  Pixel** image = createImage(width, height); // create array of size that we need
  if (image != nullptr) {
    if (loadImage(filename, image, width, height)) {
      cout << "Start carving..." << endl;
      
      // Add code to remove seams from image (Do in part 2)
      
      //                      testing loading seam 6x5
      // int* seam = new int[height];
      // int total = loadVerticalSeam(image,2,6,5,seam);
      // for (int i = 0; i < height; i ++) {
      //   cout << seam[i] << " " << energy(image,seam[i],i,width,height) << endl;
      // }


      //                          testing min_seam 6x5
      // int* min_seam = findMinVerticalSeam(image, width, height);
      // for (int i = 0; i < height; i ++) {
      //   cout << min_seam[i] << " " << energy(image,min_seam[i],i,width,height) << endl;
      // }

      // test if remove works on minimum seam
      //removeVerticalSeam(image,width,height,min_seam);

      //                        tells me energy of each pixel
      // for (int row = 0; row < height; row++) {
      //   for (int col = 0; col < width; col++ ) {
      //     cout << "[" << image[col][row].r  << ", " << image[col][row].g << ", " << image[col][row].b << "]" ; //
      //     //cout << "(" << energy(image,col,row,width,height) << ") - ";
      //   }
      //   cout << endl;
      // }      

    
      stringstream ss;
      ss << "carved" << width << "X" << height << "." << filename;
      outputImage(ss.str().c_str(), image, width, height);
    }
  
    // call last to remove the memory from the heap
    deleteImage(image, originalWidth);
  }
  // else 
  
}