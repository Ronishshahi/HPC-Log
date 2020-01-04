#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>

int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$.OnsM0.pEomFoalYh1Tz0da3BPcVeBs6fn3fn6Aq8XMjLMc5aImRqL9hBnjFpCVLigSq9dYwAelFBufipopxY1",
  "$6$KB$Q5Giqxk18QBwn.TQ6ppHIR22LhLutR0I5/HeWN.nWO0oC3tp/uBras7iQuxz88mYdM7oIlf3uyq4jvwaGx56A1",
  "$6$KB$wS9zCwAyXqJPYHs.a7GClFMcRxm2hkKC6td5rpfeAYjo44Wfq0Ih1knvpZ.ad7PDBG2JhSmFCRp.iYSswWsho1",
  "$6$KB$9hElopWPDMu9Pa8.XeEHPXP1j5Dp4wcm5aPwYfhYJBGhiSPgpTL81DOF9tjeabL6PJYHtsY/mfD/t5P24V9S9."
};



void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}


void crack(char *salt_and_encrypted){
  int ro, ni,ha, sh;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far$6$KB$HK.9mb7mAX5Q7r6eTRn9jZHPLuHoNxLJ27mGV2gk7kv8rpKwNshAWblZ1FkZ07ue3iJrcRZ5tXbw7L82Z2Ujm0

  substr(salt, salt_and_encrypted, 0, 6);

  for(ro='A'; ro<='Z'; ro++){
  for(ha='A'; ha<='Z'; ha++){
    for(ni='A'; ni<='Z'; ni++){
      for(sh=0; sh<=99; sh++){
        sprintf(plain, "%c%c%c%02d", ro, ni, ha, sh); 
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
  }
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish, 
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
struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
 
  int i;
  
  for(i=0;i<n_passwords;i<i++) {
    crack(encrypted_passwords[i]);
  }

clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, 
         (time_elapsed/1.0e9)); 

  return 0;
}
