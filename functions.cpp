#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // delete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

// implement for part 1

// int* createSeam(int length) { **************
//   return nullptr;
// }

// void deleteSeam(int* seam) { ********
// }





bool loadImage(string filename, Pixel** image, int width, int height) {
  ifstream fileStream; //creates my file input stream
  string inpline;
  int f_width;
  int f_height;

  fileStream.open(filename); // File Opened
  // Checking if File Opens
  if (!fileStream.is_open()) {
    cout << "Error: failed to open input file - " << filename << endl;
    fileStream.close();
    return false;
  }
  
  // First Line Check 'p3'
  fileStream >> inpline;
  
  if ((inpline != "P3") ) { //!(inpline == "P3")|| !(inpline == "p3")
    if ((inpline != "p3")) {
    cout << "Error: type is " << inpline << " instead of P3" << endl;
    //cout << "-" << inpline << "----" << endl;
    //throw std::invalid_argument("Error: type is P6 instead of P3");

    fileStream.close();
    return false;
    }
  }
  else {
    fileStream.clear();
  }
  
  // Second Line Check input is of int type
  fileStream >> f_width >> f_height; // this takes in the expected two int values into variables accordingly
  
  if (fileStream.fail()) { // if there are wrong data types or more or least than expected variables, all flag errors which are picked up by fail()
    cout << "Error: read non-integer value" << endl;
    fileStream.clear();
    fileStream.close();
    return false;
  }
  else {
    fileStream.clear();
  }
  //            checking for incorrect file & input values
  if (f_width != width)  { 
    cout << "Error: input width (" << width << ") does not match value in file (" << f_width << ")" << endl;
    fileStream.close();
    return false;
  }
  else if (f_height != height) {
    cout << "Error: input height (" << height << ") does not match value in file (" << f_height << ")" << endl;
    fileStream.close();
    return false;
  }

  // Third Line Check max RGB value of 255
  int RGB_max;
  fileStream >> RGB_max; // collects third line value RGB_max
  if ( (RGB_max != 255) || (fileStream.fail()))  { // checks for fail() just in case there is too many/less variables for input or data types not int
    cout << "Error: expected RGB max value, " << RGB_max << ", not equivalent to 255" << endl;
    fileStream.clear();
    fileStream.close();
    return false;
  }
  else {
    fileStream.clear();
  }
  //                      ALL POTENTIAL ERRORS HAVE BEEN CHECKED FOR FIRST 3 LINES OF PROGRAM
  //                      NOW WE PAIR UP IN 3s AND ADD THE PAIR TO A MASTER ARRAY 
  int index = 0;
  bool read = true;
  int SIZE = width * height;
  Pixel *master = new Pixel[SIZE];
  int color1;
  int var1 = 0;
  int var2 = 0;
  bool pair = true;
  int pair_count = 4;

  while (read) {
    fileStream >> color1; // takes in one RGB value
    int total = pair_count - 4;
    total++; // total will tell me how many input have been read before errors are checked
    int MAX = SIZE * 3;
     // this will keep it in account the value of 4 it began with, now it's a valid counter of how many values were traversed
    
    if ( (total < MAX) && (fileStream.eof()) ) { // not enough colors //&& ((static_cast<int>(color1) / color1) == 1)
      fileStream.clear();
      fileStream.close();
      cout << "Error: not enough color values" << endl;
      return false;
    }
    else if((total < MAX) && fileStream.fail()) { // checking if value is of int type      
      fileStream.clear();
      fileStream.close();
      cout << "Error: input #" << index << " of " << color1 << " is not of int type" << endl;
      return false;
    }
    // if ((total > MAX) && (!fileStream.eof())) { // too many colors..NEEDS TO EXCLUDE WHITESPACE
    //   fileStream.clear();
    //   fileStream.close();
    //   cout << "Error: too many color values"   <<endl;
    //   return false;
    // }
    // else if ( (total < MAX) && (fileStream.eof()) ) { // not enough colors //&& ((static_cast<int>(color1) / color1) == 1)
    //   fileStream.clear();
    //   fileStream.close();
    //   cout << "Error: not enough color values" << endl;
    //   return false;
    // }
    // else if((total < MAX) && fileStream.fail()) { // checking if value is of int type      
    //   fileStream.clear();
    //   fileStream.close();
    //   cout << "Error: input #" << index << " of " << color1 << " is not of int type" << endl;
    //   return false;
    // }
    else if ((total > MAX) && (!fileStream.eof())) { // too many colors..NEEDS TO EXCLUDE WHITESPACE
      fileStream.clear();
      fileStream.close();
      cout << "Error: too many color values"   <<endl;
      return false;
    }

    else if ( (color1 < 0) || (color1 > RGB_max) )  { // checks for proper range of int value
      fileStream.clear();
      fileStream.close();
      cout << "Error: invalid color value " << color1 << endl;
      return false;
    }
    // after the error checking of the input is valid, we now append it to the master array of pairs
    if ((pair_count % 3) != 0) {
      pair = false;
    }
    else {
      pair = true;
    }


    if (pair) { // the value is to be assigned to the pair 
      
      Pixel temp = {var1,var2,color1}; // creates temp Pixel object with initialized values
      
      if (index < SIZE) { 
        master[index] = (temp); // assigns temp object to correct master index to store pair 
      }
      // else { // throws too many color error
      //   fileStream.clear();
      //   fileStream.close();
      //   //cout << "Error: too many color values with a total of " << index << endl;
      //   cout << "Error: too many color values" << endl;
      //   return false;
      // }
      index++;
      pair_count++;
      var1 = 0;
      var2 = 0;


    }
    else { // 
      if ((pair_count % 3) == 1) {
        var1 = color1;
        pair_count++;
      }
      else if ((pair_count % 3) == 2) {
        var2 = color1;
        pair_count++;
      }
      else  
        cout << "Something is wrong with pair_count modulas division in functions.cpp" << endl;

    }


  if(fileStream.eof()) { // end of file
      read = false;
      //break;
    }

    
  }
  
  // Check for Errors considering to many or not enough pixels in the master array
  // pair_count -= 4; // this will keep it in account the value of 4 it began with, now it's a valid counter of how many values were traversed
  // if (pair_count < (SIZE*3)) { // i could do '>' to check if there were more values than needed but that error is already handled before during runtime 
  //   fileStream.clear();
  //   fileStream.close();
  //   cout << "Error: not enough color values with a total recorded of " << pair_count << " and expecting a total of " << (SIZE * 3) << " values" << endl;
  //   return false;
  // }

  // I beleive i can now populate the 2D Image array
  
  // "index" variable will give me the last index of the pixel pair that was created
  // var::index + 1 will give me the total amount of Pixel pairs created

  int image_count = 0; // counter var that will track what Pixel pair i am populating to 2D image array
  for ( int row = 0; row < height; row++ ) {
    for ( int col = 0; col < width; col++ ) {
        image[col][row] = master[image_count];
        image_count++;
    }
  }

  // the 2D image array has now been populated with error checked Pixel pairs consisting of 3 values via RGB sequence
  // however i am not sure the image array that has recieved values from a pointer that points to object "new Pixel[SIZE]" will cause issue later on??? confused on pass by reference so not confident i passed it correctly

  
  //                      USING THE MASTER ARRAY, WE ORGANIZE THE ELEMENTS OF THE PIXELS INTO THE 2D image ARRAY

  
  return true;
}





