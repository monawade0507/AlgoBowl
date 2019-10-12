#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <set>
#include <iostream>
#include <math.h>

using namespace std;

set<string> covers;
char firstRepeating(string &str);
bool printDuplicates(vector<string> words);
void findDec(int numSets);
void findInc(int numSets, int end);
//vector<int> findPowerSet(vector<int> const &S, vector<int> &set, int n);
vector<string> printPowerSet(vector<int> __set, int set_size);
void findPowerSet(vector<int>S, vector<int> set, int n);
template<typename Out>
void split(const std::string &s, char delim, Out result);
vector<string> split(const string &s, char delim);


int main(int argc, char const *argv[]) {
  /*
    Heuristic Program
  */

  // Open, read, and store file contents
  ifstream infile(argv[1]);
  string line;
  int numElements = -1;
  int numSubSets = -1;
  int lineNum = 0;
  int weight = 0;
  map<int, vector<int>> _set;
  map<int, int> _weight;
  vector<int> universal;

  int count = 0;
  int minWeight = 100000; //10,000
  string bestCover = "";
  int bestCoverSize = 0;
  vector<int> previous;
  vector<string> almostWin;

  while (getline(infile, line))
  {
    istringstream iss(line);
    vector<int> lineElement;

    for (int s; iss >> s; ) {
      lineElement.push_back(s);
    }
    if (lineElement.size() == 1 && lineNum == 0) {
      numElements = lineElement.at(0);
      // create universal set
      for (int i = 0; i < numElements; i++) {
        universal.push_back(i);
      }
    }
    else if (lineElement.size() == 1 && lineNum == 1) {
      numSubSets = lineElement.at(0);
    }
    else if (lineElement.size() == 1 && lineNum > 1) {
      weight = lineElement.at(0);
      // store the weight as key
      _set.insert({weight, previous});
      _weight.insert({count, weight});
      count++;
    }
    else {
      previous = lineElement;
    }

    // capture current line number
    lineNum ++;
  }

  // check to see if contents were store
  cout << "Amount of SubSets: " << _set.size() << endl;

// *************************************************************************************************************************************
// FINISHED ABOVE
// *************************************************************************************************************************************


  //the set cover problem goal is to identify the smallest
  //sub-collection of S whose union equals the universe


  vector<int> S;
  vector<int> setA;

  for(int i = 0; i < numSubSets; i++) {
    S.push_back(i);
  }

  int n = S.size();
  cout << "FindPowerSet with amount: " << S.size() << endl;

  vector<string> mona =  printPowerSet(S, n);

  cout << "Amount of power sets: " << mona.size() << endl;

  // *************************************************************************************************
  // FINISHED POWER SET
  // ****************************************************************************************************

  // Determine the total weight of each cover
  for (auto elem : mona) {
    string tempCover = elem;
    istringstream iss(tempCover);
    vector<string> v;

    for (string s; iss >> s; ) {
      v.push_back(s);
    }

    int total = 0;
    vector<int> elemList;
    for (int i = 0; i < v.size(); i++) {
      stringstream toInt(v.at(i));
      int subSetNum;
      toInt >> subSetNum;
      total += _weight.at(subSetNum);
      vector<int> tempSubSet = _set.at(_weight.at(subSetNum));
      // store each elem in the tempSubSet to uniqueElem to create a true cover
      for (int j = 0; j < tempSubSet.size(); j++) {
          elemList.push_back(tempSubSet.at(j));
      }
    }


    if (elemList.size() <= numElements) {
      if (elemList.size() >= bestCoverSize) {
        //minWeight = total;
        bestCover = tempCover;
        bestCoverSize = elemList.size();

        almostWin.push_back(tempCover);
      }
      else {

      }
    }
  }

  // finalist
  cout << "Amount of finalist: " << almostWin.size() << endl;
  //cout << endl;
  for (int i = 0; i < almostWin.size(); i++) {
    string tempCover = almostWin.at(i);
    //cout << "Final Cover: " << tempCover << endl;



    istringstream iss(tempCover);
    vector<string> v;

    for (string s; iss >> s; ) {
      v.push_back(s);
    }


    //
    int total = 0;
    vector<int> elemList;
    for (int i = 0; i < v.size(); i++) {
      stringstream toInt(v.at(i));
      int subSetNum;
      toInt >> subSetNum;
      total += _weight.at(subSetNum);

      // obtain the stored SubSet

        // obtain the stored SubSet
        vector<int> tempSubSet = _set.at(_weight.at(subSetNum));
        // store each elem in the tempSubSet to uniqueElem to create a true cover
        for (int j = 0; j < tempSubSet.size(); j++) {
            elemList.push_back(tempSubSet.at(j));
        }

        // check elemList for duplication
        vector<string> check;
        for (int k = 0; k < elemList.size(); k++){
          string t = "";
          t += elemList.at(k);
          check.push_back(t);
        }
        // TODO

        //if(printDuplicates(check)) {
          if (elemList.size() == bestCoverSize) {
            if (total <= minWeight) {
              cout << "Winning cost: " << total << ". With cover: " << tempCover << endl;
              minWeight = total;
              bestCover = tempCover;
            }
          }
        //}
     }
  }


  ofstream myfile;
  string file = argv[1];
  file += "_output.txt";
  myfile.open (file);


  // hopefully found the best cover
  cout << endl;
  cout << "Solution: " << endl;
  cout << "Weight total: " << minWeight << endl;
  myfile << minWeight << endl;
  cout << "Cover string: ";
  //seperate string between
  vector<string> x = split(bestCover, ' ');
  for (int i = 0; i < x.size(); i++) {
    if (x.at(i) != " ") {
      string t = "";
      t += x.at(i);
      stringstream toInt(t);
      int subSetNum = 0;
      toInt >> subSetNum;
      cout << subSetNum + 1 << " ";
      myfile << subSetNum + 1 << " ";
    }
  }
  cout << endl;
  cout << "Amount of elements: " << bestCoverSize << endl;
  myfile << endl;
  myfile.close();
  return 0;
}


