#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

// path relative from userhome
#define filepath ".battery_plot"


void print_seperation_line(int length){
	for(int i=0; i<length; i++){
		printf("-");
	}
	printf("\n");
}

int countWords(char* filename){
	FILE* file = fopen(filename, "r");
	if(file == NULL){
		printf("ERROR: No such file: ~/%s\n", filepath);
		exit(-1);
	}
	int tmp;
	int words = 0;
	while(fscanf(file, "%d", &tmp) != EOF){
		words ++;
	}
	fclose(file);
	return words;
}

void main(){
	// Open file
	chdir(getenv("HOME"));
	int wordcount = countWords(filepath);
	FILE* file = fopen(filepath, "r");
	if(file == NULL){
		printf("ERROR: No such file: ~/%s\n", filepath);
		return;
	}
	
	
	
	// Dynamic windowsize
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int WINSIZE_ROW = w.ws_row-3; //two lines for seperation, one for new shell-line
    int WINSIZE_COL = w.ws_col;
    int skip_first_data = wordcount - (WINSIZE_COL-1);

	
	
	// Initialize graph with " "
	char plot[WINSIZE_ROW][WINSIZE_COL];
	for(int a = 0; a<WINSIZE_ROW; a++){
		for(int i=0; i<WINSIZE_COL-1; i++){
			plot[a][i] = ' ';
		}
		plot[a][WINSIZE_COL-1] = '\0';
	}
	
	
	
	
	// Skip old data
	int tmp;
	for(int i=0; i<skip_first_data; i++){
		fscanf(file, "%d", &tmp);
	}
	// Plot graph
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
	printf("\x1b[33m"); // Set color yellow
	for(int i=0; i<WINSIZE_ROW; i++){
		printf(" %s\n", plot[i]);
	}
	printf("\x1b[0m"); // Reset color
	printf("0%% ");
	print_seperation_line(WINSIZE_COL - 3);
	fclose(file);
}
