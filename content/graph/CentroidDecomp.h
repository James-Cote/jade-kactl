/**
 * Author: USACO Guide
 * License: CC0
 * Source: USACO Guide
 * Description: Centroid decomp.
 * Time: $O(N \log N)$ overall
 */
#pragma once

vi adj[N];
int subtree_size[N], removed[N];

int get_subtree_size(int node, int p = -1) {
	subtree_size[node] = 1;
	for (auto nxt : adj[node]) if (!removed[nxt] && nxt != p) {
		subtree_size[node] += get_subtree_size(nxt, node);
	}
	return subtree_size[node];
}

int get_centroid(int node, int s, int p = -1) {
	for (auto nxt : adj[node]) if (!removed[nxt] && nxt != p) {
		if (subtree_size[nxt] * 2 > s) {
			return get_centroid(nxt, s, node);
		}
	}
	return node;
}

/** Build up the centroid decomposition recursively */
void centroid_decomp(int node) {
	int c = get_centroid(node, get_subtree_size(node));

	// do something

	removed[c] = 1;
	for (auto nxt : adj[c]) if (!removed[nxt]) {
		centroid_decomp(nxt);
	}
}