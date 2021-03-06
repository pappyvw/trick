/**
 * @if Er7UtilsUseGroups
 * @addtogroup Er7Utils
 * @{
 * @addtogroup Integration
 * @{
 * @endif
 */

/**
 * @file
 * Defines member functions for the class SymplecticEulerIntegratorConstructor.
 */

/*
Purpose: ()
*/

// System includes

// Interface includes
#include "er7_utils/interface/include/alloc.hh"

// Integration includes
#include "er7_utils/integration/core/include/integrator_constructor_utils.hh"
#include "er7_utils/integration/euler/include/euler_first_order_ode_integrator.hh"
#include "er7_utils/integration/core/include/single_cycle_integration_controls.hh"

// Model includes
#include "../include/symplectic_euler_integrator_constructor.hh"
#include "../include/symplectic_euler_second_order_ode_integrator.hh"


namespace er7_utils {

// Named constructor; create an SymplecticEulerIntegratorConstructor.
IntegratorConstructor*
SymplecticEulerIntegratorConstructor::create_constructor (
   void)
{
   return alloc::allocate_object<SymplecticEulerIntegratorConstructor> ();
}


// Create a duplicate of the constructor.
IntegratorConstructor *
SymplecticEulerIntegratorConstructor::create_copy (
   void)
const
{
   return alloc::allocate_object<
                 SymplecticEulerIntegratorConstructor,
                 const SymplecticEulerIntegratorConstructor &> (*this);
}


// Create an integration controls for SymplecticEuler.
IntegrationControls *
SymplecticEulerIntegratorConstructor::create_integration_controls (
   void)
const
{
   return integ_utils::allocate_controls<SingleCycleIntegrationControls> (1);
}


// Create an Euler integrator for a first order ODE.
FirstOrderODEIntegrator *
SymplecticEulerIntegratorConstructor::create_first_order_ode_integrator (
   unsigned int size,
   IntegrationControls & controls)
const
{
   return integ_utils::allocate_integrator<EulerFirstOrderODEIntegrator> (
             size, controls);
}


// Create a symplectic Euler integrator for a second order ODE.
SecondOrderODEIntegrator *
SymplecticEulerIntegratorConstructor::create_second_order_ode_integrator (
   unsigned int size,
   IntegrationControls & controls)
const
{
   return integ_utils::allocate_integrator<
                SymplecticEulerSimpleSecondOrderODEIntegrator> (
             size, controls);
}


// Create a symplectic Euler integrator for a second order ODE.
SecondOrderODEIntegrator *
SymplecticEulerIntegratorConstructor::
create_generalized_deriv_second_order_ode_integrator (
   unsigned int position_size,
   unsigned int velocity_size,
   const GeneralizedPositionDerivativeFunctions & deriv_funs,
   IntegrationControls & controls)
const
{
   return integ_utils::allocate_integrator<
                SymplecticEulerGeneralizedDerivSecondOrderODEIntegrator> (
             position_size, velocity_size, deriv_funs, controls);
}


// Create a symplectic Euler integrator for a second order ODE.
SecondOrderODEIntegrator *
SymplecticEulerIntegratorConstructor::
create_generalized_step_second_order_ode_integrator (
   unsigned int position_size,
   unsigned int velocity_size,
   const GeneralizedPositionStepFunctions & step_funs,
   IntegrationControls & controls)
const
{
   return integ_utils::allocate_integrator<
                SymplecticEulerGeneralizedStepSecondOrderODEIntegrator> (
             position_size, velocity_size, step_funs, controls);
}


}
/**
 * @if Er7UtilsUseGroups
 * @}
 * @}
 * @endif
 */
