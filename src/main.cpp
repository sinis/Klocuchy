#include "klocuchy.h"

int main(int argc, char *argv[])
{
    // Unused parameter warning.
    argc = argc;
    argv = argv;

    Klocuchy klocuchy;
    int ret;

    if (!klocuchy.Initialize())
        return -1;

    ret = klocuchy.Exec();

    klocuchy.Unload();
    return ret;
}
