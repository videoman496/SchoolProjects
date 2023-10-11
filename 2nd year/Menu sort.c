#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIZZAS 100
#define MAX_NAME_LENGTH 101

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} Pizza;

int read_pizza(Pizza* p) {
    if(fgets(p->name, MAX_NAME_LENGTH, stdin) == NULL) return 0; // Reading the name of the pizza
    p->name[strcspn(p->name, "\n")] = 0; // Removing the newline character

    if (scanf("%f", &p->price) != 1) { // Reading the price of the pizza
        return 0;
    }
    while((getchar()) != '\n'); // Clearing the input buffer
    return p->price > 0 ? 1 : 0;
}

int compare_pizzas(const void* a, const void* b) {
    const Pizza* pa = (const Pizza*)a;
    const Pizza* pb = (const Pizza*)b;

    if (pa->price < pb->price) return -1;
    if (pa->price > pb->price) return 1;

    return strcmp(pa->name, pb->name);  // v případě stejných cen porovnáme názvy
}

int main() {
    Pizza pizzas[MAX_PIZZAS];
    int count = 0;

    while (count < MAX_PIZZAS && read_pizza(&pizzas[count])) {
        count++;
    }

    qsort(pizzas, count, sizeof(Pizza), compare_pizzas);

    
    for (int i = 0; i < count; i++) {
        printf("%s\n%.2f\n", pizzas[i].name, pizzas[i].price);
    }

    return 0;
}
