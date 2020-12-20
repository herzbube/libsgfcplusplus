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

// Project includes
#include "SgfcPropertyValueTypeDescriptorConstants.h"

namespace LibSgfcPlusPlus
{
  // Basic value type descriptors
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorNone = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::None));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Number));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorReal = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Real));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Double));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorColor = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Color));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::SimpleText));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorText = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Text));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorPoint = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Point));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorMove = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Move));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorStone = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Stone));
  const std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorUnknown = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Unknown));

  // List value type descriptors, consisting of only basic value type descriptors
  const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorPoint));
  const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfStone = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorStone));

  // Composed value type descriptors
  const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorComposedNumberAndNumber = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorNumber, DescriptorNumber));
  const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorComposedSimpleTextAndSimpleText = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorSimpleText, DescriptorSimpleText));
  const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorComposedPointAndPoint = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorPoint, DescriptorPoint));
  const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorComposedStoneAndStone = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorStone, DescriptorStone));
  const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorComposedPointAndSimpleText = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorPoint, DescriptorSimpleText));
  const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorComposedNumberAndSimpleText = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorNumber, DescriptorSimpleText));
  const std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorComposedStoneAndPoint = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorPoint, DescriptorStone));

  // List value type descriptors, consisting of composed value type descriptors
  const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfComposedPointAndSimpleText = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorComposedPointAndSimpleText));
  const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfComposedStoneAndPoint = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorComposedStoneAndPoint));
  const std::shared_ptr<SgfcPropertyListValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfComposedPointAndPoint = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorComposedPointAndPoint));

  // Dual value type descriptors
  const std::shared_ptr<SgfcPropertyDualValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorNumberOrComposedNumberAndNumber = std::shared_ptr<SgfcPropertyDualValueTypeDescriptor>(
    new SgfcPropertyDualValueTypeDescriptor(DescriptorNumber, DescriptorComposedNumberAndNumber));
  const std::shared_ptr<SgfcPropertyDualValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorNoneOrComposedNumberAndSimpleText = std::shared_ptr<SgfcPropertyDualValueTypeDescriptor>(
    new SgfcPropertyDualValueTypeDescriptor(DescriptorNone, DescriptorComposedNumberAndSimpleText));

  // Elist value type descriptors
  const std::shared_ptr<SgfcPropertyElistValueTypeDescriptor> SgfcPropertyValueTypeDescriptorConstants::DescriptorElistOfPoint = std::shared_ptr<SgfcPropertyElistValueTypeDescriptor>(
    new SgfcPropertyElistValueTypeDescriptor(DescriptorListOfPoint));
}
