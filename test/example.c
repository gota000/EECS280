#include <stdio.h>
int main()
{
int a=45; // declare and initialize an integer
int n = 10;
float b[n]; // declare a vector of 10 real numbers
b[0]=3.4;
b[1]=5.6;
b[2]=10.5;
b[3]=119.2;
b[4]=47.2;
b[5]=90.1;
b[6]=71.1;
b[7]=14.7;
b[8]=37.3;
b[9]=1.2;

double sum = 0.0;

for (int i = 0; i < n; i++){
    sum = sum + b[i];
}

// print numbers:
printf("The sum is: %f\n", sum);
printf("The average is: %f\n", sum / n);

return 0;
}