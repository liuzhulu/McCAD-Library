#ifndef MCNPWRITER_HPP
#define MCNPWRITER_HPP

// C++
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <optional>
// McCAD
#include "solid_impl.hpp"
#include "compound.hpp"
#include "voidCell.hpp"
#include "inputconfig.hpp"
// OCC
#include <Standard.hxx>

namespace McCAD::Conversion{
    class MCNPWriter {
    public:
        MCNPWriter(const IO::InputConfig& inputConfig);
        ~MCNPWriter();
    private:
        using surfacesMap = std::map<Standard_Integer, std::shared_ptr<Geometry::BoundSurface>>;
        using finalMap = std::map<Standard_Integer, std::string>;
        using matMap = std::map<std::tuple<std::string, Standard_Real>, Standard_Integer>;
        using solidsMap = std::map<Standard_Integer, std::shared_ptr<Geometry::Solid>>;
        using compoundsMap = std::map<Standard_Integer, std::shared_ptr<Geometry::Impl::Compound>>;
        using voidsMap = std::map<std::tuple<Standard_Integer, Standard_Integer, std::string>,
                                  std::shared_ptr<VoidCell>>;
    public:
        IO::InputConfig inputConfig;
        Standard_Integer continueSpacing{6};
        Standard_Real scalingFactor{1.0}, radius;
        surfacesMap uniquePlanes, uniqueCylinders, uniqueTori;
        finalMap uniqueSurfaces;
        matMap materialsMap;
        solidsMap solidObjMap;
        compoundsMap compoundObjMap;
        voidsMap voidCellsMap;

        void operator()(
                const std::vector<std::shared_ptr<Geometry::Impl::Compound>>& compoundList,
                const std::shared_ptr<VoidCell>& voidCell);
        void processSolids(const std::vector<std::shared_ptr<Geometry::Impl::Compound>>& compoundList);
        void processVoids(const std::shared_ptr<VoidCell>& voidCell);
        void addUniqueSurfNumbers(const std::vector<std::shared_ptr<Geometry::Impl::Compound>>& compoundList);
        std::optional<Standard_Integer> findDuplicate(
                const std::shared_ptr<Geometry::BoundSurface>& surface,
                surfacesMap& uniqueMap);
        void createSolidsMap(const std::vector<std::shared_ptr<Geometry::Impl::Compound>>& compoundList);
        void createMaterialsMap(const std::vector<std::tuple<std::string, double>>& materialsInfo);
        void addDaughterVoids(const std::shared_ptr<VoidCell>& voidCell);
        void createVoidMap(const std::shared_ptr<VoidCell>& voidCell);
        std::string adjustLineWidth(const std::string& mainExpr,
                                    const std::string& bodyExpr,
                                    Standard_Integer& continueSpacing);
        void writeHeader(std::ofstream& outputStream);
        void writeCellCard(std::ofstream& outputStream, std::ofstream& volumeStream);
        void writeVoidCard(std::ofstream& outputStream);
        void writeSurfCard(std::ofstream& outputStream);
        void writeDataCard(std::ofstream& outputStream);
    };
}

#endif // MCNPWRITER_HPP
