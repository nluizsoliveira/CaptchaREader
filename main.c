#include<stdio.h>
#include<stdlib.h>
#include<string.h>



int main (){
    int debug = 0; //Se =1, permite impressão de debugs 
    char* captcha_file_name = malloc(20*sizeof(char)); //armazena nome do arquivo de captcha digitado pelo usuario
    char* captcha_file_path = malloc(40*sizeof(char)); //armazena o caminho de tal arquivo
    char** masks_paths = malloc(10*sizeof(char*)); //Armazena o caminho dos arquivos das máscaras
            for(int i = 0; i < 10; i++){
                masks_paths[i] = malloc(40*sizeof(char));
            }
    int ** captcha; //Matriz que carrega o captcha lido no arquivo na heap, permitindo fechá-lo
    int mask_size; //Área de máscara 
    int *** masks; //Matriz tridmensional [k][i][j], onde cada k armazena uma máscara [i][j]
    int * ones_per_mask = calloc(10, sizeof(int)); //Número de 1's em cada máscara


    scanf("%s", captcha_file_name);
    //Imprime o nome do arquivo no caminho correto
    sprintf(captcha_file_path, "./captcha/%s", captcha_file_name);

    if(debug)printf("%s", captcha_file_path);
    //Gera os caminhos corretos para as máscaras
    for(int i = 0 ; i < 10; i++){
        sprintf(masks_paths[i], "./mascaras/%d.pgm", i);
        if(debug)printf("%s\n", masks_paths[i]);
    }

    FILE* captcha_file = fopen(captcha_file_path, "r");
    int captcha_i;
    int captcha_j;
    fscanf(captcha_file, "%*s %d %d %*d",&captcha_j, &captcha_i); //Le o cabeçalho e armazena tamanho da matriz do captcha nas variáveis captcha_i e captcha_j

    //Aloca matriz do captcha dinamicamente
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
    
    //Tenta remover um pouco de Salt, igualando o pixel central a seus vizinhos caso todos possuam o mesmo valor, permitindo utilizar uma 
    //similaridade maior
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
    //cada masks[k] possui uma matriz mask[k][i][j] que armazena uma máscara. 
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

    //Testa as máscaras vertical por vertical horizontalmente
    for(int x = 0; x < captcha_j - mask_j; x++){
        //Testa as máscaras primeiramente na vertical
        for(int y = 0; y < captcha_i - mask_i; y++){
            // Testa máscara por máscara em uma região do tamanho de uma máscara.
            //A posição da máscara é controlada por x e y, que são incrementados acima. 
            for(int k = 0; k < mask_k; k++){
                int coincident_cells = 0; 
                double similarity = 0;
                for(int i = 0; i < mask_i; i++){
                    for(int j = 0; j < mask_j; j++){
                        if(captcha[i+y][j+x] == masks[k][i][j]){
                                coincident_cells ++;
                        }
                    }
                    
                    
                }

                //Similaridade escolhida: Células coincidentes na máscara desenhada sobre o captcha / número de celulas de uma máscara
                    similarity = (double) coincident_cells / mask_size;
                    if(similarity > 0.9){ //Valor alto de similaridade heuristicamente

                        printf("%d", k); //Imprime o valor caso seja similar, e shifta o quadrante 30 pixels para a direita e para o topo, reiniciando a busca
                        if(((x+30) < (captcha_j - mask_j))){
                            x = x+30; 
                        }
                        else{
                            x = captcha_j;
                        }
                        y = 0; 
                        k = 10; 

                    }
            }
        }
    }

    //Libera todas as estruturas alocadas
    free(captcha_file_name);
    free(captcha_file_path);
    free(ones_per_mask);

    for(int i = 0; i < 10; i++){
        free(masks_paths[i]);
    }

    free(masks_paths);

    for(int i = 0; i < captcha_i; i++){
        free(captcha[i]);
    }

    free(captcha);
    for(int k = 0; k < mask_k; k++){
        for(int i = 0; i < mask_i; i++){
            free(masks[k][i]);
        }
        free(masks[k]);
    }
    free(masks);

    

}