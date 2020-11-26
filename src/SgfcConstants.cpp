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
#include "../include/SgfcConstants.h"
#include "SgfcPrivateConstants.h"

// C++ Standard Library includes
#include <limits>

namespace LibSgfcPlusPlus
{
  const std::string SgfcConstants::LibraryName = "libsgfc++";
  const std::string SgfcConstants::LibraryVersion = "0.1 (alpha)";
  const std::string SgfcConstants::SgfcVersion = "1.18";

  const int SgfcConstants::InvalidLineNumber = -1;
  const int SgfcConstants::InvalidColumnNumber = -1;

  const int SgfcConstants::LibraryErrorNumberNoError = 0;

  const std::string SgfcConstants::NoneValueString = SgfcPrivateConstants::EmptyString;
  const std::string SgfcConstants::DoubleNormalString = "1";
  const std::string SgfcConstants::DoubleEmphasizedString = "2";
  const std::string SgfcConstants::ColorBlackString = "B";
  const std::string SgfcConstants::ColorWhiteString = "W";
  const std::string SgfcConstants::GoMovePassString = SgfcPrivateConstants::EmptyString;

  const std::map<std::string, SgfcPropertyType> SgfcConstants::PropertyNameToPropertyTypeMap =
  {
    // Standard properties from FF4
    { "B", SgfcPropertyType::B },
    { "KO", SgfcPropertyType::KO },
    { "MN", SgfcPropertyType::MN },
    { "W", SgfcPropertyType::W },
    { "AB", SgfcPropertyType::AB },
    { "AE", SgfcPropertyType::AE },
    { "AW", SgfcPropertyType::AW },
    { "PL", SgfcPropertyType::PL },
    { "C", SgfcPropertyType::C },
    { "DM", SgfcPropertyType::DM },
    { "GB", SgfcPropertyType::GB },
    { "GW", SgfcPropertyType::GW },
    { "HO", SgfcPropertyType::HO },
    { "N", SgfcPropertyType::N },
    { "UC", SgfcPropertyType::UC },
    { "V", SgfcPropertyType::V },
    { "BM", SgfcPropertyType::BM },
    { "DO", SgfcPropertyType::DO },
    { "IT", SgfcPropertyType::IT },
    { "TE", SgfcPropertyType::TE },
    { "AR", SgfcPropertyType::AR },
    { "CR", SgfcPropertyType::CR },
    { "DD", SgfcPropertyType::DD },
    { "LB", SgfcPropertyType::LB },
    { "LN", SgfcPropertyType::LN },
    { "MA", SgfcPropertyType::MA },
    { "SL", SgfcPropertyType::SL },
    { "SQ", SgfcPropertyType::SQ },
    { "TR", SgfcPropertyType::TR },
    { "AP", SgfcPropertyType::AP },
    { "CA", SgfcPropertyType::CA },
    { "FF", SgfcPropertyType::FF },
    { "GM", SgfcPropertyType::GM },
    { "ST", SgfcPropertyType::ST },
    { "SZ", SgfcPropertyType::SZ },
    { "AN", SgfcPropertyType::AN },
    { "BR", SgfcPropertyType::BR },
    { "BT", SgfcPropertyType::BT },
    { "CP", SgfcPropertyType::CP },
    { "DT", SgfcPropertyType::DT },
    { "EV", SgfcPropertyType::EV },
    { "GN", SgfcPropertyType::GN },
    { "GC", SgfcPropertyType::GC },
    { "ON", SgfcPropertyType::ON },
    { "OT", SgfcPropertyType::OT },
    { "PB", SgfcPropertyType::PB },
    { "PC", SgfcPropertyType::PC },
    { "PW", SgfcPropertyType::PW },
    { "RE", SgfcPropertyType::RE },
    { "RO", SgfcPropertyType::RO },
    { "RU", SgfcPropertyType::RU },
    { "SO", SgfcPropertyType::SO },
    { "TM", SgfcPropertyType::TM },
    { "US", SgfcPropertyType::US },
    { "WR", SgfcPropertyType::WR },
    { "WT", SgfcPropertyType::WT },
    { "BL", SgfcPropertyType::BL },
    { "OB", SgfcPropertyType::OB },
    { "OW", SgfcPropertyType::OW },
    { "WL", SgfcPropertyType::WL },
    { "FG", SgfcPropertyType::FG },
    { "PM", SgfcPropertyType::PM },
    { "VW", SgfcPropertyType::VW },

    // Standard properties from FF1-3
    { "BS", SgfcPropertyType::BS },
    { "CH", SgfcPropertyType::CH },
    { "EL", SgfcPropertyType::EL },
    { "EX", SgfcPropertyType::EX },
    { "ID", SgfcPropertyType::ID },
    { "L", SgfcPropertyType::L },
    { "LT", SgfcPropertyType::LT },
    { "M", SgfcPropertyType::M },
    { "OM", SgfcPropertyType::OM },
    { "OP", SgfcPropertyType::OP },
    { "OV", SgfcPropertyType::OV },
    { "RG", SgfcPropertyType::RG },
    { "SC", SgfcPropertyType::SC },
    { "SE", SgfcPropertyType::SE },
    { "SI", SgfcPropertyType::SI },
    { "TC", SgfcPropertyType::TC },
    { "WS", SgfcPropertyType::WS },

    // Game of Go properties
    { "HA", SgfcPropertyType::HA },
    { "KM", SgfcPropertyType::KM },
    { "TB", SgfcPropertyType::TB },
    { "TW", SgfcPropertyType::TW },

    // Game of Backgammon properties
    { "CO", SgfcPropertyType::CO },
    { "CV", SgfcPropertyType::CV },
    { "DI", SgfcPropertyType::DI },
    { "MI", SgfcPropertyType::MI },

    // Game of Lines of Action properties
    { "IY", SgfcPropertyType::IY },
    { "SU", SgfcPropertyType::SU },

    // Game of Hex properties
    { "IS", SgfcPropertyType::IS },

    // Game of Amazons properties
    { "AA", SgfcPropertyType::AA },

    // Game of Octi properties
    { "BO", SgfcPropertyType::BO },
    { "WO", SgfcPropertyType::WO },
    { "NP", SgfcPropertyType::NP },
    { "NR", SgfcPropertyType::NR },
    { "NS", SgfcPropertyType::NS },
    { "CS", SgfcPropertyType::CS },
    { "MS", SgfcPropertyType::MS },
    { "SS", SgfcPropertyType::SS },
    { "TS", SgfcPropertyType::TS },
    { "RP", SgfcPropertyType::RP },

    // Properties for more than one game
    { "AS", SgfcPropertyType::AS },
    { "IP", SgfcPropertyType::IP },
  };

