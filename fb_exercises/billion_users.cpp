#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;
float EPS = 0.0000001;

// Add any helper functions you may need here

bool greaterThanBillion(vector<float> &nums){
    float counter = 0;
    for(int i=0; i<nums.size(); ++i){
        counter += nums[i];
    }
    return counter > (float)1'000'000'000 - EPS;
}

int getBillionUsersDay(vector <float> growthRates) {
  // Write your code here
  // 10^9
  //
  // 1.1   0   0     1.1
  //   0 1.2   0     1.2
  //   0   0  1.3    1.3
  //
  vector<float> users = growthRates;
  int days = 1;
  while(!greaterThanBillion(users)){
      for(int i=0; i<users.size(); ++i){
        users[i] *= growthRates[i];
      }
      days++;
  }
  return days;
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

  vector <float> test_1{1.1, 1.2, 1.3};
  int expected_1 = 79;
  int output_1 = getBillionUsersDay(test_1);
  check(expected_1, output_1);

  vector <float> test_2{1.01, 1.02};
  int expected_2 = 1047;
  int output_2 = getBillionUsersDay(test_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
