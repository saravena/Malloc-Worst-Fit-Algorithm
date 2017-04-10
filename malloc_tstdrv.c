
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mymalloc.c"

#define malloc my_worstfit_malloc
#define free my_free

int main() {
  /* comment and uncomment in order to test specific cases */
  /* change free input as well */

  
  /* test first malloc node */
  int *a = my_worstfit_malloc(8);
  *a = 2;
  printf("\n%i", *a);
  printf("\n%p\n", a);
  printList();

  /* test free first node case */
  // my_free(a);
  // printList();

  /* test second malloc case */
  int *b = my_worstfit_malloc(10);
  *b = 3;
  printf("\n%i", *b);
  printf("\n%p\n", b);
  printList();

  int *c = my_worstfit_malloc(12);
  *c = 10;
  printf("\n%i", *c);
  printf("\n%p\n", c);
  printList();

  /* test second case of free */
  // printf("\n\n");
  // my_free(b);
  // printf("\n%i", *b);
  // printf("\n%p\n", b);
  // printList();

  /* check third malloc case */
  int *d = my_worstfit_malloc(20);
  *d = 6;
  printf("\n%d\n", *d);
  printf("\n%p\n", d);
  printList();

  int *e = my_worstfit_malloc(18);
  *e = 6;
  printf("\n%d\n", *e);
  printf("\n%p\n", e);
  printList();

  int *f = my_worstfit_malloc(2);
  *f = 6;
  printf("\n%d\n", *f);
  printf("\n%p\n", f);
  printList();

  int *g = my_worstfit_malloc(21);
  *g = 6;
  printf("\n%d\n", *g);
  printf("\n%p\n", g);
  printList();



  // my_free(d);
  // printList();
  return 0;
}
