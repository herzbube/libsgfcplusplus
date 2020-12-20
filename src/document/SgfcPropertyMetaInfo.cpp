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
#include "../parsing/SgfcPropertyValueTypeDescriptorConstants.h"
#include "SgfcPropertyMetaInfo.h"

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
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
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorMove;
      case SgfcPropertyType::KO:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNone;
      case SgfcPropertyType::MN:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::W:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorMove;

      case SgfcPropertyType::AB:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfStone;
      case SgfcPropertyType::AE:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::AW:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfStone;
      case SgfcPropertyType::PL:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorColor;

      case SgfcPropertyType::C:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorText;
      case SgfcPropertyType::DM:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;
      case SgfcPropertyType::GB:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;
      case SgfcPropertyType::GW:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;
      case SgfcPropertyType::HO:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;
      case SgfcPropertyType::N:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::UC:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;
      case SgfcPropertyType::V:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorReal;

      case SgfcPropertyType::BM:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;
      case SgfcPropertyType::DO:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNone;
      case SgfcPropertyType::IT:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNone;
      case SgfcPropertyType::TE:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;

      case SgfcPropertyType::AR:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfComposedPointAndPoint;
      case SgfcPropertyType::CR:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::DD:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorElistOfPoint;
      case SgfcPropertyType::LB:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfComposedPointAndSimpleText;
      case SgfcPropertyType::LN:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfComposedPointAndPoint;
      case SgfcPropertyType::MA:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::SL:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::SQ:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::TR:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;

      case SgfcPropertyType::AP:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorComposedSimpleTextAndSimpleText;
      case SgfcPropertyType::CA:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::FF:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::GM:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::ST:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::SZ:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumberOrComposedNumberAndNumber;

      case SgfcPropertyType::AN:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::BR:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::BT:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::CP:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::DT:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::EV:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::GC:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorText;
      case SgfcPropertyType::GN:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::ON:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::OT:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::PB:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::PC:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::PW:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::RE:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::RO:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::RU:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::SO:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::TM:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorReal;
      case SgfcPropertyType::US:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::WR:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;
      case SgfcPropertyType::WT:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorSimpleText;

      case SgfcPropertyType::BL:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorReal;
      case SgfcPropertyType::OB:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::OW:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::WL:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorReal;

      case SgfcPropertyType::FG:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNoneOrComposedNumberAndSimpleText;
      case SgfcPropertyType::PM:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::VW:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorElistOfPoint;

      // ----------------------------------------------------------------------
      // Standard properties from FF1-3
      // ----------------------------------------------------------------------
      case SgfcPropertyType::BS:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::CH:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;
      case SgfcPropertyType::EL:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::EX:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorMove;
      case SgfcPropertyType::ID:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorText;
      case SgfcPropertyType::L:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::LT:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNone;
      case SgfcPropertyType::M:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::OM:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::OP:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorReal;
      case SgfcPropertyType::OV:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorReal;
      case SgfcPropertyType::RG:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::SC:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::SE:
        if (this->gameType == SgfcGameType::LinesOfAction)
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorPoint;
        else
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorListOfPoint;
      case SgfcPropertyType::SI:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorDouble;
      case SgfcPropertyType::TC:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
      case SgfcPropertyType::WS:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;

      // ----------------------------------------------------------------------
      // Game of Go properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::HA:
        if (this->gameType == SgfcGameType::Go)
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorNumber;
        else
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorUnknown;
      case SgfcPropertyType::KM:
        if (this->gameType == SgfcGameType::Go)
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorReal;
        else
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorUnknown;
      case SgfcPropertyType::TB:
        if (this->gameType == SgfcGameType::Go)
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorElistOfPoint;
        else
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorUnknown;
      case SgfcPropertyType::TW:
        if (this->gameType == SgfcGameType::Go)
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorElistOfPoint;
        else
          return SgfcPropertyValueTypeDescriptorConstants::DescriptorUnknown;

      // ----------------------------------------------------------------------
      // Non-standard properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::Unknown:
        return SgfcPropertyValueTypeDescriptorConstants::DescriptorUnknown;

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
