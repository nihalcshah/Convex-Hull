#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>  
#include <math.h>
#include <fstream>
#include "iomanip"
#include <list>
#include <iterator>
#include "algorithm"
#include "cstring"
#include <unordered_map>
#include <chrono> 

using namespace std;
using namespace std::chrono;


class Point{
    double first;
    double second;
    public:
        Point(double x, double y){
            first = x;
            second = y;
        }
        double getX(){
            return first;
        }
        double getY(){
            return second;
        }
        void setX(double x){
            first = x;
        }
        void setY(double y){
            second = y;
        }
        bool rightOf(Point start, Point end){
            return ((end.getX() - start.getX())*(second - start.getY()) - (end.getY() - start.getY())*(first - start.getX())) < 0;
            // return (first > k.findx(second));
        }
        bool leftOf(Point start, Point end){
            return ((end.getX() - start.getX())*(second - start.getY()) - (end.getY() - start.getY())*(first - start.getX())) > 0;
            // return (first > k.findx(second));
        }
        double distance(Point p){
            return sqrt(pow(first-p.getX(),2)+pow(second-p.getY(),2));
        }
        ~Point(){}
        bool operator==(const Point& p) const
        {
            return first == p.first && second == p.second;
        }
    
};

class Line{
    double slope;
    double yintercept;
    double xintercept;
    double x1;
    double x2;
    double y1;
    double y2;
    public:
        
        Line(double x, double y, double secondx, double secondy){
            x1 = x;
            y1=y;
            x2= secondx;
            y2=secondy;
            slope = (y2-y1)/(x2-x1);
            yintercept = y1-(slope*x1);
            xintercept = -yintercept/slope;
        }
    Line findPerp(double x, double y){
        double pslope = -1/slope;
        double ydouble = y-(pslope*x);
        Line l = Line(x, y, 0, ydouble);
        return l;
    }
    double findy(double xval){
        return (slope*xval)+yintercept;
    }
    Point getStart(){
        return Point(x1,y1);
    }
    Point getEnd(){
        return Point(x2,y2);
    }
    Point intersection(Line l){
        double x = (yintercept-l.yintercept)/(l.slope-slope);
        double y = findy(x);
        return Point(x, y);
    }
    double findx(double yval){
        return (yval-yintercept)/slope;
    }
    Line eline(){
        int firstx;
        int secondx;
        int firsty;
        int secondy;
        if(yintercept<0){
            double m = findy(1);
            firstx = (int) (xintercept*800);
            firsty = 0;
            if(m>1){
                secondx = (int) (findx(1)*800);
                secondy = 799;
            }else{
                secondx = 799;
                secondy = (int) (findy(1)*800);
            }
        }else if(yintercept>1){
            double m = findy(1);
            secondx = (int) (findx(1)*800);
            secondy = 799;
            if(m<0){
                firstx = (int) (xintercept*800);
                firsty = 0;
            }else{
                firstx = 799;
                firsty = (int) (findy(1)*800);      
            }
        } else if(xintercept<0){
            double m = findy(1);
            firstx = 0;
            firsty = (int) (yintercept*800);
            if(m>1){
                secondx = (int) (findx(1)*800);
                secondy = 799;
            }else{
                secondx = 799;
                secondy = (int) (findy(1)*800);
            }
        } else if(xintercept>1){
            double m = findy(0);
            secondx = 799;
            secondy = (int) (findy(1)*800);
            if(m<1){
                firstx = 0;
                firsty = (int) (yintercept*800);
            }else{
                firstx = (int) (findx(1)*800);
                firsty = 799;
            }
        }else{
            secondy = (int) (yintercept*800);
            secondx = 0;
            firstx = (int) (xintercept*800);
            firsty = 0;
        }
        Line k = Line(firstx, firsty, secondx, secondy);
        return k;
    }
};


class TwoPoints{
    public:
        Point first = Point(0,0);
        Point second = Point(0,0);
        double dist;
        TwoPoints( double d,Point x, Point y){
            first = x;
            second = y;
            dist = d;
        }
};

