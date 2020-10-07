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
#include "../SgfcUtility.h"
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
    , propertyMetaInfo(nullptr)
    , boardSize(boardSize)
  {
    if (this->sgfProperty == nullptr)
      throw std::domain_error("SgfcPropertyDecoder constructor failed: Property object is nullptr");

    if (this->sgfProperty->idstr == nullptr)
      throw std::domain_error("SgfcPropertyDecoder constructor failed: Property object's ID string is nullptr");

    // SGFC is supposed to provide us with a non-null PropValue object even if
    // the property value is SgfcPropertyValueType::None
    if (this->sgfProperty->value == nullptr)
      throw std::domain_error("SgfcPropertyDecoder constructor failed: Property object's value is nullptr");

    this->propertyMetaInfo = std::shared_ptr<SgfcPropertyMetaInfo>(
      new SgfcPropertyMetaInfo(GetPropertyTypeInternal(), gameType));
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
    return SgfcUtility::MapPropertyNameToPropertyType(this->sgfProperty->idstr);
  }

  std::string SgfcPropertyDecoder::GetPropertyName() const
  {
    return this->sgfProperty->idstr;
  }

  std::vector<std::shared_ptr<ISgfcPropertyValue>> SgfcPropertyDecoder::GetPropertyValues() const
  {
    std::vector<std::shared_ptr<ISgfcPropertyValue>> propertyValues;

    PropValue* sgfPropertyValue = this->sgfProperty->value;

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

        // The implementation of SgfcPropertyDualValueTypeDescriptor supports
        // any one of the following 4 cases:
        // - Case 1: 2x SgfcPropertyBasicValueTypeDescriptor
        // - Case 2: 1x SgfcPropertyBasicValueTypeDescriptor +
        //           1x SgfcPropertyComposedValueTypeDescriptor
        // - Case 3: 1x SgfcPropertyComposedValueTypeDescriptor +
        //           1x SgfcPropertyBasicValueTypeDescriptor
        // - Case 4: 2x SgfcPropertyComposedValueTypeDescriptor
        //
        // The following implementation covers only case 2, because the
        // SGF standard only describes properties that match this case (SZ and
        // FG) and because, consequently, the current implementation of
        // SgfcPropertyMetaInfo should only ever return dual value type
        // descriptors that match this case.
        if (dualValueTypeDescriptor->GetDescriptorValueType1()->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::BasicValueType)
        {
          std::stringstream message;
          message << "GetPropertyValues: Dual value type descriptor hhas unexpected first descriptor type " << static_cast<int>(dualValueTypeDescriptor->GetDescriptorValueType1()->GetDescriptorType());
          throw std::logic_error(message.str());
        }
        else if (dualValueTypeDescriptor->GetDescriptorValueType2()->GetDescriptorType() != SgfcPropertyValueTypeDescriptorType::ComposedValueType)
        {
          std::stringstream message;
          message << "GetPropertyValues: Dual value type descriptor hhas unexpected second descriptor type " << static_cast<int>(dualValueTypeDescriptor->GetDescriptorValueType2()->GetDescriptorType());
          throw std::logic_error(message.str());
        }

        std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor;
        if (sgfPropertyValue->value2 == nullptr)
          valueTypeDescriptor = dualValueTypeDescriptor->GetDescriptorValueType1();
        else
          valueTypeDescriptor = dualValueTypeDescriptor->GetDescriptorValueType2();

        std::shared_ptr<ISgfcPropertyValue> propertyValue =
          GetSgfcPropertyValueFromSgfPropertyValue(sgfPropertyValue, valueTypeDescriptor);

        if (propertyValue == nullptr)
        {
          // nullptr means it was a basic value type descriptor with basic value
          // type SgfcPropertyValueType::None. We ignore these. Example: The
          // property "FG".
        }
        else
        {
          propertyValues.push_back(propertyValue);
        }

        break;
      }
      case SgfcPropertyValueTypeDescriptorType::ElistValueType:
      {
        if (sgfPropertyValue->value == nullptr)
        {
          std::stringstream message;
          message << "GetPropertyValues: Expected an elist value, but SGFC gave us no value";
          throw std::domain_error(message.str());
        }
        else if (SgfcConstants::NoneValueString == sgfPropertyValue->value)
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
    if (sgfNode == nullptr)
      throw std::domain_error("Node object is nullptr");

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

      if (propertyValues.size() == 0)
      {
        // Valid SGF content should contain either a GM property with a value,
        // or no GM property at all. SGFC fixes a missing property by adding
        // one. SGFC also fixes a missing value by adding the default value 1
        // (i.e. game type Go). So in practice this should never occur.
        throw std::domain_error("Node object contains a GM property without a value");
      }
      else
      {
        std::shared_ptr<ISgfcPropertyValue> propertyValue = propertyValues.front();

        // This occurs if SgfcPropertyMetaInfo provides the wrong value type
        // descriptor
        if (propertyValue->IsComposedValue())
          throw std::logic_error("Node object contains a GM property that has a composed valued");

        // This occurs if SgfcPropertyMetaInfo provides the wrong value type
        // descriptor
        const ISgfcNumberPropertyValue* numberValue = propertyValue->ToSingleValue()->ToNumberValue();
        if (numberValue == nullptr)
          throw std::logic_error("Property value object is not an instance of ISgfcNumberPropertyValue");

        // This occurs if the property value string is not a Number string
        if (! numberValue->HasTypedValue())
          throw std::domain_error("Node object contains a GM property that does not have a Number value");

        // Can't use numberValue directly, the factory wants an std::shared_ptr.
        // std::dynamic_pointer_cast performs a downcast and packages the result
        // into a shared_ptr, all in one go. Note: We can't use
        // std::static_pointer_cast because of multiple inheritance.
        std::shared_ptr<ISgfcNumberPropertyValue> numberValueSharedPtr =
          std::dynamic_pointer_cast<ISgfcNumberPropertyValue>(propertyValue);

        auto propertyFactory = SgfcPlusPlusFactory::CreatePropertyFactory();
        std::shared_ptr<ISgfcGameTypeProperty> property = propertyFactory->CreateGameTypeProperty(
          numberValueSharedPtr);

        return property->GetGameType();
      }
    }

    return SgfcConstants::DefaultGameType;
  }

  SgfcBoardSize SgfcPropertyDecoder::GetBoardSizeFromNode(const Node* sgfNode, SgfcGameType gameType)
  {
    if (sgfNode == nullptr)
      throw std::domain_error("Node object is nullptr");

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
        // Valid SGF content should contain either an SZ property with a value,
        // or no SZ property at all. SGFC has different error correction
        // behavour depending on the game type:
        // - Go games: SGFC fixes a missing SZ property by adding the property
        //   with value 19. It fixes a missing value by adding the default
        //   value 19.
        // - Games that are not Go: SGFC does not add a missing property. It
        //   fixes a missing value by removing the property. Note that this is
        //   the behaviour even for Chess games where the SGF standard defines
        //   a default board size.
        //
        // Conclusion: In practice this should never occur.
        throw std::domain_error("Node object contains an SZ property without a value");
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

            // This occurs if SgfcPropertyMetaInfo provides the wrong value type
            // descriptor
            const ISgfcNumberPropertyValue* numberValue1 = composedValueSharedPtr->GetValue1()->ToSingleValue()->ToNumberValue();
            const ISgfcNumberPropertyValue* numberValue2 = composedValueSharedPtr->GetValue2()->ToSingleValue()->ToNumberValue();
            if (numberValue1 == nullptr || numberValue2 == nullptr)
              throw std::logic_error("Either the first or the second property value object is not an instance of ISgfcNumberPropertyValue");

            // If the game type is Go only square boards are allowed, i.e. the
            // SZ property should have a single value. Alas, SGFC has a bug and
            // does not fix the SGF content if it has a composed value. We treat
            // this as an interfacing error and do not attempt to fix the
            // problem ourselves.
            if (gameType == SgfcGameType::Go)
              throw std::domain_error("Node object contains an SZ property with a non-square board even though the game type is Go");

            std::shared_ptr<ISgfcBoardSizeProperty> property = propertyFactory->CreateBoardSizeProperty(
              composedValueSharedPtr);

            return property->GetBoardSize(gameType);
          }
          else
          {
            // This occurs if SgfcPropertyMetaInfo provides the wrong value type
            // descriptor
            const ISgfcNumberPropertyValue* numberValue = propertyValue->ToSingleValue()->ToNumberValue();
            if (numberValue == nullptr)
              throw std::logic_error("Property value object is not an instance of ISgfcNumberPropertyValue");

            std::shared_ptr<ISgfcNumberPropertyValue> numberValueSharedPtr =
              std::dynamic_pointer_cast<ISgfcNumberPropertyValue>(propertyValue);

            std::shared_ptr<ISgfcBoardSizeProperty> property = propertyFactory->CreateBoardSizeProperty(
              numberValueSharedPtr);

            return property->GetBoardSize(gameType);
          }
        }
        catch (std::invalid_argument&)
        {
          // The factory throws an invalid_argument in several cases when the
          // property value object is somehow malformed. The only way how this
          // is possible is if the property value object has been created from
          // a string that is not a Number string.
          //
          // SGFC has the following error correction behaviour that prevents
          // most (but not all) of these cases:
          // - Go games
          //   - If the value is a single value but is not a Number string,
          //     SGFC fixes the problem by setting the default value 19.
          //   - If the value is a composed value and either the first value,
          //     or the second value, or both are not Number strings, SGFC
          //     fixes the problem by setting the default value 19.
          // - Games that are not Go
          //   - If the value is a single value but is not a Number string,
          //     SGFC fixes the problem by removing the property.
          //   - If the value is a composed value and either the first value
          //     or both values are not Number strings, SGFC fixes the problem
          //     by removing the property.
          //   - If the value is a composed value and the first value is a
          //     Number string but the second value is not a Number string,
          //     SGFC does NOT fix the problem!
          //
          // So as the last case shows, this CAN occur. Instead of just checking
          // for exactly this loophole in the SGFC error correction behaviour
          // we let the factory do all the checks and handle the exception here.
          if (propertyValue->IsComposedValue())
            throw std::domain_error("Node object contains an SZ property with a composed value, of which one or both values are not Number values");
          else
            throw std::domain_error("Node object contains an SZ property with a single value that is not a Number value");
        }
      }
    }

    switch (gameType)
    {
      case SgfcGameType::Go:
        return SgfcConstants::BoardSizeDefaultGo;
      case SgfcGameType::Chess:
        return SgfcConstants::BoardSizeDefaultChess;
      default:
        return SgfcConstants::BoardSizeNone;
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
        if (sgfPropertyValue->value == nullptr)
        {
          std::stringstream message;
          message << "GetSgfcPropertyValueFromSgfPropertyValue: Expected a composed value, but SGFC gave us no values";
          throw std::domain_error(message.str());
        }

        if (sgfPropertyValue->value2 == nullptr)
        {
          // We expected a composed value (according to the SGF standard's
          // definition of the property), but SGFC gave us a single value. We
          // have no choice but to throw an exception. Alas, this forces someone
          // else to handle that exception, with the only possible handling
          // being to discard some or even all of the SGF content.

          std::stringstream message;
          message << "GetSgfcPropertyValueFromSgfPropertyValue: Expected a composed value, but SGFC gave us only a single value";
          throw std::domain_error(message.str());
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
        SgfcPropertyValueType basicValueType =
          valueTypeDescriptor->ToBasicValueTypeDescriptor()->GetValueType();

        if (sgfPropertyValue->value == nullptr)
        {
          std::stringstream message;
          message << "GetSgfcPropertyValueFromSgfPropertyValue: Expected a single value of value type " << static_cast<int>(basicValueType) << ", but SGFC gave us no value";
          throw std::domain_error(message.str());
        }

        if (sgfPropertyValue->value2 != nullptr)
        {
          std::stringstream message;
          message << "GetSgfcPropertyValueFromSgfPropertyValue: Expected a single value of value type " << static_cast<int>(basicValueType) << ", but SGFC gave us a composed value";
          throw std::domain_error(message.str());
        }

        if (basicValueType == SgfcPropertyValueType::None)
        {
          // The SGF standard defines value type None to be an empty string.
          // If the original SGF content contains a non-empty string we expect
          // SGFC to correct this. We don't check if sgfPropertyValue->value
          // actually contains an empty string, though, because if it doesn't
          // we can't really do anything about it. The only thing we could do
          // is throw an exception, but this would force someone else to handle
          // that exception, with the only possible handling being to discard
          // some or even all of the SGF content. It's better to just discard
          // the superfluous property value here.

          return nullptr;
        }

        // Here we expect a value type != SgfcPropertyValueType::None. Should
        // we do something special if the SGF content gives us an empty string
        // as the string value? It could be argued that we should return
        // nullptr, because the SGF standard defines an empty string to be the
        // equivalent of "no value". This would help clients to better deal
        // with bad SGF content. On the other hand, filtering out an empty
        // string value would mean tampering with the SGF data. Currently the
        // tampering argument seems to be the stronger argument, so we don't
        // do anything special with empty string values here. The result is that
        // for thhose value types for which an empty string cannot be converted
        // to a value of the required type (e.g. SgfcPropertyValueType::Number)
        // the resulting ISgfcPropertyValue object will have only a raw value
        // and HasTypedValue() will return false.
        // Note: If a change to this decision is ever considered, also think
        // about how to deal with composed value types for which one of the
        // two values is an empty string.

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
        propertyValue = GetSgfcSimpleTextPropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
        break;
      case SgfcPropertyValueType::Text:
        propertyValue = GetSgfcTextPropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
        break;
      case SgfcPropertyValueType::Point:
        propertyValue = GetSgfcPointPropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
        break;
      case SgfcPropertyValueType::Move:
        propertyValue = GetSgfcMovePropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
        break;
      case SgfcPropertyValueType::Stone:
        propertyValue = GetSgfcStonePropertyValueFromSgfPropertyValue(rawPropertyValueBuffer);
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

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcSimpleTextPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    // We have to remove line breaks ourselves because of a bug in SGFC.
    // If the SimpleText value is the second value of a composed value then
    // SGFC does not detect and remove hard and soft line breaks in all
    // cases. If it's the first value of a composed value, then SGFC seems
    // to be able to handle line breaks correctly. Examples:
    // - Property "AP": SGFC detects neither hard nor soft line breaks in the
    //   second value of the composed value.
    // - Property "LB": SGFC detects soft line breaks, but not hard line
    //   breaks, in the second value of the composed value.
    //
    // Although the described bug only affects SimpleText values that are the
    // second value of a composed value, we still remove line breaks for all
    // SimpleText values, because SGFC only recognizes and handles one kind of
    // platform-specific line break (e.g. LF, CRLF, ...).
    std::string rawValueWithoutLineBreaks =
      RemoveSimpleTextLineBreaks(rawPropertyValueBuffer);

    std::string rawValueWithoutEscapeCharacters =
      RemoveSimpleTextAndTextEscapeCharacters(rawValueWithoutLineBreaks);

    return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcSimpleTextPropertyValue(
      rawPropertyValueBuffer,
      rawValueWithoutEscapeCharacters));
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcTextPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    // In theory no line break removal is necessary for Text values because
    // SGFC has no known bug in handling them. In practice we still have to
    // perform the line break removal, because SGFC only recognizes and handles
    // one kind of platform-specific line break (e.g. LF, CRLF, ...).
    std::string rawValueWithoutLineBreaks =
      RemoveTextLineBreaks(rawPropertyValueBuffer);

    std::string rawValueWithoutEscapeCharacters =
      RemoveSimpleTextAndTextEscapeCharacters(rawValueWithoutLineBreaks);

    return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcTextPropertyValue(
      rawPropertyValueBuffer,
      rawValueWithoutEscapeCharacters));
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcPointPropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    SgfcGameType gameType = this->propertyMetaInfo->GetGameType();

    if (gameType == SgfcGameType::Go)
    {
      try
      {
        return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoPointPropertyValue(
         rawPropertyValueBuffer,
         this->boardSize));
      }
      catch (std::invalid_argument&)
      {
        // Interpretation of the property value failed. We expect SGFC to
        // validate point values for us in relation to the board size, but we
        // don't rely on it.
        return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoPointPropertyValue(
         rawPropertyValueBuffer));
      }
    }
    else
    {
      std::string rawValueWithoutEscapeCharacters = RemoveMandatoryEscapeCharacters(rawPropertyValueBuffer);
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcPointPropertyValue(
       rawValueWithoutEscapeCharacters));
    }
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcMovePropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    SgfcGameType gameType = this->propertyMetaInfo->GetGameType();

    if (gameType == SgfcGameType::Go)
    {
      SgfcColor color = GetColorForPropertyType();
      if (rawPropertyValueBuffer == SgfcConstants::GoMovePassString)
      {
        // For Go the SGF standard defines that black or white pass moves can
        // have either value "" (an empty string) or "tt". The latter counts as
        // pass move only for board sizes <= 19, for larger boards "tt" is a
        // normal move. The SGF standard also mentions that "tt" is kept only
        // for compatibility with FF3.
        // Here we rely on SGFC doing the interpretation for us, and for passing
        // an empty string value to us if it encountered "tt".
        return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoMovePropertyValue(
         color));
      }
      else
      {
        try
        {
          return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoMovePropertyValue(
           rawPropertyValueBuffer, this->boardSize, color));
        }
        catch (std::invalid_argument&)
        {
          // Interpretation of the property value failed. We expect SGFC to
          // validate move values for us in relation to the board size, but we
          // don't rely on it.
          return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoMovePropertyValue(
           rawPropertyValueBuffer, color));
        }
      }
    }
    else
    {
      std::string rawValueWithoutEscapeCharacters = RemoveMandatoryEscapeCharacters(rawPropertyValueBuffer);
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcMovePropertyValue(
       rawValueWithoutEscapeCharacters));
    }
  }

  std::shared_ptr<ISgfcSinglePropertyValue> SgfcPropertyDecoder::GetSgfcStonePropertyValueFromSgfPropertyValue(
    const char* rawPropertyValueBuffer) const
  {
    SgfcGameType gameType = this->propertyMetaInfo->GetGameType();

    if (gameType == SgfcGameType::Go)
    {
      SgfcColor color = GetColorForPropertyType();
      try
      {
        return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoStonePropertyValue(
         rawPropertyValueBuffer, this->boardSize, color));
      }
      catch (std::invalid_argument&)
      {
        // Interpretation of the property value failed. We expect SGFC to
        // validate stone values for us in relation to the board size, but w
        // don't rely on it.
        return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcGoStonePropertyValue(
         rawPropertyValueBuffer, color));
      }
    }
    else
    {
      std::string rawValueWithoutEscapeCharacters = RemoveMandatoryEscapeCharacters(rawPropertyValueBuffer);
      return std::shared_ptr<ISgfcSinglePropertyValue>(new SgfcStonePropertyValue(
       rawValueWithoutEscapeCharacters));
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
        // Notably, for SgfcGameType::Go all properties that have the value
        // types Stone and Move are allowed because for those properties the
        // property type specifies which color the placed stone has or which
        // player made the move.
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
    // SGFC removes all unnecessary escape characters from SimpleText and Text
    // values, so we don't have to deal with them. E.g. escaping the "a"
    // character is not necessary, so when SGFC sees "\a" it removes the
    // unnecessary escape character and this method gets to process only "a".
    //
    // The characters that need escaping are:
    // - The property value closing character "]": This needs to be always
    //   escaped.
    // - The escape character "\": This needs to be always escaped.
    // - The composed property value separator character ":": This needs to be
    //   escaped only in composed property values, and then only if it appears
    //   in the first value. Consequently, SGFC removes the escape character
    //   from "\:" if it appears in single property values, and keeps it if it
    //   appears in a composed property value. SGFC keeps the escape character
    //   even if it appears in the second value. E.g. if the LB property
    //   property value looks like this "aa:foo\:bar", then SGFC retains that
    //   value exactly as-is, although strictly speaking it could simplify
    //   the value to "aa:foo:bar".

    std::string result = RemoveMandatoryEscapeCharacters(rawPropertyValue);

    result = std::regex_replace(
      result,
      SgfcPrivateConstants::EscapedComposedValueSeparatorTokenRegex,
      SgfcPrivateConstants::ComposedValueSeparatorToken);

    // Escape characters must be removed last so that we don't remove the escape
    // characters from other escape sequences. E.g. "\\:" must result in "\:".
    // Note: There is no order of precedence, an escape character simply always
    // must act upon the character that follows it. Although the way this
    // method is implemented does not follow this rule (we first escape the
    // "]" and ":" characters, then the "\" characters), the outcome is
    // equivalent.
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
