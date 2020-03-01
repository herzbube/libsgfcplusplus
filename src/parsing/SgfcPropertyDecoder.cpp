// Project includes
#include "../../include/SgfcColor.h"
#include "../../include/SgfcDouble.h"
#include "../../include/SgfcGameType.h"
#include "../document/typedpropertyvalue/SgfcColorPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcDoublePropertyValue.h"
#include "../document/typedpropertyvalue/SgfcMovePropertyValue.h"
#include "../document/typedpropertyvalue/SgfcNumberPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcPointPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcRealPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcSimpleTextPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcStonePropertyValue.h"
#include "../document/typedpropertyvalue/SgfcTextPropertyValue.h"
#include "../document/typedpropertyvalue/SgfcUnknownPropertyValue.h"
#include "../document/SgfcComposedPropertyValue.h"
#include "../SgfcConstants.h"
#include "propertyvaluetypedescriptor/SgfcPropertyBasicValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyComposedValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyDualValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyElistValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyListValueTypeDescriptor.h"
#include "SgfcPropertyDecoder.h"

// SGFC includes
extern "C"
{
  #include <stdio.h>  // required to define size_t and FILE which are used in all.h
  #include "../../sgfc/all.h"
}

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>
#include <charconv>

namespace LibSgfcPlusPlus
{
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
  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfMove = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorMove));
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
  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfComposedSimpleTextAndSimpleText = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorComposedSimpleTextAndSimpleText));
  std::shared_ptr<SgfcPropertyListValueTypeDescriptor> DescriptorListOfComposedStoneAndPoint = std::shared_ptr<SgfcPropertyListValueTypeDescriptor>(
    new SgfcPropertyListValueTypeDescriptor(DescriptorComposedStoneAndPoint));

  // Dual value type descriptors
  std::shared_ptr<SgfcPropertyDualValueTypeDescriptor> DescriptorNumberOrComposedNumberAndNumber = std::shared_ptr<SgfcPropertyDualValueTypeDescriptor>(
    new SgfcPropertyDualValueTypeDescriptor(DescriptorNumber, DescriptorComposedNumberAndNumber));
  std::shared_ptr<SgfcPropertyDualValueTypeDescriptor> DescriptorNoneOrComposedNumberAndSimpleText = std::shared_ptr<SgfcPropertyDualValueTypeDescriptor>(
    new SgfcPropertyDualValueTypeDescriptor(DescriptorNone, DescriptorComposedNumberAndSimpleText));

  // Elist value type descriptors
  std::shared_ptr<SgfcPropertyElistValueTypeDescriptor> DescriptorElistOfPoint = std::shared_ptr<SgfcPropertyElistValueTypeDescriptor>(
    new SgfcPropertyElistValueTypeDescriptor(DescriptorListOfPoint));

  SgfcPropertyDecoder::SgfcPropertyDecoder(const Property* sgfProperty, SgfcGameType gameType)
    : sgfProperty(sgfProperty)
    , propertyType(GetPropertyTypeInternal())
    , gameType(gameType)
    , valueTypeDescriptor(GetValueTypeDescriptor())
  {
  }

  SgfcPropertyDecoder::~SgfcPropertyDecoder()
  {
  }

  SgfcPropertyType SgfcPropertyDecoder::GetPropertyType() const
  {
    return this->propertyType;
  }

  SgfcPropertyType SgfcPropertyDecoder::GetPropertyTypeInternal() const
  {
    switch (this->sgfProperty->id)
    {
      case TKN_NONE:
        return SgfcPropertyType::Unknown;
      case TKN_UNKNOWN:
        return SgfcPropertyType::Unknown;
      case TKN_B:
        return SgfcPropertyType::B;
      case TKN_W:
        return SgfcPropertyType::W;
      case TKN_AB:
        return SgfcPropertyType::AB;
      case TKN_AW:
        return SgfcPropertyType::AW;
      case TKN_AE:
        return SgfcPropertyType::AE;
      case TKN_N:
        return SgfcPropertyType::N;
      case TKN_C:
        return SgfcPropertyType::C;
      case TKN_BL:
        return SgfcPropertyType::BL;
      case TKN_WL:
        return SgfcPropertyType::WL;
      case TKN_OB:
        return SgfcPropertyType::OB;
      case TKN_OW:
        return SgfcPropertyType::OW;
      case TKN_FF:
        return SgfcPropertyType::FF;
      case TKN_GM:
        return SgfcPropertyType::GM;
      case TKN_SZ:
        return SgfcPropertyType::SZ;
      case TKN_ST:
        return SgfcPropertyType::ST;
      case TKN_CA:
        return SgfcPropertyType::CA;
      case TKN_AP:
        return SgfcPropertyType::AP;
      case TKN_GN:
        return SgfcPropertyType::GN;
      case TKN_GC:
        return SgfcPropertyType::GC;
      case TKN_PB:
        return SgfcPropertyType::PB;
      case TKN_PW:
        return SgfcPropertyType::PW;
      case TKN_BR:
        return SgfcPropertyType::BR;
      case TKN_WR:
        return SgfcPropertyType::WR;
      case TKN_PC:
        return SgfcPropertyType::PC;
      case TKN_DT:
        return SgfcPropertyType::DT;
      case TKN_RE:
        return SgfcPropertyType::RE;
      case TKN_KM:
        return SgfcPropertyType::KM;
      case TKN_KI:
        return SgfcPropertyType::KI;
      case TKN_HA:
        return SgfcPropertyType::HA;
      case TKN_TM:
        return SgfcPropertyType::TM;
      case TKN_EV:
        return SgfcPropertyType::EV;
      case TKN_RO:
        return SgfcPropertyType::RO;
      case TKN_SO:
        return SgfcPropertyType::SO;
      case TKN_US:
        return SgfcPropertyType::US;
      case TKN_BT:
        return SgfcPropertyType::BT;
      case TKN_WT:
        return SgfcPropertyType::WT;
      case TKN_RU:
        return SgfcPropertyType::RU;
      case TKN_AN:
        return SgfcPropertyType::AN;
      case TKN_OT:
        return SgfcPropertyType::OT;
      case TKN_ON:
        return SgfcPropertyType::ON;
      case TKN_CP:
        return SgfcPropertyType::CP;
      case TKN_L:
        return SgfcPropertyType::L;
      case TKN_LB:
        return SgfcPropertyType::LB;
      case TKN_AR:
        return SgfcPropertyType::AR;
      case TKN_LN:
        return SgfcPropertyType::LN;
      case TKN_M:
        return SgfcPropertyType::M;
      case TKN_MA:
        return SgfcPropertyType::MA;
      case TKN_TR:
        return SgfcPropertyType::TR;
      case TKN_CR:
        return SgfcPropertyType::CR;
      case TKN_TB:
        return SgfcPropertyType::TB;
      case TKN_TW:
        return SgfcPropertyType::TW;
      case TKN_SQ:
        return SgfcPropertyType::SQ;
      case TKN_SL:
        return SgfcPropertyType::SL;
      case TKN_DD:
        return SgfcPropertyType::DD;
      case TKN_PL:
        return SgfcPropertyType::PL;
      case TKN_V:
        return SgfcPropertyType::V;
      case TKN_GB:
        return SgfcPropertyType::GB;
      case TKN_GW:
        return SgfcPropertyType::GW;
      case TKN_UC:
        return SgfcPropertyType::UC;
      case TKN_DM:
        return SgfcPropertyType::DM;
      case TKN_TE:
        return SgfcPropertyType::TE;
      case TKN_BM:
        return SgfcPropertyType::BM;
      case TKN_DO:
        return SgfcPropertyType::DO;
      case TKN_IT:
        return SgfcPropertyType::IT;
      case TKN_HO:
        return SgfcPropertyType::HO;
      case TKN_KO:
        return SgfcPropertyType::KO;
      case TKN_FG:
        return SgfcPropertyType::FG;
      case TKN_MN:
        return SgfcPropertyType::MN;
      case TKN_VW:
        return SgfcPropertyType::VW;
      case TKN_PM:
        return SgfcPropertyType::PM;
      case TKN_CH:
        return SgfcPropertyType::CH;
      case TKN_SI:
        return SgfcPropertyType::SI;
      case TKN_BS:
        return SgfcPropertyType::BS;
      case TKN_WS:
        return SgfcPropertyType::WS;
      case TKN_ID:
        return SgfcPropertyType::ID;
      case TKN_TC:
        return SgfcPropertyType::TC;
      case TKN_OM:
        return SgfcPropertyType::OM;
      case TKN_OP:
        return SgfcPropertyType::OP;
      case TKN_OV:
        return SgfcPropertyType::OV;
      case TKN_LT:
        return SgfcPropertyType::LT;
      case TKN_RG:
        return SgfcPropertyType::RG;
      case TKN_SC:
        return SgfcPropertyType::SC;
      case TKN_SE:
        return SgfcPropertyType::SE;
      case TKN_EL:
        return SgfcPropertyType::EL;
      case TKN_EX:
        return SgfcPropertyType::EX;
      default:
        // If we get here a "case" statement is missing
        std::stringstream message;
        message << "Unexpected SGFC token value: " << sgfProperty->id;
        throw std::logic_error(message.str());
    }
  }

  std::string SgfcPropertyDecoder::GetPropertyName() const
  {
    return this->sgfProperty->idstr;
  }

  std::vector<std::shared_ptr<ISgfcPropertyValue>> SgfcPropertyDecoder::GetPropertyValues() const
  {
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;

    PropValue* sgfPropertyValue = sgfProperty->value;
    if (sgfPropertyValue == nullptr)
    {
      // TODO: This is unexpected - SGFC is supposed to provide us with a
      // non-null PropValue object even if the property value is
      // SgfcPropertyValueType::None

      return propertyValues;
    }

    SgfcPropertyValueTypeDescriptorType descriptorType = this->valueTypeDescriptor->GetDescriptorType();
    switch (descriptorType)
    {
      case SgfcPropertyValueTypeDescriptorType::DualValueType:
      {
        const SgfcPropertyDualValueTypeDescriptor* dualValueTypeDescriptor =
          this->valueTypeDescriptor->ToDualValueTypeDescriptor();

        std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType1 =
          dualValueTypeDescriptor->GetDescriptorValueType1();
        std::shared_ptr<ISgfcPropertyValue> propertyValueType1 =
          GetSgfcPropertyValueFromSgfPropertyValue(sgfPropertyValue, descriptorValueType1);

        bool doesPropertyValueType1HaveTypedValues = DoesSgfcPropertyHaveTypedValues(propertyValueType1);
        if (doesPropertyValueType1HaveTypedValues)
        {
          // Property value had the first of the two possible value types. We
          // don't need to try out the second of the two possible value types.

          propertyValues.push_back(propertyValueType1);
        }
        else
        {
          std::shared_ptr<ISgfcPropertyValueTypeDescriptor> descriptorValueType2 =
            dualValueTypeDescriptor->GetDescriptorValueType2();
          std::shared_ptr<ISgfcPropertyValue> propertyValueType2 =
            GetSgfcPropertyValueFromSgfPropertyValue(sgfPropertyValue, descriptorValueType2);

          bool doesPropertyValueType2HaveTypedValues = DoesSgfcPropertyHaveTypedValues(propertyValueType2);
          if (doesPropertyValueType2HaveTypedValues)
          {
            // Property value had the second of the two possible value types
            propertyValues.push_back(propertyValueType1);
          }
          else
          {
            // Property value did not have any of the two possible value types.
            // The library client has to deal with the situation.
            propertyValues.push_back(propertyValueType1);
          }
        }

        break;
      }
      case SgfcPropertyValueTypeDescriptorType::ElistValueType:
      {
        if (strlen(sgfPropertyValue->value) == 0)
        {
          // Probing showed that the property has no value
        }
        else
        {
          std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor =
            this->valueTypeDescriptor->ToElistValueTypeDescriptor()->GetDescriptorListValueType()->GetDescriptorElementValueType();

          propertyValues =
            GetSgfcPropertyValuesFromSgfPropertyValue(sgfPropertyValue, elementValueTypeDescriptor);
        }

        break;
      }
      case SgfcPropertyValueTypeDescriptorType::ListValueType:
      {
        std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor =
          this->valueTypeDescriptor->ToListValueTypeDescriptor()->GetDescriptorElementValueType();

        propertyValues =
          GetSgfcPropertyValuesFromSgfPropertyValue(sgfPropertyValue, elementValueTypeDescriptor);

        break;
      }
      case SgfcPropertyValueTypeDescriptorType::ComposedValueType:
      case SgfcPropertyValueTypeDescriptorType::BasicValueType:
      {
        std::shared_ptr<ISgfcPropertyValue> propertyValue =
          GetSgfcPropertyValueFromSgfPropertyValue(sgfPropertyValue, this->valueTypeDescriptor);

        if (propertyValue == nullptr)
        {
          // nullptr means it was a basic value type descriptor with basic value
          // type SgfcPropertyValueType::None. We ignore these. Example: The
          // property "IT" should have an empty list of property values.
        }
        else
        {
          propertyValues.push_back(propertyValue);
        }

        break;
      }
      default:
      {
        std::stringstream message;
        message << "Unexpected descriptor type: " << static_cast<int>(descriptorType);
        throw std::logic_error(message.str());
      }
    }

    return propertyValues;
  }

  SgfcGameType SgfcPropertyDecoder::GetGameTypeFromNode(const Node* sgfNode)
  {
    Property* sgfProperty = sgfNode->prop;
    while (sgfProperty)
    {
      SgfcPropertyDecoder propertyDecoder(sgfProperty, SgfcGameType::Unknown);
      SgfcPropertyType propertyType = propertyDecoder.GetPropertyType();
      if (propertyType != SgfcPropertyType::GM)
      {
        sgfProperty = sgfProperty->next;
        continue;
      }

      std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues = propertyDecoder.GetPropertyValues();
      if (propertyValues.size() == 0)
        return SgfcConstants::DefaultGameType;

      std::shared_ptr<ISgfcPropertyValue> propertyValue = propertyValues.front();
      const ISgfcSinglePropertyValue* singlePropertyValue = propertyValue->ToSingleValue();
      if (! singlePropertyValue->HasTypedValue())
          return SgfcGameType::Unknown;

      return SgfcPropertyDecoder::MapNumberValueToGameType(
        singlePropertyValue->ToNumberValue()->GetNumberValue());
    }

    // SgfcPropertyType::GM is not present. This is not the same as when the
    // property is present but has no value, so we can't return
    // SgfcConstants::DefaultGameType.
    return SgfcGameType::Unknown;
  }

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyDecoder::GetValueTypeDescriptor() const
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
        return DescriptorListOfMove;
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
        return DescriptorComposedPointAndPoint;
      case SgfcPropertyType::CR:
        return DescriptorListOfMove;
      case SgfcPropertyType::DD:
        return DescriptorElistOfPoint;
      case SgfcPropertyType::LB:
        return DescriptorListOfComposedPointAndSimpleText;
      case SgfcPropertyType::LN:
        return DescriptorComposedPointAndPoint;
      case SgfcPropertyType::MA:
        return DescriptorListOfMove;
      case SgfcPropertyType::SL:
        return DescriptorListOfMove;
      case SgfcPropertyType::SQ:
        return DescriptorListOfMove;
      case SgfcPropertyType::TR:
        return DescriptorListOfMove;

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
        return DescriptorListOfMove;
      case SgfcPropertyType::LT:
        return DescriptorNone;
      case SgfcPropertyType::M:
        return DescriptorListOfMove;
      case SgfcPropertyType::OM:
        return DescriptorNumber;
      case SgfcPropertyType::OP:
        return DescriptorReal;
      case SgfcPropertyType::OV:
        return DescriptorReal;
      case SgfcPropertyType::RG:
        return DescriptorListOfMove;
      case SgfcPropertyType::SC:
        return DescriptorListOfMove;
      case SgfcPropertyType::SE:
        /// @todo For the game of Lines of Action in FF4 this is defined as
        /// DescriptorPoint.
        return DescriptorListOfMove;
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
      // Game of Backgammon properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::CO:
        if (this->gameType == SgfcGameType::Backgammon)
          return DescriptorSimpleText;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::CV:
        if (this->gameType == SgfcGameType::Backgammon)
          return DescriptorNumber;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::DI:
        if (this->gameType == SgfcGameType::Backgammon)
          return DescriptorNumber;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::MI:
        if (this->gameType == SgfcGameType::Backgammon)
          return DescriptorListOfComposedSimpleTextAndSimpleText;
        else
          return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // Game of Lines of Action properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::IY:
        if (this->gameType == SgfcGameType::LinesOfAction)
          return DescriptorSimpleText;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::SU:
        if (this->gameType == SgfcGameType::LinesOfAction)
          return DescriptorSimpleText;
        else
          return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // Game of Hex properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::IS:
        if (this->gameType == SgfcGameType::Hex)
          return DescriptorListOfComposedSimpleTextAndSimpleText;
        else
          return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // Game of Amazons properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::AA:
        if (this->gameType == SgfcGameType::Amazons)
          return DescriptorListOfMove;
        else
          return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // Game of Octi properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::BO:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorListOfMove;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::WO:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorListOfMove;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::NP:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorNumber;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::NR:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorNumber;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::NS:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorNumber;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::CS:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorListOfStone;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::MS:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorListOfStone;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::SS:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorListOfStone;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::TS:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorListOfStone;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::RP:
        if (this->gameType == SgfcGameType::Octi)
          return DescriptorListOfStone;
        else
          return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // Properties for more than one game
      // ----------------------------------------------------------------------
      case SgfcPropertyType::AS:
        switch (this->gameType)
        {
          case SgfcGameType::Octi:
            return DescriptorListOfComposedStoneAndPoint;
          case SgfcGameType::LinesOfAction:
            return DescriptorSimpleText;
          default:
            return DescriptorUnknown;
        }
      case SgfcPropertyType::IP:
        switch (this->gameType)
        {
          case SgfcGameType::LinesOfAction:
          case SgfcGameType::Hex:
            return DescriptorSimpleText;
          default:
            return DescriptorUnknown;
        }

      // ----------------------------------------------------------------------
      // Non-standard properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::KI:
        if (this->gameType == SgfcGameType::Go)
          // The type comes from the SGFC README.
          return DescriptorNumber;
        else
          return DescriptorUnknown;
      case SgfcPropertyType::Unknown:
        return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // If we get here a "case" statement is missing
      // ----------------------------------------------------------------------
      default:
        std::stringstream message;
        message << "Unexpected property type value: " << static_cast<int>(this->propertyType);
        throw std::logic_error(message.str());
    }
  }

  /// @brief This method can handle a list of property values. All values must
  /// have the same value type described by @e elementValueTypeDescriptor.
  ///
  /// Each property value is either a single property value (if
  /// @a valueTypeDescriptor is an SgfcPropertyBasicValueTypeDescriptor), or a
  /// composed property value (if @a valueTypeDescriptor is an
  /// SgfcPropertyComposedValueTypeDescriptor).
  std::vector<std::shared_ptr<ISgfcPropertyValue>> SgfcPropertyDecoder::GetSgfcPropertyValuesFromSgfPropertyValue(
    PropValue* sgfPropertyValue,
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor) const
  {
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;

    while (sgfPropertyValue)
    {
      std::shared_ptr<ISgfcPropertyValue> propertyValue =
        GetSgfcPropertyValueFromSgfPropertyValue(sgfPropertyValue, elementValueTypeDescriptor);

      propertyValues.push_back(propertyValue);

      sgfPropertyValue = sgfPropertyValue->next;
    }

    return propertyValues;
  }

  /// @brief This method can handle a single property value (if
  /// @a valueTypeDescriptor is an SgfcPropertyBasicValueTypeDescriptor), or a
  /// composed property value (if @a valueTypeDescriptor is an
  /// SgfcPropertyComposedValueTypeDescriptor).
  std::shared_ptr<ISgfcPropertyValue> SgfcPropertyDecoder::GetSgfcPropertyValueFromSgfPropertyValue(
    PropValue* sgfPropertyValue,
    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor) const
  {
    SgfcPropertyValueTypeDescriptorType descriptorType = valueTypeDescriptor->GetDescriptorType();
    switch (descriptorType)
    {
      case SgfcPropertyValueTypeDescriptorType::ComposedValueType:
      {
        if (sgfPropertyValue->value2 == nullptr)
        {
          // TODO: SGFC gave us a single value, but we expected composed value
        }

        const SgfcPropertyComposedValueTypeDescriptor* composedValueTypeDescriptor =
          valueTypeDescriptor->ToComposedValueTypeDescriptor();
        SgfcPropertyValueType basicValueType1 =
          composedValueTypeDescriptor->GetDescriptorValueType1()->ToBasicValueTypeDescriptor()->GetValueType();
        SgfcPropertyValueType basicValueType2 =
          composedValueTypeDescriptor->GetDescriptorValueType2()->ToBasicValueTypeDescriptor()->GetValueType();

        std::shared_ptr<ISgfcSinglePropertyValue> propertyValue1 = GetSgfcPropertyValueFromSgfPropertyValue(
          sgfPropertyValue->value,
          basicValueType1);
        std::shared_ptr<ISgfcSinglePropertyValue> propertyValue2 = GetSgfcPropertyValueFromSgfPropertyValue(
          sgfPropertyValue->value2,
          basicValueType2);

        std::shared_ptr<ISgfcPropertyValue> propertyValue = std::shared_ptr<ISgfcPropertyValue>(new SgfcComposedPropertyValue(
          propertyValue1,
          propertyValue2));

        return propertyValue;
      }
      case SgfcPropertyValueTypeDescriptorType::BasicValueType:
      {
        if (sgfPropertyValue->value2 != nullptr)
        {
          // TODO: SGFC gave us a composed value, but we expected a single value
        }

        SgfcPropertyValueType basicValueType =
          valueTypeDescriptor->ToBasicValueTypeDescriptor()->GetValueType();

        if (basicValueType == SgfcPropertyValueType::None)
        {
          if (sgfPropertyValue->value != SgfcConstants::EmptyString)
          {
            // TODO: SGFC gave us a non-empty value, but we expected an empty value
          }

          return nullptr;
        }

        std::shared_ptr<ISgfcPropertyValue> propertyValue = GetSgfcPropertyValueFromSgfPropertyValue(
          sgfPropertyValue->value,
          basicValueType);

        return propertyValue;
      }
      // This private helper method only supports composed value type
      // descriptors and basic value type descriptors. Any other descriptors
      // are a coding error.
      default:
      {
        std::stringstream message;
        message << "Unexpected descriptor type: " << static_cast<int>(descriptorType);
        throw std::logic_error(message.str());
      }
    }
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer,
    SgfcPropertyValueType propertyValueType) const
  {
    std::shared_ptr<ISgfcSinglePropertyValue> propertyValue;

    switch (propertyValueType)
    {
      case SgfcPropertyValueType::Number:
        propertyValue = GetSgfcNumberPropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
        break;
      case SgfcPropertyValueType::Real:
        propertyValue = GetSgfcRealPropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
        break;
      case SgfcPropertyValueType::Double:
        propertyValue = GetSgfcDoublePropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
        break;
      case SgfcPropertyValueType::Color:
        propertyValue = GetSgfcColorPropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
        break;
      case SgfcPropertyValueType::SimpleText:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcSimpleTextPropertyValue(
         rawPropertyValueBuffer,
         rawPropertyValueBuffer));
        break;
      case SgfcPropertyValueType::Text:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcTextPropertyValue(
         rawPropertyValueBuffer,
         rawPropertyValueBuffer));
        break;
      case SgfcPropertyValueType::Point:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcPointPropertyValue(
         rawPropertyValueBuffer));
        break;
      case SgfcPropertyValueType::Move:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcMovePropertyValue(
         rawPropertyValueBuffer));
        break;
      case SgfcPropertyValueType::Stone:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcStonePropertyValue(
         rawPropertyValueBuffer));
        break;
      case SgfcPropertyValueType::Unknown:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcUnknownPropertyValue(
          rawPropertyValueBuffer));
        break;
      case SgfcPropertyValueType::None:
      default:
        std::stringstream message;
        message << "Unexpected property value type: " << static_cast<int>(propertyValueType);
        throw std::logic_error(message.str());
    }

    return propertyValue;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcNumberPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    // std::from_chars() only recognizes the minus sign, not the plus sign
    if (*rawPropertyValueBuffer == '+')
      rawPropertyValueBuffer++;

    std::string rawPropertyValue = rawPropertyValueBuffer;

    SgfcNumber numberValue;
    std::from_chars_result result = std::from_chars(
      rawPropertyValue.c_str(),
      rawPropertyValue.c_str() + rawPropertyValue.size(),
      numberValue);

    std::shared_ptr<ISgfcSinglePropertyValue> propertyValue;

    switch (result.ec)
    {
      case std::errc::invalid_argument:
         propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcNumberPropertyValue(
          rawPropertyValue,
          "Raw property string value is not an integer value"));
        break;
      case std::errc::result_out_of_range:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcNumberPropertyValue(
         rawPropertyValue,
         "Raw property string value is an integer value that is out of range"));
        break;
      default:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcNumberPropertyValue(
         rawPropertyValue,
         numberValue));
        break;
    }

    return propertyValue;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcRealPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    // std::from_chars() only recognizes the minus sign, not the plus sign
    if (*rawPropertyValueBuffer == '+')
      rawPropertyValueBuffer++;

    std::string rawPropertyValue = rawPropertyValueBuffer;

    std::shared_ptr<ISgfcSinglePropertyValue> propertyValue;

    try
    {
      // We would like to use std::from_chars, just like we do in
      // GetSgfcNumberPropertyValueFromSgfPropertyValue(). Unfortunately at the
      // time of writing clang still only has integer support for
      // std::from_chars.
      SgfcReal realValue = stod(rawPropertyValue);
      propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcRealPropertyValue(
       rawPropertyValue,
       realValue));
    }
    catch (std::invalid_argument& exception)
    {
      propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcRealPropertyValue(
       rawPropertyValue,
       "Raw property string value is not a floating point value"));
    }
    catch (std::out_of_range& exception)
    {
      propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcRealPropertyValue(
       rawPropertyValue,
       "Raw property string value is a floating point value that is out of range"));
    }

    return propertyValue;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcDoublePropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    std::string rawPropertyValue = rawPropertyValueBuffer;

    std::shared_ptr<ISgfcSinglePropertyValue> propertyValue;

    if (rawPropertyValueBuffer == SgfcConstants::DoubleNormalString)
    {
      propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcDoublePropertyValue(
       rawPropertyValue,
       SgfcDouble::Normal));
    }
    else if (rawPropertyValueBuffer == SgfcConstants::DoubleEmphasizedString)
      {
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcDoublePropertyValue(
         rawPropertyValue,
         SgfcDouble::Emphasized));
      }
    else
    {
      std::stringstream message;
      message
        << "Raw property string value is not a Double value. The SGF standard allows these values: "
        << SgfcConstants::DoubleNormalString << " or " << SgfcConstants::DoubleEmphasizedString;

      propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcDoublePropertyValue(
       rawPropertyValue,
       message.str()));
    }

    return propertyValue;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcColorPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    std::string rawPropertyValue = rawPropertyValueBuffer;

    std::shared_ptr<ISgfcSinglePropertyValue> propertyValue;

    if (rawPropertyValueBuffer == SgfcConstants::ColorBlackString)
    {
      propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcColorPropertyValue(
       rawPropertyValue,
       SgfcColor::Black));
    }
    else if (rawPropertyValueBuffer == SgfcConstants::ColorWhiteString)
      {
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcColorPropertyValue(
         rawPropertyValue,
         SgfcColor::White));
      }
    else
    {
      std::stringstream message;
      message
        << "Raw property string value is not a Color value. The SGF standard allows these values: "
        << SgfcConstants::ColorBlackString << " or " << SgfcConstants::ColorWhiteString;

      propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcDoublePropertyValue(
       rawPropertyValue,
       message.str()));
    }

    return propertyValue;
  }

  bool SgfcPropertyDecoder::DoesSgfcPropertyHaveTypedValues(
    const std::shared_ptr<ISgfcPropertyValue>& propertyValue) const
  {
    if (propertyValue->IsComposedValue())
    {
      const ISgfcComposedPropertyValue* composedPropertyValue = propertyValue->ToComposedValue();
      return (composedPropertyValue->GetValue1()->HasTypedValue() &&
              composedPropertyValue->GetValue2()->HasTypedValue());
    }
    else
    {
      const ISgfcSinglePropertyValue* singlePropertyValue = propertyValue->ToSingleValue();
      return singlePropertyValue->HasTypedValue();
    }
  }

  SgfcGameType SgfcPropertyDecoder::MapNumberValueToGameType(SgfcNumber gameTypeAsNumber)
  {
    switch (gameTypeAsNumber)
    {
      case 1:
        return SgfcGameType::Go;
      case 2:
        return SgfcGameType::Othello;
      case 3:
        return SgfcGameType::Chess;
      case 4:
        return SgfcGameType::GomokuAndRenju;
      case 5:
        return SgfcGameType::NineMensMorris;
      case 6:
        return SgfcGameType::Backgammon;
      case 7:
        return SgfcGameType::ChineseChess;
      case 8:
        return SgfcGameType::Shogi;
      case 9:
        return SgfcGameType::LinesOfAction;
      case 10:
        return SgfcGameType::Ataxx;
      case 11:
        return SgfcGameType::Hex;
      case 12:
        return SgfcGameType::Jungle;
      case 13:
        return SgfcGameType::Neutron;
      case 14:
        return SgfcGameType::PhilosophersFootball;
      case 15:
        return SgfcGameType::Quadrature;
      case 16:
        return SgfcGameType::Trax;
      case 17:
        return SgfcGameType::Tantrix;
      case 18:
        return SgfcGameType::Amazons;
      case 19:
        return SgfcGameType::Octi;
      case 20:
        return SgfcGameType::Gess;
      case 21:
        return SgfcGameType::Twixt;
      case 22:
        return SgfcGameType::Zertz;
      case 23:
        return SgfcGameType::Plateau;
      case 24:
        return SgfcGameType::Yinsh;
      case 25:
        return SgfcGameType::Punct;
      case 26:
        return SgfcGameType::Gobblet;
      case 27:
        return SgfcGameType::Hive;
      case 28:
        return SgfcGameType::Exxit;
      case 29:
        return SgfcGameType::Hnefatal;
      case 30:
        return SgfcGameType::Kuba;
      case 31:
        return SgfcGameType::Tripples;
      case 32:
        return SgfcGameType::Chase;
      case 33:
        return SgfcGameType::TumblingDown;
      case 34:
        return SgfcGameType::Sahara;
      case 35:
        return SgfcGameType::Byte;
      case 36:
        return SgfcGameType::Focus;
      case 37:
        return SgfcGameType::Dvonn;
      case 38:
        return SgfcGameType::Tamsk;
      case 39:
        return SgfcGameType::Gipf;
      case 40:
        return SgfcGameType::Kropki;
      default:
        return SgfcGameType::Unknown;
    }
  }
}
