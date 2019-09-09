#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main (){
    int debug = 0;
    char* captcha_file_name = malloc(20*sizeof(char));
    char* captcha_file_path = malloc(40*sizeof(char));
    char** masks_paths = malloc(10*sizeof(char*));
            for(int i = 0; i < 10; i++){
                masks_paths[i] = malloc(40*sizeof(char));
            }
    int ** captcha;
    int mask_size;
    int *** masks;
    int * ones_per_mask = calloc(10, sizeof(int));


    scanf("%s", captcha_file_name);

    sprintf(captcha_file_path, "./captcha/%s", captcha_file_name);

    if(debug)printf("%s", captcha_file_path);

    for(int i = 0 ; i < 10; i++){
        sprintf(masks_paths[i], "./mascaras/%d.pgm", i);
        if(debug)printf("%s\n", masks_paths[i]);
    }

    FILE* captcha_file = fopen(captcha_file_path, "r");
    int captcha_i;
    int captcha_j;
    fscanf(captcha_file, "%*s %d %d %*d",&captcha_j, &captcha_i);

    captcha = malloc(captcha_i*sizeof(int*));
    
    for(int i = 0; i < captcha_i; i++){
        captcha[i] = malloc(captcha_j*sizeof(int));
    }

    if(debug) printf("\n--------------------printing captcha before cleaning-------------------\n");
    for(int i = 0; i < captcha_i; i++){
        for(int j = 0; j < captcha_j; j++){
            fscanf(captcha_file, "%d", &captcha[i][j]);
            if(debug) printf("%d ", captcha[i][j]);
        }
        if(debug) printf("\n");
    }
    
    //Tenta remover poeira 

    if(debug) printf("\n--------------------printing captcha after cleaning-------------------\n");
    for(int i = 1; i < captcha_i-1; i++){
        for(int j = 1; j < captcha_j-1; j++){
            if(captcha[i+1][j] && captcha[i+1][j-1] && captcha[i+1][j+1] && captcha[i][j] && captcha[i][j-1] && captcha[i][j+1] && captcha[i-1][j] && captcha[i-1][j-1] && captcha[i-1][j+1]){
                captcha[i][j] = 1;
            }

            if(!captcha[i+1][j] && !captcha[i+1][j-1] && !captcha[i+1][j+1] && !captcha[i][j] && !captcha[i][j-1] && !captcha[i][j+1] && !captcha[i-1][j] && !captcha[i-1][j-1] && !captcha[i-1][j+1]){
                captcha[i][j] = 0;
            }
            if(debug) printf("%d ", captcha[i][j]);
        }
        if(debug)printf("\n");
    }

    fclose(captcha_file);

    //masks are all i = 50 j = 30,então o override de seus i's e j's não é problematico
    int mask_k = 10; 
    int mask_i = 50;
    int mask_j = 30; 
    mask_size = mask_i * mask_j;

    masks =  malloc(mask_k*sizeof(int**));

    for(int k = 0; k < mask_k; k++){
        masks[k] =  malloc(mask_i*sizeof(int*));

        for(int i = 0 ; i < mask_i; i++){
            masks[k][i] = malloc(mask_j*sizeof(int));
        }
    }

    for(int k = 0; k < mask_k; k++){
        if(debug) printf("\n------------Printing %d.pgm---------\n", k);
        FILE* mask_file = fopen(masks_paths[k], "r");
        fscanf(mask_file, "%*s %*d %*d %*d");

        for(int i = 0; i < mask_i; i++){
            for(int j = 0; j < mask_j; j++){
                fscanf(mask_file, "%d", &masks[k][i][j]);
                if(masks[k][i][j]) ones_per_mask[k]++;
                if(debug) printf("%d ", masks[k][i][j]);
            }
            if(debug) printf("\n");
        }
        if(debug) printf("\n-----------Finished printing %d.pgm. It has %d 1's-----------\n", k, ones_per_mask[k]);
    }

    for(int y = 0; y < captcha_i - mask_i; y++){
        for(int x = 0; x < captcha_j - mask_j; x++){
            for(int k = 0; k < mask_k; k++){
                int coincident_cells = 0; 
                double similarity = 0;
                for(int i = 0; i < mask_i; i++){
                    for(int j = 0; j < mask_j; j++){
                        if(captcha[i+y][j+x] == masks[k][i][j]){
                                coincident_cells ++;
                        }
                    }
                    similarity = (double) coincident_cells / mask_size;
                    if(similarity > 0.95) printf("%d", k);
                }
            }
        }
    }

}