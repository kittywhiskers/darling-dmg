#ifndef BE_HFS_H
#define BE_HFS_H

#include <drludif/endian.h>
#include "hfsplus.h"

template <> inline RecordType be(RecordType value)
{
	return RecordType(be16toh(uint16_t(value)));
}

#endif
