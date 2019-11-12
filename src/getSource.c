#include <stdio.h>
#include <string.h>
#include "getSource.h"

#define MAXLINE 120
#define MAXERROR 30
#define MAXNUM 14
#define TAB 5

static FILE *fpi;
static FILE *fptex;
static char line[MAXLINE];

static int lineIndex;
static char ch;

static Token cToken;
static KindT idKind;
static int spaces;
static int CR;
static int printed;

static int errorNo = 0;
static char nextChar();
static int isKeySym(KeyId k);
static int isKeyWd(KeyId k);
static void printSpaces();
static void printcToken();

struct KeyWd {
    char *word;
    KeyId keyId;
};

static struct KeyWd KeyWdT[] = {
    {"begin", Begin},
    {"end", End},
    {"if", If},
    {"then", Then},
    {"while", While},
    {"do", Do},
    {"return", Ret},
    {"function", Func},
    {"var", Var},
    {"const", Const},
    {"odd", Odd},
    {"write", Write},
    {"writeln", WriteLn},
    {"$dummy1", end_of_KeyWd},
    {"+", Plus},
    {"-", Minus},
    {"*", Mult},
    {"/", Div},
    {"(", Lparen},
    {")", Rparen},
    {"=", Equal},
    {"<", Lss},
    {">", Gtr},
    {"<>", NotEq},
    {"<=", LssEq},
    {">=", GtrEq},
    {",", Comma},
    {".", Period},
    {";", Semicolon},
    {":=", Assign},
    {"$dummy2", end_of_KeySym}
};
// TODO

int openSource(char fileName[])
{
    char fileNameO[30];
    if ( (fpi = fopen(fileName, "r")) == NULL) {
        printf("can't open %s\n", fileName);
        return 0;
    }
    strcpy(fileNameO, fileName);
    strcat(fileNameO, ".tex");
    if ( (fptex = fopen(fileNameO, "w")) == NULL) {
        printf("can't open %s\n", fileNameO);
        return 0;
    }
    return 1;
}

void closeSource()
{
    fclose(fpi);
    fclose(fptex);
}

void errorNoCheck()
{
    if (errorNo++ > MAXERROR) {
        fprintf(fptex, "too many errors\n\\end{document}\n");
        printf("abort compilation\n");
        exit(1);
    }
}

void errorType(char *m)
{
    // TODO
}

void errorInsert(KeyId k)
{
    // TODO
}

void errorMissingId()
{
    // TODO
}

void errorMissingOp()
{
    // TODO
}

void errorDelete()
{
    // TODO
}

void errorMessage(char *m)
{
    fprintf(fptex, "$^{%s}$", m);
    errorNoCheck();
}

void errorF(char *m)
{
    errorMessage(m);
    fprintf(fptex, "fatal errors\n\\end{document}\n");
    if (errorNo)
        printf("total %d errors\n", errorNo);
    printf("abort compilation\n");
    exit(1);
}

int errorN()
{
    return errorNo;
}

char nextChar()
{
    char ch;
    if (lineIndex == -1) {
        if (fgets(line, MAXLINE, fpi) != NULL) {
            puts(line);
            lineIndex = 0;
        } else {
            errorF("end of file\n"); // TODO
        }
    }
    if ((ch = line[lineIndex++]) == '\n') {
        lineIndex = -1;
        return '\n';
    }
    return ch;
}