/*
Notes/rewrite for inter_neuron creation nested loop...
-if start_neuron layer size is 73, and it decreases by 10 per layer, then there cannot be 10 layers of hidden_neurs;
 either decrease the amount npl decreases each time, or decrease the amount of layers
 here, we'll decrease the amount of layers
-fixed problem with for loop (double nested for connection building was adding WAY TOO MANY connections...)
 ...also made connections two-way, doubly linked (making use of both input and output)
*/

int net_init () {
  int layers = 7; // changing number of layers
  int npl = 63;
  start_neuron *startarr[73];
  in_layer *hidarr[layers];
  
  // creating the start neurons...
  
  for (int i = 0; i < 73; i++) { // nothing much changed here...
    intake = malloc(sizeof(start_neuron));
    intake->value = sigmoid1(bdarr[i]);
    intake->weight = randomz1();
    intake->bias = 0;
    intake->pos = i;
    startarr[i] = intake;
  }
  
  // ... start_neuron creation done, onto changed inter_neuron creation...
  
  for (int i = 0; i < layers; i++) {
    hidlayer = malloc(sizeof(in_layer));
    hidlayer->layer = i;
    for (int j = 0; j < npl; j++) {
      hidden = malloc(sizeof(inter_neuron));
      hidden->value = 0;
      hidden->weight = randomz1();
      hidden->bias = 0;
      hidlayer->hidden_neurs[j] = hidden;
      if (i == 0) { // CHANGES HAPPENING HERE
        for (int k = 0; k < 73; k++) { // only building links ONE NEW NODE AT A TIME
          startarr[k]->output[j] = hidden; // also need to add link that goes other way...
          hidden->in_outarr[k]->input = startarr[k]; // ...like so.
        }
      }
      else if (i != 0) {
        for (int k = 0; k < npl + 10; k++) { // same for all other cases
          hidarr[i - 1]->hidden_neurs[k]->in_outarr[j]->output = hidden; // need to add link here too...
          hidden->in_outarr[k]->input = hidarr[i - 1]->hidden_neurs[k]; //...there we go.
        }
      }
    }
    hidarr[i] = hidlayer;
    npl = npl - 10;
  }
  
  // that's what I've added...
  
}
