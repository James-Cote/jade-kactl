/**
 * Author: James Cote
 * Date: 2025-03-09
 * License: CC0
 * Description: Range min set with sum query (can change to max set or max query or min query)
 */
#pragma once

const ll inf = 1e18;
struct Node {
    typedef ll T;
    static constexpr T unit = 0;
    Node *l = 0, *r = 0;
    ll lo, hi, mset = inf, madd = 0;
    T val = unit;
    ll mx = inf, smx = -inf, cnt = 0;
    Node(ll lo,ll hi):lo(lo),hi(hi),cnt(hi-lo){}
    T f(T a, T b) {return a + b;}
    void update() {
        val = f(l->val, r->val);
        mx = max(l->mx, r->mx);
        smx = max(l->smx, r->smx);

        cnt = 0;
        if (l->mx == mx) cnt += l->cnt;
        else smx = max(smx, l->mx);
        if (r->mx == mx) cnt += r->cnt;
        else smx = max(smx, r->mx);
    }

    T query(ll L, ll R) {
        if (R <= lo || hi <= L) return unit;
        if (L <= lo && hi <= R) return val;
        push();
        return f(l->query(L, R), r->query(L, R));
    }
    void set(ll L, ll R, ll x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) mset = x, val = x*(hi-lo), mx = x, smx = -inf, cnt = hi-lo, madd = 0;
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
            val += x*(hi-lo);
            mx += x;
            if (smx != -inf) smx += x;
        }
        else {
            push(), l->add(L, R, x), r->add(L, R, x);
            update();
        }
    }
    void setmn(ll L, ll R, ll x) {
        if (R <= lo || hi <= L || mx <= x) return;
        if (L <= lo && hi <= R && smx < x) {
            val -= (mx-x)*cnt;
            mx = x;
        }
        else {
            push(), l->setmn(L, R, x), r->setmn(L, R, x);
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
        l->setmn(lo, hi, mx), r->setmn(lo, hi, mx);
    }
};