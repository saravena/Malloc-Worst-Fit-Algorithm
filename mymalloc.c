/*************************************************************
* Project:   A Custom malloc(): Worst-Fit Algorithm          *
* Name:      Sabrina Aravena                                 *
* Due :      Novemeber 6, 2016                               *
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

typedef struct node {
  struct node *next;
  struct node *prev;
  void *heap_ptr;
  int amount;
  int check;
} Node;

Node *head;
Node *tail;
Node *curr;
Node *temp_use;
Node *temp_free;

void *my_worstfit_malloc(int size) {
  int worst_size = 0; /* tracker for the worst size in linked list */

  /* If first Node in list is empty */
  if (head == NULL) {
    head = sbrk(sizeof(Node));
    /* assign tail/curr to head because only one Node exists */
    tail = head;
    curr = head;
    /* update size and flag that Node is used */
    head -> next = NULL;
    head -> prev = NULL;
    head -> amount = size;
    head -> check = 1;
    head -> heap_ptr = sbrk(size);
    return head -> heap_ptr;

  } else {
    /* Go through every Node in list to find the best worst fit */
    curr = head;
    while (curr -> next != NULL) {
      //printf("\nenter here\n");
      if (curr -> check == 0) {
        if ((curr -> amount) > worst_size) {
          worst_size = curr -> amount;      /* Store the worst size for future use in special cases */
          temp_use = curr;   /* Store the address of current node of the worst size for use in special cases */
        }
      }
      curr = curr -> next;
    } /* end while */

    /* If the worst size cannot fit size being passed in */
    if (worst_size < size) {
      curr -> next = sbrk(sizeof(Node));
      /* reassign tail to new node*/
      tail = curr -> next;
      /* update next/prev, flag, and size */
      tail -> next = NULL;
      tail -> prev = curr;
      tail -> amount = size;
      tail -> check = 1;
      tail -> heap_ptr = sbrk(size);
      return tail -> heap_ptr;
    }
    /* If the worst size is equal to size being passed in and size of node */
    if (worst_size == size) {
      curr = temp_use;
      curr -> check = 1;
      // allocate space
      curr -> heap_ptr = sbrk(size);
      return curr -> heap_ptr;
    }
    /* If the worst size is larger than size being passed in */
    /* THIS DOES NOT WORK A SECOND TIME */
    if (worst_size > size && worst_size > (size + sizeof(Node))) {
      Node *temp_splt;
      int temp = worst_size;

      temp_use -> check = 1;
      temp_use -> amount = size;

      temp_splt = temp_use + sizeof(Node) + size;
      temp_splt -> check = 0;
      temp_splt -> prev = temp_use;
      temp_splt -> next = temp_use -> next;
      temp_splt -> amount = (temp - size - sizeof(Node));
      temp_use -> next = temp_splt;
      return temp_use -> heap_ptr;
    }
  }
} /* end my_worstfit_malloc(int) */

void my_free(void *ptr) {
  temp_free = (ptr - sizeof(Node));
  temp_free -> check = 0;
  /* check if first node is the only that exists */
  if (temp_free == head && temp_free -> next == NULL) {
    sbrk(0 - (head -> amount + sizeof(Node)));
    head = NULL;
    return;
  /* if node next to ptr are used on both left and right side */
} else if (temp_free -> next -> check == 1 && temp_free -> prev -> check == 1) {
    return;
  /* if node next to ptr is free on right*/
} else if (temp_free -> next -> check == 0 && temp_free -> next != NULL) {
    temp_free -> amount = temp_free -> next -> amount + sizeof(Node);
    if (temp_free -> next -> next != tail) {
      temp_free -> next = temp_free -> next -> next;
      (temp_free -> next) -> prev = temp_free;
    } else {
      temp_free -> next = temp_free -> next -> next;
      tail = temp_free -> next;
      tail -> prev = temp_free;
    }
    return;
  /* if node next to ptr is free on left */
} else if (temp_free -> prev -> check == 0) {
  temp_free -> amount = temp_free -> prev -> amount + sizeof(Node);
  if (temp_free -> prev -> prev != head) {
    temp_free -> prev = temp_free -> prev -> prev;
    (temp_free -> prev) -> next = temp_free;
  } else {
    temp_free -> prev = temp_free -> prev -> prev;
    head = temp_free -> prev;
    head -> prev = temp_free;
  }
  return;
  /* if both sides are free */
} else if (temp_free -> next -> check == 0 && temp_free -> prev -> check == 0) {
    temp_free -> amount == temp_free -> next -> amount + temp_free -> prev -> amount + (2*sizeof(Node));
    if (temp_free -> next == tail) {
      tail = temp_free;
    } else if (temp_free -> prev == head) {
      head = temp_free;
    } else if (temp_free -> prev == head && temp_free -> next == tail) {
      head = temp_free;
      tail = head;
      head -> next = NULL;
      head -> prev = NULL;
    } else {
      temp_free -> prev = temp_free -> prev -> prev;
      temp_free -> next = temp_free -> next -> next;
    }
    return;
    /* if head needs to be free */
    /* SEGMENTATION FAULT */
  } else if (temp_free == head) {
    if (head -> next -> check == 0) {
      temp_free -> amount = temp_free -> next -> amount + sizeof(Node);
      //sbrk(0 - (temp_free -> amount + sizeof(Node)));
      head = temp_free -> next -> next;
    } else {
      //sbrk(0 - (head -> amount + sizeof(Node)));
      head = temp_free -> next;
    }
    return;
    /* if tail needs to be free */
    /* SEGMENTATION FAULT */
  } else if (temp_free == tail) {
    if (tail -> prev -> check == 0) {
      temp_free -> amount = temp_free -> prev -> amount + sizeof(Node);
      //sbrk(0 - (temp_free -> amount + sizeof(Node)));
      tail = temp_free -> prev -> prev;
    } else {
      //sbrk(0 - (head -> amount + sizeof(Node)));
      tail = temp_free -> prev;
    }
    return;
  } else {
    return;
  }
} /* end my_free(void) */


/* prints linked list */
void printList() {
    printf("List: ");
    if(head == NULL) {
        printf("Head is null. The list does not exist.\n");
        return;
    }
    Node *curr = head;
    while(curr -> next != NULL) {
        if(curr -> heap_ptr == NULL)
          printf("\tF(%d)\t", curr -> amount);
        else
          printf("\tX(%d)\t", curr -> amount);
        curr = curr -> next;
    }
    if(curr -> heap_ptr == NULL)
      printf("\tF(%d)\t",curr -> amount);
    else
      printf("\tX(%d)\t", curr-> amount);
    printf("\n");
} /* end printList() */
