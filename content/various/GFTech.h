/**
 * Author: Shash
 * Description: GF deriv, integ, inv, etc. 
 */
typedef Mod mint;

vector<mint> deriv(const vector<mint>& v) {
  vector<mint> ret(v.size());
  rep(i, 1, sz(v)) ret[i-1] = (mint)i * v[i];
  return ret;
}

vector<mint> integ(const vector<mint>& v, mint ic) {
  vector<mint> ret(v.begin(),v.end());
  for(int i = sz(ret)-1; i > 0; i--) ret[i] = ret[i-1] / (mint)i;
  ret[0] = ic;
  return ret;
}

vector<mint> inv(const vector<mint>& v) {
  vector<mint> ret{(mint)1 / v[0]};
  for(int z = 2; z < sz(v)*2; z *= 2) {
    vector<mint> f = conv(ret, vector<mint>(v.begin(), min(v.begin()+z,v.end())));
    f.resize(z);
    for(auto& x : f) x = (mint)(-1) * x;
    f[0] = f[0] + 2;
    ret = conv(f, ret);
    ret.resize(z);
  }
  ret.resize(sz(v));
  return ret;
}

vector<mint> log(const vector<mint>& v) {
  vector<mint> ret = conv(deriv(v), inv(v));
  ret.resize(sz(v));
  return integ(ret,0);
}

vector<mint> exp(const vector<mint>& v) {
  vector<mint> ret{1};
  for(size_t z = 2; z < v.size() * 2; z *= 2) {
      vector<mint> f(v.begin(), min(v.begin()+z,v.end()));
      f.resize(z);
      f[0] = (f[0] + 1);
      ret.resize(z);
      vector<mint> lg = log(ret);
      rep(i, 0, z) f[i] = f[i] - lg[i];
      ret = conv(f, ret);
    }
    ret.resize(v.size());
    return ret;
}

pair<vector<mint>,vector<mint>> divmod(const vector<mint>& a, const vector<mint>& b) {
  int deg = a.size() - b.size() + 1;
  if (deg < 1) return {{0}, a};
  
  vector<mint> ar(a.rbegin(),a.rbegin()+deg);
  vector<mint> br(b.rbegin(),b.rend());
  br.resize(deg);
  auto dr = conv(ar,inv(br));
  vector<mint> d(dr.rend()-deg,dr.rend());
  
  vector<mint> ret = conv(d,b);
  rep(i, 0, sz(a)) ret[i] = a[i] - ret[i];
  ret.resize(b.size());
  return {d, ret};
}