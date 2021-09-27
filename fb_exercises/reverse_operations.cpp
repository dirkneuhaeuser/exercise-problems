#include <bits/stdc++.h>
// Add any extra import statements you may need here

using namespace std;

struct Node {
  int data;
  Node *next;
  Node(int x) : data(x), next(NULL) {}
};

// Add any helper functions you may need here
void print(Node* node){
    while(node != nullptr){
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

pair<Node*, Node*> reverseSubpart(Node* head){
    Node* tail = nullptr;
    Node* last = nullptr;
    while(head != nullptr){
        Node* temp = head->next;
        head->next = tail;
        tail = head;
        head = temp;
        if(last == nullptr) last = tail;
    }
    return {tail, last};
}


Node* reverse(Node *head) {
    Node* root = head;
    Node* dummy = new Node(-1);
    dummy->next = head;
    head = dummy;
    int step = 1;
    while(head->next != nullptr){
        if(head->next->data&1){ // next is odd
            head = head->next;
            continue;
        }
        Node* curRoot = head->next; //even
        Node* cur = curRoot;
        while(cur->next != nullptr && ((cur->next->data)&1) == 0){ // even
            cur = cur->next;
        }
        Node* temp = cur->next;
        cur->next = nullptr;
        auto [tail, last] = reverseSubpart(curRoot);
        head->next = tail;
        head = last;
        last->next = temp;
    }
    return dummy->next;

}

// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom.
void printLinkedList(Node *head) {
  cout << "[";
  while (head != NULL) {
    cout << head -> data;
    head = head -> next;
    if (head != NULL)
      cout << " ";
  }
  cout << "]";
}

int test_case_number = 1;

void check(Node *expectedHead, Node *outputHead) {
  bool result = true;
  Node *tempExpectedHead = expectedHead;
  Node *tempOutputHead = outputHead;
  while (expectedHead != NULL && outputHead != NULL) {
    result &= (expectedHead -> data == outputHead -> data);
    expectedHead = expectedHead -> next;
    outputHead = outputHead -> next;
  }
  if (!(expectedHead == NULL && outputHead == NULL)) result = false;

  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << "Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << "Test #" << test_case_number << ": Expected ";
    printLinkedList(tempExpectedHead); 
    cout << " Your output: ";
    printLinkedList(tempOutputHead);
    cout << endl; 
  }
  test_case_number++;
}

Node* createLinkedList(vector<int> arr) {
  Node *head = NULL;
  Node *tempHead = head;
  for (auto &v : arr) {
    if (head == NULL) head = new Node(v), tempHead = head;
    else {
      head -> next = new Node(v);
      head = head -> next;
    }
  }
  return tempHead;
}

int main() {

  Node *head_1 = createLinkedList({1, 2, 8, 9, 12, 16});
  Node *expected_1 = createLinkedList({1, 8, 2, 9, 16, 12});
  Node *output_1 = reverse(head_1);
  check(expected_1, output_1);

  Node *head_2 = createLinkedList({2, 18, 24, 3, 5, 7, 9, 6, 12});
  Node *expected_2 = createLinkedList({24, 18, 2, 3, 5, 7, 9, 12, 6});
  Node *output_2 = reverse(head_2);
  check(expected_2, output_2);

  // Add your own test cases here
  
}
