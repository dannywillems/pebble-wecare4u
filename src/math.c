#include <pebble.h>
#include "math.h"

double norme_2(AccelData data)
{
    return (data.x * data.x + data.y * data.y + data.z * data.z);
}