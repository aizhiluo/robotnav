/* 
 * graph_edge_impl.hpp
 * 
 * Created on: Sep 04, 2018 01:37
 * Description: 
 * 
 * Copyright (c) 2018 Ruixiang Du (rdu)
 */

#ifndef GRAPH_EDGE_IMPL_HPP
#define GRAPH_EDGE_IMPL_HPP

namespace rnav
{
template <typename State, typename Transition, typename StateIndexer>
bool Graph<State, Transition, StateIndexer>::Edge::operator==(const Graph<State, Transition, StateIndexer>::Edge &other)
{
    if (src_ == other.src_ && dst_ == other.dst_ && cost_ == other.cost_)
        return true;
    return false;
}

template <typename State, typename Transition, typename StateIndexer>
void Graph<State, Transition, StateIndexer>::Edge::PrintEdge()
{
    std::cout << "Edge_t: src - " << src_->GetVertexID() << " , dst - " << dst_->GetVertexID() << " , cost - " << cost_ << std::endl;
}

} // namespace rnav

#endif /* GRAPH_EDGE_IMPL_HPP */
