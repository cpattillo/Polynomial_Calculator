# Polynomial_Calculator
Polynomial Calculator 

I.	General Concept of Project:

My project calculates basic arithmetic operations for polynomials. Specifically, the project can compute addition, subtraction, and
multiplication of polynomials passed from a file. In my main class I used a while loop and the getline function to read each
polynomial. I then declared a stringstream and set its value to the file line. Using the stream input operator, I extracted a
coefficient and degree and inserted the values into a linked list. Each Node in the linked had a coefficient and degree private data
member. Once I inserted the polynomial into the linked list, I pushed the linked list into a stack. I kept pushing linked lists into a
stack until the getline function came across an operator. Once an operator was found, I retrieved the top linked list from the stack
and removed the top list in the stack. I then pushed the computed polynomial back into the stack.

II.	Linked List and Stack:
I implemented a doubly linked list with a sentinel node. In the Node class I declared the private data members: next, previous,
coefficient, and degree. In the linked list class, I declared a private data member, sentinel. In the constructor I initialized
sentinel to a node with the next and previous pointers pointing to sentinel. For the insert and erase methods, I generally declared a
pointer to the sentinel node’s next value. I then traversed the list and inserted or deleted nodes. I overloaded the addition,
multiplication and subtraction operators. I implemented an array based stack that is used to hold integers or linked list. The top
function returns the top element and the pop function remove the last element. 
Add and Subtract specifics: 
For the addition method, I first sorted the two polynomials from largest degree to smallest degree using a bubble sort function. Next,
I declared a temporary linked list object (list) to hold the sum of the two polynomials. I then declared two current pointers that
pointed to the last node of the polynomials lists, represented by (sentinel->prev and poly.sentinel->prev).  I then implemented a
while loop that ran until one or both of the currents traversed all of the nodes. Inside the while loop, I compared the two degrees.
If the degrees were equal, I added the coefficient and inserted the degree and coefficient to list using the insert front function,
and then moved both pointers to the previous node. If the degrees were unequal, I inserted the smaller degree and its coefficient into
list and moved the smaller degree’s current pointer to the previous node. Because the polynomials are in order from largest to
smallest before entering the while loop, list is in order from largest to smallest. Once the while loop ends, if one current did not
fully traverse one polynomial, I inserted the remaining nodes form that polynomial into list. I then returned the temporary linked
list (list). My subtraction function followed the same format, except I subtracted the coefficients instead of adding them. 

Multiplication specifics: 
The general design for overloading my multiplication operator was taking one term of from polynomial 1 and multiplying it by every
term in polynomial 2. I then pushed that expression into a stack. I then got the second term in polynomial 1 and multiplied it by
every term in polynomial 2 and pushed the expression into a stack. I repeated this process until I used all the terms in polynomial 1.
Once the stack was filled with all the individual expressions, I popped the top two expressions and added them together. I kept
popping and adding the expression until there was one expression in the stack. If there was only one element in the stack to begin
with, I did not pop or add any elements. I then returned the linked list in the top element of the stack. The add method sorted the
expressions with a bubble sort, so the returned expression was in order from largest degree to smallest degree.

III. How to run program
In the main function, I had a loadMineData method that read the polynomials and operators from the file. I had a while loop that gets
each line. I then checked that line had an operator, and if so I performed the polynomial operations. If the line contained no
operators, I declared a stringstream object that held each line from the file. I then extracted each element of the polynomial and
pushed a coefficient and degree into each node of a linked list. I then pushed the whole linked list into a stack. The stack got the
top element and removed the top element during polynomial calculations. The new polynomial after the calculation was pushed into the
stack. 
