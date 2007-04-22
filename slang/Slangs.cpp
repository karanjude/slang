#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>
#include <ctype.h>

//typedef int bool;


#define TAB			'\t'
//#define true		(1)
//#define false		(0)
#define KEYWORDS	(17)

// max size of stack and segment

#define MAX_STACK_SIZE	   (100)
#define MAX_SEGMENT_SIZE	(500)

// max size of symbol table
const int MAX = 100;

// each identifier is a symbol of 32 characters
typedef char _symbol[32];
typedef _symbol symbol;

// keeps track of the number of lines in the program
int _lineCounter;

int _lineCount;

// might eliminate
bool _true;

// an item in the information segment

// pointer to address of the function

union  Code
{
	void (*op)(void);
	int value;
	int index;
};


// data stack
int _stack[MAX_STACK_SIZE];

// stack pointer
int _stackp;

// program counter for our information segment
int _pc;

// used to index the names in symbol table
int _index;

// numeric value of variable
int _num;

// information segment
Code _segment[MAX_SEGMENT_SIZE];
// ???
int _L[MAX];

// array of strings used in prj
char * _strings[MAX];
// used to keep track of messages in slang
int _msgCount;

// our symbol table
//symbol _symTab[1000];
// pointer to our symbol table
symbol * _tablePtr;


/* look ahead global variable
 : used to store the next token in token stream */
char _lookAhead;
// used to keep the track of levels of identations
int _levels;
// ???
int _lineLevel;

// store token type
char _token;
// store the value 
char _value[16];

// number of entries in symbol table
int _numEntry;

// the actual symbol table
 _symbol  _st[MAX];
 // used to store the stype of data 
 char _stype[MAX];
// used to store the value of each data
 int _svalue[MAX];

 // number of keywords 
 const int  NUMKEYWORDS=23;
 

// our keyword table
 symbol _keywordList[NUMKEYWORDS] = {"","BREAK","IF","ELSE","ENDIF","WHILE","ENDWHILE",
 											    "LOOP","ENDLOOP","REPEAT","UNTIL","FOR","DO",
                                     "ENDFOR","TO","ENDDO","END","READ","WRITE","VAR","BEGIN","END","PROGRAM"
						  						};

// our code for each symbol
char _keywordCode[NUMKEYWORDS+1] = "xbileweperufdeteeRWvbep";

// used to check whether the file is used or not
FILE * _file;

// show this info 
char _info[] = "\n\n\tSLANG : Simple Language Interpreter "
					"\n\tA pilot test project "
					"\n\n\tTo operate in interactive mode type :"
					"\n\n\t\tslang run "
					"\n\n\t OR \n"
					"\n\tTo operate in file mode type :"
					"\n\n\t\tslang filename";

// constants 
enum
{
	FILE_DOES_NOT_EXIST ,	 
	UNKNOWN_FILE_TYPE,		
	UNKNOWN_OPTION			
};

// list of errors for corresponding file type constants
char * _errors[] = {
						  "The File Does not Exist ",
						  "The File type cannot be understood ",
						  "The option specified is not supported "
						 };



void Initialize(void);
void Start(void);
void Execute(void);
void Process(void);
void ShowInfo(void);
void ShowError(int);

void Init();
void MainProg();
void Prog();

/* codegen3.cpp */
void SetLess (void);
void SetGreater (void);
void SetLessOrEqual(void);
void SetGreaterOrEqual(void);
void Branch(char * str,int );
void Branch(void);
void BranchFalse(char * str,int);
void BranchFalse(void);
void BranchTrue(void);
void WriteVar(void);
void ReadVar(void);
void Store(char * name);
void Store(void);

/* codegen4.cpp */
void Ident(int);
void Clear();
void Negate();
void NotIt();
void LoadConstant(int n);
void LoadVariable(char * name);
void Push();
void PopAdd();
void PopSub();
void PopMul();
void PopDiv();
void PopModulus();
void PopAnd();
void PopOr();
void PopXor();
void PopCompare();
void SetEqual();
void SetNotEqual();
void Eval(int);
void Load(void);
void Inc(void);

/* output4.cpp */
void Emit (char * s);
void EmitLine(char * s);
char * NewLabel(void);
void  PostLabel (char * L);


/* output3.cpp */
void Header();
void Epilog();
void Prolog();

 // parser1.cpp
 void Expression(void);
 void Equal(void);
 void LessOrEqual();
 void NotEquals(void);
 void Less(void);
 void Greater(void);
 void Relation(void);
 void NotFactor(void);
 void BoolTerm(void);
 void BoolOr(void) ;
 void BoolXor(void) ;
 void BoolExpression(int );
 void Assignment(int);
 void DoIf(int,int);
 void DoWhile(int,int);
 void DoLoop(int,int);
 void DoRepeat(int,int);
 void DoFor(void);
 void DoDo(void);
 void DoBreak(char * L,int);
 void DoRead(void);
 void DoWrite(int);
 void Block(char * ,int,int  );

 void NegativeFactor(void);

 // parser2.cpp
 void Factor(void);
 void FirstFactor(void);
 void Multiply(void);
 void Divide(void);
 void Modulus(void);
 void Term1(void);
 void Term(void);
 void FirstTerm(void);
 void Add(void);
 void Substract(void);



  // scanner1.cpp
  int LookUp(symbol * _tablePtr,char* str,int n);
  void Scan (void);
  void MatchString(char*	str);
  bool IsMulOp(char c);
  bool IsOrOp (char c);
  bool IsRelOp(char c);
  bool IsWhite(char c);
  void Match(char x);
  int Locate(_symbol n);
  bool InTable(_symbol n);
  void AddEntry(_symbol n, char t);
  void GetName(void);
  void GetNum(void);
  void NewLine(void);

  // scanner2.cpp
  void Decl(void);
  void TopDecls(void);

 // scanner3.cpp
 void GetChar(void);
 bool IsAlpha(int Char);
 bool IsDigit(int Char);
 bool IsAddOp(char c);
 bool IsAlNum(char c);

 // scanner.cpp
 void SkipWhite(void);
 void SkipComment(void);
 void ShowMessage(void);
 void SkipMessage(void);
 void Alloc(_symbol N);

 // error.cpp
