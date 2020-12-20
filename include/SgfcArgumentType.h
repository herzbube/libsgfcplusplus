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

// Project includes (generated)
#include "SgfcPlusPlusExport.h"

namespace LibSgfcPlusPlus
{
  /// @brief SgfcArgumentType enumerates the arguments that can be passed on to
  /// SGFC when it reads or writes SGF content.
  ///
  /// @ingroup public-api
  ///
  /// Some arguments have a parameter, but most arguments do not. Unless
  /// documented otherwise an argument does not have a parameter.
  ///
  /// Some of the arguments with parameters can be specified multiple times.
  /// Unless documented otherwise an argument can be specified only once.
  ///
  /// Some arguments are specific for games of type Go (GM[1]), but most
  /// arguments are generic. Unless documented otherwise an argument works for
  /// all game types.
  ///
  /// The following SGFC command line options are not supported as SGFC
  /// arguments by libsgfc++:
  /// - Option -k. The library currently does not support preserving the
  ///   header in front of the SGF data. See GitHub issue #24 for details on
  ///   this decision.
  /// - Option -g. The library currently does not support game signatures.
  /// - Option -v. The library currently does not support querying the SGFC
  ///   version.
  /// - Option -s. The library currently does not support splitting a game
  ///   collection into separate files when writing out SGF content. This is
  ///   a limitation when working with ISgfcCommandLine. When working with
  ///   ISgfcDocumentWriter the library client can implement the splitting
  ///   function itself by writing out documents with a single game tree only.
  /// - Option -c. Unlike the SGFC command line program, the library gives the
  ///   client free rein in writing out SGF content even when it was read with
  ///   critical errors. It is the library client's job to examine the parse
  ///   results and take appropriate steps when it encounters critical errors.
  /// - Options -i, -h and --help. The library does not support these options
  ///   because they are useful only for an interactive command line program.
  /// - Option -U. The library client can achieve the same by specifying
  ///   #SgfcArgumentType::DefaultEncoding with parameter "UTF-8".
  enum class SGFCPLUSPLUS_EXPORT SgfcArgumentType
  {
    /// @brief Select how to search for the beginning of SGF data. This argument
    /// requires a numeric parameter value 1, 2 or 3. The corresponding SGFC
    /// command line option is -bx.
    ///
    /// The argument is invalid if you specify a parameter value that is not
    /// 1, 2 or 3.
    ///
    /// The parameter values 1-3 have the following meaning:
    /// - 1 = Advanced search algorithm (default)
    /// - 2 = First occurence of "(;"
    /// - 3 = First occurence of "("
    ///
    /// The advanced search algorithm can be said to be a combination of
    /// the more simple and straightforward algorithms 2 and 3. SGFC basically
    /// searches for "(;", but some erroneous files mark the beginning only
    /// with "(". To detect such files SGFC uses a more sophisticated search.
    /// In rare cases this might go wrong, so if you find yourself in that
    /// position you may wish to use the algorithm 2 or 3.
    BeginningOfSgfData,

    /// @brief Disable a given message ID. This argument requires an
    /// SgfcMessageID parameter value, the value denotes the ID of the message
    /// to disable. This argument can be specified multiple times.
    /// The corresponding SGFC command line option is -dn.
    ///
    /// If you feel that the SGFC syntax checking is too pedantic and generates
    /// too many messages, then you can use this argument to reduce the number
    /// of messages. You cannot use this argument to disable fatal error
    /// messages.
    ///
    /// Hints for a few non-critical warnings that you may wish to disable are
    /// #SgfcMessageID::EmptyValueDeleted,
    /// #SgfcMessageID::RequestedPropertyDeleted (since these messages are
    /// generated in response to an explicit request by the library client) and
    /// #SgfcMessageID::PropertyNotDefinedInFF.
    DisableMessageID,

    /// @brief Disable @b all warning messages. The corresponding SGFC command
    /// line option is -w.
    ///
    /// If you feel that the SGFC syntax checking is too pedantic and generates
    /// too many messages, then you can use this argument to reduce the number
    /// of messages.
    ///
    /// Use this argument with care!
    DisableWarningMessages,

