#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "neuronclass.h"

// currently using rand1 for weights, rand10 for biases. Works?
// I think so.
// let's try rand3 for weights (-3 to 3)

int neurons = 826;
int cycles = 60000; // the number of items to go through in the training data set

typedef struct link { // the struct for connections. Contains the weight of the connection and the position of the neuron connected to
  float weight;
  int pos;
} link;

typedef struct neuron { // the struct for neurons.
  float activation, bias; // the neuron's activation, bias
  int pos, ihoID, linksize; // the neuron's position in the net_list (pos), status as input (0), hidden (1) or output (2) neuron, link_list size
  struct link *link_list[784]; // the list for containing connections and their weights. Not using flex array (should be), so size is 784 default
} neuron;

typedef struct net { // the struct for the net.
  int neurs, weights, biases, passes, fails; // # of neurons, weights, biases, test passes, test fails.
  float avg_cost, ps_fs; // overall cost for training examples, ratio of passes to fails as a float (passes / fails)
  float ac_arr[10]; // array containing the target output values for each training example
  float cost_arr[10]; // array containing the output costs for each training example
  float img_arr[784]; // array containing the input vals, loaded in as floats from 0 to 1
  struct neuron *net_list[826]; // the list containing the actual neurons
} net;

struct net* build (); // configured for specific type of perceptron. Builds/links the structure, randomizes weights/biases, etc.
int forward (struct net *net_iq); // feeds forward.
int cost (struct net *net_iq); // calculates the cost for each training example.
//int bprop (struct net *net_iq);
struct net* trainer (struct net *tbt); // trains the net on (cycle) amount of training images. Uses forward, cost, and bprop.
struct neuron* creator (int pos, int ihoID); // creates neurons, taking in list position and status as input (0), hidden (1), or output (2) neuron
int linker (struct net *net_iq, struct neuron *niq, struct neuron *ntl); // creates a connection from neuron niq to neuron ntl (in net net_iq)
float sigmoid (float val); // fast sigmoid (ReLu? is that what it's called?)
float rand10 (); // random numbers between 0 and 10
float rand3 (); // random numbers between -3 and 3
float rand1 (); // random numbers between 0 and 1

int main (int argc, char *argv[]) {
  srand(time(NULL)); // for generating new random numbers with each execution of the program
  struct net *perceptron = build(); // building the net
  struct net *p_trained = trainer(perceptron); // training it
}

struct net* build () {
  struct net *retnet = (net *)malloc(sizeof(net)); // mallocing (done correctly? who knows) and initializing relevant values (as well as arrays)
  retnet->biases = 0;
  retnet->weights = 0;
  retnet->neurs = 0;
  retnet->avg_cost = 0;
  for (int i = 0; i < 10; i++) {
    retnet->ac_arr[i] = 0;
  }
  for (int i = 0; i < 784; i++) {
    retnet->img_arr[i] = 0;
  }
  for (int i = 0; i < neurons; i++) { // building the neurons
    struct neuron *add; // declaration of neuron to be added
    retnet->net_list[i] = (neuron *)malloc(sizeof(neuron)); // malloc for space in net_list
    if (i < 784) { // If i < 784, then it is one of the input neurons...
      add = creator(i, 0); // ...so, create a neuron of type input (0) with pos (i) and increment neurs (input neurons have no bias)
      retnet->neurs++;
    }
    else if (i >= 784 && i < 816) { // If i >= 784 && < 816, then it is one of the hidden neurons...
      add = creator(i, 1); // ...so, create a neuron of type hidden (1) with pos (i), increment neurs and biases
      retnet->neurs++;
      retnet->biases++;
    }
    else if (i >= 816 && i < 826) { // If i >= 816 && i < 826, then it is one of the output neurons...
      add = creator(i, 2); // ...so, create a neuron of type output (2) with pos (i), increment neurs and biases
      retnet->neurs++;
      retnet->biases++;
    }
    retnet->net_list[i] = add; // place the neuron created in the net_list at index i
  }
  for (int i = 784; i < neurons; i++) { // linking the neurons (only the hidden and output neurons need actual internal lists, so it starts at 784)
    if (i < 800) { // if i < 800, then it's in the first hidden layer. Each neuron needs connections to all 784 neurons in the input layer...
      for (int j = 0; j < 784; j++) { // ...so, for each neuron in the input layer...
	linker(retnet, retnet->net_list[i], retnet->net_list[j]); // ...add it to the link_list of net_list[i] in retnet
      }
    }
    else if (i >= 800 && i < 816) { 
      for (int j = 784; j < 800; j++) {
	linker(retnet, retnet->net_list[i], retnet->net_list[j]);
      }
    }
    else if (i >= 816 && i < 826) {
      for (int j = 800; j < 816; j++) {
	linker(retnet, retnet->net_list[i], retnet->net_list[j]);
      }
    }
  }
  return retnet; // ...blah blah blah, you get the point for the rest of them. Fully built and linked net returned.
}

