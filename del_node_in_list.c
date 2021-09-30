#include <stdio.h>
#include <error.h>

#include <stdlib.h>
struct Node {
        int data;
        struct Node* next;
};

int main()
{
        struct Node* head = NULL;
        struct Node* second = NULL;
        struct Node* third = NULL;
        struct Node* forth = NULL;
        struct Node* fifth = NULL;
        // allocate 3 nodes in the heap
        head = (struct Node*)malloc(sizeof(struct Node));
        second = (struct Node*)malloc(sizeof(struct Node));
        third = (struct Node*)malloc(sizeof(struct Node));
        forth = (struct Node*)malloc(sizeof(struct Node));
        fifth = (struct Node*)malloc(sizeof(struct Node));


        head->data = 1; // assign data in first node
        head->next = second; // Link first node with
        second->data = 2;
        third->data = 3; // assign data to third node
        third->next = forth;
        forth->data = 4; // assign data to third node
        forth->next = fifth;
        fifth->data = 5; // assign data to third node
        fifth->next = NULL;

        struct Node * tmp = head;
        while(tmp){
                printf("%d\t", tmp->data);   // 1 2 3 4 5
                tmp=tmp->next;
        }
        printf("\n");
        struct Node ** ptmp = &head;
        while(*ptmp){
                if((*ptmp)->data == 3){
                        *ptmp = (*ptmp)->next;
                }else {
                        ptmp = &((*ptmp)->next);
                }
        }
        tmp = head;
        while(tmp){
                printf("%d\t", tmp->data); // 1 2 4 5
                tmp=tmp->next;
        }
        printf("\n");

        return 0;
}
/*
+------+   +------+   +------+   +-------+  +-------+
|      |   |      |   |      |   |       |  |       |
+--+---+   +--+---+   +--+---+   +---+---+  +---+---+
   |          |          |           |          |
   |          |          |           |          |
+--+---+   +--+---+   +--+---+-  +---+---+  +---+---+
| head +---+second+---+third +---+ forth +--+ fifth |
+--+---+   +------+   +------+   +-------+  +-------+
   |
   |
+--+---+
| ptmp |
+------+

*/
