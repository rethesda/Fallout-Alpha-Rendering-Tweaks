#pragma once

class BSShader;
class ShadowSceneNode;
class BSRenderedTexture;
class BSShaderAccumulator;
class NiDX9Renderer;
class TangentSpaceData;

class BSShaderManager {
public:
	enum SceneGraphType : UInt32 {
		BSSM_SSN_WORLD = 0x0,
		BSSM_SSN_MENU_OBJECT_3D = 0x1,
		BSSM_SSN_UNK_2 = 0x2,
		BSSM_SSN_MENU_PLAYER_3D = 0x3,
		BSSM_SSN_COUNT = 0x4,
	};

	enum ShaderType : UInt32 {
		BSSM_SHADER_DEFAULT = 0x0,
		BSSM_SHADER_SHADOWLIGHT = 0x1,
		BSSM_SHADER_TALL_GRASS = 0x2,
		BSSM_SHADER_DISTANT_LOD = 0x3,
		BSSM_SHADER_ST_BRANCH = 0x4,
		BSSM_SHADER_ST_FROND = 0x5,
		BSSM_SHADER_ST_LEAF = 0x6,
		BSSM_SHADER_BLOOD_SPLATTER = 0x7,
		BSSM_SHADER_DISTANT_TREE = 0x8,
		BSSM_SHADER_DEBUG = 0x9,
		BSSM_SHADER_SKY = 0xA,
		BSSM_SHADER_HAIR = 0xD,
		BSSM_SHADER_SKIN = 0xE,
		BSSM_SHADER_PARALLAX = 0xF,
		BSSM_SHADER_NiDX9ShaderDeclaration = 0x10,
		BSSM_SHADER_WATER = 0x11,
		BSSM_SHADER_PARTICLE = 0x18,
		BSSM_SHADER_BOLT = 0x19,
		BSSM_SHADER_BEAM = 0x1A,
		BSSM_SHADER_LIGHTING30 = 0x1D,
		BSSM_SHADER_PRECIPITATION = 0x1E,
		BSSM_SHADER_TILE = 0x20,
		BSSM_SHADER_NOLIGHTING = 0x21,
		BSSM_SHADER_VOLUMETRIC_FOG = 0x22,
	};

