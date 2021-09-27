#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

class Node {
public:
  int val;
  vector<Node*> children;
  
  Node() {
    val = 0;
    children = vector<Node*>();
  }
  
  Node(int _val) {
    val = _val;
    children = vector<Node*>();
  }
  
  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

struct Query {
  int u; 
  char c; 
};

// Add any helper functions you may need here

vector<int> postOrder(Node* node, vector<vector<int>> &frequencies, string &s){
    vector<int> freqThis(26, 0);
    for(Node* kid: node->children){
        if(kid != nullptr){
            vector<int> freqKid = postOrder(kid, frequencies, s);
            for(int i=0; i<26; ++i){
                freqThis[i] += freqKid[i];
            }
        }
    }
    int charThis = s[node->val -1] - 'a';
    freqThis[charThis]++;
    frequencies[node->val -1] = freqThis;
    return freqThis;
}


vector<int> countOfNodes(Node* root, vector<Query> queries, string s) {
    vector<vector<int>> frequencies(1'000'001, vector<int>());
    postOrder(root, frequencies, s);
    vector<int> ret;
    for(auto [u, c]: queries){
        int charVal = c - 'a';
        ret.push_back(frequencies[u-1][charVal]);
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

  // Testcase 1
  int n_1 = 3, q_1 = 1;
  string s_1 = "aba";
  Node *root_1 = new Node(1);
  root_1->children.push_back(new Node(2)); 
  root_1->children.push_back(new Node(3));  
  vector<Query> queries_1{{1,'a'}};
  vector<int> output_1 = countOfNodes(root_1, queries_1, s_1); 
  vector<int> expected_1 = {2};
  check(expected_1, output_1); 
  
  // Testcase 2
  int n_2 = 7, q_2 = 3;
  string s_2 = "abaacab";
  Node *root_2 = new Node(1); 
  root_2->children.push_back(new Node(2)); 
  root_2->children.push_back(new Node(3)); 
  root_2->children.push_back(new Node(7)); 
  root_2->children[0]->children.push_back(new Node(4)); 
  root_2->children[0]->children.push_back(new Node(5)); 
  root_2->children[1]->children.push_back(new Node(6));  
  vector<Query> queries_2{{1,'a'}, {2, 'b'}, {3, 'a'}};
  vector<int> output_2 = countOfNodes(root_2, queries_2, s_2); 
  vector<int> expected_2 = {4, 1, 2};
  check(expected_2, output_2); 

  // Add your own test cases here
  
}
