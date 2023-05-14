 
#include "pico/stdlib.h"
#include "pico/time.h"
#include "distance.h"
#include <math.h>
#include "main.h"
#include "./screens/simulator_screen.h"
#include "simulation.h"
int depths[Q_SIZE] ;

//initialize depth array
void simulation_init(){
     for(int i=0;i<Q_SIZE;i++)depths[i]=0;

}

//rebar depth simulation by update depth array  
void simulate(int end,int curr_distance){
     if(end>=Q_SIZE){
        for(int i=0;i<Q_SIZE-1;i++)depths[i]=depths[i+1];
        depths[Q_SIZE-1]=curr_distance;
     }
     else{depths[end]=curr_distance;}
   
     return ;
}

//update UI accordingly
void display_simulation(int end){
     simulator_screen_init(depths,end);
}
 

