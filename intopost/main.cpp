#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef char element;

typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

void init_stack(StackType* s) {
    s->top = -1;
}

int is_full(StackType* s) {
    return s->top == MAX_STACK_SIZE - 1;
}

int is_empty(StackType* s) {
    return s->top == -1;
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택이 꽉 찼습니다\n");
        return;
    }
    else s->stack[++(s->top)] = item;
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있습니다\n");
        exit(1);
    }
    else return s->stack[(s->top)--];
}

int eval(char exp[]) {
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;
    init_stack(&s);

    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (ch >= '0' && ch <= '9') { // 숫자일 경우
            value = ch - '0';
            push(&s, value);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { // 연산자일 경우
            if (is_empty(&s)) {
                fprintf(stderr, "잘못된 표기식입니다\n");
                exit(1);
            }
            op2 = pop(&s);
            if (is_empty(&s)) {
                fprintf(stderr, "잘못된 표기식입니다\n");
                exit(1);
            }
            op1 = pop(&s);
            switch (ch) {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
        else { // 피연산자와 연산자가 아닐 경우
            fprintf(stderr, "잘못된 표기식입니다\n");
            exit(1);
        }
    }
    if (is_empty(&s)) {
        fprintf(stderr, "잘못된 표기식입니다\n");
        exit(1);
    }
    return pop(&s);
}

int main(void) {
    int result;
    char exp[MAX_STACK_SIZE];
    printf("후위표기식을 입력하세요: ");
    scanf_s("%s", exp);
    result = eval(exp);
    printf("결과값은 %d\n", result);
    return 0;
}
