#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

// path relative from userhome
#define filepath ".battery_plot"

/*
	Draw a line of length X_SIZE
*/
void print_seperation_line(int length){
	for(int i=0; i<length; i++){
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
	
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    int WINSIZE_ROW = w.ws_row-3; //two lines for seperation, one for new shell-line
    int WINSIZE_COL = w.ws_col;


	// Create space for graph
	char plot[WINSIZE_ROW][WINSIZE_COL];
	
	
	// Initialize graph with " "
	for(int a = 0; a<WINSIZE_ROW; a++){
		for(int i=0; i<WINSIZE_COL-1; i++){
			plot[a][i] = ' ';
		}
		plot[a][WINSIZE_COL-1] = '\0';
	}
	
	
	// Plot file content in graph
	int current = 0;
	int x_axis = 0;
	while(fscanf(file, "%d", &current) != EOF){
		for(int i = 0; i < WINSIZE_ROW; i++){
			if(current >= 100 - i * (100.0 / WINSIZE_ROW)){
				plot[i][x_axis] = '*';
				break;
			}
		}
		x_axis ++;
		if(x_axis >= WINSIZE_COL) break;
	}
	
	
	// Output
	printf("100%% ");
	print_seperation_line(WINSIZE_COL - 5);
	for(int i=0; i<WINSIZE_ROW; i++){
		printf(" %s\n", plot[i]);
	}
	printf("0%% ");
	print_seperation_line(WINSIZE_COL - 3);
}
