//
// Shader Example.
// Copyleft (c) 2007 Heesung Oh(Galic Studio). All rights Not reserved.
//
////////////////////////////////////////////////////////////////////////////////


float4x4	m_mtWld;	// World
float4x4	m_mtViw;	// View Projection
float4x4	m_mtPrj;	// Projection
float3x3	m_mtRot;	// Rotation Matrix
float3		m_vcLgt;	// Lighting Direction
float3		m_vcCam;	// Camera Position
float		m_fShrp;	// Sharpness
float4		m_vColor;

// Output Vertex Processing Structure
struct SVsOut
{
	float4 Pos	: POSITION;
	float3 Nor	: TEXCOORD6;	// Normal Vector
	float3 Eye	: TEXCOORD7;	// Eye Direction Vector
};



// Vertex Shader Processing
SVsOut VtxPrc(	float3 Pos : POSITION,	// Local Position
				float3 Nor : NORMAL		// Normal Vector
			)
{
	SVsOut Out = (SVsOut)0;							// Initialize to Zero

	float4 P = float4(Pos, 1);

	P	= mul(P, m_mtWld);							// Transform Rotation, Scaling, Translation of Vertex Position

	float3 E = normalize(m_vcCam - P);				// Eye Vector = Camera Position - Transform World Vertex Position
	float3 N = mul(Nor, m_mtRot);					// Rotation Normal Vector

	P	= mul(P, m_mtViw);
	P	= mul(P, m_mtPrj);

	Out.Pos = P;									// Output Position
	Out.Eye = E;
	Out.Nor = N;

	return Out;
}


// Pixel Shader Processing
// (Pixel Shader 2.0 or later is required:compile ps_3_0)
float4 PxlPrc(SVsOut In) : COLOR
{
	float4 Out;

	float3 E = normalize(In.Eye);					// Eye Vector
	float3 N = normalize(In.Nor);					// Normal Vector
	float3 L = normalize(-m_vcLgt);
	float3 R = reflect(-L, N);						// Reflection Vector
	float4 S = pow( max(0, dot(R, E)), m_fShrp);	// Phong Shading

	float4 D;									// Output Color

	D	= (0.5f + dot(N, L)) * 0.2f;			// Lambert
	D.a = 1.0f;

	Out = S + D + m_vColor;
	Out.a = 1.0f;
	return Out;
}



technique Tech0
{
	pass P0
	{ 
		VertexShader = compile vs_3_0 VtxPrc();
		PixelShader  = compile ps_3_0 PxlPrc();
	}
}