  const std::map<SgfcPropertyType, std::string> SgfcConstants::PropertyTypeToPropertyNameMap =
  {
    // Standard properties from FF4
    { SgfcPropertyType::B, "B" },
    { SgfcPropertyType::KO, "KO" },
    { SgfcPropertyType::MN, "MN" },
    { SgfcPropertyType::W, "W" },
    { SgfcPropertyType::AB, "AB" },
    { SgfcPropertyType::AE, "AE" },
    { SgfcPropertyType::AW, "AW" },
    { SgfcPropertyType::PL, "PL" },
    { SgfcPropertyType::C, "C" },
    { SgfcPropertyType::DM, "DM" },
    { SgfcPropertyType::GB, "GB" },
    { SgfcPropertyType::GW, "GW" },
    { SgfcPropertyType::HO, "HO" },
    { SgfcPropertyType::N, "N" },
    { SgfcPropertyType::UC, "UC" },
    { SgfcPropertyType::V, "V" },
    { SgfcPropertyType::BM, "BM" },
    { SgfcPropertyType::DO, "DO" },
    { SgfcPropertyType::IT, "IT" },
    { SgfcPropertyType::TE, "TE" },
    { SgfcPropertyType::AR, "AR" },
    { SgfcPropertyType::CR, "CR" },
    { SgfcPropertyType::DD, "DD" },
    { SgfcPropertyType::LB, "LB" },
    { SgfcPropertyType::LN, "LN" },
    { SgfcPropertyType::MA, "MA" },
    { SgfcPropertyType::SL, "SL" },
    { SgfcPropertyType::SQ, "SQ" },
    { SgfcPropertyType::TR, "TR" },
    { SgfcPropertyType::AP, "AP" },
    { SgfcPropertyType::CA, "CA" },
    { SgfcPropertyType::FF, "FF" },
    { SgfcPropertyType::GM, "GM" },
    { SgfcPropertyType::ST, "ST" },
    { SgfcPropertyType::SZ, "SZ" },
    { SgfcPropertyType::AN, "AN" },
    { SgfcPropertyType::BR, "BR" },
    { SgfcPropertyType::BT, "BT" },
    { SgfcPropertyType::CP, "CP" },
    { SgfcPropertyType::DT, "DT" },
    { SgfcPropertyType::EV, "EV" },
    { SgfcPropertyType::GN, "GN" },
    { SgfcPropertyType::GC, "GC" },
    { SgfcPropertyType::ON, "ON" },
    { SgfcPropertyType::OT, "OT" },
    { SgfcPropertyType::PB, "PB" },
    { SgfcPropertyType::PC, "PC" },
    { SgfcPropertyType::PW, "PW" },
    { SgfcPropertyType::RE, "RE" },
    { SgfcPropertyType::RO, "RO" },
    { SgfcPropertyType::RU, "RU" },
    { SgfcPropertyType::SO, "SO" },
    { SgfcPropertyType::TM, "TM" },
    { SgfcPropertyType::US, "US" },
    { SgfcPropertyType::WR, "WR" },
    { SgfcPropertyType::WT, "WT" },
    { SgfcPropertyType::BL, "BL" },
    { SgfcPropertyType::OB, "OB" },
    { SgfcPropertyType::OW, "OW" },
    { SgfcPropertyType::WL, "WL" },
    { SgfcPropertyType::FG, "FG" },
    { SgfcPropertyType::PM, "PM" },
    { SgfcPropertyType::VW, "VW" },

    // Standard properties from FF1-3
    { SgfcPropertyType::BS, "BS" },
    { SgfcPropertyType::CH, "CH" },
    { SgfcPropertyType::EL, "EL" },
    { SgfcPropertyType::EX, "EX" },
    { SgfcPropertyType::ID, "ID" },
    { SgfcPropertyType::L, "L" },
    { SgfcPropertyType::LT, "LT" },
    { SgfcPropertyType::M, "M" },
    { SgfcPropertyType::OM, "OM" },
    { SgfcPropertyType::OP, "OP" },
    { SgfcPropertyType::OV, "OV" },
    { SgfcPropertyType::RG, "RG" },
    { SgfcPropertyType::SC, "SC" },
    { SgfcPropertyType::SE, "SE" },
    { SgfcPropertyType::SI, "SI" },
    { SgfcPropertyType::TC, "TC" },
    { SgfcPropertyType::WS, "WS" },

    // Game of Go properties
    { SgfcPropertyType::HA, "HA" },
    { SgfcPropertyType::KM, "KM" },
    { SgfcPropertyType::TB, "TB" },
    { SgfcPropertyType::TW, "TW" },

    // Game of Backgammon properties
    { SgfcPropertyType::CO, "CO" },
    { SgfcPropertyType::CV, "CV" },
    { SgfcPropertyType::DI, "DI" },
    { SgfcPropertyType::MI, "MI" },

    // Game of Lines of Action properties
    { SgfcPropertyType::IY, "IY" },
    { SgfcPropertyType::SU, "SU" },

    // Game of Hex properties
    { SgfcPropertyType::IS, "IS" },

    // Game of Amazons properties
    { SgfcPropertyType::AA, "AA" },

    // Game of Octi properties
    { SgfcPropertyType::BO, "BO" },
    { SgfcPropertyType::WO, "WO" },
    { SgfcPropertyType::NP, "NP" },
    { SgfcPropertyType::NR, "NR" },
    { SgfcPropertyType::NS, "NS" },
    { SgfcPropertyType::CS, "CS" },
    { SgfcPropertyType::MS, "MS" },
    { SgfcPropertyType::SS, "SS" },
    { SgfcPropertyType::TS, "TS" },
    { SgfcPropertyType::RP, "RP" },

    // Properties for more than one game
    { SgfcPropertyType::AS, "AS" },
    { SgfcPropertyType::IP, "IP" },
  };

