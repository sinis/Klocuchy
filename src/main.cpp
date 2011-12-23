#include <cstdlib>
#include <ctime>
#include "klocuchy.h"

int main(int, char **)
{
    Klocuchy klocuchy;
    int ret;

    srand(time(0));

    if (!klocuchy.Initialize())
        return -1;

    ret = klocuchy.Exec();

    klocuchy.Unload();
    return ret;
}
