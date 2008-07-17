//////////////////////////////////////////////////////////////////
// (c) Copyright 2003-  by Jeongnim Kim
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//   National Center for Supercomputing Applications &
//   Materials Computation Center
//   University of Illinois, Urbana-Champaign
//   Urbana, IL 61801
//   e-mail: jnkim@ncsa.uiuc.edu
//   Tel:    217-244-6319 (NCSA) 217-333-3324 (MCC)
//
// Supported by 
//   National Center for Supercomputing Applications, UIUC
//   Materials Computation Center, UIUC
//////////////////////////////////////////////////////////////////
// -*- C++ -*-
#include "QMCWaveFunctions/OrbitalBase.h"
#include "QMCWaveFunctions/DiffOrbitalBase.h"
#include "QMCWaveFunctions/ProxyOrbital.h"

namespace qmcplusplus {
  OrbitalBase::OrbitalBase(): 
    Optimizable(true), UseBuffer(true), Counter(0),
    LogValue(1.0),PhaseValue(0.0)
#if !defined(ENABLE_SMARTPOINTER)
  ,dPsi(0)
#endif
  { }

  void OrbitalBase::setDiffOrbital(DiffOrbitalBasePtr d)
  {
#if defined(ENABLE_SMARTPOINTER)
    dPsi=DiffOrbitalBasePtr(d);
#else
    dPsi=d;
#endif
  }

  //void OrbitalBase::checkOutVariables(const opt_variables_type& o)
  //{
  //  myVars.getIndex(o);
  //}
  void OrbitalBase::evaluateDerivatives(ParticleSet& P, RealType ke0, 
      const opt_variables_type& active,
      vector<RealType>& dlogpsi, vector<RealType>& dhpsioverpsi)
  {
#if defined(ENABLE_SMARTPOINTER)
    if(dPsi.get()) 
#else
    if(dPsi) 
#endif
      dPsi->evaluateDerivatives(P, ke0, active, dlogpsi, dhpsioverpsi);
  }

  ///** makeClone uses optVars  to determine if it will make a clone (deepcopy) 
  // * or make a ProxyOrbital.
  // */
  //OrbitalBasePtr OrbitalBase::makeClone(ParticleSet& tpq,  int i)
  //{
  //  int loc=-1;
  //  int iii=0;
  //  while(loc<0 && iii<myVars.size())
  //  {
  //    if(myVars.Index[iii]==i) loc=iii;
  //    ++iii;
  //  }
  //  if(loc<0)
  //    return makeProxy(tpq,this);
  //  else
  //    return makeClone(tpq,true);
  //}

  /*@todo makeClone should be a pure virtual function 
   */
  OrbitalBasePtr OrbitalBase::makeClone(ParticleSet& tpq, bool deepcopy)
  {
    if(deepcopy)
    {
      APP_ABORT("OrbitalBase::makeClone is not implemented for a deep copy.");
    }

    return makeProxy(tpq,this);
  }

  OrbitalBasePtr OrbitalBase::makeProxy(ParticleSet& tpq, OrbitalBase* org)
  {
    OrbitalBase* proxy= new ProxyOrbital(tpq,org);
#if defined(ENABLE_SMARTPOINTER)
    return OrbitalBasePtr(proxy);
#else
    return proxy;
#endif
  }
}
/***************************************************************************
 * $RCSfile$   $Author: jnkim $
 * $Revision: 1770 $   $Date: 2007-02-17 17:45:38 -0600 (Sat, 17 Feb 2007) $
 * $Id: OrbitalBase.h 1770 2007-02-17 23:45:38Z jnkim $ 
 ***************************************************************************/