  const std::map<SgfcPropertyType, SgfcPropertyCategory> SgfcConstants::PropertyTypeToPropertyCategoryMap =
  {
    // Standard properties from FF4
    { SgfcPropertyType::B, SgfcPropertyCategory::Move },
    { SgfcPropertyType::KO, SgfcPropertyCategory::Move },
    { SgfcPropertyType::MN, SgfcPropertyCategory::Move },
    { SgfcPropertyType::W, SgfcPropertyCategory::Move },
    { SgfcPropertyType::AB, SgfcPropertyCategory::Setup },
    { SgfcPropertyType::AE, SgfcPropertyCategory::Setup },
    { SgfcPropertyType::AW, SgfcPropertyCategory::Setup },
    { SgfcPropertyType::PL, SgfcPropertyCategory::Setup },
    { SgfcPropertyType::C, SgfcPropertyCategory::NodeAnnotation },
    { SgfcPropertyType::DM, SgfcPropertyCategory::NodeAnnotation },
    { SgfcPropertyType::GB, SgfcPropertyCategory::NodeAnnotation },
    { SgfcPropertyType::GW, SgfcPropertyCategory::NodeAnnotation },
    { SgfcPropertyType::HO, SgfcPropertyCategory::NodeAnnotation },
    { SgfcPropertyType::N, SgfcPropertyCategory::NodeAnnotation },
    { SgfcPropertyType::UC, SgfcPropertyCategory::NodeAnnotation },
    { SgfcPropertyType::V, SgfcPropertyCategory::NodeAnnotation },
    { SgfcPropertyType::BM, SgfcPropertyCategory::MoveAnnotation },
    { SgfcPropertyType::DO, SgfcPropertyCategory::MoveAnnotation },
    { SgfcPropertyType::IT, SgfcPropertyCategory::MoveAnnotation },
    { SgfcPropertyType::TE, SgfcPropertyCategory::MoveAnnotation },
    { SgfcPropertyType::AR, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::CR, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::DD, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::LB, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::LN, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::MA, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::SL, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::SQ, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::TR, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::AP, SgfcPropertyCategory::Root },
    { SgfcPropertyType::CA, SgfcPropertyCategory::Root },
    { SgfcPropertyType::FF, SgfcPropertyCategory::Root },
    { SgfcPropertyType::GM, SgfcPropertyCategory::Root },
    { SgfcPropertyType::ST, SgfcPropertyCategory::Root },
    { SgfcPropertyType::SZ, SgfcPropertyCategory::Root },
    { SgfcPropertyType::AN, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::BR, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::BT, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::CP, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::DT, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::EV, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::GN, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::GC, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::ON, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::OT, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::PB, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::PC, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::PW, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::RE, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::RO, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::RU, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::SO, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::TM, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::US, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::WR, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::WT, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::BL, SgfcPropertyCategory::Timing },
    { SgfcPropertyType::OB, SgfcPropertyCategory::Timing },
    { SgfcPropertyType::OW, SgfcPropertyCategory::Timing },
    { SgfcPropertyType::WL, SgfcPropertyCategory::Timing },
    { SgfcPropertyType::FG, SgfcPropertyCategory::Miscellaneous },
    { SgfcPropertyType::PM, SgfcPropertyCategory::Miscellaneous },
    { SgfcPropertyType::VW, SgfcPropertyCategory::Miscellaneous },

    // Standard properties from FF1-3                               // Index page       FF3 specs page    FF1 specs page
    { SgfcPropertyType::BS, SgfcPropertyCategory::GameInfo },       // GameInfo         Root              Root
    { SgfcPropertyType::CH, SgfcPropertyCategory::MoveAnnotation }, // -                MoveAnnotation    -
    { SgfcPropertyType::EL, SgfcPropertyCategory::Miscellaneous },  // -                n/a               -
    { SgfcPropertyType::EX, SgfcPropertyCategory::Miscellaneous },  // -                n/a               -
    { SgfcPropertyType::ID, SgfcPropertyCategory::GameInfo },       // GameInfo         GameInfo          n/a
    { SgfcPropertyType::L, SgfcPropertyCategory::Markup },          // -                n/a               Superseded by LB
    { SgfcPropertyType::LT, SgfcPropertyCategory::Root },           // -                Root              n/a
    { SgfcPropertyType::M, SgfcPropertyCategory::Markup },          // -                n/a               "Marked points"
    { SgfcPropertyType::OM, SgfcPropertyCategory::Timing },         // -                Timing            n/a
    { SgfcPropertyType::OP, SgfcPropertyCategory::Timing },         // -                Timing            n/a
    { SgfcPropertyType::OV, SgfcPropertyCategory::Timing },         // -                Timing            n/a
    { SgfcPropertyType::RG, SgfcPropertyCategory::Markup },         // -                "Sets of points can be marked [...]"
    { SgfcPropertyType::SC, SgfcPropertyCategory::Markup },         // -                "Sets of points can be marked [...]"
    { SgfcPropertyType::SE, SgfcPropertyCategory::Miscellaneous },  // -                 -                n/a
                                                                    // SE in Lines of Action is a Markup property
    { SgfcPropertyType::SI, SgfcPropertyCategory::MoveAnnotation }, // -                 MoveAnnotation   n/a
    { SgfcPropertyType::TC, SgfcPropertyCategory::Miscellaneous },  // -                 -                n/a
    { SgfcPropertyType::WS, SgfcPropertyCategory::GameInfo },       // GameInfo          Root             Root

    // Game of Go properties
    { SgfcPropertyType::HA, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::KM, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::TB, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::TW, SgfcPropertyCategory::Markup },

    // Game of Backgammon properties
    { SgfcPropertyType::CO, SgfcPropertyCategory::Setup },
    { SgfcPropertyType::CV, SgfcPropertyCategory::Setup },
    { SgfcPropertyType::DI, SgfcPropertyCategory::Setup },
    { SgfcPropertyType::MI, SgfcPropertyCategory::GameInfo },

    // Game of Lines of Action properties
    { SgfcPropertyType::IY, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::SU, SgfcPropertyCategory::GameInfo },
    
    // Game of Hex properties
    { SgfcPropertyType::IS, SgfcPropertyCategory::Root },

    // Game of Amazons properties
    { SgfcPropertyType::AA, SgfcPropertyCategory::Setup },

    // Game of Octi properties
    { SgfcPropertyType::BO, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::WO, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::NP, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::NR, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::NS, SgfcPropertyCategory::GameInfo },
    { SgfcPropertyType::CS, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::MS, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::SS, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::TS, SgfcPropertyCategory::Markup },
    { SgfcPropertyType::RP, SgfcPropertyCategory::Setup },

    // Properties for more than one game
    { SgfcPropertyType::AS, SgfcPropertyCategory::Miscellaneous },  // Lines of Action = Miscellaneous, Octi = Markup
    { SgfcPropertyType::IP, SgfcPropertyCategory::GameInfo },       // Hex = GameInfo

    // Non-standard properties
    { SgfcPropertyType::Unknown, SgfcPropertyCategory::Miscellaneous },
  };

