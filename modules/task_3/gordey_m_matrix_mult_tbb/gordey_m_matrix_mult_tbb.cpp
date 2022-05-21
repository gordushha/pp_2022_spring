// Copyright 2018 Nesterov Alexander
#include <vector>
#include <string>
#include <random>
#include <functional>
#include <numeric>
#include "../gordey_m_matrix_mult_tbb/gordey_m_matrix_mult.h"
double* create_random_matrix(int size_n) {
        std::random_device dev;
        std::mt19937 gen(dev());
        double* in = new double[size_n];
        for (int i = 0; i < size_n; ++i) {
                in[i] = static_cast<double>(gen()) / gen();
                if ((i % 3 == 0)) in[i] = 0;
        }
        return in;
}
SparseM operator *(const SparseM& A, const SparseM& B) {
        SparseM C(A);
        std::vector<int> row;
        std::vector<double>value;
        std::vector<int>col_idx(B.cols);
        transport(&C);
        int ci = 0;
        bool flag = true;
        for (int i = 0; i < B.cols; i++) {
                for (int j = 0; j < C.cols; j++) {
                        double res = 0;
                        int ls = B.col_idx[i];
                        int lf = B.col_idx[i + 1] - 1;
                        int ks = C.col_idx[j];
                        int kf = C.col_idx[j + 1] - 1;
                        while ((ks <= kf) && (ls <= lf)) {
                                if (C.row[ks] == B.row[ls]) {
                                        res += C.value[ks] * B.value[ls];
                                        ks++;
                                        ls++;
                                } else {
                                        if (C.row[ks] < B.row[ls]) {
                                                ks++;
                                        } else {
                                                ls++;
                                        }
                                }
                        }
                        if (res != 0) {
                                if (flag) {
                                        col_idx[i] = (ci);
                                        flag = false;
                                }
                                value.push_back(res);
                                row.push_back(j);
                                ci++;
                        }
                }
                if (flag)  col_idx[i] = (ci);
                flag = true;
        }
        col_idx.push_back(ci);
        C.row = std::move(row);
        C.value = std::move(value);
        C.col_idx = std::move(col_idx);

        return C;
}
void transport(SparseM* v) {
        std::vector<std::queue<int >> A(v->rows);
        std::vector<std::queue<double >> B(v->rows);
        std::vector<int>col_idx(v->cols);
        int k = 0;
        bool flag = true;
        for (int i = 0; i < v->cols; i++) {
                for (int j = v->col_idx[i]; j <= v->col_idx[i + 1] - 1; j++) {
                        A[v->row[j]].push(i);
                        B[v->row[j]].push(v->value[j]);
                }
        }

        v->value.resize(0);
        v->row.resize(0);
        for (int i = 0; i < v->rows; i++) {
                while (!B[i].empty()) {
                        if (flag) {
                                col_idx[i] = k;
                                flag = false;
                        }
                        v->value.push_back(B[i].front());
                        B[i].pop();
                        v->row.push_back(A[i].front());
                        A[i].pop();
                        k++;
                }
                flag = true;
        }
        col_idx.push_back(k);
        v->col_idx = std::move(col_idx);
}

struct Functor {
        const SparseM* B;
        SparseM* C;
        std::vector<int>* col_idx;
        std::vector<double> vals;
        std::vector<int>rows;
        Functor(const SparseM* B, SparseM* C, std::vector<int>* CI): B(B),
                 C(C), col_idx(CI) {}
        Functor(const Functor& f, tbb::split): B(f.B), C(f.C),
                 col_idx(f.col_idx) {}
        void operator()(const tbb::blocked_range<int> &r) {
                int begin = r.begin();
                int end = r.end();
                for (int i = begin; i < end; i++) {
                        for (int j = 0; j < C->cols; j++) {
                                double res = 0;
                                int ls = B->col_idx[i];
                                int lf = B->col_idx[i + 1] - 1;
                                int ks = C->col_idx[j];
                                int kf = C->col_idx[j + 1] - 1;
                                while ((ks <= kf) && (ls <= lf)) {
                                        if (C->row[ks] == B->row[ls]) {
                                                res +=
                                                C->value[ks] * B->value[ls];
                                                ks++;
                                                ls++;
                                        } else {
                                                if (C->row[ks] < B->row[ls]) {
                                                        ks++;
                                                } else {
                                                        ls++;
                                                }
                                        }
                                }
                                if (res != 0) {
                                        (*col_idx)[i]++;
                                        vals.push_back(res);
                                        rows.push_back(j);
                                }
                        }
                }
        }
        void join(const Functor& f) {
                vals.insert(vals.end(), f.vals.begin(), f.vals.end());
                rows.insert(rows.end(), f.rows.begin(), f.rows.end());
        }
};

SparseM Mult_parallel(const SparseM& A, const SparseM& B) {
        SparseM C(A);
        std::vector<double>vals;
        std::vector<int> rows;
        std::vector<int>col_idx(B.cols, 0);
        transport(&C);
        Functor f(&B, &C, &col_idx);
        tbb::parallel_reduce(tbb::blocked_range<int>(0, B.cols, B.cols / 4), f);
        int sum = 0;
        for (size_t i = 0; i < col_idx.size(); i++) {
                int tmp = col_idx[i];
                col_idx[i] = sum;
                sum = tmp + sum;
        }
        col_idx.emplace_back(sum);
        C.col_idx = std::move((col_idx));
        C.row = std::move(f.rows);
        C.value = std::move(f.vals);
        return C;
}