void Error(char * Str);
void Abort(char * Str);
void Expected(char * Str);
void Undefined(char * str);



/*
Function Name: SetLess
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and set D0 if compare was >
*/
void SetLess (void)
{
	//printf("\t SLT D0\n");
	//printf("\t EXT D0\n");
   int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left < right;

}



/*
Function Name: SetGreater
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and set D0 if compare was  <
*/
void SetGreater (void)
{
	//printf("\t SGT D0\n");
	//printf("\t EXT D0\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left > right;
}


/*
Function Name: SetLessOrEqual
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and set D0 if compare was <=
*/
void SetLessOrEqual(void)
{
	//printf("\t SGT D0\n");
	//printf("\t EXT D0\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left <= right;
}


/*
Function Name: SetGreaterOrEqual
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and set D0 if compare was >=
*/
void SetGreaterOrEqual(void)
{
	//printf("\t SLE D0\n");
	//printf("\t EXT D0\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left >= right;
}


/*
Function Name: Branch
Return Type: void
Purpose: Does not return a value
Input Parameter: char *, integer
Purpose:
Function Purpose: Branch unconditional
*/
void Branch(char * L,int l = 0)
{
	// printf("\t BRA %s\n",L);
	_pc = _L[l];
}


/*
Function Name: Branch
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Branch unconditional
*/
void Branch(void)
{
	//printf("\t BRA %s\n",L);
	_pc = _L[_segment[_pc].value];
}


/*
Function Name: BranchFalse
Return Type: void
Purpose: Does not return a value
Input Parameter: char *, integer
Purpose:
Function Purpose: Branch false code generation
*/
void BranchFalse(char * L,int l = 0)
{
	//printf("\t TST D0\n");
	//printf("\t BRA %s\n",L);
	if(_stack[--_stackp] == 0)
	_pc = _L[l];
}


/*
Function Name: BranchFalse
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Branch false code generation
*/
void BranchFalse(void)
{
	//printf("\t TST D0\n");
	//printf("\t BRA %s\n",L);
	if(_stack[--_stackp] == 0)
	{
		_pc = _L[_segment[_pc].value];_true=false;
	}
	else
	{
		_pc++;_true=true;
	}
}


/*
Function Name: BranchTrue
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Branch true code generation
*/
void BranchTrue(void)
{
	if(_stack[--_stackp] == 1)
	{
		_pc = _L[_segment[_pc].value];
	}
	else
	{
		_pc= _L[_segment[_pc+1].value];
	}
}

/*
Function Name: Store
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Storing of variables
*/
void Store(void)
{
	_index = _segment[_pc++].index;
	_svalue[_index] = _stack[--_stackp];
}


/*
Function Name: Store
Return Type: void
Purpose: Does not return a value
Input Parameter: char *
Purpose:
Function Purpose:
storing of variables
*/
void Store(char * name)
{
//printf("\t LEA %s(PC),A0\n",name);
_index = LookUp(_st,name,_numEntry);
_svalue[_index] = _stack[--_stackp];
//printf("\t MOVE D0,(A0)\n");
}


/*
Function Name: Eval
Return Type: Void
Purpose: Does not return a value
Input Parameter: integer
Purpose: Token to evaluate
Function Purpose: evalute and execute the code
*/
void Eval(int pc)
{
	_pc = pc;
	while(_segment[_pc].op != NULL)
	{
		(*_segment[_pc++].op)();
	}
}


/*
Function Name: ReadVar
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Reading variable to primary register
*/
void ReadVar(void)
{
	//printf("\t BSR READ\n");
	cin >> _num;
	//fscanf(stdin,"\n%s",&_num);
	_stack[_stackp++] = _num;
	//_index = LookUp(_st,_value,_numEntry);
	_svalue[_segment[_pc++].index] = _num;
	// Store(_value);
}


/*
Function Name: WriteVar
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Write variable from primary register
*/
void WriteVar(void)
{
//printf("\t BSR WRITE\n");
printf("%d",_stack[--_stackp]);
}

/*
Function Name: Ident
Return Type: void
Purpose: Does not return a value
Input Parameter: integer
Purpose:
Function Purpose:
*/
void Ident(int line)
{
	static int old_line = 1;
	if(old_line != line)
	{
		old_line = line;
		for(int i = 1;i <= _levels && !_file;i++)
		printf("\t");
	}
}

/*
Function Name: Clear
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Clear the Primary Register
*/
void Clear()
{
	//printf("\t CLR D0\n");
	_stackp++;
}


/*
Function Name: Negate
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Negate the primary register
*/
void Negate()
{
	//printf("\t NEG D0\n");
	_stack[_stackp -1 ] = - (_stack[_stackp - 1]);
}


/*
Function Name: NotIt
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Complement the primary register
*/
void NotIt()
{
//	printf("\t NOT D0\n");
	_stack[_stackp -1 ] = !(_stack[_stackp - 1]);

}


/*
Function Name: LoadConstant
Return Type: void
Purpose: Does not return value
Input Parameter: integer
Purpose: used to load the token
Function Purpose: Load a Constant Value to Primary Register
*/
void LoadConstant(int n)
{
	//printf("\t MOVE #%d , D0\n",n);
	_segment[_pc++].op = Push;
	_segment[_pc++].value = n;
	//_stack[_stackp++] = n;
}



/*
Function Name: LoadVariable
Return Type: void
Purpose: Does not return a value
Input Parameter: char *
Purpose: Used to load a string
Function Purpose: Load a Variable to Primary Register
*/
void LoadVariable(char * Name)
{

	if(!(InTable(Name)))
	{
		Undefined(Name);
	}
	//printf("\t MOVE %s(PC),D0\n",Name);
	//_stack[_stackp++] = _svalue[_index];
	_segment[_pc++].op = Load;
	_segment[_pc++].index = _index;

}


/*
Function Name: Load
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose:
*/
void Load(void)
{
 _stack[_stackp++] = _svalue[_segment[_pc++].index];
}


/*
Function Name: Inc
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose:
*/
void Inc(void)
{
 _stack[_stackp] = _svalue[_segment[_pc++].index];
 _stack[_stackp++]++;
}




