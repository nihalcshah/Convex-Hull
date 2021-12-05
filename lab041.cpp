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
    public:
        double first;
        double second;
        Point(double x, double y){
            first = x;
            second = y;
        }
        ~Point(){}
        bool operator==(const Point& p) const
        {
            return first == p.first && second == p.second;
        }
};
