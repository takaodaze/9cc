#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    ND_ADD,
    ND_SUB,
    ND_MUL,
    ND_DIV,
    ND_NUM,
} NodeKind;

typedef struct Node Node;

struct Node {
    NodeKind kind;
    Node* lhs;  // 左辺 left-hand side
    Node* rhs;  // 右辺
    int val;    // kind: ND_NUM の場合のみに使用
};

// 二項演算子を扱う
Node* new_node(NodeKind kind, Node* lhs, Node* rhs) {
    Node* node = calloc(1, sizeof(Node));
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node* new_node_num(int val) {
    Node* node = calloc(1, sizeof(Node));
    node->kind = ND_NUM;
    node->val = val;
    return node;
}

Node* primary() {
    // 次のトークンが"("なら、"(" expr ")"のはず
    if (consume('(')) {
        Node* node = expr();
        expect(')');
        return node;
    }

    // そうでなければ数値のはず
    return new_node_num(expect_number());
}

Node* mul() {
    Node* node = primary();

    for (;;) {
        if (consume('*'))
            node = new_node(ND_MUL, node, primary());
        else if (consume('/'))
            node = new_node(ND_DIV, node, primary());
        else
            return node;
    }
}

/**
 * 一般的な x + y + z のような加算を考えるなら
 * この関数が返すのは右側の + に対応付くノードのポインタだろうか
 */
Node* expr() {
    Node* node = mul();

    for (;;) {
        if (consume('+'))
            node = new_node(ND_ADD, node, mul()); // arg1:kind, arg2:さっき生成したノード, arg3:これから生成するノード
        else if (consume('-'))
            node = new_node(ND_SUB, node, mul());
        else
            return node;
    }
}
typedef enum {
    TK_RESERVED,  // symbol
    TK_NUM,       // integer
    TK_EOF,       // end of input
} TokenKind;

typedef struct Token Token;

struct Token {
    TokenKind kind;
    Token* next;
    int val;
    char* str;
};

Token* token;  // current focus token

char* user_input;

void error_at(char* loc, char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    int pos = loc - user_input;
    fprintf(stderr, "%s\n", user_input);
    fprintf(stderr, "%*s", pos, " ");  // pos個の空白を出力
    fprintf(stderr, "^ ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

void error(char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// 次のトークンが期待する記号なら、読み進め、真を返す
// それ以外は偽を返す
bool consume(char op) {
    if (token->kind != TK_RESERVED || token->str[0] != op) return false;
    token = token->next;
    return true;
}

// 次のトークン期待する記号なら、読み進める
// それ以外はエラーで落とす
void expect(char op) {
    if (token->kind != TK_RESERVED || token->str[0] != op)
        error_at(token->str, "'%c'ではありません", op);

    token = token->next;
}

int expect_number() {
    if (token->kind != TK_NUM) error_at(token->str, "数ではありません");
    int val = token->val;
    token = token->next;
    return val;
}

bool at_eof() {
    return token->kind == TK_EOF;
}

// 新しいTokenを作り、curに繋げる
// 新しく繋げたtokenのポインタを返す
Token* new_token(TokenKind kind, Token* cur, char* str) {
    Token* tok = calloc(1, sizeof(Token));
    // callocはmallocと同じようにメモリを割り当てる関数です。mallocとは異なり、callocは割り当てられたメモリをゼロクリアします。ここでは要素をゼロクリアする手間を省くためにcallocを使うことにしました。
    tok->kind = kind;
    tok->str = str;

    cur->next = tok;
    return tok;
}

Token* tokenize() {
    // 先頭の構造体(ダミー)を宣言し、アドレスを確保。それを数珠繋ぎにする
    char* p = user_input;
    Token head;
    head.next = NULL;
    Token* cur = &head;

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (*p == '+' || *p == '-') {
            cur = new_token(TK_RESERVED, cur, p++);  // p++ で文字列のカーソルをついでに進める
            continue;
        }

        if (isdigit(*p)) {
            cur = new_token(TK_NUM, cur, p);
            cur->val = strtol(p, &p, 10);  // new_token() 内ではvalの設定をしていない。
            // ついでにstrtol() でpを読み進める
            continue;
        }

        error_at(p, "トークナイズできません");
    }

    new_token(TK_EOF, cur, p);
    return head.next;  // headはダミーなのでいらない
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "引数の個数が正しくありません\n");
        return 1;
    }

    user_input = argv[1];
    token = tokenize();

    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");

    // 式の最初は数でなくてはならない
    printf("  mov rax, %d\n", expect_number());  // 次の整数の後ろまで、ポインタを進める

    while (!at_eof()) {
        if (consume('+')) {
            printf("  add rax, %d\n", expect_number());
            continue;
        }

        expect('-');
        printf("  sub rax, %d\n", expect_number());
    }

    printf("  ret\n");
    return 0;
}