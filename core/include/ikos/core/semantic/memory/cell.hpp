/*******************************************************************************
 *
 * \file
 * \brief Generic API for variables representing memory cells
 *
 * Author: Maxime Arthaud
 *
 * Contact: ikos@lists.nasa.gov
 *
 * Notices:
 *
 * Copyright (c) 2018 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Disclaimers:
 *
 * No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
 * ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS,
 * ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE
 * ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO
 * THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
 * ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
 * RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
 * RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
 * DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
 * IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
 *
 * Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
 * THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL
 * AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS
 * IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH
 * USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM,
 * RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
 * HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS,
 * AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.
 * RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE,
 * UNILATERAL TERMINATION OF THIS AGREEMENT.
 *
 ******************************************************************************/

#pragma once

#include <ikos/core/number/machine_int.hpp>
#include <ikos/core/support/mpl.hpp>

namespace ikos {
namespace core {
namespace memory {

/// \brief Traits for memory cell variables
///
/// A cell is a triple `(b, o, s)` modelling all bytes at address `b`, starting
/// at offset `o` up to `o + s - 1`.
///
/// Elements to provide:
///
/// static MemoryLocationRef base(VariableRef)
///   Return the base memory location of the given cell
///
/// static const MachineInt& offset(VariableRef)
///   Return the offset of the given cell
///
/// static const MachineInt& size(VariableRef)
///   Return the size of the given cell
template < typename VariableRef, typename MemoryLocationRef >
struct CellVariableTraits {};

/// \brief Check if a type implements CellVariableTraits
template < typename VariableRef,
           typename MemoryLocationRef,
           typename CellVariableTrait =
               CellVariableTraits< VariableRef, MemoryLocationRef >,
           typename = void >
struct IsCellVariable : std::false_type {};

template < typename VariableRef,
           typename MemoryLocationRef,
           typename CellVariableTrait >
struct IsCellVariable<
    VariableRef,
    MemoryLocationRef,
    CellVariableTrait,
    void_t< std::enable_if_t<
                std::is_same< MemoryLocationRef,
                              decltype(CellVariableTrait::base(
                                  std::declval< VariableRef >())) >::value >,
            std::enable_if_t<
                std::is_same< const MachineInt&,
                              decltype(CellVariableTrait::offset(
                                  std::declval< VariableRef >())) >::value >,
            std::enable_if_t<
                std::is_same< const MachineInt&,
                              decltype(CellVariableTrait::size(
                                  std::declval< VariableRef >())) >::value > > >
    : std::true_type {};

} // end namespace memory
} // end namespace core
} // end namespace ikos
