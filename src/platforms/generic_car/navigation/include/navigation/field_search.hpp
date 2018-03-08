/* 
 * field_search.hpp
 * 
 * Created on: Mar 08, 2018 17:35
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef FIELD_SEARCH_HPP
#define FIELD_SEARCH_HPP

#include <memory>
#include <vector>
#include <tuple>

#include "field/collision_field.hpp"

#include "graph/graph.hpp"
#include "graph/algorithms/dijkstra.hpp"

namespace librav
{
class FieldTile
{
public:
  FieldTile(int32_t posx, int32_t posy, std::shared_ptr<CollisionField> cf) : position_x_(posx), position_y_(posy), field_(cf){};
  ~FieldTile() = default;

  std::shared_ptr<CollisionField> field_;

  int32_t position_x_;
  int32_t position_y_;

  int64_t GetUniqueID() const
  {
    return field_->SizeX() * position_y_ + position_x_;
  }

  double GetCollisionThreat()
  {
    return field_->collision_threat_matrix_(position_x_, position_y_);
  }
};

class GetFieldTileNeighbour
{
public:
  GetFieldTileNeighbour(std::shared_ptr<CollisionField> cf);

  // define the functor operator
  std::vector<std::tuple<FieldTile, double>> operator()(FieldTile tile);

private:
  std::shared_ptr<CollisionField> field_;
};
}

#endif /* FIELD_SEARCH_HPP */