//C++
#include <array>
//McCAD
#include "triangleCollision.hpp"
//OCC
#include <BRepTools.hxx>

template<>
Standard_Boolean
McCAD::Decomposition::PointOnSurface::pointOnSurface<Geometry::BoundSurfacePlane>(
        const gp_Pnt& aPoint, const TopoDS_Face& extendedFace,
        const Standard_Real& distanceTolerance){
    //std::cout << "pointOnSurface" << std::endl;
    BRepAdaptor_Surface surfaceAdaptor(extendedFace, Standard_True);
    Standard_Real uvTolerance = surfaceAdaptor.Tolerance();
    std::array<Standard_Real, 4> uvParameters;
    uvParameters[0] = surfaceAdaptor.FirstUParameter();
    uvParameters[1] = surfaceAdaptor.LastUParameter();
    uvParameters[2] = surfaceAdaptor.FirstVParameter();
    uvParameters[3] = surfaceAdaptor.LastVParameter();
    Extrema_ExtPS extremumDistances(aPoint, surfaceAdaptor, uvParameters[0],
            uvParameters[1], uvParameters[2], uvParameters[3], uvTolerance,
            uvTolerance);
    if (extremumDistances.IsDone() && extremumDistances.NbExt() != 0){
        gp_Pnt point = extremumDistances.Point(1).Value();
        Standard_Real distance = std::sqrt(std::pow(aPoint.X() - point.X(), 2) +
                                           std::pow(aPoint.Y() - point.Y(), 2) +
                                           std::pow(aPoint.Z() - point.Z(), 2));
      if (distance < distanceTolerance){
          return Standard_True;
      }
    }
    //std::cout << "pointOnSurface return"	<< std::endl;
    return Standard_False;
}
