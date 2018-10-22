/// \file GPUOrbitalTensors.h

#pragma once
#include "GPUDataDependentObject.h"
#include "GPUStreamTensor.h"
#include "GPUConstTensor.h"
#include "GPUMetricTensor.h"

/// Constructs Orbital Tensors and all related quantities from 4-Vectors
	/**
	This class constructs all orbital Tensors and the quantities used in their
	calculation (Barrier factors etc.) from the four momenta of the relevant
	particles a, b and c in a two-particle decay \f$ a \longrightarrow b c \f$. 
	Follows Zou and Bugg, arxiv:hep-ph/0211457v2 and Dulat and Zou,
	arxiv:hep-ph/0508087v1. All objects are created during construction; as
	ususal, actual calculations are only performed upon calling the () operator
	of the relevant stream tensor objects.
	**/
class GPUOrbitalTensors :
	public GPUDataDependentObject
{
public:
	/// Constructor with a stream for the parent object 4-momentum
	/**
	\param _list: List where this Object is registered, used for cache handling of the created objects;
	\param _pa: 4-Momentum of the mother particle (stream);
	\param _pb: 4-Momentum of decay particle;
	\param _pc: 4-Momentum of decay particle;
	\param _r:  Radius for the Potential used in the Blatt-Weisskopf barrier factors (fm)
	**/
	GPUOrbitalTensors(GPUDataDependentObjectList * _list, GPUStreamVector & _pa, GPUStreamVector & _pb, GPUStreamVector & _pc, float _r = 0.728656f);

	/// Constructor with a const for the parent object 4-momentum
	/**
	\param _list: List where this Object is registered, used for cache handling of the created objects;
	\param _pa: 4-Momentum of the mother particle (GPU const vector);
	\param _pb: 4-Momentum of decay particle;
	\param _pc: 4-Momentum of decay particle;
	\param _r:  Radius for the Potential used in the Blatt-Weisskopf barrier factors (fm)
	**/
	GPUOrbitalTensors(GPUDataDependentObjectList * _list, GPUConstVector & _pa, GPUStreamVector & _pb, GPUStreamVector & _pc, float _r = 0.728656f);

	/// Constructor with a float4 for the parent object 4-momentum
	/**
	\param _list: List where this Object is registered, used for cache handling of the created objects;
	\param _pa: 4-Momentum of the mother particle (float4);
	\param _pb: 4-Momentum of decay particle;
	\param _pc: 4-Momentum of decay particle;
	\param _r:  Radius for the Potential used in the Blatt-Weisskopf barrier factors (fm)
	**/
	GPUOrbitalTensors(GPUDataDependentObjectList * _list, float4 & _pa, GPUStreamVector & _pb, GPUStreamVector & _pc, float _r = 0.728656f);

	/// Destructor
	virtual ~GPUOrbitalTensors(void);

	/// Reset meber streams if necessary
	void Reset(int index);

	/// Reset parts of member streams if necessary
	void Reset(int index, int block);

	/// Get Radius for the Potential used in the Blatt-Weisskopf barrier factors
	float GetRadius(){return mRadius;};


	/// Get mother particle momentum stream (if present - check!)
	GPUStreamVector *           GetPaStream(){return mstreampa;};
	/// Get mother particle momentum CONST (if present - check!)
	GPUConstVector  *           GetPaConst(){return mconstpa;};
	/// Get mother particle momentum
	GPUTensor &                 GetPa(){return *mpa;};
	/// Get daughter particle momentum
	GPUStreamVector &           GetPb(){return mpb;};
	/// Get other daugther particle momentum
	GPUStreamVector &           GetPc(){return mpc;};

	/// Get the metric tensor g_mu_nu
	GPUConstTensor2 &           GetMetric(){return *mmetric;};


	/// Get Spin 0 (S-wave) Orbital Tensor (==1)
	GPUConstScalar  &			Spin0OrbitalTensor(){return *new GPUConstScalar(1.0f);};
	/// Get Spin 1 (P-wave) Orbital Tensor
	GPUStreamVector &			Spin1OrbitalTensor(){return *mSpin1OrbitalTensor;};
	/// Get Spin 2 (D-wave) Orbital Tensor
	GPUStreamTensor2 &			Spin2OrbitalTensor(){return *mSpin2OrbitalTensor;};
	/// Get Spin 3 (F-wave) Orbital Tensor
	GPUStreamTensor3 &			Spin3OrbitalTensor(){return *mSpin3OrbitalTensor;};
	/// Get Spin 4 (G-wave) Orbital Tensor
	GPUStreamTensor4 &			Spin4OrbitalTensor(){return *mSpin4OrbitalTensor;};



	/// Get relative momentum of decay particles (r = pb-pc)
	GPUStreamVector &			RelativeMomentum(){return *mr;};

	/// Get Blatt Weisskopf barrier factor for spin 1
	GPUStreamScalar &			Barrier1() {return *mB1;};
	/// Get Blatt Weisskopf barrier factor for spin 2
	GPUStreamScalar &			Barrier2() {return *mB2;};
	/// Get Blatt Weisskopf barrier factor for spin 3
	GPUStreamScalar &			Barrier3() {return *mB3;};
	/// Get Blatt Weisskopf barrier factor for spin 4
	GPUStreamScalar &			Barrier4() {return *mB4;};

	/// Contract the Spin 3 spin projection operator (a rank 6 Tensor) with a rank two tensor
	/// (thus avoiding a "bare" rank 6 tensor)
	/** This is used in Zou and Bugg, formula 44 **/
	GPUStreamTensor4 & Spin3ProjectTensor2(GPUStreamTensor2& T);

protected:
	/// Set up all the needed objects
	void MakeTensors();

	/// The metric tensor
	GPUMetricTensor * mmetric;

	/// The stream variant of the mother particle momentum
	GPUStreamVector * mstreampa;
	/// The const variant of the mother particle momentum
	GPUConstVector  * mconstpa;
	/// The mother particle momentum
	GPUTensor       * mpa;
	/// First daughter particle momentum
	GPUStreamVector & mpb;
	/// Second daughter particle momentum
	GPUStreamVector & mpc;

	/// Radius for the Potential used in the Blatt-Weisskopf barrier factors
	const float mRadius;

	/// Mass squared of the mother particle
	GPUTensor       * msa;
	/// Mass squared of the first daughter particle
	GPUStreamScalar * msb;
	/// Mass squared of the second daughter particle
	GPUStreamScalar * msc;

	/// Relative momentum of the daughters \f$ r_{\mu}\f$
	GPUStreamVector  * mr;
	/// \f$ \tilde{g}_{\mu\nu}(p_{a}) \f$, stream version
	GPUStreamTensor2 * mguv_tilde_pa_stream;
	/// \f$ \tilde{g}_{\mu\nu}(p_{a}) \f$, const version
	GPUConstTensor2  * mguv_tilde_pa_const;
	/// \f$ Q^{2}_{abc} \f$
	GPUStreamScalar  * mQ2abc;
	/// \f$ \tilde{r}_{\mu} \f$
	GPUStreamVector  * mr_tilde;
	/// \f$ \tilde{r}_{\mu}^{2} \f$
	GPUStreamScalar  * mr_tilde2;
	
	/// Spin 1 barrier factor
	GPUStreamScalar  * mB1;
	/// Spin 2 barrier factor
	GPUStreamScalar  * mB2;
	/// Spin 3 barrier factor
	GPUStreamScalar  * mB3;
	/// Spin 4 barrier factor
	GPUStreamScalar  * mB4;
	
	/// Spin 1 Orbital Tensor
	GPUStreamVector  * mSpin1OrbitalTensor;
	/// Spin 2 Orbital Tensor
	GPUStreamTensor2 * mSpin2OrbitalTensor;
	/// Spin 3 Orbital Tensor
	GPUStreamTensor3 * mSpin3OrbitalTensor;
	/// Spin 4 Orbital Tensor
	GPUStreamTensor4 * mSpin4OrbitalTensor;

};