/*
Function Name: Push
Return Type: void
Purpose:  Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Push Primary onto Stack
*/
void Push(void)
{
	//printf("\t MOVE D0, -(SP)\n");
	_stack[_stackp++] = _segment[_pc++].value;
}



/*
Function Name: PopAdd
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Add Top of Stack to Primary
*/
void PopAdd()
{
	//	printf("\t ADD (SP)+, D0)\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left + right;
}



/*
Function Name: PopSub
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Subtract Primary from Top of Stack
*/
void PopSub()
{
	//printf("\t SUB (SP)+, D0\n");
	//printf("\t NEG D0\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left - right;
}



/*
Function Name: PopMul
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Multiply Top of Stack by Primary
*/
void PopMul()
{
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left * right;
}



/*
Function Name: PopDiv
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Divide Top of Stack by Primary
*/
void PopDiv()
{
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	if(right == 0)
		Abort("Divide by 0 error => the right term is 0");
	_stack[_stackp++] = left / right;
}


/*
Function Name: PopModulus
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Modulus Top of Stack with primary
*/
void PopModulus()
{
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	if(right == 0)
		Abort("Divide by 0 error => the right term is 0");
	_stack[_stackp++] = left % right;
}



/*
Function Name: PopAnd
Return Type:
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: AND Top of Stack with Primary
*/
void PopAnd()
{
	//printf("\t AND (SP)+, D0\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left & right;

}



/*
Function Name: PopOr
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
function Purpose: OR Top of Stack with Primary
*/
void PopOr()
{
	//printf("\t OR (SP)+, D0\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left | right;

}



/*
Function Name: PopXor
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: XOR Top of Stack with Primary
*/
void PopXor()
{
	//printf("\t EOR (SP)+, D0\n");
	 int left,right;
 right = _stack[--_stackp];
 left = _stack[--_stackp];
 _stack[_stackp++] = left ^ right;

}



/*
Function Name: PopCompare
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Compare Top of Stack with Primary
*/
void PopCompare()
{
	//printf("\t CMP (SP)+, D0\n");
	//int left,right;
	//right = _stack[--_stackp];
	//left = _stack[--_stackp];
	//_stack[_stackp++] = left > right;

}



/*
Function Name: SetEqual
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Set D0 If Compare was =
*/
void SetEqual()
{
	//printf("\t SEQ D0\n");
	//printf("\t EXT D0\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left == right;

}



/*
Function Name: SetNotEqual
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Set D0 If Compare was !=
*/
void SetNotEqual()
{
	//	printf("\t SNE D0\n");
	//	printf("\t EXT D0\n");
	int left,right;
	right = _stack[--_stackp];
	left = _stack[--_stackp];
	_stack[_stackp++] = left != right;
}


/*
Function Name : Error
Return Type : void
Purpose : Does not return a value
Input Parameter : char *
Purpose : String to be printed
Function Purpose : Error reporting function
*/
void Error(char * Str)
{
 printf("\t Line : %d Error : %s !\n",_lineCounter,Str);
}



/*
Function Name : Abort
Return Type : void
Purpose : Does not return a value
Input Paramater : char *
Purpose : string to be printed
Function Purpose : Function to report error and exit
*/
void Abort(char * Str)
{
	Error(Str);
	if(_file)
		fclose(_file);
	exit(0);
}


/*
Function Name : Expected
Return Type : Void
Purpose : does not return a value
Input Paramater : char *
Purpose : string to be printed
Function Purpose : Used to print message in error generation
*/
void Expected(char * Str)
{
	printf("\t Line : %d Error : %s ! \" Expected \" \n",_lineCounter,Str);
	if(_file)
	fclose(_file);
	exit(0);
}



/*
Function Name: Undefined
Return Type: void
Purpose: Does not return a value
Input Parameter: char *
Purpose: String to be printed
Function Purpose: Used to print message for undefined identifier
*/
void Undefined(char * Str)
{
	printf("\n\t Line : %d Error : %s ! \" Undefined \" \n",_lineCounter,Str);
	if(_file)
		fclose(_file);
	exit(0);
}


/*
Function Name: Header
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: For writing header info
*/
void Header()
{
	// printf(" WARMST,TAB,EQU $ A01E \n");
	_pc = 0;
	_stackp = 0;
}


/*
Function Name: Epilog
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: For the epilog
*/
void Epilog()
{
	 //printf("\t DC WARMST \n");
}

/*
Function Name: Prolog
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: For the prolog
*/
void Prolog()
{
	//PostLabel("MAIN\n");
}

/*
Function Name: Emit
Return Type: void
Purpose: Does not return a value
Input Parameter: char *
Purpose:
Function Purpose: Output a string with tab
*/
void Emit (char * s)
{
	printf("\t %s\n",s);
}


/*
Function Name: EmitLine
Return Type: void
Purpose: Does not return a value
Input Parameter: char *
Purpose:
Function Purpose: Output a string with Tab and CRLF
*/
void EmitLine(char * s)
{
	Emit(s);
	printf("\n");
}



/*
Function Name: NewLabel
Return Type: char *
Purpose: Return the label
Input Parameter: void
Purpose:
Function Purpose: Generate a unique label
*/
char * NewLabel(void)
{
	char s[20];
	char label[20];
	itoa(_lineCount,s,10);
	strcpy(label,"L");
	strcat(label,s);
	//_L[_lineCount++] = _pc;
	_lineCount++;
	return(label);
}


/*
Function Name: PostLabel
Return Type: void
Purpose: Does not return a value
Input Parameter: char *
Purpose: String to be printed
Function Purpose: Post a label to output
*/
void  PostLabel (char * L)
{
	printf ("\n %s :",L);
}

/*
Function Name: NegativeFactor
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose:
*/
void NegativeFactor(void)
{
	Match('-');
	if( IsDigit(_lookAhead) )
	{
		GetNum();LoadConstant(atoi(_value));
	}
	else
	{
		Factor();
		Negate();
	}
}


