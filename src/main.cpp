#include "klocuchy.h"

int main(int, char **)
{
    Klocuchy klocuchy;
    int ret;

    if (!klocuchy.Initialize())
        return -1;

    ret = klocuchy.Exec();

    klocuchy.Unload();
    return ret;
}