  const std::map<SgfcPropertyType, SgfcPropertyTraits> SgfcConstants::PropertyTypeToPropertyTraitsMap =
  {
    // Standard properties from FF4
    { SgfcPropertyType::B, 0 },
    { SgfcPropertyType::KO, 0 },
    { SgfcPropertyType::MN, 0 },
    { SgfcPropertyType::W, 0 },
    { SgfcPropertyType::AB, 0 },
    { SgfcPropertyType::AE, 0 },
    { SgfcPropertyType::AW, 0 },
    { SgfcPropertyType::PL, 0 },
    { SgfcPropertyType::C, 0 },
    { SgfcPropertyType::DM, 0 },
    { SgfcPropertyType::GB, 0 },
    { SgfcPropertyType::GW, 0 },
    { SgfcPropertyType::HO, 0 },
    { SgfcPropertyType::N, 0 },
    { SgfcPropertyType::UC, 0 },
    { SgfcPropertyType::V, 0 },
    { SgfcPropertyType::BM, 0 },
    { SgfcPropertyType::DO, 0 },
    { SgfcPropertyType::IT, 0 },
    { SgfcPropertyType::TE, 0 },
    { SgfcPropertyType::AR, 0 },
    { SgfcPropertyType::CR, 0 },
    { SgfcPropertyType::DD, static_cast<SgfcPropertyTraits>(SgfcPropertyTrait::Inheritable) },
    { SgfcPropertyType::LB, 0 },
    { SgfcPropertyType::LN, 0 },
    { SgfcPropertyType::MA, 0 },
    { SgfcPropertyType::SL, 0 },
    { SgfcPropertyType::SQ, 0 },
    { SgfcPropertyType::TR, 0 },
    { SgfcPropertyType::AP, 0 },
    { SgfcPropertyType::CA, 0 },
    { SgfcPropertyType::FF, 0 },
    { SgfcPropertyType::GM, 0 },
    { SgfcPropertyType::ST, 0 },
    { SgfcPropertyType::SZ, 0 },
    { SgfcPropertyType::AN, 0 },
    { SgfcPropertyType::BR, 0 },
    { SgfcPropertyType::BT, 0 },
    { SgfcPropertyType::CP, 0 },
    { SgfcPropertyType::DT, 0 },
    { SgfcPropertyType::EV, 0 },
    { SgfcPropertyType::GN, 0 },
    { SgfcPropertyType::GC, 0 },
    { SgfcPropertyType::ON, 0 },
    { SgfcPropertyType::OT, 0 },
    { SgfcPropertyType::PB, 0 },
    { SgfcPropertyType::PC, 0 },
    { SgfcPropertyType::PW, 0 },
    { SgfcPropertyType::RE, 0 },
    { SgfcPropertyType::RO, 0 },
    { SgfcPropertyType::RU, 0 },
    { SgfcPropertyType::SO, 0 },
    { SgfcPropertyType::TM, 0 },
    { SgfcPropertyType::US, 0 },
    { SgfcPropertyType::WR, 0 },
    { SgfcPropertyType::WT, 0 },
    { SgfcPropertyType::BL, 0 },
    { SgfcPropertyType::OB, 0 },
    { SgfcPropertyType::OW, 0 },
    { SgfcPropertyType::WL, 0 },
    { SgfcPropertyType::FG, 0 },
    { SgfcPropertyType::PM, static_cast<SgfcPropertyTraits>(SgfcPropertyTrait::Inheritable) },
    { SgfcPropertyType::VW, static_cast<SgfcPropertyTraits>(SgfcPropertyTrait::Inheritable) },

    // Standard properties from FF1-3
    { SgfcPropertyType::BS, 0 },
    { SgfcPropertyType::CH, 0 },
    { SgfcPropertyType::EL, 0 },
    { SgfcPropertyType::EX, 0 },
    { SgfcPropertyType::ID, 0 },
    { SgfcPropertyType::L, 0 },
    { SgfcPropertyType::LT, 0 },
    { SgfcPropertyType::M, 0 },
    { SgfcPropertyType::OM, 0 },
    { SgfcPropertyType::OP, 0 },
    { SgfcPropertyType::OV, 0 },
    { SgfcPropertyType::RG, 0 },
    { SgfcPropertyType::SC, 0 },
    { SgfcPropertyType::SE, 0 },
    { SgfcPropertyType::SI, 0 },
    { SgfcPropertyType::TC, 0 },
    { SgfcPropertyType::WS, 0 },

    // Game of Go properties
    { SgfcPropertyType::HA, 0 },
    { SgfcPropertyType::KM, 0 },
    { SgfcPropertyType::TB, 0 },
    { SgfcPropertyType::TW, 0 },

    // Game of Backgammon properties
    { SgfcPropertyType::CO, 0 },
    { SgfcPropertyType::CV, 0 },
    { SgfcPropertyType::DI, 0 },
    { SgfcPropertyType::MI, 0 },

    // Game of Lines of Action properties
    { SgfcPropertyType::IY, 0 },
    { SgfcPropertyType::SU, 0 },

    // Game of Hex properties
    { SgfcPropertyType::IS, 0 },

    // Game of Amazons properties
    { SgfcPropertyType::AA, 0 },

    // Game of Octi properties
    { SgfcPropertyType::BO, 0 },
    { SgfcPropertyType::WO, 0 },
    { SgfcPropertyType::NP, 0 },
    { SgfcPropertyType::NR, 0 },
    { SgfcPropertyType::NS, 0 },
    { SgfcPropertyType::CS, 0 },
    { SgfcPropertyType::MS, 0 },
    { SgfcPropertyType::SS, 0 },
    { SgfcPropertyType::TS, 0 },
    { SgfcPropertyType::RP, 0 },

    // Properties for more than one game
    { SgfcPropertyType::AS, 0 },
    { SgfcPropertyType::IP, 0 },

    // Non-standard properties
    { SgfcPropertyType::Unknown, 0 },
  };

