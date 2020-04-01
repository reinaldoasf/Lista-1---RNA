#include "gap_common.h"
#include "gap_cluster.h"
#define CORE_NUMBER   (8)
#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include "omp_gap8.h"

/*#define CORE_NUMBER (1)*/

typedef struct L1_structure0{
float global_result;
float a;
float b;
float n;
int num_cores;
}L1_structure0;
L1_structure0 romp_global_structure0;
typedef struct L1_structure1{
float global_result;
float a;
float b;
float n;
int num_cores;
}L1_structure1;
L1_structure1 romp_global_structure1;
int x_flagsingle_x=0;
int romp_cores=CORE_NUMBER;
int cores_num[1];
void generic_function0(void* gen_var0);
void caller(void* arg){
int x = (int)arg;
if(x ==0)return generic_function0((void*)x);
}


void Master_Entry(void *arg) {
    CLUSTER_CoresFork(caller, arg);
}
/* File:    omp_trap2a.c

 * Purpose: Estimate definite integral (or area under curve) using trapezoidal 

 *          rule.  This version uses a hand-coded reduction after the function

 *          call.

 *

 * Input:   a, b, n

 * Output:  estimate of integral from a to b of f(x)

 *          using n trapezoids.

 *

 * Compile: gcc -g -Wall -fopenmp -o omp_trap2a omp_trap2a.c -lm

 * Usage:   ./omp_trap2a <number of threads>

 *

 * Notes:   

 *   1.  The function f(x) is hardwired.

 *   2.  This version assumes that n is evenly divisible by the 

 *       number of threads

 * IPP:  Section 5.4 (p. 222)

 */







/*------------------------------------------------------------------

 * Function:    f

 * Purpose:     Compute value of function to be integrated

 * Input arg:   x

 * Return val:  f(x)

 */

double f(double x) 

{

    double return_val;



    return_val = x*x;

    return return_val;

}  /* f */



/*------------------------------------------------------------------

 * Function:    Local_trap

 * Purpose:     Use trapezoidal rule to estimate part of a definite 

 *              integral

 * Input args:  

 *    a: left endpoint

 *    b: right endpoint

 *    n: number of trapezoids

 * Return val:  estimate of integral from local_a to local_b

 *

 * Note:        return value should be added in to an OpenMP

 *              reduction variable to get estimate of entire

 *              integral

 */

double Local_trap(double a, double b, int n)

{

    double  h, x, my_result;

    double  local_a, local_b;

    int  i, local_n;

    int my_rank = omp_get_thread_num();

    int thread_count = omp_get_num_threads();



    h = (b-a)/n; 

    local_n = n/thread_count;  

    local_a = a + my_rank*local_n*h; 

    local_b = local_a + local_n*h; 

    my_result = (f(local_a) + f(local_b))/2.0; 

    for (i = 1; i <= local_n-1; i++) {

     x = local_a + i*h;

     my_result += f(x);

    }

    my_result = my_result*h; 



    return my_result;

}  /* Trap */



int main() 

{

    double  global_result;        /* Store result in global_result */

    double  a=0, b=1000;                 /* Left and right endpoints      */

    int     n=4000;                    /* Total number of trapezoids    */

    int     thread_count=8;



    global_result = 0.0;

    int qqrcoisa = 10;

cores_num[0]=thread_count;

romp_cores=thread_count;

romp_global_structure0.global_result=global_result;

romp_global_structure0.a=a;

romp_global_structure0.b=b;

romp_global_structure0.n=n;

romp_global_structure0.global_result=global_result;

romp_global_structure0.a=a;

romp_global_structure0.b=b;

romp_global_structure0.n=n;

CLUSTER_Start(0,thread_count);
CLUSTER_SendTask(0, Master_Entry, (void *)0, 0);
CLUSTER_Wait(0);
CLUSTER_Stop(0);
x_flagsingle_x=0;
romp_cores=CORE_NUMBER;
global_result=romp_global_structure0.global_result;

a=romp_global_structure0.a;

b=romp_global_structure0.b;

n=romp_global_structure0.n;

    printf("With n = %d trapezoids, our estimate\n", n);

    printf("of the integral from %d to %d = %d\n", 

            (int) a, (int) b, (int) global_result);

    exit(0);

}  /* main */

void generic_function0(void* gen_var0){
    {

        double my_result = 0.0;


        my_result += Local_trap(romp_global_structure0.a, romp_global_structure0.b, romp_global_structure0.n);


EU_MutexLock(0);
            romp_global_structure0.global_result += my_result;

EU_MutexUnlock(0);

    }


}

