#include "utils.h"

bool getParameterValue(char *parameter, int argc, char *argv[], string *value)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(parameter, argv[i]) == 0)
        {
            if ((strcmp(parameter, "-f") == 0 ||
                 strcmp(parameter, "-o") == 0 ||
                 strcmp(parameter, "-i") == 0) &&
                i + 1 < argc)
            {
                *value = string(argv[i + 1]);
                return true;
            }
            else if ((strcmp(parameter, "-h") == 0 ||
                      strcmp(parameter, "-s") == 0))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}