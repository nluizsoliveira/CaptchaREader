# T3 Algoritmos 1 - Captcha

## Especificações

### Contexto

Os arquivos **PGM (Portable GrayMap)** podem ser preto e brancos, em escala de cinza ou coloridos. A primeira dupla de caracteres define de qual maneira a imagem será renderizada. 

P1 - PBM - Preto e Branco
P2 - PGM - Escalas de CInza
P3 - PPM - Colorido

Em seguida, são definidos **altura m** e **largura n** da imagem, o **valor máximo dos tons de cinza** e enfim o **valor de cada pixel**.

```
P2 //Imagem PGM - Greyscale
24 7 //Imagem 24 x 7
15 //Tons de cinza baseados em uma escala de 15 tons 
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  3  3  3  3  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15 15 15 15  0
0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0 15  0
0  3  3  3  0  0  0  7  7  7  0  0  0 11 11 11  0  0  0 15 15 15 15  0
0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0  0  0
0  3  0  0  0  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```

<span class = "duvida">Nas especificaçõees m e n parecem estar invertidos </span>

Nos captchas fornecidos, todos os captchas possuem <span class = "testes">m = k*46</span> e <span class = "testes"> n = 100 </span>, ou seja, <span class = "testes">100 de altura</span> e algum <span class = "testes">múltiplo de 46 de altura</span>, com k variando de 1 a 10 (46 a 460). Além disso, mesmo em formato PGM, <span class = "testes">todos possuem apenas 1 tom</span>. <span class = "duvida"> 

São fornecidas **mascaras** também em PGM. Todas as máscaras possuem <span class = "testes">m = 30</span> e <span class = "testes">n = 50</span>

<span class = "duvida">A situação acima pode mudar?</span>



### Entrada

Nome do arquivo .pgm
```captcha_6.pgm```

### Saída

Numero do Captcha
```13579```

### Processamento

#### Duvidas processamento

* <span class = "duvida">  É mais eficiente trabalhar a leitura e processamento diretamente no arquivo ou carregar os pgm's em alguma estrutura? </span>

* <span class = "duvida"> É preciso se livrar do salt? </span>
* <span class = "duvida"> Será levada em consideração a eficiência do algoritmo?</span>


#### Passo a Passo processamento

- Ler string com nome do .pgm com o captcha 
- Descobrir a localização do .pgm com o captcha (Na mesma pasta do .c ou em algum path especifico) <span class = "duvida">qual é a organização das pastas?</span>
- Atribuir a um ponteiro do tipo FILE o arquivo .pgm com o captcha no modo leitura  
  ```c
    FILE *captcha;

    char captchaPath[15];

    scanf("%s", captchaPath);

    /*  open the file for reading */

    captcha = fopen(captchaPath, "r");
    ```

    
    







```
<span class = "duvida"></span>
<span class = "testes"></span>
```

<style>
.duvida{
    color: red;
}

.testes{
    color: Fuchsia;
}
</style>
