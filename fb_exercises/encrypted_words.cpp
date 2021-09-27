#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here

void recurse(string &s, string &r, int left, int right){
    if(left>= right){
        return;
    }
    int mid = (right + left - 1)/2; // abc: left 0, right 3 -> 1 // abcd: left 0, right 4 -> 2
    string curElement = string(1, s[mid]);
    r.append(curElement);
    recurse(s, r, left, mid);
    recurse(s, r, mid+1, right);
}

string findEncryptedWord(string s) {
    string r;
    r.reserve(s.size());
    int left =0, right = s.size();
    recurse(s, r, left, right);
    return r;
}


// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom.

void printString(string& str) {
  cout << "[\"" << str << "\"]";
}

int test_case_number = 1;

void check(string& expected, string& output) {
  bool result = (expected == output);
  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << " Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << " Test #" << test_case_number << ": Expected ";
    printString(expected); 
    cout << " Your output: ";
    printString(output);
    cout << endl; 
  }
  test_case_number++;
}

int main() {

  string s_1 = "abc";
  string expected_1 = "bac";
  string output_1 = findEncryptedWord(s_1);
  check(expected_1, output_1);

  string s_2 = "abcd";
  string expected_2 = "bacd";
  string output_2 = findEncryptedWord(s_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
