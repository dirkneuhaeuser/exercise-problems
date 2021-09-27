#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here


int matchingPairs(string s, string t) {
    vector<vector<bool>> canSwap(26, vector<bool>(26, false)) ;
    bool perfectSwap = false;
    int cnt = 0;
    bool noLose = false;
    vector<int> freq(26, 0);
    for(int i=0; i<s.size(); ++i){
        int idx = t[i] - 'a';
        freq[idx]++;
        if(freq[idx] > 1) noLose=true;
        if(s[i] == t[i]) cnt++;
        else{
            if(perfectSwap) continue;
            int have = s[i] - 'a';
            int should = t[i] - 'a';
            if (canSwap[should][have]){
                cnt += 2;
                perfectSwap = true;
            }
            canSwap[have][should] = true;
        }
    }
    if(perfectSwap) return cnt;
    unordered_set<int> sNotMatch, tNotMatch;
    for(int i=0; i<s.size(); ++i){
        if(s[i] != t[i]){
            sNotMatch.insert(s[i]);
            tNotMatch.insert(t[i]);
        }
    }
    for(int sElement: sNotMatch){
        if (tNotMatch.count(sElement)){
            return cnt+1;
        }
    }
    if(sNotMatch.size() >= 2 || noLose) return cnt;
    if(sNotMatch.size() >= 1) return cnt -1;
    return cnt - 2;
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
  string s_1 = "abcde";
  string t_1 = "adcbe";
  int expected_1 = 5;
  int output_1 = matchingPairs(s_1, t_1);
  check(expected_1, output_1);

  string s_2 = "abcd";
  string t_2 = "abcd";
  int expected_2 = 2;
  int output_2 = matchingPairs(s_2, t_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
