#include <stdio.h>

#include "robject.h"

void test_1();
void test_2();

int main(int argc, char * argv[]) {

    printf("--------- Begin Test for fomula.\n");
    test_1();
    printf("--------- Finish test.\n");

    printf("--------- Begin Test for Student/Teacher/Class.\n");
    test_2();
    printf("--------- Finish test.\n");

    return 0;
}