bool outputImage(string filename, const Pixel*const* image, int width, int height) { 
  ofstream outFile;

  outFile.open(filename); 
  if (!outFile.is_open()) { // check for error opening file
    cout << "Error: failed to open output file - " << filename << endl;
    return false;
  }
  int RGB_max = 255;
  //  creating and writting preamble
  outFile << "P3" << endl;
  outFile << width << " " << height << endl;
  outFile << RGB_max << endl;



  for (int row = 0; row < height; row++) {

    for (int col = 0; col < width; col++) { // width was row giving an error
      int red = image[col][row].r;
      int green = image[col][row].g;
      int blue = image[col][row].b;

      outFile << red << " " << green << " " << blue << " ";

    }
    outFile << endl;

  }

  outFile.close();

  return true;
}



int energy(const Pixel*const* image, int x, int y, int width, int height) {  
  
  // x var: represents what column pixel (width)
  // y var: represents what row pixel (height)
  // X Variables
  int x1_red;
  int x2_red;
  int x1_gre;
  int x2_gre;
  int x1_blu;
  int x2_blu;
  // Y Variables
  int y1_red;
  int y2_red;
  int y1_gre;
  int y2_gre;
  int y1_blu;
  int y2_blu;

  int energy_tot = 0;
  int x_energy_tot = 0;
  int y_energy_tot = 0;

  //            calculate X_ENERGY 
  
  for (int i = 0; i < 3; i++ ) { // loops to calculate R, G, B
    if (i == 0) { // calculate Red
      if ((x+1) > (width - 1)) {
        x2_red = image[0][y].r;
      } else {
      x2_red = image[x+1][y].r;
      }
      if ((x-1) < 0) {
        x1_red = image[width-1][y].r;
      } else {
      x1_red = image[x-1][y].r;
      }

      x_energy_tot += pow(( abs(x2_red) - abs(x1_red)),2);


    }
    else if (i == 1) { // claculate Green
      if ((x+1) > (width - 1)) {
        x2_gre = image[0][y].g;
      } else {
      x2_gre = image[x+1][y].g;
      }
      if ((x-1) < 0) {
        x1_gre = image[width -1][y].g;
      } else {
      x1_gre = image[x-1][y].g;
      }

      x_energy_tot += pow(( abs(x2_gre) - abs(x1_gre)),2);


    }
    else if (i == 2) { // calculate Blue
      if ((x+1) > (width - 1)) {
        x2_blu = image[0][y].b;
      } else {
      x2_blu = image[x+1][y].b;
      }
      if ((x-1) < 0) {
        x1_blu = image[width - 1][y].b;
      } else {
      x1_blu = image[x -1][y].b;
      }

      x_energy_tot += pow(( abs(x2_blu) - abs(x1_blu)),2);

    }

  }
  energy_tot += x_energy_tot;

  for (int i = 0; i < 3; i++ ) { // loops to calculate R, G, B
    if (i == 0) { // calculate Red
      if ((y+1) > (height - 1)) {
        y2_red = image[x][0].r;
      } else {
      y2_red = image[x][y+1].r;
      }
      if ((y-1) < 0) {
        y1_red = image[x][height-1].r;
      } else {
      y1_red = image[x][y-1].r;
      }

      y_energy_tot += pow(( abs(y2_red) - abs(y1_red)),2);


    }
    else if (i == 1) { // claculate Green
      if ((y+1) > (height - 1)) {
        y2_gre = image[x][0].g;
      } else {
      y2_gre = image[x][y+1].g;
      }
      if ((y-1) < 0) {
        y1_gre = image[x][height -1].g;
      } else {
      y1_gre = image[x][y-1].g;
      }

      y_energy_tot += pow(( abs(y2_gre) - abs(y1_gre)),2);


    }
    else if (i == 2) { // calculate Blue
      if ((y+1) > (height - 1)) {
        y2_blu = image[x][0].b;
      } else {
      y2_blu = image[x][y+1].b;
      }
      if ((y-1) < 0) {
        y1_blu = image[x][height - 1].b;
      } else {
      y1_blu = image[x][y -1].b;
      }

      y_energy_tot += pow(( abs(y2_blu) - abs(y1_blu)),2);

    }

  }
  energy_tot += y_energy_tot;
  //cout << energy_tot << " " << endl;
  return energy_tot;
  
  
  
  //this prints out table correctly
  // for (int row = 0; row < height; row++) {
  //   for (int col = 0; col < width; col++ ) {
  //     cout << image[col][row].r << " " << image[col][row].g << " " << image[col][row].b << " " ;


  //   }
  //   cout << endl;

  // }

  //return 0;
}