    /// @brief Select how to interpret line breaks when reading Text property
    /// values. This argument requires a numeric parameter value 1, 2, 3 or 4.
    /// The corresponding SGFC command line option is -lx.
    ///
    /// This argument only affects how SGFC interprets SGF content during
    /// reading. When SGFC writes SGF content the output is always in FF4
    /// format.
    ///
    /// The argument is invalid if you specify a parameter value that is not
    /// 1, 2, 3 or 4.
    ///
    /// The parameter values 1-4 have the following meaning:
    /// - 1 = A line break preceded by a backslash ("\") character is treated
    ///       as a soft line break. All other line breaks are treated as a hard
    ///       line break. This is the default behaviour.
    /// - 2 = A line break preceded by a backslash ("\") character is treated
    ///       as a soft line break. A line break preceded by a space character
    ///       is converted to a space character (the result is that there are
    ///       now two space characters, the one that was in the original SGF
    ///       content and the one that was created by converting the line
    ///       break). All other line breaks are treated as a hard line break.
    ///       The SGFC documentation indicates that the MS-DOS/Windows
    ///       application "MGT" writes SGF content in this format.
    /// - 3 = A line break preceded by a backslash ("\") character is treated
    ///       as a soft line break. A single line break is converted to a space
    ///       character. Two line breaks are treated as a hard line break.
    /// - 4 = Experimentally determined that this seems to be almost the same
    ///       as parameter value 3. The distinction seems to be that the double
    ///       line break is preserved on writing. The SGFC documentation
    ///       characterizes this line break behaviour as "paragraph style
    ///       (ISHI format, MFGO)".
    ///
    /// @todo Find out more about parameter value 4. What does "paragraph style"
    /// mean? What is the ISHI format? MFGO is likely the abbreviation for the
    /// Go playing application "Many Faces of Go".
    HardLineBreakMode,

    /// @brief When writing SGF content try to make each line end at the end of
    /// a node. The corresponding SGFC command line option is -L.
    ///
    /// This argument affects how SGFC formats the output when it writes SGF
    /// content:
    /// - By default SGFC attempts to keep the line length to a certain maximum.
    ///   If that length were to be exceeded SGFC inserts a line break before it
    ///   writes out the next property. In case of a Text property SGFC inserts
    ///   a soft line break in the middle of the property value.
    /// - When this argument is specified, SGFC instead focuses on keeping a
    ///   node's content on the same line, inserting a line break before it
    ///   writes out the next node. This can lead to longer lines being written
    ///   when a node has many properties or properties have many values. Also
    ///   SGFC does not insert soft line breaks in the middle of a Text property
    ///   value.
    LineBreakAtEndOfNode,

    /// @brief Do not insert soft line breaks into Text values. The
    /// corresponding SGFC command line option is -t.
    ///
    /// This argument affects how SGFC formats the output when it writes SGF
    /// content:
    /// - By default SGFC attempts to keep the line length to a certain maximum.
    ///   If that length were to be exceeded SGFC inserts a line break before it
    ///   writes out the next property. In case of a Text property SGFC inserts
    ///   a soft line break in the middle of the property value.
    /// - When this argument is specified, SGFC never inserts soft line breaks
    ///   in the middle of a Text property value.
    ///
    /// Old SGF handling applications that pre-date FF4 cannot deal with soft
    /// line breaks. If you are concerned about compatibility to old
    /// applications you should specify this argument to avoid soft line breaks.
    NoSoftLineBreaksInTextValues,

    /// @brief Delete markup on current move. This argument works only for games
    /// of type Go (GM[1]). The corresponding SGFC command line option is -m.
    ///
    /// Definition of "markup on current move":
    /// - A node contains a move property (e.g. B[aa]).
    /// - The same node also contains a markup property (MA, CR, TR, SQ, SL).
    /// - The markup property marks the point on which the move in the same
    ///   node played a stone.
    ///
    /// Some Go game servers create SGF files where the current move is marked
    /// with e.g. a circle (CR[]). Some people find this annoying. Specifying
    /// this argument tells SGFC to delete any markup properties on the position
    /// of the current move.
    ///
    /// @note When a markup property is deleted because of this argument type,
    /// this results in an error type message with
    /// #SgfcMessageID::PositionNotUnique. Example:
    /// "Markup <CR> position not unique ([partially] deleted)".
    DeleteMarkupOnCurrentMove,

