/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "libsgfc++", "index.html", [
    [ "Project build system", "md__build.html", [
      [ "What is it?", "index.html#autotoc_md127", null ],
      [ "What it's not", "index.html#autotoc_md128", null ],
      [ "Dependencies", "index.html#autotoc_md129", null ],
      [ "Project build system", "index.html#autotoc_md130", null ],
      [ "More documentation", "index.html#autotoc_md131", null ],
      [ "Acknowledgment", "index.html#autotoc_md132", null ],
      [ "License", "index.html#autotoc_md133", null ],
      [ "Prerequisites", "md__build.html#autotoc_md1", null ],
      [ "How to build", "md__build.html#autotoc_md2", null ],
      [ "How to test", "md__build.html#autotoc_md3", [
        [ "Executing tests", "md__build.html#autotoc_md4", null ],
        [ "Integrating Catch2 into the build", "md__build.html#autotoc_md5", null ]
      ] ],
      [ "How to install", "md__build.html#autotoc_md6", null ],
      [ "How to generate and install the API documentation", "md__build.html#autotoc_md7", null ],
      [ "Sample code", "md__build.html#autotoc_md8", null ],
      [ "Enabling/disabling build products", "md__build.html#autotoc_md9", null ],
      [ "Xcode build", "md__build.html#autotoc_md10", null ],
      [ "Building on Windows", "md__build.html#autotoc_md11", [
        [ "Visual Studio", "md__build.html#autotoc_md12", null ],
        [ "Cygwin", "md__build.html#autotoc_md13", null ],
        [ "MinGW/MSYS", "md__build.html#autotoc_md14", null ]
      ] ],
      [ "Cross-compiling for iOS", "md__build.html#autotoc_md15", [
        [ "The old way: <span class=\"tt\">IOS_INSTALL_COMBINED</span>", "md__build.html#autotoc_md16", null ],
        [ "The new way: XCFramework", "md__build.html#autotoc_md17", null ],
        [ "Xcode's old/new build system", "md__build.html#autotoc_md18", null ]
      ] ],
      [ "Codesigning when building for iOS", "md__build.html#autotoc_md19", null ],
      [ "Deployment target when building for iOS", "md__build.html#autotoc_md20", null ],
      [ "Bundle identifier when building for iOS", "md__build.html#autotoc_md21", null ],
      [ "CMake support for downstream projects", "md__build.html#autotoc_md22", null ]
    ] ],
    [ "ChangeLog", "md__change_log.html", [
      [ "Version 3.0.0 (March 22 2026)", "md__change_log.html#autotoc_md24", [
        [ "Features", "md__change_log.html#autotoc_md25", null ],
        [ "Bugfixes", "md__change_log.html#autotoc_md26", null ],
        [ "Regressions", "md__change_log.html#autotoc_md27", null ],
        [ "Technical changes", "md__change_log.html#autotoc_md28", null ],
        [ "GitHub issue list", "md__change_log.html#autotoc_md29", null ]
      ] ],
      [ "Version 2.0.1 (January 5 2024)", "md__change_log.html#autotoc_md30", null ],
      [ "Version 2.0.0 (January 3 2024)", "md__change_log.html#autotoc_md31", [
        [ "Features", "md__change_log.html#autotoc_md32", null ],
        [ "Bugfixes", "md__change_log.html#autotoc_md33", null ],
        [ "Regressions", "md__change_log.html#autotoc_md34", null ],
        [ "Technical changes", "md__change_log.html#autotoc_md35", null ],
        [ "GitHub issue list", "md__change_log.html#autotoc_md36", null ]
      ] ],
      [ "Version 1.0 (February 23 2021)", "md__change_log.html#autotoc_md37", null ],
      [ "Version 0.2 (beta) (January 12 2021)", "md__change_log.html#autotoc_md38", null ],
      [ "Version 0.1 (alpha) (October 11 2020)", "md__change_log.html#autotoc_md39", null ],
      [ "September 20 2020", "md__change_log.html#autotoc_md40", null ],
      [ "May 23 2020", "md__change_log.html#autotoc_md41", null ],
      [ "April 09 2020", "md__change_log.html#autotoc_md42", null ],
      [ "February 5 2020", "md__change_log.html#autotoc_md43", null ]
    ] ],
    [ "Coding guidelines", "md__coding_guidelines.html", [
      [ "Naming", "md__coding_guidelines.html#autotoc_md45", null ],
      [ "Indentation and formatting", "md__coding_guidelines.html#autotoc_md46", null ],
      [ "Preprocessor", "md__coding_guidelines.html#autotoc_md47", null ],
      [ "Header files", "md__coding_guidelines.html#autotoc_md48", null ],
      [ "Code structure", "md__coding_guidelines.html#autotoc_md49", null ],
      [ "C++ language features", "md__coding_guidelines.html#autotoc_md50", null ],
      [ "Other stuff", "md__coding_guidelines.html#autotoc_md51", null ]
    ] ],
    [ "Library design and working principles", "md__principles.html", [
      [ "Public API vs. private implementation", "md__principles.html#autotoc_md53", null ],
      [ "Memory management", "md__principles.html#autotoc_md54", null ],
      [ "Concurrency", "md__principles.html#autotoc_md55", null ],
      [ "Operation modes", "md__principles.html#autotoc_md56", null ],
      [ "Error handling", "md__principles.html#autotoc_md57", [
        [ "SGFC messages", "md__principles.html#autotoc_md58", null ],
        [ "Exceptions", "md__principles.html#autotoc_md59", null ]
      ] ],
      [ "Document concept", "md__principles.html#autotoc_md60", null ],
      [ "Virtual inheritance", "md__principles.html#autotoc_md61", null ]
    ] ],
    [ "Project notes", "md__project_notes.html", [
      [ "Two project names: libsgfc++ and libsgfcplusplus", "md__project_notes.html#autotoc_md63", null ],
      [ "The export header file", "md__project_notes.html#autotoc_md64", [
        [ "Basics", "md__project_notes.html#autotoc_md65", null ],
        [ "Include directory", "md__project_notes.html#autotoc_md66", null ],
        [ "Angle syntax vs. quotes syntax when including", "md__project_notes.html#autotoc_md67", null ]
      ] ]
    ] ],
    [ "Release steps", "md__release_steps.html", [
      [ "Before the release", "md__release_steps.html#autotoc_md69", null ],
      [ "Create artifacts", "md__release_steps.html#autotoc_md70", [
        [ "Create an archive", "md__release_steps.html#autotoc_md71", null ],
        [ "Generate and publish API documentation", "md__release_steps.html#autotoc_md72", null ]
      ] ],
      [ "Make the release", "md__release_steps.html#autotoc_md73", null ]
    ] ],
    [ "SGFC notes", "md__sgfc_notes.html", [
      [ "Escaping", "md__sgfc_notes.html#autotoc_md75", null ],
      [ "Line breaks", "md__sgfc_notes.html#autotoc_md76", null ],
      [ "Pass moves for Go games", "md__sgfc_notes.html#autotoc_md77", null ],
      [ "Compressed point lists", "md__sgfc_notes.html#autotoc_md78", null ],
      [ "Why document writing works like it does today", "md__sgfc_notes.html#autotoc_md79", null ],
      [ "SGFC code reuse in a software library", "md__sgfc_notes.html#autotoc_md80", [
        [ "The <span class=\"tt\">main()</span> function", "md__sgfc_notes.html#autotoc_md81", null ],
        [ "Global functions", "md__sgfc_notes.html#autotoc_md82", null ],
        [ "Hooks/callbacks", "md__sgfc_notes.html#autotoc_md83", null ]
      ] ],
      [ "Handling of special properties", "md__sgfc_notes.html#autotoc_md84", null ],
      [ "Building SGFC on macOS", "md__sgfc_notes.html#autotoc_md87", [
        [ "Install <span class=\"tt\">check</span> testing framework", "md__sgfc_notes.html#autotoc_md88", null ],
        [ "Modify Makefiles", "md__sgfc_notes.html#autotoc_md89", null ],
        [ "Build", "md__sgfc_notes.html#autotoc_md90", null ]
      ] ]
    ] ],
    [ "SGFC Patches", "md__sgfc_patches.html", [
      [ "How to apply the patches", "md__sgfc_patches.html#autotoc_md92", null ],
      [ "Patches 001-015", "md__sgfc_patches.html#autotoc_md93", null ]
    ] ],
    [ "SGF notes", "md__sgf_notes.html", [
      [ "Object model", "md__sgf_notes.html#autotoc_md95", null ],
      [ "SGF format", "md__sgf_notes.html#autotoc_md96", null ],
      [ "Properties with no value", "md__sgf_notes.html#autotoc_md97", null ],
      [ "Pre-FF4 properties", "md__sgf_notes.html#autotoc_md98", null ],
      [ "Precision of properties with SGF type <span class=\"tt\">Real</span>", "md__sgf_notes.html#autotoc_md99", null ],
      [ "Value range of properties with SGF type <span class=\"tt\">Number</span>", "md__sgf_notes.html#autotoc_md100", null ],
      [ "Property value validation", "md__sgf_notes.html#autotoc_md101", null ],
      [ "Escaping", "md__sgf_notes.html#autotoc_md102", null ],
      [ "Line breaks", "md__sgf_notes.html#autotoc_md107", null ],
      [ "Compressed point lists", "md__sgf_notes.html#autotoc_md108", null ],
      [ "Go support", "md__sgf_notes.html#autotoc_md112", null ],
      [ "Inheritable properties", "md__sgf_notes.html#autotoc_md117", null ],
      [ "Character encoding", "md__sgf_notes.html#autotoc_md118", [
        [ "Introduction", "md__sgf_notes.html#autotoc_md119", null ],
        [ "Encoding modes", "md__sgf_notes.html#autotoc_md120", null ],
        [ "ASCII-compatible vs. ASCII-safe", "md__sgf_notes.html#autotoc_md121", null ],
        [ "Escaping and multi-byte character encodings", "md__sgf_notes.html#autotoc_md122", null ],
        [ "UTF-8 is recommended for programmatically creating ISgfcDocument object trees", "md__sgf_notes.html#autotoc_md123", null ],
        [ "UTF-8 support in <span class=\"tt\">ISgfcDocumentReader</span>", "md__sgf_notes.html#autotoc_md124", null ],
        [ "UTF-8 is the default character encoding in <span class=\"tt\">ISgfcDocumentWriter</span>", "md__sgf_notes.html#autotoc_md125", null ]
      ] ]
    ] ],
    [ "Why another library?", "md__why_another_library.html", null ],
    [ "Todo List", "todo.html", null ],
    [ "Topics", "topics.html", "topics" ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", null ],
        [ "Functions", "namespacemembers_func.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ]
      ] ]
    ] ],
    [ "Concepts", "concepts.html", "concepts" ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_i_sgfc_argument_8h_source.html",
"class_lib_sgfc_plus_plus_1_1_i_sgfc_document.html#ab4e4b46d26dfc1f472ebb76bdea7d16c",
"class_lib_sgfc_plus_plus_1_1_i_sgfc_game_info.html#adfa4e8695d6a454a233f9406d95b6246",
"class_lib_sgfc_plus_plus_1_1_i_sgfc_node.html#ad2e6424b881be25110577d8e49b3a62f",
"class_lib_sgfc_plus_plus_1_1_i_sgfc_single_property_value.html#a8c0b209887ed15406ce273738d225051",
"class_lib_sgfc_plus_plus_1_1_sgfc_document.html#ad4aaaf5c6a6fed6349ac62c9b4878e7a",
"class_lib_sgfc_plus_plus_1_1_sgfc_game_type_property.html#a13044e6f848943edd4e9b043133e1033",
"class_lib_sgfc_plus_plus_1_1_sgfc_node.html#aed192a74975ec305eae2ddf66109fcd9",
"class_lib_sgfc_plus_plus_1_1_sgfc_property_value_factory.html#ab7c4f7bbaaef9022a92afad368a6b72b",
"group__internals.html#gga571441add19dc4c28e8f7cdfcf8b0c66a0e4f72347fc57c7ddd6e7f6277f47eb8",
"group__public-api.html#ggafa2abf726df4472560967e1b7fc193eeaaada90cc294c8653a20746a6f5651b18",
"struct_lib_sgfc_plus_plus_1_1_sgfc_board_size.html"
];

var SYNCONMSG = 'click to disable panel synchronization';
var SYNCOFFMSG = 'click to enable panel synchronization';
var LISTOFALLMEMBERS = 'List of all members';