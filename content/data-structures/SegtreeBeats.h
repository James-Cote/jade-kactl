/**
 * Author: James Cote
 * Date: 2025-03-09
 * License: CC0
 * Description: Range max/min set, range sum, range add. 
 */
#pragma once

struct Node {
	Node *l = 0, *r = 0;
	ll lo, hi, mset = inf, madd = 0;
    ll mn = inf, nxtmn = inf, num_mn = 0;
	ll mx = -inf, nxtmx = -inf, num_mx = 0;
	ll sum = 0;
	Node(ll lo,ll hi):lo(lo),hi(hi),num_mn(hi-lo){}
	ll qsum(ll L, ll R) {
		if (R <= lo || hi <= L) return 0;
		if (L <= lo && hi <= R) return sum;
		push();
		return l->qsum(L, R) + r->qsum(L, R);
	}
	ll qmin(ll L, ll R) {
		if (R <= lo || hi <= L) return LLONG_MAX;
		if (L <= lo && hi <= R) return mn;
		push();
		return min(l->qmin(L, R), r->qmin(L, R));
	}
	ll qmax(ll L, ll R) {
		if (R <= lo || hi <= L) return LLONG_MIN;
		if (L <= lo && hi <= R) return mx;
		push();
		return max(l->qmax(L, R), r->qmax(L, R));
	}
    void update() {
        if (l->mn == r->mn) {
            mn = l->mn;
			num_mn = l->num_mn + r->num_mn;
            nxtmn = min(l->nxtmn, r->nxtmn);
        } else if (l->mn < r->mn) {
            mn = l->mn;
			num_mn = l->num_mn;
            nxtmn = min(l->nxtmn, r->mn);
        } else {
			mn = r->mn;
			num_mn = r->num_mn;
            nxtmn = min(l->mn, r->nxtmn);
        }
		if (l->mx == r->mx) {
            mx = l->mx;
			num_mx = l->num_mx + r->num_mx;
            nxtmx = max(l->nxtmx, r->nxtmx);
        } else if (l->mx > r->mx) {
            mx = l->mx;
			num_mx = l->num_mx;
            nxtmx = max(l->nxtmx, r->mx);
        } else {
			mx = r->mx;
			num_mx = r->num_mx;
            nxtmx = max(l->mx, r->nxtmx);
        }
		sum = l->sum + r->sum;
    }
	void set(ll L, ll R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            mn = mx = x, nxtmn = inf, nxtmx = -inf;
			num_mn = num_mx = hi-lo;
			sum = x*num_mn;
            mset = x;
        }
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			update();
		}
	}
    void maxset(ll L, ll R, ll x) {  // A = max(A, x)
		if (R <= lo || hi <= L || mn >= x) return;
		if (L <= lo && hi <= R && nxtmn > x) {
            sum -= num_mn*mn;
			if (mx == mn) mx = x;
			if (nxtmx == mn) nxtmx = x;
			mn = x;
            sum += num_mn*mn;
        }
		else {
			push(), l->maxset(L, R, x), r->maxset(L, R, x);
			update();
		}
	}
	void minset(ll L, ll R, ll x) {  // A = min(A, x)
		if (R <= lo || hi <= L || mx <= x) return;
		if (L <= lo && hi <= R && nxtmx < x) {
			sum -= num_mx*mx;
			if (mx == mn) mn = x;
			if (nxtmn == mx) nxtmn = x;
			mx = x;
            sum += num_mx*mx;
        }
		else {
			push(), l->minset(L, R, x), r->minset(L, R, x);
			update();
		}
	}
	void add(ll L, ll R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			sum += (hi-lo)*x;
			if (mn != inf) mn += x;
			if (nxtmn != inf) nxtmn += x;
			if (mx != -inf) mx += x;
			if (nxtmx != -inf) nxtmx += x;
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
		l->maxset(lo, hi, mn), r->maxset(lo, hi, mn);
		l->minset(lo, hi, mx), r->minset(lo, hi, mx);
		update();
	}
};