#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <set>

using namespace std;

class Movies
{
   public:
      struct Movie
      {
         string name;
         double rating;
         Movie(string name1 = "", double rating1 = 0.0) : name(name1), rating(rating1) {}
      };

      struct reverseMovie
      {
         string name;
         double rating;
         reverseMovie(string name1 = "", double rating1 = 0.0) : name(name1), rating(rating1) {}
      };

      void print();
};

// #include "movies.cpp"
#endif
