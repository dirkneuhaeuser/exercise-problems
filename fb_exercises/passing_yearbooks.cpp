#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here

int dfs(int curIdx, int startIdx, vector<int> &arr, vector<int> &visited){
    if(visited[curIdx] != -1) return 0;
    visited[curIdx] = startIdx;
    return 1 + dfs(arr[curIdx], startIdx, arr, visited);
}

vector<int> findSignatureCounts(vector <int> arr) {
    for(int i=0; i<arr.size(); ++i){
        arr[i]--;
    }
    vector<int> visited(arr.size(), -1), ret(arr.size(), 0);
    unordered_map<int, int> idxToRet;
    for(int i=0; i<arr.size(); ++i){
        if(visited[i] == -1){
            int ans = dfs(i, i, arr, visited);
            ret[i] = ans;
            idxToRet[i] = ans;
        }else{
            ret[i] = idxToRet[visited[i]];
        }
    }
    return ret;
}

// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom.
void printIntegerVector(vector <int> array) {
  int size = array.size();
  cout << "[";
  for (int i = 0; i < size; i++) {
    if (i != 0) {
      cout << ", ";
    }
   cout << array[i];
  }
  cout << "]";
}

int test_case_number = 1;

void check(vector <int>& expected, vector <int>& output) {
  int expected_size = expected.size(); 
  int output_size = output.size(); 
  bool result = true;
  if (expected_size != output_size) {
    result = false;
  }
  for (int i = 0; i < min(expected_size, output_size); i++) {
    result &= (output[i] == expected[i]);
  }
  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << "Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << "Test #" << test_case_number << ": Expected ";
    printIntegerVector(expected); 
    cout << " Your output: ";
    printIntegerVector(output);
    cout << endl; 
  }
  test_case_number++;
}

int main() {
  vector <int> arr_1{2, 1};
  vector <int> expected_1{2, 2};
  vector <int> output_1 = findSignatureCounts(arr_1);
  check(expected_1, output_1);

  vector <int> arr_2{1, 2};
  vector <int> expected_2{1, 1};
  vector <int> output_2 = findSignatureCounts(arr_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
