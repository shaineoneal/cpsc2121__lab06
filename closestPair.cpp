/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};

void checkCell(point inputPoint, vector<point> cell, double &smallDist) {
       
    double dist;    //distance between two points
    //iterate thru all cells in vector
    for(int i = 0; i < cell.size(); i++) {
        //calculate distance
        dist = sqrt(pow((cell.at(i).x - inputPoint.x), 2) + pow((cell.at(i).y - inputPoint.y), 2));

        //check if new distance is smaller than current smallest, update current smallest
        if(dist < smallDist && dist != 0) {
            smallDist = dist;
        }
    }
}



/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
    remaining (#of points) lines: x-value and y-value of point
    one point per line
    x-value and y-value are double-precision values and
    bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename) {
    
    ifstream file(filename);  //open file

    //error check file opening
    if(!file.is_open()) { 
        cerr << "Error opening file!" << endl;
        return -1; 
    } 

    //read number of points listed
    string line;    //temp value to hold line from file
    int num_points; //num of points from first line of file

    getline(file, line);
    num_points = stoi(line);

    int xpos = 0, ypos = 0;    //coordinate to cell of grid
            
    int b = (int)sqrt(num_points);  //the num of divisions along x and y axis
            //within the unit square for spatial hashing
    double interval = 1/(double)b;

    //initialize array of b*b cells to contain empty set of points
    vector<point> grid[b][b];
    double smallDist = 1;

    //read the remainder of input file, adding each point to the appropirate cell
    for(int i = 1; i < num_points; i++) {
        //create point
        point inputPoint;
        file >> inputPoint.x >> inputPoint.y;

        //determine cell
        xpos = inputPoint.x/interval;
        ypos = inputPoint.y/interval;

        //pick a cell
        grid[xpos][ypos].push_back(inputPoint);

        //compare point to all others within its cell
        checkCell(inputPoint, grid[xpos][ypos], smallDist);

        //check all adjacent cells
        if(xpos - 1 >= 0 ) {
            if(ypos - 1 >= 0) {
                checkCell(inputPoint, grid[xpos - 1][ypos - 1], smallDist); //upper left
            }
            checkCell(inputPoint, grid[xpos - 1][ypos], smallDist); //left
        }
        if(xpos + 1 <= b) {
            if(ypos + 1 <= b) {
                checkCell(inputPoint, grid[xpos + 1][ypos - 1], smallDist); //upper right
            }
            checkCell(inputPoint, grid[xpos + 1][ypos], smallDist); //right
        }
        if(ypos - 1 >= 0) {
            checkCell(inputPoint, grid[xpos][ypos - 1], smallDist); //up
        }
        if(ypos + 1 <= b) {
            checkCell(inputPoint, grid[xpos][ypos + 1], smallDist); //down
        }
        delete inputPoint;
        //keep smallest distance obtained
    } 
    //return smallest distance
    return smallDist;
}

int main()
{
    double min;
    string filename;
    cout << "File with list of points within unit square: ";
    cin >> filename;
    min = closestPair(filename);
    cout << setprecision(16);
    cout << "Distance between closest pair of points: " << min << endl;
    return 0;
}