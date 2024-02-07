#include "le3_script_bindings.h"
#include "le3_engine_systems.h"
using namespace le3;

FBIND_OBJECT_GETTER_VEC3(LE3Light, get_color, getColor)
FBIND_OBJECT_SETTER_VEC3(LE3Light, set_color, setColor)
FBIND_OBJECT_GETTER_NUMBER(LE3Light, get_intensity, getIntensity)
FBIND_OBJECT_SETTER_NUMBER(LE3Light, set_intensity, setIntensity)


LIB(LE3Light, get_color, set_color, get_intensity, set_intensity)
LIB(LE3AmbientLight)
LIB(LE3DirectionalLight)


FBIND_OBJECT_GETTER_NUMBER(LE3PointLight, get_attn_const, getAttnConst)
FBIND_OBJECT_SETTER_NUMBER(LE3PointLight, set_attn_const, setAttnConst)
FBIND_OBJECT_GETTER_NUMBER(LE3PointLight, get_attn_linear, getAttnLinear)
FBIND_OBJECT_SETTER_NUMBER(LE3PointLight, set_attn_linear, setAttnLinear)
FBIND_OBJECT_GETTER_NUMBER(LE3PointLight, get_attn_exp, getAttnExp)
FBIND_OBJECT_SETTER_NUMBER(LE3PointLight, set_attn_exp, setAttnExp)

LIB(LE3PointLight, 
    get_attn_const, set_attn_const,
    get_attn_linear, set_attn_linear,
    get_attn_exp, set_attn_exp,
)

// ----------------------------------------------------------------

FBIND_OBJECT_GETTER_NUMBER(LE3SpotLight, get_cutoff, getCutoff)
FBIND_OBJECT_SETTER_NUMBER(LE3SpotLight, set_cutoff, setCutoff)
FBIND_OBJECT_GETTER_NUMBER(LE3SpotLight, get_outer_cutoff, getOuterCutoff)
FBIND_OBJECT_SETTER_NUMBER(LE3SpotLight, set_outer_cutoff, setOuterCutoff)

LIB(LE3SpotLight, 
    get_cutoff, set_cutoff,
    get_outer_cutoff, set_outer_cutoff,
)
