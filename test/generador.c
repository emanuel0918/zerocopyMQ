#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int cadenaEsNumero (char **cadena);
int cadenaANumero (char **cadena);
long cadenaANumeroL (char **cadena);
int scan (char **cadena);
void numeroABinario (char **cadena, long n);
int main(int argc, char *argv[]){
    int i;
    int aleatorio1,aleatorio2;
    int opc;
    int num;
  char *cadena, *s_opc, *s_n;
  FILE *archivo;
  do
    {
      printf ("Generador de archivos\n");
      printf ("1)Generar de manera manual\n");
      printf ("2)Generar de manera aleatoria\n");
      printf ("3)Salir\n");
      scan (&s_opc);
    }
  while (!(cadenaEsNumero (&s_opc)));
  opc = cadenaANumero (&s_opc);
  if(opc==1){
      scan(&cadena);
  }
  if (opc == 2)
    {
	  printf ("Ingrese longitud del texto:\n");
	  do
	    {
	      scan (&s_n);
	    }
	  while (!(cadenaEsNumero (&s_n)));
	  num = cadenaANumeroL (&s_n);
      cadena=(char*)malloc(sizeof(char)*num);
	  srand (time (NULL));
      for(i=0;i<num;i++){
	  aleatorio1 =(int) (rand () % (9));
            if(aleatorio1==2){
                aleatorio2=0;
            }else{
                aleatorio2=(int) (rand () % (255));
            }
          cadena[i]=(char)aleatorio2;
      }
	//numero aleatorio entre 1 y 255

	  //printf ("Subconjunto L generado aleatoriamente hasta el numero %ld\n",num);
	}
  system ("rm prueba.txt");
  system ("echo > prueba.txt");
  archivo = fopen ("prueba.txt", "w");
  fprintf (archivo, "%s", cadena);
  fclose (archivo);

    return 0;
}


void
numeroABinario (char **cadena, long n)
{
  int i, c;
  char *rev;
  i = 0;
  *cadena = (char *) malloc (sizeof (char));
  rev = (char *) malloc (sizeof (char));
  if (n == 0)
    {
      (*cadena)[i] = '0';
      i++;
      *cadena = (char *) realloc (*cadena, sizeof (char) * (i + 1));
      rev = (char *) realloc (rev, sizeof (char) * (i + 1));
    }
  while (n > 0)
    {
      (*cadena)[i] = (n % 2) + 48;
      n /= 2;
      i++;
      *cadena = (char *) realloc (*cadena, sizeof (char) * (i + 1));
      rev = (char *) realloc (rev, sizeof (char) * (i + 1));
    }
  i--;
  c = 0;
  while (i >= 0)
    {
      rev[c] = (*cadena)[i];
      c++;
      i--;
    }
  rev[c] = '\0';
  i = 0;
  while (rev[i] != '\0')
    {
      (*cadena)[i] = rev[i];
      i++;
    }
  (*cadena)[i] = '\0';
}

int cadenaANumero (char **cadena)
{
  int d = 0, l = 0, i, j, b;
  while ((*cadena)[l] != '\0')
    {
      l++;
    }
  for (i = 0; i < l; i++)
    {
      b = 1;
      for (j = 1; j < (l - i); j++)
	{
	  b *= 10;
	}
      d += ((*cadena)[i] - 48) * b;
    }
  return d;
}
long cadenaANumeroL (char **cadena)
{
  int  l = 0, i, j, b;
  long d=0;
  while ((*cadena)[l] != '\0')
    {
      l++;
    }
  for (i = 0; i < l; i++)
    {
      b = 1;
      for (j = 1; j < (l - i); j++)
	{
	  b *= 10;
	}
      d += (long)(((*cadena)[i] - 48) * b);
    }
  return d;
}

int cadenaEsNumero (char **cadena)
{
  int numero = 1;
  int i = 0;
  while ((*cadena)[i] != '\0')
    {
      if (!((*cadena)[i] >= 48 && (*cadena)[i] <= 57))
	{
	  numero = 0;
	  break;
	}
      i++;
    }
  if (i < 1)
    {
      numero = 0;
    }
  return numero;
}

int scan (char **cadena)
{
  char c;
  int i = 0;
  *cadena = (char *) malloc (sizeof (char));
  setbuf (stdin, NULL);
  while (c != '\n')
    {
      c = getc (stdin);
      if (c != '\n')
	{
	  (*cadena)[i] = c;
	  i++;
	  *cadena = (char *) realloc (*cadena, sizeof (char) * (i + 1));
	}
    }
  (*cadena)[i] = '\0';
  return i;
}