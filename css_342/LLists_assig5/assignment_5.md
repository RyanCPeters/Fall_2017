 
# CSS342 Data Structures, Algorithms, and Discrete Mathematics I
### Assignement 5: Linked Lists

## Purpose
Practice the use of pointers and pointer operations to implement various linked-list functionalities.In this assignment you will design and implement your own single-linked-list class (not at template) from scratch in C++. 

## List Functionality
Design your own linked list class to hold a series of objects.

## Basic Operations
The class should have member functions to implement all basic functionality of a list (i.e., appending, inserting and deleting nodes) as well as constructors and destructors.   

You should implement this list such that it can hold any kind of object in the node. You must implement this as a pointer to an object.

##### Here is what the abstract node would look like:
```

Node
{
	Object *data;
	Node *next;
}

```

For the purpose of this assignment, the Object can simply be a pointer to an integer, so that you can easily display and verify your results, but in theory, you could plug in *any* object. 

In addition, you should implement the following member functions:Add a print member function.  This should display all the values in the linked list, test the class by starting with an empty list, add some elements and print the resulting list.

###### Add a copy constructor. 

Test by making a list, making a copy and displaying the values in the copy.