    /// @brief Delete empty nodes, i.e. nodes that contain no properties. The
    /// corresponding SGFC command line option is -n.
    ///
    /// There are empty nodes which cannot be deleted. These nodes are:
    /// - Root node, if it has more than one child.
    /// - A node which has siblings and has more than one child.
    ///
    /// @note When an empty node is deleted because of this argument type,
    /// this results in a warning type message with
    /// #SgfcMessageID::EmptyNodeDeleted. Example: "empty node deleted".
    DeleteEmptyNodes,

    /// @brief Delete obsolete properties, i.e. properties that are not part of
    /// FF4. The corresponding SGFC command line option is -o.
    ///
    /// SGFC knows all FF4 properties (general ones and Go specific ones) and
    /// all FF1-FF3 properties. Properties that are defined only in FF1-FF3 but
    /// not in FF4 are considered obsolete. When this argument is specified
    /// SGFC deletes all such obsolete properties it encounters. Exceptions:
    /// - "L" is converted to its FF4 counterpart "LB".
    /// - "M" is converted to an FF4 counterpart, either "MA" or "TR".
    ///
    /// @note When an obsolete property is deleted because of this argument
    /// type, this results in a warning type message with
    /// #SgfcMessageID::RequestedPropertyDeleted. Example:
    /// "obsolete property <EL> deleted". Regardless of whether this argument
    /// type is used or not, SGFC generates a warning type message with
    /// #SgfcMessageID::PropertyNotDefinedInFF when it encounters an obsolete
    /// property. Example:
    /// "property <EL> is not defined in FF[4] (parsing done anyway)".
    DeleteObsoleteProperties,

    /// @brief Delete unknown properties, i.e. properties that are not part of
    /// FF1-FF4. The corresponding SGFC command line option is -u.
    ///
    /// SGFC knows all FF4 properties (general ones and Go specific ones) and
    /// all FF1-FF3 properties. Properties that are not defined in any of these
    /// versions of the SGF standard are considered to be private properties of
    /// the application that was used to create the SGF content. When this
    /// argument is specified SGFC deletes all such unknown properties it
    /// encounters. Exceptions:
    /// - The "KI" property, which is a private property of the
    ///   "Smart Game Board" application (SGB), is converted to its FF4
    ///   counterpart "KM".
    ///
    /// @note When an unknown property is deleted because of this argument
    /// type, this results in a warning type message with
    /// #SgfcMessageID::UnknownPropertyDeleted. Example:
    /// "unknown property <XX> deleted".
    DeleteUnknownProperties,

    /// @brief Delete properties of a given property type. This argument
    /// requires an SgfcPropertyType parameter value, the value denotes the
    /// properties to delete. This option can be specified multiple times. The
    /// corresponding SGFC command line option is -yP.
    ///
    /// SGFC converts certain obsolete and unknown properties to an FF4
    /// counterpart. To delete these properties you have to specify their
    /// original type, i.e. the type before the conversion takes place. Exmaple:
    /// SGFC converts the "L" property to its FF4 counterpart "LB". You have
    /// to specify SgfcPropertyType::L do delete this property.
    ///
    /// The SgfcPropertyType enumeration contains a number of values for
    /// properties that SGFC does not know about. Example: Game-specific
    /// property types like "CO" (Backgammon) or "BO" (Octi). The argument is
    /// invalid if you specify an SgfcPropertyType value that refers to a
    /// property type that is not known by SGFC.
    ///
    /// @note When a property is deleted because of this argument type, this
    /// results in a warning type message with
    /// #SgfcMessageID::RequestedPropertyDeleted. Example:
    /// "property <FF> deleted".
    DeletePropertyType,

    /// @brief Write pass moves as "[tt]" if possible. This argument works only
    /// for games of type Go (GM[1]). The corresponding SGFC command line option
    /// is -p.
    ///
    /// The Go-specific part of FF4 specifies that pass moves should be written
    /// with an empty property value (e.g. B[]). For compatibility with FF3
    /// the value "tt" is still allowed, though (e.g. B[tt]). Specifying this
    /// argument causes SGFC to write pass moves out using the old "tt"
    /// notation. This is only possible if the board size is <= 19x19, because
    /// for board sizes 20x20 and larger the value "tt" refers to a valid
    /// location on the board. So for board sizes 20x20 and larger, SGFC writes
    /// a pass move with an empty property value even if this argument is
    /// specified.
    UseOldPassMoveNotation,

