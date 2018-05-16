#ifndef NEURAL_NET
#define NEURAL_NET

// do I actually need to define the operations as structs?

//double value;
//double weight;
//int bias;
//int npl = 0;
//int layers = 0;
//int layerarr[0]; // supposed to be 'npl' also whatever
//double slider1;
//double slider2;
//double slider3;

/*
typedef struct operation { // sigmoid here, others (maybe?)
  // sigmoid math goes here
} operation;

typedef struct in_conversion { // used for input neurons
  // bdstate int array goes here
} in_conversion;

typedef struct out_conversion { // used for output neuron
  // conversion back out to bd.state int array goes here
} out_conversion;
*/
/*
typedef struct inter_neuron {
  double value;
  double weight;
  double bias;
  double in_slider;
  //struct operation *sigmoid;
  //struct inter_neuron *input[0], *output; // don't know if this (the **input) works.
  struct input_output *in_outarr[];
} inter_neuron;

typedef struct in_out {
  int in;
  int out;
} in_out;
*/

typedef struct neuron {
  int used;
  int size;
  int layer;
  int pos;
  double value;
  double weight;
  double weighted_val;
  double bias;
  double threshold;
  double in_slider;
  int in[200];
  int out[200];
} neuron;

typedef struct move {
  int move;
  char FENtranslation[73];
} move;

extern neuron nnarray[8][73];
extern int layers;
extern int npl;
extern double adjustment;
extern double convarr[73];
extern int epoch;
extern move gamearr[500][269];
extern int mpg; // moves per game
extern int gps; // games per session

/*
typedef struct input_output {
  struct start_neuron *start_input;
  struct inter_neuron *input;
  struct inter_neuron *output;
} input_output;

typedef struct in_layer {
  int layer;
  int size;
  double slider3;
  struct inter_neuron *hidden_neurs[];
} in_layer;

typedef struct start_neuron {
  int pos;
  double value;
  double weight;
  double bias;
  //struct in_conversion *bd_to_num;
  //struct operation *sigmoid;
  struct inter_neuron *output[];
} start_neuron;

typedef struct end_neuron { // need those three for this one?
  double value;
  double weight;
  double bias;
  //struct out_conversion *num_to_bd;
  struct inter_neuron *input[]; // don't know if this (also the **input) works.
} end_neuron;

typedef struct chess_net {
  int input_amts; // will be inited to 73
  int layers;
  //int layersizes[0];
  double slider1; // for cost fxn
  double slider2; // additional utility slider
  struct end_neuron *end_target;
  struct in_layer *hidden_layers[];
} chess_net;

extern start_neuron *intake;
extern inter_neuron *hidden;
extern in_layer *hidlayer;
extern end_neuron *target;
extern chess_net *prelim;
*/
int pcconv(char pc);
int FENtranslator();
int ruleprocess(int pc, int row, int col);
int possmovecalc ();
double exemplifyfxn();
int net_init();
int net_init2(neuron **array);
int fillfront(neuron **array);
int fire(neuron **array);
int biascalc();
double sigmoid1(int val);
double sigmoid2(double val);
double randomz1();
double decomp(neuron **array);
double compare ();


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
  
#endif

// -4-2-3-5-6-3-2-4-1-10-1-1-1-1-10000000000-10000000001000000002001111011142356304011110012
