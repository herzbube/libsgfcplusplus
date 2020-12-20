// -----------------------------------------------------------------------------
// Copyright 2020 Patrick Näf (herzbube@herzbube.ch)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -----------------------------------------------------------------------------

#pragma once

// Project includes
#include "propertyvaluetypedescriptor/SgfcPropertyBasicValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyComposedValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyDualValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyElistValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyListValueTypeDescriptor.h"

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcPropertyValueTypeDescriptorConstants class is a container
  /// class for library-internal property value type descriptor constants.
  ///
  /// @ingroup internals
  /// @ingroup library-support
  class SgfcPropertyValueTypeDescriptorConstants
  {
  public:
    /// @name Basic value type descriptors
    //@{
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorNone;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorNumber;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorReal;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorDouble;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorColor;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorSimpleText;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorText;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorPoint;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorMove;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorStone;
    static const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorUnknown;
    //@}

    /// @name List value type descriptors, consisting of only basic value type descriptors
    //@{
    static const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfPoint;
    static const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfStone;
    //@}

    /// @name Composed value type descriptors
    //@{
    static const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedNumberAndNumber;
    static const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedSimpleTextAndSimpleText;
    static const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedPointAndPoint;
    static const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedPointAndSimpleText;
    static const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedNumberAndSimpleText;
    static const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedStoneAndPoint;
    //@}

    /// @name List value type descriptors, consisting of composed value type descriptors
    //@{
    static const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfComposedPointAndSimpleText;
    static const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfComposedStoneAndPoint;
    static const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfComposedPointAndPoint;
    //@}

    /// @name Dual value type descriptors
    //@{
    static const std::shared_ptr<SgfcPropertyDualValueTypeDescriptor> DescriptorNumberOrComposedNumberAndNumber;
    static const std::shared_ptr<SgfcPropertyDualValueTypeDescriptor> DescriptorNoneOrComposedNumberAndSimpleText;
    //@}

    /// @name Elist value type descriptors
    //@{
    static const std::shared_ptr<SgfcPropertyElistValueTypeDescriptor> DescriptorElistOfPoint;
    //@}
  };
}
