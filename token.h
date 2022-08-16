#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <string>

using namespace std;

enum Names 
{
    UNDEF,
    ID,
    IF,
    THEN,
    ELSE,
    RELOP,
    LT,
    LE,
    GT,
    GE,
    EQ,
    NE,
    ARITHOP,
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,
    LBRACE,
    RBRACE,
    SEMICOLON,
    DOT,
    COMMA,
    NUMBER,
    INTEGER_LITERAL,//integer_literal
    FLOAT,//float_literal
    DOUBLE,//double_e_literal
    ATTRIB,
    FDA,//end_of_file
    CLASS,
    EXTENDS,
    INT,
    STRING,
    BREAK,
    PRINT,
    READ,
    RETURN,
    SUPER,
    FOR,
    NEW,
    CONSTRUCTOR
};

class Token 
{
    public: 
        int name;
        int attribute;
        string lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, string l)
        {
            this->name = name;
            attribute = UNDEF;
            lexeme = l;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};
