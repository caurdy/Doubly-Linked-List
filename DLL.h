#pragma once
#include <iostream>
using std::cout; using std::endl;
using std::ostream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using std::ostringstream;

struct Node {
  string key{};
  int value{};
  Node *next = nullptr;
  Node *prev = nullptr;
  Node() = default;
  Node(string, int, Node * = nullptr, Node * = nullptr);
  bool operator==(const Node &) const;
  friend ostream &operator<<(ostream &out, const Node &n) {
    out << n.key << ":" << n.value;
    return out;
  }
};

Node::Node(string key_, int value_, Node *prev_, Node *next_) {
  key = key_;
  value = value_;
  prev = prev_;
  next = next_;
}

bool Node::operator==(const Node &n) const {
  if ((key == n.key) && (value == n.value)) {
    return true;
  } else {
    return false;
  }
}

// DO NOT MODIFY
//
// DLL
//
class DLL {
private:
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  size_t sz_ = 0;

public:
  DLL() = default;
  DLL(vector<Node>);
  DLL(const DLL &);
  DLL &operator=(DLL list);
  ~DLL();
  Node *get_head();
  Node *get_tail();
  size_t get_size();
  Node add_back(string, int);
  Node add_front(string, int);
  Node add_after(string, string, int);
  Node search(string);
  Node remove_front();
  Node remove_back();
  Node remove_key(string);
  int update_value(string, int);
  friend ostream &operator<<(ostream &out, const DLL &list) {
    auto itr = list.head_;
    ostringstream oss;
    for (; itr != nullptr; itr = itr->next) {
      oss << itr->key << ":" << itr->value << ", ";
    }
    string ans = oss.str();
    ans = ans.substr(0, ans.size() - 2);
    out << ans;
    return out;
  }
};

Node *DLL::get_head() { return head_; }
Node *DLL::get_tail() { return tail_; }
size_t DLL::get_size() { return sz_; }

DLL::~DLL() {
  while (head_)
    delete std::exchange(head_, head_->next);
}

DLL & DLL::operator =(DLL list) {
  using std::swap;
  swap(head_,list.head_);
  swap(tail_,list.tail_);
  swap(sz_,list.sz_);
  return *this;
}

DLL::DLL(const DLL &list) {
  for (Node *p = list.head_; p; p = p->next)
    add_back(p->key, p->value);
}

DLL::DLL(vector<Node> vec) {
  for (const auto &node : vec)
    add_back(node.key, node.value);
}

//Adds new node of (str,num) to back of list, returns this node
Node DLL::add_back(string str, int num) {
  Node * newnode = new Node(str, num, tail_, nullptr);
  if(head_ == nullptr) {
    head_ = newnode;
    tail_ = newnode;
  } else {
    (*tail_).next = newnode;
    tail_ = newnode;
  }
  sz_ += 1;
  return *newnode;
}
//Adds new node of (str,num) to fromt of list, returns this node
Node DLL::add_front(string str, int num) {
  Node * newnode = new Node(str, num, nullptr, head_);
  if(head_ == nullptr) {
    head_ = newnode;
    tail_ = newnode;
  } else {
    (*head_).prev = newnode;
    head_ = newnode;
  }
  sz_ += 1;
  return *newnode;
}
//Adds new node of (str,num) after node of key add_key, returns said Node
//does nothing if key doesn't exist, which returns empty Node
Node DLL::add_after(string add_key, string str, int num) {
  Node * newnode = new Node(str,num);
  Node before = this->search(add_key);
  Node * after_pnt = this->search(add_key).next;
  //cout << before << endl;
  if ( before.key == "") {
    return Node("",0);
  }
  if ( before == *tail_ ) {
    this->add_back(str,num);
    return *newnode;
  }
  else {
    Node * before_pnt = before.next->prev;
    newnode->prev = after_pnt->prev;
    newnode->next = before_pnt->next;
    before_pnt->next = newnode;
    after_pnt->prev = newnode;
    sz_ += 1;
    return *newnode;
  }
}
//removes last node in list, returns said node
Node DLL::remove_back() {
  //check if more than one node in list
  if(head_ != nullptr && head_ != tail_) {
    Node * newlast = tail_->prev;
    Node * oldlast = tail_;
    tail_ = newlast;
    newlast->next = nullptr;
    sz_ -= 1;
    return *oldlast;
  //check if more than one node in list
  } else if (head_ == tail_ && head_ != nullptr) {
    Node * rnode = head_;
    tail_ = nullptr;
    head_ = nullptr;
    sz_ -= 1;
    return *rnode;
  } else {
    return Node("",0);
  }
}
//removes first node in list, returns said node
Node DLL::remove_front() {
  //check if more than one node in list
    if(head_ != nullptr && head_ != tail_) {
    Node * newhead = head_->next;
    Node * oldhead = head_;
    head_ = newhead;
    newhead->prev = nullptr;
    sz_ -= 1;
    return *oldhead;
  //check if more than one node in list
  } else if (head_ == tail_ && head_ != nullptr) {
    Node * rnode = head_;
    tail_ = head_ = nullptr;
    sz_ -= 1;
    return *rnode;
  } else {
    return Node("",0);
  }
}
//removes node of key to_remove
//returns -1 if not found
Node DLL::remove_key(string to_remove) {
  Node * it = head_;
  while(it != nullptr) {
    if(it->key == to_remove) {
      //check if last node
      if(it->next == nullptr) {
        Node rnode = this->remove_back();
        return rnode;
      //check if first node
      } else if (it->prev == nullptr) {
        Node rnode = this->remove_front();
        return rnode;
      } else {
        Node pop = this->search(to_remove);
        Node * prev = pop.prev;
        Node * next = pop.next;
        prev->next = next;
        next->prev = prev;
        sz_ -= 1;
        return pop;
      }
    }
    it = it->next;
  }
  return Node("",0);
}
//returns node of find_key
//or blank node if not found
Node DLL::search(string find_key) {
  Node * it = head_;
  Node * rnode = nullptr;
  while(it != nullptr) {
    if(it->key == find_key) {
      rnode = it;
      break;
    }
    it = it->next;
  }
  if(rnode == nullptr) {
    return Node("",0);
  } else {
    return *rnode;
  }
}
//updates value of node find_key
//returns -1 if not found
int DLL::update_value(string find_key, int new_value) {
  Node * it = head_;
  while(it != nullptr) {
    if(it->key == find_key) {
      it->value = new_value;
      return new_value;
    }
    it = it->next;
  }
  return -1;
}
