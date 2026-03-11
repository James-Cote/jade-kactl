#pragma once
/**
 * Author: Andrew He, chilli
 * Date: 2019-05-07
 * License: CC0
 * Source: folklore
 * Description: Minkowski sum of n convex polygons. Each one needs to be in CCW order.
 * Time: O(NlogN)
 * Status: stress-tested
 */
#pragma once
#include "Point.h"
#include "PolarSort.h"

vector<P> minkowski(vector<vector<P>> &poly) {
    vector<P> D;
    P cur(0, 0);
    // Compute the offsets for each polygon
    for (auto &pts: poly) {
        int n = sz(pts);
        Point mn = pts[0];
        rep(i, 0, n) {
            mn = min(mn, pts[i]);
            P d = pts[(i + 1) % n] - pts[i];
            if (d.x == 0 && d.y == 0) continue;
            D.pb(delta);
        }
        cur = cur + mn;
    }
    vector<P> ans;
    sort(all(D), polarcomp); // Sort offsets by angle
    for (auto &d: D) {
        ans.push_back(cur);
        cur = cur + d;
    }
    if (!sz(ans)) return {cur};
    return ans;
}