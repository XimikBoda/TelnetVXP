#pragma once
#include "vmsys.h"
#include "vmio.h"
#include "vmgraph.h"
#include "vmchset.h"
#include "vmstdlib.h"
#include "ResID.h"
#include "string.h"

extern int scr_w, scr_h;
extern VMUINT8 *layer_bufs[2];
extern VMINT layer_hdls[2];

const unsigned short tr_color = VM_COLOR_888_TO_565(0, 255, 255);