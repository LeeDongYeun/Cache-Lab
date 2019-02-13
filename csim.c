// student id : 20160444
// name : ÀÌµ¿¿¬ 
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include "cachelab.h"

int vagmt;
int s;
int E;
int b;

	
int hits=0;
int misses=0;
int evicts=0;

int time=0; // for eviction

char *trace;// filename
int c; // for getopt

typedef struct{
	int last_use;
	int v;
	int tag;
}c_1;

typedef c_1 *line;
typedef line *set;

set cache;

void doit(unsigned long long address){
	int tag = address >> (s+b);
	int set_index = (address>>b) - (tag<<s);
	int i=0;
	int T_evict=0; // to store time of last used cache
	int Index=0; // to store index of last used cache
	int ForEviction = 1, ForHit = 0;
	
	
	time++;
	T_evict = time;
	
	for(i = 0; i < E; i++){
		
		//to find last-used cache
		if(cache[set_index][i].last_use<T_evict){
				T_evict = cache[set_index][i].last_use;
				Index = i;
			}
		
		//case1 hit
		if(cache[set_index][i].v){
			if(cache[set_index][i].tag == tag){
				ForHit = 1;
				break; 
			}
		}
		//case2 miss
		else{
			Index = i;
			ForEviction = 0;
			
			break;
		}
	}
	
	//case1 hit
	if(ForHit){
		if(vagmt)
			printf(" hit\n");
		hits++;
		cache[set_index][i].last_use = time;
	}
	//case2 miss
	else{
		misses++;
		if(vagmt)
			printf(" miss ");
		
		//case3 evict
		if(ForEviction){
			if(vagmt)
				printf(" eviction\n");
			evicts++;
		
		}
		cache[set_index][Index].v = 1;
		cache[set_index][Index].tag = tag;
		cache[set_index][Index].last_use = time;
	}
}


void sEbtSet(int argc, char *argv[]){
	while((c = getopt(argc, argv, "hvs:E:b:t:")) != -1){
		switch(c){
			case 'h':
				break;
			case 'v':
				vagmt = 1;
				break;
			case 's':
				s = atoi(optarg);
				break;
			case 'E':
				E = atoi(optarg);
				break;
			case 'b':
				b = atoi(optarg);
				break;
			case 't':
				trace = optarg;
				break;
			default:
				exit(1);
		}
	}
}

int main(int argc, char **argv)
{
	FILE *file;
	int i=0, j=0;
	
	char op;
	unsigned long long address;
	int size;
	
	
	sEbtSet(argc,argv);
	//printf("%d %d %d %d %s\n", vagmt,s,E,b,trace);
	

	//making cache
	cache = (line*)malloc(sizeof(line)*(1<<s));
	
	for(i = 0; i < (1<<s) ; i++){
		cache[i] = (c_1*)malloc(sizeof(c_1)*E);
		for(j = 0; j < E; j++){
			cache[i][j].last_use = 0;
			cache[i][j].v = 0;
			cache[i][j].tag = 0;
			
		}
	}
	
	
	//file opening
	file = fopen(trace, "r");
	if(file != NULL){
		while(fscanf(file, " %c %llx,%d", &op,&address,&size) == 3){
			//printf("%c %llx %d\n",op,address,size);
			switch(op){
				case 'I':
					
					break;
				case 'L':
					
					doit(address);
					break;
				case 'S':
					
					doit(address);
					break;
				case 'M':
					
					doit(address);
					doit(address);
					break;
				default:
					break;
			}
		}
	}
	/*
	for(i=0;i<(1<<s);i++){
		for(j=0;j<E;j++){
			printf("%d %d %d %llx\n",cache[i][j].v, cache[i][j].last_use, cache[i][j].tag, cache[i][j].address);
		}
	}
	*/
	
    printSummary(hits, misses, evicts);
    fclose(file);
    /*
    for(i = 0; i < S; i++){
    	free(cache[i]);
	}
	free(cache);
    */
    return 0;
}
