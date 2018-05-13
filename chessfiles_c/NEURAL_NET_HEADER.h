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

typedef struct inter_neuron {
  double value;
  double weight;
  double bias;
  struct operation *sigmoid;
  double in_slider;
  struct input_output *in_outarr[]; // don't know if this (the **input) works.
} inter_neuron;

typedef struct input_output {
  struct inter_neuron *input;
  struct inter_neuron *output;
} input_output;

typedef struct in_layer {
  int layer;
  int size;
  double slider3;
  struct inter_neuron *hidden_neurs[];
} in_layer;

//typedef struct start_layer {
//int size;
//struct start
//} start_layer;

typedef struct start_neuron {
  int pos;
  double value;
  double weight;
  double bias;
  struct in_conversion *bd_to_num;
  struct operation *sigmoid;
  struct inter_neuron *output[];
} start_neuron;

//typedef struct start_layer {
//int size;
//struct start_neuron *start_neurs[0];
//double slider4;
//} start_layer;

typedef struct end_neuron { // need those three for this one?
  double value;
  double weight;
  double bias;
  struct out_conversion *num_to_bd;
  struct inter_neuron *input[]; // don't know if this (also the **input) works.
} end_neuron;

typedef struct chess_net {
  int input_amts; // will be inited to 73
  int layers;
  //int layersizes[];
  double slider1; // for cost fxn
  double slider2; // additional utility slider
  struct end_neuron *end_target;
  struct start_neuron *inputs[]; // is this how an array of structs goes?
  struct in_layer *hidden_layers[];
} chess_net;

extern start_neuron *intake;
extern inter_neuron *hidden;
//extern start_layer frontlayer;
extern in_layer *hidlayer;
extern end_neuron *target;
extern chess_net *prelim;

int pcconv(char pc);
double cost_fxn();
int net_init();
double sigmoid1(int val);
double sigmoid2(double val);
double randomz1();

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
  
#endif
