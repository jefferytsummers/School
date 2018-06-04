#include <iostream>
#include <cstdlib>
#include "SumofGaussians.h"
#include <fstream>

using std::cin;
using std::cout;
using std::ofstream;

typedef unsigned int uint;

int main(int argc, char* argv[])
{
    //Seed random function with first terminal argument.
    srand(atoi(argv[1]));

    //Variable declarations.
    uint           dimension = atoi(argv[2]),       //Dimension of the domain.
                   centers   = atoi(argv[3]);       //Number of Gaussians.
    float          step      = 1e-2;                //Step size.
    double         epsilon   = 1e-8,                //Tolerance.
                   beforeClimb,                     //Stores pre-step value.
                   x[dimension],                    //Stores coordinate x_i
                   G[dimension];                    //Gradient
    SumofGaussians curve(dimension, centers);       //Generate a curve.

    //Pick random starting values for each dimension.
    for(uint i = 0; i < dimension; ++i)
        x[i] = getRandom();

    //Perform the gradient ascent.
    do
    {
        curve.deriv(x, G);                          //Generate gradient.
        beforeClimb = curve.eval(x);                //Save initial point value.
        cout << x[0] << ' ' << beforeClimb << '\n'; //Output point and value.
        for(uint i = 0; i < dimension; ++i)         //Update coordinates.
            x[i] += step*G[i];
    } while(curve.eval(x) - beforeClimb > epsilon); /*Repeat until the
                                                      difference is less than
                                                      the tolerance.*/

    /*
    //Delete this before turn in.
    double* y[101];
    ofstream outFile("curveVals.txt");
    for(uint i = 0; i < 101; ++i)
    {
        y[i] = new double[1];
        cin >> y[i][0];
        outFile << y[i][0] << ' ' << curve.eval(y[i]) << '\n';
    }
    outFile.close();
    ///////////////
    */

    return 0;
}
