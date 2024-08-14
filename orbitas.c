#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<omp.h>

#define CORPOS 2
#define DIMENSOES 3

#define MAX_MASSA 1
#define MIN_MASSA 1

#define MAX_POS_INI 10000

#define MAX_VEL_INI 0
#define MIN_VEL_INI 0

#define G 1
#define PASSO 0.1
#define TEMPO 100

typedef struct{

  double massa;
  double posicao[DIMENSOES];
  double velocidade[DIMENSOES];
  double aceleracao[DIMENSOES];

} Corpo;

typedef struct{

  double comp[DIMENSOES];

} Vetor;

Corpo Aleatorizador(int i){

  Corpo a;
  int r_massa = MAX_MASSA - MIN_MASSA;
  int r_vel = MAX_VEL_INI - MIN_VEL_INI;

  srand(time(NULL)*(1+i)*100);

  if(r_massa != 0) a.massa = MIN_MASSA + rand() % r_massa;
  if(r_massa == 0) a.massa = MAX_MASSA;

  for(int i2 = 0; i2 < DIMENSOES; i2++){

    a.posicao[i2] = (rand() % (2*MAX_POS_INI)) - MAX_POS_INI;

  }

  for(int i2 = 0; i2 < DIMENSOES; i2++){

    if(r_vel != 0) a.velocidade[i2] = MIN_VEL_INI + rand() % r_vel;
    if(r_vel == 0) a.velocidade[i2] = 0;

  }

  for(int i2 = 0; i2 < DIMENSOES; i2++){

    a.aceleracao[i2] = 0;

  }

  return a;

}

Corpo Calcular_Aceleracao(Corpo a[], int c){

  double d[CORPOS];
  double mod[CORPOS];
  double soma;
  double soma_vet[DIMENSOES];
  Vetor vetor[CORPOS];

  for(int i1 = 0; i1 < CORPOS; i1++){

    soma = 0;

    for(int i2 = 0; i2 < DIMENSOES; i2++){

      soma = soma + pow((a[c].posicao[i2] - a[i1].posicao[i2]), 2);

    }
    
    d[i1] = pow(soma, (1.0/2));

    mod[i1] = -1 * G * (a[i1].massa / pow(d[i1], 2));
    if(d[i1] == 0) mod[i1] = 0;
    
    for(int i2 = 0; i2 < DIMENSOES; i2++){

      vetor[i1].comp[i2] = (a[c].posicao[i2] - a[i1].posicao[i2]) * mod[i1] / d[i1];
      if(d[i1] == 0) vetor[i1].comp[i2] = 0;
      
      soma_vet[i2] = soma_vet[i2] + vetor[i1].comp[i2];

    }

  }
  
  for(int i = 0; i < DIMENSOES; i++){

    a[c].aceleracao[i] = soma_vet[i];

  }

  return a[c];

}

Corpo Calcular_Velocidade(Corpo a){

  for(int i = 0; i < DIMENSOES; i++){

    a.velocidade[i] = a.velocidade[i] + a.aceleracao[i] * PASSO;

  }

  return a;
  
}

Corpo Calcular_Posicao(Corpo a){

  for(int i = 0; i < DIMENSOES; i++){

    a.posicao[i] = a.posicao[i] + a.velocidade[i] * PASSO;

  }

  return a;

}

void Visualizar_Corpos(Corpo a[]){

  for(int i = 0; i < CORPOS; i++){

    printf("%16.6f |", a[i].massa);

    for(int i2 = 0; i2 < DIMENSOES; i2++){

      printf(" %16.6f ", a[i].posicao[i2]);

    }

    printf("|");

    for(int i2 = 0; i2 < DIMENSOES; i2++){

      printf(" %16.6f ", a[i].velocidade[i2]);

    }

    printf("|");

    for(int i2 = 0; i2 < DIMENSOES; i2++){

      printf(" %16.6f ", a[i].aceleracao[i2]);

    }

    printf("\n");

  }  
  
  printf("\n\n");

}

int main(){

  Corpo planetas[CORPOS];
  double cont = 99;

  for(int i = 0; i < CORPOS; i++){

    planetas[i] = Aleatorizador(i);

  }
  
  for(float t = 0; t < TEMPO; t = t + PASSO){

    for(int i = 0; i < CORPOS; i++){

      planetas[i] = Calcular_Aceleracao(planetas, i);

      planetas[i] = Calcular_Velocidade(planetas[i]);

      planetas[i] = Calcular_Posicao(planetas[i]);

    }

    cont++;
    
    if(cont == 100){

      Visualizar_Corpos(planetas);
      cont = 0;

    }

  }

}
