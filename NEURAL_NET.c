#include "NEURAL_NET_HEADER.h"

/*

start_neuron *intake, *start_input = NULL;
inter_neuron *hidden, *input, *output = NULL;
//start_layer frontlayer = NULL;
in_layer *hidlayer = NULL;
end_neuron *target = NULL;
chess_net *prelim = NULL;

*/

int bdarr[73];
int layers = 8;
int npl = 73;
double adjustment = .5;
double diff;
double convarr[73];
double error;
int total;

/*

typedef struct in_out {
  int in;
  int out;
} in_out;

*/

/*

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
  int in[200]; // totally arbitrary number. Heres how it works:
                   // indices 0 and 1: first input (layer, pos)
                   // indices 2 and 3: second input
                   // indices 4 and 5: third
                   // and so on, and so on, and so on
  int out[200]; // works the same as the previous 
} neuron;

*/

//double errorsig = sigmoid1(error);

int main (int argc, char *argv[]) {
  neuron **nnarray = malloc(sizeof(neuron *) * 8); 
  for (int i = 0; i < 8; i++) {
    nnarray[i] = malloc(sizeof(neuron) * 73);
  }
  int count = 0;
  char c;
  while ((c = getchar()) != '\n') {
    bdarr[count] = c;
    total = total + (c - 48);
    printf("%d\n", total); // DEBUG STMT
    count++;
  }
  net_init2(nnarray);
  fillfront(nnarray);
  fire(nnarray);
  //exemplifyfxn();
  
  /*

  for (int i = 0; i < 20; i++) { // DEBUG LOOP
    double rando = randomz1();
    printf("%f\n", rando);
  }

  */
}

int net_init2 (neuron **array) { //init works! All layers, from 0 with size 73 to 7 with size 3, fully initialized and connected! 
  layers = 8;
  npl = 73;
  int count = 73;
  for (int i = 0; i < layers; i++) {
    for (int j = 0; j < npl; j++) {
      struct neuron *neur = malloc(sizeof(*neur));
      neur->used = 1; // if the neuron is actually used within the array (if it's not one of the 'blank' spaces)
      neur->layer = i; // the layer
      neur->pos = j; // the position
      neur->value = 0; // the value held (double)
      neur->weight = randomz1(); // the randomized weight (double)
      neur->bias = randomz1(); // the randomized bias (also double)
      neur->threshold = 0; // threshold
      neur->weighted_val = (neur->value * neur->weight); // a random utility slider (double as well)
      neur->in[0] = 0; // the default settings of the input conn array
      neur->in[1] = 0;
      neur->out[0] = 0; // default settings of the output conn array
      neur->out[1] = 0;
      array[i][j] = *neur; // insertion of neur into the network array
    }
    if (count > npl) {
      for (int j = npl; j < count; j++) { // because the spaces have to be filled? I think? I may just get rid of this. 
	struct neuron *neur = malloc(sizeof(*neur));
	neur->used = 0;
	neur->layer = 0;
	neur->pos = 0;
	neur->value = 0;
	neur->weight = 0;
	neur->bias = 0;
	neur->in_slider = 0;
	neur->in[0] = 0;
	neur->in[1] = 0;
	neur->out[0] = 0;
	neur->out[1] = 0;
	array[i][j] = *neur;
      }
    }
    npl = npl - 10;
  }
  npl = 73;
  
  /*

  for (int i = 0; i < layers; i++) { // DEBUG LOOP
    for (int j = 0; j < npl; j++) {
      if (nnarray[i][j].used == 1) {
	printf("%d", nnarray[i][j].layer);
      }
      else if (nnarray[i][j].used == 0) {
	printf("_");
      }
    }
    printf("\n");
  }

  */

  for (int i = 1; i < layers; i++) { // through the layers, starting with layer 'two' (1) - IN-CONNECTIONS
    for (int j = 0; j < npl; j++) { // through each neuron of the current layer
      int count1 = 0; // starting with the first 'input' indice, zero (layer)
      int count2 = 1; // ... and the second, one (pos)
      for (int k = 0; k < npl + 10; k++) { // cycling through each neuron of the previous layer...
	if (array[i][j].used == 1) {
	  array[i][j].in[count1] = array[i - 1][k].layer;
	  array[i][j].in[count2] = array[i - 1][k].pos;
	  count1 = count1 + 2;
	  count2 = count2 + 2;
        }
      }
    }
    npl = npl - 10;
  }
  npl = 73;
  for (int i = 0; i < layers - 1; i++) { // OUT-CONNECTIONS
    for (int j = 0; j < npl; j++) {
      int count1 = 0;
      int count2 = 1;
      for (int k = 0; k < npl - 10; k++) {
	if (array[i][j].used == 1) {
	  array[i][j].out[count1] = array[i + 1][k].layer;
	  array[i][j].out[count2] = array[i + 1][k].pos;
	  count1 = count1 + 2;
	  count2 = count2 + 2;
	}
      }
    }
    npl = npl - 10;
  }
  npl = 73;

  //A VERY LARGE SERIES OF DEBUG LOOPS - DISPLAY ALL HIDDEN LAYERS, WITH EACH NEURON'S SET OF CONNECTIONS
  /*
  npl = 73;
  printf("\n");
  for (int i = 0; i < layers; i++) {
    printf("LAYER %d\n\n", i);
    int count1 = 0;
    int count2 = 1;
    for (int j = 0; j < npl; j++) {
      printf("NEURON %d, ", j);
      if (i == 0) {
	printf("OUT\n");
	for (int k = 0; k < npl - 10; k++) {
	  printf("%d %d; ", array[array[i][j].out[count1]][array[i][j].out[count2]].layer, array[array[i][j].out[count1]][nnarray[i][j].out[count2]].pos);
	  count1 = count1 + 2;
	  count2 = count2 + 2;
	}
	printf("\n");
	count1 = 0;
	count2 = 1;
      }
      else if (i == 7) {
	printf(" IN\n");
	for (int k = 0; k < npl + 10; k++) {
	  printf("%d %d; ", array[array[i][j].in[count1]][array[i][j].in[count2]].layer, array[array[i][j].in[count1]][array[i][j].in[count2]].pos);
	  count1 = count1 + 2;
	  count2 = count2 + 2;
	}
	printf("\n");
	count1 = 0;
	count2 = 1;
      }
      else {
	printf(" IN-OUT\n");
        for (int k = 0; k < npl + 10; k++) {
	  if (nnarray[i][j].used == 1 && ((array[array[i][j].out[count1]][array[i][j].out[count2]].layer) != 0 || (array[array[i][j].out[count1]][array[i][j].out[count2]].pos) != 0)) { 
	    printf("%d %d; ", nnarray[nnarray[i][j].in[count1]][nnarray[i][j].in[count2]].layer, nnarray[nnarray[i][j].in[count1]][nnarray[i][j].in[count2]].pos);
	    printf("%d %d| ", nnarray[nnarray[i][j].out[count1]][nnarray[i][j].out[count2]].layer, nnarray[nnarray[i][j].out[count1]][nnarray[i][j].out[count2]].pos);
	  }
	  else {
	    printf("%d %d; ", nnarray[nnarray[i][j].in[count1]][nnarray[i][j].in[count2]].layer, nnarray[nnarray[i][j].in[count1]][nnarray[i][j].in[count2]].pos);
	    printf("N N| ");
	  }
	  count1 = count1 + 2;
	  count2 = count2 + 2;
        }
        printf("\n");
        count1 = 0;
        count2 = 1;
      }
    }
    printf("\n");
    npl = npl - 10;
  }
  */
  return 1;
}