class Draw{
    public:
        string (*grid)[400];
        Draw(string (*g)[400]){
            grid = g;
        }
        string (*segment(int x1, int y1, int x2, int y2, string color))[400]{
                    int distance1 = x2-x1;
                    int distance2 = y2-y1;
                    int distancechange = distance2-distance1;
                    for(int i =x1; i<=x2; ++i){
                        grid[i][y1] = color;
                        if (distancechange>0){
                            y1=y1+1;
                            distancechange = distancechange - distance1;
                        }
                        distancechange = distancechange + distance2;
                    }
                    return grid;
                }

        string (*segment3(int x1, int y1, int x2, int y2, string color))[400]{
            // return g;
            // cout<<"x1: " + to_string(x1) + " y1: " + to_string(y1) <<endl;
            // cout<<"x2: " + to_string(x2) + " y2: " + to_string(y2) <<endl;
            int distance1 = x2-x1;
            int distance2 = y2-y1;
            int distancechange = distance1-distance2;
            
            for(int i =y1; i<=y2; ++i){
                grid[x1][i] = color;
                // cout<<grid[x1][i]<<endl;
                if (distancechange>0){
                    x1=x1+1;
                    distancechange = distancechange - distance2;
                }
                distancechange = distancechange + distance1;
            }
            return grid;
        }

        string (*segment2(int x1, int y1, int x2, int y2, string color))[400]{
            // cout<<"x1: " + to_string(x1) + " y1: " + to_string(y1) <<endl;
            // cout<<"x2: " + to_string(x2) + " y2: " + to_string(y2) <<endl;
            // cout<<"segment 2"<<endl;
            // if(x1==593){
            //     cout<<"hi"<<endl;
            // }
            int distance1 = x2-x1;
            int distance2 = y2-y1;
            int distancechange = distance2-distance1;
            for(int i =x1; i>=x2; i--){
                grid[i][y1] = color;
                // cout<<grid[i][y1]<<endl;
                if (distancechange<0){
                    y1+=1;
                    distancechange = distancechange - distance1;
                }
                distancechange = distancechange - distance2;
            }
            // cout<<"x1: "+ to_string(x1) + " y1:" + to_string(y1)<<endl;
            return grid;
        }

