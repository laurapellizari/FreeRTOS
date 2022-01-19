#include <stdio.h>
#include "kernel.h"

char proc1(void){
    printf("Laura\n");
    return SUCCESS;
}

char proc2(void){
    printf("2019018756\n");
    return SUCCESS;
}

char proc3(void){
    printf("UNIFEI\n");
    return REPEAT;
}

char proc4(void){
    static int i = 0;
    printf("ECOS03\n");
    i++;
    return REPEAT;
}


void main(){
    
    process p1 = {proc1};
    process p2 = {proc2};
    process p3 = {proc3};
    process p4 = {proc4};
    kernelInit();
    
    if(kernelAddProc(&p1) == SUCCESS){
        printf("1st process added\n"); }
    if(kernelAddProc(&p2) == SUCCESS){
        printf("2nd process added\n"); }
    if(kernelAddProc(&p3) == SUCCESS){
        printf("3rd process added\n"); }
    if(kernelAddProc(&p4) == SUCCESS){
        printf("4th process added\n"); }
    kernelLoop();    
}