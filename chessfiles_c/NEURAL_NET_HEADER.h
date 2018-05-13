#ifndef NEURAL_NET
#define NEURAL_NET

// do I actually need to define the operations as structs?

//double value;
//double weight;
//int bias;
int npl = 0;
int layers = 0;
int layerarr[0]; // supposed to be 'npl' also whatever
//double slider1;
//double slider2;
//double slider3;

typedef struct operation { // sigmoid here, others (maybe?)
  // sigmoid math goes here
} operation;

typedef struct in_conversion { // used for input neurons
  // bdstate int array goes here
} in_conversion;

typedef struct out_conversion { // used for output neuron
  // conversion back out to bd.state int array goes here
} out_conversion;

typedef struct inter_neuron {
  double value;
  double weight;
  int bias;
  struct operation *sigmoid;
  struct inter_neuron *input[0], *output; // don't know if this (the **input) works.
  double in_slider; // random utility slider
} neuron;

typedef struct in_layer {
  int layer;
  struct inter_neuron *hidden_neurs[0];
  double slider3; // random utility slider
} in_layer;

typedef struct start_neuron {
  double value;
  double weight;
  int bias;
  struct in_conversion *bd_to_num;
  struct operation *sigmoid;
  struct inter_neuron *output;
} start_neuron;

typedef struct end_neuron { // need those three for this one?
  double value;
  double weight;
  int bias;
  struct out_conversion *num_to_bd;
  struct inter_neuron *input[]; // don't know if this (also the **input) works.
} end_neuron;

typedef struct chess_net {
  int input_amts; // will be inited to 73
  int layers;
  int layersizes[0];
  double slider1; // for cost fxn
  double slider2; // additional utility slider
  struct start_neuron *inputs[0]; // is this how an array of structs goes?
  struct in_layer *hidden_layers[0];
  struct end_neuron *end_target;
} chess_net;

int pcconv (char pc);
double cost_fxn ();

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
  
#endif