/*
Function Name : Expression
Return Type : void
Purpose : Does not return a value
Input Parameter : void
Purpose : Parse and translate a mathematical expression
*/
void Expression(void)
{
	//int old_pc = _pc;
	/*
   if(IsAddOp(_lookAhead))
		EmitLine("CLR D0");
	else
		Term();
	*/
	FirstTerm();
	while(IsAddOp(_lookAhead))
	{
		//Push();
		switch(_lookAhead)
		{
			case '+': Add();
                   break;
			case '-': Substract();
						 break;
			default:  Expected("Addop");
		}
	}
	//Eval(old_pc);
}


/*
Function Name: Equal
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate a relation equals
*/
void  Equal(void)
{
	Match('=');
	Expression();
	//PopCompare();
	_segment[_pc++].op = SetEqual;
}


/*
Function Name: LessOrEqual
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate a relation less than or equals
*/
void LessOrEqual(void)
 { Match('=');
  Expression();
 // PopCompare();
  _segment[_pc++].op = SetLessOrEqual;
}



/*
Function Name: NotEquals
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate a Relation "Not Equals" */
void NotEquals(void)
{
	Match('#');
	Expression();
	//PopCompare();
	_segment[_pc++].op = SetNotEqual;
}



/*
Function Name: Less
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate a relation less than
*/
void Less(void)
{
	Match('<');
	switch(_lookAhead)
	{
		case '=': LessOrEqual();
      			 break;
		default : Expression();
					 //PopCompare();
					 _segment[_pc++].op = SetLess;
					 break;
	}

}



/*
Function Name: Greater
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate a relation greater than
*/
void Greater(void)
{
	Match('>');
	if (_lookAhead=='=')
	{
		Match('=');
		Expression();
		//PopCompare();
		_segment[_pc++].op = SetGreaterOrEqual;
	}
	else
	{
		Expression();
		//PopCompare();
		_segment[_pc++].op = SetGreater;
	}
}



/*
Function Name: Relation
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Parse and translate a Relation
*/
void Relation(void)
{
	Expression();
	if (IsRelOp(_lookAhead))
	{
		//Push();
		switch(_lookAhead)
		{
			case '=' : Equal();
         			  break;
			case '#' : NotEquals();
         			  break;
			case '<' : Less();
         			  break;
			case '>' : Greater();
         			  break;
		}
	}
}


/*
Function Name: NotFactor
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Parse and Translate a Boolean Factor with Leading NOT
*/
void NotFactor(void)
{
	if (_lookAhead=='!')
	{
		Match('!');
		Relation();
		_segment[_pc++].op = NotIt;
	}
	else
		Relation();
}



/*
Function Name: BoolTerm
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Parse and Translate a Boolean Term
*/
void BoolTerm(void)
{
	NotFactor();
	while (_lookAhead=='&')
	{
		//Push();
		Match('&');
		NotFactor();
		_segment[_pc++].op = PopAnd;
	}
}


/*
Function Name: BoolOr
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and Translate a Boolean OR
*/
void BoolOr(void)
{
	Match('|');
	BoolTerm();
	//PopOr();
	_segment[_pc++].op = PopOr;
}



/*
Function Name: BoolXor
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and Translate an Exclusive Or
*/
void BoolXor(void)
{
	Match('^');
	BoolTerm();
	_segment[_pc++].op = PopXor;
	//PopXor();
}



/*
Function Name: BoolExpression
Return Type: void
Purpose: Does not return a value
Input Parameter: integer
Purpose:
Function Purpose: Parse and Translate a Boolean Expression
*/
void BoolExpression(int eval = 0)
{
	int old_pc = _pc;
	BoolTerm();
	while (IsOrOp(_lookAhead))
	{
		//Push();
		switch(_lookAhead)
		{
			case '|': BoolOr();
         			 break;
			case '^': BoolXor();
         			 break;
		}
	}
	if(eval)
		Eval(old_pc);
}


/*
Function Name : Assignment
Return Type : void
Purposee : does not return a value
Input Parameter : integer
Purpose :
Function Purpose: Parse and Translate an Assignment Statement
*/
void Assignment(int eval = 0)
{
	char Name[30];
	strcpy(Name,_value); SkipWhite();
	Match('=');
	BoolExpression(eval);
	int old_pc = _pc;
	_index = LookUp(_st,Name,_numEntry);
	_segment[_pc++].op = Store;
	_segment[_pc++].index = _index;
	//Store(Name);
	if(eval)
		Eval(old_pc);
}




/*
Function Name: DoIf
Return Type: void
Purpose: Does not return a value
Input Parameter: integer , integer
Purpose:
Function Purpose: Recognize and translate an IF construct
*/
void DoIf(int eval = 0,int l = 0)
{
	char L1[30], L2[30];
	_true = false;
	_lineLevel = 1;
	//for(int i = 1;i <= _levels;i++)
	//	printf("\t");
	BoolExpression(eval);
	strcpy(L1,NewLabel());
	strcpy(L2,L1);
	int old_pc = _pc;
	int l1,l2;
	l1	= _lineCount - 1;
	l2 = l1;
	//BranchFalse(L1,l1);
	_segment[_pc++].op = BranchFalse;
	_segment[_pc++].value = l1;
	Block("",0,l);
	if (_token=='l')
	{
		strcpy(L2,NewLabel());
		l2 = _lineCount - 1;
		//Branch(L2,l2);
		//PostLabel(L1);
		_segment[_pc++].op = Branch;
		_segment[_pc++].value = l2;
		_L[l1] = _pc;
		//_pc = _L[l1];
		 Block("",0,l);
	}
   //PostLabel(L2);
	//_pc = _L[l2];
	_L[l2] = _pc;
	MatchString("ENDIF");
	_levels--;_lineLevel = 0;
	if(eval)
		Eval(old_pc);
}



