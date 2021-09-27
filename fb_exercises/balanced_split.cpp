#include<bits/stdc++.h>
typedef long long ll;
// Add any extra import statements you may need here

using namespace std; 

// Add any helper functions you may need here


bool balancedSplitExists(vector<int>& arr){
    sort(arr.rbegin(), arr.rend()); // reversed sort
    ll sumLeft = 0, sumRight = 0;
    for(int i=0; i<arr.size(); ++i) sumRight += arr[i];
    for(int i=0; i<arr.size(); ++i){
        sumLeft += arr[i];
        sumRight -= arr[i];
        if(i<arr.size()-1 && arr[i+1] == arr[i]){ // 3 3 || 6
            continue;
        }else{
            if(sumLeft == sumRight){
                return true;
            }
        }
    }
    return false;
  
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
  vector<int> arr_1{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10};
  bool expected_1 = true;
  bool output_1 = balancedSplitExists(arr_1); 
  check(expected_1, output_1); 
  
  // Testcase 2
  vector<int> arr_2{3, 6, 3, 4, 4};
  bool expected_2 = false;
  bool output_2 = balancedSplitExists(arr_2); 
  check(expected_2, output_2); 

  // Add your own test cases here
  
  return 0; 
}
