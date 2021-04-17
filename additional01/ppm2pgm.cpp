/*
* file: ppm2pgm.cpp
* Enigma Swan Adams
* 4/16/2021
*
* source code for the additional program 1 section of
* homework 7. For a full description see blackbuard
*
* takes a .ppm file and converts it to pgm file
*/

/* code expects this format from the ppm
*  the file may have as many comments as neccessary
*  but otherewise the formatt needs to be followed exactly
P3
# CREATOR: GIMP PNM Filter Version 1.1
# other comments
80 80
255
0
0
1
10
11
8
*/

#include <iostream>
#include <vector> 
#include <fstream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;
using std::stoi;
using std::ofstream;




int main()
{
    //cout << "# Program to convert a ppm to ascii art" << endl;

    // open the file
    string infile = "parrot02.ppm"; // copied the file 
    ifstream fin(infile);
    if (!fin) {
        cout << "# Error opening " << infile << endl;
        exit(1);
    }
    //cout << "# Opened " << infile << endl;

    // read the magic number
    string line;
    getline(fin, line);

    if (line.size() < 2) {
        cout << "# Magic number does not exist" << endl;
    }
    else {
        if (line.at(0) == 'P' && line.at(1) == '3') {
            //cout << "# PPM (text)" << endl;
        }
        else {
            cout << "# Unable to read magic number P3. Magic number was: " << line.at(0) << line.at(1) << " instead" << endl;
            exit(2);
        }
    }

    //open a file and write the new magic number to it  
    ofstream fout("parrot_grey.pgm");
    if (!fout) {
        cout << "# Error writing file" << endl;
    }
    fout <<"P2" << endl;



    int xres, yres, maxval;
    //process comments
    int comments = 0;
    getline(fin, line);
    while (line.at(0) == '#') {
        comments++;
        cout << "# Ignoring comment number " << comments << endl;
        getline(fin, line);

    }

    //get xres and yres from line
    xres = stoi(line.substr(0, 2));
    yres = stoi(line.substr(2, 3));

    // program expects no more comments from this point on
    //get maxval
    fin >> maxval;
    if (!fin) {
        cout << "Error reading stream" << endl;
        exit(3);
    }

    //write the size (xres and yres) and the maxval
    fout << xres << " " << yres << endl;
    fout << maxval << endl;
    //print aquired values
    //cout << "Image size: " << xres << " x " << yres << endl;
    //cout << "Maxval = " << maxval << endl;

    // loop for xres * yres iterations
    int r, g, b, iy;
    int y;
    //THIS WILL NEED TO BE CHANGED
    //vector<char> values = { '@', 'M', '0', '#', 'I', 'S', 'O', 'i','s', '*', '+', '^', '~', '-', '`', ' ' }; 
    for (int i = 0; i < xres * yres; i++) {
        fin >> r >> g >> b;
        if (!fin) {
            cout << "Error reading stream" << endl;
            exit(4);
        }

        // Y = 0.2126R + 0.7152G + 0.0722B (from HW7) one value for grayscale instead of three for rgb
        y = 0.2126 * r + 0.7152 * g + 0.0722 * b;

        // tests
        if (y < 0.0 || y >= maxval + 1.0) cout << "ERROR!!!!!!!!!!!" << endl;
        //    cout << r << " " << g << " " << b;
        //    cout << " => " << y;

        //DONT NEED iy ANYMORE SINCE GREYSCALE VALUES ARE 0-255
        //iy = (int)y;
        // iy should be [0...255]
        //if (iy < 0 || iy > maxval) cout << "ERROR!!!!!!!!!!!!!!" << endl;
        //    cout << " => " << iy;

        //iy /= values.size();
        // iy should be [0...15]
        //if (iy < 0 || iy > values.size() - 1) cout << "ERROR!!!!!!!!!!!!!!" << endl;
        //    cout << " => " << iy << endl;

        //write the grescale value y to the file
        fout << y << endl;
        
    }

    cout << "Program finished" << endl;



}
