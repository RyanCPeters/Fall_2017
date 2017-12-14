 
# CSS342 Data Structures, Algorithms, and Discrete Mathematics I
### Assignement 5: Linked Lists
#### Contents:
[Purpose]()
[]()
[]()
[]()

## Purpose
Practice the use of pointers and pointer operations to implement various linked-list functionalities.In this assignment you will design and implement your own single-linked-list class (not at template) from scratch in C++. 

#### List Functionality
_Design your own linked list class to hold a series of objects._

## Basic Operations
The class should have member functions to implement all basic functionality of a list (i.e., appending, inserting and deleting nodes) as well as constructors and destructors.   

You should implement this list such that it can hold any kind of object in the node. You must implement this as a pointer to an object.

##### Here is what the abstract node would look like:


	Node 																
	{
		Object *data;
		Node *next;
	}


For the purpose of this assignment, the Object can simply be a pointer to an integer, so that you can easily display and verify your results, but in theory, you could plug in *any* object. 

In addition, you should implement the following member functions:Add a print member function.  This should display all the values in the linked list, test the class by starting with an empty list, add some elements and print the resulting list.

###### Add a copy constructor. 

Test by making a list, making a copy and displaying the values in the copy.


#### Reverse
Add a member function that rearranges the nodes so that their order is reversed. Test byprinting the list before and after it is reversed.

*You are not allowed to use any additional list to reverse the original list.  You should do this by rearranging the pointers.*

1. Implement an iterative version of the reverse function, place your solution in a function named **ReverseIterative**
2. Implement a recursive solution of the Reverse function,
	* name it ReverseRecursive
		* Hint: implement the recursive solution first, then use that as a basis for the iterative solution.
		* Note: if you use *any* external sources or references, you must include the reference in your document, otherwise it will be considered plagiarism.
		
#### Driver

* Allocate a list of 10-20 random integers.
* Demo all the functionalities of your list with a driver program. 
* Clearly print out the results of each operation (e.g., list before and after an insert).

## Deliverables

1. Source codea.
	1. List Class
	2. Driver
		1. Must demonstrate every an each functionality described above2.
2. Documentationa.
	1. Discuss your design and approach for solving the problemb.
	2. You are encouraged to use pictures to illustrate what you're doingc.
	3. Discuss the differences and similarities between the two approaches, i.e., iterative vs. recursive

## Grading Guide
*Out of 20 pts*

1. Documentation (6 pt)
	* Design and approach discussion: 4pt
	* Differences and similarities: 2pt
2. Correctness (12 pt) 
	* _As usual, zero points if program doesn't compile_
	* [1p] Correct implementation of basic operations
	* [1p] Copy Constructo
	* [1p] Print list
	* [4p] Reverse Iterative*
	* [4p] Reverse Recursive
	* [1p] Driver
	
###### [back to top](https://github.com/RyanCPeters/Fall_UWB_2017/blob/master/css_342/LLists_assig5/ReadMe.md#css342-data-structures-algorithms-and-discrete-mathematics-i)