  const std::map<SgfcNumber, SgfcGameType> SgfcConstants::GameTypeAsNumberToGameTypeMap =
  {
    { 1, SgfcGameType::Go },
    { 2, SgfcGameType::Othello },
    { 3, SgfcGameType::Chess },
    { 4, SgfcGameType::GomokuAndRenju },
    { 5, SgfcGameType::NineMensMorris },
    { 6, SgfcGameType::Backgammon },
    { 7, SgfcGameType::ChineseChess },
    { 8, SgfcGameType::Shogi },
    { 9, SgfcGameType::LinesOfAction },
    { 10, SgfcGameType::Ataxx },
    { 11, SgfcGameType::Hex },
    { 12, SgfcGameType::Jungle },
    { 13, SgfcGameType::Neutron },
    { 14, SgfcGameType::PhilosophersFootball },
    { 15, SgfcGameType::Quadrature },
    { 16, SgfcGameType::Trax },
    { 17, SgfcGameType::Tantrix },
    { 18, SgfcGameType::Amazons },
    { 19, SgfcGameType::Octi },
    { 20, SgfcGameType::Gess },
    { 21, SgfcGameType::Twixt },
    { 22, SgfcGameType::Zertz },
    { 23, SgfcGameType::Plateau },
    { 24, SgfcGameType::Yinsh },
    { 25, SgfcGameType::Punct },
    { 26, SgfcGameType::Gobblet },
    { 27, SgfcGameType::Hive },
    { 28, SgfcGameType::Exxit },
    { 29, SgfcGameType::Hnefatal },
    { 30, SgfcGameType::Kuba },
    { 31, SgfcGameType::Tripples },
    { 32, SgfcGameType::Chase },
    { 33, SgfcGameType::TumblingDown },
    { 34, SgfcGameType::Sahara },
    { 35, SgfcGameType::Byte },
    { 36, SgfcGameType::Focus },
    { 37, SgfcGameType::Dvonn },
    { 38, SgfcGameType::Tamsk },
    { 39, SgfcGameType::Gipf },
    { 40, SgfcGameType::Kropki },
  };

