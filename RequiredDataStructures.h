#define IPRange 60			//192.168.1.IPRange
#define IPSize 15
#define timeout 500
#define TotalRoutes 8
#define destinationHost "192.168.1.100"  // Destination IP Address
#define sourceHost "192.168.1.1"         // Source IP Address
#define selectionQtd 4
#define lastDestinationOc 100
#define lastSourceOc 1
#define total_packets 20000
#define avg

typedef struct router{                   // Creating structure Router
	char ip [IPSize];
	struct router *nextRtd;
	int nextTime;
	double pack_rcvd;
	char lastBinOc [9];
	double fitness;
}router;

typedef struct route{                    // Creating structure Route
	router *firstRouter;
	int routeTime;
	double packets;
	double fitnessSum;
	int n_routers;
}route;

void removeRepeated (route *way[],int *cntr){
	int i;
	for (i=0 ; i<TotalRoutes ; i++){
		router *iterator = way[i]->firstRouter->nextRtd;
		router *comparator = iterator->nextRtd;
		while (iterator->nextRtd != NULL){
			while (comparator->nextRtd != NULL){
				if (strcmp (comparator->ip, iterator->ip) == 0){
					router *remover = way[i]->firstRouter->nextRtd;
					while (remover->nextRtd != comparator){
						remover = remover->nextRtd;
						(*cntr)++;
					}
					remover->nextRtd = comparator->nextRtd;
					free (comparator);
				}
				comparator = comparator->nextRtd;
			}
			iterator = iterator->nextRtd;
			comparator = iterator->nextRtd;
		}
	}
}

router* createRouter (char ip [], int lastIntOc){
	router *no = (router*)malloc(sizeof(router));

	char lastCharOc [9];
	itoa (lastIntOc, lastCharOc, 2);

	strcpy (no->ip, ip);
	no->nextRtd = NULL;
	no->fitness = 0.0;
	no->nextTime = rand() % timeout + 20;
	no->pack_rcvd = 1 - (float)(rand() % 200) / 10000;
	strcpy (no->lastBinOc, lastCharOc);
	return no;
}

route* initializeRoute (){
	route *way = (route*)malloc(sizeof(route));			//allocating space in memory to linked list
	router *rtd = createRouter(sourceHost, lastSourceOc); //creating the first router with the origin-IP
	way->firstRouter = rtd;
	way->routeTime = 0;								//route time initialized
	way->fitnessSum = 0.0;
	way->n_routers = 0;
	way->packets = total_packets;
	return way;											//first router return
}

void addRouter (route *way, char ip [], int lastIntOc,int *cntr){ // function to add a router to a route
	router *iterator = way->firstRouter;
	router *aux = createRouter(ip, lastIntOc);

	while (iterator->nextRtd != NULL){
		iterator = iterator->nextRtd;
		(*cntr)++;
	}
	iterator->nextRtd = aux;
}

int detectRepeated (route *way, char ip[],int *cntr){     // Function to detect a repeated router in a given route

	router *iterator = way->firstRouter;
	while (iterator->nextRtd != NULL){
		if (strcmp (iterator->ip, ip) == 0){
			return 0;
		}
		iterator = iterator->nextRtd;
		(*cntr)++;
	}
	if (strcmp (iterator->ip, ip) == 0){
			return 0;
	}
	return -1;
}


