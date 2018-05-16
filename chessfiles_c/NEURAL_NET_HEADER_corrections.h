/*
Things that I'm going to put here, that need to go into the header file:
-A struct for the end of the net (this idea replacing that of the out_conversion) responsible for backprop AS WELL AS
 conversion, other important stuff (usage of the cost function, for example), and and necessary sub-structs for it
-definitions of some other important methods; one for topographical-the right word? who knows..-comparison of two graphs, 
 sub-functions for the cost fxn (if necessary) and other fxns, backprop function 
-a struct for the 'overarching' improvement algol (if that even is fucking possible, who knows...)
*/

// structs

typedef struct end_control { // NOT THE END NEURONS (THERE WILL BE 3); COMES AFTER
  
  struct end_neuron *end_list[];
} end_control;

typedef struct derivative_net {
  // largely the same as the previous net; save for some other stuff.
  
} derivative_net;

typedef struct deriv_inoutlist{
  // need to figure out types for input, output
} deriv_inoutlist;

typedef struct matroishka {
  struct derivative_net map;
  
} matroishka;

/*
typedef struct end_list {

} end_list;
*/

// structs

// methods

void backprop(); // directs backpropagation
void monitor(); // monitors net internals (which neurons have the highest biases, weights, fire the most, etc)
void compare(); // compares the topology of two nets for similarities
void matr_direct(); // directs formation, growth of the matroishka improvement net (and so directs correction of the
                       neural net as well)

// methods
