#include "scanner.h"

string* vet;

void print(Token*);
void allocVetor();
void freeVetor();

int main(int argc, char* argv[]) 
{
    
    string input;
    
    getline(cin, input);

    Scanner* scanner = new Scanner(input);

    allocVetor();
    
    Token* t;

    if(argc != 2)
    
    do
    {
        t = scanner->nextToken();
        
        print(t);
    }while (t->name != FDA);

    cout << endl;

    freeVetor();

    delete scanner;

    return 0;
}

void allocVetor()
{
    vet = new string[45];

    vet[0] = "UNDEF";
    vet[1] = "ID";
    vet[2] = "IF";
    vet[3] = "THEN";
    vet[4] = "ELSE";
    vet[5] = "RELOP"; 
    vet[6] = "LT";
    vet[7] = "LE";
    vet[8] = "GT";
    vet[9] = "GE";
    vet[10] = "EQ";
    vet[11] = "NE";
    vet[12] = "ARITHOP";
    vet[13] = "PLUS";
    vet[14] = "MINUS";
    vet[15] = "MULT";
    vet[16] = "DIV";
    vet[17] = "MOD";
    vet[18] = "LPAREN";
    vet[19] = "RPAREN";
    vet[20] = "LBRACKET";
    vet[21] = "RBRACKET";
    vet[22] = "LBRACE";
    vet[23] = "RBRACE";
    vet[24] = "SEMICOLON";
    vet[25] = "DOT";
    vet[26] = "COMMA";
    vet[27] = "NUMBER";
    vet[28] = "INTEGER_LITERAL";
    vet[29] = "FLOAT";
    vet[30] = "DOUBLE";
    vet[31] = "ATTRIB";
    vet[32] = "FDA";
    vet[33] = "CLASS";
    vet[34] = "EXTENDS";
    vet[35] = "INT";
    vet[36] = "STRING";
    vet[37] = "BREAK";
    vet[38] = "PRINT";
    vet[39] = "READ";
    vet[40] = "RETURN";
    vet[41] = "SUPER";
    vet[42] = "FOR";
    vet[43] = "NEW";
    vet[44] = "CONSTRUCTOR";
   
}

void freeVetor()
{
    delete[] vet;
}

void print(Token* t)
{
    cout << vet[t->name];

    if (t->attribute != UNDEF)
        cout << "(" << vet[t->attribute] << ")";

    cout << " ";
}
