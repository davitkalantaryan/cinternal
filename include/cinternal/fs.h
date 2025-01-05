//
// repo:			cinternal
// file:			fs.h
// path:			src/include/cinternal/logger.h
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_FS_H
#define CINTERNAL_INCLUDE_CINTERNAL_FS_H

#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C

#ifdef _MSC_VER
#define CINTERNAL_FILE_DELIMER01	'\\'
#define CINTERNAL_FILE_DELIMER02	'/'
#else
#define CINTERNAL_FILE_DELIMER01	'/'
#define CINTERNAL_FILE_DELIMER02	'\\'
#endif


#ifdef FileNameFromPossiblePathInline_needed
#undef FileNameFromPossiblePathInline_needed
static inline const char* FileNameFromPossiblePathInline(const char* a_cpcSrcPath) CPPUTILS_NOEXCEPT {
	const char* cpcTerm = strrchr(a_cpcSrcPath, CPPUTILS_FILE_DELIM_001);
	if (cpcTerm) { return cpcTerm + 1; }
	cpcTerm = strrchr(a_cpcSrcPath, CPPUTILS_FILE_DELIM_002);
	if (cpcTerm) { return cpcTerm + 1; }
	return a_cpcSrcPath;
}
#endif


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_FS_H
