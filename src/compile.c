#include "getSource.h"
#ifndef TBL
#define TBL
#include "table.h"
#endif
#include "codegen.h"

#define MINERROR 3
#define FIRSTADDR 2

static Token token;

static void block(int pIndex);
static void constDecl();
static void varDecl();
static void funcDecl();
static void statement();
static void expression();
static void term();
static void factor();
static void condition();
static int isStBeginKey(Token t);

// TODO

int compile()
{
    int i;
    printf("start compilation\n");
    initSource();
    token = nextToken();
    // TODO
    return i<MINERROR;
}