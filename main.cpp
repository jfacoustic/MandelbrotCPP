//this program computes the mandelbrot set
//Joshua Mathews 2016

#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

double mid(double x, double y)
{
    return (x+y)/2;
}
void zoom(double & xmin, double & xmax, double & ymin, double & ymax, double percentZoomX, double percentZoomY)
{
    xmin = xmin + (mid(xmin, xmax) - xmin)*percentZoomX/100;
    ymin = ymin + (mid(ymin, ymax) - ymin)*percentZoomY/100;
    xmax = xmax - (xmax - mid(xmin, xmax))*percentZoomX/100;
    ymax = ymax - (ymax - mid(ymin, ymax))*percentZoomY/100;
    
}

void print(int scaleX, int scaleY, double maxX, double minX, double maxY, double minY, double & maxIteration)
{
        for(int j = 0; j< scaleX; j++)
        {
            for(int i = 0; i < scaleY; i++)
            {
                double x0 = ((maxX -minX)* (static_cast<double>(i) / static_cast<double>(scaleX)) + minX);
                double y0 = ((maxY - minY) * (static_cast<double>(j) / static_cast<double>(scaleY)) + minY);
                double x = 0.0;
                double y = 0.0;
                int iteration = 0;
                while(x*x + y*y < 2*2 && iteration < maxIteration)
                {
                    double xtemp = x*x - y*y + x0;
                    y = 2*x*y + y0;
                    x = xtemp;
                    iteration++;
                }
                if (iteration >= maxIteration -1)
                {
                    //mandelbrot[i][j] = true;
                    cout << "#";
                }
                else if (maxIteration/2 <= iteration && iteration < maxIteration -1)
                {
                    cout << "-";
                }
                else if(maxIteration/3 <= iteration && iteration < maxIteration/2)
                {
                    cout << "$";
                }
                else if(maxIteration/4 <= iteration && iteration < maxIteration/3)
                {
                    cout << "%";
                }
                else if(maxIteration/5 <= iteration && iteration < maxIteration/4)
                {
                    cout << ".";
                }
                
                else if (maxIteration/10 <= iteration && iteration < maxIteration/5)
                {
                    cout << "~";
                }
                else{
                    cout << " ";
                }
            }
            cout << endl;
        }
    
}

void outFile(int scaleX, int scaleY, double maxX, double minX, double maxY, double minY, double & maxIteration, ofstream & fout)
{
    for(int j = 0; j< scaleX; j++)
    {
        for(int i = 0; i < scaleY; i++)
        {
            double x0 = ((maxX -minX)* (static_cast<double>(i) / static_cast<double>(scaleX)) + minX);
            double y0 = ((maxY - minY) * (static_cast<double>(j) / static_cast<double>(scaleY)) + minY);
            double x = 0.0;
            double y = 0.0;
            int iteration = 0;
            while(x*x + y*y < 2*2 && iteration < maxIteration)
            {
                double xtemp = x*x - y*y + x0;
                y = 2*x*y + y0;
                x = xtemp;
                iteration++;
            }
            if (iteration >= maxIteration -1)
            {
                //mandelbrot[i][j] = true;
                fout << "#";
            }
            else if (maxIteration/2 <= iteration && iteration < maxIteration -1)
            {
                fout << "-";
            }
            else if(maxIteration/3 <= iteration && iteration < maxIteration/2)
            {
                fout << "$";
            }
            else if(maxIteration/4 <= iteration && iteration < maxIteration/3)
            {
                fout << "%";
            }
            else if(maxIteration/5 <= iteration && iteration < maxIteration/4)
            {
                fout << ".";
            }
            
            else if (maxIteration/10 <= iteration && iteration < maxIteration/5)
            {
                fout << "~";
            }
            else{
                fout << " ";
            }
        }
        fout << endl;
    }
    
}

