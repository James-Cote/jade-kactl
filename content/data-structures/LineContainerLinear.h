/**
 * Author: Simon Lindholm - James Cote
 * Date: 2026-10-2026
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick''). When x is increasing and the slopes are decreasing it becomes O(1) amortized
 * Time: O(N) total
 * Status: stress-tested
 */
#pragma once

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer {
    typedef ll T;
    const T inf = 1e17;
    struct Line {
        T m, b, l, r;
        Line(T m, T b, T l, T r): m(m), b(b), l(l), r(r) {}
        T calc(T x) { return x*m + b; }
        T iter(Line& o) {
            assert(m != o.m);
            return (o.b - b) / (m - o.m);
        }
    };
    deque<Line> d;
    LineContainer() {}
    T query(T x) { // assume that x in increasing
        while (x > d.front().r) d.pop_front();
        d.front().l = -inf;
        return d.front().calc(x);
    }
    void add(T m, T b) { // assume that m is decreasing
        Line line(m, b, -inf, inf);
        while (!d.empty()) {
            T x = d.back().iter(line);
            line.l = x, d.back().r = x;
            if (d.back().r < d.back().l) d.pop_back();
            else break;
        }
        if (d.empty()) line.l = -inf;
        d.push_back(line);
    }
};