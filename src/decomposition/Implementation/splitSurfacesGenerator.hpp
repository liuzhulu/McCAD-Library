#ifndef SPLITSURFACESGENERATOR_HPP
#define SPLITSURFACESGENERATOR_HPP

// C++
#include <vector>
#include <memory>
// McCAD
#include "boundSurface_impl.hpp"

namespace McCAD::Decomposition{
  class SplitSurfacesGenerator{
  public:
    SplitSurfacesGenerator();
    ~SplitSurfacesGenerator();
    static void generateSplitFacesList(
            std::vector<std::shared_ptr<Geometry::BoundSurface>>& splitFacesList,
            std::vector<std::shared_ptr<Geometry::BoundSurface>>& selectedSplitFacesList);
    static void sortSplitFaces(
            std::vector<std::shared_ptr<Geometry::BoundSurface>>& splitFacesList);
  };
}

#endif //SPLITSURFACESGENERATOR_HPP
