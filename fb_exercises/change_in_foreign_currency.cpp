#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here
int memo[1000001];

int dp(int target, vector<int>& denominations){
    int &ans = memo[target];
    if(ans != -1) return ans;
    if(target == 0) return ans = 1;
    for(int i=0; i<denominations.size(); ++i){
        if(denominations[i]<=target && dp(target - denominations[i], denominations) == 1){
            return ans = 1;
        }
    }
    return ans = 0;
}


bool canGetExactChange(int targetMoney, vector<int>& denominations){
  // Write your code here
  memset(memo, -1, sizeof memo);
  int result = dp(targetMoney, denominations);
  return result == 1;
}

// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom.

void printString(string& str) {
  cout << "[\"" << str << "\"]";
}

int test_case_number = 1;

void check(bool expected, bool output) {
  bool result = (expected == output);
  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << "Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << "Test #" << test_case_number << ": Expected ";
    printf("%s", expected ? "true" : "false");
    cout << " Your output: ";
    printf("%s", output ? "true" : "false");
    cout << endl; 
  }
  test_case_number++;
}

int main(){
  // Testcase 1
  int target_1 = 94;
  vector<int> arr_1{5, 10, 25, 100, 200};
  bool expected_1 = false;
  bool output_1 = canGetExactChange(target_1, arr_1); 
  check(expected_1, output_1); 
  
  // Testcase 2
  int target_2 = 75;
  vector<int> arr_2{4, 17, 29};
  bool expected_2 = true;
  bool output_2 = canGetExactChange(target_2, arr_2); 
  check(expected_2, output_2); 

  // Add your own test cases here
  
  return 0; 
}
