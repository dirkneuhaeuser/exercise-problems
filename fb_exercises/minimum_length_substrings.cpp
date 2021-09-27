#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here
bool isOk(vector<int> &freqS, vector<int> &freqT){
    for(int i=0; i<26; ++i){
        if(freqS[i] < freqT[i]) return false;
    }
    return true;
}

int minLengthSubstring(string s, string t) {
    vector<int> freqS(26, 0), freqT(26, 0);
    for(int i=0; i<t.size(); ++i){
        int cur = t[i]-'a';
        freqT[cur]++;
    }
    int lp =0, hp=0;
    int ret = INT_MAX;
    while(hp < s.size()){
        while(hp<s.size() && !isOk(freqS, freqT)){
            int cur = s[hp] - 'a';
            freqS[cur]++;
            hp++;
        }
        while(isOk(freqS, freqT)){
            ret = min(ret, hp - lp);
            int cur = s[lp] - 'a';
            freqS[cur]--;
        }
    }
    if(ret == INT_MAX) return -1;
    return ret;
  
}

// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom.

void printInteger(int n) {
  cout << "[" << n << "]";
}

int test_case_number = 1;

void check(int expected, int output) {
  bool result = (expected == output);
  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << "Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << "Test #" << test_case_number << ": Expected ";
    printInteger(expected); 
    cout << " Your output: ";
    printInteger(output);
    cout << endl; 
  }
  test_case_number++;
}

int main() {

  string s_1 = "dcbefebce";
  string t_1 = "fd";
  int expected_1 = 5;
  int output_1 = minLengthSubstring(s_1, t_1);
  check(expected_1, output_1);

  string s_2 = "bfbeadbcbcbfeaaeefcddcccbbbfaaafdbebedddf";
  string t_2 = "cbccfafebccdccebdd";
  int expected_2 = -1;
  int output_2 = minLengthSubstring(s_2, t_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
