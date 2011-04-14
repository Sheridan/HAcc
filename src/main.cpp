#include "st.h"

int main(int argc, char ** argv)
{
        HACC_SINGLETONE->setCommandLine(argc, argv);
        int r = HACC_APPLICATION->run();
        delete HACC_SINGLETONE;
        return r;
}

