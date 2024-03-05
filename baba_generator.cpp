// thanks to mathis for most of the generator code
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> 
#include <bits/stdc++.h>
using namespace std;

const string PROBLEM_NAME = "baba";

const int MAX_LEN = 1e5;
const int RANDOM_CASES = 6;
const int SEMI_RANDOM_CASES = 10;
const pair<int, int> LEN_BOUNDS = {3, 100'000};
// const pair<int, int> COLOR_BOUNDS = {1, 100};
typedef string Case;

long long solve(Case &str)
{
  typedef long long ll;
  map<int, ll> prefix;
  prefix[0] = 1;
  ll ans = 0;

  if(str.size() > LEN_BOUNDS.second || str.size() < 1) cerr << "generated string length out of bounds (len=" << str.size() << ")" << endl;

  int cur = 0;
  for(int i = 0; i < str.size(); i++)
  {
    cur += (str[i] == 'A' ? 1 : -1);
    if(str[i] != 'A' && str[i] != 'B') cerr << "characters in string not A or B" << endl;

    ans += prefix[cur];
    prefix[cur]++;
  }

  if(cur != 0) return -1;
  return ans;  
}

int main() {

  // generate custom cases
  vector<Case> samples = {
      "BABA",
      "BABBB",
      "AAABBB",
      "A",
      "B",
      "AB",
      "BA",
      "ABAB",
      "AAAAAAAAABBBBBBBBB",
      "BBBBBBBBBAAAAAAAAA"
      };

  // max cases: all B's and all B's
  string allBs = "";
  string allAs = "";
  for(int i = 0; i < MAX_LEN; i++)
  {
    allAs += "A";
    allBs += "B";
  }

  // max case all AB's
  // max case all BA's
  string AB = "";
  string BA = "";
  for(int i = 0; i < MAX_LEN; i += 2)
  {
    AB += "AB";
    BA += "BA";
  }

  samples.push_back(allAs);
  samples.push_back(allBs);
  samples.push_back(AB);
  samples.push_back(BA);


  // random cases x15
  srand(420420420);
  vector<Case> random;
  for (size_t tc = 0; tc < RANDOM_CASES; ++tc) {
    int n = (rand() % (LEN_BOUNDS.second - LEN_BOUNDS.first + 1)) + LEN_BOUNDS.first;

    Case new_case = "";
    for (size_t index = 0; index < n; ++index) {
      new_case += (char) ('A' + (rand() % 2));
    }

    random.push_back(new_case);
  }

  for (size_t tc = 0; tc < SEMI_RANDOM_CASES; ++tc) {
    int n = (rand() % (LEN_BOUNDS.second - LEN_BOUNDS.first + 1)) + LEN_BOUNDS.first;
    if(n % 2 == 1) n --;

    Case new_case = "";
    int offset = 0;
    for (size_t index = 0; index < n; ++index) {
      if(n - index >= abs(offset)) new_case += (offset > 0 ? 'B' : 'A');
      else new_case += (char) ('A' + (rand() % 2));
      offset += new_case.back() == 'A' ? 1 : -1;
    }

    random.push_back(new_case);
  }

  vector<Case> all;
  all.insert(end(all), begin(samples), end(samples));
//   all.insert(end(all), begin(custom), end(custom));
  all.insert(end(all), begin(random), end(random));

  for (size_t tc = 0; tc < all.size(); tc++) {
    Case current_case = all[tc];

    stringstream file_prefix;
    file_prefix << PROBLEM_NAME << setw(3) << setfill('0') << (tc + 1);

    ofstream in(file_prefix.str() + ".in");
    ofstream out(file_prefix.str() + ".out");

    // for (int color : current_case)
    in << current_case;
    in << "\n";

    long long ans = solve(current_case);
    if(ans == -1) out << "BABA IS NOT YOU!\n";
    else out << ans << "\n";

    // solve
    // int ans = 0;
    // for (size_t i = 0; i < current_case.size(); i++)
    //   ans = ( current_case[0] != current_case[2] ? 1 : 0) + (current_case[1] != current_case[3] ? 1 : 0);

    // out << ans << "\n";

    in.close();
    out.close();
  }

  return 0;
}
