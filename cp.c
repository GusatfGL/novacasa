#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

int* GenerateMatrix(int N, int E)
{
	int * pointer; // (0-0, 0-1... 0-N, 1-0 1-1, 1-N... N-N)
	// General formula: N * Source + Target
	pointer = (int*)malloc(N*N * sizeof(int));
	
	for (int i = 1; i < N; i++)
	{
		int sourceNode = rand() % i;
		int weight = 1 + rand() % 9;
		
		pointer[sourceNode * N + i] = weight;
	}

	int placedEdges = N-1;

	while (placedEdges < E)
	{
		int sourceNode = rand() % N;
		int weight = 1 + rand() % 9;
		int targetNode = rand() % N;

		while (targetNode == sourceNode || pointer[N*sourceNode +targetNode] != 0)
		{
			sourceNode = rand() % N;
			targetNode = rand() % N;
		}

		pointer[N*sourceNode + targetNode] = weight;
		placedEdges++;
	}


	return pointer;
}

void PrintMatrix(int* matrix, int N)
{
	for (int i = 0; i < N*N; i++)
	{
		if (i % N == 0)
		{
			printf("\n");
		}

		printf("%d, ", matrix[i]);
	}
}

int* FindShortestPath(int* matrix, int N)
{
	int * distance;
	distance = (int*)malloc(N* sizeof(int));

	// Assign every distance to infinity
	distance[0] = 0;
	for (int i = 1; i< N; i++)
	{
		distance[i] = INT_MAX;
	}

	for (int source = 0; source < N; source++)
	{
		for (int target = 0; target < N; target++)
		{
			if (matrix[source * N + target] == 0)
			{
				matrix[source * N + target] = INT_MAX;
			}
			
		}
	}

	
	// Here is the actual pathfinding
	for (int relax = 0; relax < N; relax++) // neccsry i think
	{
		for (int source = 0; source < N; source++)
		{
			for (int target = 0; target < N; target++)
			{
				if (matrix[N*source + target] != INT_MAX)
				{	
					if (distance[source] + matrix[source*N+target] < distance[target])
					{
						distance[target] = distance[source] + matrix[source*N+target];
					}
				}
			}
		}
	}
	return distance;
}

void PrintArray(int * data, int length)
{
	for (int i = 0; i< length; i++)
	{
		printf("Dist to %d has %d \n", i, data[i]);
	}
}

int main()
{
	srand (time(NULL)); // Initizialize random, only called once.
	printf("starting..");	
	int * graph = GenerateMatrix(10, 40);
	PrintMatrix(graph, 10);
	int * distance = FindShortestPath(graph, 10);
	printf("\n");
	PrintArray(distance, 10);
	graph = NULL; // Maybe unnecesssary. Used instead of free


	return 0;
}
