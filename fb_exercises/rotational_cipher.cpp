#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here


string rotationalCipher(string input, int rotationFactor) {
    // Write your code here
    for(int i=0; i<input.size(); ++i){
        if(isalpha(input[i]) && isupper(input[i])){
            int cur = input[i] -'A';
            cur += rotationFactor;
            cur %= 26;
            input[i] = cur + 'A';
        }else if(isalpha(input[i])){ 
            int cur = input[i] -'a';
            cur += rotationFactor;
            cur %= 26;
            input[i] = cur + 'a';
        }else if(isdigit(input[i])){
            int cur = input[i] -'0';
            cur += rotationFactor;
            cur %= 10;
            input[i] = cur + '0';
        }else{
            // do nothing
        }
    }
    return input;
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
    cout << rightTick << "Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << "Test #" << test_case_number << ": Expected ";
    printString(expected); 
    cout << " Your output: ";
    printString(output);
    cout << endl; 
  }
  test_case_number++;
}

int main() {

  string input_1 = "All-convoYs-9-be:Alert1.";
  int rotationFactor_1 = 4;
  string expected_1 = "Epp-gsrzsCw-3-fi:Epivx5.";
  string output_1 = rotationalCipher(input_1, rotationFactor_1);
  check(expected_1, output_1);

  string input_2 = "abcdZXYzxy-999.@";
  int rotationFactor_2 = 200;
  string expected_2 = "stuvRPQrpq-999.@";
  string output_2 = rotationalCipher(input_2, rotationFactor_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
