#include "scanner.h"

//Construtor
Scanner::Scanner(string input)
{

    tabKeywords = new Token*[15];//número de palavras reservadas
    

    fillTable();

    /*this->input = input;
    cout << "Entrada: " << input << endl << "Tamanho: " 
         << input.length() << endl;*/
    pos = 0;
    line=1;

    ifstream inputFile(input, ios::in);
    string line;

    if(inputFile.is_open())
    {
        while(getline(inputFile, line))
        {
            this->input.append(line + '\n');
        }
        inputFile.close();
    }
    else
        cout <<"Unable to open file\n";

        cout <<this->input;


}

int
Scanner::getLine()
{
    return line;
}

//Método que retorna o próximo token da entrada
Token*
Scanner::nextToken()
{
    Token* tok;
    string lexeme;


    //Verifica se chegou no final do arquivo
    if(input[pos] == '\0')
    {
        tok = new Token(FDA);

        return tok;
    }

    //Consome espaços em branco
    while(isspace(input[pos]))
    {
          pos++;
          if(input[pos] == '\n')
             line++;
    }
    //Comentários
    if(input[pos] == '/')
    {
        if(input[pos + 1] == '/')//Comentário em linha
        {
            pos = pos + 2;
            while(input[pos] != '\n' && input[pos] != '\0')
                pos++;
            if(input[pos] == '\n')
               line++;       
        }
    
    else if(input[pos + 1] == '*')//Comentário em bloco
    {
        while(input[pos] != '*' && input[pos + 1] != '/' && input[pos] != '\0')
             pos++;
        if(input[pos] == '\0')
            lexicalError("Token mal formado");
     }
 }

    //Operadores relacionais
    if(input[pos] == '<'){
        pos++;

        if(input[pos] == '=')//<=
        {
            pos++;
            tok = new Token(RELOP, LE);
            return tok;
        }
        /*else if(input[pos] == '>')//<>
        {
            pos++;
            tok = new Token(RELOP, NE);
            return tok;
        }*/
        else//<
        {
            tok = new Token(RELOP, LT);
            return tok;
        }
    }
    else if(input[pos] == '=')//=
    {
        pos++;
        tok = new Token(RELOP, EQ);
        return tok;
    }
    else if(input[pos] == '>')
    {
        pos++;
        if(input[pos] == '=')//>=
        {
            pos++;
            tok = new Token(RELOP, GE);
            return tok;
        }
        else//>
        {
            tok = new Token(RELOP, GT);
            return tok;
        }
    }
    else if(input[pos] == '=')
    {
        pos++;
        if(input[pos] == '=')
        {
            pos++;
            tok = new Token(RELOP, EQ);
            return tok;
        }
        else
        {
            tok = new Token(ATTRIB);
            return tok;
        }
    }
    else if(input[pos] == '!')
    {
        pos++;
        if(input[pos] == '=')
        {
            pos++;
            tok = new Token(RELOP, NE);
            return tok;
        }
        else
        {
            lexicalError("Token mal formado");
        }
    }

    //Operadores aritméticos
    else if(input[pos] == '+')
    {
        pos++;
        tok = new Token(ARITHOP, PLUS);
        return tok;
    }
    else if(input[pos] == '-')
    {
        pos++;
        tok = new Token(ARITHOP, MINUS);
        return tok;
    }
    else if(input[pos] == '*')
    {
        pos++;
        tok = new Token(ARITHOP, MULT);
        return tok;
    }
    else if(input[pos] == '/')
    {
        pos++;
        tok = new Token(ARITHOP, DIV);
        return tok;
    }
    else if(input[pos] == '%')
    {
        pos++;
        tok = new Token(ARITHOP, MOD);
        return tok;
    }
    else if(input[pos] == '(')
    {
        pos++;
        tok = new Token(LPAREN);
        return tok;
    }
    else if(input[pos] == ')')
    {
        pos++;
        tok = new Token(RPAREN);
        return tok;
    }
    else if(input[pos] == '[')
    {
        pos++;
        tok = new Token(LBRACKET);
        return tok;
    }
    else if(input[pos] == ']')
    {
        pos++;
        tok = new Token(RBRACKET);
        return tok;
    }
    else if(input[pos] == '{')
    {
        pos++;
        tok = new Token(LBRACE);
        return tok;
    }
    else if(input[pos] == '}')
    {
        pos++;
        tok = new Token(RBRACE);
        return tok;
    }
    else if(input[pos] == ';')
    {
        pos++;
        tok = new Token(SEMICOLON);
        return tok;
    }
    else if(input[pos] == '.')
    {
        pos++;
        tok = new Token(DOT);
        return tok;
    }
    else if(input[pos] == ',')
    {
        pos++;
        tok = new Token(COMMA);
        return tok;
    }
    
    //Identificadores
    if(isalpha(input[pos]))
    {
        lexeme.push_back(input[pos]);
        pos++;

        while(isalnum(input[pos]))
        {
            lexeme.push_back(input[pos]);
              pos++;
        }
        //Busco na tabela para ver se é palavra reservada
        tok = search(lexeme);
        if(!tok)
           tok = new Token(ID);

        return tok;
    }

    //Números
    if(isdigit(input[pos]))
    {
        
        pos++;

        while(isdigit(input[pos]))
        
        
         pos++;
        
        bool isFloat = false;

        if(input[pos] == '.')
        {
            pos++;

            if(isdigit(input[pos]))
            {
                pos++;

                while(isdigit(input[pos]))
                      pos++;
            }
            else
                lexicalError("Token mal formado");

            isFloat = true;
        }

            if(input[pos] == 'E')
            {
                pos++;

                if(input[pos] == '+' || input[pos] == '-')
                   pos++;
                
                if(isdigit(input[pos]))
                {
                    pos++;
                    while(isdigit(input[pos]))
                          pos++;
                }
                else
                    lexicalError("Token mal formado");

                  tok = new Token(NUMBER, DOUBLE);
            }
                else if(isFloat)
                {
                  tok = new Token(NUMBER, FLOAT);
                }
                else
                {
                  tok = new Token(NUMBER, INTEGER_LITERAL);
                }

                  return tok;   
            }

            lexicalError("Token mal formado");

            tok = new Token(UNDEF);

            return tok;
}

