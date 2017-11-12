//Brendon Brandolino
#include <iostream>
#include <string>
#include <vector>
#include "bitmap.h"
using namespace std;

const int maxNumImage = 10; // max number of images

vector<string> getImage();// get images from the user
bool isValid(string);// check the file name to ensure it is a bmp
vector<vector<vector<Pixel> > > createImageVector(vector<string>);
vector<vector<Pixel> > collapseVector(vector<vector<vector<Pixel> > > ); //collpase the vectors into a single layer with averaged pixels



int main() {
  Bitmap image;
  vector<vector<vector<Pixel> > > bmp;
  vector<string> fileNames;
  Pixel rgb;

fileNames =getImage();


  return 0;
}

vector<vector<vector<Pixel> > > createBmpVector(vector<string>){
  vector<vector<vector<Pixel> > > BmpVector;
  Pixel rgb;

}

vector<string> getImage(){
  vector<string> imageVector;
  int count = 0;
  do {
    string im;
    cin>>im;
    if (im == "DONE") {
      return imageVector;
    }
    if (isValid(im) == true) {
      imageVector.push_back(im);
    }
    else{
      cout<<"Please enter a VALID file name"<<endl;
    }
  } while(count < maxNumImage);

  return imageVector;
}

bool isValid(string im){
  Bitmap image;
  if (image.isImage() == false) {
    return false;
    }
  else{
    return true;
    }
  }

  vector<vector<Pixel> > collapseVector(vector<vector<vector<Pixel> > > ){
  }
