# Queue

TL; DR: implementation of the std::queue structure

## Documentation for Queue

Defines in header "queue.h"

`template<typename ValueType> class Queue`

The **Queue** class is a container that gives the programmer
the functionality of a queue — specifically, FIFO (first-in, 
first-out) data structure. The class template acts as a wrapper 
to the underlying container - only a specific set of functions 
is provided. The queue pushes the elements on the back of the
underlying container and pops them from the front.

### Rule of five

**Queue** has destructor, copy and move semantics:

+ Destructor

+ Copy constructor

+ Copy assignment operator

+ Move constructor

+ Move assignment operator

### Methods

`Front` — access the first element

`Back` — access the last element

`Empty` — checks whether the underlying container is empty

`Size` — returns the number of elements

`Clear` — removes all elements

`Push` — inserts element at the end

`Pop` — removes the first element

`Swap` — swaps the contents