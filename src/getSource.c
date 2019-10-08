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