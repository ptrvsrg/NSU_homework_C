#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char TValue;

struct Tstack 
{
    TValue Value;
    struct Tstack* Next;
};

typedef struct Tstack* TStack;

bool IsEmptyStack(TStack list)
{
    return list == NULL;
}

TStack CreateItem(TValue value)
{
    TStack new = malloc(sizeof(*new));
    assert(!IsEmptyStack(new));

    new->Value = value;
    new->Next = NULL;
    
    return new;
}

TStack Push(float value, TStack* list)
{
    TStack new = CreateItem(value);
    new->Next = *list;
    (*list) = new;

    return *list;
}

TStack ConvertArrayToStack(size_t arraySize, char* array)
{
    if (arraySize == 0)
    {
        return NULL;
    }

    TStack list = CreateItem(*array);
    list->Next = ConvertArrayToStack(arraySize - 1, array + 1);

    return list;
}

TValue Pop(TStack* stack)
{
    assert(!IsEmptyStack(*stack));

    TValue value = (*stack)->Value;

    TStack removeElem = *stack;
    *stack = (*stack)->Next;

    free(removeElem);

    return value;
}

void FreeStack(TStack* stack) 
{
    while (!IsEmptyStack(*stack))
    {
        Pop(stack);
    }
}

float Fabs(float num)
{
    return (num >= 0) ? num : -num;
}

bool IsDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

float SymbolToDigit(char symbol)
{
    return symbol - '0';
}

float GetExpressionValue(char operator, float first, float second)
{
    switch(operator)
    {
        case '+': return first + second;
        case '-': return first - second;
        case '*': return first * second;
        case '/':
            assert(Fabs(second) > 1E-6);
            return first / second;
        default: assert(false);
    }
}

float CalcPrefix(TStack* prefix)
{
    char symbol = Pop(prefix);

    if(IsDigit(symbol))
    {
        return SymbolToDigit(symbol);
    }
    else
    {
        float first = CalcPrefix(prefix);
        float second = CalcPrefix(prefix);
        return GetExpressionValue(symbol, first, second);
    }
}

int main(void)
{
    char* prefix1 = "/*432";
    char* prefix2 = "2";

    TStack stack1 = ConvertArrayToStack(strlen(prefix1), prefix1);
    TStack stack2 = ConvertArrayToStack(strlen(prefix2), prefix2);
    
    printf("%s = %f\n", prefix1, CalcPrefix(&stack1));
    printf("%s = %f\n", prefix2, CalcPrefix(&stack2));

    return 0;
}