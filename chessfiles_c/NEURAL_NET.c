#include "NEURAL_NET_HEADER.h"

start_neuron *intake = NULL;
inter_neuron *hidden = NULL;
//start_layer frontlayer = NULL;
in_layer *hidlayer = NULL;
end_neuron *target = NULL;
chess_net *prelim = NULL;
int bdarr[73];

int main (int argc, char *argv[]) {
  int count = 0;
  char c;
  while ((c = getchar()) != '\n') {
    bdarr[count] = c;
    count++;
  }
  net_init();
}

int net_init () {
  //RAND_MAX = 1;
  int layers = 10;
  int npl = 63;
  start_neuron *startarr[73];
  in_layer *hidarr[layers];
  
  //frontlayer->size = 73;

  // creating the start neurons...

  for (int i = 0; i < 73; i++) {
    intake = malloc(sizeof(start_neuron));
    intake->value = sigmoid1(bdarr[i]);
    intake->weight = randomz1();
    intake->bias = 0;
    intake->pos = i;
    startarr[i] = intake;
  }

  // ...start neuron creation done...creating the inter_neurons...

  for (int i = 0; i < layers; i++) {
    hidlayer = malloc(sizeof(in_layer));
    hidlayer->layer = i;
    for (int j = 0; j < npl; j++) {
      hidden = malloc(sizeof(inter_neuron));
      hidden->value = 0;
      hidden->weight = randomz1();
      hidden->bias = 0;
      hidlayer->hidden_neurs[j] = hidden;
      if (i == 0) {
	for (int k = 0; k < 63; k++) {
	  for (int l = 0; l < 73; l++) {
	    startarr[l]->output[k] = hidden;
	  }
        }
      }
      else if (i != 0) {
	for (int a = 0; a < npl; a++) {
	  for (int b = 0; b < npl + 10; b++) {
	    hidarr[i - 1]->hidden_neurs[b]->in_outarr[a]->output = hidden;
	  }
	}
      }
    }
    hidarr[i] = hidlayer;
  }

  // well boy oh boy...what incredible time complexity
 
}

double costfxn () {

}

double sigmoid1 (int val) {
  double out;
  out = (double)val / (1 + (double)abs(val));
  return out;
}

double sigmoid2 (double val) {
  double out;
  out = val / (1 + abs(val));
  return out;
}

double randomz1 () { // set to generate some small random numbers
  int rando1;
  int div;
  int min = 30;
  int max = 70;
  rando1 = rand() % (max + 1 - min) + min;
  div = rand() % (max + 1 - min) + min;
  double rando2;
  rando2 = ((double)rando1 / (double)div);
  return rando2;
}