/*
Function Name: DoWhile
Return Type: void
Purpose: Does not return a value
Input Parameter: integer , integer
Purpose:
Function Purpose: Parse and Translate a WHILE Statement
*/
void DoWhile(int eval = 0,int l = 0)
{
	char L1[30], L2[30];
	int l1,l2;
	strcpy(L1,NewLabel());
	l1 = _lineCount - 1;
	strcpy(L2,NewLabel());
	l2 = _lineCount - 1;
	int old_pc = _pc;
	//PostLabel(L1);
	_L[l1] = _pc;
	BoolExpression(eval);
	_segment[_pc++].op = BranchFalse;
	_segment[_pc++].value = l2;
	//BranchFalse(L2);
	Block("",0,l2);
	MatchString("ENDWHILE");
	_segment[_pc++].op = Branch;
	_segment[_pc++].value = l1;
	//Branch(L1);
	//PostLabel(L2);
	_L[l2] = _pc;
	_levels--;
	if(eval)
		Eval(old_pc);
}


/*
Function Name: DoLoop
Return Type: void
Purpose: Does not return a value
Input Parameter: integer , integer
Purpose:
Function Purpose: DoLoop is an infinite loop , normally from which a
                  only a break statement can cause an exit
*/
void DoLoop(int eval = 0,int l = 0)
{
	// use label L1 to mark the beginning of the looping block
	// use label L2 to mark th end of the looping block
	// and will be used by the break and Block functions
	char L1[20], L2[20];
	int l1,l2;
	// try to match the DoLoop token ( 'p' )
	//Match('p');
	// generate dynamic addresses
	strcpy(L1,NewLabel());
	l1 = _lineCount - 1;
	strcpy(L2,NewLabel());
	l2 = _lineCount - 1;
	// print the start of loop block label
	//PostLabel(L1);
	int old_pc = _pc;
	_L[l1] = _pc;
	Block("",0,l2);
	// try to find the end of block
	MatchString("ENDLOOP");
	//char temp[20];
	//strcpy(temp,"BRA ");
	//strcat(temp,L1);
	_segment[_pc++].op = Branch;
	_segment[_pc++].value = l1;
	//EmitLine(temp);
	// print the end of loop block label
	//PostLabel(L2);
	_L[l2] = _pc;
	_levels--;
	if(eval)
		Eval(old_pc);
}



/*
Function Name: DoRepeat
Return Type: void
Purpose: Does not return a value
Input Parameter: integer , integer
Purpose:
Function Purpose: The DoRepeat function is similar in nature to the do while
						loop found in the 'c' programming language
*/
void DoRepeat(int eval = 0,int l = 0)
{
	// use label L1 to mark the beginning of the looping block
	// use label L2 to mark th end of the looping block
	// and will be used by the break and Block functions
	char L1[20], L2[20];
	//Match('r');
	// generate dynamic addresses
	int l1,l2;
	strcpy(L1,NewLabel());
	l1 = _lineCount - 1;
	strcpy(L2,NewLabel());
	l2 = _lineCount - 1;

   //PostLabel(L1);
	int old_pc = _pc;
	_L[l1] = _pc;
	Block("",0,l2);
	// check for a condition , similar in nature to the
	// do while loop
	MatchString("UNTIL");_levels--;
	BoolExpression(eval);
	//char temp[20];
	//strcpy(temp,"BRA ");
	//strcat(temp,L1);
	//EmitLine(temp);
	_segment[_pc++].op = BranchTrue;
	_segment[_pc++].value = l2;
	_segment[_pc++].value = l1;
	//PostLabel(L2);
	_L[l2] = _pc;
	if(eval)
		Eval(old_pc);
}


/*
Function Name: DoFor
Return Type: void
Purpose: Does not return a value
Input Parameter: integer , integer
Purpose:
Function Purpose: The for loop construct is handled by this function it parses
						for loop structure of the form
                  for name = expression1 expression2
					   where name is the variable which holds the value
			  		   of expression1 initially and then as the loop iterates till
                  the value of expression2
*/
void DoFor(int eval = 0,int l = 0)
{
	// use label L1 to mark the beginning of the looping block
	// use label L2 to mark th end of the looping block
	// and will be used by the break and Block functions

   char L1[20], L2[20];
	char Name[20];
	// used to represent for
	//Match('f');
	// generate dynamic addresses
	int l1,l2;
	strcpy(L1,NewLabel());
	l1 = _lineCount - 1;
	strcpy(L2,NewLabel());
	l2 = _lineCount - 1;
	// for name
	GetName();
	strcpy(Name,_value);
	// for name =
	Match('=');
	// for name = expression1
	BoolExpression(eval);
	//char temp[32];
	//char str[20];
	// decrement 1 from the expression stored in D0 to indicate
	// an entry into the loop
	int index;
	if(!(InTable(Name)))
	{
		Undefined(Name);
	}
	index = _index;
	_segment[_pc++].op = Store;
	_segment[_pc++].index = index;
	int old_pc;
	_L[l1] = _pc;
	_segment[_pc++].op = Load;
	_segment[_pc++].index = index;

	//EmitLine("SUBQ #1,D0");
	// load the address of variable name in A0 and perform loop
	// initialization
	//strcpy(temp,"LEA ");
	//strcat(temp,Name);
	//strcat(temp,"(PC),A0");
	//EmitLine(temp);
	// for name = expression1 expression2
	Scan();
	MatchString("TO");
	BoolExpression(eval);
	// store the loop terminating expression on the stack
	//EmitLine("MOVE D0,-(SP)");
	//PostLabel(L1);
	//_L[l1] = _pc;
	_segment[_pc++].op = SetLessOrEqual;
	_segment[_pc++].op = BranchFalse;
	_segment[_pc++].value = l2;
	// reinitialize the temp and str string
	//strcpy(temp,"");
	//strcpy(str,"");
	//strcpy(temp,"LEA ");
	//strcat(temp,Name);
	// move the value of name variable in d0 and increment d0
	// and restore the value back in memory
	// EmitLine("MOVE (A0),D0");
	// EmitLine("ADDQ #1,D0");
	// EmitLine("MOVE D0,(A0)");

	// check for termination condition by comparing the value of
	// expression1 stored in D0 with the value of expression2
	// stored in stack
	//EmitLine("CMP (SP),D0");
	//strcpy(temp,"");
	// if condition failed jump to L2
	//strcpy(temp,"BGT ");
	//strcat(temp,L2);
	// EmitLine(temp);
	Block("",0,l2);
	_segment[_pc++].op = Inc;
	_segment[_pc++].index = index;
	_segment[_pc++].op = Store;
	_segment[_pc++].index = index;
	//_segment
	//_svalue[index]++;
	MatchString("ENDFOR");
	//strcpy(temp,"");
	// if value of name is less than expression2 jump to L1
	//strcpy(temp,"BRA ");
	//strcat(temp,L1);
	//EmitLine(temp);
	//PostLabel(L2);
	_segment[_pc++].op = Branch;
	_segment[_pc++].value = l1;
	_L[l2] = _pc;
	_levels--;
	// pop the expression2 value stored in stack
	//EmitLine("ADDQ #2,SP");
	if(eval)
		Eval(old_pc);
}



