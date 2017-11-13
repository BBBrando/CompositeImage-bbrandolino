//Brendon Brandolino
#include <iostream>
#include <string>
#include <vector>
#include "bitmap.h"
using namespace std;

const int maxNumImage = 10; // max number of images

vector<string> getImage();// get images from the user
bool isValid(string);// check the file name to ensure it is a bmp
bool sizeCheck(int , int , int, int); // check the size of the images and compare to first
vector<vector<vector<Pixel> > > createBmpVector(vector<string>); // create a 3D vector of images
vector<vector<Pixel> > collapseVector(vector<vector<vector<Pixel> > > & bmpVector); //collpase the vectors into a single layer with averaged pixels
void printImage(vector<vector<Pixel> >); // save the image

int main() {
  vector<vector<vector<Pixel> > > bmpVector;
  Pixel rgb;
  printImage(collapseVector(bmpVector = createBmpVector(getImage())));
  return 0;
}
vector<vector<vector<Pixel> > > createBmpVector(vector<string>fileNames){
  vector<vector<vector<Pixel> > > bmpVector;
  Bitmap image;
  Pixel rgb;

  for (int z = 0; z < fileNames.size();) {
    image.open(fileNames[z]);
    bmpVector.resize(fileNames.size());
    bmpVector[z]= image.toPixelMatrix();
    z++;
    }
  return bmpVector;
}
vector<string> getImage(){
  vector<string> imageVector;
  int count = 0;
  int x;
  int y;
  int checkX;
  int checkY;
  Bitmap image;
  vector<vector<Pixel> > bmp;
  Pixel rgb;

  do {
    cout<<"Please enter a file name"<<endl;
    string im;
    cin>>im;
    if (im == "DONE") {
      if (imageVector.size()>1) {
        return imageVector;
      }
      else{
        cout<<"At least 2 images are required"<<endl;
      }
    }
    if (isValid(im) == true) {
      count++;
        if (count == 1) {
          image.open(im);
          bmp= image.toPixelMatrix();
          x = bmp.size();
          y = bmp[0].size();
          imageVector.push_back(im);
        }
        else{
          image.open(im);
          bmp= image.toPixelMatrix();
          checkX = bmp.size();
          checkY = bmp[0].size();
        if (sizeCheck(x, y, checkX, checkY)== false){
          cout<<"The images are not the same size"<<endl;
        }
        if (sizeCheck(x, y, checkX, checkY)== true){
          imageVector.push_back(im);
        }
      }
    }
    if (isValid(im)== false) {
      cout<<"Please enter a VALID file name"<<endl;
    }
  } while(count < maxNumImage);
  return imageVector;
}

bool sizeCheck(int x, int y, int checkX, int checkY){
  if (x == checkX) {
    if(y == checkY){
      return true;
    }
  }
  //cout<<x<<"  "<<y<<"     "<<checkX<<"    "<<checkY<<endl;
return false;
}

bool isValid(string im){
  Bitmap image;
  image.open(im);
  if (image.isImage() == false) {
    return false;
    }
  else{
    return true;
    }
  }

  vector<vector<Pixel> > collapseVector(vector<vector<vector<Pixel> > > & bmpVector){
    int r = 0;
    int g = 0;
    int b = 0;
    Pixel RGB;
    int rTemp;
    int gTemp;
    int bTemp;
    int size = bmpVector.size();
    vector<vector<Pixel> > finalImage;
    Bitmap image;

    finalImage.resize(bmpVector[0].size());  // size the finalImage vector appropriatly
    for (int x = 0; x < finalImage.size(); x++) {
     finalImage[x].resize(bmpVector[0][0].size());
    }
        for (int rows = 0; rows < bmpVector[0].size(); rows++) {
          for (int cols = 0; cols < bmpVector[0][0].size(); cols++) {
            for (int images = 0; images < bmpVector.size(); images++) {
            r = bmpVector[images][rows][cols].red;
            g = bmpVector[images][rows][cols].green;
            b = bmpVector[images][rows][cols].blue;
            RGB = bmpVector[images][rows][cols];
            rTemp = rTemp + r;
            gTemp = gTemp + g;
            bTemp = bTemp + b;
          }
          r = rTemp/size;
          g = gTemp/size;
          b = bTemp/size;
          rTemp = 0;
          gTemp = 0;
          bTemp = 0;
            if (r > 255) {  //ensure that the pixels are valid numerically
              r = 255;}
            if (r < 0) {
              r = 0;}
            if (g > 255) {
              g = 255;}
            if (g < 0) {
              g = 0;}
            if (b > 255) {
              b = 255;}
            if (b < 0) {
              b = 0;}
          RGB.red = r;
          RGB.green = g;
          RGB.blue = b;
          finalImage[rows][cols] = RGB;
        }
        if (rows == (bmpVector[0].size()/2)) {
          cout<<"50% completed."<<endl;
        }
        if (rows == (bmpVector[0].size()/4)) {
          cout<<"25% completed."<<endl;
        }
        if (rows == (bmpVector[0].size()/10)) {
          cout<<"10% completed."<<endl;
        }
        if (rows == (bmpVector[0].size()*3/4)) {
          cout<<"75% completed."<<endl;
        }
      }
      cout<<"COMPLETED"<<endl;
  return finalImage;
  }

  void printImage(vector<vector<Pixel> >finalImage){
    Bitmap image;

    image.fromPixelMatrix(finalImage);
    image.save("composite-bbrandolino.bmp");
  }
