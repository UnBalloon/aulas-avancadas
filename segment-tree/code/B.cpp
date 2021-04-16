#include <bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
#define sws ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

const int MAX = 1e5; // tamanho máximo do vetor
const ll LLINF = 0x3f3f3f3f3f3f3f3f;

// End Template //

vector<ll> tree(4*MAX, LLINF), vet(MAX, LLINF); // segtree e vetor
int N;

void build(int l=0, int r=N-1, int no=1){
    if(l==r){ // caso base
        tree[no] = vet[l];
        return;
    }

    int mid = (l + r)/2;
    build(l, mid, 2*no); // filho da esquerda
    build(mid+1, r, 2*no+1); // filho da direita

    tree[no] = min(tree[2*no], tree[2*no+1]); // merge
}

void update(int i, int x, int l=0, int r=N-1, int no=1){
    if(l==r){ // caso base
        tree[no] = x;
        return;
    }

    int mid = (l + r)/2;
    if(i<=mid) // esquerda
        update(i, x, l, mid, 2*no);
    else // direita
        update(i, x, mid+1, r, 2*no+1);

    tree[no] = min(tree[2*no], tree[2*no+1]); // merge
}

ll query(int A, int B, int l=0, int r=N-1, int no=1){
    if(r<A or B<l) return LLINF; // 1º caso
    if(A<=l and r<=B) return tree[no]; // 2º caso

    // 3º caso
    int mid = (l + r)/2;

    ll minLeft = query(A, B, l, mid, 2*no);
    ll minRight = query(A, B, mid+1, r, 2*no+1);

    return min(minLeft, minRight);
}

int32_t main()
{sws;

    int M, opt, id, v, l, r;
    cin >> N >> M;
    for(int i=0;i<N;i++)
        cin >> vet[i];

    build();

    for(int i=0;i<M;i++){
        cin >> opt;
        if(opt==1){ // update
            cin >> id >> v;
            update(id, v);
        }else{ // query
            cin >> l >> r;
            cout << query(l, r-1) << endl;
        }
    }

    return 0;
}