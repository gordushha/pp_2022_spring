// Copyright 2022 Shabunin Vladislav
#ifndef MODULES_TASK_4_SHABUNIN_V_CSR_MULT_DOUBLE_CSR_MULT_DOUBLE_H_
#define MODULES_TASK_4_SHABUNIN_V_CSR_MULT_DOUBLE_CSR_MULT_DOUBLE_H_

#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

#include "../../3rdparty/unapproved/unapproved.h"

class RandomDouble {
 public:
  static double Next() {
    static RandomDouble rand = RandomDouble();
    return rand.dist_(rand.gen_);
  }

 private:
  RandomDouble() : gen_(std::random_device()()), dist_(-1e3, 1e3) {
  }

  std::mt19937_64 gen_;
  std::uniform_real_distribution<double> dist_;
};

template <class T>
bool Compare(const T &lhs, const T &rhs) {
  static float float_eps = 1e-3;
  static double double_eps = 1e-6;
  if (std::is_same<T, float>::value) {
    return (lhs + float_eps > rhs) && (lhs - float_eps < rhs);
  }
  if (std::is_same<T, double>::value) {
    return (lhs + double_eps > rhs) && (lhs - double_eps < rhs);
  }
  return lhs == rhs;
}

template <class ValueType, typename UIntType = uint16_t>
class CSRMatrixSTD {
 public:
  CSRMatrixSTD() = delete;

  CSRMatrixSTD(const CSRMatrixSTD &other) = default;
  CSRMatrixSTD(CSRMatrixSTD &&other) = default;

  explicit CSRMatrixSTD(UIntType height, UIntType width, size_t num_threads = 1)
      : counts_(height + 1, 0), num_threads_(num_threads), num_cols_(width) {
  }

  explicit CSRMatrixSTD(UIntType height, UIntType width, const std::vector<ValueType> &matrix,
                        size_t num_threads = 1)
      : counts_(height + 1), num_threads_(num_threads), num_cols_(width) {
    if (static_cast<UIntType>(matrix.size()) != height * width) {
      throw std::runtime_error("Init matrix must consist of height*width elements");
    }
    counts_[0] = 0;
    for (UIntType row = 0; row < height; ++row) {
      counts_[row + 1] = counts_[row];
      for (UIntType col = 0; col < width; ++col) {
        auto cur_val = matrix[width * row + col];
        if (cur_val) {
          vals_.emplace_back(cur_val);
          cols_.emplace_back(col);
          ++counts_[row + 1];
        }
      }
    }
  }

  CSRMatrixSTD &operator=(CSRMatrixSTD other) {
    Swap(other);
    return *this;
  }

  void Swap(CSRMatrixSTD &other) {
    std::swap(vals_, other.vals_);
    std::swap(cols_, other.cols_);
    std::swap(counts_, other.counts_);
    std::swap(num_threads_, other.num_threads_);
    std::swap(num_cols_, other.num_cols_);
  }

  bool operator==(const CSRMatrixSTD &rhs) const {
    const CSRMatrixSTD &lhs = *this;
    if (lhs.vals_.size() != rhs.vals_.size() || lhs.counts_.size() != rhs.counts_.size() ||
        lhs.num_cols_ != rhs.num_cols_) {
      return false;
    }
    for (UIntType i = 1; i < lhs.counts_.size(); ++i) {
      if (lhs.counts_[i] != rhs.counts_[i]) {
        return false;
      }
    }
    for (UIntType i = 0; i < lhs.vals_.size(); ++i) {
      if (lhs.cols_[i] != rhs.cols_[i] || !Compare(lhs.vals_[i], rhs.vals_[i])) {
        return false;
      }
    }
    return true;
  }

  CSRMatrixSTD &operator*=(const CSRMatrixSTD &other) {
    CSRMatrixSTD rhs = other.GetTransposed();
    UIntType res_width = other.num_cols_;
    UIntType res_height = counts_.size() - 1;
    std::vector<ValueType> res_mat(res_width * res_height);
    auto mult_fun = [&](UIntType first_row, UIntType last_row) {
      for (UIntType row = first_row; row < last_row; ++row) {
        for (UIntType col = 0; col < res_width; ++col) {
          UIntType l_row_cur = counts_[row], r_row_cur = rhs.counts_[col];
          ValueType cur_val = 0;
          while (l_row_cur < counts_[row + 1] && r_row_cur < rhs.counts_[col + 1]) {
            if (cols_[l_row_cur] < rhs.cols_[r_row_cur]) {
              ++l_row_cur;
            } else if (cols_[l_row_cur] > rhs.cols_[r_row_cur]) {
              ++r_row_cur;
            } else {
              cur_val += vals_[l_row_cur++] * rhs.vals_[r_row_cur++];
            }
          }
          res_mat[row * res_width + col] = cur_val;
        }
      }
    };
    std::vector<std::thread> threads;
    UIntType rows_per_thread = res_height / static_cast<UIntType>(num_threads_);
    size_t num_threads_with_add = static_cast<size_t>(res_height) % num_threads_;
    UIntType cur_row = 0;
    for (size_t td = 0; td < num_threads_; ++td) {
      UIntType num_row_for_cur_thread = rows_per_thread + (td < num_threads_with_add ? 1 : 0);
      threads.emplace_back(mult_fun, cur_row, cur_row + num_row_for_cur_thread);
      cur_row += num_row_for_cur_thread;
    }
    for (size_t td = 0; td < num_threads_; ++td) {
      threads[td].join();
    }

    num_cols_ = res_width;
    vals_.resize(0);
    cols_.resize(0);
    counts_.resize(res_height + 1);
    counts_[0] = 0;
    for (UIntType row = 0; row < res_height; ++row) {
      counts_[row + 1] = counts_[row];
      for (UIntType col = 0; col < res_width; ++col) {
        auto cur_val = res_mat[res_width * row + col];
        if (cur_val) {
          vals_.emplace_back(cur_val);
          cols_.emplace_back(col);
          ++counts_[row + 1];
        }
      }
    }
    return *this;
  }

  void SetNumThreads(size_t num_threads) {
    num_threads_ = num_threads;
  }

 protected:
  const CSRMatrixSTD GetTransposed() const {
    CSRMatrixSTD other(num_cols_, counts_.size() - 1);
    for (UIntType i = 0; i < cols_.size(); ++i) {
      ++other.counts_[cols_[i]];
    }
    for (UIntType col = 0, sum = 0; col < other.counts_.size(); ++col) {
      UIntType tmp = other.counts_[col];
      other.counts_[col] = sum;
      sum += tmp;
    }
    other.cols_.resize(other.counts_.back());
    other.vals_.resize(other.counts_.back());

    for (UIntType row = 0; static_cast<UIntType>(row + 1) < counts_.size(); ++row) {
      for (UIntType cnt = counts_[row]; cnt < counts_[row + 1]; ++cnt) {
        UIntType col = cols_[cnt];
        UIntType dest_place = other.counts_[col];
        other.vals_[dest_place] = vals_[cnt];
        other.cols_[dest_place] = row;
        ++other.counts_[col];
      }
    }
    for (UIntType col = 0, last = 0; col <= num_cols_; ++col) {
      UIntType tmp = other.counts_[col];
      other.counts_[col] = last;
      last = tmp;
    }
    return other;
  }

  std::vector<ValueType> vals_;
  std::vector<UIntType> cols_;
  std::vector<UIntType> counts_;
  size_t num_threads_;
  UIntType num_cols_;
};

#endif  // MODULES_TASK_4_SHABUNIN_V_CSR_MULT_DOUBLE_CSR_MULT_DOUBLE_H_
