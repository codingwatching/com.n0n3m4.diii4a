//========================================//
// legacy_gfx_2d.shader
//========================================//


//========================================//
// HUD assets
//========================================//
// chat background
gfx/2d/colorbar
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/colorbar.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// disguised shader
gfx/2d/friendlycross
{
	nocompress
	nopicmip
	{
		map gfx/2d/friendlycross.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// disconnect icon
gfx/2d/net
{
	nocompress
	nopicmip
	{
		map gfx/2d/net.jpg
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}
//========================================//


//========================================//
// Cursorhints
// Fixed drawing with clampMap
//========================================//

gfx/2d/legacy_usablehint
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/usableHint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/legacy_breakablehint
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/breakablehint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/legacy_notusablehint
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/notusablehint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/legacy_healthhint
{
 	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/usableHint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/legacy_buttonhint
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/usableHint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/legacy_weaponhint
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/usableHint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/legacy_ammohint
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/usableHint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/legacy_poweruphint
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/usableHint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

gfx/2d/legacy_disarmhint
{
	nomipmaps
	nopicmip
	{
		clampMap gfx/2d/disarmhint.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}
//========================================//


//========================================//
// Crosshairs
//========================================//
// sharp crosshairs
gfx/2d/crosshairk
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairk.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// nothing
gfx/2d/crosshairk_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshaira_alt.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// slightly modified version of crosshair b so it centers
gfx/2d/crosshairl
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairl.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// sharp center version of b_alt
gfx/2d/crosshairl_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairl_alt.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// copy of c
gfx/2d/crosshairm
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairc.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// sharp version of b_alt
gfx/2d/crosshairm_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// copy of d
gfx/2d/crosshairn
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshaird.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// sharp version of d_alt
gfx/2d/crosshairn_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// copy of e
gfx/2d/crosshairo
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshaire.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

// sharp version of e_alt
gfx/2d/crosshairo_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}

//sharp dot
gfx/2d/crosshairp
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairp.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
// blurs even less, but artifacts at many sizes
//		alphaFunc GT0
		rgbGen vertex
	}
}

// nothing
gfx/2d/crosshairp_alt
{
	nocompress
	nopicmip
	{
		map gfx/2d/crosshairf_alt.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbGen vertex
	}
}
//========================================//