struct neuron* creator (int pos, int ihoID) {
  struct neuron *retneur = (neuron *)malloc(sizeof(neuron)); // malloc for neuron, initializing of relevant values 
  retneur->activation = 0;
  retneur->bias = 0;
  retneur->pos = pos;
  retneur->ihoID = ihoID;
  retneur->linksize = -1; // set default to -1 (since 784 out of the 826 neurons have no list)
  /*
  if (retneur->ihoID == 0) { 
    retneur->linksize = -1;
  }
  */
  if (retneur->ihoID == 1) { // if it's a hidden neuron, set linksize to 0 (means that it can have a link_list) and generate a random bias
    retneur->linksize = 0;
    retneur->bias = rand10();
  }
  else if (retneur->ihoID == 2) { // same if it's an output neuron
    retneur->linksize = 0;
    retneur->bias = rand10();
  }
  return retneur; // return the newly created neuron
}

int linker (struct net *net_iq, struct neuron *niq, struct neuron *ntl) {
  int size = niq->linksize; // intermediate vars for linksize and pos (makes writing the code easier)
  int pos = ntl->pos;
  float weight = rand3(); // randomized weight for connection
  niq->link_list[size] = (link *)malloc(sizeof(link)); // mallocing of index in link_list, and creation of link itself (with mallocing)
  struct link *lnew = (link *)malloc(sizeof(link));
  lnew->pos = pos; // link's position set to the position of the neuron 'ntl' (neuron to link)
  lnew->weight = weight; // link's weight set to the randomized weight
  niq->link_list[size] = lnew; // link inserted into 'niq' (neuron in question) link_list, at position size
  niq->linksize++; // new link, so linksize of niq increased 
  net_iq->weights++; // overall amount of weights in net_iq increased
  return 1; // returns 1 if executed successfully
}

struct net* trainer (struct net *tbt) {
  FILE *imageFile, *labelFile; // declaring names of MNIST files to be opened, files then opened with MNISTutils functions
  imageFile = openMNISTIMGFile(MNIST_TRAINING_SET_IMAGE_FILE_NAME);
  labelFile = openMNISTLBLFile(MNIST_TRAINING_SET_LABEL_FILE_NAME);
  for (int i = 0; i < cycles; i++) { // for the amount of cycles specified...
    struct MNIST_IMG *img = getIMG(imageFile); // gets an image and its label from the file (then sets an intermediate var to lbl->label)
    struct MNIST_LBL *lbl = getLBL(labelFile);
    uint8_t label = lbl->label;
    for (int j = 0; j < 10; j++) { // sets the net's target values for this given training example. 1 for the label's position, 0 for all other positions
      if (j == label) { 
	tbt->ac_arr[j] = 1;
      }
      else if (j != label) {
	tbt->ac_arr[j] = 0;
      }
    }
    for (int j = 0; j < 28; j++) { // takes the greyscale values in img, converts them to proportional floats (from 0 to 1)...
      for (int k = 0; k < 28; k++) {
	float div = ( (img->pixel[(j * 28) + k]) * (uint8_t)10 ) / (uint8_t)255;
	float div_d = div / 10;
	tbt->img_arr[(j * 28) + k] = div_d; // ...places the new value into into img_arr...
        tbt->net_list[(j * 28) + k]->activation = tbt->img_arr[(j * 28) + k]; // ... then sets that value as the activation of input neur [(j * 28) + k]
      }
    }
    forward(tbt); // feed forward
    cost(tbt); // cost calc

    printf("\nCYCLE %d, LABEL (BELOW): %hhu\n\n", i, label);
    for (int j = 0; j < 28; j++) {
      for (int k = 0; k < 28; k++) {
	float iq = tbt->img_arr[(j * 28) + k];
	if (iq == 0) {
	  printf("_");
	}
	else if (iq > 0 && iq <= .2) {
	  printf("e");
	}
	else if (iq > .2 && iq <= .4) {
	  printf("d");
	}
	else if (iq > .4 && iq <= .6) {
	  printf("c");
	}
	else if (iq > .6 && iq <= .8) {
	  printf("b");
	}
	else if (iq > .8 && iq <= 1) {
	  printf("a");
	}
      }
      printf("\n");
    }
    printf("\n");
    printf("AVG_COST %f, OUTPUT VALS:\n", tbt->avg_cost);
    for (int i = 816; i < 826; i++) {
      printf("...NEUR %d ACTIVATION: %f, goal, %f\n", i, tbt->net_list[i]->activation, tbt->ac_arr[i - 816]); 
    }
    
  }
  fclose(imageFile);
  fclose(labelFile);
  return tbt;
}

