#include <sys/time.h>



#include "ngspice/ngspice.h"
#include "ngspice/cktdefs.h"
#include "ngspice/devdefs.h"


#include "ngspice/sperror.h"

#include "time_bsim.h"

extern long number_loops;
extern char *timing_outfile;

/*
specify two command line options. 
-f, --timingfile specify the output file where timing is saved
-l, --loops specify the number of loops to run
*/
void time_bsim(CKTcircuit *ckt){
    int i;
    for (i = 0; i < DEVmaxnum; i++) {
        if (DEVices[i] && DEVices[i]->DEVload && ckt->CKThead[i]) {
            if( strcmp(DEVices[i]->DEVpublic.name, "BSIM4v7")){
                FILE *fp = fopen(timing_outfile, "a");
                if (fp == NULL){
                    printf("Error opening file %s\n", timing_outfile);
                    return;
                }

                if (number_loops <= 0)
                    number_loops = 1000;
                int j;
                struct timeval start_t, end_t;
                gettimeofday(&start_t, NULL);
                for (j=0; j < number_loops; j++){
                    DEVices[i]->DEVload (ckt->CKThead[i], ckt);
                }
                gettimeofday(&end_t, NULL);
                double elapsed = (double) (end_t.tv_usec - start_t.tv_usec)/1000000 +
                    (double) (end_t.tv_sec - start_t.tv_sec);
                fprintf(fp, "%d, %8g\n", -1, elapsed);
                printf("Elapsed %8g\n", elapsed);
            }
        }
    }
    
}

