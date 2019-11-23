#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <sched.h>
#include <unistd.h>

#define BUF_SIZE 1048576 // 1 MB
#define INIT_VAL 0
#define CHG_VAL 1
#define ALT_VAL 2

char bss_seg[BUF_SIZE];
char bss_seg_changing[BUF_SIZE];
char data_seg[BUF_SIZE] = {
    INIT_VAL,
};
char data_seg_changing[BUF_SIZE] = {
    INIT_VAL,
};

int main(int argc, char *argv[])
{
    char stack_seg[BUF_SIZE];
    char stack_seg_changing[BUF_SIZE];
    char *heap_seg = (char *)malloc(BUF_SIZE);
    char *heap_seg_changing = (char *)malloc(BUF_SIZE);
    char *heap_seg_calloc = (char *)calloc(INIT_VAL, BUF_SIZE);
    char *heap_seg_calloc_changing = (char *)calloc(INIT_VAL, BUF_SIZE);

    memset(bss_seg_changing, CHG_VAL, BUF_SIZE);
    memset(data_seg_changing, CHG_VAL, BUF_SIZE);
    memset(stack_seg_changing, CHG_VAL, BUF_SIZE);
    memset(heap_seg_changing, CHG_VAL, BUF_SIZE);
    memset(heap_seg_calloc_changing, CHG_VAL, BUF_SIZE);

    int pid = fork();
    if (pid) // 부모 프로세스
    {
        cpu_set_t cpu_using;
        CPU_ZERO(&cpu_using);
        CPU_SET(0, &cpu_using);
        sched_setaffinity(getpid(), sizeof(cpu_using), &cpu_using);

        // prevent context switching(global critical section)
        // clock1 = current clock cycle counter
        memset(bss_seg, ALT_VAL, BUF_SIZE);
        // clock2 = current clock cycle counter
        // release from global critical section
        // printing out (clock2 - clock1)
    }
    else // 자식 프로세스
    {
        cpu_set_t cpu_using;
        CPU_ZERO(&cpu_using);
        CPU_SET(1, &cpu_using);
        sched_setaffinity(getpid(), sizeof(cpu_using), &cpu_using);


    }

    return 0;
}