        string (*segment4(int x1, int y1, int x2, int y2, string color))[400]{
            int distance1 = x2-x1;
            int distance2 = y2-y1;
            int distancechange = distance1-distance2;
            
            for(int i =y1; i<=y2; i++){
                if(x1<0){
                    break;
                }
                grid[x1][i] = color;
                // cout<<grid[x1][i]<<endl;
                if (distancechange<0){
                    x1-=1;
                    distancechange = distancechange + distance2;
                }
                distancechange = distancechange + distance1;
            }
            return grid;
        }
        //Decides which Line Segment algorithm to utilize.
        string (*gensegment(Point p1, Point p2, string color))[400]{
            int x1 = p1.getX()*400;
            int y1 = p1.getY()*400;
            int x2 = p2.getX()*400;
            int y2 = p2.getY()*400;
            if (x2>x1&& y2>y1){
                if(x2-x1<y2-y1){
                    return segment3(x1,y1, x2, y2, color );
                }
                return segment(x1, y1, x2, y2,color );
            }
            else if (x1>x2 && y1>y2){
                if(x1-x2<y1-y2){
                    return segment3(x2,y2, x1, y1, color );
                }
                return segment(x2, y2, x1, y1, color);
            }
            else{
                // cout<<abs(x1-x2)<<endl;
                if(abs(x1-x2)<abs(y1-y2)){
                    if(y1>y2){
                        return segment4(x2,y2, x1, y1, color );
                    }
                    return segment4(x1,y1, x2, y2, color );
                }
                if(x1>x2){
                    return segment2(x1, y1, x2, y2, color );
                }
                return segment2(x2, y2, x1, y1, color);
                
            }
        }
        string (*circle(double x, double y, int radius))[400]{
            int xcenter = (int) (x*400);
            int ycenter = (int) (y*400);
            int ym = radius;
            int xm = 0;
            int dm = 3 - (2*radius);
            if(xcenter+xm<400){
                if(ycenter+ym<400){
                    grid[xcenter+xm][ycenter +ym] = "0 1 0 ";
                }
                if(ycenter-ym>=0){
                    grid[xcenter+xm][ycenter -ym] = "0 1 0 "; 
                }
            }
            if(xcenter-xm>0){
                if(ycenter+ym<400){
                    grid[xcenter-xm][ycenter+ym] = "0 1 0 ";
                }
                if(ycenter-ym>=0){
                    grid[xcenter-xm][ycenter -ym] = "0 1 0 ";
                }
            }

            if(xcenter+ym<400){
                if(ycenter+xm<400){
                    grid[xcenter+ym][ycenter +xm] = "0 1 0 ";
                }
                if(ycenter-xm>=0){
                    grid[xcenter+ym][ycenter -xm] = "0 1 0 "; 
                }
            }
            if(xcenter-ym>0){
                if(ycenter+xm<400){
                    grid[xcenter-ym][ycenter+xm] = "0 1 0 ";
                }
                if(ycenter-xm>=0){
                    grid[xcenter-ym][ycenter -xm] = "0 1 0 ";
                }
            }
            while(ym>=xm){
                xm++;
                if(dm>0){
                    ym--;
                    dm= dm+ 4*(xm-ym) + 10;
                }else{
                    dm = dm+(4*xm)+6;
                }
                if(xcenter+xm<400){
                    if(ycenter+ym<400){
                        grid[xcenter+xm][ycenter +ym] = "0 1 0 ";
                        }
                    if(ycenter-ym>=0){
                        grid[xcenter+xm][ycenter -ym] = "0 1 0 "; 
                        }
                }
                if(xcenter-xm>0){
                    if(ycenter+ym<400){
                        grid[xcenter-xm][ycenter+ym] = "0 1 0 ";
                        }
                    if(ycenter-ym>=0){
                        grid[xcenter-xm][ycenter -ym] = "0 1 0 ";
                        }
                }

                if(xcenter+ym<400){
                    if(ycenter+xm<400){
                        grid[xcenter+ym][ycenter +xm] = "0 1 0 ";
                        }
                    if(ycenter-xm>0){
                        grid[xcenter+ym][ycenter -xm] = "0 1 0 "; 
                        }
                }
                if(xcenter-ym>0){
                    if(ycenter+xm<400){
                        grid[xcenter-ym][ycenter+xm] = "0 1 0 ";
                        }
                    if(ycenter-xm>=0){
                        grid[xcenter-ym][ycenter -xm] = "0 1 0 ";
                        }
                }
            }
            return grid;
        }

        //Draws a line
        string (*line(Line l))[400]{
            
            grid = gensegment(l.getStart(),l.getEnd(), "1 0 0 ");
            return grid;
        }

        string (*plotpoints(vector<Point> l))[400]{
            vector<Point>::iterator it;
            for(it = l.begin(); it!=l.end(); it++){
                int x = (int) ((*it).getX()*400);
                int y = (int) ((*it).getY()*400);
                grid[x][y] = "1 1 0 ";
                grid = circle((*it).getX(), (*it).getY(), 3);
            }
            return grid;
        }
        
};


class Lab04{
    string (*grid)[400] = new string[400][400];
    vector <Point> vec;
    vector <Point> convex;
    public:
        void init(){
            for(int i =0; i<400;i++){
                for(int k = 0; k<400;k++){
                    grid[i][k] ="0 0 0 ";
                }
            }
        }
        void genrand(){
            for(int i =0; i<60; i++){
                double x = (double)rand() / (double)RAND_MAX;
                double y = (double)rand() / (double)RAND_MAX;
                vec.push_back(Point(x,y));

            }
        }

