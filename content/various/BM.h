/**
 * Author: Shash
 * Description: Bostan-Mori
 */
mint BM(vector<mint> P, vector<mint> Q, ll k) {
  for(;k;k/=2) {
    auto Qm = Q;
    for(int i = 1; i < Qm.size(); i+=2) Qm[i] *= -1;
    
    auto tmp = conv(P,Qm);
    vector<mint> nP; nP.reserve(min(k+1,(ll)P.size()));
    for(ll i = k%2; i < 2ll*(k+1) && i < tmp.size(); i+=2) nP.emplace_back(tmp[i]);
    swap(P,nP);
    
    tmp = conv(Q,Qm);
    vector<mint> nQ; nQ.reserve(min(k+1,(ll)Q.size()));
    for(ll i = 0; i < 2ll*(k+1) && i < tmp.size(); i+=2) nQ.emplace_back(tmp[i]);
    swap(Q,nQ);
  }
  return P[0] / Q[0];
}