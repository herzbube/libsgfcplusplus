#pragma once

// Project includes
#include "../../include/ISgfcPropertyValue.h"
#include "../../include/SgfcBoardSize.h"
#include "../../include/SgfcColor.h"
#include "../../include/SgfcGameType.h"
#include "../../include/SgfcPropertyType.h"
#include "../../include/SgfcPropertyValueType.h"
#include "../../include/SgfcTypedefs.h"
#include "../interface/internal/ISgfcPropertyValueTypeDescriptor.h"

// C++ Standard Library includes
#include <memory>
#include <vector>

// Forward declarations
struct Node;
struct Property;
struct PropValue;

namespace LibSgfcPlusPlus
{
  // Forward declarations
  class SgfcPropertyMetaInfo;

  /// @brief The SgfcPropertyDecoder class parses the raw strings that SGFC
  /// provides for SGF properties and their values, and generates proper
  /// objects from those parsing activities.
  class SgfcPropertyDecoder
  {
  public:
    /// @brief Initializes a newly constructed SgfcPropertyDecoder object. The
    /// object parses the specified SGF property @a sgfProperty and its values.
    /// The specified @a gameType and @a boardSize are important for
    /// interpreting certain game-specific properties and their values, but
    /// are ignored for all other properties and their values.
    ///
    /// @exception std::invalid_argument Is thrown if @a sgfProperty is
    /// nullptr, or if @a sgfProperty->idstr is nullptr, or if
    /// @a sgfProperty->value is nullptr, or if @a sgfProperty->id holds an
    /// unexpected enumeration value.
    SgfcPropertyDecoder(const Property* sgfProperty, SgfcGameType gameType, SgfcBoardSize boardSize);

    /// @brief Destroys and cleans up the SgfcPropertyDecoder object.
    virtual ~SgfcPropertyDecoder();

    /// @brief Returns the SgfcPropertyType value that corresponds to the
    /// SGF property with which SgfcPropertyDecoder was constructed. Returns
    /// SgfcPropertyType::Unknown for properties that are not defined in the
    /// SGF standard.
    SgfcPropertyType GetPropertyType() const;

    /// @brief Returns the raw string name of the SGF property with which
    /// SgfcPropertyDecoder was constructed.
    std::string GetPropertyName() const;

    /// @brief Returns a list with the values of the SGF property with which
    /// SgfcPropertyDecoder was constructed.
    ///
    /// If GetPropertyType() returns SgfcPropertyType::Unknown all
    /// ISgfcSinglePropertyValue objects contain uninterpreted raw values only
    /// and their GetValueType() method returns SgfcPropertyValueType::Unknown.
    /// This is because the property is not defined in the SGF standard, so
    /// SgfcPropertyDecoder does not know the type the raw values should have.
    ///
    /// If GetPropertyType() returns something other than
    /// SgfcPropertyType::Unknown, the property is defined in the SGF standard
    /// and SgfcPropertyDecoder attempts to convert the raw string values into
    /// values of the types required by the property according to the SGF
    /// standard. In all cases the GetValueType() method of
    /// ISgfcSinglePropertyValue objects returns the value type as defined by
    /// the SGF standard. The outcome of the conversion attempt determines the
    /// other properties of ISgfcSinglePropertyValue objects:
    /// - If SgfcPropertyDecoder fails to convert the raw string value, the
    ///   ISgfcSinglePropertyValue objects' HasTypedValue() method returns false
    ///   and the GetTypeConversionErrorMessage() method returns a message that
    ///   describes the reason for the conversion failure.
    /// - If SgfcPropertyDecoder succeeds to convert the raw string value, the
    ///   ISgfcSinglePropertyValue objects' HasTypedValue() method returns true
    ///   and one of the numerous To...() methods can be used to cast the
    ///   object to a concrete type.
    ///
    /// @note This method relies on certain pre-processing performed by SGFC.
    /// Notably:
    /// - SGFC is expected to trim leading and trailing whitespace from values
    ///   that are not SimpleText or Text. Without trimming this method would
    ///   be unable to recognize Double and Color values.
    /// - In SimpleText values, SGFC is expected to convert whitespace
    ///   characters other than space to space (i.e. line breaks are not
    ///   preserved). Due to shortcomings in SGFC's handling of line breaks
    ///   this method adds its own line break handling, so currently SGFC's
    ///   line break handling is irrelevant to the implementation of this
    ///   method. See the next note for details.
    /// - In Text values, SGFC is expected to convert whitespace characters
    ///   other than line breaks are converted to space (i.e. line breaks are
    ///   preserved). SGFC is also expected to remove escaped line breaks.
    ///   Due to shortcomings in SGFC's handling of line breaks this method
    ///   adds its own line break handling, so currently SGFC's line break
    ///   handling is irrelevant to the implementation of this method.
    ///   See the next note for details.
    /// - In SimpleText and Text values, all unnecessary escape characters
    ///   are removed. E.g. escaping the "a" character is not necessary, so
    ///   when SGFC sees "\a" it removes the unnecessary escape character and
    ///   this method gets to process only "a". In short, this method does not
    ///   perform any escape character handling.
    ///
    /// @note This method has its own line break handling for SimpleText and
    /// Text values, due to two shortcomings in SGFC: 1) A bug in SGFC: If a
    /// SimpleText value is the second value of a composed value then SGFC does
    /// not detect and remove hard and soft line breaks in all cases. This
    /// method is capable of detecting these cases. 2) SGFC only handles one
    /// kind of line break (e.g. LF, CRLF, ...) in SimpleText and Text values:
    /// The one that was predetermined at compile time. This method is capable
    /// of recognizing and handling all kinds of platform-specific line breaks.
    ///
    /// @note If SgfcPropertyDecoder was constructed with SgfcGameType::Go
    /// the decoding process performs the following game logic validation:
    /// - If SgfcPropertyDecoder was constructed with
    ///   SgfcConstants::BoardSizeNone or SgfcConstants::BoardSizeInvalid, any
    ///   game-specific property value objects (e.g. ISgfcGoPointPropertyValue)
    ///   that would normally contain an ISgfcGoPoint do not contain such an
    ///   object. Instead they contain the raw property value only.
    /// - If SgfcPropertyDecoder was constructed with a valid board size but
    ///   the property value contains a location that is outside the boundaries
    ///   of the specified board size, any game-specific property value objects
    ///   (e.g. ISgfcGoPointPropertyValue) that would normally contain an
    ///   ISgfcGoPoint do not contain such an object. Instead they contain the
    ///   raw property value only.
    ///
    /// @note This documentation has to be replicated on the public interface.
    /// specifically, the notes regarding the expected pre-processing performed
    /// by SGFC must be available as well in the documentation of
    /// ISgfcSinglePropertyValue::GetRawValue().
    std::vector<std::shared_ptr<ISgfcPropertyValue>> GetPropertyValues() const;