int main()
{
    ofstream fout;
    fout.open("/Users/jmax8910/Desktop/mandelbrot/m.out");
    std::clock_t start;
    double duration;
    double maxX, minX, maxY, minY, zoomX, zoomY;
    //default zoom:
    zoomX = 80;
    zoomY = 100;
    maxX = .5;
    minX = -2;
    maxY = 1;
    minY = -1;
    double xAmount, yAmount;
    cout << setprecision(15);
    //zoom(minX, maxX, minY, maxY, 99);
    bool running = true;
    start = std::clock();
    int scaleX, scaleY;
    scaleX = 80; //note x ranges from -2 to 1.5
    scaleY = 100; //ranges from -1 to 1
    //bool mandelbrot[scaleX][scaleY];
    string command;
    double maxIteration = 1000;
    while (running)
    {
        //a bunch of greek
        cin >> command;
        if (command == "print")
            print(scaleX, scaleY, maxX, minX, maxY, minY, maxIteration);
        else if (command == "stop")
            running = false;
        else if (command == "zoom")
        {
            //cout << "Enter X-percent" << endl;
            cin >> zoomX;
            //cout << "Enter Y-percent" << endl;
            cin >> zoomY;
            zoom(minX, maxX, minY, maxY, zoomX, zoomY);
            maxIteration *= 1 + static_cast<int>(zoomX) / 100;
            print(scaleX, scaleY, maxX, minX, maxY, minY, maxIteration);
        }
        else if (command == "move")
        {
            //cout << "Enter X amount" << endl;
            cin >> xAmount;
            //cout << "Enter Y amount" << endl;
            cin >> yAmount;
            minX += xAmount;
            maxX += xAmount;
            minY += yAmount;
            maxY += yAmount;
            print(scaleX, scaleY, maxX, minX, maxY, minY, maxIteration);
        }
        else if (command == "getPos")
        {
            cout << "xMin: " << minX << endl;
            cout << "xMax: " << maxX << endl;
            cout << "yMin: " << minY << endl;
            cout << "yMax: " << maxY << endl;
            cout << "iterations: " << maxIteration << endl;
        }
        else if (command == "restart")
        {
            maxX = .5;
            minX = -2;
            maxY = 1;
            minY = -1;
            maxIteration = 1000;
        }
        else if (command == "down")
        {
            double multiplier;
            cin >> multiplier;
            double ydiff = maxY -minY;
            ydiff = multiplier * ydiff/scaleY;
            minY += ydiff;
            maxY += ydiff;
            print(scaleX, scaleY, maxX, minX, maxY, minY, maxIteration);
        }
        else if (command == "up")
        {
            double multiplier;
            cin >> multiplier;
            double ydiff = maxY -minY;
            ydiff = multiplier * ydiff/scaleY;
            minY -= ydiff;
            maxY -= ydiff;
            print(scaleX, scaleY, maxX, minX, maxY, minY, maxIteration);
        }
        else if (command == "left")
        {
            double multiplier;
            cin >> multiplier;
            double xdiff = maxX -minX;
            xdiff = multiplier * xdiff/scaleX;
            minX -= xdiff;
            maxX -= xdiff;
            print(scaleX, scaleY, maxX, minX, maxY, minY, maxIteration);
        }
        else if (command == "right")
        {
            double multiplier;
            cin >> multiplier;
            double xdiff = maxX -minX;
            xdiff = multiplier*xdiff/scaleX;
            minX += xdiff;
            maxX += xdiff;
            print(scaleX, scaleY, maxX, minX, maxY, minY, maxIteration);
        }
        else if (command == "changePos")
        {
            cin >> minX;
            cin >> maxX;
            cin >> minY;
            cin >> maxY;
            print(scaleX, scaleY, maxX, minX, maxY, minY, maxIteration);
        }
        else if (command == "iterations")
        {
            cin >> maxIteration;
        }
        else if (command == "outfile")
        {
            double outIteration;
            int scaleX1, scaleY1;
            cin >> scaleX1;
            cin >> scaleY1;
            cin >> outIteration;
            
            outFile(scaleX1, scaleY1, maxX, minX, maxY, minY, outIteration, fout);
        }
    }
    

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    cout << "time: " << duration << endl;
    
    return 0;
}