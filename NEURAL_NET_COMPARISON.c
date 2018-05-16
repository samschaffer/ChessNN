#include "NEURAL_NET_HEADER.h"

double compare (neuron **array1, neuron **array2) {
  int int1arr[73];
  int int2arr[73];
  double error;
  //array1 = malloc(sizeof(neuron *) * 8);
  //array2 = malloc(sizeof(neuron *) * 8);
  /*
  for (int i = 0; i < 8; i++) {
    array1[i] = malloc(sizeof(neuron) * 73);
    array2[i] = malloc(sizeof(neuron) * 73);
  }
  */
  net_init2(array1);
  net_init2(array2);
}
