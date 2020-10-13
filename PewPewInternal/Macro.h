#pragma once

#define STR_MERGE_IMPL(a,b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

#define TORAD(x) ((x) * 0.01745329252)

#define W2S(x,y) g_meme->WorldToScreen(x,y)


