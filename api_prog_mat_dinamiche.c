#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h> 
#define MAX_CAR_NUM 512
#define MAT_ROW 256

typedef struct {
    int **edges;
}mat;

FILE *file;
char carattereInFile[2];
char distance_string[10];
char num_car_string[10];
char range_string[10];

int* station;
mat* vehicles;
size_t mat_row = MAT_ROW;
size_t array_size = 1;
size_t station_size = 1;
int distance;
int num_car;
int range;
int start;
int end;


// Incrementa le righe della matrice di MAX_CAR_NUM (incremento lo spazio utilizzato di 1048576 [byte] = 1.04 [MB] )
void resize_mat(){
    int temp = mat_row;
    mat_row += MAT_ROW;
    vehicles->edges = realloc( vehicles->edges, (mat_row)*sizeof(int*) );
    for(int i = temp; i < mat_row; i++){
        vehicles->edges[i] = calloc(sizeof(int), MAX_CAR_NUM);
    }
}

mat *create_mat(){
    mat *m = malloc(sizeof(*m));
    //allocate matrix
    m->edges = calloc(sizeof(int*), MAT_ROW);

    for(int i=0; i < MAT_ROW; i++){
        m->edges[i] = calloc(sizeof(int), MAX_CAR_NUM);
    }
    return m;
}

void print_mat(){
    for(int i=0; i < station_size-1; i++){
        printf("%d : ", i);
        for(int j=0; j < station_size; j++){
            printf("%d ", vehicles->edges[i][j]);
            if(vehicles->edges[i][j] == -1){
                break;
            }
        }
        printf("\n");
    }
}

void print_array(){
    for(int i=0; i< station_size; i++){
        printf("%d -> ", station[i]);
    }
}

void shift_array_from_index(size_t index){ 
    
    for(int i = (station_size - 1); i>index; i--){
        if(i == 0){
            break;
        }
        station[i] = station[i-1];
    }

}

void shift_array_to_index(int index){
    for(int i = index; i<station_size; i++){
        station[i] = station[i+1];
    }
}

void shift_mat_from_index(int index){

    // sposto in basso tutti i valori di una riga (dalla riga finale alla riga index)
    for(int i = (station_size - 1); i > index; i--){
        for(int j = 0; j < MAX_CAR_NUM; j++){
            
            if(i != 0){
                vehicles->edges[i][j] = vehicles->edges[i-1][j];

                if(vehicles->edges[i-1][j] == -1){
                    vehicles->edges[i-1][j] = 0;
                    break;
                }
                vehicles->edges[i-1][j] = 0;
            }
            
        }
    }
}

void shift_mat_to_index(size_t index){

    if(index == (station_size - 1)){
        vehicles->edges[index][0] = -1;
        return;
    }

    // sposto in alto tutti i valori di una riga (dalla riga index alla riga finale)
    for(int i = index; i < (station_size -1); i++){

        for(int j = 0; j < MAX_CAR_NUM; j++){

            if(i != station_size){
                vehicles->edges[i][j] = vehicles->edges[i+1][j];
                if(vehicles->edges[i+1][j] == -1){
                    vehicles->edges[i+1][j] = 0;
                    break;
                }
                vehicles->edges[i+1][j] = 0;
            }
            
        }
    }

}

void aggiungi_stazione(){

	memset(distance_string, 0, sizeof(char[10]));
    while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(distance_string, carattereInFile);
        }
    }
    distance = atoi(distance_string);
	
	memset(num_car_string, 0, sizeof(char[10]));
	while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(num_car_string, carattereInFile);
        }
    }
    num_car = atoi(num_car_string);

    
    for(int i = 0; i < station_size; i++){
        
        if(station[i] < distance && i == (station_size-1)){
            
            if(station_size == array_size){
                array_size++;
                station = realloc(station, (array_size)*sizeof(int));                   
            }
            station_size++;
            station[i+1] = distance;

            if(station_size > mat_row){
                resize_mat();
            }

            //aggiungo auto alla matrice 2D di auto
            for(int j = 0; j < num_car; j++){

                memset(range_string, 0, sizeof(char[10]));
                while(fgets(carattereInFile, 2, file) != NULL){
                    if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
                        break;
                    }else{
                        strcat(range_string, carattereInFile);
                    }
                }
                range = atoi(range_string);

                vehicles->edges[i][j] = range;
            }
            vehicles->edges[i][num_car] = -1;
            break;

        }
        
        //aggiungo stazione alla lista di stazioni
        if(station[i] > distance){

            if(station_size == array_size){
                array_size++;
                station = realloc(station, (array_size)*sizeof(int));                   
            }
            station_size++;
            shift_array_from_index(i);
            station[i] = distance;

            if(station_size > mat_row){
                resize_mat();
            }

            shift_mat_from_index(i);
            //aggiungo auto alla matrice 2D di auto
            for(int j = 0; j < num_car; j++){

                memset(distance_string, 0, sizeof(char[10]));
                while(fgets(carattereInFile, 2, file) != NULL){
                    if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
                       
                        break;
                    }else{
                        strcat(distance_string, carattereInFile);
                    }
                }
                range = atoi(distance_string);

                vehicles->edges[i][j] = range;
            }

            vehicles->edges[i][num_car] = -1;
            break;

        }
        if(station[i] == distance){
            break;
        }
    }

}