	enum RenderPassType : UInt32 {
		BSSM_EMPTY = 0x0,
		BSSM_ZONLY = 0x1,
		BSSM_ZONLY_At = 0x2,
		BSSM_ZONLY_S = 0x3,
		BSSM_ZONLY_TEXEFFECT = 0x4,
		BSSM_ZONLY_TEXEFFECT_S = 0x5,
		BSSM_CONSTALPHA = 0x6,
		BSSM_CONSTALPHA_At = 0x7,
		BSSM_CONSTALPHA_S = 0x8,
		BSSM_AMBIENT_OCCLUSION = 0x9,
		BSSM_3XZONLY = 0xA,
		BSSM_3XZONLY_S = 0xB,
		BSSM_3XZONLY_Vc = 0xC,
		BSSM_3XZONLY_SVc = 0xD,
		BSSM_3XZONLY_TEXEFFECT = 0xE,
		BSSM_3XZONLY_TEXEFFECT_S = 0xF,
		BSSM_DEPTHMAP = 0x10,
		BSSM_DEPTHMAP_At = 0x11,
		BSSM_DEPTHMAP_S = 0x12,
		BSSM_DEPTHMAP_SAt = 0x13,
		BSSM_SELFILLUMALPHABLOCK = 0x14,
		BSSM_SELFILLUMALPHABLOCK_S = 0x15,
		BSSM_GRASS_NOALPHA_DIRONLY_LF = 0x16,
		BSSM_GRASS_NOALPHA_DIRONLY_LV = 0x17,
		BSSM_GRASS_NOALPHA_DIRONLY_LFS = 0x18,
		BSSM_GRASS_NOALPHA_DIRONLY_LVS = 0x19,
		BSSM_GRASS_NOALPHA_DIRONLY_LFP = 0x1A,
		BSSM_GRASS_NOALPHA_DIRONLY_LVP = 0x1B,
		BSSM_GRASS_NOALPHA_DIRONLY_LFSP = 0x1C,
		BSSM_GRASS_NOALPHA_DIRONLY_LVSP = 0x1D,
		BSSM_GRASS_NOALPHA_DIRONLY_LFShp = 0x1E,
		BSSM_GRASS_NOALPHA_DIRONLY_LVShp = 0x1F,
		BSSM_GRASS_NOALPHA_DIRONLY_LFSShp = 0x20,
		BSSM_GRASS_NOALPHA_DIRONLY_LVSShp = 0x21,
		BSSM_GRASS_NOALPHA_DIRONLY_LFPShp = 0x22,
		BSSM_GRASS_NOALPHA_DIRONLY_LVPShp = 0x23,
		BSSM_GRASS_NOALPHA_DIRONLY_LFSPShp = 0x24,
		BSSM_GRASS_NOALPHA_DIRONLY_LVSPShp = 0x25,
		BSSM_GRASS_NOALPHA_DIRONLY_LFB = 0x26,
		BSSM_GRASS_NOALPHA_DIRONLY_LFSB = 0x27,
		BSSM_GRASS_NOALPHA_DIRONLY_LFPB = 0x28,
		BSSM_GRASS_NOALPHA_DIRONLY_LFSPB = 0x29,
		BSSM_GRASS_NOALPHA_1POINT_LF = 0x2A,
		BSSM_GRASS_NOALPHA_1POINT_LV = 0x2B,
		BSSM_GRASS_NOALPHA_1POINT_LFS = 0x2C,
		BSSM_GRASS_NOALPHA_1POINT_LVS = 0x2D,
		BSSM_GRASS_NOALPHA_1POINT_LFP = 0x2E,
		BSSM_GRASS_NOALPHA_1POINT_LVP = 0x2F,
		BSSM_GRASS_NOALPHA_1POINT_LFSP = 0x30,
		BSSM_GRASS_NOALPHA_1POINT_LVSP = 0x31,
		BSSM_GRASS_NOALPHA_1POINT_LFShp = 0x32,
		BSSM_GRASS_NOALPHA_1POINT_LVShp = 0x33,
		BSSM_GRASS_NOALPHA_1POINT_LFSShp = 0x34,
		BSSM_GRASS_NOALPHA_1POINT_LVSShp = 0x35,
		BSSM_GRASS_NOALPHA_1POINT_LFPShp = 0x36,
		BSSM_GRASS_NOALPHA_1POINT_LVPShp = 0x37,
		BSSM_GRASS_NOALPHA_1POINT_LFSPShp = 0x38,
		BSSM_GRASS_NOALPHA_1POINT_LVSPShp = 0x39,
		BSSM_GRASS_NOALPHA_1POINT_LFB = 0x3A,
		BSSM_GRASS_NOALPHA_1POINT_LFSB = 0x3B,
		BSSM_GRASS_NOALPHA_1POINT_LFPB = 0x3C,
		BSSM_GRASS_NOALPHA_1POINT_LFSPB = 0x3D,
		BSSM_LEAVES_AD = 0x3E,
		BSSM_LEAVES_ADPt = 0x3F,
		BSSM_FRONDS = 0x40,
		BSSM_PARTICLE_PREPASS = 0x41,
		BSSM_NOLIGHTING = 0x42,
		BSSM_NOLIGHTING_VC = 0x43,
		BSSM_NOLIGHTING_TexVC = 0x44,
		BSSM_NOLIGHTING_MAT = 0x45,
		BSSM_NOLIGHTING_S = 0x46,
		BSSM_NOLIGHTING_VC_S = 0x47,
		BSSM_NOLIGHTING_TexVC_S = 0x48,
		BSSM_NOLIGHTING_MAT_S = 0x49,
		BSSM_NOLIGHTING_FALLOFF = 0x4A,
		BSSM_NOLIGHTING_VC_FALLOFF = 0x4B,
		BSSM_NOLIGHTING_TexVC_FALLOFF = 0x4C,
		BSSM_NOLIGHTING_MAT_FALLOFF = 0x4D,
		BSSM_NOLIGHTING_FALLOFF_S = 0x4E,
		BSSM_NOLIGHTING_VC_FALLOFF_S = 0x4F,
		BSSM_NOLIGHTING_TexVC_FALLOFF_S = 0x50,
		BSSM_NOLIGHTING_MAT_FALLOFF_S = 0x51,
		BSSM_NOLIGHTING_PSYS = 0x52,
		BSSM_NOLIGHTING_PSYS_SUBTEX_OFFSET = 0x53,
		BSSM_NOLIGHTING_PSYS_PREMULT_ALPHA = 0x54,
		BSSM_NOLIGHTING_PSYS_SUBTEX_OFFSET_PREMULT_ALPHA = 0x55,
		BSSM_NOLIGHTING_STRIP_PSYS = 0x56,
		BSSM_NOLIGHTING_STRIP_PSYS_SUBTEX = 0x57,
		BSSM_AMBIENT = 0x58,
		BSSM_AMBIENT_G = 0x59,
		BSSM_AMBIENT_At = 0x5A,
		BSSM_AMBIENT_GAt = 0x5B,
		BSSM_AMBIENT_S = 0x5C,
		BSSM_AMBIENT_SG = 0x5D,
		BSSM_AMBIENT_SAt = 0x5E,
		BSSM_AMBIENT_SGAt = 0x5F,
		BSSM_AMBIENT_Sb = 0x60,
		BSSM_AMBIENT_Mn = 0x61,
		BSSM_AMBIENT_F = 0x62,
		BSSM_AMBIENT_FAt = 0x63,
		BSSM_AMBDIFFTEX = 0x64,
		BSSM_AMBDIFFTEX_Vc = 0x65,
		BSSM_AMBDIFFTEX_G = 0x66,
		BSSM_AMBDIFFTEX_GVc = 0x67,
		BSSM_AMBDIFFTEX_Fg = 0x68,
		BSSM_AMBDIFFTEX_A = 0x69,
		BSSM_AMBDIFFTEX_AVc = 0x6A,
		BSSM_AMBDIFFTEX_GA = 0x6B,
		BSSM_AMBDIFFTEX_GAVc = 0x6C,
		BSSM_AMBDIFFTEX_FgA = 0x6D,
		BSSM_AMBDIFFTEX_GFgA = 0x6E,
		BSSM_AMBDIFFTEX_S = 0x6F,
		BSSM_AMBDIFFTEX_SVc = 0x70,
		BSSM_AMBDIFFTEX_SG = 0x71,
		BSSM_AMBDIFFTEX_SGVc = 0x72,
		BSSM_AMBDIFFTEX_SFg = 0x73,
		BSSM_AMBDIFFTEX_SA = 0x74,
		BSSM_AMBDIFFTEX_SAVc = 0x75,
		BSSM_AMBDIFFTEX_SGA = 0x76,
		BSSM_AMBDIFFTEX_SGAVc = 0x77,
		BSSM_AMBDIFFTEX_SFgA = 0x78,
		BSSM_AMBDIFFTEX_SGFgA = 0x79,
		BSSM_AMBDIFFTEX_Sb = 0x7A,
		BSSM_AMBDIFFTEX_SbF = 0x7B,
		BSSM_AMBDIFFDIRANDPT = 0x7C,
		BSSM_AMBDIFFDIRANDPT_S = 0x7D,
		BSSM_AMBDIFFDIRANDPT_Sb = 0x7E,
		BSSM_AMBDIFFTEX_F = 0x7F,
		BSSM_AMBDIFFTEX_FVc = 0x80,
		BSSM_AMBDIFFTEX_FG = 0x81,
		BSSM_AMBDIFFTEX_FGVc = 0x82,
		BSSM_AMBDIFFTEX_FA = 0x83,
		BSSM_AMBDIFFTEX_FAVc = 0x84,
		BSSM_AMBDIFFTEX_FFg = 0x85,
		BSSM_AMBDIFFTEX_FGA = 0x86,
		BSSM_AMBDIFFTEX_FGAVc = 0x87,
		BSSM_AMBDIFFTEX_FGFgA = 0x88,
		BSSM_AMBDIFFTEX_SF = 0x89,
		BSSM_AMBDIFFTEX_SFVc = 0x8A,
		BSSM_AMBDIFFTEX_SFG = 0x8B,
		BSSM_AMBDIFFTEX_SFGVc = 0x8C,
		BSSM_AMBDIFFTEX_SFA = 0x8D,
		BSSM_AMBDIFFTEX_SFAVc = 0x8E,
		BSSM_AMBDIFFTEX_SFFg = 0x8F,
		BSSM_AMBDIFFTEX_SFGA = 0x90,
		BSSM_AMBDIFFTEX_SFGAVc = 0x91,
		BSSM_AMBDIFFTEX_SFGFgA = 0x92,
		BSSM_LANDAD = 0x93,
		BSSM_LANDAD_Shp = 0x94,
		BSSM_ADTS = 0x95,
		BSSM_ADTS_G = 0x96,
		BSSM_ADTS_H = 0x97,
		BSSM_ADTS_Fg = 0x98,
		BSSM_ADTS_Px = 0x99,
		BSSM_ADTS_GPx = 0x9A,
		BSSM_ADTS_S = 0x9B,
		BSSM_ADTS_SG = 0x9C,
		BSSM_ADTS_SH = 0x9D,
		BSSM_ADTS_SFg = 0x9E,
		BSSM_ADTS_Sb = 0x9F,
		BSSM_ADTS_Shp = 0xA0,
		BSSM_ADTS_GShp = 0xA1,
		BSSM_ADTS_HShp = 0xA2,
		BSSM_ADTS_FgShp = 0xA3,
		BSSM_ADTS_PxShp = 0xA4,
		BSSM_ADTS_GPxShp = 0xA5,
		BSSM_ADTS_SShp = 0xA6,
		BSSM_ADTS_SGShp = 0xA7,
		BSSM_ADTS_SHShp = 0xA8,
		BSSM_ADTS_SFgShp = 0xA9,
		BSSM_ADTS_SbShp = 0xAA,
		BSSM_ADTS2 = 0xAB,
		BSSM_ADTS2_G = 0xAC,
		BSSM_ADTS2_H = 0xAD,
		BSSM_ADTS2_Fg = 0xAE,
		BSSM_ADTS2_Px = 0xAF,
		BSSM_ADTS2_GPx = 0xB0,
		BSSM_ADTS2_S = 0xB1,
		BSSM_ADTS2_SG = 0xB2,
		BSSM_ADTS2_SH = 0xB3,
		BSSM_ADTS2_SFg = 0xB4,
		BSSM_ADTS2_Sb = 0xB5,
		BSSM_ADTS2_Shp = 0xB6,
		BSSM_ADTS2_GShp = 0xB7,
		BSSM_ADTS2_HShp = 0xB8,
		BSSM_ADTS2_FgShp = 0xB9,
		BSSM_ADTS2_PxShp = 0xBA,
		BSSM_ADTS2_GPxShp = 0xBB,
		BSSM_ADTS2_SShp = 0xBC,
		BSSM_ADTS2_SGShp = 0xBD,
		BSSM_ADTS2_SHShp = 0xBE,
		BSSM_ADTS2_SFgShp = 0xBF,
		BSSM_ADTS2_SbShp = 0xC0,
		BSSM_ADTS_ONELIGHT = 0xC1,
		BSSM_ADTS_DIRANDPT = 0xC2,
		BSSM_ADT10 = 0xC3,
		BSSM_ADT10_G = 0xC4,
		BSSM_ADT10_Fg = 0xC5,
		BSSM_ADT10_S = 0xC6,
		BSSM_ADT10_SG = 0xC7,
		BSSM_ADT10_SFg = 0xC8,
		BSSM_ADT4 = 0xC9,
		BSSM_ADT4_Opt = 0xCA,
		BSSM_ADT4_G = 0xCB,
		BSSM_ADT4_Fg = 0xCC,
		BSSM_ADT4_S = 0xCD,
		BSSM_ADT4_SG = 0xCE,
		BSSM_ADT4_SFg = 0xCF,
		BSSM_ADTS10 = 0xD0,
		BSSM_ADTS10_Opt = 0xD1,
		BSSM_ADTS10_G = 0xD2,
		BSSM_ADTS10_Fg = 0xD3,
		BSSM_ADTS10_S = 0xD4,
		BSSM_ADTS10_SG = 0xD5,
		BSSM_ADTS10_SFg = 0xD6,
		BSSM_AD2 = 0xD7,
		BSSM_AD2_G = 0xD8,
		BSSM_AD2_Px = 0xD9,
		BSSM_AD2_GPx = 0xDA,
		BSSM_AD2_Fg = 0xDB,
		BSSM_AD2_S = 0xDC,
		BSSM_AD2_SG = 0xDD,
		BSSM_AD2_SFg = 0xDE,
		BSSM_AD2_Sb = 0xDF,
		BSSM_AD2_Shp = 0xE0,
		BSSM_AD2_GShp = 0xE1,
		BSSM_AD2_PxShp = 0xE2,
		BSSM_AD2_GPxShp = 0xE3,
		BSSM_AD2_FgShp = 0xE4,
		BSSM_AD2_SShp = 0xE5,
		BSSM_AD2_SGShp = 0xE6,
		BSSM_AD2_SFgShp = 0xE7,
		BSSM_AD2_SbShp = 0xE8,
		BSSM_AD3 = 0xE9,
		BSSM_AD3_G = 0xEA,
		BSSM_AD3_Px = 0xEB,
		BSSM_AD3_GPx = 0xEC,
		BSSM_AD3_Fg = 0xED,
		BSSM_AD3_S = 0xEE,
		BSSM_AD3_SG = 0xEF,
		BSSM_AD3_SFg = 0xF0,
		BSSM_AD3_Sb = 0xF1,
		BSSM_AD3_Shp = 0xF2,
		BSSM_AD3_GShp = 0xF3,
		BSSM_AD3_PxShp = 0xF4,
		BSSM_AD3_GPxShp = 0xF5,
		BSSM_AD3_FgShp = 0xF6,
		BSSM_AD3_SShp = 0xF7,
		BSSM_AD3_SGShp = 0xF8,
		BSSM_AD3_SFgShp = 0xF9,
		BSSM_AD3_SbShp = 0xFA,
		BSSM_ADT = 0xFB,
		BSSM_ADT_Opt = 0xFC,
		BSSM_ADT_OptLOD = 0xFD,
		BSSM_ADT_Mn = 0xFE,
		BSSM_ADT_G = 0xFF,
		BSSM_ADT_Fg = 0x100,
		BSSM_ADT_Px = 0x101,
		BSSM_ADT_PxOpt = 0x102,
		BSSM_ADT_GPx = 0x103,
		BSSM_ADT_H = 0x104,
		BSSM_ADT_S = 0x105,
		BSSM_ADT_SG = 0x106,
		BSSM_ADT_SFg = 0x107,
		BSSM_ADT_Sb = 0x108,
		BSSM_ADT_SH = 0x109,
		BSSM_ADT_Shp = 0x10A,
		BSSM_ADT_MnShp = 0x10B,
		BSSM_ADT_GShp = 0x10C,
		BSSM_ADT_FgShp = 0x10D,
		BSSM_ADT_PxShp = 0x10E,
		BSSM_ADT_GPxShp = 0x10F,
		BSSM_ADT_HShp = 0x110,
		BSSM_ADT_SShp = 0x111,
		BSSM_ADT_SGShp = 0x112,
		BSSM_ADT_SFgShp = 0x113,
		BSSM_ADT_SbShp = 0x114,
		BSSM_ADT_SHShp = 0x115,
		BSSM_ADT2 = 0x116,
		BSSM_ADT2_G = 0x117,
		BSSM_ADT2_Fg = 0x118,
		BSSM_ADT2_Px = 0x119,
		BSSM_ADT2_GPx = 0x11A,
		BSSM_ADT2_H = 0x11B,
		BSSM_ADT2_S = 0x11C,
		BSSM_ADT2_SG = 0x11D,
		BSSM_ADT2_SFg = 0x11E,
		BSSM_ADT2_Sb = 0x11F,
		BSSM_ADT2_SH = 0x120,
		BSSM_ADT2_Shp = 0x121,
		BSSM_ADT2_GShp = 0x122,
		BSSM_ADT2_FgShp = 0x123,
		BSSM_ADT2_PxShp = 0x124,
		BSSM_ADT2_GPxShp = 0x125,
		BSSM_ADT2_HShp = 0x126,
		BSSM_ADT2_SShp = 0x127,
		BSSM_ADT2_SGShp = 0x128,
		BSSM_ADT2_SFgShp = 0x129,
		BSSM_ADT2_SbShp = 0x12A,
		BSSM_ADT2_SHShp = 0x12B,
		BSSM_DIFFUSEDIR = 0x12C,
		BSSM_DIFFUSEPT = 0x12D,
		BSSM_DIFFUSEDIR_S = 0x12E,
		BSSM_DIFFUSEPT_S = 0x12F,
		BSSM_DIFFUSEDIR_Sb = 0x130,
		BSSM_DIFFUSEPT_Sb = 0x131,
		BSSM_DIFFUSEPT2 = 0x132,
		BSSM_DIFFUSEPT2_Fg = 0x133,
		BSSM_DIFFUSEPT2_Px = 0x134,
		BSSM_DIFFUSEPT2_S = 0x135,
		BSSM_DIFFUSEPT2_SFg = 0x136,
		BSSM_DIFFUSEPT2_Sb = 0x137,
		BSSM_DIFFUSEPT2_Shp = 0x138,
		BSSM_DIFFUSEPT2_FgShp = 0x139,
		BSSM_DIFFUSEPT2_PxShp = 0x13A,
		BSSM_DIFFUSEPT2_SShp = 0x13B,
		BSSM_DIFFUSEPT2_SFgShp = 0x13C,
		BSSM_DIFFUSEPT2_SbShp = 0x13D,
		BSSM_DIFFUSEPT3 = 0x13E,
		BSSM_DIFFUSEPT3_Fg = 0x13F,
		BSSM_DIFFUSEPT3_Px = 0x140,
		BSSM_DIFFUSEPT3_S = 0x141,
		BSSM_DIFFUSEPT3_SFg = 0x142,
		BSSM_DIFFUSEPT3_Sb = 0x143,
		BSSM_DIFFUSEPT3_Shp = 0x144,
		BSSM_DIFFUSEPT3_FgShp = 0x145,
		BSSM_DIFFUSEPT3_PxShp = 0x146,
		BSSM_DIFFUSEPT3_SShp = 0x147,
		BSSM_DIFFUSEPT3_SFgShp = 0x148,
		BSSM_DIFFUSEPT3_SbShp = 0x149,
		BSSM_TEXTURE = 0x14A,
		BSSM_TEXTURE_Fg = 0x14B,
		BSSM_TEXTURE_H = 0x14C,
		BSSM_TEXTURE_S = 0x14D,
		BSSM_TEXTURE_Vc = 0x14E,
		BSSM_TEXTURE_SVc = 0x14F,
		BSSM_TEXTURE_SFg = 0x150,
		BSSM_TEXTURE_Sb = 0x151,
		BSSM_TEXTURE_SH = 0x152,
		BSSM_TEXTURE_Px = 0x153,
		BSSM_SPECULARDIR = 0x154,
		BSSM_SPECULARPT = 0x155,
		BSSM_SPECULARDIR_S = 0x156,
		BSSM_SPECULARPT_S = 0x157,
		BSSM_2x_SPECULARDIR = 0x15A,
		BSSM_2x_SPECULARDIR_H = 0x15B,
		BSSM_2x_SPECULARDIR_Px = 0x15C,
		BSSM_2x_SPECULARDIR_S = 0x15D,
		BSSM_2x_SPECULARDIR_SH = 0x15E,
		BSSM_2x_SPECULARDIR_Sb = 0x15F,
		BSSM_2x_SPECULARDIR_Shp = 0x160,
		BSSM_2x_SPECULARDIR_HShp = 0x161,
		BSSM_2x_SPECULARDIR_PxShp = 0x162,
		BSSM_2x_SPECULARDIR_SShp = 0x163,
		BSSM_2x_SPECULARDIR_SHShp = 0x164,
		BSSM_2x_SPECULARDIR_SbShp = 0x165,
		BSSM_2x_SPECULARPT = 0x166,
		BSSM_2x_SPECULARPT_H = 0x167,
		BSSM_2x_SPECULARPT_Px = 0x168,
		BSSM_2x_SPECULARPT_S = 0x169,
		BSSM_2x_SPECULARPT_SH = 0x16A,
		BSSM_2x_SPECULARPT_Sb = 0x16B,
		BSSM_2x_SPECULARPT2 = 0x16C,
		BSSM_2x_SPECULARPT2_H = 0x16D,
		BSSM_2x_SPECULARPT2_Px = 0x16E,
		BSSM_2x_SPECULARPT2_S = 0x16F,
		BSSM_2x_SPECULARPT2_SH = 0x170,
		BSSM_2x_SPECULARPT2_Sb = 0x171,
		BSSM_2x_SPECULARPT3 = 0x172,
		BSSM_2x_SPECULARPT3_H = 0x173,
		BSSM_2x_SPECULARPT3_Px = 0x174,
		BSSM_2x_SPECULARPT3_S = 0x175,
		BSSM_2x_SPECULARPT3_SH = 0x176,
		BSSM_2x_SPECULARPT3_Sb = 0x177,
		BSSM_3XOCCLUSION = 0x178,
		BSSM_3XLIGHTING = 0x17F,
		BSSM_3XLIGHTING_S = 0x180,
		BSSM_3XLIGHTING_H = 0x181,
		BSSM_3XLIGHTING_Px = 0x182,
		BSSM_3XLIGHTING_Pxo = 0x183,
		BSSM_3XLIGHTING_Fg = 0x184,
		BSSM_3XLIGHTING_SFg = 0x185,
		BSSM_3XLIGHTING_G = 0x186,
		BSSM_3XLIGHTING_SG = 0x187,
		BSSM_3XLIGHTING_Vc = 0x188,
		BSSM_3XLIGHTING_VcS = 0x189,
		BSSM_3XLIGHTING_VcPx = 0x18A,
		BSSM_3XLIGHTING_VcPxo = 0x18B,
		BSSM_3XLIGHTING_VcG = 0x18C,
		BSSM_3XLIGHTING_VcSG = 0x18D,
		BSSM_3XLIGHTING_Spc = 0x18E,
		BSSM_3XLIGHTING_SSpc = 0x18F,
		BSSM_3XLIGHTING_HSpc = 0x190,
		BSSM_3XLIGHTING_PxSpc = 0x191,
		BSSM_3XLIGHTING_PxoSpc = 0x192,
		BSSM_3XLIGHTING_FgSpc = 0x193,
		BSSM_3XLIGHTING_SFgSpc = 0x194,
		BSSM_3XLIGHTING_GSpc = 0x195,
		BSSM_3XLIGHTING_SGSpc = 0x196,
		BSSM_3XLIGHTING_VcSpc = 0x197,
		BSSM_3XLIGHTING_VcSSpc = 0x198,
		BSSM_3XLIGHTING_VcPxSpc = 0x199,
		BSSM_3XLIGHTING_VcPxoSpc = 0x19A,
		BSSM_3XLIGHTING_VcGSpc = 0x19B,
		BSSM_3XLIGHTING_VcSGSpc = 0x19C,
		BSSM_3XLIGHTING_Shp = 0x19D,
		BSSM_3XLIGHTING_SShp = 0x19E,
		BSSM_3XLIGHTING_HShp = 0x19F,
		BSSM_3XLIGHTING_PxShp = 0x1A0,
		BSSM_3XLIGHTING_PxoShp = 0x1A1,
		BSSM_3XLIGHTING_FgShp = 0x1A2,
		BSSM_3XLIGHTING_SFgShp = 0x1A3,
		BSSM_3XLIGHTING_GShp = 0x1A4,
		BSSM_3XLIGHTING_SGShp = 0x1A5,
		BSSM_3XLIGHTING_VcShp = 0x1A6,
		BSSM_3XLIGHTING_VcSShp = 0x1A7,
		BSSM_3XLIGHTING_VcPxShp = 0x1A8,
		BSSM_3XLIGHTING_VcPxoShp = 0x1A9,
		BSSM_3XLIGHTING_VcGShp = 0x1AA,
		BSSM_3XLIGHTING_VcSGShp = 0x1AB,
		BSSM_3XLIGHTING_ShpSpc = 0x1AC,
		BSSM_3XLIGHTING_SShpSpc = 0x1AD,
		BSSM_3XLIGHTING_HShpSpc = 0x1AE,
		BSSM_3XLIGHTING_PxShpSpc = 0x1AF,
		BSSM_3XLIGHTING_PxoShpSpc = 0x1B0,
		BSSM_3XLIGHTING_FgShpSpc = 0x1B1,
		BSSM_3XLIGHTING_SFgShpSpc = 0x1B2,
		BSSM_3XLIGHTING_GShpSpc = 0x1B3,
		BSSM_3XLIGHTING_SGShpSpc = 0x1B4,
		BSSM_3XLIGHTING_VcShpSpc = 0x1B5,
		BSSM_3XLIGHTING_VcSShpSpc = 0x1B6,
		BSSM_3XLIGHTING_VcPxShpSpc = 0x1B7,
		BSSM_3XLIGHTING_VcPxoShpSpc = 0x1B8,
		BSSM_3XLIGHTING_VcGShpSpc = 0x1B9,
		BSSM_3XLIGHTING_VcSGShpSpc = 0x1BA,
		BSSM_3XSILHOUETTE = 0x1BB,
		BSSM_3XSILHOUETTE_Vc = 0x1BC,
		BSSM_3XENVMAP = 0x1BD,
		BSSM_3XENVMAP_W = 0x1BE,
		BSSM_3XENVMAP_Vc = 0x1BF,
		BSSM_3XENVMAP_WVc = 0x1C0,
		BSSM_3XENVMAP_S = 0x1C1,
		BSSM_3XENVMAP_SVc = 0x1C2,
		BSSM_3XENVMAP_EYE = 0x1C3,
		BSSM_3XLIGHTING_SIMPLESHADOW = 0x1C4,
		BSSM_3XLIGHTING_SIMPLESHADOW_Vc = 0x1C5,
		BSSM_3XLIGHTING_SIMPLESHADOW_S = 0x1C6,
		BSSM_3XLIGHTING_SIMPLESHADOW_VcS = 0x1C7,
		BSSM_3XDEPTHMAP = 0x1C8,
		BSSM_3XDEPTHMAP_Vc = 0x1C9,
		BSSM_3XDEPTHMAP_S = 0x1CA,
		BSSM_3XDEPTHMAP_VcS = 0x1CB,
		BSSM_3XRENDERNORMALS = 0x1CC,
		BSSM_3XRENDERNORMALS_Vc = 0x1CD,
		BSSM_3XRENDERNORMALS_S = 0x1CE,
		BSSM_3XRENDERNORMALS_VcS = 0x1CF,
		BSSM_3XRENDERNORMALS_FIRE = 0x1D0,
		BSSM_3XRENDERNORMALS_CLEAR = 0x1D1,
		BSSM_3XRENDERNORMALS_CLEAR_S = 0x1D2,
		BSSM_3XCONSTALPHA = 0x1D3,
		BSSM_3XCONSTALPHA_Vc = 0x1D4,
		BSSM_3XCONSTALPHA_S = 0x1D5,
		BSSM_3XCONSTALPHA_SVc = 0x1D6,
		BSSM_3XDEPTH = 0x1D7,
		BSSM_3XDEPTH_Vc = 0x1D8,
		BSSM_3XDEPTH_S = 0x1D9,
		BSSM_3XDEPTH_SVc = 0x1DA,
		BSSM_3XVELOCITY = 0x1DB,
		BSSM_3XVELOCITY_S = 0x1DC,
		BSSM_3XLOCALMAP = 0x1DD,
		BSSM_3XLOCALMAP_S = 0x1DE,
		BSSM_3XLOCALMAP_CLEAR = 0x1DF,
		BSSM_3XTEXEFFECT = 0x1E0,
		BSSM_3XTEXEFFECT_S = 0x1E1,
		BSSM_RENDERNORMALS = 0x1E2,
		BSSM_RENDERNORMALS_S = 0x1E3,
		BSSM_RENDERNORMALS_FIRE = 0x1E4,
		BSSM_RENDERNORMALS_CLEAR = 0x1E5,
		BSSM_RENDERNORMALS_CLEAR_S = 0x1E6,
		BSSM_DEPTH = 0x1E7,
		BSSM_DEPTH_S = 0x1E8,
		BSSM_DEPTH_Mn = 0x1E9,
		BSSM_VELOCITY = 0x1EA,
		BSSM_VELOCITY_S = 0x1EB,
		BSSM_LOCALMAP = 0x1EC,
		BSSM_LOCALMAP_S = 0x1ED,
		BSSM_LOCALMAP_CLEAR = 0x1EE,
		BSSM_LANDDIFF = 0x1EF,
		BSSM_LAND2xDIFF = 0x1F0,
		BSSM_LAND_G = 0x1F1,
		BSSM_LANDAD_A = 0x1F2,
		BSSM_LANDAD_AShp = 0x1F3,
		BSSM_LAND_GA = 0x1F4,
		BSSM_LANDDIFF_A = 0x1F5,
		BSSM_LAND2xDIFF_A = 0x1F6,
		BSSM_LAND1O = 0x1F7,
		BSSM_LAND1O_Shp = 0x1F8,
		BSSM_LAND1O_Simple = 0x1F9,
		BSSM_LAND1O_SimpleShp = 0x1FA,
		BSSM_LAND1O4 = 0x1FB,
		BSSM_LAND1O4_Shp = 0x1FC,
		BSSM_LAND1O4_Simple = 0x1FD,
		BSSM_LAND1O4_SimpleShp = 0x1FE,
		BSSM_LAND2O = 0x1FF,
		BSSM_LAND2O_Shp = 0x200,
		BSSM_LAND2O_Simple = 0x201,
		BSSM_LAND2O_SimpleShp = 0x202,
		BSSM_LAND2O4 = 0x203,
		BSSM_LAND2O4_Shp = 0x204,
		BSSM_LAND2O4_Simple = 0x205,
		BSSM_LAND2O4_SimpleShp = 0x206,
		BSSM_LAND3O = 0x207,
		BSSM_LAND3O_Shp = 0x208,
		BSSM_LAND3O_Simple = 0x209,
		BSSM_LAND3O_SimpleShp = 0x20A,
		BSSM_LAND3O4 = 0x20B,
		BSSM_LAND3O4_Shp = 0x20C,
		BSSM_LAND3O4_Simple = 0x20D,
		BSSM_LAND3O4_SimpleShp = 0x20E,
		BSSM_LAND4O = 0x20F,
		BSSM_LAND4O_Shp = 0x210,
		BSSM_LAND4O_Simple = 0x211,
		BSSM_LAND4O_SimpleShp = 0x212,
		BSSM_LAND4O4 = 0x213,
		BSSM_LAND4O4_Shp = 0x214,
		BSSM_LAND4O4_Simple = 0x215,
		BSSM_LAND4O4_SimpleShp = 0x216,
		BSSM_LAND5O = 0x217,
		BSSM_LAND5O_Shp = 0x218,
		BSSM_LAND5O_Simple = 0x219,
		BSSM_LAND5O_SimpleShp = 0x21A,
		BSSM_LAND5O4 = 0x21B,
		BSSM_LAND5O4_Shp = 0x21C,
		BSSM_LAND5O4_Simple = 0x21D,
		BSSM_LAND5O4_SimpleShp = 0x21E,
		BSSM_LAND6O = 0x21F,
		BSSM_LAND6O_Shp = 0x220,
		BSSM_LAND6O_Simple = 0x221,
		BSSM_LAND6O_SimpleShp = 0x222,
		BSSM_LAND6O4 = 0x223,
		BSSM_LAND6O4_Shp = 0x224,
		BSSM_LAND6O4_Simple = 0x225,
		BSSM_LAND6O4_SimpleShp = 0x226,
		BSSM_LAND7O = 0x227,
		BSSM_LAND7O_Shp = 0x228,
		BSSM_LAND7O_Simple = 0x229,
		BSSM_LAND7O_SimpleShp = 0x22A,
		BSSM_LAND7O4 = 0x22B,
		BSSM_LAND7O4_Shp = 0x22C,
		BSSM_LAND7O4_Simple = 0x22D,
		BSSM_LAND7O4_SimpleShp = 0x22E,
		BSSM_LANDO_Am = 0x22F,
		BSSM_LANDLO_A = 0x230,
		BSSM_2x_SIMPLESHADOW = 0x231,
		BSSM_2x_SIMPLESHADOW_S = 0x232,
		BSSM_2x_SIMPLESHADOW_LAND = 0x233,
		BSSM_2x_SIMPLESHADOW_Sb = 0x234,
		BSSM_ADT_Sbb = 0x235,
		BSSM_DISTANT_TREE_BASE = 0x236,
		BSSM_UNK_237 = 0x237,
		BSSM_SKYBASEPRE = 0x238,
		BSSM_SKY = 0x239,
		BSSM_SKY_MOON_STARS_MASK = 0x23A,
		BSSM_SKY_STARS = 0x23B,
		BSSM_SKY_TEXTURE = 0x23C,
		BSSM_SKY_CLOUDS = 0x23D,
		BSSM_SKY_CLOUDS_UNDERWATER = 0x23E,
		BSSM_WATER_LOD = 0x23F,
		BSSM_WATER_LOD_NO_REFLECTIONS = 0x240,
		BSSM_PARTICLE = 0x241,
		BSSM_BOLT = 0x242,
		BSSM_BEAM = 0x243,
		BSSM_ENVMAP = 0x244,
		BSSM_ENVMAP_Vc = 0x245,
		BSSM_ENVMAP_S = 0x246,
		BSSM_ENVMAP_SVc = 0x247,
		BSSM_2x_ENVMAP = 0x248,
		BSSM_2x_ENVMAP_S = 0x249,
		BSSM_2x_ENVMAP_W = 0x24A,
		BSSM_2x_ENVMAP_EYE = 0x24B,
		BSSM_GEOMDECAL = 0x24C,
		BSSM_GEOMDECAL_S = 0x24D,
		BSSM_TEXEFFECT = 0x24E,
		BSSM_TEXEFFECT_S = 0x24F,
		BSSM_2x_TEXEFFECT = 0x250,
		BSSM_2x_TEXEFFECT_S = 0x251,
		BSSM_FOG = 0x252,
		BSSM_FOG_A = 0x253,
		BSSM_FOG_S = 0x254,
		BSSM_FOG_SA = 0x255,
		BSSM_FOG_Sb = 0x256,
		BSSM_VFOG_1 = 0x259,
		BSSM_VFOG_2 = 0x25A,
		BSSM_VFOG_3 = 0x25B,
		BSSM_GRASS_DIRONLY_LF = 0x25C,
		BSSM_GRASS_DIRONLY_LV = 0x25D,
		BSSM_GRASS_DIRONLY_LFS = 0x25E,
		BSSM_GRASS_DIRONLY_LVS = 0x25F,
		BSSM_GRASS_DIRONLY_LFP = 0x260,
		BSSM_GRASS_DIRONLY_LVP = 0x261,
		BSSM_GRASS_DIRONLY_LFSP = 0x262,
		BSSM_GRASS_DIRONLY_LVSP = 0x263,
		BSSM_GRASS_DIRONLY_LFShp = 0x264,
		BSSM_GRASS_DIRONLY_LVShp = 0x265,
		BSSM_GRASS_DIRONLY_LFSShp = 0x266,
		BSSM_GRASS_DIRONLY_LVSShp = 0x267,
		BSSM_GRASS_DIRONLY_LFPShp = 0x268,
		BSSM_GRASS_DIRONLY_LVPShp = 0x269,
		BSSM_GRASS_DIRONLY_LFSPShp = 0x26A,
		BSSM_GRASS_DIRONLY_LVSPShp = 0x26B,
		BSSM_GRASS_DIRONLY_LFB = 0x26C,
		BSSM_GRASS_DIRONLY_LFSB = 0x26D,
		BSSM_GRASS_DIRONLY_LFPB = 0x26E,
		BSSM_GRASS_DIRONLY_LFSPB = 0x26F,
		BSSM_GRASS_1POINT_LF = 0x270,
		BSSM_GRASS_1POINT_LV = 0x271,
		BSSM_GRASS_1POINT_LFS = 0x272,
		BSSM_GRASS_1POINT_LVS = 0x273,
		BSSM_GRASS_1POINT_LFP = 0x274,
		BSSM_GRASS_1POINT_LVP = 0x275,
		BSSM_GRASS_1POINT_LFSP = 0x276,
		BSSM_GRASS_1POINT_LVSP = 0x277,
		BSSM_GRASS_1POINT_LFShp = 0x278,
		BSSM_GRASS_1POINT_LVShp = 0x279,
		BSSM_GRASS_1POINT_LFSShp = 0x27A,
		BSSM_GRASS_1POINT_LVSShp = 0x27B,
		BSSM_GRASS_1POINT_LFPShp = 0x27C,
		BSSM_GRASS_1POINT_LVPShp = 0x27D,
		BSSM_GRASS_1POINT_LFSPShp = 0x27E,
		BSSM_GRASS_1POINT_LVSPShp = 0x27F,
		BSSM_GRASS_1POINT_LFB = 0x280,
		BSSM_GRASS_1POINT_LFSB = 0x281,
		BSSM_GRASS_1POINT_LFPB = 0x282,
		BSSM_GRASS_1POINT_LFSPB = 0x283,
		BSSM_GRASS_SHADOW_L = 0x284,
		BSSM_GRASS_SHADOW_LS = 0x285,
		BSSM_GRASS_SHADOW_LB = 0x286,
		BSSM_GRASS_SHADOW_LSB = 0x287,
		BSSM_WATER_STENCIL = 0x288,
		BSSM_WATER_STENCIL_Vc = 0x289,
		BSSM_WATER_WADING = 0x28A,
		BSSM_WATER_WADING_NO_REFLECTIONS_NO_REFRACTIONS = 0x28B,
		BSSM_WATER_WADING_NO_REFRACTIONS = 0x28C,
		BSSM_WATER_WADING_NO_REFLECTIONS = 0x28D,
		BSSM_WATER_WADING_NO_DEPTH = 0x28E,
		BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS = 0x28F,
		BSSM_WATER_WADING_NO_DEPTH_NO_REFRACTIONS = 0x290,
		BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS = 0x291,
		BSSM_WATER_INTERIOR_WADING = 0x292,
		BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_NO_REFRACTIONS = 0x293,
		BSSM_WATER_INTERIOR_WADING_NO_REFRACTIONS = 0x294,
		BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS = 0x295,
		BSSM_WATER_INTERIOR_WADING_NO_DEPTH = 0x296,
		BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS = 0x297,
		BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFRACTIONS = 0x298,
		BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS = 0x299,
		BSSM_WATER_WADING_SPECULAR_LIGHTING = 0x29A,
		BSSM_WATER_WADING_Vc = 0x29B,
		BSSM_WATER_WADING_NO_REFLECTIONS_Vc = 0x29C,
		BSSM_WATER_WADING_NO_REFRACTIONS_Vc = 0x29D,
		BSSM_WATER_WADING_NO_REFLECTIONS_NO_REFRACTIONS_Vc = 0x29E,
		BSSM_WATER_WADING_NO_DEPTH_Vc = 0x29F,
		BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_Vc = 0x2A0,
		BSSM_WATER_WADING_NO_DEPTH_NO_REFRACTIONS_Vc = 0x2A1,
		BSSM_WATER_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc = 0x2A2,
		BSSM_WATER_INTERIOR_WADING_Vc = 0x2A3,
		BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_Vc = 0x2A4,
		BSSM_WATER_INTERIOR_WADING_NO_REFRACTIONS_Vc = 0x2A5,
		BSSM_WATER_INTERIOR_WADING_NO_REFLECTIONS_NO_REFRACTIONS_Vc = 0x2A6,
		BSSM_WATER_INTERIOR_WADING_NO_DEPTH_Vc = 0x2A7,
		BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_Vc = 0x2A8,
		BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFRACTIONS_Vc = 0x2A9,
		BSSM_WATER_INTERIOR_WADING_NO_DEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc = 0x2AA,
		BSSM_WATER_WADING_SPECULAR_LIGHTING_Vc = 0x2AB,
		BSSM_WATER = 0x2AC,
		BSSM_WATER_NO_REFLECTIONS_NO_REFRACTIONS = 0x2AD,
		BSSM_WATER_NO_REFRACTIONS = 0x2AE,
		BSSM_WATER_NO_REFLECTIONS = 0x2AF,
		BSSM_WATER_INTERIOR = 0x2B0,
		BSSM_WATER_INTERIOR_NO_REFLECTIONS_NO_REFRACTIONS = 0x2B1,
		BSSM_WATER_INTERIOR_NO_REFRACTIONS = 0x2B2,
		BSSM_WATER_INTERIOR_NO_REFLECTIONS = 0x2B3,
		BSSM_WATER_NODEPTH = 0x2B4,
		BSSM_WATER_NODEPTH_NO_REFLECTIONS = 0x2B5,
		BSSM_WATER_NODEPTH_NO_REFRACTIONS = 0x2B6,
		BSSM_WATER_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS = 0x2B7,
		BSSM_WATER_INTERIOR_NODEPTH = 0x2B8,
		BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS = 0x2B9,
		BSSM_WATER_INTERIOR_NODEPTH_NO_REFRACTIONS = 0x2BA,
		BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS = 0x2BB,
		BSSM_WATER_SPECULAR_LIGHTING = 0x2BC,
		BSSM_WATER_UNDERWATER = 0x2BD,
		BSSM_WATER_Vc = 0x2BE,
		BSSM_WATER_NO_REFLECTIONS_NO_REFRACTIONS_Vc = 0x2BF,
		BSSM_WATER_NO_REFRACTIONS_Vc = 0x2C0,
		BSSM_WATER_NO_REFLECTIONS_Vc = 0x2C1,
		BSSM_WATER_INTERIOR_Vc = 0x2C2,
		BSSM_WATER_INTERIOR_NO_REFLECTIONS_NO_REFRACTIONS_Vc = 0x2C3,
		BSSM_WATER_INTERIOR_NO_REFRACTIONS_Vc = 0x2C4,
		BSSM_WATER_INTERIOR_NO_REFLECTIONS_Vc = 0x2C5,
		BSSM_WATER_NODEPTH_Vc = 0x2C6,
		BSSM_WATER_NODEPTH_NO_REFLECTIONS_Vc = 0x2C7,
		BSSM_WATER_NODEPTH_NO_REFRACTIONS_Vc = 0x2C8,
		BSSM_WATER_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc = 0x2C9,
		BSSM_WATER_INTERIOR_NODEPTH_Vc = 0x2CA,
		BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_NO_REFRACTIONS_Vc = 0x2CB,
		BSSM_WATER_INTERIOR_NODEPTH_NO_REFRACTIONS_Vc = 0x2CC,
		BSSM_WATER_INTERIOR_NODEPTH_NO_REFLECTIONS_Vc = 0x2CD,
		BSSM_WATER_SPECULAR_LIGHTING_Vc = 0x2CE,
		BSSM_PRECIPITATION_RAIN = 0x2CF,
		BSSM_SKYBASEPOST = 0x2D0,
		BSSM_SELFILLUM_SKY = 0x2D1,
		BSSM_SKY_SUNGLARE = 0x2D2,
		BSSM_SELFILLUM_SKY_SUN = 0x2D3,
		BSSM_SELFILLUM_SKY_CLOUDS = 0x2D4,
		BSSM_SELFILLUM_SKY_SKY_QUAD = 0x2D5,
		BSSM_SELFILLUMALPHA = 0x2D6,
		BSSM_SELFILLUMALPHA_S = 0x2D7,
		BSSM_WATER_DEPTH = 0x2D8,
		BSSM_WATER_DEPTH_S = 0x2D9,
		BSSM_3XWATER_DEPTH = 0x2DA,
		BSSM_3XWATER_DEPTH_S = 0x2DB,
		BSSM_NLWATER_DEPTH = 0x2DC,
		BSSM_NLWATER_DEPTH_S = 0x2DD,
		BSSM_WATER_DEPTH_At = 0x2DE,
		BSSM_WATER_DEPTH_SAt = 0x2DF,
		BSSM_3XWATER_DEPTH_At = 0x2E0,
		BSSM_3XWATER_DEPTH_SAt = 0x2E1,
		BSSM_NLWATER_DEPTH_At = 0x2E2,
		BSSM_NLWATER_DEPTH_At_S = 0x2E3,
		BSSM_WATER_DEPTH_Vc = 0x2E4,
		BSSM_WATER_DEPTH_SVc = 0x2E5,
		BSSM_3XWATER_DEPTH_Vc = 0x2E6,
		BSSM_3XWATER_DEPTH_SVc = 0x2E7,
		BSSM_NLWATER_DEPTH_Vc = 0x2E8,
		BSSM_NLWATER_DEPTH_Vc_S = 0x2E9,
		BSSM_WATER_DEPTH_AtVc = 0x2EA,
		BSSM_WATER_DEPTH_SAtVc = 0x2EB,
		BSSM_3XWATER_DEPTH_AtVc = 0x2EC,
		BSSM_3XWATER_DEPTH_SAtVc = 0x2ED,
		BSSM_NLWATER_DEPTH_AtVc = 0x2EE,
		BSSM_NLWATER_DEPTH_AtVc_S = 0x2EF,
		BSSM_BLOOD_SPLATTER_FLARE = 0x2F0,
		BSSM_BLOOD_SPLATTER = 0x2F1,
		BSSM_SHADOWVOLUME_BACK = 0x2F2,
		BSSM_SHADOWVOLUME_FRONT = 0x2F3,
		BSSM_SHADOWVOLUME_WIRE = 0x2F4,
		BSSM_TILE = 0x2F5,
		BSSM_IMAGESPACE = 0x2F6,
		BSSM_FINAL_PASS = 0x2F7,
	};

