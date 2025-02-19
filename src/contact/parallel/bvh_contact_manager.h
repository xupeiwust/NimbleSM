/*
//@HEADER
// ************************************************************************
//
//                                NimbleSM
//                             Copyright 2018
//   National Technology & Engineering Solutions of Sandia, LLC (NTESS)
//
// Under the terms of Contract DE-NA0003525 with NTESS, the U.S. Government
// retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY NTESS "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
// NO EVENT SHALL NTESS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions?  Contact David Littlewood (djlittl@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef NIMBLE_BVH_CONTACT_MANAGER_H
#define NIMBLE_BVH_CONTACT_MANAGER_H

#include <bvh/collision_world.hpp>
#include <bvh/types.hpp>

#include <memory>

#include "parallel_contact_manager.h"

namespace bvh {

class collision_object;

}

namespace nimble {
struct NarrowphaseResult
{
  std::size_t local_index;
  double      gap;
  double      contact_force[3];
  double      bary[3];
  bool        node;
};

class BvhContactManager : public ParallelContactManager
{
 public:
  BvhContactManager(
      std::shared_ptr<ContactInterface> interface,
      nimble::DataManager&              data_manager,
      std::size_t                       _overdecomposition,
      std::string                       splitting_alg);

  BvhContactManager(const BvhContactManager&) = delete;
  BvhContactManager(BvhContactManager&&)      = delete;

  BvhContactManager&
  operator=(const BvhContactManager&) = delete;
  BvhContactManager&
  operator=(BvhContactManager&&) = delete;

  ~BvhContactManager() = default;

 protected:
  void
  ComputeParallelContactForce(int step, bool debug_output, nimble::Viewify<2> contact_force) override;

  void
  ComputeBoundingVolumes();

  bvh::collision_world   m_world;
  bvh::collision_object* m_nodes;
  bvh::collision_object* m_faces;

  bvh::split_algorithm m_split_alg = bvh::split_algorithm::geom_axis;

  std::vector<NarrowphaseResult> m_last_results;
};
}  // namespace nimble

#endif  // NIMBLESM_BVH_CONTACT_MANAGER_H
