// for unit testing
#include <cassert>
#include <sstream>

#include "splay_tree.cpp"

void testInsertAndInorder() {
    SplayTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(7);
    
    // Check inorder traversal: should be sorted
    ostringstream out;
    streambuf* oldCout = cout.rdbuf(out.rdbuf());
    tree.inorder();  // Expected: 5 7 10 15
    cout.rdbuf(oldCout);
    
    assert(out.str() == "5 7 10 15 \n");
}

void testContains() {
    SplayTree tree{1, 2, 3, 4, 5};
    assert(tree.contains(3) == true);
    assert(tree.contains(10) == false);
}

void testErase() {
    SplayTree tree{5, 3, 7, 2, 4, 6, 8};
    tree.erase(3);
    tree.erase(6);
    
    // After erasing 3 and 6, in-order should be: 2 4 5 7 8
    ostringstream out;
    streambuf* oldCout = cout.rdbuf(out.rdbuf());
    tree.inorder();
    cout.rdbuf(oldCout);
    
    assert(out.str() == "2 4 5 7 8 \n");
}

void testFindSplayEffect() {
    SplayTree tree{20, 10, 30, 5, 15};
    tree.find(5);  // This should splay node with key=5 to root

    // Now root should be 5
    ostringstream out;
    streambuf* oldCout = cout.rdbuf(out.rdbuf());
    tree.preorder();
    cout.rdbuf(oldCout);
    
    // Root should be 5 now due to splaying (first value in preorder)
    assert(out.str().rfind("5 ", 0) == 0); // starts with 5
}

void testClear() {
    SplayTree tree{1, 2, 3};
    tree.clear();
    assert(tree.empty() == true);
}

int main() {
    testInsertAndInorder();
    testContains();
    testErase();
    testFindSplayEffect();
    testClear();

    cout << "✅ All tests passed!\n";
    return 0;
}
