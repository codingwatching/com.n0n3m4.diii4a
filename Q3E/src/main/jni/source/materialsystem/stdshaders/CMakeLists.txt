cmake_minimum_required(VERSION 3.9)
project (source-stdshader_dx9)

set(binary_name ${SOURCE_ENGINE_PREFIX}stdshader_dx9)

set(source_src 
		aftershock.cpp
		aftershock_helper.cpp
		AccumBuff4Sample.cpp
		accumbuff5sample.cpp
		BaseVSShader.cpp
		bik_dx90.cpp
		Bloom.cpp
		BlurFilterX.cpp
		BlurFilterY.cpp
		BufferClearObeyStencil_dx9.cpp
		cable_dx9.cpp
		cloak.cpp
		cloak_blended_pass_helper.cpp
		cloak_dx9_helper.cpp
		cloud_dx9.cpp
		colorcorrection.cpp
		compositor.cpp
		core_dx9.cpp
		color_projection.cpp
		debugmrttexture.cpp
		#debugmorphaccumulator_dx9.cpp					[$WIN32]
		DebugTextureView.cpp
		DecalBaseTimesLightmapAlphaBlendSelfIllum_dx9.cpp
		DecalModulate_dx9.cpp
		depthwrite.cpp
		Downsample.cpp
		downsample_nohdr.cpp
		Engine_Post_dx9.cpp
		emissive_scroll_blended_pass_helper.cpp
		eye_refract.cpp
		eye_refract_helper.cpp
		eyes_dx8_dx9_helper.cpp
		eyes_dx9.cpp
		eyeglint_dx9.cpp
		filmdust_dx8_dx9.cpp							
		filmgrain_dx8_dx9.cpp							
		flesh_interior_blended_pass_helper.cpp
		floatcombine.cpp
		floatcombine_autoexpose.cpp
		floattoscreen.cpp
		floattoscreen_vanilla.cpp
		HDRCombineTo16Bit.cpp
		HDRSelectRange.cpp
		hsl_filmgrain_pass1.cpp
		hsl_filmgrain_pass2.cpp
		hsv.cpp
		introscreenspaceeffect.cpp
		lightmappedgeneric_dx9.cpp
		lightmappedgeneric_dx9_helper.cpp
		lightmappedreflective.cpp
		modulate_dx9.cpp
		MonitorScreen_dx9.cpp
		#morphaccumulate_dx9.cpp					[$WIN32]
		#morphweight_dx9.cpp						[$WIN32]
		motion_blur_dx9.cpp
		occlusion_dx9.cpp
		particlelitgeneric_dx9.cpp
		particlelitgeneric_dx9_helper.cpp
		particlesphere_dx9.cpp
		pbr_dx9.cpp
		portal.cpp
		portalstaticoverlay.cpp
		portal_refract.cpp
		portal_refract_helper.cpp
		pyro_vision.cpp
		refract.cpp
		refract_dx9_helper.cpp
		#rendertargetblit_x360.cpp					[$X360]	
		sample4x4.cpp
		sample4x4_blend.cpp
		screenspace_general.cpp
		sfm_blurfilterx.cpp
		sfm_blurfiltery.cpp
		sfm_downsample.cpp
		sfm_integercombine.cpp
		shadow.cpp
		shadowbuild_dx9.cpp
		shadowmodel_dx9.cpp
		shatteredglass.cpp
		showz.cpp
		skin_dx9_helper.cpp
		sky_dx9.cpp
		sky_hdr_dx9.cpp
		sprite_dx9.cpp
		spritecard.cpp
		teeth.cpp
		TreeLeaf.cpp
		unlitgeneric_dx9.cpp
		unlittwotexture_dx9.cpp
		vertexlitgeneric_dx9.cpp
		vertexlitgeneric_dx9_helper.cpp
		volume_clouds.cpp
		volume_clouds_helper.cpp
		vortwarp_dx9.cpp
		vr_distort_hud.cpp
		vr_distort_texture.cpp
		warp.cpp
		water.cpp
		weapon_sheen_pass_helper.cpp
		windowimposter_dx90.cpp
		wireframe_dx9.cpp
		worldtwotextureblend.cpp
		worldvertexalpha.cpp
		worldvertextransition.cpp
		worldvertextransition_dx8_helper.cpp
		writez_dx9.cpp
		writestencil_dx9.cpp
		eyeball.cpp
		../../public/tier0/memoverride.cpp
#		$Folder	stdshader_dbg Files [$X360]
#		{
#			debugdepth.cpp
#			DebugDrawEnvmapMask.cpp
#			debugluxel.cpp
#			debugnormalmap.cpp
#			debugtangentspace.cpp
#			fillrate.cpp
)

set(source_inc 
		.
		../../public
		../../public/tier0
		../../public/tier1
		fxctmp9
		vshtmp9
)

set(source_def "STDSHADER_DX9_DLL_EXPORT=1;FAST_MATERIALVAR_ACCESS")

set(source_lib 
	${SOURCE_ENGINE_PREFIX}tier0 
	${SOURCE_ENGINE_PREFIX}shaderlib 
	${SOURCE_ENGINE_PREFIX}tier1 
	${SOURCE_ENGINE_PREFIX}mathlib  
	) # ANDROID_SUPPORT

add_library (${binary_name} SHARED ${source_src})
target_include_directories(${binary_name} PRIVATE ${source_inc})
set_target_properties(${binary_name} PROPERTIES COMPILE_DEFINITIONS "${source_def}")
target_link_libraries(${binary_name} PRIVATE ${source_lib})