int fillfront (neuron **array) { // loads up the starter neurons
  for (int i = 0; i < 73; i++) {
    double convert;
    convert = ((double)bdarr[i] / (double)total) - 1; // Every element divided by the total - becomes a ratio
    convarr[i] = convert;
    printf("%f, array indice %d\n", convert, i); // DEBUG STMT
  }
  //printf("VALUES, MULTIPLIED BY WEIGHTS\n");
  for (int i = 0; i < 73; i++) {
    printf("%f\n", array[0][i].weight); // DEBUG STMT
    array[0][i].value = convarr[i];
    array[0][i].weighted_val = array[0][i].value * array[0][i].weight;
    printf("%f (weighted val), %f (val), %f (weight), %f bias, indice %d\n", array[0][i].weighted_val, array[0][i].value, array[0][i].weight, array[0][i].bias, i); // DEBUG STMT
  }
}

int fire (neuron **array) {
  for (int i = 0; i < layers - 1; i++) {
    for (int j = 0; j < npl; j++) {
      for (int k = 0; k < npl - 10; k++) {
	double check;
	check = (array[i + 1][k].weighted_val + array[i][j].weighted_val) * array[i + 1][k].weight * array[i + 1][k].bias;
	//printf("Currently at nnarray[%d][%d], have just evalled one at [%d][%d]...", i, j, i + 1, k); // DEBUG STMT
	if (check >= array[i + 1][k].threshold) {
	  array[i + 1][k].weighted_val = sigmoid2(check);
	  //nnarray[i + 1][k].bias = nnarray[i + 1][k].bias + .01;
	  //printf("%f is new weighted val at [%d][%d]\n", sigmoid2(check), i + 1, k); // DEBUG STMT
	}
	
	//printf("%f is weighted val at [%d][%d]\n", check, i + 1, k); // DEBUG STMT
      }
    }
    npl = npl - 10;
  }
  npl = 73;
  decomp(array);
  
  //exemplifyfxn(); // Makes small values 
  //printf("%d\n", epoch); // DEBUG STMT
  return diff;
}

/*

int biascalc () {
  
}

*/

