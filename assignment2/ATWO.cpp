//
//  main.cpp
//  Assignment_two
//
//  Created by Tim McQuillis on 1/30/15.
//  Copyright (c) 2015 Tim McQuillis. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

using namespace std;

ifstream a2;
int lines = 0;

struct Expressions{
    string expressions;
}num[10];

struct Stack{
    
    float numbers;
    char symbols;
    Stack *next;
};

int stackEmptyCheck(Stack *Top)
{
    if(Top == NULL)
        return 0;
    else
        return 1;
}

void pullExpressions(Stack *&Top, Stack *&Bottom)
{
    
    if (Top == Bottom)
    {
        delete Top;
        Top = NULL;
        Bottom = NULL;
    }
    
    else
    {
        Stack *temp = Top;
        Top = Top->next;
        delete temp;
    }
    
}

void pushNumbers(Stack *&Top,Stack *&Bottom, float newNumbers)
{
    if(stackEmptyCheck(Top)==0)
    {
        Stack *temp = new Stack;
        temp->numbers = newNumbers;
        temp->next = NULL;
        Top = temp;
    }
    else if(stackEmptyCheck(Top)==1)
    {
        Stack *temp = new Stack;
        temp->numbers = newNumbers;
        temp->next = Top;
        Top = temp;
        
    }
}

void pushSymbols(Stack *&Top, Stack *&Bottom, char newSymbols)
{
    if(stackEmptyCheck(Top)==0)
    {
        Stack *temp = new Stack;
        temp->symbols = newSymbols;
        temp->next = NULL;
        Top = temp;
    }
    else if(stackEmptyCheck(Top)==1)
    {
        Stack *temp = new Stack;
        temp->symbols = newSymbols;
        temp->next = Top;
        Top = temp;
    }
}

struct Queue{
    
    char symbols;
    Queue *next;
};

int queueEmptyCheck(Queue *Head)
{
    if(Head == NULL)
        return 0;
    else
        return 1;
}

void enqueue(Queue *&Head, Queue *&Tail, int n)
{
    if(queueEmptyCheck(Head)==0)
    {
        Queue *temp = new Queue;
        temp->symbols = n;
        Head = temp;
        Tail = temp;
    }
    else if(queueEmptyCheck(Head)==1)
    {
        Queue *temp = new Queue;
        temp->symbols = n;
        temp->next = NULL;
        Tail->next = temp;
        Tail = temp;
    }
}

void dequeue(Queue *&Head, Queue *&Tail)
{
    if (Head == Tail)
    {
        delete Head;
        Head = NULL;
        Tail = NULL;
    }
    else
    {
        Queue *temp = Head;
        Head = Head->next;
        delete temp;
    }
}


int operationOrder(char operation)
{
    switch (operation)
    {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '^': return 3;
            
        default: return 0;
    }
}
int numberOfLines()
{
    string line;
    ifstream a2("a2.txt");
    
    if(a2.is_open())
    {
        while(!a2.eof())
        {
            getline(a2,line);
            lines++;
        }
        a2.close();
    }
    lines--;
    return lines;
}

string infixToPostfix(string expression, Stack *&Top, Stack *&Bottom, Queue *&Head, Queue *&Tail)
{
    string postfix = "";
    
    for(int i =0;i < expression.length(); i++)
    {
        if(expression[i] == '(')
        {
            pushSymbols(Top, Bottom, expression[i]);
        }
        else if(expression[i] == ')')
        {
            while(Top->symbols != '(')
            {
                enqueue(Head, Tail, Top->symbols);
                pullExpressions(Top, Bottom);
            }
            pullExpressions(Top, Bottom);
        }
        
        else if(expression[i] == '^' || expression[i] ==  '*' || expression[i] ==  '/' || expression[i] ==  '+' || expression[i] ==  '-')
        {
            while(stackEmptyCheck(Top)==1 && Top->symbols != '(' && Top->symbols >= operationOrder(expression[i]))
            {
                enqueue(Head, Tail, Top->symbols);
                pullExpressions(Top, Bottom);
            }
            pushSymbols(Top, Bottom, expression[i]);
        }
        else if(expression[i] >= '0' && expression[i] <= '9')
        {
            enqueue(Head, Tail, expression[i]);
        }
    }
    
    while (stackEmptyCheck(Top)==1)
    {
        enqueue(Head, Tail, Top->symbols);
        pullExpressions(Top, Bottom);
    }
    while(queueEmptyCheck(Head)==1)
    {
        postfix = postfix + Head->symbols;
        dequeue(Head, Tail);
    }
    a2.close();
    return postfix;
}
float evalPostfix(string postfix, Stack *&fTop, Stack *&fBottom)
{
    float numbers, answer,finalAnswers, v1, v2;
    int i;
    for(i=0; i < postfix.length(); i++)
    {
        if(postfix[i] >= '0' && postfix[i] <= '9')
        {
            numbers = (float)postfix[i] - 48;
            pushNumbers(fTop, fBottom, numbers);
        }
        if(postfix[i] == '^' || postfix[i] ==  '*' || postfix[i] ==  '/' || postfix[i] ==  '+' || postfix[i] ==  '-')
        {
            v2 = fTop->numbers;
            pullExpressions(fTop, fBottom);
            v1 = fTop->numbers;
            pullExpressions(fTop, fBottom);
            
            switch(postfix[i]){
                case '+':
                {
                    answer = v1+v2;
                    pushNumbers(fTop, fBottom, answer);
                    break;
                }
                case '-':
                {
                    answer = v1-v2;
                    pushNumbers(fTop, fBottom, answer);
                    break;
                }
                case '*':
                {
                    answer = v1*v2;
                    pushNumbers(fTop, fBottom, answer);
                    break;
                }
                case '/':
                {
                    answer = v1/v2;
                    pushNumbers(fTop, fBottom, answer);
                    break;
                }
                case '^':
                {
                    answer = pow(v1, v2);
                    pushNumbers(fTop, fBottom, answer);
                    break;
                }
            }
        }
    }
    finalAnswers = fTop->numbers;
    pullExpressions(fTop, fBottom);
    return finalAnswers;
}
void fileInfix_to_Post(Stack *&Top, Stack *&Bottom, Queue *&Head, Queue *&Tail)
{
    Stack *fTop = NULL;
    Stack *fBottom = NULL;
    string postfix = "";
    string expression = "";
    float answer;
    int i=0;
    int numberLines;
    numberLines = numberOfLines();
    a2.open("a2.txt");
    while(i != numberLines)
    {
        getline(a2, num[i].expressions);
        cout << num[i].expressions << endl;
        postfix = infixToPostfix(num[i].expressions, Top, Bottom, Head, Tail);
        cout << postfix << endl;
        answer = evalPostfix(postfix, fTop, fBottom);
        cout << answer << endl << endl;
        i++;
    }
    a2.close();
}

int main() {
    
    Stack *myTop = NULL, *tail = NULL;
    Queue *front = NULL, *end = NULL;
    
    fileInfix_to_Post(myTop, tail, front, end);
    
    return 0;
}
