/*

  Searching the best Route using Distance Vector which use
  BELLMAN FORD ALGORITHM with parameters hop count and latency

  Time Complexity in this case is O(VE)
  As this is a mesh network with E=O(V*V)
  Therefore overall time complexity is = O(V*V*V)

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "RequiredDataStructures.h"
#include "geneticAlgo.h"


int cost[100][100];  // cost matrix contains the latency between a pair of routers
int dist[100]; // dist refers to route time

const int edges = 20000;

struct nodes{      // nodes indicate my pair of hops and latency from one to other
  int from;//hop
  int next;//hop
  int latency;
};

int main()
{
  int i,j,k,cnt=1;

  for(i=1;i<=IPRange+2;i++) // IPRange indicate the number of routers between source and destination
      dist[i]=1e9;          // initializing total route time from a hop to source as infinite

  struct nodes nodes[edges];

  /* Populating cost matrix Begins */
  // Making sure that source and destination are not connected directly

  cost[1][1]=0;
  nodes[1].from=1;
  nodes[1].next=1;
  nodes[1].latency=cost[1][1];
  cnt++;

  for(int i=2;i<=IPRange+1;i++)
    {
      cost[1][i]=rand()%timeout + 20;
      cost[i][1]=cost[1][i];

      nodes[cnt].from=1;
      nodes[cnt].next=i;
      nodes[cnt].latency=cost[1][i];
      cnt++;

      nodes[cnt].from=i;
      nodes[cnt].next=1;
      nodes[cnt].latency=cost[i][1];
      cnt++;
    }

    for(int i=2;i<=IPRange+2;i++)
    {
        cost[i][i]=0;
        nodes[cnt].from=i;
        nodes[cnt].next=i;
        nodes[cnt].latency=cost[i][i];
        cnt++;

        for(int j=i+1;j<=IPRange+2;j++)
        {
            cost[i][j]=rand()%timeout + 20;
            cost[j][i]=cost[i][j];

            nodes[cnt].from=i;
            nodes[cnt].next=j;
            nodes[cnt].latency=cost[i][j];
            cnt++;

            nodes[cnt].from=j;
            nodes[cnt].next=i;
            nodes[cnt].latency=cost[j][i];
            cnt++;
        }

    }
   /* Populating cost matrix Ends */

    dist[1]=0; // Making Route time from source to source 0


    /* Applying Bellman Ford Algorithm*/
    int exe=0;
    for(i=1;i<=IPRange+2-1;i++)
    {
       int j=1;
       while(j>=1 && j<=cnt)
       {  exe++;
           if(dist[nodes[j].from]+ nodes[j].latency< dist[nodes[j].next])
           {
              dist[nodes[j].next]=dist[nodes[j].from]+nodes[j].latency;
           }
           j++;
       }
    }


    printf("Final distance(route time) from source to all other routers is :\n");

    for(i=2;i<=IPRange+1;i++)
        printf("from %d dist(route time) is %d\n",i,dist[i]);

    printf("\nNumber of instructions executed is : %d\n",exe);
    printf("Shortest path(route time) from source to destination : %d\n",dist[IPRange+2]);

    return 0;
}
