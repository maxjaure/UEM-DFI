#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Functions from maxb.h */

/* Find the mean of a list of numbers */
double mean(double a[], int size) {
  double mean=0.0;
  int i;
  for (i=0; i<size; i++) {
    mean += a[i];
  }
  mean = mean/size;
  return(mean);
}

/* Find the standard deviation of a list of numbers */
double sd(double a[], int size) {
  double sd=0, m;
  int i;
  m=mean(a,size);
  for (i=0; i<size; i++) {
    sd+=pow((a[i]-m),2.0);
  }
  sd=pow(sd/(size-1),0.5);
  return(sd);
}

/* Obtain the coefficients of the linear regression by using the method of least squares */
double *lm(double x[], double y[], int size) {
  int i;
  double a, b, *lm, mx, my, sdx;
  mx = mean(x,size);
  my = mean(y,size);
  b = 0;
  for (i=0;i<size;i++) {
    b += (x[i]-mx)*(y[i]-my);
  }
  sdx = sd(x,size);
  b /= (size-1)*sdx*sdx;
  a = my-b*mx;
  lm = malloc(2*sizeof(double));
  lm[0] = a;
  lm[1] = b;
  return(lm);
}

int main() {
  int o, i, n;
  double *coef, *x, *y, m, s;
  printf("Programa para calcular o seguinte:\n");
  printf("[1] média e desvio padrão de uma lista de números\n");
  printf("[2] regressão linear y=a+bx a partir de uma tabela de dados\n");
  printf("Qual cálculo quer realizar (1 ou 2)?\n");
  scanf("%d",&o);
  if (o==1) {
    printf("A lista tem quantos números?\n");
    scanf("%d",&n);
    x = malloc(n*sizeof(double));
    printf("Escreva os %d números separados por espaço ou um em cada linha:\n",n);
    for (i=0;i<n;i++) {
      scanf("%lf",&x[i]);
    }
    m = mean(x,n);
    s = sd(x,n);
    printf("Média: %lf\n",m);
    printf("Desvio padrão: %lf\n",s);
    free(x);
  }
  if (o==2) {
    printf("A tabela tem quantos pares de números (x, y)?\n");
    scanf("%d",&n);
    x = malloc(n*sizeof(double));
    y = malloc(n*sizeof(double));
    printf("Escreva os %d números correspondentes ao eixo das abscissas (x) separados por espaço ou um em cada linha:\n",n);
    for (i=0;i<n;i++) {
      scanf("%lf",&x[i]);
    }
    printf("Escreva os %d números correspondentes ao eixo das ordenadas (y) separados por espaço ou um em cada linha:\n",n);
    for (i=0;i<n;i++) {
      scanf("%lf",&y[i]);
    }
    coef = malloc(2*sizeof(double));
    coef = lm(x,y,n);
    printf("Coeficiente linear: %lf\n",coef[0]);
    printf("Coeficiente angular: %lf\n",coef[1]);
    free(x);
    free(y);
  }
  if (o!=1 && o!=2) {
    printf("Error!");
    exit(-1);
  }
  exit(0);
}
