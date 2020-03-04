#pragma once

// Forward declarations
struct SGFInfo;

namespace LibSgfcPlusPlus
{
  /// @brief The SgfcBackendDataWrapper class is a wrapper around the SGFInfo
  /// data structure that is defined by the SGFC backend. SgfcBackendDataWrapper
  /// is responsible for managing the memory of an SGFInfo object.
  ///
  /// When SgfcBackendDataWrapper is constructed it immediately allocates
  /// the memory for a basic empty SGFInfo object that does not contain any
  /// data yet.
  ///
  /// While SgfcBackendDataWrapper lives, clients can access the SGFInfo object
  /// for the following purposes:
  /// - Only once: Pass the SGFInfo object to the SGFC backend for a load
  ///   operation. The SGFC backend will populate the SGFInfo object with
  ///   further data structures that contain the SGF data it loaded.
  ///   SgfcBackendDataWrapper becomes responsible for deallocating these
  ///   further data structures.
  /// - Any amount of times: Parse the SGFInfo object after it was populated
  ///   by an SGFC backend load operation.
  /// - Only once: Populate the empty SGFInfo object with data structures that
  ///   contain the SGF data to be passed to SGFC for writing.
  ///   SgfcBackendDataWrapper becomes responsible for deallocating the data
  ///   structures.
  /// - Only once: Pass the SGFInfo object to the SGFC backend for a save
  ///   operation. The SGFC backend will modify some of the data in the SGFInfo
  ///   object, so parsing the object before and after a save operation will
  ///   yield different results.
  ///
  /// When SgfcBackendDataWrapper is destroyed, it deallocates all memory
  /// that is currently occupied by the SGFInfo object. It doesn't matter
  /// whether an SGFC backend load and/or save operation have been performed
  /// since construction.
  class SgfcBackendDataWrapper
  {
  public:
    /// @brief Initializes a newly constructed SgfcBackendDataWrapper object
    /// that wraps an empty SGFInfo data structure.
    SgfcBackendDataWrapper();

    /// @brief Destroys and cleans up the SgfcBackendDataWrapper object.
    virtual ~SgfcBackendDataWrapper();

    /// @brief Returns a pointer to the SGFInfo data object that the
    /// SgfcBackendDataWrapper encapsulates.
    SGFInfo* GetSgfData() const;

  private:
    SGFInfo* sgfData;
  };
}