int forward (struct net *net_iq) {
  for (int i = 784; i < neurons; i++) { // for all hidden and output neurons...
    struct neuron *niq = net_iq->net_list[i]; // intermediate neuron niq
    for (int j = 0; j < niq->linksize; j++) { // ...for all items in niq's link_list...
      int pos = niq->link_list[j]->pos; 
      int weight = niq->link_list[j]->weight;
      struct neuron *tbs = net_iq->net_list[pos]; // ...tbs (to be summed) is the neuron with position 'pos'...

      /*
      niq->activation = niq->activation + sigmoid(tbs->activation * weight); // are these correct?
      niq->activation = sigmoid(niq->activation);
      */

      niq->activation = niq->activation + (tbs->activation * weight); // ...niq's activation is equal to its activation plus the weighted sum of tbs...
    }
    niq->activation = sigmoid(niq->activation + niq->bias); // ...activation = sigmoid of activation (now sum of all prev. ones) plus bias
  }
  return 1; // return 1 if successful
}

int cost (struct net *net_iq) {
  float newcost = 0; // var newcost initialized
  for (int i = 0; i < 10; i++) { // for each position in the output layer...
    float sqar = (net_iq->net_list[i + 816]->activation - net_iq->ac_arr[i]); // sqar ('square'): activation of output neuron, minus target in ac_arr...
    sqar = sqar * sqar; // ...squared.
    net_iq->cost_arr[i] = sqar; // sqar placed into cost_array
    newcost = newcost + sqar; // newcost is equal to newcost plus the newly calculated sqar
  }
  newcost = newcost / 10; // newcost divided by 10, to give the average cost over all 10 targets...
  if (net_iq->avg_cost == 0) { // if avg_cost is 0 (AKA if its on the first training example)
    net_iq->avg_cost = newcost; // avg_cost equals newcost
  }
  else if (net_iq->avg_cost != 0) { // if avg_cost doesn't equal 0 (if it's not on the first training example)
    newcost = (newcost + net_iq->avg_cost) / 2; // newcost equals (newcost plus avg_cost) divided by two
    net_iq->avg_cost = newcost; // THEN avg_cost equals newcost
  }
  return 1;
}

/*
int bprop (struct net *net_iq) {
  
}
*/

float sigmoid (float val) { // not technically sigmoid, something faster I found online.
  return val / ((float)1 + fabs(val));
}

float rand1 () {
  return fabs((float)rand() / (float)RAND_MAX);
}

float rand3 () {
  float retnum;
  float sign = rand1();
  if (sign >= .5) {
    retnum = rand1() * (float)3;
  }
  else if (sign < .5) {
    retnum = (rand1() * (float)3) * -1;
  }
  return retnum;
}

float rand10 () {
  float retnum;
  retnum = rand1() * (float)10;
  return retnum;
}
