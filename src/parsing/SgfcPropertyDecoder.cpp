// Project includes
#include "../../include/ISgfcBoardSizeProperty.h"
#include "../../include/ISgfcGameTypeProperty.h"
#include "../../include/ISgfcPropertyFactory.h"
#include "../../include/SgfcColor.h"
#include "../../include/SgfcConstants.h"
#include "../../include/SgfcDouble.h"
#include "../../include/SgfcGameType.h"
#include "../../include/SgfcPlusPlusFactory.h"
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
#include "../document/typedpropertyvalue/go/SgfcGoMovePropertyValue.h"
#include "../document/typedpropertyvalue/go/SgfcGoPointPropertyValue.h"
#include "../document/typedpropertyvalue/go/SgfcGoStonePropertyValue.h"
#include "../document/SgfcComposedPropertyValue.h"
#include "../document/SgfcPropertyMetaInfo.h"
#include "../SgfcPrivateConstants.h"
#include "propertyvaluetypedescriptor/SgfcPropertyBasicValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyComposedValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyDualValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyElistValueTypeDescriptor.h"
#include "propertyvaluetypedescriptor/SgfcPropertyListValueTypeDescriptor.h"
#include "SgfcPropertyDecoder.h"
#include "SgfcValueConverter.h"

// SGFC includes
extern "C"
{
  #include <stdio.h>  // required to define size_t and FILE which are used in all.h
  #include "../../sgfc/all.h"
}

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

namespace LibSgfcPlusPlus
{
  SgfcPropertyDecoder::SgfcPropertyDecoder(const Property* sgfProperty, SgfcGameType gameType, SgfcBoardSize boardSize)
    : sgfProperty(sgfProperty)
    , propertyMetaInfo(new SgfcPropertyMetaInfo(GetPropertyTypeInternal(), gameType))
    , boardSize(boardSize)
  {
  }

  SgfcPropertyDecoder::~SgfcPropertyDecoder()
  {
  }

  SgfcPropertyType SgfcPropertyDecoder::GetPropertyType() const
  {
    return this->propertyMetaInfo->GetPropertyType();
  }

