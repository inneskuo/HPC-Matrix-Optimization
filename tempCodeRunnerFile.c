#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
char name[20];
strcpy(name, "Julian");
printf("Hello, %s\n", name);
int* p = malloc(sizeof(int) * 5);
if (p != NULL) {
p[0] = 100;
printf("Value: %d\n", p[0]);
free(p);
}
return 0;
}
