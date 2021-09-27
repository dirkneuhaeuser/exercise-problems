#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here


vector <int> findMedian(vector <int> arr) {
    vector<int> ret(arr.size(), -1);
    priority_queue<int, vector<int>, ::greater<int>> minHeap;
    priority_queue<int> maxHeap;
    for(int i=0; i<arr.size(); ++i){
        maxHeap.push(arr[i]);
        if(maxHeap.size() && minHeap.size()){
            if(maxHeap.top() > minHeap.top()){
                int maxE = maxHeap.top(); maxHeap.pop();
                int minE = minHeap.top(); minHeap.pop();
                maxHeap.push(minE);
                minHeap.push(maxE);
            }
        }
        if(maxHeap.size() > minHeap.size() + 1){
            int maxE = maxHeap.top(); maxHeap.pop();
            minHeap.push(maxE);
        }
        if(maxHeap.size() > minHeap.size()){
            ret[i] = maxHeap.top();
        }else{
            ret[i] = (maxHeap.top() + minHeap.top())/2;
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
  vector <int> arr_1{5, 15, 1, 3};
  vector <int> expected_1{5, 10, 5, 4};
  vector <int> output_1 = findMedian(arr_1);
  check(expected_1, output_1);

  vector <int> arr_2{2, 4, 7, 1, 5, 3};
  vector <int> expected_2{2, 3, 4, 3, 4, 3};
  vector <int> output_2 = findMedian(arr_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
