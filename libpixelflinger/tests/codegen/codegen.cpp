#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" void ggl_test_codegen(
        int mode, uint32_t n, uint32_t p, uint32_t t0, uint32_t t1);

void usage_exit(const char *name)
{
    printf("usage: %s a|m 00000117:03454504:00001501:00000000\n", name);
    exit(1);
}

int main(int argc, char** argv)
{
    if (argc != 3 || (argv[1][0] != 'a' && argv[1][0] != 'm'  && argv[1][0] != 'b')) {
        usage_exit(argv[0]);
    }
    int      mode, acnt;
    uint32_t n;
    uint32_t p;
    uint32_t t0;
    uint32_t t1;
    if (argv[1][0] == 'a') mode = 1;
    else if (argv[1][0] == 'm') mode = 2;
    else mode = 3;  // both (mips with arm mixed)
    acnt = sscanf(argv[2], "%08x:%08x:%08x:%08x", &n, &p, &t0, &t1);
    if (acnt != 4) {
        // OK, try the alternate format-order that the ARM code prints out....
        // note that n & p are reversed in this one
        acnt = sscanf(argv[2], "%08x:%08x_%08x_%08x", &p, &n, &t0, &t1);
        if (acnt != 4) {
            usage_exit(argv[0]);
        }
    }
    ggl_test_codegen(mode, n, p, t0, t1);
    return 0;
}
