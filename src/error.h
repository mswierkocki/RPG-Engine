#ifndef _ERROR_H_
#define _ERROR_H_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Lindows.h"

void error (char*,...);
void fatal (char*,...);
void message (char*,...);

#endif /* _ERROR_H_ */