	enum LightingPasses : UInt32 {
		BSSM_PASS_NONE = 0x0,
		BSSM_PASS_AMBIENT = 0x1,
		BSSM_PASS_DIFFUSE = 0x2,
		BSSM_PASS_TEXTURE = 0x4,
		BSSM_PASS_SPECULAR = 0x8,
		BSSM_PASS_SHADOW = 0x10,
		BSSM_PASS_CANOPYSHADOW = 0x20,
		BSSM_PASS_OPT = 0x100,
		BSSM_PASS_ALL = BSSM_PASS_AMBIENT | BSSM_PASS_DIFFUSE | BSSM_PASS_TEXTURE | BSSM_PASS_SPECULAR | BSSM_PASS_SHADOW | BSSM_PASS_CANOPYSHADOW | BSSM_PASS_OPT,
	};

	enum RenderMode : UInt32 {
		BSSM_RENDER_NORMAL = 0x0, // Renders everything as you'd expect
		BSSM_RENDER_UNK1 = 0x1,
		BSSM_RENDER_UNK2 = 0x2,
		BSSM_RENDER_UNK3 = 0x3,
		BSSM_RENDER_UNK4 = 0x4,
		BSSM_RENDER_UNK5 = 0x5,
		BSSM_RENDER_UNK6 = 0x6,
		BSSM_RENDER_DEPTH_MAP = 0x7,
		BSSM_RENDER_CONST_ALPHA = 0x8, // Everything is green
		BSSM_RENDER_LOCAL_MAP = 0x9, // Renders vertex normals, skips landscape
		BSSM_RENDER_TILES = 0xA,
		BSSM_RENDER_UNK11 = 0xB,
		BSSM_RENDER_NO_WATER_PASS = 0xC, // Skips water rendering
		BSSM_RENDER_UNK13 = 0xD,
		BSSM_RENDER_WATER_DEPTH = 0xE,
		BSSM_RENDER_SILHOUETTE = 0xF, // Everything is black except for grass, sky and emissives
	};
};