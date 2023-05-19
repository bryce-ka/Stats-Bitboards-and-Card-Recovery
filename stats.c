/* Function producing mean and variance of input values.
 *
 * Time spent: 3 hours
 *
 * Authors: Paige Johnson, Bryce Anthony
*/
#include "io.h"
#include <stdio.h>
void computeStats(){
printf("Please enter a number: ");
float sum = 0;
float num = 1;
float count = 0;
float avg = 0;
float var = 0;
float squaretotal = 0;

int numRead = scanf("%f", &num);

while(num > 0){
    if(numRead == 0){
    printf("\nSorry, that is not a valid number - input ignored");
    flushInputBuffer();
    // numRead = scanf("%f", &num);
    }
    else if(numRead == 1){
    sum += num;
    squaretotal = squaretotal + (num * num);
    //printf("square total: %g\n", squaretotal);
    count = count + 1;
    }
    printf("\nPlease enter a number: ");
    numRead = scanf("%f", &num);
}

avg = sum/count;
var = (squaretotal / count ) - (avg * avg);
if(count == 0){
    avg = 0.00;
    var = 0.00;
}
printf("Mean: %.2f, Variance: %.2f\n", avg, var);
}

int main(){
    printf("test1: \n");
    computeStats();
    return 0;
}
