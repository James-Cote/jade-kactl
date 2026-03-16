/**
 * Author: Takanori Maehara
 * License: CC0
 * Description: $O(n^2)$ Polygon Triangulation
 */

real triangulate(vector<point> ps) {
  int n = ps.size();
  vector<int> next(n);
  for (int i = 0; i < n-1; ++i) next[i] = i+1;
  auto is_ear = [&](int i, int j, int k) {
    if (sign(cross(ps[j]-ps[i], ps[k]-ps[i])) <= 0) return false;
    for (int l = next[k]; l != i; l = next[l])
      if (sign(cross(ps[i]-ps[l], ps[j]-ps[l])) >= 0
       && sign(cross(ps[j]-ps[l], ps[k]-ps[l])) >= 0
       && sign(cross(ps[k]-ps[l], ps[i]-ps[l])) >= 0) return false;
    return true;
  };
  real area = 0;
  for (int i = 0; next[next[i]] != i; ) {
    if (is_ear(i, next[i], next[next[i]])) {
      area  += abs(cross(ps[next[i]]-ps[i], ps[next[next[i]]] - ps[i])) / 2;
      next[i] = next[next[i]];
    } else i = next[i];
  }
  return area;
}