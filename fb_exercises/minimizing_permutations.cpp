#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here
int INF = 1 << 30;
map<vector<int>, int> memo;
set<vector<int>> seen;

bool isIncreasing(vector<int> arr){
    for(int i =1; i<arr.size(); ++i){
        if(arr[i] <= arr[i-1]) return false;
    }
    return true;
}

void print(vector<int> &arr){
    for(int i=0; i<arr.size(); ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int minOperations(const vector<int> &arr) {
    // 8! states 42K
    // one state takes O(624) -> 42K * 624 = O(42 Mil)
    auto it = memo.find(arr);
    if(it != memo.end()) return it->second;
    if(seen.count(arr)) return -1;
    //print(arr);
    seen.insert(arr);
    if(isIncreasing(arr)){
        return memo[arr] = 0;
    }
    int ans = INF;
    for(int i=0; i<arr.size(); ++i){
        for(int j=i+1; j<arr.size(); ++j){ // O(8 * 8 * 8) = 64 * 8 = 640 - 16 = 624 
            vector<int> newArr;
            for(int k = 0; k<i; ++k){
                newArr.push_back(arr[k]);
            }
            for(int k = j; k>=i; --k){
                newArr.push_back(arr[k]);
            }
            for(int k = j+1; k<arr.size(); ++k){
                newArr.push_back(arr[k]);
            }
            int cur = minOperations(newArr) + 1;
            if(cur != 0) ans = min(ans, cur);
        }

    }
    return memo[arr] = ans;
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

  int n_1 = 5;
  vector <int> arr_1{8, 1, 2, 7, 5, 4, 3, 6}; // 3 4 5 7 2 1 8 -> |1 2 7 5 4 3| 8 -> ok
  int expected_1 = 1;
  int output_1 = minOperations(arr_1);
  check(expected_1, output_1);

  int n_2 = 3;
  vector <int> arr_2{3, 1, 2};
  int expected_2 = 2;
  int output_2 = minOperations(arr_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