char firstRepeating(string &str)
{
    // Creates an empty hashset
    unordered_set<char> h;

    // Traverse the input array from left to right
    for (int i=0; i<str.length(); i++)
    {
        char c = str[i];

        // If element is already in hash set, update x
        // and then break
        if (h.find(c) != h.end())
            return c;

        else // Else add element to hash set
            h.insert(c);
    }

    // If there was no repeated character
    return '\0';
}

bool printDuplicates(vector<string> words)
{
    vector<string>duplicate;

    // STL function to sort the array of string
    sort(words.begin(), words.end());

    for (int i = 1; i<words.size(); i++)
        if (words[i-1] == words[i])

            // STL function to push the duplicate
            // words in a new vector string
            duplicate.push_back(words[i]);

  if (duplicate.size() > 0) {
    return true;
  }
  else {
    return false;
  }

  return false;

}


// find covers, decrement
void findDec (int numSets) {
  if (numSets == 0) {
    return;
  }
  else {
    string _cover = "";
    for(int i = 0; i < numSets; i++) {
      string num = to_string(i);
      _cover += num + " ";
      //cout << _cover << endl;
      covers.insert(_cover);
    }
    findDec(numSets - 1);
  }
}

void findInc (int numSets, int end) {
  if (numSets == end) {
    return;
  }
  else {
    string _cover = "";
    for(int i = numSets - 1; i > 0; i--) {
      string num = to_string(i);
      _cover += num + " ";
      //cout << _cover << endl;
      covers.insert(_cover);
    }
    findInc(numSets + 1, end);
  }
}

template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}


vector<string> printPowerSet(vector<int> __set, int set_size)
{
    int n = 0;
    vector<string> static_vector;
    while ( n < 64 ) {

      /*set_size of power set of a set with set_size
      n is (2**n -1)*/
      unsigned int pow_set_size = pow(2, set_size);
      int counter, j;

      /*Run from counter 000..0 to 111..1*/
      for(counter = 0; counter < pow_set_size; counter++)
      {
        string TT = "";
        for(j = 0; j < set_size; j++)
        {
            /* Check if jth bit in the counter is set
                If set then print jth element from set */
            if(counter & (1 << j))
                TT += to_string(__set[j]) + " ";


        }
        cout << "Power Set Elem: " << TT << endl;
        static_vector.push_back(TT);
      }
      n++;
    }
    return static_vector;
}