/*
Function Name: DoDo
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: This function corresponds to the do loop found in the
  						c programming language its token structure is
						do condition
						begin
                  block
						end
*/
void DoDo(void)
{
	// use label L1 to mark the beginning of the looping block
	// use label L2 to mark th end of the looping block
	// and will be used by the break and Block functions

	char L1[20], L2[20];
	// match token
	//Match('d');
   // generate dynamic addresses
	strcpy(L1,NewLabel());
	strcpy(L2,NewLabel());
	// check expression
	BoolExpression();
	// decrement the expression1 value stored in D0 to mark the
	// entry of loop
	EmitLine("SUBQ #1,D0");
	PostLabel(L1);
	// also push the expression1 value in stack
	EmitLine("MOVE D0,-(SP)");
	Block("",0,0);
	EmitLine("MOVE (SP)+,D0");
	// pop the expression value back in D0
	char temp[32];
	// if the expression value is greater than zero goto label L1
	strcpy(temp,"DBRA D0");
	strcat(temp,L1);
	EmitLine(temp);
	// reset the stack
	MatchString("ENDDO");
	EmitLine("SUBQ #2,SP");
	PostLabel(L2);
	EmitLine("ADDQ #2,SP");
}


/*
Function Name: DoBreak
Return Type: void
Purpose: Does not return a value
Input Parameter: char * . integer
Purpose:
Function Purpose: Similar to the break statement in C
		  				it jumps to the label L passed to it .
*/
void DoBreak(char * L,int l = 0)
{
	//Match('b');
	// branch to the label L
	//char temp[32];
	//strcpy(temp,"BRA ");
	//strcat(temp,L);
	//EmitLine(temp);
	_segment[_pc++].op = Branch;
	_segment[_pc++].value = l;
}



/*
Function Name: DoRead
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Process a Read Statement
*/
void DoRead(void)
{
	SkipWhite();
	Match('(');
	GetName();SkipWhite();
	if(( _index = LookUp(_st,_value,_numEntry)) != 0)
	{
		_segment[_pc++].op = ReadVar;
		_segment[_pc++].index = _index;
	}

	else Abort("Not a Valid variable !");
	while (_lookAhead==',')
	{
		Match(',');
		GetName();SkipWhite();
		if(( _index = LookUp(_st,_value,_numEntry)) != 0)
		{
			_segment[_pc++].op = ReadVar;
		 	_segment[_pc++].index = _index;
      }
		else
      	Abort("Not a Valid variable !");

	}
	Match(')');
}



/*
Function Name: DoRead
Return Type: void
Purpose: Does not return a value
Input Parameter: integer
Purpose:
Function Purpose: Process a Write Statement
*/
void DoWrite(int eval = 0)
{
	int old_pc;
	SkipWhite();
	Match('(');
	if(_lookAhead == '"')
	{
		SkipMessage();
	}
	else
	{
		BoolExpression(1);SkipWhite();
		old_pc = _pc;
		_segment[_pc++].op = WriteVar;
		//Eval(old_pc);
		while (_lookAhead==',')
		{
			Match(',');
			BoolExpression(eval);SkipWhite();
			//old_pc = _pc;
		   _segment[_pc++].op = WriteVar;
			//Eval(old_pc);
		}
	}
	Match(')');
	if(eval)
		Eval(old_pc);
}




/*
Function Name: Block
Return Type: void
Purpose: Does not return a value
Input Parameter: char * , integer , integer
Purpose:
Function Purpose: Depending upon the look ahead variable the construct to be
						chosen is decided and the corresponding loop is executed
*/
void Block(char * L,int eval = 0,int l = 0)
{
	Scan();
	while(!(_token == 'e' || _token == 'l' || _token == 'u'))
	{
		//Scan();//Fin();
		switch(_token)
		{
			case 'i': _levels++;DoIf(eval,l);
         			 break;
			case 'R': DoRead();
         			 break;
			case 'W': DoWrite(eval);
         			 break;
         case 'v': Decl();
         			 break;
         case 'w': _levels++;DoWhile(eval,l);
         			 break;
			case 'p': _levels++;DoLoop(eval,l);
         			 break;
         case 'r': _levels++;DoRepeat(eval,l);
         			 break;
         case 'f': _levels++;DoFor(eval);
         			 break;
         //case 'd': DoDo();break;
			case 'b': DoBreak(L,l);
         			 break;
			default : Assignment(eval);
		}
		Scan();//Fin();
	}
}



/*
Function Name: Factor
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Parse and translate a math factor
*/
void Factor(void)
{
	SkipWhite();
	if (_lookAhead=='(')
	{
		Match('(');
		BoolExpression();
		Match(')');
	}

   else if (IsAlpha(_lookAhead))
	{
   	GetName();
		LoadVariable(_value);
	}
	else
	{
		GetNum();LoadConstant(_num);
	}
	SkipWhite();
}

/*
Function Name: FirstFactor
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Parse and translate a leading factor
*/
void FirstFactor(void)
{
	switch(_lookAhead)
	{
		case'+': Match('+');
				   Factor();
				   break;
		case'-': NegativeFactor();
      			break;
	 	default : Factor();
	}

}



/*
Function Name: Multiply
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate multiply
*/
void Multiply(void)
{
	Match('*');
	Factor();
	_segment[_pc++].op = PopMul;
}



/*
Function Name: Divide
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate a divide
*/
void Divide(void)
{
	Match('/');
	Factor();
   _segment[_pc++].op = PopDiv;
}



/*
Function Name: Modulus
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate modulus of a number
*/
void Modulus(void)
{
	Match('%');
	Factor();
	_segment[_pc++].op = PopModulus;
}


