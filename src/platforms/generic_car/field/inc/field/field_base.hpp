/* 
 * field.hpp
 * 
 * Created on: Nov 17, 2017 13:25
 * Description: 
 * 
 * Copyright (c) 2017 Ruixiang Du (rdu)
 */

#ifndef FIELD_HPP
#define FIELD_HPP

#include <cstdint>
#include <vector>

#include <Eigen/Dense>

namespace librav
{

struct ScalarFieldMatrix
{
  Eigen::VectorXd x;
  Eigen::VectorXd y;
  Eigen::MatrixXd z;
};

template <typename T>
class FieldBase
{
public:
  FieldBase();
  FieldBase(int64_t size_x, int64_t size_y);

  int64_t SizeX() const { return size_x_; };
  int64_t SizeY() const { return size_y_; };
  void PrintField() const;

protected:
  int64_t size_x_;
  int64_t size_y_;
  std::vector<std::vector<T>> field_tiles_;

  void ResizeField(int64_t x, int64_t y);
  void SetTileAtLocation(int64_t x, int64_t y, T tile);
  T &GetTileAtLocation(int64_t x, int64_t y);
};
}

#include "details/field_base_impl.hpp"

#endif /* FIELD_HPP */
