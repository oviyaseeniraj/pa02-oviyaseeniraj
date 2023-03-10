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
    return (m1.rating > m2.rating);
}

bool operator<(Movies::reverseMovie const &m1, Movies::reverseMovie const &m2)
{
    if (m1.rating == m2.rating)
    {
        return m1.name > m2.name;
    }
    return m1.rating < m2.rating;
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

    vector<Movies::Movie> highestRated(argc - 2);
    priority_queue<Movies::reverseMovie> prefix;
    for (int i = 2; i < argc; i++)
    {
        double max = -42;
        string prefix1 = argv[i];
        for (auto item : allMovies)
        {
            if (item.name.length() >= prefix1.length() && item.name.substr(0, prefix1.length()) == prefix1)
            {
                prefix.push(Movies::reverseMovie(item.name, item.rating));
                if (item.rating > max)
                {
                    highestRated[i - 2] = item;
                    max = item.rating;
                }
                else if (item.rating == max && item < highestRated[i - 2])
                {
                    highestRated[i - 2] = item;
                }
            }
        }

        if (prefix.empty())
        {
            cout << "No movies found with prefix " << prefix1 << endl;
        }
        else
        {
            while (!prefix.empty())
            {
                Movies::reverseMovie mov = prefix.top();
                cout << mov.name << ", " << std::fixed << std::setprecision(1) << mov.rating << endl;
                prefix.pop();
            }
        }

        cout << endl;
    }


    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for (int i = 0; i < argc - 2; i++)
    {
        if (highestRated[i].name != "")
        {
            cout << "Best movie with prefix "
                 << argv[i + 2]
                 << " is: "
                 << highestRated[i].name
                 << " with rating " << std::fixed << std::setprecision(1) << highestRated[i].rating << endl;
        }
    }

    return 0;
}

// RUNTIME ANALYSIS FOR PART 2 FOLLOWS BELOW:

/*  === PART 3A: TIME COMPLEXITY ANALYSIS ===

    In part 2, the worst case time complexity of my algorithm was O(n*m*log(k)), where m is the number of prefixes, n is the number of movies, and k is the maximum number of movies that begin with each prefix.
        To break down this conclusion, I will present an explanation of my code.
        1. To begin with, I wrote an outer for loop that iterated over the prefixes, which was m times, with a worst case time complexity of O(m).
            Current total worst case time complexity: O(m).
        2. I then wrote an inner for loop of movie iterations, which happened n times, giving me a worst case time complexity of O(n).
            Current total worst case time complexity: O(m) * O(n) = O(m*n).
        3. I use push and pop operations on a priority queue, which has a worst case time complexity of  O(log (# of movies matching the prefix)), aka O(log(k)).
            Current total worst case time complexity: O(m) * O(n) * O (log k) = O(m*n*log(k))
        4. I then use a while loop to print the movies that have the prefixes, which has a time complexity of O(k*log(k)).
            Current total worst case time complexity: O(m) * O(n) * O (log n) + O (k * log(k)) -> O(m*n*log(k)
        5. The second for loop to output the highest rated movies for each prefix is iterated # of prefix times, which is O(m).
            Current total worst case time complexity: O(m) * O(n) * O (log n) + O (k * log(k)) + O(n) -> O(m*n*log(k)
        Note: the if-else statements and variable declarations had no effect on the time complexity as they were constant O(1) operations.
    Thus, the worst case time complexity of the algorithm is O(m*n*log(k)).

*/

/*  === PART 3B: SPACE COMPLEXITY ANALYSIS ===

    In part 2, the worst case space complexity of my algorithm was O(m+k), where m is the number of prefixes and k is the maximum number of movies beginning with each prefix.
        To break down this conclusion, I will present an explanation of my code and allocated data structures.
        1. I created a vector to store the highest rated movies of each prefix, which has a maximum space complexity of the maximum number of prefixes: O(m).
            Current total worst case space complexity: O(m)
        2. I used a priority queue to store movies that had the given prefixes, which has a maximum space complexity of the maximum number of matching movies: O(k)
            Current total worst case space complexity: O(m) + O(k) = O(m+k)
    Thus, the worst case space complexity of the algorithm is O(m+k).

 */

/*  === PART 3C: TRADEOFFS BETWEEN SPACE AND TIME COMPLEXITY ===

    I designed my algorithm to have both a low worst case space complexity and time complexity.
    However, I feel that I mainly managed to achieve a low space complexity, as my time complexity was still quite high.
    The high time complexity is due to the need for iterations over each movie for each prefix. Still, by using a priority queue to store the movies matching the prefixes, I was able to save some time as that runs in O(log(k)).
    On the other hand, my space complexity is quite low, as the only data structures I use are a vector (O(m)) and a priority queue (O(k)), which are smaller than O(n) in this scenario.
    
    When these complexities are compared, it is obvious the space complexity is far more optimized than the time complexity. If my iterations were perhaps replaced by a binary search, the time complexity could be improved.

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
