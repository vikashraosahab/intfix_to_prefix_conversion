// PROGRAM THAT CONVERT INFIX TO POST FIX  EXPRESSION 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 40
typedef struct 
{
    char stack [MAX_SIZE];
    int top;
} STACK;

void initialized (STACK *);
int getPriority (char c);
void push (STACK *,char value);
char pop (STACK *);
int isEmpty (STACK *);
int isFulled (STACK *);

// MAIN FUNCTION OF THE PROGRAM
int main (int argc, char *argv[])
{
  STACK s1; // STRUCTURE VARIABLE
  initialized (&s1); // INITIALIZED STRUCTURE VARIABLE
  char infix_exp [MAX_SIZE], postfix_exp [MAX_SIZE];
  int i = 0, j = 0; 
  printf ("\nEnter infix expression : ");
  fgets (infix_exp,MAX_SIZE,stdin);
  infix_exp [strcspn (infix_exp , "\n")] = '\0'; // REMOVE NEWLINE CHARACTER BY NULL OPERATOR
  // LOGIC OF THE INFIX TO POST EXPRESSION
  while (infix_exp [i] != '\0' && infix_exp [i] != '\n')
  {
    if (infix_exp [i] == '(')
    {
        push (&s1,infix_exp [i]);
    }
    else if (infix_exp [i] == ')')
    {
        while (s1.top != -1 && s1.stack [s1.top] != '(')
        {
            postfix_exp [j++] = pop (&s1);
        }
        /* MISMATCHED PARENTHESIS */
        if (s1.stack [s1.top] == -1)
        {
            printf ("\nStack is empty");
            exit (1);
        }
        pop (&s1); // REMOVE OTHER PARENTHESIS
    }
    else if (isdigit (infix_exp [i]) || isalpha (infix_exp [i]) || infix_exp [i] == ' ')
    {
        postfix_exp [j++] = infix_exp [i];
    }
    else if (infix_exp [i] == '+' || infix_exp [i] == '-' || infix_exp [i] == '*' || infix_exp [i] == '/')
    {
        while (s1.top != -1 && s1.stack [s1.top] != '(' && getPriority (s1.stack[s1.top]) > getPriority (infix_exp [i]))
        {
          postfix_exp [j++] = pop (&s1);
        }
        push (&s1,infix_exp[i]); // INCREMENT I BY 1
    }
    else 
    {
        printf ("\nIn-valid expression");
        exit (1);
    }
    i = i + 1;
  }
  while (s1.top != -1 && s1.stack[s1.top] != '(')
  {
    postfix_exp [j++] = pop (&s1);
  }
  postfix_exp [j] = '\0';
  printf ("postfix expression are : %s",postfix_exp);
    return 0; // TERMINATE PROGRAM AFTER SUCCESSFULLY EXECUTION
}

void initialized (STACK *s1)
{
    s1->top = -1; // INITIALIZE STACK WITH EMPY
}
int isEmpty (STACK *s1)
{
   return s1->top == -1;
}
int isFulled (STACK *s1)
{
    return s1->top == MAX_SIZE - 1;
}
void push (STACK *s1, char value)
{
  if (isFulled (s1) == -1)
  {
    printf ("\nStack is fulled !");
    exit (1);
  }
  else 
  {
    s1->stack [++s1->top] = value;
  }
}
char pop (STACK *s1)
{
    if (isEmpty (s1))
    {
       printf ("\nSTACK IS EMPTY !");
       exit (1);
    }
    else 
    {
        return s1->stack [s1->top--];
    }
}
int getPriority (char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else 
    return 0;
}