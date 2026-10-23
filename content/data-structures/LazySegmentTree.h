/**
 * Author: Simon Lindholm - James Cote
 * Date: 2026-10-26
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute max of intervals.
 * Can be changed to other things.
 * Use with a bump allocator for better performance, and SmallPtr or implicit indices to save memory.
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 * Status: stress-tested a bit
 */
#pragma once

#include "../various/BumpAllocator.h"

const ll inf = 1e18;
struct Node {
    typedef ll T;
    static constexpr T unit = -inf;
    Node *l = 0, *r = 0;
    ll lo, hi, mset = inf, madd = 0;
    T val = unit;
    Node(ll lo,ll hi):lo(lo),hi(hi){}
    T f(T a, T b) {return max(a, b);}
    void update() {val = f(l->val, r->val);}

    T query(ll L, ll R) {
        if (R <= lo || hi <= L) return unit;
        if (L <= lo && hi <= R) return val;
        push();
        return f(l->query(L, R), r->query(L, R));
    }
    void set(ll L, ll R, ll x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) mset = val = x, madd = 0;
        else {
            push(), l->set(L, R, x), r->set(L, R, x);
            update();
        }
    }
    void add(ll L, ll R, ll x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            if (mset != inf) mset += x;
            else madd += x;
            val += x;
        }
        else {
            push(), l->add(L, R, x), r->add(L, R, x);
            update();
        }
    }
    void push() {
        if (!l) {
            ll mid = lo + (hi - lo)/2;
            l = new Node(lo, mid); r = new Node(mid, hi);
        }
        if (mset != inf)
            l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
        else if (madd)
            l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
    }
};