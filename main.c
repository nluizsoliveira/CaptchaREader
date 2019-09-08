#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main (){
    
    int debug = 0; //variável de controle de funções de debug. 0 esconde printfs e 1 os mostra. 
    char fName [40];
    char fPath [40];
    char fMaskName[10][6];
    char fMaskNamePath[10][20];
    int captcha_cols, captcha_rows;
    int num_PGMs;
    int mask_cols, mask_rows;
    
    
    //leitura do nome do arquivo e atribuição de seu caminho relativo à string 
    scanf("%s", fName);
    sprintf(fPath, "./captcha/%s", fName);

    if(debug){
        printf("Captcha Name: %s\n", fName);
        printf("Captcha Path: %s\n", fPath);
    }

    //Criação de matriz com os caminhos dos arquivos das máscaras.
    //fMaskNamePath[0] armazena "./mascaras/0.pgm" e assim sucessivamente
    for(int i = 0; i < 10; i++){
        sprintf(fMaskName[i], "%d%s", i, ".pgm");
        sprintf(fMaskNamePath[i], "./mascaras/%s", fMaskName[i]);
        if(debug){
            printf("Mask Path: %s\n",fMaskNamePath[i]);
        }
    }
    
    //Abertura do arquivo que contém o captcha e leitura do número de colunas e linhas da matriz de 0's e 1's
    FILE* fCaptcha;
    fCaptcha = fopen(fPath, "r");
    fscanf(fCaptcha, "%*s %d %d %*d",&captcha_cols,&captcha_rows); //O tipo do arquivo e a variação são ignorados
    if(debug) printf("%s possui: %d colunas e %d linhas \n", fPath, captcha_cols,captcha_rows);
    
    //Leitura da matriz de 0's e 1's do catpcha
    int captcha[captcha_cols][captcha_rows];
    for(int i = 0; i < captcha_rows; i++){
        for(int j = 0; j < captcha_cols; j++){
            fscanf(fCaptcha, "%d", &captcha[i][j]);
            if(debug)printf("%d ", captcha[i][j]);
        }
        if(debug) printf("\n");
    }

    //O conteúdo importante de captcha já foi alocado na memória, deve ser fechada. 
    fclose(fCaptcha);


    num_PGMs = 11; 
    FILE* fPGM [num_PGMs];
    mask_cols = 30;
    mask_rows = 50;

    int masks [num_PGMs][mask_cols][mask_rows];

    for(int k = 0; k < num_PGMs-1; k++){
        if(debug) printf("Mascara numero %d -------Mascara numero %d -------Mascara numero %d -------\n\n\n",k,k,k);
        fPGM[k] = fopen(fMaskNamePath[k], "r");
        fscanf(fPGM[k], "%*s %*d %*d %*d");
        for(int i = 0; i < mask_rows; i++){
            for(int j = 0; j < mask_cols; j++){
                fscanf(fPGM[k], "%d", &masks[k][i][j]);
                if(debug)printf("%d ", masks[k][i][j]);
            }
            if(debug) printf("\n");
        }
        fclose(fPGM[k]);
    }

    int similarity; 
    for(int i = 0; i < captcha_rows; i++){
        for(int j = 0; j < captcha_cols; j++){
            
        }
    }
}