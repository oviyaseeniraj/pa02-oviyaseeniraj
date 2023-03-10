#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>

using namespace std;

class Movies {
};

struct Movie
{
   Movie(string name1 = "", double rating1 = 0.0):name(name1), rating(rating1){}
   Movie(double rating1 = 0.0, string name1 = ""): rating(rating1), name(name1){}
   string name;
   double rating;
};

struct reverseMovie
{
   reverseMovie(string name1 = "", double rating1 = 0.0):name(name1), rating(rating1){}
   string name;
   double rating;
};

#include "movies.cpp" 
#endif
