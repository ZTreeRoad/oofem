/* $Header: /home/cvs/bp/oofem/sm/src/Attic/rankinepm.h,v 1.1.2.1 2004/04/05 15:19:47 bp Exp $ */
/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2008   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

//   **********************************
//   *** CLASS Rankine plastic material
//   **********************************

#ifndef rankinepm_h
#define rankinepm_h

#include "mplasticmaterial.h"

namespace oofem {
class Domain;

/**
 * This class implements a isotropic  plastic linear material (J2 plasticity condition is used)
 *      in a finite element problem. A material
 * is an attribute of a domain. It is usually also attribute of many elements.
 */
class RankinePlasticMaterial : public MPlasticMaterial
{
protected:
    /// yield value
    double k;
public:

    RankinePlasticMaterial(int n, Domain *d);
    ~RankinePlasticMaterial();

    IRResultType initializeFrom(InputRecord *ir);
    const char *giveClassName() const { return "RankinePlasticMaterial"; }
    classType giveClassID()         const { return PerfectlyPlasticMaterialClass; }

    MaterialStatus *CreateStatus(GaussPoint *gp) const;

protected:

    //
    // yield(YC-like functions) and loading(LC-like functions) criteria specific section
    //

    /// Computes the value of yield function
    double computeYieldValueAt(GaussPoint *gp, int isurf, const FloatArray &stressVector,
                               const FloatArray &stressSpaceHardeningVars);

    void   computeHardeningReducedModuli(FloatMatrix &answer,
                                         GaussPoint *gp,
                                         const FloatArray &strainSpaceHardeningVariables,
                                         TimeStep *atTime);
    void computeStressGradientVector(FloatArray &answer, functType ftype, int isurf, GaussPoint *gp, const FloatArray &stressVector,
                                     const FloatArray &stressSpaceHardeningVars);
    void computeStressSpaceHardeningVarsReducedGradient(FloatArray &answer, functType ftype, int isurf, GaussPoint *gp,
                                                        const FloatArray &stressVector,
                                                        const FloatArray &stressSpaceHardeningVars);
    int hasHardening() { return 0; }
    void  computeReducedGradientMatrix(FloatMatrix &answer, int isurf,
                                       GaussPoint *gp,
                                       const FloatArray &stressVector,
                                       const FloatArray &stressSpaceHardeningVars);

    void computeStressSpaceHardeningVars(FloatArray &answer, GaussPoint *gp,
                                         const FloatArray &strainSpaceHardeningVariables);
};
} // end namespace oofem
#endif // rankinepm_h
