#include <bits/stdc++.h>
using namespace std;

// Linear Operations

typedef int tipo;

struct Ponto {
    tipo x, y;
    Ponto() {}
    Ponto(tipo x, tipo y): x(x), y(y) {}
    Ponto& operator+=(const Ponto &other){
        x += other.x;
        y += other.y;
        return *this;
    }
    Ponto& operator-=(const Ponto &other){
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Ponto& operator*=(tipo val){
        x *= val;
        y *= val;
        return *this;
    }
    Ponto& operator/=(tipo val){
        x /= val;
        y /= val;
        return *this;
    }
    Ponto operator+(const Ponto &other) const {
        return Ponto(*this) += other;
    }
    Ponto operator-(const Ponto &other) const {
        return Ponto(*this) -= other;
    }
    Ponto operator*(tipo val) const {
        return Ponto(*this) *= val;
    }
    Ponto operator/(tipo val) const {
        return Ponto(*this) /= val;
    }
};

tipo dot(Ponto a, Ponto b){
    return a.x * b.x + a.y * b.y;
}

tipo norm(Ponto a){
    return dot(a, a);
}

double abs(Ponto a){
    return sqrt(norm(a));
}

double proj(Ponto a, Ponto b){
    return dot(a, b) / abs(a);
}

double angle(Ponto a, Ponto b){
    return acos(dot(a,b) / abs(a) / abs(b));
}

int main(){
    Ponto ponto;
    cin >> ponto.x >> ponto.y;
    cout << ponto.x << " " << ponto.y;
}