        void writearr(){
            ofstream ofs;
            ofs.open("output.ppm");
            int total = 0;
            ofs << "P3" << endl << 400 << " " << 400 << endl << "1" << endl;
            for (int i = 0; i<400; ++i){
                for (int k = 0; k<400; ++k){
                    string s = grid[k][i];
                    ofs << grid[k][i];
                }
                ofs << "\n";
            }
            ofs.close();
        }


        void quickHull(vector<Point>& vect){
            //find the left and right most point in the vector
            Point leftMost = vect[0];
            Point rightMost = vect[0];
            for(int i = 1; i<vect.size(); i++){
                if(vect[i].getX() < leftMost.getX()){
                    leftMost = vect[i];
                }
                if(vect[i].getX() > rightMost.getX()){
                    rightMost = vect[i];
                }
            }
            Line sectorline = Line(leftMost.getX(), leftMost.getY(), rightMost.getX(), rightMost.getY());
            convex.push_back(leftMost);
            convex.push_back(rightMost);
            vector<Point> ab;
            vector<Point> ba;
            for(int i = 0; i<vect.size(); i++){
                if(vect[i].rightOf(leftMost, rightMost)){
                    ab.push_back(vect[i]);
                }
                if(vect[i].rightOf(rightMost, leftMost)){
                    ba.push_back(vect[i]);
                }
            }
            findHull(ab,leftMost,rightMost);
            findHull(ba,rightMost,leftMost);
            // display convex vector
            // for(int i=)
            //print convex vector
            // for(int i = 0; i<convex.size(); i++){
            //     cout<<convex[i].getX()<<" "<<convex[i].getY()<<endl;
            // }
        }
        void findHull(vector<Point>& v, Point p, Point q){
            // cout<<p.getX()<<" "<<p.getY()<<" "<<q.getX()<<" "<<q.getY()<<endl;
            //Base Case
            if(v.size() == 0){
                return;
            }
            //find the point with the maximum distance from the line
            Point max = v[0];
            double dist = 0;
            Line l = Line(p.getX(), p.getY(), q.getX(), q.getY());
            for(int i = 0; i<v.size(); i++){
                
                Line perpl = l.findPerp(v[i].getX(), v[i].getY());
                Point intpoint = perpl.intersection(l);  
                double d = v[i].distance(intpoint);
                if(d>dist){
                    dist = d;
                    max = v[i];
                }
            }
            vector<Point>::iterator it;
            
            for(int i=0; i<convex.size(); i++){
                if(convex[i] == p){
                    convex.insert(convex.begin()+i+1, max);
                    break;
                }
            }
            // convex.push_back(max);
            //Find points to the right of pc
            // Line pcline = Line(p.getX(), p.getY(), max.getX(), max.getY());
            // Line cqline = Line(max.getX(), max.getY(), q.getX(), q.getY());
            vector <Point> pcset;
            vector <Point> cqset;
            for(int i = 0; i<v.size(); i++){
                if(v[i].rightOf(p, max)){
                    pcset.push_back(v[i]);
                }
                if(v[i].rightOf(max, q)){
                    cqset.push_back(v[i]);
                }
            }
            findHull(pcset, p, max);
            findHull(cqset, max, q);
        }
    
        void display(){
            Draw d = Draw(grid);
            grid = d.plotpoints(vec);
            for(int i =1; i<convex.size(); i++){
                grid = d.line(Line(convex[i-1].getX(), convex[i-1].getY(), convex[i].getX(), convex[i].getY()));
            }
            grid = d.line(Line(convex[0].getX(), convex[0].getY(), convex[convex.size()-1].getX(), convex[convex.size()-1].getY()));
            writearr();
        }
        void part1(){
            quickHull(vec);
            display();
        }
};

int main(){
    Lab04 l;
    srand(time(NULL));
    l.genrand();
    l.init();
    l.part1();
}