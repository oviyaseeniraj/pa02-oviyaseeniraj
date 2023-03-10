// Spring'22
// Instructor: Diba Mirza
// Student name: Oviya Seeniraj
#include <iostream>
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

bool operator==(Movies::Movie const &m1, Movies::Movie const &m2)
{
    return (m1.name == m2.name);
}

bool operator<(Movies::Movie const &m1, Movies::Movie const &m2)
{
    return (m1.name < m2.name);
}

bool operator>(Movies::Movie const &m1, Movies::Movie const &m2)
{
    return (m1.name > m2.name);
}

bool operator==(Movies::reverseMovie const &m1, Movies::reverseMovie const &m2)
{
    return (m1.rating == m2.rating);
}

bool operator>(Movies::reverseMovie const &m1, Movies::reverseMovie const &m2)
{
    return (m1.rating < m2.rating);
}

bool operator<(Movies::reverseMovie const &m1, Movies::reverseMovie const &m2)
{
    return (m1.rating > m2.rating);
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
    set<Movies::Movie> allMovies;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline(movieFile, line) && parseLine(line, movieName, movieRating))
    {
        // Use std::string movieName and double movieRating
        // to construct your Movie objects
        // cout << movieName << " has rating " << movieRating << endl;
        // insert elements into your data structure

        Movies::Movie m = Movies::Movie(movieName, movieRating);
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

    vector<Movies::Movie> highestRated;
    for (int i = 2; i < argc; i++)
    {
        double max = -42;
        multiset<Movies::reverseMovie> prefix;
        string empty = "";
        string prefix1 = empty.append(argv[i]);
        for (auto item : allMovies)
        {
            highestRated.push_back(Movies::Movie("", 0.0));
            if (item.name.substr(0, prefix1.length()) == prefix1)
            {
                prefix.insert(Movies::reverseMovie(item.name, item.rating));
                if (item.rating > max)
                {
                    highestRated.at(i - 2) = item;
                    max = item.rating;
                }
                else if (item.rating == max && item < highestRated.at(i - 2))
                {
                    highestRated.at(i - 2);
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

// RUNTIME ANALYSIS FOR PART 2 FOLLOWS BELOW:

/*  === PART 3A: TIME COMPLEXITY ANALYSIS ===

    In part 2, the worst case time complexity of my algorithm was O(n*m*log(n)), where m is the number of prefixes and n is the number of movies.
        To break down this conclusion, I will present an explanation of my code.
        1. To begin with, I wrote an outer for loop that iterated over the prefixes, which was m times, with a worst case time complexity of O(m).
            Current total worst case time complexity: O(m).
        2. I then wrote an inner for loop of movie iterations, which happened n times, giving me a worst case time complexity of O(n).
            Current total worst case time complexity: O(m) * O(n) = O(m*n).
        3. I then use an insertion operation of movies into a multiset, which has a worst case time complexity of  O(log n).
            Current total worst case time complexity: O(m) * O(n) * O (log n) = O(m*n*log(n))
        4. I compare strings a maximum of m times when printing the highest rated movie, which has a worst case time complexity of O(m).
            Current total worst case time complexity: O(m) * O(n) * O (log n) + O (m) = O(m*n*log(n) + m) -> O(m*n*log(n)
    Thus, the worst case time complexity of the algorithm is O(m*n*log(n)).

*/


/*  === PART 3B: SPACE COMPLEXITY ANALYSIS ===

    In part 2, the worst case space complexity of my algorithm was O(n+m), where m is the number of prefixes and n is the number of movies.
        To break down this conclusion, I will present an explanation of my code.
        1. I created a vector to store the highest rated movies of each prefix, which has a maximum space complexity of the maximum number of prefixes: O(m).
            Current total worst case space complexity: O(m)
        2. I used one multiset/BST to store movies that had the given prefixes that deconstructed at the end of the for loop, which has a maximum space complexity of the maximum number of movies: O(n)
            Current total worst case space complexity: O(m) + O(n) = O(m+n)
    Thus, the worst case space complexity of the algorithm is O(n+m).

 */


/*  === PART 3C: TRADEOFFS BETWEEN SPACE AND TIME COMPLEXITY ===

    TODO

 */

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
