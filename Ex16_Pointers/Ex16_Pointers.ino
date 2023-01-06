#include <stdio.h>
#include <LibPrintf.h>

// Ex. 16.2
int a[5] = {9,2,42,5,8};
int *pointer = &a[0];
char buff[50];
char buff2[50];

// Ex. 16.1 and 16.3
int val1 = 1;
int val2 = 10;
int *ptr_val1 = &val1;
int *ptr_val2 = &val2;

void setup() {
  Serial.begin(9600);
}

void loop() {

  // Ex. 16.1
  (*ptr_val1)++;
  Serial.println(val1);
  
  /*
  // Ex. 16.2
  sprintf(buff, "Address of pointer is %x\n", pointer);
  Serial.print(buff);
  sprintf(buff2,"Value of pointer is %d\n\n",*pointer);
  Serial.print(buff2);
  pointer++;;
  delay(3000);

  // Ex. 16.3
  Serial.println(val1);
  Serial.println(val2);
  swap(ptr_val1, ptr_val2);
  */
  delay(2000);
}

void swap(int *ptr1, int *ptr2) {
 int TMP = *ptr1;
 *ptr1 = *ptr2;
 *ptr2 = TMP;
}