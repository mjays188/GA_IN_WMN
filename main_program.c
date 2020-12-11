/*
  SEARCH BASED ROUTING IN WIRELESS MESH NETWORK USING GENETIC ALGORITHM

  TEAM MEMBERS - ASHISH SINGH       ROLL NO - 106118016
                 YASHWANT GOHOKAR   ROLL NO - 106118108
                 MRITYUNJAY SANKHLA ROLL NO - 106118060

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "RequiredDataStructures.h"
#include "geneticAlgo.h"




int main (){
	//int continue_exe=1;

	int cntr=0;
	int stop_cntr=0;
    double cur=0.0;

	/* INITIALIZING THE ROUTES POPULATION */
	route *way [TotalRoutes]; // Using way we create linked list of routes

	int i=0;
	srand(time(0));

	for (i=0 ; i<TotalRoutes; i++){
		way[i] = initialize(&cntr); // We populate the routes with routers using initialize function
	}
	/* INITIALIZATION ENDS */

	evaluateFitness (way,&cntr); // Evaluating Fitness for zeroth Generation

	printf ("Generation 0:\n");                  // Printing Results for Zeroth Generation
	show (way,&stop_cntr,&cur);                  // Showing all the routes along with the intermediate routers

	//printf ("Do you want to continue route crossover? 1-yes, 0-no ");
	//scanf ("%d", &continue_exe);

	int GenerationCount = 1;		//initializing generations counter


	while (1){

		srand(time(0));
		printf ("Generation %d:\n\n", GenerationCount);
		Crosover (way,&cntr);             // Performing Crossover
		Do_Elitism (way,&cntr);           // Performing Elitism
		removeRepeated (way,&cntr);
		update_route_time_total (way,&cntr); // Updating the latencies of routers in the corresponding routes
		evaluateFitness (way,&cntr);      // Evaluating fitness for the current Generation
		show (way,&stop_cntr,&cur);
		GenerationCount++;

		//printf ("Do you want to continue route crossover? 1-yes, 0-no ");
        printf("stop counter %d\n",stop_cntr);
		//scanf ("%d", &continue_exe);
		printf ("\n\n");
        if(stop_cntr==4)
            break;
	}
   printf("\n\n[########## ----  OPTIMALITY REACHED SUCCESSFULLY ---- ##########]\n\n\n");
   printf("Number of instructions executed is : %d\n",cntr);
   printf("Total Generations involved is : %d\n",GenerationCount);
	return 0;
}
