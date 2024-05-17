/**
 * Select dmadata table for version
 */
#ifdef NON_MATCHING
// For non-matching builds, dmadata is generated from the specfile segments
#include "dmadata/dmadata_table_spec.h"
#else
#include "dmadata/dmadata_table_us.h"
#endif
