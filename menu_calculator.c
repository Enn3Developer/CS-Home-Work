#include <stdio.h>
#include <stdlib.h>

// to add another operation, add the name here, create a function and add the case in the
// switch statement in `get_result`
typedef enum {addition, subtraction, multiplication, division} operation;
typedef enum {not_op, div_by_zero} error_type;  // error handling

void error(error_type e);
operation get_operation();
float get_num(char name);
float get_result(float a, float b, operation op);
float add_op(float a, float b);
float sub_op(float a, float b);
float mul_op(float a, float b);
float div_op(float a, float b);

int main() {
    operation op = get_operation();
    float a = get_num('a');
    float b = get_num('b');
    float result = get_result(a, b, op);
    printf("%g\n", result);  // format `g` round the float numbers "smartly"

    return 0;
}

void error(error_type e) {
    switch (e) {
        case not_op:
            printf("You have chosen an operation not handled by the program\n");
            break;
        case div_by_zero:
            printf("Division by zero is impossible\n");
            break;
        default:
            break;
    }
    exit(1);  // error code for "There was an error during execution of `program`"
}

operation get_operation() {
    printf("Write the character of your operation.\n"
            "This character may be `+` or `*` and so on.\n");  // multiline string
    char op_c;
    op_c = getchar();  // get the first character of the total input

    switch (op_c) {
        case '+':
            return addition;
        case '-':
            return subtraction;
        case '*':
            return multiplication;
        case '/':
            return division;
        default:
            error(not_op);
    }
}

float get_num(char name) {
    printf("Write the number for %c: ", name);  // used for `a` and `b`
    float num;
    scanf("%f", &num);
    fflush(stdout);
    return num;
}

float get_result(float a, float b, operation op) {
    if (b == 0 && op == division) error(div_by_zero);  // check for the error `div_by_zero`

    switch (op) {  // add here other cases for operations
        case addition: return add_op(a, b);
        case subtraction: return sub_op(a, b);
        case multiplication: return mul_op(a, b);
        case division: return div_op(a, b);
    }
}

float add_op(float a, float b) {
    return a+b;
}

float sub_op(float a, float b) {
    return a-b;
}

float mul_op(float a, float b) {
    return a*b;
}

float div_op(float a, float b) {
    return a/b;
}