void
Scanner::fillTable()
{
    tabKeywords[0] = new Token(IF, "if");
    tabKeywords[1] = new Token(THEN, "then");
    tabKeywords[2] = new Token(ELSE, "else");
    tabKeywords[3] = new Token(CLASS, "class");
    tabKeywords[4] = new Token(EXTENDS, "extends");
    tabKeywords[5] = new Token(INT, "int");
    tabKeywords[6] = new Token(STRING, "string");
    tabKeywords[7] = new Token(BREAK, "break");
    tabKeywords[8] = new Token(PRINT, "print");
    tabKeywords[9] = new Token(READ, "read");
    tabKeywords[10] = new Token(RETURN, "return");
    tabKeywords[11] = new Token(SUPER, "super");
    tabKeywords[12] = new Token(FOR, "for");
    tabKeywords[13] = new Token(NEW, "new");
    tabKeywords[14] = new Token(CONSTRUCTOR, "constructor");
}

Token*
Scanner::search(string lexeme)
{
    //cout << "Buscando " << lexeme << " ";

    for (int i = 0; i < 15; i++)
        if (lexeme.compare(tabKeywords[i]->lexeme) == 0)
            return tabKeywords[i];

    return 0;
}

void 
Scanner::lexicalError(string msg)
{
    cout << "Linha" << line << ";" << msg << endl;
    
    exit(EXIT_FAILURE);
}

Scanner::~Scanner()
{
    for (int i = 0; i < 15; i++)
        delete tabKeywords[i];

    delete[] tabKeywords;
}
