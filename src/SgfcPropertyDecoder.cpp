// Project includes
#include "SgfcPropertyDecoder.h"
#include "SgfcPropertyBasicValueTypeDescriptor.h"
#include "SgfcPropertyComposedValueTypeDescriptor.h"
#include "SgfcPropertyDualValueTypeDescriptor.h"
#include "SgfcPropertyElistValueTypeDescriptor.h"
#include "SgfcPropertyListValueTypeDescriptor.h"

// SGFC includes
extern "C"
{
  #include <stdio.h>  // required to define size_t and FILE which are used in all.h
  #include "../sgfc/all.h"
}

// C++ Standard Library includes
#include <sstream>
#include <stdexcept>

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

  SgfcPropertyDecoder::SgfcPropertyDecoder()
  {
  }

  SgfcPropertyDecoder::~SgfcPropertyDecoder()
  {
  }

  SgfcPropertyType SgfcPropertyDecoder::GetSgfcPropertyTypeFromSgfProperty(Property* sgfProperty)
  {
    switch (sgfProperty->id)
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

  std::shared_ptr<ISgfcPropertyValueTypeDescriptor> SgfcPropertyDecoder::GetValueTypeDescriptorForPropertyType(
    SgfcPropertyType propertyType)
  {
    switch (propertyType)
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
        return DescriptorNumber;
      case SgfcPropertyType::KM:
        return DescriptorReal;
      case SgfcPropertyType::TB:
        return DescriptorElistOfPoint;
      case SgfcPropertyType::TW:
        return DescriptorElistOfPoint;

      // ----------------------------------------------------------------------
      // Game of Backgammon properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::CO:
        return DescriptorSimpleText;
      case SgfcPropertyType::CV:
        return DescriptorNumber;
      case SgfcPropertyType::DI:
        return DescriptorNumber;
      case SgfcPropertyType::MI:
        return DescriptorListOfComposedSimpleTextAndSimpleText;

      // ----------------------------------------------------------------------
      // Game of Lines of Action properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::IY:
        return DescriptorSimpleText;
      case SgfcPropertyType::SU:
        return DescriptorSimpleText;

      // ----------------------------------------------------------------------
      // Game of Hex properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::IS:
        return DescriptorListOfComposedSimpleTextAndSimpleText;

      // ----------------------------------------------------------------------
      // Game of Amazons properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::AA:
        return DescriptorListOfMove;

      // ----------------------------------------------------------------------
      // Game of Octi properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::BO:
        return DescriptorListOfMove;
      case SgfcPropertyType::WO:
        return DescriptorListOfMove;
      case SgfcPropertyType::NP:
        return DescriptorNumber;
      case SgfcPropertyType::NR:
        return DescriptorNumber;
      case SgfcPropertyType::NS:
        return DescriptorNumber;
      case SgfcPropertyType::CS:
        return DescriptorListOfStone;
      case SgfcPropertyType::MS:
        return DescriptorListOfStone;
      case SgfcPropertyType::SS:
        return DescriptorListOfStone;
      case SgfcPropertyType::TS:
        return DescriptorListOfStone;
      case SgfcPropertyType::RP:
        return DescriptorListOfStone;

      // ----------------------------------------------------------------------
      // Properties for more than one game
      // ----------------------------------------------------------------------
      // Lines of Action (GM[9]) and Octi (GM[19])
      case SgfcPropertyType::AS:
        /// @todo For the game of Octi in FF4 this is defined as
        /// DescriptorListOfComposedStoneAndPoint.
        return DescriptorSimpleText;
      // Lines of Action (GM[9]) and Hex (GM[11])
      case SgfcPropertyType::IP:
        return DescriptorSimpleText;

      // ----------------------------------------------------------------------
      // Non-standard properties
      // ----------------------------------------------------------------------
      case SgfcPropertyType::KI:
        // The type comes from the SGFC README.
        return DescriptorNumber;
      case SgfcPropertyType::Unknown:
        return DescriptorUnknown;

      // ----------------------------------------------------------------------
      // If we get here a "case" statement is missing
      // ----------------------------------------------------------------------
      default:
        std::stringstream message;
        message << "Unexpected property type value: " << static_cast<int>(propertyType);
        throw std::logic_error(message.str());
    }
  }
}