/*
double exemplifyfxn () { // very simple - "heightens" contrast between nodes (small nodes smaller, large nodes larger)
  double tbr;
  int high_nodes = 0;
  int low_nodes = 0;
  //double adjustprev;
  npl = 3;
  for (int i = 0; i < 3; i++) { // DEBUG LOOP
    printf("nnarray[%d][%d].weighted_val is %f\n", 7, i, nnarray[7][i].weighted_val);
  }
  for (int i = 7; i > 0; i--) {
    for (int j = 0; j < npl; j++) {
      for (int k = 0; k < npl + 10; k++) {
	int count1 = 0;
	int count2 = 0;
	if (nnarray[i][j].weighted_val > adjustment) { // changing from weighted_val to weight
	  nnarray[i][j].bias = nnarray[i][j].bias + .01;
	  high_nodes++;
	  for (int a = 0; a < npl + 10; a++) {
	    int layr = nnarray[nnarray[i][j].in[count1]][nnarray[i][j].in[count2]].layer;
	    int poz = nnarray[nnarray[i][j].in[count1]][nnarray[i][j].in[count2]].pos;
	    nnarray[layr][poz].weight + .001;
	    count1 = count1 + 2;
	    count2 = count2 + 2;
	  }
	  count1 = 0;
	  count2 = 1;
	  //printf("NEW BIASE FOR NNARR[%d][%d], %f; ", i - 1, k, nnarray[i - 1][k].bias); // DEBUG STMT
	}
	else if (nnarray[i][j].weighted_val <= adjustment) {
	  nnarray[i][j].bias  = nnarray[i][j].bias - .01;
	  low_nodes++;
	  for (int a = 0; a < npl + 10; a++) {
	    int layr = nnarray[nnarray[i][j].in[count1]][nnarray[i][j].in[count2]].layer;
	    int poz = nnarray[nnarray[i][j].in[count1]][nnarray[i][j].in[count2]].pos;
	    nnarray[layr][poz].weight - .001;
	    count1 = count1 + 2;
	    count2 = count2 + 2;
	  }
	  count1 = 0;
	  count2 = 1;
	  //printf("NEW BIASE FOR NNARR[%d][%d], %f; ", i - 1, k, nnarray[i - 1][k].bias); // DEBUG STMT
	}
      }
      //printf("\nNEW NODE!\n"); // DEBUG STMT
    }
    //printf("\nNEW LAYER!\n"); // DEBUG STMT
    npl = npl + 10;
  }
  //printf("DONE!\n"); // DEBUG STMT
  printf("%d high nodes, %d low nodes\n", high_nodes, low_nodes); // DEBUG STMT
  if ((high_nodes > low_nodes && high_nodes < 7500) && low_nodes > 2500) { // if there are more high nodes, but less than 7500, and less low nodes, but more than 2500
    //adjustprev = adjustment;
    adjustment = sigmoid1((double)high_nodes / (double)low_nodes);
    //adjustment = (adjustment + adjustprev) / 2;
  }
  else if ((low_nodes > high_nodes && low_nodes < 7500) && low_nodes > 2500) { // if there are more low nodes, but less than 2500 (you get my point)
    //adjustprev = adjustment;
    adjustment = sigmoid1((double)high_nodes / (double)low_nodes);
    //adjustment = (adjustment + adjustprev) / 2;
  }
  //tbr = adjustprev - adjustment; // the difference between the current and previous adjustment (what determines a node's status as low or high)
  //printf("%f, adjustment, %f, tbr\n", adjustment, tbr); // DEBUG STMT
  npl = 73;
  decomp(nnarray); // pass into decomp, the actual backprop fxn
  fire(nnarray);
  npl = 73;
  return tbr;
}
*/


double sigmoid1 (int val) {
  double out;
  out = ((double)val / (1 + (double)abs(val))) / 10;
  return out;
}

double sigmoid2 (double val) {
  double out;
  out = val / (1 + abs(val));
  return out;
}

double randomz1 () { // set to generate some small random numbers
  return (double)rand() / (double)RAND_MAX;
}

double decomp (neuron **array) {
  int epoch = 10;
  npl = 3;
  for (int i = 0; i < epoch; i++) {
    double dotp = 0;
    for (int i = 7; i < 0; i--) {
      for (int j = 0; j < npl; j++) {
	dotp = dotp + (array[i][j].value * array[i][j].bias);
      }
      dotp = sigmoid2(dotp);
      
    }
  }
}


  
  /*
  
  printf("%f, %f, %f\n", d1, d2, d3); // DEBUG STMT
  //double sum1 = d1 + d2 + d3;
  double sum2;
  //printf("%f\n", sum1); // DEBUG STMT
  for (int i = 0; i < 73; i++) {
    sum2 = sum2 + (bdarr[i] - 48);
  }
  printf("%f\n", sum2); // DEBUG STMT
  for (int i = 7; i > 0; i--) {
    for (int j = 0; j < npl; j++) {
      for (int k = 0; k < npl + 10; k++) {
	if (i == 7) {
	  double new1_weight = sum2 / nnarray[i][j].weighted_val; // changed to sigmoidal
	  nnarray[i][j].weight = new1_weight;
	  printf("%f, %f\n", nnarray[i][j].weighted_val, new1_weight);// DEBUG STMT
	}
	double new_weight = nnarray[i][j].weighted_val / nnarray[i - 1][k].weighted_val;
	nnarray[i - 1][k].weight = new_weight;
	printf("%f\n", new_weight); // DEBUG
      }
    }
    npl = npl - 10;
  }

  */