    /// @brief Enable restrictive checking. The corresponding SGFC command line
    /// option is -r.
    ///
    /// If this argument is set then SGFC is even more pedantic than usual. The
    /// argument is designed to flag all kinds of bad style or uncommon
    /// characteristics that can cause problems with applications that are just
    /// able to deal with common cases. For example, if the SGF content contains
    /// more than one game tree SGFC now issues an error instead of a warning.
    ///
    /// Furthermore for games of type Go (GM[1]) SGFC now checks that no two
    /// successive moves have the same color, that no setup properties
    /// (AB/AW/AE) appear in the main branch apart from the root node, and that
    /// the "HA" property is set correctly.
    EnableRestrictiveChecking,

    /// @brief Correct variation level and root moves. Variation level
    /// correction works only for games of type Go (GM[1]). The corresponding
    /// SGFC command line option is -v.
    ///
    /// It is bad style to have alternative moves at different tree levels. Some
    /// applications chose that way to represent variations as siblings instead
    /// of children - they add a child node, remove the latest move by using an
    /// "AE" property and put the alternative move into the node. When this
    /// argument is specified SGFC tries to correct such variations. Note that
    /// this kind of corrective action works only for games of type Go (GM[1]).
    ///
    /// Example: >>(;GM[1];B[aa](;W[bb])(;AE[aa]B[cc])(;AE[aa]B[dd]))<<
    /// Correct: >>(;GM[1](;B[aa];W[bb])(;B[cc])(;B[dd]))<<
    ///
    /// Another bad style is having the first move in the root node of a game
    /// tree. When this argument is specified SGFC splits the root node into
    /// two nodes and moves the first move into the second node. Note that this
    /// kind of corrective action works for all game types.
    ///
    /// Example: >>(;GM[1]C[first move in root node]GC[bad style]B[aa])<<
    /// Correct: >>(;GM[1]GC[good style];B[aa]C[first move not in root node])<<
    ///
    /// @note Variation fixes and root move fixes made because of this argument
    /// type result in warning type messages with
    /// #SgfcMessageID::VariationLevelCorrected and
    /// #SgfcMessageID::MoveInRootNodeSplit, respectively.
    /// Examples: "variation level corrected" and "move in root node found
    /// (splitted node into two)".
    CorrectVariationLevelAndRootMoves,

    /// @brief Reverse ordering of variations. The corresponding SGFC command
    /// line option is -z.
    ///
    /// It is bad style to have the main line of the game not in the main branch
    /// (variation "A"). When this argument is specified SGFC reverses the
    /// ordering of all variations in a game tree, assuming that the main line
    /// of the game is actually in the last branch. Example: Variations A,B,C,D
    /// are reordered as D,C,B,A.
    ///
    /// The function can reorder only up to a hardcoded limit of variations
    /// of a single node. If you hit this limit you need to adjust the
    /// preprocessor macro MAX_REORDER_VARIATIONS in file all.h to a higher
    /// value and recompile SGFC and libsgfc++.
    ReverseVariationOrdering,

    /// @brief When writing SGF content, expand compressed point lists. This
    /// argument works only for games of type Go (GM[1]). The corresponding SGFC
    /// command line option is -e.
    ///
    /// This argument affects how SGFC formats the output when it writes SGF
    /// content:
    /// - By default when the game type is Go (GM[1]) and SGFC encounters a
    ///   property with a point list value type (e.g. property "MA"), it
    ///   attempts to compress the point values to take advantage of the FF4
    ///   "compressed point lists" format. If SGFC reads in SGF content that
    ///   already contains point lists in the compressed format, it retains the
    ///   compressed format when writing the SGF content.
    /// - When this argument is specified, SGFC does not compress uncompressed
    ///   point lists, and it actively expands point lists that were in the
    ///   compressed format in the original SGF content.
    ///
    /// Old SGF handling applications that pre-date FF4 cannot deal with the
    /// compressed format. If you are concerned about compatibility to old
    /// applications you should specify this argument to avoid compressed point
    /// lists.
    ///
    /// @note After reading in SGF content point lists are always made
    /// available to the library client in uncompressed form in the document
    /// object tree.
    ExpandCompressedPointLists,

