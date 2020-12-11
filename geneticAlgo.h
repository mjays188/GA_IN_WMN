void evaluateFitness (route *way[],int *cntr){       // Function to evaluate Fitness of routes
	int i;
	for (i=0 ; i<TotalRoutes ; i++){
		router *iterator = way[i]->firstRouter;
		way[i]->fitnessSum = 0;

		while (iterator->nextRtd != NULL){           // Updating the fitness jump for each router in the respective route
			iterator->fitness = 1.0 / iterator->nextTime;
			iterator = iterator->nextRtd;
			(*cntr)++;
		}
		way[i]->fitnessSum = 1.0 / (way[i]->n_routers * way[i]->routeTime * (1 - way[i]->packets/total_packets));
	}
}


void Do_Elitism (route *way[],int *cntr){           // Function to perform Elitism
	int i;
	for (i = 0; i < TotalRoutes-1; i++) {
		router *iterator = way[i]->firstRouter->nextRtd;
		router *faster = iterator;
		float smallerTime = iterator->nextTime * iterator->pack_rcvd;

		while (iterator->nextRtd != NULL){
			if (smallerTime > iterator->nextTime){
				smallerTime = iterator->nextTime * iterator->pack_rcvd;
				faster = iterator;
			}
			iterator = iterator->nextRtd;
			(*cntr)++;
		}

		iterator = way [i+1]->firstRouter->nextRtd;
		router *slower = iterator;
		float greaterTime = iterator->nextTime * iterator->pack_rcvd;

		while (iterator->nextRtd != NULL){
			if (greaterTime < iterator->nextTime){
				greaterTime = iterator->nextTime * iterator->pack_rcvd;
				slower = iterator;
			}
			iterator = iterator->nextRtd;
			(*cntr)++;
		}

		strcpy (slower->ip, faster->ip);
		slower->nextTime = faster->nextTime;
		slower->pack_rcvd = faster->pack_rcvd;
		strcpy (slower->lastBinOc, faster->lastBinOc);
		slower->fitness = faster->fitness;
	}
}


void Crosover (route *way[],int *cntr){          // Function to perform Crossover between pair of routes

	int routesSize [TotalRoutes], i;

	for (i=0 ; i<TotalRoutes ; i++){
		router *aux = way[i]->firstRouter;
		routesSize[i] = 0;
		while (aux!=NULL){
			routesSize[i]++;
			aux = aux->nextRtd;
			(*cntr)++;
		}
	}

	int smallerRoute = routesSize[0];

	for (i=0 ; i<TotalRoutes ; i++){
		if (smallerRoute>routesSize[i])
			smallerRoute = routesSize[i];

        (*cntr)++;
	}

	srand (time(0));
	int crossoved [TotalRoutes];		//control flag to know which routes was crossoved
	int method = rand() % 3;

	for (i=0 ; i<TotalRoutes; i++)
		{crossoved [i] = 0;
		 (*cntr)++;
		}

	for (i=0 ; i<TotalRoutes ; i++){
            (*cntr)++;
		if (method == 1){
			if (crossoved[i] == 0){
				int separationPoint = 1 + (rand() % smallerRoute);
				printf ("SEPARATION POINT %d - %d: %d\n", i+1, i+3, separationPoint);
				if (smallerRoute == separationPoint || separationPoint > smallerRoute)		// This way, the separation point never will be greater than the smaller route
					separationPoint = 1;													// And if be, the separation point will be after first router

				/* Crossover  */
				router *iteratorRoute1 = way[i]->firstRouter;
				router *iteratorRoute2 = way[i+2]->firstRouter;  // 1-3, 2-4, 5-7, 6-8

				int j;
				for (j=0 ; j<separationPoint-1 ; j++){
					iteratorRoute1 = iteratorRoute1->nextRtd;
					iteratorRoute2 = iteratorRoute2->nextRtd;
					(*cntr)++;
				}
				router *aux = createRouter ("0.0.0.0", 0);

				aux->nextRtd = iteratorRoute1->nextRtd;
				iteratorRoute1->nextRtd = iteratorRoute2->nextRtd;
				iteratorRoute2->nextRtd = aux->nextRtd;
                /* End of Crossover */
				crossoved[i] = 1;
				crossoved[i+2] = 1;
			}
		}

		if (method == 0){
			if (crossoved[i] == 0){
				int separationPoint = 1 + (rand() % smallerRoute);
				printf ("SEPARATION POINT %d - %d: %d\n", i+1, i+2, separationPoint);
				if (smallerRoute == separationPoint || separationPoint > smallerRoute)		// This way, the separation point never will be greater than the smaller route
					separationPoint = 1;													// And if be, the separation point will be after first router

				/* Crossover */
				router *iteratorRoute1 = way[i]->firstRouter;
				router *iteratorRoute2 = way[i+1]->firstRouter; // 1-2, 3-4, 5-6, 7-8

				int j;
				for (j=0 ; j<separationPoint-1 ; j++){
					iteratorRoute1 = iteratorRoute1->nextRtd;
					iteratorRoute2 = iteratorRoute2->nextRtd;
					(*cntr)++;
				}
				router *aux = createRouter ("0.0.0.0", 0);

				aux->nextRtd = iteratorRoute1->nextRtd;
				iteratorRoute1->nextRtd = iteratorRoute2->nextRtd;
				iteratorRoute2->nextRtd = aux->nextRtd;
				/* End of Crossover */
				crossoved[i] = 1;
				crossoved[i+1] = 1;
			}
		}

		if (method == 2){
			if (crossoved[i] == 0){
				int separationPoint = 1 + (rand() % smallerRoute);
				printf ("SEPARATION POINT %d - %d: %d\n", i+1, TotalRoutes-i, separationPoint);
				if (smallerRoute == separationPoint || separationPoint > smallerRoute)		// This way, the separation point never will be greater than the smaller route
					separationPoint = 1;													// And if be, the separation point will be after first router

				/* Crossover */
				router *iteratorRoute1 = way[i]->firstRouter;
				router *iteratorRoute2 = way[TotalRoutes-i-1]->firstRouter; // 1-8, 2-7, 3-6, 4-5

				int j;
				for (j=0 ; j<separationPoint-1 ; j++){
					iteratorRoute1 = iteratorRoute1->nextRtd;
					iteratorRoute2 = iteratorRoute2->nextRtd;
					(*cntr)++;
				}
				router *aux = createRouter ("0.0.0.0", 0);

				aux->nextRtd = iteratorRoute1->nextRtd;
				iteratorRoute1->nextRtd = iteratorRoute2->nextRtd;
				iteratorRoute2->nextRtd = aux->nextRtd;
				/* End of Crossover */
				crossoved[i] = 1;
				crossoved[TotalRoutes-i-1] = 1;
			}
		}

	}
	printf ("\n\n");
}
