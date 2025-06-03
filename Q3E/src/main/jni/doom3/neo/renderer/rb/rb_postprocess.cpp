idCVar r_renderMode( "r_renderMode", "0", CVAR_RENDERER | CVAR_ARCHIVE | CVAR_INTEGER, "retro postprocess render. 0 = Doom, 1 = CGA, 2 = CGA Highres, 3 = Commodore 64, 4 = Commodore 64 Highres, 5 = Amstrad CPC 6128, 6 = Amstrad CPC 6128 Highres, 7 = Sega Genesis, 8 = Sega Genesis Highres, 9 = Sony PSX", 0, 9, idCmdSystem::ArgCompletion_Integer<0, 9> );
idCVar r_retroDitherScale( "r_retroDitherScale", "0.3", CVAR_RENDERER | CVAR_FLOAT, "" );

enum RenderMode
{
    RENDERMODE_DOOM,
    RENDERMODE_2BIT,
    RENDERMODE_2BIT_HIGHRES,
    RENDERMODE_C64,
    RENDERMODE_C64_HIGHRES,
    RENDERMODE_CPC,
    RENDERMODE_CPC_HIGHRES,
    RENDERMODE_GENESIS,
    RENDERMODE_GENESIS_HIGHRES,
    RENDERMODE_PSX,
};

void RB_PP_Render(void)
{
    if(r_renderMode.GetInteger() == 0)
        return;

    float jitterTexScale[4] = { 0.0f };

    switch (r_renderMode.GetInteger())
    {
        case RENDERMODE_2BIT:
            jitterTexScale[0] = 1.0f;
            GL_UseProgram(&retro2BitShader);
            break;
        case RENDERMODE_2BIT_HIGHRES:
            jitterTexScale[0] = 2.0f;
            GL_UseProgram(&retro2BitShader);
            break;
        case RENDERMODE_C64:
            jitterTexScale[0] = 1.0f;
            GL_UseProgram(&retroC64Shader);
            break;
        case RENDERMODE_C64_HIGHRES:
            jitterTexScale[0] = 2.0f;
            GL_UseProgram(&retroC64Shader);
            break;
        case RENDERMODE_CPC:
            jitterTexScale[0] = 1.0f;
            GL_UseProgram(&retroCPCShader);
            break;
        case RENDERMODE_CPC_HIGHRES:
            jitterTexScale[0] = 2.0f;
            GL_UseProgram(&retroCPCShader);
            break;
        case RENDERMODE_GENESIS:
            jitterTexScale[0] = 1.0f;
            GL_UseProgram(&retroGenesisShader);
            break;
        case RENDERMODE_GENESIS_HIGHRES:
            jitterTexScale[0] = 2.0f;
            GL_UseProgram(&retroGenesisShader);
            break;
        case RENDERMODE_PSX:
            GL_UseProgram(&retroPS1Shader);
            break;
        default:
            return;
    }
    jitterTexScale[1] = r_retroDitherScale.GetFloat();
    GL_Uniform4fv(SHADER_PARMS_ADDR(u_uniformParm, 0), jitterTexScale);

    const int &x = backEnd.viewDef->viewport.x1;
    const int &y = backEnd.viewDef->viewport.y1;
    const int w = backEnd.viewDef->viewport.x2 - backEnd.viewDef->viewport.x1 + 1;
    const int h = backEnd.viewDef->viewport.y2 - backEnd.viewDef->viewport.y1 + 1;

	if (r_useScissor.GetBool()) {
		qglScissor(x, y, w, h);
		backEnd.currentScissor = backEnd.viewDef->scissor;
	}

    GLboolean depthMask;
    GLint bufferId;
    qglGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
    qglGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bufferId);
    GLboolean isBlend = qglIsEnabled(GL_BLEND);
    GLboolean isDepthTest = qglIsEnabled(GL_DEPTH_TEST);

	//int glState = backEnd.glState.glStateBits;
	//GL_State(GLS_SRCBLEND_ONE | GLS_DSTBLEND_ZERO);


    if(isBlend) qglDisable(GL_BLEND);
    if(isDepthTest)
        qglDisable(GL_DEPTH_TEST);
    if(depthMask)
        qglDepthMask(GL_FALSE);
	if(bufferId != 0)
		qglBindBuffer(GL_ARRAY_BUFFER, 0);

	const float hw = (float)w * 0.5f;
	const float hh = (float)h * 0.5f;

    const float vs[] = {
            -hw, -hh,
            hw, -hh,
            -hw, hh,
            hw, hh,
    };
    static const float ts[] = {
            0,0,
            1,0,
            0,1,
            1,1,
    };

    globalImages->frameImage->CopyFramebuffer(0, 0, glConfig.vidWidth, glConfig.vidHeight, true);
	const float sw = glConfig.vidWidth;
	const float sh = glConfig.vidHeight;

    float	parm[4];
    float		pot;

    parm[2] = 0.0f;
    parm[3] = 1.0f;

    // screen power of two correction factor, assuming the copy to _currentRender
    // also copied an extra row and column for the bilerp
    pot = globalImages->frameImage->uploadWidth;
    parm[0] = sw / pot;

    pot = globalImages->frameImage->uploadHeight;
    parm[1] = sh / pot;

    GL_Uniform4fv(SHADER_PARM_ADDR(nonPowerOfTwo), parm);

    // window coord to 0.0 to 1.0 conversion
    parm[0] = 1.0f / sw;
    parm[1] = 1.0f / sh;
	//karin: need x and y offset coord if copy framebuffer with current viewport, and uv = gl_FragCoord.xy - nonPowerOfTwo.zw in fragment shader
    //parm[2] = x;
    //parm[3] = y;
    GL_Uniform4fv(SHADER_PARM_ADDR(windowCoords), parm);

    GL_SelectTexture( 0 );
    globalImages->frameImage->Bind();

    GL_EnableVertexAttribArray(SHADER_PARM_ADDR(attr_Vertex));
    GL_EnableVertexAttribArray(SHADER_PARM_ADDR(attr_TexCoord));

    GL_VertexAttribPointer(offsetof(shaderProgram_t, attr_Vertex), 2, GL_FLOAT, false, 0, vs);
    GL_VertexAttribPointer(offsetof(shaderProgram_t, attr_TexCoord), 2, GL_FLOAT, false, 0, ts);

    qglDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    globalImages->BindNull();

    GL_DisableVertexAttribArray(SHADER_PARM_ADDR(attr_Vertex));
    GL_DisableVertexAttribArray(SHADER_PARM_ADDR(attr_TexCoord));
    GL_UseProgram(NULL);

	//GL_State(glState);
    if(isBlend)
        qglEnable(GL_BLEND);
    if(isDepthTest)
        qglEnable(GL_DEPTH_TEST);
    if(depthMask)
        qglDepthMask(GL_TRUE);
    if(bufferId != 0)
        qglBindBuffer(GL_ARRAY_BUFFER, bufferId);
}
