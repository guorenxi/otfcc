#ifndef CARYLL_INCLUDE_GLYPH_ORDER_H
#define CARYLL_INCLUDE_GLYPH_ORDER_H

#include "dep/sds.h"
#include "dep/json.h"
#include "dep/uthash.h"
#include "caryll/ownership.h"
#include "otfcc/primitives.h"
#include "otfcc/handle.h"
#include "otfcc/options.h"

typedef struct {
	glyphid_t gid;
	sds name;
	uint8_t orderType;
	uint32_t orderEntry;
	UT_hash_handle hhID;
	UT_hash_handle hhName;
} otfcc_GlyphOrderEntry;

typedef struct {
	otfcc_GlyphOrderEntry *byGID;
	otfcc_GlyphOrderEntry *byName;
} otfcc_GlyphOrder;

otfcc_GlyphOrder *otfcc_new_GlyphOrder();
void otfcc_delete_GlyphOrder(otfcc_GlyphOrder *go);
sds otfcc_setGlyphOrderByGID(otfcc_GlyphOrder *go, glyphid_t gid, sds name);
glyphid_t otfcc_setGlyphOrderByName(otfcc_GlyphOrder *go, sds name, glyphid_t gid);
void otfcc_setGlyphOrderByNameWithOrder(otfcc_GlyphOrder *go, sds name, uint8_t orderType, uint32_t orderEntry);
void otfcc_orderGlyphs(otfcc_GlyphOrder *go);
otfcc_GlyphOrder *otfcc_parse_GlyphOrder(json_value *root, const otfcc_Options *options);
bool gord_nameAFieldShared(otfcc_GlyphOrder *go, glyphid_t gid, sds *field); // return a shared name pointer
bool gord_consolidateHandle(otfcc_GlyphOrder *go, otfcc_GlyphHandle *h);
otfcc_GlyphOrderEntry *otfcc_lookupName(otfcc_GlyphOrder *go, sds name);

otfcc_GlyphHandle gord_formIndexedHandle(otfcc_GlyphOrder *go, glyphid_t gid);
otfcc_GlyphHandle gord_formNamedHandle(otfcc_GlyphOrder *go, const sds name);

#endif