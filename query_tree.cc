// Yi Zong Kuang
// Main file for Part2(a) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
  ifstream input;
  input.open(db_filename.c_str());
  if (input.fail()){
    cout<<"File failed to open..."<<endl;
    return;
  }

  string db_line;
  // Read the file line-by-line:
  while(std::getline(input, db_line)) {
    std::string::iterator itr = db_line.begin();
    // If input string is empty, skip to next line of input.
    if (itr == db_line.end() or (db_line.find(' ') != string::npos)) { //string::npos means it contains a space in the line, which is not correct format. 
      continue;
    }
    
    // This first for loop will get the enzy to be stored into the vector.
    string enzy = "";
    for (;*itr != '/' ; ++itr) {
      enzy += *itr;
    }

    // This second for loop will go through the rest of the string assuming it's all recognition IDs with each being a new object.
    string recog = "";
    for (; (itr + 1) != db_line.end(); ++itr) {
      if (*itr == '/') {  
        if (recog == "") // To prevent the first run of this loop, where *itr is at the first instance of '/' and recog being empty, so that an empty SequenceMap is not created.
          continue;
        SequenceMap a_seq_map(recog, enzy);
        a_tree.insert(a_seq_map);
        recog = "";
      } else {
        recog += *itr;
      }
    }
  }
  
  // Accepting user input.
  string input_strings[3];
  cout << "Enter your Recognition Sequence...:" << endl;
  for(unsigned int i = 0; i < 3; ++i) {
    getline(std::cin, input_strings[i]);
  }

  // Searching through the trees.
  /*
  * Creates a temp sequence map to reuse codes for searching through the tree of SequenceMap type.
  */
  for(unsigned int i = 0; i< 3; ++i) {
    SequenceMap temp(input_strings[i], "");  
    const SequenceMap* seq_ptr = a_tree.find(temp);
    if (seq_ptr == nullptr)
      cout << "Not Found" << endl; 
    else 
      cout << *seq_ptr << endl;
  }
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
