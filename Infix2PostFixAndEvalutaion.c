
//https://www.hackerrank.com/contests/cs1300-odd-2014/challenges/evaluate-expression

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 101

float eval_post();
void infix_to_postfix();
void push(float);
float pop ();

int prec(char);

char infix[MAX], postfix[MAX];
float stack[MAX];
int top;
int flag=0;
int main()
{
   float value;
   top = 0;
   //printf("Enter infix : ");
   fflush(stdin);
   //scanf ("%s", infix);
   gets (infix);
   infix_to_postfix();
   //printf("Postfix : [%s]\n",postfix);
   value=eval_post();
   //printf("Value of expression : %ld\n",value);
   if (flag == 0)
   {
       int x = value;
       if (value - x)
	       printf ("%.1f\n", value);
       else
           printf ("%d\n", x);
   }
   else
	   printf ("ERROR\n");
   return 0;
}/*End of main()*/

void infix_to_postfix()
{
	int i,p=0,type,precedence,len;
	char next ;
	stack[top]='#';
	len=strlen(infix);
	//printf ("Infix len %d\n", len);

	for(i=0; i < len;i++)
	{
		//printf ("%c", infix[i]);
		switch(infix[i])
		{
			case '(':
				push(infix[i]);
				break;
			case ')':
				while((next = pop()) != '(')
					postfix[p++] = next;

				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '^':
				precedence = prec(infix[i]);
				while(stack[top]!='#' && precedence<= prec(stack[top]))
				{
					postfix[p++] = pop();
				}
				push(infix[i]);
				break;
			case ' ':
				//printf ("Ignore space\n");
				break;
			default: /*if an operand comes */
				postfix[p++] = infix[i];
		}/*End of switch */
	}/*End of for */

	while(stack[top]!='#')
		postfix[p++] = pop();
	postfix[p] = '\0' ; /*End postfix with'' to make it a string*/
}/*End of infix_to_postfix()*/


/* This function returns the precedence of the operator */
int prec(char symbol )
{
	switch(symbol)
	{
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
		case '^':
			return 3;
	}/*End of switch*/
	return 0;
}/*End of prec()*/

void push(float symbol)
{
	if(top > MAX)
	{
		printf("Stack overflown");
		exit(1);
	}
	else
	{
		top=top+1;
		stack[top] = symbol;
	}
}/*End of push()*/
float pop()
{
	if (top == -1 )
	{
		printf("Stack underflow n");
		exit(2);
	}
	else
		return (stack[top--]);
}/*End of pop()*/

float eval_post()
{
	long int len;
	float a, b, temp, result;
	int i;
	len=strlen(postfix);

	for(i=0; i < len;i++)
	{
		if(postfix[i]<='9' && postfix[i]>='0') //if number, push in stack and wait for operator
			push(postfix[i]-48 );
		else
		{ // If operator, evaluate
			a=pop();
			b=pop();

			if (b == 35 && postfix[i] == '-')
			{
				//to handle scenario ((-2) + 3)
				push ( a * -1);
				continue;
			}

			if (a == 35 || b == 35)
			{
				flag = 1;
				return 0;
			}
			switch(postfix[i])
			{
				case '+':
					temp=b+a; break;
				case '-':
					temp=b-a;break;
				case '*':
					temp=b*a;break;
				case '/':
					if (a == 0)
                    {
						//To handle division by 0.
						flag=1;
						return 0;
                    }
					temp=b/a;break;
#if 0
				case '%':
					temp=b%a;break;
				case '^':
					temp=b<<(a/2);
#endif
			}/*End of switch */
			push(temp);
		}/*End of else*/
	}/*End of for */
	result=pop();
	return result;
}/*End of eval_post */
