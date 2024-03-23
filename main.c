#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// doubles instead of longs or ints to handle decimals in equation

extern double add(double a, double b);
extern double subtract(double a, double b);
extern double multiply(double a, double b);
extern double divide(double a, double b);

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

double performOperation(double a, double b, char op) {
    switch (op) {
        case '+': return add(a, b);
        case '-': return subtract(a, b);
        case '*': return multiply(a, b);
        case '/':
            if (b == 0.0) {
                printf("division by zero not allowed \n");
                exit(EXIT_FAILURE);
            }
            return divide(a, b);
        default: printf("invalid operator \n"); exit(EXIT_FAILURE);
    }
}

void infixToPostfix(const char* infix, char* postfix) {
    char stack[256];
    int top = -1;
    int j = 0;

    for (int i = 0; infix[i]; ++i) {
        if (isdigit(infix[i]) || infix[i] == '.') {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            stack[++top] = '(';
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            top--;
        } else if (isOperator(infix[i])) {
            while (top != -1 && precedence(infix[i]) <= precedence(stack[top])) {
                postfix[j++] = stack[top--];
                postfix[j++] = ' ';
            }
            stack[++top] = infix[i];
        }
    }

    while (top != -1) {
        postfix[j++] = stack[top--];
        postfix[j++] = ' ';
    }

    postfix[j - 1] = '\0';
}

double evaluatePostfix(const char* postfix) {
    double stack[256];
    int top = -1;

    for (int i = 0; postfix[i]; ++i) {
        if (isdigit(postfix[i]) || postfix[i] == '.') {
            double num = 0.0;
            double fraction = 1.0;
            int decimalPointSeen = 0;
            while (isdigit(postfix[i]) || (!decimalPointSeen && postfix[i] == '.')) {
                if (postfix[i] == '.') {
                    decimalPointSeen = 1;
                } else {
                    num = num * 10 + (postfix[i] - '0');
                    if (decimalPointSeen) {
                        fraction *= 10.0;
                    }
                }
                i++;
            }
            num /= fraction;
            stack[++top] = num;
            i--;
        } else if (postfix[i] == ' ') {
            continue;
        } else if (isOperator(postfix[i])) {
            double b = stack[top--];
            double a = stack[top--];
            stack[++top] = performOperation(a, b, postfix[i]);
        }
    }

    return stack[top];
}

int main(int argc, const char * argv[]) { // required due to the GAS prefix from xcode
    char infix[256] = {0};
    char postfix[256] = {0};

    printf("Enter expression: ");
    if (!fgets(infix, sizeof(infix), stdin)) {
        printf("Error.\n");
        return 1;
    }

    infixToPostfix(infix, postfix);
    double result = evaluatePostfix(postfix);
    printf("result: %lf\n", result);

    return 0;
}
