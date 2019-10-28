#ifndef CYLSOLID_IMPL_HPP
#define CYLSOLID_IMPL_HPP

// C++
// McCAD
#include "cylSolid.hpp"
#include "solid_impl.hpp"
// OCC

namespace McCAD::Geometry{
  class CYLSolid::Impl {
  public:
    Impl();
    ~Impl();

    void judgeDecomposeSurfaces(Solid::Impl*& solidImpl);
  };
}

#endif //CYLSOLID_IMPL_HPP
