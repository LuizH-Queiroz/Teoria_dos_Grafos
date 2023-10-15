#include "union_find.hpp"


/**
 * O vetor de conjuntos começa vazio
*/
UnionFind::UnionFind() {
    // Nada :)
}


/**
 * O vetor de conjuntos começa com o tamanho fornacido
*/
UnionFind::UnionFind(int n) {
    Initialize(n);
}


/**
 * Encontra o conjunto ao qual o inteiro pertence
*/
int UnionFind::Find(int n) {
    if (parent[n] == n)
        return n;
    return parent[n] = Find(parent[n]);
}


/**
 * Inicializa um vetor de tamanho n.
 * Sendo assim, os conjuntos estarão no intervalo [0, n-1]
*/
void UnionFind::Initialize(int n) {
    parent.resize(n);

    for (int i = 0; i < n; i++)
        parent[i] = i;
}


/**
 * Une os conjuntos recebidos como parâmetros
*/
void UnionFind::Union(int a, int b) {
    parent[Find(a)] = Find(b);
}