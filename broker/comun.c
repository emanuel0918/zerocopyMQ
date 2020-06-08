#define _BSD_SOURCE
#include "comun.h"


int obtenerSocket(){
	int s;
	struct sockaddr_in dir;
	struct hostent *host_info;
	if ((s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("error creando socket");
		return -1;
	}
	host_info=gethostbyname(getenv("BROKER_HOST"));
	dir.sin_addr=*(struct in_addr *)host_info->h_addr;
	dir.sin_port=htons(atoi(getenv("BROKER_PORT")));
	dir.sin_family=PF_INET;
	if (connect(s, (struct sockaddr *)&dir, sizeof(dir)) < 0) {
		perror("error en connect");
		close(s);
		return -1;
	}
	return s;

}

char * reverseString(char *s, int l){
int i;
 char * r=(char*)malloc((l+2)*sizeof(char));
 for( i=0;i<l;i++){
  r[(l-(i+1))]=s[i];
 }
 r[l]='\0';
 return r;
}
char rand_char(){
	time_t t;
	srand((unsigned)time(&t));
	return ((char)(rand()%255));	
}
char * intToString(long n){
 char * s;
 s=(char*)malloc(sizeof(char));
 int i=0;
 s[i]=(char)((n%10)+48);
 while(n/10>0){
  i++;
  s=(char*) realloc(s,(i+2)*sizeof(char));
  n/=10;
  s[i]=(char)((n%10)+48);
 }
 s=reverseString(s,(i+1));
 s[(i+1)]='\0';
 return s;
}
int stringToInt(char *s){
 int d=0;
 int i=0;
 int j=0;
 int l=0;
 int diez=1;
 int n=0;
 char c=0;
 while((c=s[i])!='\0'){
  l++;
  i++;
 }
 i=0;
 while((c=s[i])!='\0'){
  n=c-48;
  for(j=0,diez=1;j<(l-(i+1));j++){
   diez*=10;
  }
  d+=n*diez;
  i++;
 }
 return d;
}

char *
scan ()
{
  char * cadena;
  char c;
  int i = 0;
  cadena = (char *) malloc (sizeof (char));
  setbuf (stdin, NULL);
  while (c != '\n')
    {
      c = getc (stdin);
      if (c != '\n')
	{
	  cadena[i] = c;
	  i++;
	  cadena = (char *) realloc (cadena, sizeof (char) * (i + 1));
	}
    }
  cadena[i] = '\0';
  return cadena;
}
char* subString (const char* input, int offset, int len, char* dest)
{
  int input_len = strlen (input);

  if (offset + len > input_len)
  {
     return NULL;
  }

  strncpy (dest, input + offset, len);
  return dest;
}
