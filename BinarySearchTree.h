// Yi Zong Kuang
// Binary Search Tree class.
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// Comparable* find( x )  --> I(Yi Zong Kuang) added this function to aid me in my project. Return object, null if not in the tree.
// unsigned int numOfNodes() --> I(Yi Zong Kuang) added this function to aid me in my project. Return number of node in the tree.
// calAvgDepth()          --> Calculate the average Depth by recursively going to each node and keeping a counter.
// Comparable* find( X , int )--> Find the item, keep track of the number of recursion calls. Will return null if none found.
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    // Added by Yi Zong Kuang, to aid in project. Keeps track of number of Recursion calls.
    void remove( const Comparable & x , int & recur_tracker , bool & found_flag)
    {
        remove( x, root, recur_tracker, found_flag );
    }

    // Find an element and return it from the tree.
    const Comparable* find( const Comparable & x ) const {
      return find( x , root );
    }
    
    // Find an elementand return it from the tree, also keep track of number of recursion.
    const Comparable* find( const Comparable & x, int & recur_tracker ) const {
      return find( x , root , recur_tracker );
    }
 
    // Counts the # of nodes in the tree.  
    unsigned int numOfNodes() {
      if( isEmpty( ) )
          return 0;
      else
          return numOfNodes( root );

    }

    // Recursively going through each node and keep track of the depth of each node in each level of recursion, then calculate the average.
    float calAvgDepth() {
      static int depth_calculate = 0;
      float allDepths = 0;
      float num_of_nodes = 0;
      calAvgDepthHelper(root, depth_calculate, allDepths, num_of_nodes);
      depth_calculate = 0;
      //calculates avg.
//std::cout << numOfNodes() << " ==? " << num_of_nodes << std::endl;
      float avg_depth = allDepths/num_of_nodes;
//std::cout << "all depths: " << allDepths << std::endl;
      return avg_depth;
    }
    // End of addon by Yi Zong Kuang.  


  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    
    };

    BinaryNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element ) 
            insert( x, t->left );
        else if( t->element < x ) 
            insert( x, t->right );
        else
            t->element.Merge(x);  // Duplicate; do nothing. But for the purpose of this program, we gonna merg the datas if recognition ID are the same.
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element ) 
            insert( std::move( x ), t->left );
        else if( t->element < x ) 
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x);  // Duplicate; do nothing. But for the purpose of this program, we gonna merg the datas if recognition ID are the same.
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
  
    // Personal addon by Yi Zong Kuang, to aid his project.
    // Helper to remove function.
    void remove( const Comparable & x, BinaryNode * & t, int & recur_tracker, bool & found_flag )
    {
        ++recur_tracker;
        if( t == nullptr ) {
            found_flag = false;
            return;   // Item not found; do nothing
        }

        if( x < t->element )
            remove( x, t->left, recur_tracker, found_flag );
        else if( t->element < x )
            remove( x, t->right, recur_tracker, found_flag );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right, recur_tracker, found_flag );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            found_flag = true;
        }
    }

    // Helper to find function.
    const Comparable* find( const Comparable & x, BinaryNode *t ) const {
      if( t == nullptr )
          return nullptr;
      else if( x < t->element )
          return find( x, t->left );
      else if( t->element < x )
          return find( x, t->right );
      else
          return &t->element;    // Match
    } 
  
    // Helper to find function.
    const Comparable* find( const Comparable & x, BinaryNode *t , int & recur_tracker ) const {
      ++recur_tracker;
      if( t == nullptr )
          return nullptr;
      else if( x < t->element )
          return find( x, t->left , recur_tracker );
      else if( t->element < x )
          return find( x, t->right , recur_tracker );
      else
          return &t->element;    // Match
    }
    
    // Helper to numOfNodes function.
    unsigned int numOfNodes( BinaryNode *t ) {
      if( t != nullptr ) 
        return 1 + numOfNodes( t->left ) + numOfNodes( t->right );      
      else
        return 0;
    } 

    // Helper to number of nodes function.
    void calAvgDepthHelper(BinaryNode *t, int & depth_calculate, float & allDepths, float & num_of_nodes) {
      if( t != nullptr )
        {
            ++num_of_nodes;
            ++depth_calculate;
            calAvgDepthHelper( t->left, depth_calculate, allDepths, num_of_nodes );
            --depth_calculate;
            allDepths += depth_calculate;
            ++depth_calculate;
            calAvgDepthHelper( t->right, depth_calculate, allDepths, num_of_nodes );
            --depth_calculate;
        }
    }
    // End of personal addon.
};

#endif