void demolisci_stazione(){
    
    memset(distance_string, 0, sizeof(char[10]));
    while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(distance_string, carattereInFile);
        }
    }
    distance = atoi(distance_string);

    for(int i=0; i<station_size; i++){
        if(station[i] == distance){
            shift_array_to_index(i);
            shift_mat_to_index(i);
            station_size--;
            break;
        }
    }

}

void aggiungi_auto(){
    memset(distance_string, 0, sizeof(char[10]));
    while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(distance_string, carattereInFile);
        }
    }
    distance = atoi(distance_string);
	
	memset(range_string, 0, sizeof(char[10]));
	while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(range_string, carattereInFile);
        }
    }
    range = atoi(range_string);

    for(int i = 0; i < station_size; i++){
        if(station[i] ==  distance){
            for(int j = 0; j < MAX_CAR_NUM; j++){
                if(vehicles->edges[i][j] == -1){
                    vehicles->edges[i][j] = range;
                    vehicles->edges[i][j+1] = -1;
                    break;   
                }
            }
            break;
        }
    }

}

void rottama_auto(){
    memset(distance_string, 0, sizeof(char[10]));
    while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(distance_string, carattereInFile);
        }
    }
    distance = atoi(distance_string);
	
	memset(range_string, 0, sizeof(char[10]));
	while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(range_string, carattereInFile);
        }
    }
    range = atoi(range_string);

    for(int i = 0; i < station_size; i++){
        if(station[i] ==  distance){
            for(int j = 0; j < MAX_CAR_NUM; j++){
                if(vehicles->edges[i][j] == -1){
                    break;
                }
                if(vehicles->edges[i][j] == range){
                    for(int k = j; k < MAX_CAR_NUM; k++){
                        vehicles->edges[i][k] = vehicles->edges[i][k+1];
                        if(vehicles->edges[i][k] == -1){
                            break;
                        }
                    }
                    break;
                }

            }
            break;
        }
    }

}

void pianifica_percorso(){
    memset(distance_string, 0, sizeof(char[10]));
    while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(distance_string, carattereInFile);
        }
    }
    start = atoi(distance_string);

    memset(distance_string, 0, sizeof(char[10]));
    while(fgets(carattereInFile, 2, file) != NULL){
        if(strcmp(carattereInFile, " ") == 0 || strcmp(carattereInFile, "\n") == 0){
            break;
        }else{
            strcat(distance_string, carattereInFile);
        }
    }
    end = atoi(distance_string);
}

int main(int argc, char *argv[]){

    station = malloc(sizeof(int*));
    station[0] = -1;
    vehicles = create_mat();
    char fileInput[2];

    file = fopen("open_80.txt", "r");
    if(NULL == file){
        perror("error when opening file!");
        return -1;
    }	

	while(fgets(fileInput, 2, file) != NULL) {	
		
		if(strcmp(fileInput , "a") == 0){

            do{
                if(fgets(fileInput, 2, file) == NULL){
                    break;
                }
            }while(strcmp(fileInput, "-") != 0);
			if(fgets(fileInput, 2, file) != NULL);
			
            if(strcmp(fileInput, "s") == 0){
            	
                do{
                    if(fgets(fileInput, 2, file) == NULL){
                    break;
                    }
                }while(strcmp(fileInput, " ") != 0);

                aggiungi_stazione();
                
            }else{
            	
            	do{
                    if(fgets(fileInput, 2, file) == NULL){
                    break;
                    }
                }while(strcmp(fileInput, " ") != 0);
                aggiungi_auto();

            }
            
        }

        if(strcmp(fileInput , "d") == 0){
            do{
                if(fgets(fileInput, 2, file) == NULL){
                    break;
                }
            }while(strcmp(fileInput, " ") != 0);
            demolisci_stazione();
        
        }

        if(strcmp(fileInput , "r") == 0){
            do{
                if(fgets(fileInput, 2, file) == NULL){
                    break;
                }
            }while(strcmp(fileInput, " ") != 0);
            rottama_auto();
            
        }

        if(strcmp(fileInput , "p") == 0){
            do{
                if(fgets(fileInput, 2, file) == NULL){
                    break;
                }
            }while(strcmp(fileInput, " ") != 0);
            //pianifica_percorso();
		}

    }

    //print_array();
    print_mat();

    fclose(file);
    return 0;
}