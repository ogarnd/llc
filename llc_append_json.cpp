#include "llc_append_json.h"

namespace llc
{
    stacxpr vcs PREPENDED_QUOT = LLC_CXS(",\"");
    stacxpr vcs NOPREPDED_QUOT = LLC_CXS("\"");

    err_t   appendOpenKey   (achar & output, vcs k       , bool prepSep)  { return append_strings(output, prepSep ? PREPENDED_QUOT : NOPREPDED_QUOT, k, "\":")              ; }
    err_t   appendKeyValue  (achar & output, vcs k, vcs v, bool prepSep)  { return append_strings(output, prepSep ? PREPENDED_QUOT : NOPREPDED_QUOT, k, "\":", v)           ; }
    err_t   appendKeyString (achar & output, vcs k, vcs v, bool prepSep)  { return append_strings(output, prepSep ? PREPENDED_QUOT : NOPREPDED_QUOT, k, "\":", '"',  v, '"'); }
    err_t   appendKeyList   (achar & output, vcs k, vcs v, bool prepSep)  { return append_strings(output, prepSep ? PREPENDED_QUOT : NOPREPDED_QUOT, k, "\":", '[',  v, ']'); }
    err_t   appendKeyObject (achar & output, vcs k, vcs v, bool prepSep)  { return append_strings(output, prepSep ? PREPENDED_QUOT : NOPREPDED_QUOT, k, "\":", '{',  v, '}'); }
}
