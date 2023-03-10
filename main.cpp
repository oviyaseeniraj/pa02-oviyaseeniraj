// Spring'22
// Instructor: Diba Mirza
// Student name: Oviya Seeniraj
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include "movies.h"

using namespace std;

bool parseLine(string &line, string &movieName, double &movieRating);

bool operator==(Movie const &m1, Movie const &m2)
{
    return (m1.name == m2.name);
}

bool operator==(reverseMovie const &m1, reverseMovie const &m2)
{
    return (m1.rating == m2.rating);
}

bool operator<(reverseMovie const &m1, reverseMovie const &m2)
{
    return (m1.rating > m2.rating);
}

bool operator>(reverseMovie const &m1, reverseMovie const &m2)
{
    return (m1.rating < m2.rating);
}

bool operator<(Movie const &m1, Movie const &m2)
{
    return (m1.name < m2.name);
}

bool operator>(Movie const &m1, Movie const &m2)
{
    return (m1.name > m2.name);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[0] << " filename prefix1 prefix2 ... prefix n " << endl;
        exit(1);
    }

    ifstream movieFile(argv[1]);

    if (movieFile.fail())
    {
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    // Create an object of a STL data-structure to store all the movies
    set<Movie> allMovies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline(movieFile, line) && parseLine(line, movieName, movieRating))
    {
        // Use std::string movieName and double movieRating
        // to construct your Movie objects
        // cout << movieName << " has rating " << movieRating << endl;
        // insert elements into your data structure

        Movie m = Movie(movieName, movieRating);
        allMovies.insert(m);
    }

    movieFile.close();

    if (argc == 2)
    {
        // print all the movies in ascending alphabetical order of movie names
        for (auto mov : allMovies)
        {
            cout << mov.name << ", " << std::fixed << std::setprecision(1) << mov.rating << endl;
        }
        return 0;
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message

    vector<Movie> highestRated;
    for (int i = 2; i < argc; i++)
    {
        double max = -42;
        multiset<reverseMovie> prefix;
        string empty = "";
        string prefix1 = empty.append(argv[i]);
        for (auto item : allMovies)
        {
            highestRated.push_back(Movie("", 0.0));
            if (item.name.substr(0, prefix1.length()) == prefix1)
            {
                prefix.insert(reverseMovie(item.name, item.rating));
                if (item.rating > max)
                {
                    highestRated.at(i-2) = item;
                    max = item.rating;
                }
                else if (item.rating == max && item < highestRated.at(i-2))
                {
                    highestRated.at(i-2);
                }
            }
        }
        for (auto mov : prefix)
        {
            cout << mov.name << ", " << std::fixed << std::setprecision(1) << mov.rating << endl;
        }

        if (prefix.empty())
        {
            cout << "No movies found with prefix " << prefix1 << endl;
        }

        cout << endl;
    }

    for (int i = 0; i < argc - 2; i++)
    {
        if (highestRated.at(i).name != "")
        {
            cout << "Best movie with prefix "
                << argv[i + 2]
                << " is: "
                << highestRated.at(i).name
                << " with rating " << std::fixed << std::setprecision(1) << highestRated.at(i).rating << endl;
        }
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating)
{
    if (line.length() <= 0)
        return false;
    string tempRating = "";

    bool flag = false;
    movieName = tempRating = "", movieRating = 0.0, flag = false;

    for (int i = 0; i < int(line.length()); i++)
    {
        if (flag)
            tempRating += line[i];
        else if (line[i] == ',' && line[0] != '"')
            flag = true;
        else
        {
            if (i == 0 && line[0] == '"')
                continue;
            if (line[i] == '"')
            {
                i++;
                flag = true;
                continue;
            }
            movieName += line[i];
        }
    }

    movieRating = stod(tempRating);
    return true;
}