    /// @brief Probes the SGF node @a sgfNode for a property of type
    /// SgfcPropertyType::GM and returns an SgfcGameType value that corresponds
    /// to the result of the probing.
    ///
    /// @param sgfNode The SGF node to be probed. The node should be the root
    /// node of a game because SgfcPropertyType::GM can be expected to be
    /// present in that node.
    ///
    /// @retval SgfcGameType If the property is present and has a value defined
    ///         in the SGF standard, returns the SgfcGameType value that
    ///         corresponds to the property value. The value is guaranteed not
    ///         to be SgfcGameType::Unknown.
    /// @retval SgfcConstants::DefaultGameType If the property is present and
    ///         has no value. The value is guaranteed not to be
    ///         SgfcGameType::Unknown.
    /// @retval SgfcGameType::Unknown If the property is present and has a value
    ///         that is not defined in the SGF standard, or if the property is
    ///         not present.
    static SgfcGameType GetGameTypeFromNode(const Node* sgfNode);

    /// @brief Probes the SGF node @a sgfNode for a property of type
    /// SgfcPropertyType::SZ and returns an SgfcBoardSize value that corresponds
    /// to the result of the probing. Returns a game-specific default board size
    /// for a few game types mentioned in the SGF standard if the property is
    /// present but has no value.
    ///
    /// @param sgfNode The SGF node to be probed. The node should be the root
    /// node of a game because SgfcPropertyType::SZ can be expected to be
    /// present in that node.
    ///
    /// @retval SgfcBoardSize If the property is present and has a valid value.
    ///         The value is guaranteed not to be SgfcConstants::BoardSizeNone
    ///         nor SgfcConstants::BoardSizeInvalid.
    /// @retval SgfcConstants::DefaultBoardSizeGo If the property is present
    ///         and has no value, and @a gameType is SgfcGameType::Go.
    /// @retval SgfcConstants::DefaultBoardSizeChess If the property is present
    ///         and has no value, and @a gameType is SgfcGameType::Chess.
    /// @retval SgfcConstants::BoardSizeNone If the property is not present, or
    ///         if the property is present and has no value, but @a gameType is
    ///         neither SgfcGameType::Go nor SgfcGameType::Chess.
    /// @retval SgfcConstants::BoardSizeInvalid If the property is present but
    ///         has an invalid value. A board size is invalid if it violates
    ///         the constraints defined by the SGF standard. See the
    ///         documentation of SgfcConstants::BoardSizeInvalid for details.
    static SgfcBoardSize GetBoardSizeFromNode(const Node* sgfNode, SgfcGameType gameType);

  private:
    const Property* sgfProperty;
    std::shared_ptr<SgfcPropertyMetaInfo> propertyMetaInfo;
    SgfcBoardSize boardSize;

    SgfcPropertyType GetPropertyTypeInternal() const;

    std::vector<std::shared_ptr<ISgfcPropertyValue>> GetSgfcPropertyValuesFromSgfPropertyValue(
      PropValue* sgfPropertyValue,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> elementValueTypeDescriptor) const;

    std::shared_ptr<ISgfcPropertyValue> GetSgfcPropertyValueFromSgfPropertyValue(
      PropValue* sgfPropertyValue,
      std::shared_ptr<ISgfcPropertyValueTypeDescriptor> valueTypeDescriptor) const;

    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer,
      SgfcPropertyValueType propertyValueType) const;

    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcNumberPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcRealPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcDoublePropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcColorPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcSimpleTextPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcTextPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcPointPropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcMovePropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;
    std::shared_ptr<ISgfcSinglePropertyValue> GetSgfcStonePropertyValueFromSgfPropertyValue(
      const char* rawPropertyValueBuffer) const;

    bool DoesSgfcPropertyHaveTypedValues(const std::shared_ptr<ISgfcPropertyValue>& propertyValue) const;

    SgfcColor GetColorForPropertyType() const;

    std::string RemoveSimpleTextLineBreaks(const std::string& rawPropertyValue) const;
    std::string RemoveTextLineBreaks(const std::string& rawPropertyValue) const;
    std::string RemoveSimpleTextAndTextEscapeCharacters(const std::string& rawPropertyValue) const;
    std::string RemoveMandatoryEscapeCharacters(const std::string& rawPropertyValue) const;
  };
}