    /// @brief Select how to determine the character encoding(s) used to decode
    /// SGF content. This argument requires a numeric parameter value 1, 2
    /// or 3. The corresponding SGFC command line option is -Ex.
    ///
    /// The argument is invalid if you specify a parameter value that is not
    /// 1, 2 or 3.
    ///
    /// The parameter values 1-3 have the following meaning:
    /// - Mode 1 (the default mode): A single encoding is used to decode the
    ///   @b entire SGF content. The encoding to use is detected by probing the
    ///   SGF content. If a Unicode BOM marker is found then the encoding
    ///   defined by that marker is used, but the first CA property in the
    ///   decoded SGF content must match the encoding detected from the BOM.
    ///   If no Unicode BOM marker is found then the SGF content is probed for
    ///   CA properties, and the first CA property value found is used as the
    ///   encoding. If no CA property is found the default encoding ISO-8859-1
    ///   is used. Note that only this mode allows the wide-character encodings
    ///   UTF-16 and UTF-32 to be processed (via BOM detection).
    /// - Mode 2 (specification conformant): A separate encoding is used to
    ///   decode each game tree in the SGF content. The encoding is defined by
    ///   the CA property value of that game tree. If a game tree has no CA
    ///   property the default encoding ISO-8859-1 is used. Only SimpleText and
    ///   Text property values are decoded! The SGF formatting skeleton as well
    ///   as property values that are not SimpleText or Text are parsed using
    ///   ASCII/ISO-8859-1.
    /// - Mode 3: No decoding takes place.
    ///
    /// @note Mode 2 is the behaviour as designed by the SGF standard. This is
    /// somewhat antiquated as it not only allows SGF content to be partially
    /// encoded, it even allows different encodings to be used within the same
    /// piece of SGF content. It also breaks the notion of SGF as text files.
    /// Mode 1, even though it does not conform to the SGF standard, is what
    /// most likely can be expected from modern-day applications that encode an
    /// entire file and use the same encoding for the entire file.
    ///
    /// @attention When mode 1 is used decoding occurs before parsing, when
    /// mode 2 is used decoding occurs after parsing. This can be important
    /// when SGF content is encoded with a multi-byte encoding, and one or
    /// more multi-byte characters contain bytes that correspond to ASCII
    /// characters that are relevant for the SGF format (escape character,
    /// property closing character). Examples that illustrate the problem can
    /// be found in SgfNotes.md.
    ///
    /// When mode 1 or 2 are used for reading, the SGF content is decoded and
    /// made available to the library client as UTF-8. Accordingly each decoded
    /// game tree's root node is populated with a CA property value "UTF-8".
    /// When mode 3 is used no decoding takes place and the library client
    /// receives the SGF content as-is.
    ///
    /// When node 1 or 2 are used for @b writing, the SGF content in the
    /// object tree is internally decoded according to the rules documented
    /// above before it is actually written out. This allows library clients to
    /// provide content in encodings that are not UTF-8. Care must be taken not
    /// to mix encodings in the same  object tree! For instance a library client
    /// might first read SGF content from some source using encoding mode 1 or
    /// 2, which produces an object tree in UTF-8, then it could modify the
    /// object tree with values in an encoding that is @b not UTF-8. Writing
    /// out such an object tree that contains values in mixed encodings is
    /// likely to produce invalid results.
    ///
    /// @see SgfcArgumentType::DefaultEncoding
    /// @see SgfcArgumentType::ForcedEncoding
    EncodingMode,

    /// @brief Select the default encoding to be used if the SGF content does
    /// not contain a CA property. This argument requires a string parameter
    /// value. The corresponding SGFC command line option is --default-encoding.
    ///
    /// The default value is ISO-8859-1. Valid values depend on the iconv
    /// implementation used by libsgfc++. Invoke "iconv --list" on the command
    /// line to see a list of supported encodings.
    ///
    /// @see SgfcArgumentType::EncodingMode
    /// @see SgfcArgumentType::ForcedEncoding
    DefaultEncoding,

    /// @brief Select the encoding to be used. This overrides even a CA property
    /// found in the SGF content. This argument requires a string parameter
    /// value. The corresponding SGFC command line option is --encoding.
    ///
    /// The argument has no default value. Valid values depend on the iconv
    /// implementation used by libsgfc++. Invoke "iconv --list" on the command
    /// line to see a list of supported encodings.
    ///
    /// @see SgfcArgumentType::EncodingMode
    /// @see SgfcArgumentType::DefaultEncoding
    ForcedEncoding,
  };
}
