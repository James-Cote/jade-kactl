/**
 * Author: Simon Lindholm - James Cote
 * Date: 2026-10-22
 * License: CC0
 * Source: me
 * Description: Persistent Segment Tree with point wise updates
 * Time: O(\log N).
 * Usage: Node* tr = new Node(v, 0, sz(v));
 */
#pragma once

#include "../various/BumpAllocator.h"

const ll inf = 1e18;
struct Node {
    typedef ll T;
    static constexpr T unit = 0;
    Node *l = 0, *r = 0;
    ll lo, hi;
    T val;
    Node(ll lo,ll hi,ll val=unit):lo(lo),hi(hi),val(val){}
    T f(T a, T b) {return a + b;}
    void update() {val = f(l->val, r->val);}

    T query(ll L, ll R) {
        if (R <= lo || hi <= L) return unit;
        if (L <= lo && hi <= R) return val;
        return f(l->query(L, R), r->query(L, R));
    }
    Node* set(ll i, ll x) {
        if (i < lo || i >= hi) return this;
        if (lo+1 == hi) return new Node(lo, hi, x);
        else { 
            Node* ret = new Node(lo, hi);
            ret->l = l->set(i, x), ret->r = r->set(i, x);
            ret->update();
            return ret;
        }
    }
    void build() {
        if (!l && lo+1 != hi) {
            ll mid = lo + (hi - lo)/2;
            l = new Node(lo, mid); r = new Node(mid, hi);
            l->build(), r->build();
        }
    }
};