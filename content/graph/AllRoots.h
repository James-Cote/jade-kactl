/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: All Roots template
 */
#pragma once
vi ews;
vector<pii> el;

struct ART {
    ll ans = 0;
    ll size = 0;
    ART operator+(const ART& otr) const {
        return {ans + otr.ans, size + otr.size};
    }
    ART promote(int x, int e) const { // x=node index, e=edge index
        int nsize = size + a[x];
        return {ans + nsize * ews[e], nsize};
    }
};
template<class T>
struct AllRoots {
    int n;
    vector<vector<pii>> adj;
    vector<vector<T>> pre, suf;
    AllRoots(vector<pii>& el) : n(sz(el)+1), adj(sz(el)+1), pre(sz(el)+1), suf(sz(el)+1) {
        rep(i,0,n-1){
            adj[el[i].first].pb({el[i].second,i});
            adj[el[i].second].pb({el[i].first,i});
        }
        rep(i,0,n) {
            pre[i].resize(adj[i].size() + 1);
            suf[i].resize(adj[i].size() + 1);
        }
    }
    T get(int x, int i = 0){
        T& v = suf[x][i+1];
        if(i) v = pre[x][i] + v; 
        return v.promote(x, adj[x][i].second);
    };
    T down(int x, int p = -1) {
        for(auto& c : adj[x]) if(c.first == p) swap(c, adj[x][0]);
        for(int i = adj[x].size()-1; i > -(p<0); --i)
            suf[x][i] = down(adj[x][i].first, x) + suf[x][i+1];
        return get(x);
    }
    void up(int x, int p = -1) {
        rep(i, p != -1, adj[x].size()) {
            pre[x][i+1] = pre[x][i] + get(adj[x][i].first);
            pre[adj[x][i].first][1] = get(x, i);
            up(adj[x][i].first, x);
        }
    }
    static vector<T> calc(vector<pii>& el) {
        AllRoots ar(el);
        ar.down(0);
        ar.up(0);
        vector<T> res(ar.n);
        rep(i,0,ar.n) res[i] = ar.pre[i].back(); // optional promote here.
        return res;
    }
}; 