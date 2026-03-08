/**
 * Author: Ulf Lundstrom with inspiration from tinyKACTL
 * Date: 2009-04-14
 * License: CC0
 * Source:
 * Description: Sort based on CCW angle to negative x axis. Points on negative x are largest.
 * Doesn't work for (0, 0)
 */
#pragma once
#include "Point.h"

int section(P p) {
    if (p.x > 0 || (p.x == 0 && p.y > 0)) return 0;
    return 1;
}

bool polarcomp(P a, P b) {
    if (section(a) != section(b)) return section(a) < section(b);
    return a.cross(b) > 0;
}