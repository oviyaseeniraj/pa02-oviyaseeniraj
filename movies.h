#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>

using namespace std;

class Movies {
};

struct Movie
{
   string name;
   double rating;
   Movie(string name1 = "", double rating1 = 0.0):name(name1), rating(rating1){}
   Movie(double rating1 = 0.0, string name1 = ""): rating(rating1), name(name1){}
};

struct reverseMovie
{
   string name;
   double rating;
   reverseMovie(string name1 = "", double rating1 = 0.0):name(name1), rating(rating1){}
};

#include "movies.cpp" 
#endif