  const std::map<SgfcGameType, SgfcNumber> SgfcConstants::GameTypeToGameTypeAsNumberMap =
  {
    { SgfcGameType::Go, 1 },
    { SgfcGameType::Othello, 2 },
    { SgfcGameType::Chess, 3 },
    { SgfcGameType::GomokuAndRenju, 4 },
    { SgfcGameType::NineMensMorris, 5 },
    { SgfcGameType::Backgammon, 6 },
    { SgfcGameType::ChineseChess, 7 },
    { SgfcGameType::Shogi, 8 },
    { SgfcGameType::LinesOfAction, 9 },
    { SgfcGameType::Ataxx, 10 },
    { SgfcGameType::Hex, 11 },
    { SgfcGameType::Jungle, 12 },
    { SgfcGameType::Neutron, 13 },
    { SgfcGameType::PhilosophersFootball, 14 },
    { SgfcGameType::Quadrature, 15 },
    { SgfcGameType::Trax, 16 },
    { SgfcGameType::Tantrix, 17 },
    { SgfcGameType::Amazons, 18 },
    { SgfcGameType::Octi, 19 },
    { SgfcGameType::Gess, 20 },
    { SgfcGameType::Twixt, 21 },
    { SgfcGameType::Zertz, 22 },
    { SgfcGameType::Plateau, 23 },
    { SgfcGameType::Yinsh, 24 },
    { SgfcGameType::Punct, 25 },
    { SgfcGameType::Gobblet, 26 },
    { SgfcGameType::Hive, 27 },
    { SgfcGameType::Exxit, 28 },
    { SgfcGameType::Hnefatal, 29 },
    { SgfcGameType::Kuba, 30 },
    { SgfcGameType::Tripples, 31 },
    { SgfcGameType::Chase, 32 },
    { SgfcGameType::TumblingDown, 33 },
    { SgfcGameType::Sahara, 34 },
    { SgfcGameType::Byte, 35 },
    { SgfcGameType::Focus, 36 },
    { SgfcGameType::Dvonn, 37 },
    { SgfcGameType::Tamsk, 38 },
    { SgfcGameType::Gipf, 39 },
    { SgfcGameType::Kropki, 40 },
  };

  const SgfcGameType SgfcConstants::DefaultGameType = SgfcGameType::Go;
  const SgfcNumber SgfcConstants::GameTypeNaN = std::numeric_limits<SgfcNumber>::min();;

  const SgfcBoardSize SgfcConstants::BoardSizeMinimum = { 1, 1 };
  const SgfcBoardSize SgfcConstants::BoardSizeMaximumGo = { 52, 52 };
  const SgfcBoardSize SgfcConstants::BoardSizeDefaultGo = { 19, 19 };
  const SgfcBoardSize SgfcConstants::BoardSizeDefaultChess = { 8, 8 };

  const SgfcBoardSize SgfcConstants::BoardSizeNone = { -1, -1 };
  const SgfcBoardSize SgfcConstants::BoardSizeInvalid = { -2, -2 };

  const SgfcNodeTraits SgfcConstants::NodeTraitsNone = 0;
  const SgfcNodeTraits SgfcConstants::NodeTraitsAll = std::numeric_limits<SgfcNodeTraits>::max();
  const SgfcPropertyTraits SgfcConstants::PropertyTraitsNone = 0;
  const SgfcPropertyTraits SgfcConstants::PropertyTraitsAll = std::numeric_limits<SgfcPropertyTraits>::max();
}