// implement for part 2

// uncomment for part 2


int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  //int width_MIN = 0;
  int width_MAX = width - 1;
  int height_MAX = height - 1;
  int total_energy = energy(image,start_col,0,width,height); // energy of starting column
  
  // seam is an array to be loaded with column indice of least energy value
  seam[0] = start_col; // this records the first start_col index for the seam

  if ( width > 1 ) {
  for (int i = 1; i <= height_MAX; i++) { // loops stops 1 row before final row so we don't find energy value of a row that's out of bounds
    if ((seam[i-1] > 0) && (seam[i-1] < width_MAX )) {
      int energy_one = energy(image,seam[i-1] - 1, i, width, height);
      int energy_two = energy(image,seam[i-1], i, width, height);
      int energy_three = energy(image,seam[i-1] + 1, i, width, height);

      // these bool var flag the priority of choosing which lesser energy to assign
      bool forward = false;
      bool left = false; // which is right when looking at graph
      int low = energy_one;
      // these if statement tree is how i create my own "min()" function with implications on priority choosing of left or foward column of all 3 optioons
      if (low > energy_two) { 
        low = energy_two;
        if (low > energy_three) {
          // if (energy_three > energy_two) {
          //   forward = true;
          // }
          // else if (energy_three == energy_two) {
          //   forward = true;
          // }
          //if {
            low = energy_three;
            left = true;
          //}
        }
        else
          forward = true;
      }
      else if (low == energy_two) {
        low = energy_two;
        if (low > energy_three) {
          low = energy_three;
          left = true;
        }
        else
          forward = true;
      }
      else if (low > energy_three) { 
        low = energy_three;
        left = true;
      }
      else if (low == energy_three) { 
        low = energy_three;
        left = true;
      }
      

      // after filtering values, i assign the column index to the pointed seam array
      if (forward) {
        seam[i] = seam[i-1];
      }
      else if (left) {
        seam[i] = seam[i-1] + 1;
      }
      else {
        seam[i] = seam[i-1] - 1;
      }
      // after assigning values, low var will have correct value to add to total energy
      total_energy += low;


    }
    else if ((seam[i-1] == 0)) { // this start_col is on far left side of image
      int energy_one = energy(image,seam[i-1], i, width, height);
      int energy_two = energy(image,seam[i-1] + 1, i, width, height);
      bool forward = false;
      bool left = false;
      int low = energy_one;
      if (low > energy_two) {
        low = energy_two;
        left = true;
      }
      else {
        forward = true;
      }
      
      if (forward) {
        seam[i] = seam[i-1];
      }
      else if (left) {
        seam[i] = seam[i-1] + 1;
      }

      total_energy += low;

    }
    else if ((seam[i-1] == (width_MAX))) { // this start_col is on far right side of image
      int energy_one = energy(image,seam[i-1], i, width, height);
      int energy_two = energy(image,seam[i-1] - 1, i, width, height);
      bool forward = false;

      int low = energy_one;

      if (low <= energy_two) {
        forward = true;
      }
      else {
        low = energy_two;
      }

      if (forward) 
        seam[i] = seam[i-1];
      else 
        seam[i] = seam[i-1] - 1;

      total_energy += low;

    }

  }
  }
  else {
  for (int i = 1; i <= height_MAX; i++) { // loops stops 1 row before final row so we don't find energy value of a row that's out of bounds
    int energy_one = energy(image,seam[i-1], i, width, height);
    int low = energy_one;
    
    seam[i] = seam[i-1];
    total_energy += low;
  }

  }
  // if the image for some reason is just one row of pixels then it will just have a seam array of the beginning column_start index and return that energy

  
  return total_energy;

}


// int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
//   return 0;
// }

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  
  int* seam = new int[height]; 
  int min_energy = loadVerticalSeam(image,0,width,height,seam);

  for (int i = 1; i < width; i++) {
    
    int* temp_array = new int[height];
    int temp_energy = loadVerticalSeam(image,i,width,height,temp_array);

    if (temp_energy < min_energy) {
      min_energy = temp_energy;
      delete [] seam;
      seam = temp_array;
    }

  }
  
  return seam;
}

// int* findMinHorizontalSeam(Pixel** image, int width, int height) {
//   return nullptr;
// }

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {

  for (int row = 0; row < height; row ++) { // each loop is for one column value to be adjusted
    
    //             verticalSeam[row] = the least column index of the seam
    Pixel pixel_removed = image[verticalSeam[row]][row];
    for (int col = verticalSeam[row]; col < width; col++ ) { // loop starts at column to be removed
      if (col == width - 1) {
        image[col][row] = pixel_removed;
      }
      else {
        image[col][row] = image[col+1][row];
      }


    }

  }

}


//  void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) { *************
//  }
