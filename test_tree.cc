// Yi Zong Kuang
// Main file for Part2(b) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)  
  ifstream input;
  input.open(db_filename.c_str());
  if (input.fail()){
    cout<<"Data file failed to open..."<<endl;
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

    // Inserting rest of data into the tree.
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
  
  // 2 print number of nodes in tree.
  unsigned int tree_num_of_nodes = a_tree.numOfNodes();
  cout << "2 : " << tree_num_of_nodes << endl;

  // 3a and 3b Prints avg depth, and ratio of avg depth to log2 n.
  float avg_depth = a_tree.calAvgDepth();
  cout << "3a: " << avg_depth << endl;
  cout << "3b: " << avg_depth/( log2( tree_num_of_nodes ) ) << endl;

  // 4a and 4b Read in a file and searches the tree.
  // Prints the total number of successful quereies and avg number of recursion calls.
  ifstream input_seq;
  input_seq.open(seq_filename.c_str());
  if (input_seq.fail()){
    cout<<"(For Find) Sequence file failed to open..."<<endl;
    return;
  }
  string seq_line = "";
  int success_queries = 0;
  int recur_calls = 0;
  while ( std::getline( input_seq , seq_line ) ) {
    SequenceMap temp( seq_line , "" );
    SequenceMap const * temp_ptr = a_tree.find( temp , recur_calls );
    if ( temp_ptr != nullptr ) {
      ++success_queries;
    }
  }
  cout << "4a: " << success_queries << endl;
//cout<<"recurs call: "<<recur_calls<<endl;
  cout << "4b: " << float( recur_calls )/float( success_queries ) << endl;
  input_seq.close();

  // 5a and 5b Removes every other sequence.
  // Prints the total number of successful removes and avg number of recursion calls.
  int odd_counter = 0;
  int recur_tracker = 0;
  int success_removes = 0;
  input_seq.open( seq_filename.c_str() );
  if ( input_seq.fail() ) {
    cout<<"(For Remove) Sequence file failed to open..."<<endl;
    return;
  }

  while ( std::getline( input_seq , seq_line ) ) {
    if (odd_counter%2 ==0) {
      SequenceMap temp( seq_line, "" );
      bool found_flag = false;
      a_tree.remove( temp, recur_tracker, found_flag );
      if ( found_flag == true )
        ++success_removes;
    }
    ++odd_counter;
  }
  cout << "5a: " << success_removes << endl ;
  cout << "5b: " << float( recur_tracker )/float( success_removes ) << endl;

  // 6a, 6b and 6c, prints statistic.
  // Prints the # of nodes, average depth, and ratio of avg depth to log2 n.
  tree_num_of_nodes = a_tree.numOfNodes();
  cout << "6a: " << tree_num_of_nodes << endl;
  avg_depth = a_tree.calAvgDepth();
  cout << "6b: " << avg_depth << endl;
  cout << "6c: " << avg_depth/( log2( tree_num_of_nodes ) ) << endl;
  return;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
