#include <stdio.h>
// gcc pif3.c -o generator

typedef struct{
    long long m[3][3];
}Matrix3x3;

typedef struct{
    long long m[3][1];
}Matrix3x1;


Matrix3x1 mult(Matrix3x3 A, Matrix3x1 v){
    Matrix3x1 res;
    res.m[0][0] = A.m[0][0] * v.m[0][0] + A.m[0][1] * v.m[1][0] + A.m[0][2] * v.m[2][0];
    res.m[1][0] = A.m[1][0] * v.m[0][0] + A.m[1][1] * v.m[1][0] + A.m[1][2] * v.m[2][0];
    res.m[2][0] = A.m[2][0] * v.m[0][0] + A.m[2][1] * v.m[1][0] + A.m[2][2] * v.m[2][0];
    return res;
}
void printMatrix(Matrix3x1 m){
    for (int i = 0; i < 3; i++){
        printf("%lld ", m.m[i][0]);
    }
    printf("\n");
}
void getstr(Matrix3x1 v, char *buffer) {
    sprintf(buffer, "%lld,%lld,%lld", v.m[0][0], v.m[1][0], v.m[2][0]);
}


void DeepMatrix(Matrix3x1 parent, int nowdeep, int maxdeep){
    if(nowdeep >= maxdeep){
        return;
    }
    Matrix3x3 trans[3] = {
        {{{1, -2, 2}, {2, -1, 2}, {2, -2, 3}}},
        {{{1, 2, 2}, {2, 1, 2}, {2, 2, 3}}},
        {{{-1, 2, 2}, {-2, 1, 2}, {-2, 2, 3}}}
    };
    char parentstr[50];
    getstr(parent, &parentstr[0]);

    for (int i = 0; i < 3; i++){
        Matrix3x1 child = mult(trans[i], parent);
        char childstr[50];
        getstr(child, &childstr[0]);
        printf("%s;%s\n", parentstr, childstr);
        DeepMatrix(child, nowdeep + 1, 4);
    }

}

int main(){
    Matrix3x1 base = {{{3}, {4}, {5}}};
    int deep = 4;
    DeepMatrix(base, 0, deep);
    // Matrix3x3 trans1 = {{{1, -2, 2}, {2, -1, 2}, {2, -2, 3}}};
    // Matrix3x3 trans2 = {{{1, 2, 2}, {2, 1, 2}, {2, 2, 3}}};
    // Matrix3x3 trans3 = {{{-1, 2, 2}, {-2, 1, 2}, {-2, 2, 3}}};
    // printMatrix(mult(trans1, base));
    // printMatrix(mult(trans2, base));
    // printMatrix(mult(trans3, base));

    return 0;
}