route* mountRoute (int *cntr){
	route *way = initializeRoute();						//initialize the route

	int i=0;
	/* Randomize the routers between the source and the destination */
	for (i=0 ; i<rand() % IPRange + 3 ; i++){
		char lastOc[3];
		int lastIntOc = rand() % IPRange + 3;
		sprintf(lastOc, "%d", lastIntOc);
		char ip[IPSize];
		strcpy (ip, "192.168.1.");
		strcat (ip, lastOc);

		if (detectRepeated (way, ip,cntr) == -1){ 	 //If already exist a router with the same IP, doesn't insert
			addRouter (way, ip, lastIntOc,cntr);
			way->n_routers++;
		}
        (*cntr)++;
	}

	/* Localizing the last random router, and linking the effective destination in the end route */
	router *aux = way->firstRouter;

	while (aux->nextRtd != NULL){
		aux = aux->nextRtd;
		(*cntr)++;
	}

	// adding destination to the end
	if (aux->nextRtd == NULL){
		router *last = createRouter (destinationHost, lastDestinationOc);
		last->nextTime = -1;
		aux->nextRtd = last;
	}

	aux = way->firstRouter;

	while (aux->nextTime != -1){                                 //	Calculate of route total time
		way->routeTime = way->routeTime + aux->nextTime;
		way->packets = way->packets * aux->pack_rcvd;
		//printf("%f\n", way->packets);
		aux = aux->nextRtd;
		(*cntr)++;
	}

	return way;
}

route* initialize (int *cntr){
	route *way;
	way = mountRoute(cntr);
	return way;
}

void show (route *way[],int *stop_cntr,double *cur){

	int i=0;
	int Average_time=0;
	double Average_fitness=0;
	float Average_Pktloss=0;
	int best_route = -1;
	int best_route_time=1e9;
	double best_route_packLoss = 100;
	double best_route_fitness = -10000;
	for (i=0 ; i<TotalRoutes ; i++){
		printf ("\nRoute %d\n\n", i+1);

		router *aux = way[i]->firstRouter;

		while (aux != NULL){
			printf ("IP: %s - Latency to next router: %dms - Last octet binary: %s - Fitness Jump: %f\n", aux->ip, aux->nextTime, aux->lastBinOc, aux->fitness);
			aux = aux->nextRtd;
		}

		float n = 100 - (way[i]->packets*100)/total_packets;
		printf ("Total Time: %dms\n", way[i]->routeTime);
		printf ("Packet Lost Percentage: %f\n", n);
		printf ("Route Fitness: %f\n\n", way[i]->fitnessSum);
		printf ("\n");

		Average_time+=way[i]->routeTime;
		Average_fitness+=(way[i]->fitnessSum);
		Average_Pktloss+=n;

		if(way[i]->fitnessSum > best_route_fitness) {
			best_route = i;
			best_route_time=way[i]->routeTime;
			best_route_fitness = way[i]->fitnessSum;
			best_route_packLoss = 100 - way[i]->packets * 100/total_packets;
		}

	}
    printf("Current Generation Analysis :\n\n");
	printf ("Best Route: %d\n", best_route + 1);
	printf ("Best Route Fitness: %f\n", best_route_fitness);
	printf ("Best Route Time: %dms\n",best_route_time);
	printf ("Best Route Packet Loss: %f\n\n", best_route_packLoss);

	printf ("Average Route Time of Generation: %dms\n",Average_time/TotalRoutes);
	printf ("Average Packetloss of Generation: %f\n",Average_Pktloss/TotalRoutes);
	printf ("Average Fitness of Generation: %f\n\n\n",Average_fitness/TotalRoutes);

	if((*cur) != (Average_fitness/TotalRoutes))
        (*stop_cntr)=0;
    else
        (*stop_cntr)++;

    (*cur)=Average_fitness/TotalRoutes;
}

void update_route_time_total (route *way[], int *cntr){    // Function to update the total route time for each route in the current Generation
	int i;
	for (i=0 ; i<TotalRoutes ; i++){
		router *iterator = way[i]->firstRouter;
		way[i]->routeTime = 0;
		way[i]->packets = total_packets;
		while (iterator->nextRtd != NULL){
			way[i]->routeTime = way[i]->routeTime + iterator->nextTime;
			way[i]->packets = way[i]->packets * iterator->pack_rcvd;
			iterator = iterator->nextRtd;
			(*cntr)++;
		}
	}
}

