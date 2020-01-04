#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>

int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$6SsUGf4Cq7/Oooym9WWQN3VKeo2lynKV9gXVyEG4HvYy1UFRx.XAye89TLp/OTcW7cGpf9UlU0F.cK/S9CfZn1",
  "$6$KB$BnOJ7N1FAfJEUjwbecr9dk3lZFbrvc0XenvCyQebIefk5xcLST4qwSQw0OkkP9QzHJHtRNyLdGiXlii0Yk08N/",
  "$6$KB$UiyPyWfoHkUq3bGKWlH39QfkjiXP7V.ldbfaZ6lm.21mF9KQS/oxcI.E4.hwumrRKi.3KdeQ870VsoOdfC1GN0",
  "$6$KB$HK.9mb7mAX5Q7r6eTRn9jZHPLuHoNxLJ27mGV2gk7kv8rpKwNshAWblZ1FkZ07ue3iJrcRZ5tXbw7L82Z2Ujm0"
};


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}



void thread(char *encrypted_passwords){
  pthread_t T1,T2;

  void *kernel_function_1();
  void *kernel_function_2();

  pthread_create(&T1, NULL, kernel_function_1, (void *)encrypted_passwords);
  pthread_create(&T2, NULL, kernel_function_2, (void *)encrypted_passwords);
 
  pthread_join(T1, NULL);
  pthread_join(T2, NULL);
}

void *kernel_function_1(char *salt_and_encrypted){
  int ro, ni, sh;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(ro='A'; ro<='M'; ro++){
    for(ni='A'; ni<='Z'; ni++){
      for(sh=0; sh<=99; sh++){
        sprintf(plain, "%c%c%02d", ro, ni, sh);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

void *kernel_function_2(char *salt_and_encrypted){
  int sh, ah, hi;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(sh='N'; sh<='Z'; sh++){
    for(ah='A'; ah<='Z'; ah++){
      for(hi=0; hi<=99; hi++){
        sprintf(plain, "%c%c%02d", sh, ah, hi);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
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



int main(int argc, char *argv[]){
  int i;
 
 struct timespec start, finish;  
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  for(i=0;i<n_passwords;i<i++) {
    thread(encrypted_passwords[i]);
  }
 
 
 
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9));
  return 0;
}
