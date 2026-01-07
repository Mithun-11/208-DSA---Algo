vector<bool> is_special(n + 1, false);
// input loop reading subset nodes:
// is_special[node_idx] = true;

// 1. Normal Move (Always allowed)
if (cost + w < dist[v][used]) { ... }

// 2. Coupon Move (Only if node is special)
if (used == 0 && is_special[u] && cost + w/2 < dist[v][1]) {
    dist[v][1] = cost + w/2;
    pq.push({dist[v][1], 1, v});
}