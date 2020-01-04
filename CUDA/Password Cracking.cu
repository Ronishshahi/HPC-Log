#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>

__device__ int is_a_match(char *attempt) {
  char password1[] = "FT81";
  char password2[] = "CV07";
  char password3[] = "IR03";
  char password4[] = "SA31";

  char *r = attempt;
  char *o = attempt;
  char *n = attempt;
  char *h = attempt;
  char *pwd1 = password1;
  char *pwd2 = password2;
  char *pwd3 = password3;
  char *pwd4 = password4;

  while(*r == *pwd1) {
   if(*r == '\0')
    {
    printf("Found password: %s\n",password1);
      break;
    }

    r++;
    pwd1++;
  }
    
  while(*o == *pwd2) {
   if(*o == '\0')
    {
    printf("Found password: %s\n",password2);
      break;
}

    o++;
    pwd2++;
  }

  while(*n == *pwd3) {
   if(*n == '\0')
    {
    printf("Found password: %s\n",password3);
      break;
    }

    n++;
    pwd3++;
  }

  while(*h == *pwd4) {
   if(*h == '\0')
    {
    printf("Found password: %s\n",password4);
      return 1;
    }

    h++;
    pwd4++;
  }
  return 0;

}

__global__ void  kernel() {
char s,z;
 
  char password[5];
  password[4] = '\0';

int i = blockIdx.x+65;
int j = threadIdx.x+65;
char firstValue = i;
char secondValue = j;
    
password[0] = firstValue;
password[1] = secondValue;
    for(s='0'; s<='9'; s++){
      for(z='0'; z<='9'; z++){
            password[2] = s;
            password[3] = z;
          if(is_a_match(password)) {
        //printf("Success");
          }
             else {
         //printf("tried: %s\n", password);          
            }
          }
        } 
      
}
int time_difference(struct timespec *start,
                    struct timespec *finish,
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main() {

  struct  timespec start, finish;
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9));
  return 0;
}




