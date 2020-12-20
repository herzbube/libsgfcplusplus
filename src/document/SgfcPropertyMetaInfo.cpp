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
#include "../parsing/propertyvaluetypedescriptor/SgfcPropertyBasicValueTypeDescriptor.h"
#include "../parsing/propertyvaluetypedescriptor/SgfcPropertyComposedValueTypeDescriptor.h"
#include "../parsing/propertyvaluetypedescriptor/SgfcPropertyDualValueTypeDescriptor.h"
#include "../parsing/propertyvaluetypedescriptor/SgfcPropertyElistValueTypeDescriptor.h"
#include "../parsing/propertyvaluetypedescriptor/SgfcPropertyListValueTypeDescriptor.h"
#include "SgfcPropertyMetaInfo.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  // ----------------------------------------------------------------------
  // The constants below are kept here instead of in SgfcPrivateConstants.cpp
  // because their scope is extremely narrow, they are used only by the
  // SgfcPropertyMetaInfo class. If the constants were in SgfcPrivateConstants
  // they would have to be exposed in the header file SgfcPrivateConstants.h.
  // Not only would this increase the size of the header file by quite a margin,
  // it would also make a number of types visible to parts of the library that
  // are not interested in value type descriptors at all.
  // ----------------------------------------------------------------------

  // Basic value type descriptors
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorNone = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::None));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorNumber = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Number));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorReal = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Real));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorDouble = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Double));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorColor = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Color));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorSimpleText = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::SimpleText));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorText = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Text));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorPoint = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Point));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorMove = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Move));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorStone = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Stone));
  std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor> DescriptorUnknown = std::shared_ptr<SgfcPropertyBasicValueTypeDescriptor>(
    new SgfcPropertyBasicValueTypeDescriptor(SgfcPropertyValueType::Unknown));

  // List value type descriptors, consisting of only basic value type descriptors
  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfPoint = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorPoint));
  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfStone = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorStone));

  // Composed value type descriptors
  std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedNumberAndNumber = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorNumber, DescriptorNumber));
  std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedSimpleTextAndSimpleText = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorSimpleText, DescriptorSimpleText));
  std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedPointAndPoint = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorPoint, DescriptorPoint));
  std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedPointAndSimpleText = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorPoint, DescriptorSimpleText));
  std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedNumberAndSimpleText = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorNumber, DescriptorSimpleText));
  std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor> DescriptorComposedStoneAndPoint = std::shared_ptr<SgfcPropertyComposedValueTypeDescriptor>(
    new SgfcPropertyComposedValueTypeDescriptor(DescriptorPoint, DescriptorStone));

  // List value type descriptors, consisting of composed value type descriptors
  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfComposedPointAndSimpleText = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorComposedPointAndSimpleText));
  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfComposedStoneAndPoint = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorComposedStoneAndPoint));
  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfComposedPointAndPoint = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorComposedPointAndPoint));

  // Dual value type descriptors
  std::shared_ptr<SgfcPropertyDualValueTypeDescriptor> DescriptorNumberOrComposedNumberAndNumber = std::shared_ptr<SgfcPropertyDualValueTypeDescriptor>(
    new SgfcPropertyDualValueTypeDescriptor(DescriptorNumber, DescriptorComposedNumberAndNumber));
  std::shared_ptr<SgfcPropertyDualValueTypeDescriptor> DescriptorNoneOrComposedNumberAndSimpleText = std::shared_ptr<SgfcPropertyDualValueTypeDescriptor>(
    new SgfcPropertyDualValueTypeDescriptor(DescriptorNone, DescriptorComposedNumberAndSimpleText));

  // Elist value type descriptors
  std::shared_ptr<SgfcPropertyElistValueTypeDescriptor> DescriptorElistOfPoint = std::shared_ptr<SgfcPropertyElistValueTypeDescriptor>(
    new SgfcPropertyElistValueTypeDescriptor(DescriptorListOfPoint));

  // ----------------------------------------------------------------------
  // End of constants
  // ----------------------------------------------------------------------

  SgfcPropertyMetaInfo::SgfcPropertyMetaInfo(SgfcPropertyType propertyType, SgfcGameType gameType)
    : propertyType(propertyType)
    , gameType(gameType)
    , valueTypeDescriptor(GetValueTypeDescriptorInternal())
  {
  }

  SgfcPropertyMetaInfo::~SgfcPropertyMetaInfo()
  {
  }

  SgfcPropertyType SgfcPropertyMetaInfo::GetPropertyType() const
  {
    return this->propertyType;
  }

  SgfcGameType SgfcPropertyMetaInfo::GetGameType() const
  {
    return this->gameType;
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyMetaInfo::GetValueTypeDescriptor() const
  {
    return this->valueTypeDescriptor;
  }

  bool SgfcPropertyMetaInfo::CanPropertyHaveValueType(SgfcPropertyValueType propertyValueType) const
  {
    SgfcPropertyValueTypeDescriptorType descriptorType = this->valueTypeDescriptor->GetDescriptorType();
    switch (descriptorType)
    {
      case SgfcPropertyValueTypeDescriptorType::DualValueType:
      {
        return CanPropertyHaveValueTypeInternal(
          this->valueTypeDescriptor->ToDualValueTypeDescriptor(),
          propertyValueType);
      }
      case SgfcPropertyValueTypeDescriptorType::ElistValueType:
      {
        return CanPropertyHaveValueTypeInternal(
          this->valueTypeDescriptor->ToElistValueTypeDescriptor(),
          propertyValueType);
      }
      case SgfcPropertyValueTypeDescriptorType::ListValueType:
      {
        return CanPropertyHaveValueTypeInternal(
          this->valueTypeDescriptor->ToListValueTypeDescriptor(),
          propertyValueType);
      }
      case SgfcPropertyValueTypeDescriptorType::ComposedValueType:
      case SgfcPropertyValueTypeDescriptorType::BasicValueType:
      {
        return CanPropertyHaveValueTypeInternal(
          this->valueTypeDescriptor,
          propertyValueType);
      }
      default:
      {
        std::stringstream message;
        message << "CanPropertyHaveValueType: Unexpected descriptor type " << static_cast<int>(descriptorType);
        throw std::logic_error(message.str());
      }
    }
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyMetaInfo::GetValueTypeDescriptorInternal() const
  {
    switch (this->propertyType)
    {
      // ----------------------------------------------------------------------
      // Standard properties from FF4
      // ----------------------------------------------------------------------
      case SgfcPropertyType::B:
        return DescriptorMove;
      case SgfcPropertyType::KO:
        return DescriptorNone;
      case SgfcPropertyType::MN:
        return DescriptorNumber;
      case SgfcPropertyType::W:
        return DescriptorMove;

      case SgfcPropertyType::AB:
        return DescriptorListOfStone;
      case SgfcPropertyType::AE:
        return DescriptorListOfPoint;
      case SgfcPropertyType::AW:
        return DescriptorListOfStone;
      case SgfcPropertyType::PL:
        return DescriptorColor;

      case SgfcPropertyType::C:
        return DescriptorText;
      case SgfcPropertyType::DM:
        return DescriptorDouble;
      case SgfcPropertyType::GB:
        return DescriptorDouble;
      case SgfcPropertyType::GW:
        return DescriptorDouble;
      case SgfcPropertyType::HO:
        return DescriptorDouble;
      case SgfcPropertyType::N:
        return DescriptorSimpleText;
      case SgfcPropertyType::UC:
        return DescriptorDouble;
      case SgfcPropertyType::V:
        return DescriptorReal;

      case SgfcPropertyType::BM:
        return DescriptorDouble;
      case SgfcPropertyType::DO:
        return DescriptorNone;
      case SgfcPropertyType::IT:
        return DescriptorNone;
      case SgfcPropertyType::TE:
        return DescriptorDouble;

      case SgfcPropertyType::AR:
        return DescriptorListOfComposedPointAndPoint;
      case SgfcPropertyType::CR:
        return DescriptorListOfPoint;
      case SgfcPropertyType::DD:
        return DescriptorElistOfPoint;
      case SgfcPropertyType::LB:
        return DescriptorListOfComposedPointAndSimpleText;
      case SgfcPropertyType::LN:
        return DescriptorListOfComposedPointAndPoint;
      case SgfcPropertyType::MA:
        return DescriptorListOfPoint;
      case SgfcPropertyType::SL:
        return DescriptorListOfPoint;
      case SgfcPropertyType::SQ:
        return DescriptorListOfPoint;
      case SgfcPropertyType::TR:
        return DescriptorListOfPoint;

      case SgfcPropertyType::AP:
        return DescriptorComposedSimpleTextAndSimpleText;
      case SgfcPropertyType::CA:
        return DescriptorSimpleText;
      case SgfcPropertyType::FF:
        return DescriptorNumber;
      case SgfcPropertyType::GM:
        return DescriptorNumber;
      case SgfcPropertyType::ST:
        return DescriptorNumber;
      case SgfcPropertyType::SZ:
        return DescriptorNumberOrComposedNumberAndNumber;

      case SgfcPropertyType::AN:
        return DescriptorSimpleText;
      case SgfcPropertyType::BR:
        return DescriptorSimpleText;
      case SgfcPropertyType::BT:
        return DescriptorSimpleText;
      case SgfcPropertyType::CP:
        return DescriptorSimpleText;
      case SgfcPropertyType::DT:
        return DescriptorSimpleText;
      case SgfcPropertyType::EV:
        return DescriptorSimpleText;
      case SgfcPropertyType::GC:
        return DescriptorText;
      case SgfcPropertyType::GN:
        return DescriptorSimpleText;
      case SgfcPropertyType::ON:
        return DescriptorSimpleText;
      case SgfcPropertyType::OT:
        return DescriptorSimpleText;
      case SgfcPropertyType::PB:
        return DescriptorSimpleText;
      case SgfcPropertyType::PC:
        return DescriptorSimpleText;
      case SgfcPropertyType::PW:
        return DescriptorSimpleText;
      case SgfcPropertyType::RE:
        return DescriptorSimpleText;
      case SgfcPropertyType::RO:
        return DescriptorSimpleText;
      case SgfcPropertyType::RU:
        return DescriptorSimpleText;
      case SgfcPropertyType::SO:
        return DescriptorSimpleText;
      case SgfcPropertyType::TM:
        return DescriptorReal;
      case SgfcPropertyType::US:
        return DescriptorSimpleText;
      case SgfcPropertyType::WR:
        return DescriptorSimpleText;
      case SgfcPropertyType::WT:
        return DescriptorSimpleText;

      case SgfcPropertyType::BL:
        return DescriptorReal;
      case SgfcPropertyType::OB:
        return DescriptorNumber;
      case SgfcPropertyType::OW:
        return DescriptorNumber;
      case SgfcPropertyType::WL:
        return DescriptorReal;

      case SgfcPropertyType::FG:
        return DescriptorNoneOrComposedNumberAndSimpleText;
      case SgfcPropertyType::PM:
        return DescriptorNumber;
      case SgfcPropertyType::VW:
        return DescriptorElistOfPoint;

      // ----------------------------------------------------------------------
      // Standard properties from FF1-3
      // ----------------------------------------------------------------------
      case SgfcPropertyType::BS:
        return DescriptorNumber;
      case SgfcPropertyType::CH:
        return DescriptorDouble;
      case SgfcPropertyType::EL:
        return DescriptorNumber;
      case SgfcPropertyType::EX:
        return DescriptorMove;
      case SgfcPropertyType::ID:
        return DescriptorText;
      case SgfcPropertyType::L:
        return DescriptorListOfPoint;
      case SgfcPropertyType::LT:
        return DescriptorNone;
      case SgfcPropertyType::M:
        return DescriptorListOfPoint;
      case SgfcPropertyType::OM:
        return DescriptorNumber;
      case SgfcPropertyType::OP:
        return DescriptorReal;
      case SgfcPropertyType::OV:
        return DescriptorReal;
      case SgfcPropertyType::RG:
        return DescriptorListOfPoint;
      case SgfcPropertyType::SC:
        return DescriptorListOfPoint;
      case SgfcPropertyType::SE:
        if (this->gameType == SgfcGameType::LinesOfAction)
          return DescriptorPoint;
        else
          return DescriptorListOfPoint;
      case SgfcPropertyType::SI:
        return DescriptorDouble;
      case SgfcPropertyType::TC:
        return DescriptorNumber;
      case SgfcPropertyType::WS:
        return DescriptorNumber;

      // ----------------------------------------------------------------------
      // Game of Go properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::HA:
        if (this->gameType == SgfcGameType::Go)
          return DescriptorNumber;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::KM:
        if (this->gameType == SgfcGameType::Go)
          return DescriptorReal;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::TB:
        if (this->gameType == SgfcGameType::Go)
          return DescriptorElistOfPoint;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::TW:
        if (this->gameType == SgfcGameType::Go)
          return DescriptorElistOfPoint;
        else
          return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // Non-standard properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::Unknown:
        return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // If we get here a "case" statement is missing
      // ----------------------------------------------------------------------
      default:
        std::stringstream message;
        message << "GetValueTypeDescriptor: Unexpected property type value " << static_cast<int>(this->propertyType);
        throw std::invalid_argument(message.str());
    }
  }

  bool SgfcPropertyMetaInfo::CanPropertyHaveValueTypeInternal(
    const SgfcPropertyDualValueTypeDescriptor* dualValueTypeDescriptor,
    SgfcPropertyValueType propertyValueType) const
  {
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1 =
      dualValueTypeDescriptor->GetDescriptorValueType1();
    bool canPropertyHaveValueType = CanPropertyHaveValueTypeInternal(descriptorValueType1, propertyValueType);
    if (canPropertyHaveValueType)
      return true;

    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2 =
      dualValueTypeDescriptor->GetDescriptorValueType2();
    canPropertyHaveValueType = CanPropertyHaveValueTypeInternal(descriptorValueType2, propertyValueType);
    if (canPropertyHaveValueType)
      return true;

    return false;
  }

  bool SgfcPropertyMetaInfo::CanPropertyHaveValueTypeInternal(
    const SgfcPropertyElistValueTypeDescriptor* elistValueTypeDescriptor,
    SgfcPropertyValueType propertyValueType) const
  {
    if (propertyValueType == SgfcPropertyValueType::None)
      return true;

    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor =
      this->valueTypeDescriptor->ToElistValueTypeDescriptor()->GetDescriptorListValueType()->GetDescriptorElementValueType();

    return CanPropertyHaveValueTypeInternal(elementValueTypeDescriptor, propertyValueType);
  }

  bool SgfcPropertyMetaInfo::CanPropertyHaveValueTypeInternal(
    const SgfcPropertyListValueTypeDescriptor* listValueTypeDescriptor,
    SgfcPropertyValueType propertyValueType) const
  {
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor =
      this->valueTypeDescriptor->ToListValueTypeDescriptor()->GetDescriptorElementValueType();

    return CanPropertyHaveValueTypeInternal(elementValueTypeDescriptor, propertyValueType);
  }

  bool SgfcPropertyMetaInfo::CanPropertyHaveValueTypeInternal(
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor,
    SgfcPropertyValueType propertyValueType) const
  {
    SgfcPropertyValueTypeDescriptorType descriptorType = valueTypeDescriptor->GetDescriptorType();
    switch (descriptorType)
    {
      case SgfcPropertyValueTypeDescriptorType::ComposedValueType:
      {
        const SgfcPropertyComposedValueTypeDescriptor* composedValueTypeDescriptor =
          valueTypeDescriptor->ToComposedValueTypeDescriptor();
        SgfcPropertyValueType basicValueType1 =
          composedValueTypeDescriptor->GetDescriptorValueType1()->ToBasicValueTypeDescriptor()->GetValueType();
        SgfcPropertyValueType basicValueType2 =
          composedValueTypeDescriptor->GetDescriptorValueType2()->ToBasicValueTypeDescriptor()->GetValueType();

        if (basicValueType1 == propertyValueType)
          return true;
        if (basicValueType2 == propertyValueType)
          return true;
        else
          return false;
      }
      case SgfcPropertyValueTypeDescriptorType::BasicValueType:
      {
        SgfcPropertyValueType basicValueType =
          valueTypeDescriptor->ToBasicValueTypeDescriptor()->GetValueType();

        return (basicValueType == propertyValueType);
      }
      // This private helper method only supports composed value type
      // descriptors and basic value type descriptors. Any other descriptors
      // are a coding error.
      default:
      {
        std::stringstream message;
        message << "CanPropertyHaveValueTypeInternal: Unexpected descriptor type: " << static_cast<int>(descriptorType);
        throw std::invalid_argument(message.str());
      }
    }
  }
}
