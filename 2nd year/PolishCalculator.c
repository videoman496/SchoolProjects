#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define STACK_SIZE 10
typedef struct {
    float values[STACK_SIZE];
    int size;
} Stack;

void push(Stack* stack, float value) {
    assert(stack->size < STACK_SIZE);
    stack->values[stack->size++] = value;
    for(int i = 0; i < stack->size; i++) {
        printf("%.2f ", stack->values[i]);
    }
    printf("\n");
}

float pop(Stack* stack) {
    assert(stack->size > 0);
    return stack->values[--stack->size];
}

bool isOperator(const char* str) {
    return strspn(str, "+-*/") == strlen(str) && strlen(str) == 1;
}

bool isNumber(const char* str) {
    char* end;
    strtod(str, &end);
    return end != str && *end == '\0' && strspn(str, "0123456789.") == strlen(str); 
}

void calculate(Stack* stack) {
    char input[50];
    while (1) {
        if (fgets(input, sizeof(input), stdin) != NULL) {
            if(feof(stdin)){
                printf("\nnot enough operands\n");
                exit (0);
            }
            if(stack->size>=STACK_SIZE){
                printf("full stack\n");
                break;
            }
            if (strcmp(input, "\n") == 0) {
                printf("no input\n");
                break;
            }
            input[strcspn(input, "\n")] = 0;
            
            if (isNumber(input)) {
                push(stack, atof(input));
            } else if (isOperator(input)) {
                if (stack->size < 2) {
                    printf("not enough operands\n");
                    break;
                }

                float b = pop(stack);
                float a = pop(stack);
                float result;

                switch (input[0]) {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/':
                        if (b != 0) {
                            result = a / b;
                        } else {
                            printf("division by zero\n");
                            return;
                        }
                        break;
                    default:
                        printf("Error: Invalid operation.\n");
                        return;
                }
                push(stack, result);
            } else {
                printf("bad input\n");
                break;
            }
        } else {
            printf("no input\n");
            break;
        }
    }
}

int main(void) {
    Stack stack = { .size = 0 };
    calculate(&stack);
    return 0;
}