  SgfcPropertyType SgfcPropertyDecoder::GetPropertyTypeInternal() const
  {
    switch (this->sgfProperty->id)
    {
      case TKN_NONE:
        return SgfcPropertyType::Unknown;
      case TKN_UNKNOWN:
        // TODO: The token enumeration does not have values for all properties
        // that we support.
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
        message << "GetPropertyTypeInternal: Unexpected SGFC token value " << sgfProperty->id << " (" << this->sgfProperty->idstr << ")";
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

    std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor =
      this->propertyMetaInfo->GetValueTypeDescriptor();
    SgfcPropertyValueTypeDescriptorType descriptorType =
      valueTypeDescriptor->GetDescriptorType();

    switch (descriptorType)
    {
      case SgfcPropertyValueTypeDescriptorType::DualValueType:
      {
        const SgfcPropertyDualValueTypeDescriptor* dualValueTypeDescriptor =
          valueTypeDescriptor->ToDualValueTypeDescriptor();

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
            valueTypeDescriptor->ToElistValueTypeDescriptor()->GetDescriptorListValueType()->GetDescriptorElementValueType();

          propertyValues =
            GetSgfcPropertyValuesFromSgfPropertyValue(sgfPropertyValue, elementValueTypeDescriptor);
        }

        break;
      }
      case SgfcPropertyValueTypeDescriptorType::ListValueType:
      {
        std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor =
          valueTypeDescriptor->ToListValueTypeDescriptor()->GetDescriptorElementValueType();

        propertyValues =
          GetSgfcPropertyValuesFromSgfPropertyValue(sgfPropertyValue, elementValueTypeDescriptor);

        break;
      }
      case SgfcPropertyValueTypeDescriptorType::ComposedValueType:
      case SgfcPropertyValueTypeDescriptorType::BasicValueType:
      {
        std::shared_ptr<ISgfcPropertyValue> propertyValue =
          GetSgfcPropertyValueFromSgfPropertyValue(sgfPropertyValue, valueTypeDescriptor);

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
        message << "GetPropertyValues: Unexpected descriptor type " << static_cast<int>(descriptorType) << " (" << this->sgfProperty->idstr << ")";
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
      // SgfcConstants::BoardSizeNone is OK because SgfcPropertyType::GM does
      // not require a valid board size.
      SgfcPropertyDecoder propertyDecoder(sgfProperty, SgfcGameType::Unknown, SgfcConstants::BoardSizeNone);
      SgfcPropertyType propertyType = propertyDecoder.GetPropertyType();
      if (propertyType != SgfcPropertyType::GM)
      {
        sgfProperty = sgfProperty->next;
        continue;
      }

      std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues = propertyDecoder.GetPropertyValues();

      auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();

      if (propertyValues.size() == 0)
      {
        std::shared_ptr<ISgfcGameTypeProperty> property = propertyFactory->CreateGameTypeProperty();
        return property->GetGameType();
      }
      else
      {
        std::shared_ptr<ISgfcPropertyValue> propertyValue = propertyValues.front();

        if (propertyValue->IsComposedValue())
          return SgfcGameType::Unknown;

        // This is just to verify that we actually have an
        // ISgfcNumberPropertyValue object - if not the factory would throw
        const ISgfcNumberPropertyValue* numberValue = propertyValue->ToSingleValue()->ToNumberValue();
        if (numberValue == nullptr)
            return SgfcGameType::Unknown;

        // Can't use numberValue directly, the factory wants an std::shared_ptr.
        // std::dynamic_pointer_cast performs a downcast and packages the result
        // into a shared_ptr, all in one go. Note: We can't use
        // std::static_pointer_cast because of multiple inheritance.
        std::shared_ptr<ISgfcNumberPropertyValue> numberValueSharedPtr =
          std::dynamic_pointer_cast<ISgfcNumberPropertyValue>(propertyValue);

        std::shared_ptr<ISgfcGameTypeProperty> property = propertyFactory->CreateGameTypeProperty(
          numberValueSharedPtr);

        return property->GetGameType();
      }
    }

    // SgfcPropertyType::GM is not present. This is not the same as when the
    // property is present but has no value, so we can't return
    // SgfcPrivateConstants::DefaultGameType.
    return SgfcGameType::Unknown;
  }

  SgfcBoardSize SgfcPropertyDecoder::GetBoardSizeFromNode(const Node* sgfNode, SgfcGameType gameType)
  {
    Property* sgfProperty = sgfNode->prop;
    while (sgfProperty)
    {
      // SgfcConstants::BoardSizeNone is OK because SgfcPropertyType::SZ does
      // not require a valid board size.
      SgfcPropertyDecoder propertyDecoder(sgfProperty, SgfcGameType::Unknown, SgfcConstants::BoardSizeNone);
      SgfcPropertyType propertyType = propertyDecoder.GetPropertyType();
      if (propertyType != SgfcPropertyType::SZ)
      {
        sgfProperty = sgfProperty->next;
        continue;
      }

      std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues = propertyDecoder.GetPropertyValues();

      auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();

      if (propertyValues.size() == 0)
      {
        std::shared_ptr<ISgfcBoardSizeProperty> property = propertyFactory->CreateBoardSizeProperty();
        return property->GetBoardSize(gameType);
      }
      else
      {
        std::shared_ptr<ISgfcPropertyValue> propertyValue = propertyValues.front();

        try
        {
          if (propertyValue->IsComposedValue())
          {
            std::shared_ptr<ISgfcComposedPropertyValue> composedValueSharedPtr =
              std::dynamic_pointer_cast<ISgfcComposedPropertyValue>(propertyValue);

            std::shared_ptr<ISgfcBoardSizeProperty> property = propertyFactory->CreateBoardSizeProperty(
              composedValueSharedPtr);

            return property->GetBoardSize(gameType);
          }
          else
          {
            std::shared_ptr<ISgfcNumberPropertyValue> numberValueSharedPtr =
              std::dynamic_pointer_cast<ISgfcNumberPropertyValue>(propertyValue);

            std::shared_ptr<ISgfcBoardSizeProperty> property = propertyFactory->CreateBoardSizeProperty(
              numberValueSharedPtr);

            return property->GetBoardSize(gameType);
          }
        }
        catch (std::logic_error&)
        {
          // The factory throws a logic_error in several cases. It's much too
          // complicated to check all these cases before using the factory,
          // so we let the factory do the checks and handle the exception here.
          return SgfcConstants::BoardSizeNone;
        }
      }
    }

    return SgfcConstants::BoardSizeNone;
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
          if (sgfPropertyValue->value != SgfcPrivateConstants::EmptyString)
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
        message << "GetSgfcPropertyValueFromSgfPropertyValue: Unexpected descriptor type: " << static_cast<int>(descriptorType);
        throw std::logic_error(message.str());
      }
    }
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer,
    SgfcPropertyValueType propertyValueType) const
  {
    SgfcGameType gameType = this->propertyMetaInfo->GetGameType();

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
      {
        // We have to remove line breaks ourselves because of a bug in SGFC.
        // If the SimpleText value is the second value of a composed value then
        // SGFC does not detect and remove hard and soft line breaks in all
        // cases. If it's the first value of a composed value, then SGFC seems
        // to be able to handle line breaks correctly. Examples:
        // - Property "AP": SGFC detects neither hard nor soft line breaks.
        // - Property "LB": SGFC detects soft line breaks, but not hard line
        //   breaks.
        // TODO: Currently we treat all SimpleText values for line breaks, but
        // we should do it only if the SimpleText value is the second value of
        // a composed value.
        std::string rawValueWithoutLineBreaks = RemoveSimpleTextLineBreaks(rawPropertyValueBuffer);

        std::string rawValueWithoutEscapeCharacters = RemoveSimpleTextAndTextEscapeCharacters(rawValueWithoutLineBreaks);
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcSimpleTextPropertyValue(
          rawValueWithoutEscapeCharacters,
          rawValueWithoutEscapeCharacters));
        break;
      }
      case SgfcPropertyValueType::Text:
      {
        // When compared to how SimpleText values are processed above, then in
        // theory we would have to invoke RemoveTextLineBreaks() here. In
        // practice no line break removal is necessary for Text values because
        // there is no property which has a composed value with Text as one (or
        // both) of the two value types.

        std::string rawValueWithoutEscapeCharacters = RemoveSimpleTextAndTextEscapeCharacters(rawPropertyValueBuffer);
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcTextPropertyValue(
          rawValueWithoutEscapeCharacters,
          rawValueWithoutEscapeCharacters));
        break;
      }
      case SgfcPropertyValueType::Point:
        if (gameType == SgfcGameType::Go)
        {
          propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoPointPropertyValue(
           rawPropertyValueBuffer,
           this->boardSize));
        }
        else
        {
          std::string rawValueWithoutEscapeCharacters = RemoveMandatoryEscapeCharacters(rawPropertyValueBuffer);
          propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcPointPropertyValue(
           rawValueWithoutEscapeCharacters));
        }
        break;
      case SgfcPropertyValueType::Move:
        if (gameType == SgfcGameType::Go)
        {
          SgfcColor color = GetColorForPropertyType();
          propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoMovePropertyValue(
           rawPropertyValueBuffer, this->boardSize, color));
        }
        else
        {
          std::string rawValueWithoutEscapeCharacters = RemoveMandatoryEscapeCharacters(rawPropertyValueBuffer);
          propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcMovePropertyValue(
           rawValueWithoutEscapeCharacters));
        }
        break;
      case SgfcPropertyValueType::Stone:
        if (gameType == SgfcGameType::Go)
        {
          SgfcColor color = GetColorForPropertyType();
          propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoStonePropertyValue(
           rawPropertyValueBuffer, this->boardSize, color));
        }
        else
        {
          std::string rawValueWithoutEscapeCharacters = RemoveMandatoryEscapeCharacters(rawPropertyValueBuffer);
          propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcStonePropertyValue(
           rawValueWithoutEscapeCharacters));
        }
        break;
      case SgfcPropertyValueType::Unknown:
        propertyValue = std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcUnknownPropertyValue(
          rawPropertyValueBuffer));
        break;
      case SgfcPropertyValueType::None:
      default:
        std::stringstream message;
        message << "GetSgfcPropertyValueFromSgfPropertyValue: Unexpected property value type: " << static_cast<int>(propertyValueType);
        throw std::logic_error(message.str());
    }

    return propertyValue;
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcNumberPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    SgfcValueConverter valueConverter;

    SgfcNumber numberValue;
    std::string outTypeConversionErrorMessage;

    bool success = valueConverter.TryConvertStringToNumberValue(
      rawPropertyValueBuffer,
      numberValue,
      outTypeConversionErrorMessage);

    if (success)
    {
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcNumberPropertyValue(
        rawPropertyValueBuffer,
        numberValue));
    }
    else
    {
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcNumberPropertyValue(
        rawPropertyValueBuffer,
        outTypeConversionErrorMessage));
    }
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcRealPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    SgfcValueConverter valueConverter;

    SgfcReal realValue;
    std::string outTypeConversionErrorMessage;

    bool success = valueConverter.TryConvertStringToRealValue(
      rawPropertyValueBuffer,
      realValue,
      outTypeConversionErrorMessage);

    if (success)
    {
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcRealPropertyValue(
        rawPropertyValueBuffer,
        realValue));
    }
    else
    {
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcRealPropertyValue(
        rawPropertyValueBuffer,
        outTypeConversionErrorMessage));
    }
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcDoublePropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    SgfcValueConverter valueConverter;

    SgfcDouble doubleValue;
    std::string outTypeConversionErrorMessage;

    bool success = valueConverter.TryConvertStringToDoubleValue(
      rawPropertyValueBuffer,
      doubleValue,
      outTypeConversionErrorMessage);

    if (success)
    {
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcDoublePropertyValue(
        rawPropertyValueBuffer,
        doubleValue));
    }
    else
    {
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcDoublePropertyValue(
        rawPropertyValueBuffer,
        outTypeConversionErrorMessage));
    }
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcColorPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    SgfcValueConverter valueConverter;

    SgfcColor colorValue;
    std::string outTypeConversionErrorMessage;

    bool success = valueConverter.TryConvertStringToColorValue(
      rawPropertyValueBuffer,
      colorValue,
      outTypeConversionErrorMessage);

    if (success)
    {
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcColorPropertyValue(
        rawPropertyValueBuffer,
        colorValue));
    }
    else
    {
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcColorPropertyValue(
        rawPropertyValueBuffer,
        outTypeConversionErrorMessage));
    }
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

  SgfcColor SgfcPropertyDecoder::GetColorForPropertyType() const
  {
    SgfcPropertyType propertyType = this->propertyMetaInfo->GetPropertyType();

    switch (propertyType)
    {
      case SgfcPropertyType::B:
      case SgfcPropertyType::AB:
      case SgfcPropertyType::GB:
      case SgfcPropertyType::BR:
      case SgfcPropertyType::BT:
      case SgfcPropertyType::PB:
      case SgfcPropertyType::BL:
      case SgfcPropertyType::OB:
      case SgfcPropertyType::TB:
      case SgfcPropertyType::BO:
        return SgfcColor::Black;
      case SgfcPropertyType::W:
      case SgfcPropertyType::AW:
      case SgfcPropertyType::GW:
      case SgfcPropertyType::WR:
      case SgfcPropertyType::WT:
      case SgfcPropertyType::PW:
      case SgfcPropertyType::WL:
      case SgfcPropertyType::OW:
      case SgfcPropertyType::TW:
      case SgfcPropertyType::WO:
        return SgfcColor::White;
      default:
        // If we get here the caller made a mistake. The method must only
        // be called for properties that have a color associated with them.
        // Notably, all properties that have the value types Stone and Move
        // are allowed because for those properties the property type specifies
        // which color the placed stone has or which player made the move.
        std::stringstream message;
        message << "GetColorForPropertyType: Unable to determine color for property type " << static_cast<int>(propertyType) << " (" << this->sgfProperty->idstr << ")";
        throw std::logic_error(message.str());
    }
  }

  std::string SgfcPropertyDecoder::RemoveSimpleTextLineBreaks(
    const std::string& rawPropertyValue) const
  {
    // Soft line breaks have to be removed according to the SGF standard
    std::string result = std::regex_replace(
      rawPropertyValue,
      SgfcPrivateConstants::EscapedLineEndingsRegex,
      SgfcPrivateConstants::EmptyString);

    // Hard line breaks have to be replaced by a space characters according to
    // the SGF standard
    // Note: Process hard line breaks after soft line breaks. If w processed
    // them before we would replace soft line breaks too.
    return std::regex_replace(
      result,
      SgfcPrivateConstants::UnescapedLineEndingsRegex,
      SgfcPrivateConstants::SpaceCharacter);
  }

  std::string SgfcPropertyDecoder::RemoveTextLineBreaks(
    const std::string& rawPropertyValue) const
  {
    // Soft line breaks have to be removed according to the SGF standard
    return std::regex_replace(
      rawPropertyValue,
      SgfcPrivateConstants::EscapedLineEndingsRegex,
      SgfcPrivateConstants::EmptyString);

    // Hard line breaks are preserved according to the SGF standard
  }

  std::string SgfcPropertyDecoder::RemoveSimpleTextAndTextEscapeCharacters(
    const std::string& rawPropertyValue) const
  {
    std::string result = RemoveMandatoryEscapeCharacters(rawPropertyValue);

    result = std::regex_replace(
      result,
      SgfcPrivateConstants::EscapedComposedValueSeparatorTokenRegex,
      SgfcPrivateConstants::ComposedValueSeparatorToken);

    // Escape characters must be removed last so that we don't remove the escape
    // characters from other escape sequences.
    result = std::regex_replace(
      result,
      SgfcPrivateConstants::EscapedEscapeCharacterRegex,
      SgfcPrivateConstants::EscapeCharacterToken);

    return result;
  }

  std::string SgfcPropertyDecoder::RemoveMandatoryEscapeCharacters(
    const std::string& rawPropertyValue) const
  {
    return std::regex_replace(
      rawPropertyValue,
      SgfcPrivateConstants::EscapedPropertyValueEndTokenRegex,
      SgfcPrivateConstants::PropertyValueEndToken);
  }
}
