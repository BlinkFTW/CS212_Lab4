/*
Eric Kang
Section 53
Lab 4

Description:
	This program allows the user to input a fully parenthesised expression consisting
	of 0123456789()*+-/ and evalues the expression.

Input(s):
	eqn[] (char array)

Output(s):
	intspeek(valStack) (int)

Function(s):
	void getInput(char *quesPtr);
	int evalExp( char ques[], int max );
	int precidence(char x);
	void printAns( char ques[], int ans );
*/
#include <stdio.h>
#include "queue.h"
#include "stack.h"
#define DEBUG 0	//debug condition true/false

void getInput(char *quesPtr);
int evalExp( char ques[], int max );
int precidence(char x);
void printAns( char ques[], int ans );


int main()
{
	char eqn[MAXQUEUESIZE]={0};	//Equation
	int maxChar=0;		//a counter for the number of the of characters in eqn[]
	int sol;			//Solution
	int i; 				//counter

	
	//prompt the user for input and stor in eqn
	getInput(eqn);

	//count the number of characters in eqn[]
	for(i=0;eqn[i]!='\0';i++)
		maxChar++;

	//Evaluate eqn and store in sol
	sol = evalExp(eqn, maxChar);

	//Display solved answer
	printAns(eqn,sol);

	return 0;
}

/**************************************************************************
function: getInput
inputs: (none)
outputs: ques	(char array)
This function prompts the user for a fully parenthesised expression
***************************************************************************/
void getInput(char *quesPtr)
{
	
	//Prompt User for equation
	printf("\nEnter an equation: ");
	scanf("%s", quesPtr);

}

/**************************************************************************
function: evalExp
inputs: ques	(char array)
		max	(int)
outputs: intspeek(valStack)	(int)
This function Evaluates a fully parenthesised expression.
First the expression is converted to post fix then evaluated.
***************************************************************************/
int evalExp( char ques[], int max )
{
	CREATE(postFix);	//postfix notation queue
	STACK(opStack);		//character stack holds operators
	intSTACK(valStack);	//int stack
	int asciiVal;		//holds ASCII value of char
	int i; 				//counter
	int parCnt=0;		// ')' counter
	int a;
	int b;

	//CONVERT to post fix notation
	for(i=0;i<max;i++)
	{	
		asciiVal=ques[i];  //asciiVal is int && eqn[] is char
		//IF number
		if(asciiVal >= 48 && asciiVal <= 57)	//ascii of 0->9 are between 48->57
			enQueue(postFix,ques[i]);
		//IF operator
		else if(asciiVal >=42 && asciiVal <= 47)//ascii of *+,-./ are between 40->47
		{
			if(parCnt)	//if '(' is present, ignore order of operations
			{
				push(opStack,ques[i]);
				parCnt--;
			}//END parCnt
			else if(!sisEmpty(opStack))	//Will not check for precidence if stack is empty
			{
				if(precidence(ques[i]) < precidence(speek(opStack)))	//Check if eqn[i] has a lower precidence than operator in stack
				{
					enQueue(postFix,pop(opStack));	//pop higher operator from stack and enqueue to postfix queue
					push(opStack,ques[i]);			//push lower operator to stack
				}//END lower precidence
				else
					push(opStack,ques[i]);
			}//END Stack not empty
			else	//If the stack IS empty then push eqn[i] to opStack anyway
				push(opStack,ques[i]);
		}//END operators
		else if(asciiVal == 40)	//IF '('
			parCnt++;
		else if(asciiVal == 41)	//IF ')'
			enQueue(postFix,pop(opStack));
	}//END post fix CONVERT	

	//Empty any remaining operators from opStack into PostFixQueue
	while(!sisEmpty(opStack))
		enQueue(postFix,pop(opStack));


	//SOLVE POST FIX EQUATION
	while(!qisEmpty(postFix))
	{
		asciiVal = deQueue(postFix);
		if(asciiVal >= 48 && asciiVal <= 57)	//ascii of 0->9 are between 48->57
			intpush(valStack,asciiVal-48);
		else
			if(asciiVal == 42)		//Multiplication
			{
				b = intpop(valStack);
				a = intpop(valStack);
				intpush(valStack,a*b);
			}//END Multiply
			else if(asciiVal == 43)	//Addition
			{
				b = intpop(valStack);
				a = intpop(valStack);
				intpush(valStack,a+b);
			}//END Addition
			else if(asciiVal == 45)	//Subtraction
			{
				b = intpop(valStack);
				a = intpop(valStack);
				intpush(valStack,a-b);
			}//END Subtraction
			else if(asciiVal == 47)	//Division
			{
				b = intpop(valStack);
				a = intpop(valStack);
				intpush(valStack,a/b);
			}//END Division		
	}//END SOLVE while

	return intspeek(valStack);	
}

/**************************************************************************
function: precidence
inputs: x (char)
outputs: prec (int)
This function determines the precidence of an operator and returns that value.
***************************************************************************/
int precidence(char x)
{
	int prec = 0;
	if(x=='*' || x=='/')
		prec=3;
	else if(x=='+')
		prec=2;
	else
		prec=1;

	return prec;
}

/**************************************************************************
function: printAns
inputs: ques	(char array)
		ans		(int)
outputs: (none)
This function prints the equation and solution
***************************************************************************/
void printAns( char ques[], int ans )
{
	//Display solved answer
	printf("\n%s = %d\n\n", ques,ans);
}
