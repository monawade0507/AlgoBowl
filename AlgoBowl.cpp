#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <bits/stdc++.h>
#include <set>

using namespace std;

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
  set<string> covers;
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
  //cout << "Amount of SubSets: " << _set.size() << endl;

  /*
  the set cover problem goal is to identify the smallest
  sub-collection of S whose union equals the universe
  */
  string _cover = "";
  for(int i = 0; i < numSubSets; i++) {
    string num = to_string(i);
    _cover += num;
    covers.insert(_cover);
  }
  _cover = "";
  for(int i = numSubSets - 1; i > 0; i--) {
    string num = to_string(i);
    _cover += num;
    covers.insert(_cover);
  }

  /* check to see the amount of covers
  cout << "Amount of Covers: " << covers.size() << endl;
  for (auto elem : covers) {
    cout << "Found Cover: " << elem << endl;
  }
  */

  // Determine the total weight of each cover
  for (auto elem : covers) {
    string tempCover = elem;
    int total = 0;
    vector<int> elemList;
    for (int i = 0; i < tempCover.length(); i++) {
      // find total weight of cover
      string t = "";
      t += tempCover.at(i);
      stringstream toInt(t);
      int subSetNum = 0;
      toInt >> subSetNum;
      total += _weight.at(subSetNum);
      // obtain the stored SubSet
      vector<int> tempSubSet = _set.at(_weight.at(subSetNum));
      // store each elem in the tempSubSet to uniqueElem to create a true cover
      for (int j = 0; j < tempSubSet.size(); j++) {
          elemList.push_back(tempSubSet.at(j));
      }
    }

    /* testing
    cout << "Testing the following cover: " << endl;
    cout << tempCover << endl;
    cout << total << endl;
    cout << "Amount of elements in cover: " << elemList.size() << endl;
    cout << " --- " << endl;
*/
      // determine the best cover with the lowest weight
      // update info when if statments are true
      /*
        minWeight -> lowest weight found
        bestCover -> best cover found
        bestCoverSize -> lenght of the best cover found
      */
      //cout << endl;
      //cout << endl;
    if (elemList.size() <= numElements) {
      if (elemList.size() >= bestCoverSize) {
        //minWeight = total;
        bestCover = tempCover;
        bestCoverSize = elemList.size();

        //cout << "Almost winner: " << endl;
        //cout << "Weight total: " << minWeight << endl;
        //cout << "Cover string: " << bestCover << endl;
        //cout << "Amount of elements: " << bestCoverSize << endl;

        almostWin.push_back(tempCover);
      }
      else {

      }
    }
  }

  // finalist
  //cout << "Amount of finalist: " << almostWin.size() << endl;
  //cout << endl;
  for (int i = 0; i < almostWin.size(); i++) {
    string tempCover = almostWin.at(i);
    int total = 0;
    vector<int> elemList;
    for (int i = 0; i < tempCover.length(); i++) {
        // find total weight of cover
        string t = "";
        t += tempCover.at(i);
        stringstream toInt(t);
        int subSetNum = 0;
        toInt >> subSetNum;
        total += _weight.at(subSetNum);

        // obtain the stored SubSet
        vector<int> tempSubSet = _set.at(_weight.at(subSetNum));
        // store each elem in the tempSubSet to uniqueElem to create a true cover
        for (int j = 0; j < tempSubSet.size(); j++) {
            elemList.push_back(tempSubSet.at(j));
        }
        if (elemList.size() == bestCoverSize) {
          if (total < minWeight) {
            minWeight = total;
            bestCover = tempCover;
          }
        }
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
  for (int i = 0; i < bestCover.length(); i++) {
    string t = "";
    t += bestCover.at(i);
    stringstream toInt(t);
    int subSetNum = 0;
    toInt >> subSetNum;
    cout << subSetNum + 1 << " ";
    myfile << subSetNum + 1 << " ";
  }
  cout << endl;
  cout << "Amount of elements: " << bestCoverSize << endl;
  myfile << endl;
  myfile.close();
  return 0;
}
