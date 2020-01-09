#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  

// X-Axis legth
#define X_SIZE 75
// path relative from userhome
#define filepath ".battery_plot"

/*
	Draw a line of length X_SIZE
*/
void print_seperation_line(){
	for(int i=0; i<X_SIZE-1; i++){
		printf("-");
	}
	printf("\n");
}

void main(){
	// Open file
	chdir(getenv("HOME"));
	FILE* file = fopen(filepath, "r");
	if(file == NULL){
		printf("ERROR: No such file: ~/%s\n", filepath);
		return;
	}


	// Create space for graph
	char plot[20][X_SIZE+1];
	int x_axis = 0;
	
	
	// Initialize graph with " "
	for(int a = 0; a<20; a++){
		for(int i=0; i<X_SIZE; i++){
			plot[a][i] = ' ';
		}
		plot[a][X_SIZE] = '\0';
	}
	
	
	// Plot file content in graph
	int current = 0;
	while(fscanf(file, "%d", &current) != EOF){
		for(int i = 0; i<20; i++){
			//5% battery-percentage steps
			if(current >= 100 - i*5){
				plot[i][x_axis] = '*';
				break;
			}
		}
		x_axis ++;
		if(x_axis >=X_SIZE) break;
	}
	
	
	// Output
	printf("\n");
	printf("100%% ");
	print_seperation_line();
	for(int i=0; i<20; i++){
		printf("|  %s\n", plot[i]);
	}
	printf("0%% --");
	print_seperation_line();
	printf("\n");
}
