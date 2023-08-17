/**
 * &: アドレス演算子
 * *: 間接演算子
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    char* p = "123";
    printf("%c\n", *p);  // 1
    // printf("%c\n", p); // err:先頭アドレス値(int)を渡しているだけなので、有効な意味を持たない。
    printf("%p\n", &p);  // 先頭アドレス
    printf("%s\n", p);   // 123

    int i = strtol(p, &p, 10);  // これmutable な関数なのか...
    printf("%d\n", i);

    printf("-------------\n");
    char* p2 = "     12 34 aa    58 ";
    strtol(p2, &p2, 10);
    printf("p: %p, '%s'\n", &p2, p2);

    printf("-------------\n");
    char* s = " +";
    if (*s == '+') {
        printf("true\n");
    } else {
        printf("false\n");
    }
}