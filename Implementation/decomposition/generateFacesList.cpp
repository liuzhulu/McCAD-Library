//McCAD
#include "generateFacesList.hpp"
#include "generateFacesList.tpp"

McCAD::Decomposition::FacesListGenerator::FacesListGenerator(){
}

McCAD::Decomposition::FacesListGenerator::~FacesListGenerator(){
}

void
McCAD::Decomposition::FacesListGenerator::mergeSurfaces(
        std::vector<BS>& surfacesList,
        Standard_Real& boxSquareLength){
    //std::cout << "mergeSurfaces" << std::endl;
    if (surfacesList.size() < 2){
        return;
    }
    for (Standard_Integer i = 0; i < surfacesList.size(); ++i){
        for (Standard_Integer j = i+1; j < surfacesList.size(); ++j){
            if (*surfacesList[i] == *surfacesList[j]){
                surfacesList[j]->accessSImpl()->surfaceNumber =
                        surfacesList[i]->accessSImpl()->surfaceNumber;
                // Test if the two surfaces can be fused.
                if (*surfacesList[i] << *surfacesList[j]){
                    //std::cout << "*** equal fuse" << std::endl;
                    if (surfacesList[i]->getSurfaceType() == Tools::toTypeName(GeomAbs_Plane)){
                        TopoDS_Face newFace = Tools::PlaneFuser{}(
                                    surfacesList[i]->accessSImpl()->face,
                                    surfacesList[j]->accessSImpl()->face);
                        BS newboundSurface =
                                generateSurface<McCAD::Geometry::PLSolid>(
                                    newFace, boxSquareLength);
                        newboundSurface->accessSImpl()->surfaceNumber =
                                surfacesList[i]->accessSImpl()->surfaceNumber;
                        // Add triangles of surface i.
                        for (Standard_Integer k = 0; k <
                             surfacesList[i]->accessBSImpl()->meshTrianglesList.size(); ++k){
                            newboundSurface->accessBSImpl()->meshTrianglesList.push_back(
                                        std::move(surfacesList[i]->accessBSImpl()->meshTrianglesList[k]));
                        }
                        // Add triangles of surface j.
                        for (Standard_Integer k = 0; k <
                             surfacesList[j]->accessBSImpl()->meshTrianglesList.size(); ++k){
                            newboundSurface->accessBSImpl()->meshTrianglesList.push_back(
                                        std::move(surfacesList[j]->accessBSImpl()->meshTrianglesList[k]));
                        }
                        // Combine edges.
                        newboundSurface->accessBSImpl()->combineEdges(
                                    surfacesList[i]->accessBSImpl()->edgesList);
                        newboundSurface->accessBSImpl()->combineEdges(
                                    surfacesList[j]->accessBSImpl()->edgesList);
                        // Erase pointer surfacesList[j] & [i] from surfacesList.
                        surfacesList.erase(surfacesList.begin() + j);
                        --j;
                        surfacesList.erase(surfacesList.begin() + i);
                        --i;
                        surfacesList.push_back(std::move(newboundSurface));
                        break;
                    }
                } else{
                    //std::cout << "*** equal, erase one" << std::endl;
                    surfacesList.erase(surfacesList.begin() + j);
                    --j;
                }
                if (surfacesList.size() < 2){
                    return;
                }
            }
        }
    }
}