/*
Function Name: Subtract
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate a subtract
*/
void Substract(void)
{
	Match('-');
	Term();
	_segment[_pc++].op = PopSub;
}



/*
Function Name: Term1
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Common code used by term and first term
*/
void Term1(void)
{
	while (IsMulOp(_lookAhead))
	{
   	switch(_lookAhead)
		{
      	case '*': Multiply();
         			 break;
			case '%': Modulus();
         			 break;
			case '/': Divide();
         			 break;
		}
   }

}


/*
Function Name: Term
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Parse and translate a math term
*/
void Term(void)
{
	Factor();
	Term1();
}


/*
Function Name: FirsrTerm
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Parse and translate a leading factor
*/
void FirstTerm(void)
{
	FirstFactor();
	Term1();
}


/*
Function Name: Add
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate an add
*/
void Add(void)
{
	Match('+');
	Term();
	_segment[_pc++].op = PopAdd;
}


/*
Function Name: Subtract
Return Type: void
Purpose: Does not return a value
Input Parameter: void
Purpose:
Function Purpose: Recognize and translate a substract
*/
void Subtract(void)
{
	Match('-');
	Term();
	PopSub();
}


/*
Function Name : SkipWhite
Return Type : void
Purpose : does not return a value
Input Parameter : void
Purpose :
Function Purpose : Function to skip the whitespaces
*/
void SkipWhite(void)
{
	while(IsWhite(_lookAhead) )
		GetChar();
}



/*
Function Name : SkipComment
Return Type : void
Purpose : does not return a value
Input Parameter : void
Purpose :
Function Purpose : Function to skip the comments
*/
void SkipComment(void)
{

	_lookAhead = (_file) ? fgetc(_file) : getchar();
	int oldLookAhead;
	if(_lookAhead == '*')
	{
		oldLookAhead = _lookAhead;
		_lookAhead = (_file) ? fgetc(_file) : getchar();
		if(_lookAhead != '/')
		{
			_lookAhead = oldLookAhead;
			SkipComment();
		}
	}
	else
		SkipComment();
	SkipWhite();
}



/*
Function Name : ShowMessage
Return Type : void
Purpose : does not return a value
Input Parameter : void
Purpose :
Function Purpose : Function to show message
*/
void ShowMessage(void)
{
	int index = _segment[_pc++].index;
	for(int i = 0;_strings[index][i] != NULL;i++)
	{
		if(_strings[index][i] == '\\')
		{
			if(_strings[index][i+1] == 't')
			{
				printf("\t");i++;
			}
			if(_strings[index][i+1] == 'n')
			{
				printf("\n");i++;
			}
		}
		else
			printf("%c",_strings[index][i]);
	}
}



/*
Function Name : SkipMessage
Return Type : void
Purpose : does not return a value
Input Parameter : void
Purpose :
Function Purpose : Function to skip Message*/

void SkipMessage(void)
{
	char string[100];
	int ctr = 0;
	Match('"');
	while(_lookAhead != '"')
	{
		string[ctr++] = _lookAhead;
		GetChar();
	}
   string[ctr] = '\0';Match('"');
	if((_strings[_msgCount] = new char[ctr+1]) != NULL)
	strcpy(_strings[_msgCount],string);
	_segment[_pc++].op = ShowMessage;
	_segment[_pc++].index = _msgCount++;
}


/*
 this function returns the index of the keyword found in the
 key table , normally it starts from the bottom and goes to the
 top and tries to find the index
*/

int LookUp(symbol * _tablePtr,char* str,int n)
{
	  int i;
	  bool found;
	  found = false;
	  i = n;
	  while (i > 0 && found == false)
		{
		  if(strcmp(str,_tablePtr[i]) == 0)
				found = true;
		  else
			  i--;
		 }
	 return i;
}


/* Get an identifier and scan it for keywords */
void Scan (void)
{
	//if (_token=='x')
	GetName();
	_token = _keywordCode[LookUp(_keywordList,_value,NUMKEYWORDS - 1)]; //check
}


/*Match a specific Input String */
void MatchString(char*	str)
{
 if (strcmp(_value,str) != 0)
	Expected(str);
}


// check if the char is a * or a /
bool IsMulOp(char c)
{
 if(c == '*' || c == '/' || c == '%')
	return true;
 return false;
}

/*Recognize a Boolean Orop */
 bool IsOrOp (char c)
{ if (c=='|' || c=='^')
	  return 1;
 else return 0;
}


 /* Recognize a Relop */
 bool IsRelOp(char c)
 { switch(c)
		{ case '=' :
			case '#' :
			case '<' :
		  case '>' : return 1;
					  }
	  return 0;
 }


 bool IsWhite(char c)
 { if (c==' '||c=='\t'||c=='\n')
	{
	 if(c == '\n') {_lineCounter++;Ident(_lineCounter);}
	 return 1;
	}
	else return 0;
 }


 void NewLine(void)
 { if (_lookAhead=='\n') { GetChar();
									SkipWhite();
								  }
 }


 void Match(char x)
 {
	SkipWhite();
	if (_lookAhead==x)
	{
	 GetChar();
	}
	else
	{
	 printf("\n\t Line : %d Expected : %c",_lineCounter,x);exit(0);
	}

	if(_lookAhead != '\n')
	 SkipWhite();
  }


  /*locate symbol in table */
  int Locate(_symbol n)
  {  return LookUp(_st, n, MAX);
  }


  /* look for symbol in table. return index if not present */
  bool InTable(_symbol n)
	{
	 _index = 0;
	 if ((_index = LookUp(_st, n, _numEntry))!=0) return 1;
	 else return 0;
	}


  //add a new entry to symbol table
	void AddEntry(_symbol n, char t)
	{     if( InTable(n) )
			 {
			  printf("Duplicate Identifier %s\n",n);
			  exit(0);
			 }
			if( (_numEntry==MAX) )
				Abort("Symbol Table Full");
			 _numEntry++;
			 strcpy(_st[_numEntry],n);
			 _stype[_numEntry]=t;
			 // set the default value to 0
			 _svalue[_numEntry] = 0;
			}





/* Get an identifier */
void GetName (void)
{
	 SkipWhite();
	 if(!IsAlpha(_lookAhead))
	 {
		  Expected("Identifier");
	 }

	 _token='x';
	 strcpy(_value,"");
	 int i = 0;
	 while(isalnum(_lookAhead))
	 {
		_value[i] = toupper(_lookAhead);i++;
		 GetChar();
	 }
	 _value[i] = '\0';
	 Ident(_lineCounter);
}




//Get a Number
void GetNum(void)
{ SkipWhite();
  if (!IsDigit(_lookAhead))
	 Expected("Number");
  _token='#';
  strcpy(_value,"");
  int i=0;
  _num = 0;
  while (IsDigit(_lookAhead))
  { _num = (10 * _num) + (_lookAhead - '0');
	 i++;
	 GetChar();
	}
	//_value[i] = '\0';

}


/*procedure for getchar*/
void GetChar(void)
{
 if(!_file)
  _lookAhead = getchar();
 else
  _lookAhead = fgetc(_file);
  if(_lookAhead == '/')
 {
	 int oldLookAhead = _lookAhead;
	 _lookAhead = (_file) ? fgetc(_file) : getchar();
	if(_lookAhead == '*')
	{
		SkipComment();
		_lookAhead = (_file) ? fgetc(_file) : getchar();
	}
	else
		_lookAhead = oldLookAhead;
 }

}

/* check if token is alphabet */
bool IsAlpha(int Char)
{
 return isalpha(Char);
}

/* check if token is digit */
bool IsDigit(int Char)
{
 return isdigit(Char);
}

/*procedure for addop*/

bool IsAddOp(char c)
{
 if (c == '+' || c == '-')   //checks if the character is + or -
 return true;
 else
 return false;
}

/* procedure for isalnum*/
bool IsAlNum(char c)
{
	if(c == isalpha(c) || c == isdigit(c) )
		return true;
	else
		return false;
}

/* Parse and Translate a Data Declaration */

		 void Decl(void)
		 {
			 GetName();
			 Alloc(_value);
			 while (_lookAhead==',')
				{
				 Match(',');
				 GetName();
				 Alloc(_value);
				}
		 }




		 /* Parse and Translate Global Declarations */
		 void TopDecls(void)
		 {
			 Scan();
			 while (_token!='b')
				{ switch(_token)
				  {
					 case 'v': Decl();break;
					 default:  char temp[100];
								  strcpy(temp,"Unrecognized Keyword  ");
								  strcat(temp,_value) ;
								  Abort(temp);
								  break;
					}
				 Scan();
			  }
		 }


		 /* Allocate Storage for a Variable */

		 void Alloc(_symbol N)
		 {
			 if (InTable(N))
									{ char temp[100];
									  strcpy(temp,"Duplicate Varible Name ");
									  strcat(temp,N);
									  Abort(temp);
									 }

			 AddEntry(N, 'v');
			 //printf("%s :\t DC ",N);
			 SkipWhite();
			 if (_lookAhead=='=')
				{
				 Match('=');
				 if (_lookAhead=='-')
					 {  //printf("%c",_lookAhead);
						 Match('-');
					 }
				 GetNum();_svalue[_numEntry] = _num;
				 //printf("%d\n",_svalue[_numEntry]);
				}
			//printf("%d\n",_svalue[_numEntry]);
			SkipWhite();
		 }


/*-------------------------------------------------*/
/*Parse and Translate a Main Program */
/* main of tutorial */
		 void MainProg()
		 {  MatchString("BEGIN");
			 Prolog();
			 Block("",0,_lineCount);
			 MatchString("END");
			 Epilog();
		 }



	  /*  Parse and Translate a Program */
		/* prog of tutorial */
		 void Prog()
		 {
			 MatchString("PROGRAM");
			 Header();
			 TopDecls();
			 MainProg();

			 Match('.');

		 }



		 /* Initialize */
		 void Init()
		 {int i;
		  for (i=0;i<=MAX;i++)
				 {
				  strcpy(_st[i],"");
				  _stype[i] = ' ';
				 }
			 GetChar();
			 Scan();
			 _pc = 0;
		 }



		 void Initialize(void)
		 {
			_pc = 0;_stackp = 0;
			_num = 0;
			_lineCounter = 1;
			_lineCount = 0;
			_true = false;
			_levels = 0;
			_lineLevel = 0;
			_msgCount = 0;
		 }

		 void Start(void)
		 {
			Init();
			Prog();
			if (_lookAhead != '\n' && _lookAhead != EOF )
			 Abort("Unexpected data after . ");    //check

		 }


		 void Execute(void)
		 {
			Eval(0);
			getchar();
			if(_file)
			 fclose(_file);
		 }

		 void Process(void)
		 {
		  Initialize();
		  Start();
		  Execute();
		  for(int i = 0 ;i < _msgCount ; i++)
			  delete _strings[i];
		 }

		 void ShowInfo(void)
		 {
		  puts(_info);
		 }

		 void ShowError(int type)
		 {
		  printf("\nError : %s !",_errors[type]);
		  getchar();
		  exit(0);
		 }

		 /* Main Program */
		 void main(int argc,char* argv[])
		 {
		  if(argc == 1)
		  {
			ShowInfo();
		  }
		  else if(argc == 2)
		  {
			if(strcmp(strlwr(argv[1]),"run") == 0)
			{
			 //_file = fopen(stdin,"r+");
			 //if(_file != NULL)
				_file = NULL;
				Process();
			}
			else
			{
			 int len = strlen(argv[1]);
			 len--;
			 if(tolower(argv[1][len-2]) == '.' && tolower(argv[1][len-1]) == 's'
					&& tolower(argv[1][len]) == 'l')
			 {
			  if((_file = fopen(argv[1],"r")) != NULL)
			  {
				Process();
			  }
			  else
			  {
				ShowError(FILE_DOES_NOT_EXIST);
			  }
			 }
			 else
			 {
			  ShowError(UNKNOWN_FILE_TYPE);
			 }
			} 
		  }
		  else
		  {
			ShowError(UNKNOWN_OPTION);
		  }
		 }
















